
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// Herkulex.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

int ex_DRS_Model_Num = 0; //기본은 DSR-0101

double ex_dMaxPosition = 1024.0;

BOOL	ex_bFlag_EEPWriteAckCallback = false;
BOOL	ex_bFlag_EEPReadAckCallback = false;
BOOL	ex_bFlag_RAMWriteAckCallback = false;
BOOL	ex_bFlag_RAMReadAckCallback = false;
BOOL	ex_bFlag_ViewModaless = false;
BOOL	ex_bFlag_Connect = false;
BOOL	ex_bFlag_WriteView = false;
BOOL	ex_bFlag_ReadView = false;

CString ex_strVersion1 = _T("0");
CString ex_strVersion2 = _T("0");

BOOL	ex_bCheckEEPRead_ACK = false;

BOOL	ex_bFlagMainUI = true;

BOOL	ex_bFlagSCAN = true;

BOOL ex_bFlagModal_Map = false;
BOOL ex_bFlagModal_View = false;
BOOL ex_bFlagModal_Test = false;
BOOL ex_bFlagModal_MultiMove = false;
BOOL ex_bFlagModal_Parameter = false;
BOOL	ex_bFlagModal_Update = false;

BOOL ex_bFlagYmodem_Mode = false;
CString ex_strYmodemMsg = _T("");

BOOL		ex_bFlag_Status = false;

BOOL		ex_bFlag_ServoON = false;