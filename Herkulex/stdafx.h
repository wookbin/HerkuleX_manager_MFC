
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원


// 폰트
#define FONT_TITLE			"휴먼둥근헤드라인"
#define FONT_BUTTON			"HY헤드라인M"
#define FONT_STATUS		    "Franklin Gothic Medium"

// Color Reference
const COLORREF WHITE = RGB(255, 255, 255);
const COLORREF BLACK = RGB(1, 1, 1);
const COLORREF WGRAY = RGB(200, 200, 200);
const COLORREF GRAY = RGB(150, 150, 150);
const COLORREF YELLOW = RGB(255, 255, 72);
const COLORREF RED = RGB(255, 90, 90);
const COLORREF RED2 = RGB(255, 210, 210);
const COLORREF GREEN = RGB(1, 255, 1);
const COLORREF GREEN1 = RGB(0, 255, 0);
const COLORREF GREEN2 = RGB(29, 219, 22);
const COLORREF BLUE = RGB(37, 36, 255);
const COLORREF BKCOLOR = RGB(75, 75, 75);


// DSR Model define
#define _MODEL_DRS_0101		0
#define _MODEL_DRS_0102		1
#define _MODEL_DRS_0201		2
#define _MODEL_DRS_0301		3
#define _MODEL_DRS_0302		4
#define _MODEL_DRS_0303		5
#define _MODEL_DRS_0401		6
#define _MODEL_DRS_0402		7
#define _MODEL_DRS_0601		8
#define _MODEL_DRS_0602		9

extern int ex_DRS_Model_Num;

extern double ex_dMaxPosition;

//Callback Flag//
extern BOOL	ex_bFlag_EEPWriteAckCallback;
extern BOOL	ex_bFlag_EEPReadAckCallback;
extern BOOL	ex_bFlag_RAMWriteAckCallback;
extern BOOL	ex_bFlag_RAMReadAckCallback;
extern BOOL	ex_bFlag_ViewModaless;
extern BOOL ex_bFlag_Connect;
extern BOOL	ex_bFlag_WriteView;
extern BOOL	ex_bFlag_ReadView;

extern CString		ex_strVersion1;
extern CString		ex_strVersion2;
extern BOOL		ex_bCheckEEPRead_ACK;
extern BOOL		ex_bFlagMainUI;
extern BOOL		ex_bFlagSCAN;
extern BOOL		ex_bFlagModal_Map;
extern BOOL		ex_bFlagModal_View;
extern BOOL		ex_bFlagModal_Test;
extern BOOL		ex_bFlagModal_MultiMove;
extern BOOL		ex_bFlagModal_Parameter;
extern BOOL		ex_bFlagModal_Update;

extern BOOL		ex_bFlagYmodem_Mode;
extern CString		ex_strYmodemMsg;
extern BOOL		ex_bFlag_Status;

extern BOOL		ex_bFlag_ServoON;


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


