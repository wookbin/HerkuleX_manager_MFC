#define _CRT_SECURE_DEPRECATE_MEMORY
#define _CRT_SECURE_NO_WARNINGS
#define __HERKULEX_C
#include "stdafx.h"
#include <memory.h>
#include <math.h>
#include "herkulexlib.h"
#include "herkulex_protocol.h"
#undef __HERKULEX_C

//unsigned char EEP_REG_SIZE[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,1,1,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,1,1,1,1,1,1,1,2,0,1,1,1,1,1,1,1,1,1,1,1,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0 };
//unsigned char RAM_REG_SIZE[] = { 1,1,1,1,1,1,1,1,1,1,1,1,2,0,1,1,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0 };
unsigned char EEP_REG_SIZE[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,1,1,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0 };
unsigned char RAM_REG_SIZE[] = { 1,1,1,1,1,1,1,1,1,1,1,1,2,0,1,1,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0 };


#define EEPRegSize(addr) (EEP_REG_SIZE[addr])
#define RAMRegSize(addr) (RAM_REG_SIZE[addr])

DrsData* get_packet_data(void* packet)
{
	DrsPacket *pPacket = (DrsPacket*)packet;
	
	return &pPacket->unData;
}

unsigned char set_packet(void* buffer, unsigned char id, unsigned char cmd, int data_length)
{
	if (buffer == 0) 
		return MIN_PACKET_SIZE + data_length;

	DrsPacket *packet = (DrsPacket*)buffer;
	unsigned char i;

	//헤더 입력
	packet->ucHeader = HEADER;
	packet->ucPacketSize = (unsigned char)(MIN_PACKET_SIZE + data_length);
	packet->ucChipID = id;
	packet->ucCmd = cmd;

	//CheckSum 계산 후 입력
	packet->ucCheckSum1 = packet->ucPacketSize ^ packet->ucChipID ^ packet->ucCmd;
	for (i = 0; i < (packet->ucPacketSize - MIN_PACKET_SIZE); i++)
		packet->ucCheckSum1 ^= packet->unData.ucData[i];

	packet->ucCheckSum2 = (unsigned char)(~(packet->ucCheckSum1));
	packet->ucCheckSum1 &= CHKSUM_MASK;
	packet->ucCheckSum2 &= CHKSUM_MASK;

	return packet->ucPacketSize;
}

DrsPacket* get_ack_packet(void* buffer, int size, int* pos)
{
	int i, j;
	unsigned char check1, check2;
	unsigned char* buff = (unsigned char*)buffer;

	if (size < MIN_ACK_PACKET_SIZE) 
		return 0;

	for (i = 0; i <= size - MIN_ACK_PACKET_SIZE; i++)
	{
		DrsPacket *packet = (DrsPacket*)(buff + i);
		if (packet->ucHeader != HEADER) 
			continue;
		if (packet->ucPacketSize > size - i) 
			continue;

		check1 = packet->ucPacketSize ^ packet->ucChipID ^ packet->ucCmd;
		for (j = 0; j < (packet->ucPacketSize - MIN_PACKET_SIZE); j++)
			check1 ^= packet->unData.ucData[j];

		check2 = (unsigned char)(~(check1));
		check1 &= CHKSUM_MASK;
		check2 &= CHKSUM_MASK;
		if (packet->ucCheckSum1 != check1 || packet->ucCheckSum2 != check2) 
			continue;

		*pos = i + packet->ucPacketSize;

		return packet;
	}

	return 0;
}

DrsStatData* get_ack_status(DrsPacket* packet)
{
	DrsStatData *pStat = 0;
	if (packet->ucCmd == CMD_EEP_READ_ACK || packet->ucCmd == CMD_RAM_READ_ACK)
	{
		pStat = (DrsStatData *)&packet->unData.ucData[packet->unData.stRWData.ucLen];
	}
	else
	{
		pStat = &packet->unData.stStatData;
	}

	return pStat;
}

API int CALLING_CONVENTION get_eep_register_size(unsigned char eep_reg)
{
	return EEPRegSize(eep_reg);
}

API int CALLING_CONVENTION get_ram_register_size(unsigned char ram_reg)
{
	return RAMRegSize(ram_reg);
}

int CALLING_CONVENTION set_eep_write_cmd(void * buffer, unsigned char sid, unsigned char address, void * value)
{
	DrsRWData* data = 0;
	unsigned char size = EEPRegSize(address);

	if (address > EEP_LAST)
		return -1;
	if (buffer == 0)
		return set_packet(buffer, sid, CMD_EEP_WRITE, (int)(sizeof(DrsRWData) + size));

	data = &(get_packet_data(buffer)->stRWData);
	data->ucAddress = address;
	data->ucLen = size;
	memcpy(data->ucData, value, size);

	return set_packet(buffer, sid, CMD_EEP_WRITE, (int)(sizeof(DrsRWData) + size));
}

int CALLING_CONVENTION set_eep_map_write_cmd(void* buffer, unsigned char sid, EEPRegisterMap map, unsigned char address, unsigned char count)
{
	DrsRWData* data = 0;
	unsigned char size = 0;
	unsigned char regSize = 0;
	for (unsigned char i = address; i <= EEP_LAST && count > 0; i++)
	{
		regSize = EEPRegSize(i);
		size += regSize;
		if (regSize > 0) 
			count--;
	}

	if (address > EEP_LAST) 
		return -1;
	if (buffer == 0) 
		return set_packet(buffer, sid, CMD_EEP_WRITE, (int)(sizeof(DrsRWData) + size));

	data = &(get_packet_data(buffer)->stRWData);
	data->ucAddress = address;
	data->ucLen = size;
	memcpy(data->ucData, (char*)&map + address, size);

	printf("map.ModelNo : %d, %d\n", map.ucModelNo1, map.ucModelNo2);
	printf("map.ID : %d, address %d\n", map.ucID, address);
	printf("size : %d\n", size);
	for (int i = 0; i < size; i++)
	{
		printf("%02X ", data->ucData[i]);
	}

	printf("\n");

	return set_packet(buffer, sid, CMD_EEP_WRITE, (int)(sizeof(DrsRWData) + size));
}

int CALLING_CONVENTION set_eep_read_cmd(void * buffer, unsigned char sid, unsigned char address)
{
	if (buffer == 0)
		return set_packet(buffer, sid, CMD_EEP_READ, sizeof(DrsRWData));

	if (address > EEP_CALIBRATION_DIFFERENCE)
		return -1;

	unsigned char len = 0;
	for (unsigned char i = address; i <= EEP_CALIBRATION_DIFFERENCE; i++)
	{
		len += EEPRegSize(i);
	}

	//unsigned char size = EEPRegSize(address);
	DrsRWData* data = &(get_packet_data(buffer)->stRWData);
	data->ucAddress = address;
	data->ucLen = len;

	return set_packet(buffer, sid, CMD_EEP_READ, sizeof(DrsRWData));
}

int CALLING_CONVENTION set_eep_map_read_cmd(void* buffer, unsigned char sid, unsigned char address, unsigned char count)
{
	DrsRWData* data = 0;
	unsigned char size = 0;
	unsigned char regSize = 0;
	for (unsigned char i = address; i <= EEP_LAST && count > 0; i++)
	{
		regSize = EEPRegSize(i);
		size += regSize;
		if (regSize > 0) count--;
	}

	if (address > EEP_LAST)
		return -1;
	if (buffer == 0) 
		return set_packet(buffer, sid, CMD_EEP_READ, sizeof(DrsRWData));


	data = &(get_packet_data(buffer)->stRWData);
	data->ucAddress = address;
	data->ucLen = size;

	//printf("count %d, size : %d\n", count, size);
	return set_packet(buffer, sid, CMD_EEP_READ, sizeof(DrsRWData));
}

int CALLING_CONVENTION set_ram_write_cmd(void * buffer, unsigned char sid, unsigned char address, void * value)
{
	DrsRWData* data = 0;
	unsigned char size = RAMRegSize(address);

	if (address > RAM_DESIRED_VELOCITY) 
		return -1;
	if (buffer == 0) 
		return set_packet(buffer, sid, CMD_RAM_WRITE, (int)(sizeof(DrsRWData) + size));

	data = &(get_packet_data(buffer)->stRWData);
	data->ucAddress = address;
	data->ucLen = size;
	memcpy(data->ucData, value, size);

	return set_packet(buffer, sid, CMD_RAM_WRITE, (int)(sizeof(DrsRWData) + size));
}

int CALLING_CONVENTION set_ram_map_write_cmd(void* buffer, unsigned char sid, RAMRegisterMap map, unsigned char address, unsigned char count)
{
	DrsRWData* data = 0;
	unsigned char size = 0;
	unsigned char regSize = 0;
	for (unsigned char i = address; i <= RAM_LAST && count > 0; i++)
	{
		regSize = RAMRegSize(i);
		size += regSize;
		if (regSize > 0) 
			count--;
	}

	if (address > RAM_DESIRED_VELOCITY) 
		return -1;
	if (buffer == 0) 
		return set_packet(buffer, sid, CMD_RAM_WRITE, (int)(sizeof(DrsRWData) + size));

	data = &(get_packet_data(buffer)->stRWData);
	data->ucAddress = address;
	data->ucLen = size;
	memcpy(data->ucData, (char*)&map + address, size);

	return set_packet(buffer, sid, CMD_RAM_WRITE, (int)(sizeof(DrsRWData) + size));
}

int CALLING_CONVENTION set_ram_read_cmd(void * buffer, unsigned char sid, unsigned char address)
{
	unsigned char size = RAMRegSize(address);
	DrsRWData* data = 0;

	if (address > RAM_LAST)
		return -1;
	if (buffer == 0) 
		return set_packet(buffer, sid, CMD_RAM_READ, sizeof(DrsRWData));

	data = &(get_packet_data(buffer)->stRWData);
	data->ucAddress = address;
	data->ucLen = size;

	return set_packet(buffer, sid, CMD_RAM_READ, sizeof(DrsRWData));
}

int CALLING_CONVENTION set_ram_map_read_cmd(void* buffer, unsigned char sid, unsigned char address, unsigned char count)
{
	DrsRWData* data = 0;
	unsigned char size = 0;
	unsigned char regSize = 0;
	for (unsigned char i = address; i <= RAM_LAST && count > 0; i++)
	{
		regSize = RAMRegSize(i);
		size += regSize;
		if (regSize > 0) count--;
	}

	if (address > RAM_LAST) 
		return -1;
	if (buffer == 0)
		return set_packet(buffer, sid, CMD_RAM_READ, sizeof(DrsRWData));

	data = &(get_packet_data(buffer)->stRWData);
	data->ucAddress = address;
	data->ucLen = size;

	return set_packet(buffer, sid, CMD_RAM_READ, sizeof(DrsRWData));
}


int CALLING_CONVENTION set_i_jog_cmd(void * buffer, unsigned char sid, IJog* jogs, int count)
{
	DrsIJog* ijog = 0;
	if (buffer == 0) 
		return set_packet(buffer, sid, CMD_I_JOG, (int)sizeof(DrsIJog) * count);

	ijog = get_packet_data(buffer)->stIJog;
	for (int i = 0; i < count; i++)
	{
		if (jogs[i].InfiniteTurn)
		{
			ijog[i].stJog.Infinite.uiValue = abs(jogs[i].Value);
			ijog[i].stJog.Infinite.Direction = (jogs[i].Value < 0 ? 1 : 0);
			ijog[i].stJog.Infinite.reserved = 0;
		}
		else 
		{
			//ijog[i].stJog.Position.uiValue = abs(jogs[i].Value);
			ijog[i].stJog.Position.iValue = jogs[i].Value;
			//ijog[i].stJog.Position.reserved = 0;
		}

		ijog[i].stSet.ucStopFlag = jogs[i].Stop;
		ijog[i].stSet.ucMode = jogs[i].InfiniteTurn;
		ijog[i].stSet.ucLedGreen = ((jogs[i].LED & LED_GREEN) == LED_GREEN);
		ijog[i].stSet.ucLedBlue = ((jogs[i].LED & LED_BLUE) == LED_BLUE);
		ijog[i].stSet.ucLedRed = ((jogs[i].LED & LED_RED) == LED_RED);
		ijog[i].stSet.ucJogInvalid = jogs[i].NoAction;
		ijog[i].stSet.ucProfile = jogs[i].Profile;

		ijog[i].ucId = jogs[i].ID;
		ijog[i].ucPlayTime = jogs[i].PlayTime_ms;
	}

	return set_packet(buffer, sid, CMD_I_JOG, (int)sizeof(DrsIJog) * count);
}

int CALLING_CONVENTION set_mi_jog_cmd(void* buffer, unsigned char sid, MIJog* jogs, int count, int turn, bool bMulti)
{
	DrsMIJog* mijog = 0;
	if (buffer == 0)
		return set_packet(buffer, sid, CMD_MI_JOG, (int)sizeof(DrsMIJog) * count);

	mijog = get_packet_data(buffer)->stMIJog;
	for (int i = 0; i < count; i++)
	{
		if (jogs[i].InfiniteTurn)
		{
			mijog[i].stJog.Infinite.uiValue = abs(jogs[i].Value);
			mijog[i].stJog.Infinite.Direction = (jogs[i].Value < 0 ? 1 : 0);
			//Add//
			mijog[i].stJog2.Turn.uiValue = turn; //Turn count//

			if (bMulti)
			{
				mijog[i].stSet.reserved = 1;
			}
			else
			{
				mijog[i].stSet.reserved = 0;
			}
		}
		else 
		{
			//mijog[i].stJog.Position.uiValue = abs(jogs[i].Value);
			mijog[i].stJog.Position.iValue = (jogs[i].Value);
			//Add//
			mijog[i].stJog2.Turn.uiValue = turn; //Turn count//

			if (bMulti)
			{
				mijog[i].stSet.reserved = 1;
			}
			else
			{
				mijog[i].stSet.reserved = 0;
			}
		}

		mijog[i].stSet.ucStopFlag = jogs[i].Stop;
		mijog[i].stSet.ucMode = jogs[i].InfiniteTurn;
		mijog[i].stSet.ucLedGreen = ((jogs[i].LED & LED_GREEN) == LED_GREEN);
		mijog[i].stSet.ucLedBlue = ((jogs[i].LED & LED_BLUE) == LED_BLUE);
		mijog[i].stSet.ucLedRed = ((jogs[i].LED & LED_RED) == LED_RED);
		mijog[i].stSet.ucJogInvalid = jogs[i].NoAction;
		mijog[i].stSet.ucProfile = jogs[i].Profile;

		mijog[i].ucId = jogs[i].ID;
		mijog[i].ucPlayTime = jogs[i].PlayTime_ms;
	}

	return set_packet(buffer, sid, CMD_MI_JOG, (int)sizeof(DrsMIJog) * count);
}

int CALLING_CONVENTION set_s_jog_cmd(void* buffer, unsigned char sid, unsigned char time_ms, SJog* jogs, int count)
{
	DrsSJogData* data = 0;
	DrsSJog* sjog = 0;

	if (buffer == 0) 
		return set_packet(buffer, sid, CMD_S_JOG, (int)sizeof(DrsSJogData) + (int)sizeof(DrsSJog) * count);

	data = &(get_packet_data(buffer)->stSJogData);
	sjog = data->stSJog;
	for (int i = 0; i < count; i++)
	{
		if (jogs[i].InfiniteTurn)
		{
			sjog[i].stJog.Infinite.uiValue = abs(jogs[i].Value);
			sjog[i].stJog.Infinite.Direction = (jogs[i].Value < 0 ? 1 : 0);
			sjog[i].stJog.Infinite.reserved = 0;
		}
		else 
		{
			//sjog[i].stJog.Position.uiValue = abs(jogs[i].Value);
			sjog[i].stJog.Position.iValue = (jogs[i].Value);
			//sjog[i].stJog.Position.reserved = 0;
		}

		sjog[i].stSet.ucStopFlag = jogs[i].Stop;
		sjog[i].stSet.ucMode = jogs[i].InfiniteTurn;
		sjog[i].stSet.ucLedGreen = ((jogs[i].LED & LED_GREEN) == LED_GREEN);
		sjog[i].stSet.ucLedBlue = ((jogs[i].LED & LED_BLUE) == LED_BLUE);
		sjog[i].stSet.ucLedRed = ((jogs[i].LED & LED_RED) == LED_RED);
		sjog[i].stSet.ucJogInvalid = jogs[i].NoAction;
		sjog[i].stSet.ucProfile = jogs[i].Profile;

		sjog[i].ucId = jogs[i].ID;
	}
	data->ucPlayTime = time_ms;
	return set_packet(buffer, sid, CMD_S_JOG, (int)(sizeof(DrsSJogData) + sizeof(DrsSJog) * (unsigned int)count));
}

int CALLING_CONVENTION set_ms_jog_cmd(void* buffer, unsigned char sid, unsigned char time_ms, MSJog* jogs, int count, int turn, bool bMulti)
{
	DrsMSJogData* data = 0;
	DrsMSJog* msjog = 0;

	if (buffer == 0)
		return set_packet(buffer, sid, CMD_MS_JOG, (int)sizeof(DrsMSJogData) + (int)sizeof(DrsMSJog) * count); 

	data = &(get_packet_data(buffer)->stMSJogData);
	msjog = data->stMSJog;
	for (int i = 0; i < count; i++)
	{
		if (jogs[i].InfiniteTurn)
		{
			msjog[i].stJog.Infinite.uiValue = abs(jogs[i].Value);
			msjog[i].stJog.Infinite.Direction = (jogs[i].Value < 0 ? 1 : 0);
			//Add//
			msjog[i].stJog2.Turn.uiValue = turn; //Turn count//

			if (bMulti)
			{
				msjog[i].stSet.reserved = 1;
			}
			else
			{
				msjog[i].stSet.reserved = 0;
			}
		}
		else 
		{
			//msjog[i].stJog.Position.uiValue = abs(jogs[i].Value);
			msjog[i].stJog.Position.iValue = (jogs[i].Value);
			//Add//
			msjog[i].stJog2.Turn.uiValue = turn; //Turn count//

			if (bMulti)
			{
				msjog[i].stSet.reserved = 1;
			}
			else
			{
				msjog[i].stSet.reserved = 0;
			}
		}

		msjog[i].stSet.ucStopFlag = jogs[i].Stop;
		msjog[i].stSet.ucMode = jogs[i].InfiniteTurn;
		msjog[i].stSet.ucLedGreen = ((jogs[i].LED & LED_GREEN) == LED_GREEN);
		msjog[i].stSet.ucLedBlue = ((jogs[i].LED & LED_BLUE) == LED_BLUE);
		msjog[i].stSet.ucLedRed = ((jogs[i].LED & LED_RED) == LED_RED);
		msjog[i].stSet.ucJogInvalid = jogs[i].NoAction;
		msjog[i].stSet.ucProfile = jogs[i].Profile;

		msjog[i].ucId = jogs[i].ID;
	}
	data->ucPlayTime = time_ms;
	return set_packet(buffer, sid, CMD_MS_JOG, (int)(sizeof(DrsMSJogData) + sizeof(DrsMSJog) * (unsigned int)count));
}


int CALLING_CONVENTION set_stat_cmd(void * buffer, unsigned char sid)
{
	DrsData* data = 0;
	if (buffer == 0) 
		return set_packet(buffer, sid, CMD_STAT, 0);

	data = get_packet_data(buffer);
	data->stStatData.ucError = 0;
	data->stStatData.ucDetail = 0;
	return set_packet(buffer, sid, CMD_STAT, 0);
}

int CALLING_CONVENTION set_rollback_cmd(void * buffer, unsigned char sid, unsigned char id_skip, unsigned char baud_skip)
{
	DrsData* data = 0;
	if (buffer == 0) 
		return set_packet(buffer, sid, CMD_ROLLBACK, sizeof(DrsRollbackData));

	data = get_packet_data(buffer);
	data->stRollbackData.ucIdSkip = id_skip;
	data->stRollbackData.ucBaudSkip = baud_skip;
	return set_packet(buffer, sid, CMD_ROLLBACK, sizeof(DrsRollbackData));
}

int CALLING_CONVENTION set_reboot_cmd(void * buffer, unsigned char sid)
{
	return set_packet(buffer, sid, CMD_REBOOT, 0);
}

int CALLING_CONVENTION set_calset_cmd(void* buffer, unsigned char sid)
{
	return set_packet(buffer, sid, CMD_CALSET, 0);
}

eep_write_ack * _eep_write_ack_callback = 0;
eep_map_write_ack* _eep_map_write_ack_callback = 0;
eep_read_ack * _eep_read_ack_callback = 0;
eep_map_read_ack* _eep_map_read_ack_callback = 0;

ram_write_ack * _ram_write_ack_callback = 0;
ram_write_ack * _ram_map_write_ack_callback = 0;
ram_read_ack * _ram_read_ack_callback = 0;
ram_map_read_ack* _ram_map_read_ack_callback = 0;

i_jog_ack * _i_jog_ack_callback = 0;
s_jog_ack * _s_jog_ack_callback = 0;
mi_jog_ack* _mi_jog_ack_callback = 0;
ms_jog_ack* _ms_jog_ack_callback = 0;
stat_ack * _stat_ack_callback = 0;
rollback_ack * _rollback_ack_callback = 0;
reboot_ack * _reboot_ack_callback = 0;


void CALLING_CONVENTION regist_ack_callback_eep_write(eep_write_ack *callback)
{
	_eep_write_ack_callback = callback;
}

void CALLING_CONVENTION regist_ack_callback_eep_map_write(eep_map_write_ack* callback)
{
	_eep_map_write_ack_callback = callback;
}

void CALLING_CONVENTION regist_ack_callback_eep_read(eep_read_ack *callback)
{
	_eep_read_ack_callback = callback;
}

void CALLING_CONVENTION regist_ack_callback_eep_map_read(eep_map_read_ack* callback)
{
	_eep_map_read_ack_callback = callback;
}

void CALLING_CONVENTION regist_ack_callback_ram_write(ram_write_ack *callback)
{
	_ram_write_ack_callback = callback;
}

void CALLING_CONVENTION regist_ack_callback_ram_map_write(ram_map_write_ack* callback)
{
	_ram_map_write_ack_callback = callback;
}

void CALLING_CONVENTION regist_ack_callback_ram_read(ram_read_ack *callback)
{
	_ram_read_ack_callback = callback;
}

void CALLING_CONVENTION regist_ack_callback_ram_map_read(ram_map_read_ack * callback)
{
	_ram_map_read_ack_callback = callback;
}

void CALLING_CONVENTION regist_ack_callback_i_jog(i_jog_ack *callback)
{
	_i_jog_ack_callback = callback;
}

void CALLING_CONVENTION regist_ack_callback_s_jog(s_jog_ack *callback)
{
	_s_jog_ack_callback = callback;
}

void CALLING_CONVENTION regist_ack_callback_mi_jog(mi_jog_ack* callback)
{
	_mi_jog_ack_callback = callback;
}

void CALLING_CONVENTION regist_ack_callback_ms_jog(ms_jog_ack* callback)
{
	_ms_jog_ack_callback = callback;
}

void CALLING_CONVENTION regist_ack_callback_stat(stat_ack *callback)
{
	_stat_ack_callback = callback;
}

void CALLING_CONVENTION regist_ack_callback_rollback(rollback_ack *callback)
{
	_rollback_ack_callback = callback;
}

void CALLING_CONVENTION regist_ack_callback_reboot(reboot_ack *callback)
{
	_reboot_ack_callback = callback;
}

RAMRegisterMap _ramMap;
EEPRegisterMap _eepMap;


void proc_eep_read_ack(DrsPacket* packet)
{
	EEPRegisterMap _eepMap;

	if (_eep_read_ack_callback != 0)
		(*_eep_read_ack_callback)(
			packet->ucChipID,
			packet->unData.stRWData.ucAddress,
			packet->unData.stRWData.ucLen,
			packet->unData.stRWData.ucData,
			get_ack_status(packet)->ucError,
			get_ack_status(packet)->ucDetail
			);

	if (_eep_map_read_ack_callback != 0)
	{
		memcpy((void*)((char*)& _eepMap + packet->unData.stRWData.ucAddress), packet->unData.stRWData.ucData, packet->unData.stRWData.ucLen);
		(*_eep_map_read_ack_callback)(
			packet->ucChipID,
			packet->unData.stRWData.ucAddress,
			packet->unData.stRWData.ucLen,
			_eepMap,
			get_ack_status(packet)->ucError,
			get_ack_status(packet)->ucDetail
			);

	}
}

void proc_ram_read_ack(DrsPacket * packet)
{
	RAMRegisterMap _ramMap;

	if (_ram_read_ack_callback != 0)
		(*_ram_read_ack_callback)(
			packet->ucChipID,
			packet->unData.stRWData.ucAddress,
			packet->unData.stRWData.ucLen,
			packet->unData.stRWData.ucData,
			get_ack_status(packet)->ucError,
			get_ack_status(packet)->ucDetail
			);
	if (_ram_map_read_ack_callback != 0)
	{
		memcpy((void*)((char*)& _ramMap + packet->unData.stRWData.ucAddress), packet->unData.stRWData.ucData, packet->unData.stRWData.ucLen);
		(*_ram_map_read_ack_callback)(
			packet->ucChipID,
			packet->unData.stRWData.ucAddress,
			packet->unData.stRWData.ucLen,
			_ramMap,
			get_ack_status(packet)->ucError,
			get_ack_status(packet)->ucDetail
			);
	}
}


int CALLING_CONVENTION parse(void * buffer, int length, int * pos)
{
	DrsPacket* packet = get_ack_packet(buffer, length, pos);
	if (packet == 0) 
		return 0;


	switch (packet->ucCmd)
	{
	case CMD_EEP_WRITE_ACK:
		if (_eep_write_ack_callback != 0)
			(*_eep_write_ack_callback)(
				packet->ucChipID,
				get_ack_status(packet)->ucError,
				get_ack_status(packet)->ucDetail
				);
		break;
	case CMD_EEP_READ_ACK:
		proc_eep_read_ack(packet);
		break;
	case CMD_RAM_WRITE_ACK:
		if (_ram_write_ack_callback != 0)
			(*_ram_write_ack_callback)(
				packet->ucChipID,
				get_ack_status(packet)->ucError,
				get_ack_status(packet)->ucDetail
				);
		break;
	case CMD_RAM_READ_ACK:
		proc_ram_read_ack(packet);
		break;
	case CMD_I_JOG_ACK:
		if (_i_jog_ack_callback != 0)
			(*_i_jog_ack_callback)(
				packet->ucChipID,
				get_ack_status(packet)->ucError,
				get_ack_status(packet)->ucDetail
				);
		break;
	case CMD_S_JOG_ACK:
		if (_s_jog_ack_callback != 0)
			(*_s_jog_ack_callback)(
				packet->ucChipID,
				get_ack_status(packet)->ucError,
				get_ack_status(packet)->ucDetail
				);
		break;
	case CMD_MI_JOG_ACK:
		if (_mi_jog_ack_callback != 0)
			(*_mi_jog_ack_callback)(
				packet->ucChipID,
				get_ack_status(packet)->ucError,
				get_ack_status(packet)->ucDetail
				);
		break;
	case CMD_MS_JOG_ACK:
		if (_ms_jog_ack_callback != 0)
			(*_ms_jog_ack_callback)(
				packet->ucChipID,
				get_ack_status(packet)->ucError,
				get_ack_status(packet)->ucDetail
				);
		break;
	case CMD_STAT_ACK:
		if (_stat_ack_callback != 0)
			(*_stat_ack_callback)(
				packet->ucChipID,
				get_ack_status(packet)->ucError,
				get_ack_status(packet)->ucDetail
				);
		break;
	case CMD_ROLLBACK_ACK:
		if (_rollback_ack_callback != 0)
			(*_rollback_ack_callback)(
				packet->ucChipID,
				get_ack_status(packet)->ucError,
				get_ack_status(packet)->ucDetail
				);
		break;
	case CMD_REBOOT_ACK:
		if (_reboot_ack_callback != 0)
			(*_reboot_ack_callback)(
				packet->ucChipID,
				get_ack_status(packet)->ucError,
				get_ack_status(packet)->ucDetail
				);
		break;
	default:
		return 0;
	}

	return 1;
}