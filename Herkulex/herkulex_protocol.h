#ifndef HERKULEX_PROTOCOL_H_
#define HERKULEX_PROTOCOL_H_

//////////////////////////////프로토콜에 대한 선언//////////////////////////////
//각 항목의 인덱스
#define PROTOCOL_SIZE_IDX					2
#define PROTOCOL_ID_IDX						3
#define PROTOCOL_CMD_IDX				4
#define PROTOCOL_CS1_IDX					5
#define PROTOCOL_CS2_IDX					6
#define PROTOCOL_DATA_IDX				7

//헤더 관련
#define HEADER										0xFFFF

//SIZE 관련
#define MIN_PACKET_SIZE						7
#define MIN_ACK_PACKET_SIZE				9
#define MAX_PACKET_SIZE						223
#define MAX_DATA_SIZE							(MAX_PACKET_SIZE-MIN_PACKET_SIZE)

//ID 관련
#define MAX_ID											0xFD    
#define BROADCAST_ID							0xFE  

//CMD 관련 - Request Packet
#define CMD_EEP_WRITE						0x01
#define CMD_EEP_READ							0x02
#define CMD_RAM_WRITE						0x03
#define CMD_RAM_READ							0x04    
#define CMD_RW_DATA_ADDR_IDX		7
#define CMD_RW_DATA_LEN_IDX			8
#define CMD_I_JOG									0x05
#define CMD_I_JOG_STRUCT_SIZE		5
#define CMD_I_JOG_MAX_DRS				(MAX_DATA_SIZE/CMD_I_JOG_STRUCT_SIZE)
#define CMD_MI_JOG								0x0A
#define CMD_MI_JOG_STRUCT_SIZE		5
#define CMD_MI_JOG_MAX_DRS				(MAX_DATA_SIZE/CMD_MI_JOG_STRUCT_SIZE)
#define CMD_S_JOG									0x06
#define CMD_S_JOG_STRUCT_SIZE		4
#define CMD_S_JOG_MAX_DRS				(MAX_DATA_SIZE/CMD_S_JOG_STRUCT_SIZE)
#define CMD_MS_JOG								0x0B
#define CMD_MS_JOG_STRUCT_SIZE	4
#define CMD_MS_JOG_MAX_DRS			(MAX_DATA_SIZE/CMD_MS_JOG_STRUCT_SIZE)

//Add _원점셋팅 명령추가//
#define CMD_CALSET								0x0C

#define CMD_STAT										0x07    
#define CMD_ROLLBACK							0x08
#define CMD_REBOOT								0x09

#define CMD_MIN										(CMD_EEP_WRITE)
#define CMD_MAX										(CMD_REBOOT)

//CMD 관련 - ACK Packet
#define CMD_ACK_MASK							0x40

#define CMD_EEP_WRITE_ACK				(CMD_EEP_WRITE|CMD_ACK_MASK)
#define CMD_EEP_READ_ACK				(CMD_EEP_READ|CMD_ACK_MASK)
#define CMD_RAM_WRITE_ACK				(CMD_RAM_WRITE|CMD_ACK_MASK)
#define CMD_RAM_READ_ACK				(CMD_RAM_READ|CMD_ACK_MASK)
#define CMD_I_JOG_ACK							(CMD_I_JOG|CMD_ACK_MASK)
#define CMD_S_JOG_ACK						(CMD_S_JOG|CMD_ACK_MASK)
#define CMD_MI_JOG_ACK						(CMD_MI_JOG|CMD_ACK_MASK)
#define CMD_MS_JOG_ACK						(CMD_MS_JOG|CMD_ACK_MASK)
#define CMD_STAT_ACK							(CMD_STAT|CMD_ACK_MASK)
#define CMD_ROLLBACK_ACK				(CMD_ROLLBACK|CMD_ACK_MASK)
#define CMD_REBOOT_ACK					(CMD_REBOOT|CMD_ACK_MASK)

#define CMD_ACK_MIN								(CMD_EEP_WRITE_ACK)
#define CMD_ACK_MAX								(CMD_REBOOT_ACK)

//CheckSum 관련
#define CHKSUM_MASK							0xFE

#pragma pack(push,1)
//////////////////////////////프로토콜 구조체//////////////////////////////
typedef struct DrsJogPosition
{
	short	iValue : 16;
	//unsigned short	uiValue : 15;
	//unsigned short	reserved : 1;
}DrsJogPosition;

typedef struct DrsJogInfinite
{
	unsigned short	uiValue : 14;
	unsigned short	Direction : 1;
	unsigned short	reserved : 1;
}DrsJogInfinite;

typedef union DrsJog
{
	DrsJogPosition Position;
	DrsJogInfinite Infinite;
}DrsJog;

//Add///////////////////////////////////////////////////////
typedef struct DrsTurnPosition
{
	//unsigned short	uiValue;
	unsigned char	uiValue;
}DrsTurnPosition;

typedef union DrsMJog
{
	DrsJogPosition Position;
	DrsJogInfinite Infinite;
	//DrsTurnPosition Turn;
}DrsMJog;

typedef union DrsMJog2
{
	DrsTurnPosition Turn;
}DrsMJog2;
///////////////////////////////////////////////////////////////

typedef struct DrsSet
{
	unsigned char	ucStopFlag : 1;
	unsigned char	ucMode : 1;
	unsigned char	ucLedGreen : 1;
	unsigned char	ucLedBlue : 1;
	unsigned char	ucLedRed : 1;
	unsigned char	ucJogInvalid : 1;
	//unsigned char	reserved : 2;
	unsigned char	reserved : 1;
	unsigned char	ucProfile : 1;	// 0 : Trapezoidal, 1 : S-Curved
}DrsSet;

typedef struct DrsIJog 
{
	DrsJog				stJog;
	DrsSet				stSet;
	unsigned char	ucId;
	unsigned char	ucPlayTime;
}DrsIJog;

typedef struct DrsSJog 
{
	DrsJog				stJog;
	DrsSet				stSet;
	unsigned char	ucId;
}DrsSJog;

typedef struct DrsMIJog
{
	DrsMJog			stJog;
	DrsMJog2	    stJog2;
	DrsSet				stSet;
	unsigned char	ucId;
	unsigned char	ucPlayTime;
}DrsMIJog;

typedef struct DrsMSJog
{
	DrsMJog			stJog;
	DrsMJog2	    stJog2;
	DrsSet				stSet;
	unsigned char	ucId;
}DrsMSJog;

typedef struct DrsSJogData
{
	unsigned char	ucPlayTime;
	DrsSJog			stSJog[];
}DrsSJogData;

typedef struct DrsMSJogData
{
	unsigned char	ucPlayTime;
	DrsMSJog			stMSJog[];
}DrsMSJogData;

typedef struct DrsRWData
{
	unsigned char	ucAddress;
	unsigned char	ucLen;        
	unsigned char	ucData[];
}DrsRWData;

typedef struct DrsStatData
{
	unsigned char ucError;
	unsigned char ucDetail;
}DrsStatData;


typedef struct DrsRollbackData
{
	unsigned char ucIdSkip;
	unsigned char ucBaudSkip;
}DrsRollbackData;

typedef union DrsData
{
	unsigned char	ucData[MAX_PACKET_SIZE-MIN_PACKET_SIZE];

	DrsRWData			stRWData;
	DrsIJog					stIJog[CMD_I_JOG_MAX_DRS];
	DrsSJogData			stSJogData;
	DrsMIJog					stMIJog[CMD_MI_JOG_MAX_DRS];
	DrsMSJogData		stMSJogData;
	
	DrsStatData			stStatData;
	DrsRollbackData		stRollbackData;
}DrsData;

typedef struct
{
	unsigned short		ucHeader;
	unsigned char			ucPacketSize;
	unsigned char			ucChipID;
	unsigned char			ucCmd;
	unsigned char			ucCheckSum1;
	unsigned char			ucCheckSum2;
	DrsData					unData;
}DrsPacket;

//////////////////////////////수신 상태 결과 값//////////////////////////////
enum{
	DRS_RXWAITING,
	DRS_RXCOMPLETE,
	DRS_HEADERNOTFOUND,
	DRS_INVALIDSIZE,
	DRS_UNKNOWNCMD,
	DRS_INVALIDID,
	DRS_CHKSUMERROR,
	DRS_RXTIMEOUT
}DrsRxStatus;

#pragma pack(pop)

#endif /* HERKULEX_PROTOCOL_H_ */