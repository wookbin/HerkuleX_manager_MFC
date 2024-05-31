
// HerkulexDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Herkulex.h"
#include "HerkulexDlg.h"
#include "afxdialogex.h"
#include "Mmsystem.h"
#include <math.h>
#include "herkulexlib.h"

//#include "CRegisterMAP.h"
#include "CProgressDlg.h"
#include "CMultiMove.h"
#include "CFirmwareUpdate.h"

#include "UseRegistry.h" //레지스트리 읽기/쓰기 기능추가

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Serial Comm.
HWND	hCommWnd;
////////////////////////////////////////////////////////////////////
unsigned char szSendBuffer[1024] = { 0, };	// 전송 버퍼
int iSize = 0;
// 사용할 모터 id 번호. ex)01~ 253까지
unsigned char szIDs[] = { /*0x00, */0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
						  0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,
						  0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,
						  0x2e,0x2f,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,
						  0x3d,0x3e,0x3f,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,
						  0x4c,0x4d,0x4e,0x4f,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,
						  0x5b,0x5c,0x5d,0x5e,0x5f,0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,
						  0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,
						  0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,
						  0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,0x95,0x96,
						  0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,
						  0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
						  0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,0xc0,0xc1,0xc2,0xc3,
						  0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,
						  0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,0xe0,0xe1,
						  0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,0xf0,
						  0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe};

DWORD	nPacketLength = 0;
unsigned char ucValue = 0;
int		m_iRGB_SUM = 0;
BOOL	bmoveMode = false;
CString strPOS_Count, strPOS_Angle, strTorque;
CString strMIN_POS, strMAX_POS, strPWM, strDiff_Position, strStatusErorr, strStatusDetail, strVoltage, strTemperature, strTurn;
CString strErorr[8];
CString strDetail[8];
double	m_dClac_Velocity = 0;
BOOL	m_bCheck_AbsolutePoseFlag = false;
double m_dGraphData[2]; //Graph Display Data//

CString m_strErrorMargin = _T("");
CString m_strErrorPosition = _T("");

CString m_regedit_Model_Name = _T("");
int		m_regedit_Model_ID = 0;
int		m_regedit_TotalCnt = 0;

CString m_regedit_COM = _T("");
CString m_regedit_Baudrate = _T("");

int			m_iSelectList_ID = 0;
double m_dZooming = 1.0;
int			m_iZoomData = 0;

double dfResOfTherm = 0.0;
double m_dCalc_Temp = 0.0;

LVITEM lvi_list;
////////////////////////////////////////////////////////////////////

// 2019.04.09 by MIni
CHerkulexDlg * _dlgHerkulex = NULL;	

void EEPWriteAckCallback(unsigned char sid, unsigned char status_error, unsigned char status_detail)
{
	//TRACE("EEPWriteAckCallback...");
	ex_bFlag_EEPWriteAckCallback = true;
}

void EEPReadAckCallback(unsigned char sid, unsigned char address, unsigned char length, void* value, unsigned char status_error, unsigned char status_detail)
{
	//TRACE("EEPReadAckCallback...");

}

void RAMWriteAckCallback(unsigned char sid, unsigned char status_error, unsigned char status_detail)
{
	//TRACE("RAMWriteAckCallback...");
	ex_bFlag_RAMWriteAckCallback = true;
}


void RAMReadAckCallback(unsigned char sid, unsigned char address, unsigned char length, void* value, unsigned char status_error, unsigned char status_detail)
{
	//TRACE("RAMReadAckCallback...");
	ex_bFlag_RAMReadAckCallback = true;
	
}

void EEPMapReadAckCallback(unsigned char sid, unsigned char address, unsigned char length, EEPRegisterMap map, unsigned char status_error, unsigned char status_detail)
{
	CHerkulexDlg *pDlg = (CHerkulexDlg *)AfxGetMainWnd();

	switch (address)
	{
	case 0:
		//EEP Register MAP All Read
		memcpy(&(pDlg->EEP), &map, sizeof(EEPRegisterMap));

		ex_strVersion1.Format("%d", map.ucVersion1); //version정보 1
		ex_strVersion2.Format("%d", map.ucVersion2); //version정보 2

		ex_bCheckEEPRead_ACK = true;

		break;
	default:
		//pDlg->writeMessageBox("[Error]없는 주소입니다..", RED);
		break;

	}

	ex_bFlag_EEPReadAckCallback = true;

}

void RAMMapReadAckCallback(unsigned char sid, unsigned char address, unsigned char length, RAMRegisterMap map, unsigned char status_error, unsigned char status_detail)
{
	CHerkulexDlg *pDlg = (CHerkulexDlg *)AfxGetMainWnd();
	CString strID;

	switch (address)
	{
		case 0:
			//RAM Register MAP All Read
			memcpy(&(pDlg->RAM[pDlg->m_imotor_ID]), &map, sizeof(RAMRegisterMap));

			//StatusError
			strStatusErorr.Format("%d", map.ucStatusError);
			for (int j = 7; j >= 0; j--)
			{
				strErorr[j].Format("%d", (map.ucStatusError >> j) & 1);
				//TRACE("strErorr[%d] = %s", j, strErorr[j]);
			}
			
			//Status Detail//
			strStatusDetail.Format("%d", map.ucStatusDetail);
			for (int i = 7; i >= 0; i--)
			{
				strDetail[i].Format("%d",(map.ucStatusDetail >> i) & 1);
				//TRACE("strDetail[%d] = %s", i, strDetail[i]);
			}
			

			//Input Voltage 
			if (ex_DRS_Model_Num == 0 || ex_DRS_Model_Num == 1 || ex_DRS_Model_Num == 2)
			{
				strVoltage.Format("%.2f", (map.ucVoltage * 0.074)); //Voltage로 환산//
				pDlg->GetDlgItem(IDC_VOLTAGE)->SetWindowText(strVoltage);
			}
			else
			{
				//03, 04, 06시리즈의 경우....
				strVoltage.Format("%.2f", (map.ucVoltage * 0.1)); //Voltage로 환산//
				pDlg->GetDlgItem(IDC_VOLTAGE)->SetWindowText(strVoltage);
			}
			
			//Temperature
			switch (ex_DRS_Model_Num)
			{
			case 0:
				dfResOfTherm = map.ucTemperature * 5.0 / REG_ADCINFO_MAX;
				dfResOfTherm = 10000.0 * (5.0 - dfResOfTherm) / dfResOfTherm;
				m_dCalc_Temp = pDlg->dfCalcTempCenigrade(dfResOfTherm, REG_ADC_THEMISTOR_B, REG_ADC_THEMISTOR_R0, REG_ADC_THEMISTOR_T0);
				strTemperature.Format(_T("%.2f"), m_dCalc_Temp);
				break;
			case 1:
				dfResOfTherm = map.ucTemperature * 5.0 / REG_ADCINFO_MAX;
				dfResOfTherm = 10000.0 * (5.0 - dfResOfTherm) / dfResOfTherm;
				m_dCalc_Temp = pDlg->dfCalcTempCenigrade(dfResOfTherm, REG_ADC_THEMISTOR_B, REG_ADC_THEMISTOR_R0, REG_ADC_THEMISTOR_T0);
				strTemperature.Format(_T("%.2f"), m_dCalc_Temp);
				break;
			case 2:
				dfResOfTherm = map.ucTemperature * 5.0 / REG_ADCINFO_MAX;
				dfResOfTherm = 10000.0 * (5.0 - dfResOfTherm) / dfResOfTherm;
				m_dCalc_Temp = pDlg->dfCalcTempCenigrade(dfResOfTherm, REG_ADC_THEMISTOR_B, REG_ADC_THEMISTOR_R0, REG_ADC_THEMISTOR_T0);
				strTemperature.Format(_T("%.2f"), m_dCalc_Temp);
				break;
			case 3: //03xx
				strTemperature.Format(_T("%.1f"), map.ucTemperature);
				break;
			case 4: //03xx
				strTemperature.Format(_T("%.1f"), map.ucTemperature);
				break;
			case 5: //03xx
				strTemperature.Format(_T("%.1f"), map.ucTemperature);
				break;
			case 6:
				strTemperature.Format(_T("%.1f"), map.ucTemperature);
				break;
			case 7:
				strTemperature.Format(_T("%.1f"), map.ucTemperature);
				break;
			case 8:
				strTemperature.Format(_T("%.1f"), map.ucTemperature);
				break;
			case 9:
				strTemperature.Format(_T("%.1f"), map.ucTemperature);
				break;
			}
			pDlg->GetDlgItem(IDC_TEMPERATURE)->SetWindowText(strTemperature);
 
			//GET_AbsolutePosition
			strPOS_Count.Format("%d", map.usAbsolutePosition);
			switch (ex_DRS_Model_Num)
			{
			case 0:
				strPOS_Angle.Format("%.2f", (map.usAbsolutePosition - 512.0) * 0.325);//받은 Count값을 Angle로 변환// //0101
				break;
			case 1:
				strPOS_Angle.Format("%.2f", (map.usAbsolutePosition - 16384.0) * 0.02778);//받은 Count값을 Angle로 변환// //0102
				break;
			case 2:
				strPOS_Angle.Format("%.2f", (map.usAbsolutePosition - 512.0) * 0.325);//받은 Count값을 Angle로 변환// //0201
				break;
			/////////////////New HerkuleX/////////////////////////////
			case 3:
				strPOS_Angle.Format("%.2f", (map.usAbsolutePosition - 512.0) * 0.325);//받은 Count값을 Angle로 변환// //0301
				break;
			case 4:
				strPOS_Angle.Format("%.2f", (map.usAbsolutePosition - 512.0) * 0.325);//받은 Count값을 Angle로 변환// //0302
				break;
			case 5:
				strPOS_Angle.Format("%.2f", (map.usAbsolutePosition - 512.0) * 0.325);//받은 Count값을 Angle로 변환// //0303
				break;
			//////////////////////////////////////////////////////////
			case 6:
				strPOS_Angle.Format("%.2f", (map.usAbsolutePosition - 1024.0) * 0.163);//받은 Count값을 Angle로 변환// //0401
				break;
			case 7:
				strPOS_Angle.Format("%.2f", (map.usAbsolutePosition - 16384.0) * 0.02778);//받은 Count값을 Angle로 변환// //0402
				break;
			case 8:
				strPOS_Angle.Format("%.2f", (map.usAbsolutePosition - 1024.0) * 0.163);//받은 Count값을 Angle로 변환// //0601
				break;
			case 9:
				strPOS_Angle.Format("%.2f", (map.usAbsolutePosition - 16384.0) * 0.02778);//받은 Count값을 Angle로 변환// //0602
				break;
			}

			//Get_PWM(Torque)//
			//strTorque.Format("%d",map.usPWM);
			//TRACE("Torque = %s", strTorque);

			//Textbox Display//
			if (m_bCheck_AbsolutePoseFlag)
			{
				pDlg->writeMessageBox(("Get_Count = ") + strPOS_Count, GREEN);
				pDlg->writeMessageBox(("Get_Angle = ") + strPOS_Angle, GREEN2);
				m_bCheck_AbsolutePoseFlag = false;
			}
			break;

		case 20: //GET_MinPosition
			strMIN_POS.Format("%d", map.usMinPosition);
			pDlg->writeMessageBox(("Min_Pos = ") + strMIN_POS, BLUE);
			pDlg->m_sliderCtrl.SetRangeMin(map.usMinPosition);
			pDlg->m_sliderCtrl2.SetRangeMin(map.usMinPosition);
			
			break;
		case 22: //GET_MaxPosition
			strMAX_POS.Format("%d", map.usMaxPosition);
			pDlg->writeMessageBox(("Max_Pos = ") + strMAX_POS, BLUE);
			pDlg->m_sliderCtrl.SetRangeMax(map.usMaxPosition);
			pDlg->m_sliderCtrl2.SetRangeMax(map.usMaxPosition);
			//Y Axis Scale Offset _ MAX
			//pDlg->_rtGraph->SetRanges(-(double)map.usMaxPosition, (double)map.usMaxPosition);
			ex_dMaxPosition = (double)map.usMaxPosition;

			strID.Format("%d", (pDlg->m_imotor_ID));
			//List Control BMP이미지 색상바꾸기 //m_iSelectList_ID  //(pDlg->m_imotor_ID-1)
			pDlg->m_listctl_ID.SetItem(m_iSelectList_ID, 0, LVIF_IMAGE, strID, 0, NULL, NULL, NULL);

			break;
		default:
			pDlg->writeMessageBox("[Error]없는 주소입니다..", RED);
			break;
	}

}

void StatAckCallback(unsigned char sid, unsigned char status_error, unsigned char status_detail)
{
	TRACE("StatAckCallback...");
}

void IJogAckCallback(unsigned char sid, unsigned char status_error, unsigned char status_detail)
{
	TRACE("IJogAckCallback...");
}

void SJogAckCallback(unsigned char sid, unsigned char status_error, unsigned char status_detail)
{
	TRACE("SJogAckCallback...");
}

void MIJogAckCallback(unsigned char sid, unsigned char status_error, unsigned char status_detail)
{
	TRACE("MIJogAckCallback...");
}

void MSJogAckCallback(unsigned char sid, unsigned char status_error, unsigned char status_detail)
{
	TRACE("MSJogAckCallback...");
}

void RollbackAckCallback(unsigned char sid, unsigned char status_error, unsigned char status_detail)
{
	TRACE("RollbackAckCallback...");
}

void RebootAckCallback(unsigned char sid, unsigned char status_error, unsigned char status_detail)
{
	TRACE("RebootAckCallback...");
}


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHerkulexDlg 대화 상자



CHerkulexDlg::CHerkulexDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HERKULEX_DIALOG, pParent)
	, m_imotor_ID(0)
	, m_dmotor_Target(0)
	, m_iSpeedTime(60)
	, m_iSlider_Data(512)
	, m_iTurn(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHerkulexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSGLIST, m_ctrlMsgList); //Color List Box//

	DDX_Text(pDX, IDC_EDIT1, m_imotor_ID);
	DDX_Text(pDX, IDC_EDIT2, m_dmotor_Target);
	DDX_Text(pDX, IDC_EDIT3, m_iSpeedTime);
	DDX_Control(pDX, IDC_DSR_MODEL, m_cmdModel);
	DDX_Control(pDX, IDC_SLIDER1, m_sliderCtrl);
	DDX_Text(pDX, IDC_EDIT5, m_iSlider_Data);
	DDX_Control(pDX, IDC_COMBO1, m_comport);
	DDX_Control(pDX, IDC_COMBO2, m_baudrate);
	DDX_Control(pDX, IDC_LIST_ID, m_listctl_ID);
	DDX_Control(pDX, IDC_SLIDER2, m_sliderCtrl2);
	DDX_Text(pDX, IDC_EDIT29, m_iTurn);
	DDX_Control(pDX, IDC_ZOOM, m_Slider_Zoom);
}

BEGIN_MESSAGE_MAP(CHerkulexDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_COMM_READ, OnCommunication)
	ON_BN_CLICKED(IDC_CONNECT, &CHerkulexDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_DISCONNECT, &CHerkulexDlg::OnBnClickedDisconnect)
	ON_BN_CLICKED(IDC_BUTTON2, &CHerkulexDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CHerkulexDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CHerkulexDlg::OnBnClickedButton4)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON5, &CHerkulexDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &CHerkulexDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CHerkulexDlg::OnBnClickedButton6)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON7, &CHerkulexDlg::OnBnClickedButton7)
	ON_CBN_SELCHANGE(IDC_DSR_MODEL, &CHerkulexDlg::OnCbnSelchangeDsrModel)
	ON_BN_CLICKED(IDC_BUTTON8, &CHerkulexDlg::OnBnClickedButton8)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CHerkulexDlg::OnNMCustomdrawSlider1)
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CHerkulexDlg::OnCbnSelchangeCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &CHerkulexDlg::OnCbnDropdownCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CHerkulexDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON9, &CHerkulexDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON11, &CHerkulexDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CHerkulexDlg::OnBnClickedButton12)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ID, &CHerkulexDlg::OnLvnItemchangedListId)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ID, &CHerkulexDlg::OnNMClickListId)
	ON_BN_CLICKED(IDC_BUTTON13, &CHerkulexDlg::OnBnClickedButton13)
	ON_STN_CLICKED(IDC_LOGO1, &CHerkulexDlg::OnStnClickedLogo1)
	ON_BN_CLICKED(IDC_BUTTON14, &CHerkulexDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CHerkulexDlg::OnBnClickedButton15)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CHerkulexDlg::OnNMCustomdrawSlider2)
	ON_BN_CLICKED(IDC_BUTTON18, &CHerkulexDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON22, &CHerkulexDlg::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON17, &CHerkulexDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON24, &CHerkulexDlg::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON25, &CHerkulexDlg::OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON26, &CHerkulexDlg::OnBnClickedButton26)
	//ON_EN_CHANGE(IDC_EDIT29, &CHerkulexDlg::OnEnChangeEdit29)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ZOOM, &CHerkulexDlg::OnNMCustomdrawZoom)
	ON_BN_CLICKED(IDC_RADIO4, &CHerkulexDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO3, &CHerkulexDlg::OnBnClickedRadio3)
END_MESSAGE_MAP()


// CHerkulexDlg 메시지 처리기

BOOL CHerkulexDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	memset(sjogs, 0, sizeof(sjogs));
	memset(ijogs, 0, sizeof(ijogs));
	memset(msjogs, 0, sizeof(msjogs));
	memset(mijogs, 0, sizeof(mijogs));

	memset(RAM, 0, sizeof(RAM));
	memset(&EEP, 0, sizeof(EEP));


	// Serial Comm.
	hCommWnd = m_hWnd;
	m_iBufferData = 0;
	m_strBufferData = _T("");
	m_strRXData = _T("");

	// 2019.04.09 by Mini
	_dlgHerkulex = this;

	regist_ack_callback_eep_write(EEPWriteAckCallback);
	regist_ack_callback_eep_read(EEPReadAckCallback);
	regist_ack_callback_ram_write(RAMWriteAckCallback);
	regist_ack_callback_ram_read(RAMReadAckCallback);
	regist_ack_callback_ram_map_read(RAMMapReadAckCallback);
	regist_ack_callback_eep_map_read(EEPMapReadAckCallback);
	regist_ack_callback_i_jog(IJogAckCallback);
	regist_ack_callback_s_jog(SJogAckCallback);
	regist_ack_callback_mi_jog(MIJogAckCallback);
	regist_ack_callback_ms_jog(MSJogAckCallback);
	regist_ack_callback_stat(StatAckCallback);
	regist_ack_callback_rollback(RollbackAckCallback);
	regist_ack_callback_reboot(RebootAckCallback);

	//시작 시 Position Mode로 Radio button 강제Check//
	CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO1);
	pButton->SetCheck(true);
	//시작 시 Angle_cmd로 Radio button 강제Check//
	CButton* pButton2 = (CButton*)GetDlgItem(IDC_RADIO4);
	pButton2->SetCheck(true);
	//시작 시 S_JOG Mode로 Radio button 강제Check//
	CButton* pButton3 = (CButton*)GetDlgItem(IDC_M_SJOG);
	pButton3->SetCheck(true);
	//시작 시 사다리 프로파일 Mode로 Radio button 강제Check//
	CButton* pButton4 = (CButton*)GetDlgItem(IDC_PROFILE22);
	pButton4->SetCheck(true);

	//Setting Slider Bar Control
	m_sliderCtrl.SetRange(0, 1024);
	m_sliderCtrl.SetLineSize(1);
	m_sliderCtrl.SetPageSize(100);
	m_sliderCtrl.SetPos(512); //중간 값으로 강제 설정//

	m_sliderCtrl2.SetRange(0, 1024);
	m_sliderCtrl2.SetPos(512); //중간 값으로 강제 설정//

	m_Slider_Zoom.SetRange(-100, 100);
	m_Slider_Zoom.SetLineSize(1);
	m_Slider_Zoom.SetPageSize(1);
	m_Slider_Zoom.SetPos(1); 


	for (int i = 0; i < 3; i++)
	{
		m_iLEDCheck[i] = 0;
	}

	//Flag Reset//
	m_bFlag_Servo_ON = FALSE;

	//List Control Setting//
	Init_ID_ListCtrlCols();
	//m_listctl_ID.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_listctl_ID.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);

	InitImageList(); //List control에 이미지 추가

	//Graph Display//
	CRect rtGraph;
	GetDlgItem(IDC_STATIC_RT_GRAPH)->GetWindowRect(rtGraph);
	ScreenToClient(rtGraph);

	_rtGraph = new COScopeCtrl(2);		//2개의 그래프 예약
	_rtGraph->Create(WS_VISIBLE | WS_CHILD, rtGraph, this, IDC_STATIC_RT_GRAPH);
	_rtGraph->SetRanges(-ex_dMaxPosition, ex_dMaxPosition);
	_rtGraph->autofitYscale = true;
	_rtGraph->SetYUnits("Data");
	_rtGraph->SetXUnits("Time");
	_rtGraph->SetLegendLabel("Actual Pose", 0);
	_rtGraph->SetLegendLabel("Desired Trajectory Pose", 1);
	_rtGraph->SetPlotColor(RED, 0);
	_rtGraph->SetPlotColor(GREEN, 1);
	
	//_rtGraph->SetTrendRatio(0, 10);
	//_rtGraph->SetTrendRatio(1, 10);

	_rtGraph->InvalidateCtrl();

	//Status표시용 BMP Image//
	m_bmpOn.LoadBitmap(IDB_ON);
	m_bmpOn2.LoadBitmap(IDB_ON2);
	m_bmpOff.LoadBitmap(IDB_OFF);
	
	//레지스트리 정보 읽기//
	Total_LoadDataFromRegistry();
	for (int i = 0; i < m_regedit_TotalCnt; i++)
	{
		LoadDataFromRegistry(i);
		Init_InsertItem_ID(m_regedit_Model_ID, m_regedit_Model_Name, false);
	}

	//Serial연결정보 읽기//
	Serial_LoadDataFromRegistry();
	//COM Port번호 Scan
	OnCbnDropdownCombo1();
	//저장된 COM포트 번호를 가져와서 연결//
	int m_iIndexListNum = m_comport.FindString(-1, CString(m_regedit_COM));
	m_comport.SetCurSel(m_iIndexListNum);

	if (m_regedit_Baudrate == _T("115200"))
		m_baudrate.SetCurSel(0);
	
	//Main UI버튼들의 비활성화//
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON11)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON12)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON13)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON14)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON15)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON17)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON18)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON22)->EnableWindow(FALSE);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CHerkulexDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CHerkulexDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CHerkulexDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

long CHerkulexDlg::OnCommunication(WPARAM wParam, LPARAM lParam)
{
	BYTE    byRx;
	CString str;

	//Check Ymodem mode
	if (!ex_bFlagYmodem_Mode)
	{
		if (wParam == m_iComport) //USB to Serial
		{
			iSize = (m_hCommPort.m_QueueRead).GetSize();

			for (int i = 0; i < iSize; i++)
			{
				(m_hCommPort.m_QueueRead).GetByte(&byRx);
				m_lstBuffer.push_back(byRx);	// 2019.04.09 by MIni

				//Display를 위함///////////////////////////////////////
				//m_iBufferData = byRx; //Hex를 바로받아서 int로
				//m_strRXData.Format("%02x", m_iBufferData);
				//m_strBufferData += m_strRXData;
				//////////////////////////////////////////////////////
			}

			int pos;
			unsigned char* buffer = new unsigned char[m_lstBuffer.size()];
			std::copy(m_lstBuffer.begin(), m_lstBuffer.end(), buffer);

			if (parse(buffer, m_lstBuffer.size(), &pos) > 0)
			{
				for (int i = 0; i < pos; i++)
					m_lstBuffer.pop_front();
			}

			if (ex_bFlag_ViewModaless) //Packet View에 출력
				Read_PrintData(buffer, iSize);

			delete[] buffer;

			////////////////////////////////////////////////////////////
			//TRACE("m_strBufferData = %s",m_strBufferData);
			//m_strBufferData = _T("");
			///////////////////////////////////////////////////////////
		}
	}
	else
	{
		if (wParam == m_iComport) //USB to Serial
		{
			iSize = (m_hCommPort.m_QueueRead).GetSize();
			ex_strYmodemMsg = _T(""); //MSG init//

			for (int i = 0; i < iSize; i++)
			{
				(m_hCommPort.m_QueueRead).GetByte(&byRx);

				m_iBufferData = byRx; //Hex를 바로받아서 int로
				m_strRXData.Format("%c", m_iBufferData);
				ex_strYmodemMsg += m_strRXData;
			}

			_pFirmDlg->writeMessageBox3(ex_strYmodemMsg, BLUE);
			
		}

	}


	
	
	return 1;
}

BOOL CHerkulexDlg::OpenPort(UINT uPortNo, DWORD uBaudRate)
{
	BOOL bReturn = FALSE;

	// Baud Rate 설정
	m_dwBaudRate = uBaudRate;

	if (uPortNo == m_iComport)
	{
		// Open port
		if (m_hCommPort.m_bConnected)
		{
			AfxMessageBox(_T("[COM]: The serial port is already open!"));
			bReturn = TRUE;
		}
		else
		{
			bReturn = m_hCommPort.OpenPort(uPortNo, m_dwBaudRate, 8, ONESTOPBIT, NOPARITY);
			if (bReturn)
				TRACE(_T("[COM]: 통신연결"));
			else
				AfxMessageBox(_T("[COM%d]: Serial Port Open Fail"), uPortNo);
		}
	}

	return bReturn;
}
void CHerkulexDlg::ClosePort(void)
{
	if (m_hCommPort.m_bConnected)
	{
		m_hCommPort.ClosePort();
		TRACE("[COM]: 통신해제");
	}
}

int CHerkulexDlg::SendHexadecimalData(const CString& strTx)
{

	int nBuffPos = 0;
	int i, j, nLen, nBuffSize;
	BYTE *pBuff, byHigh, byLow;

	nLen = strTx.GetLength();

	// 문자 길이를 %2로 나눈 값이 0이 아니면 홀수 이기 때문에 마지막 문자를 처리 해줘야 함
	if (nLen % 2 == 0)
		nBuffSize = nLen;
	else
		nBuffSize = nLen - 1;

	pBuff = new BYTE[nBuffSize];

	for (i = 0; i < nBuffSize; i += 2)
	{
		byHigh = doHexData2AsciiValue(strTx[i]);
		byLow = doHexData2AsciiValue(strTx[i + 1]);
		pBuff[nBuffPos++] = (byHigh << 4) | byLow;
	}

	//마지막 문자가 1자리수 일때 처리 하기 위해  예) 1 -> 01
	if (nLen % 2 != 0)
		pBuff[nBuffPos++] = doHexData2AsciiValue(strTx[nLen - 1]);

	// 데이터를 8byte씩 전송
	{
		int etc = nBuffPos % 8;
		//포트에 데이터를 8개씩 쓰기 위해
		//데이터의 길이가 8의 배수가 아니면 나머지 데이터는 따로 보내줌
		for (j = 0; j < nBuffPos - etc; j += 8)//8의 배수 보냄
			m_hCommPort.WriteComm(&pBuff[j], 8);

		if (etc != 0)//나머지 데이터 전송
			m_hCommPort.WriteComm(&pBuff[nBuffPos - etc], etc);
	}

	//TRACE("Send data:%s", strTx);

	delete[] pBuff;

	return nBuffPos;
}

int CHerkulexDlg::SendASCIIData(const CString& strTx)
{
	int nSize = strTx.GetLength();
	int bufPos = 0;
	BYTE *Send_buff;
	Send_buff = new BYTE[nSize + 2];
	for (int i = 0; i < nSize; i++)//ASCII 데이터 이기 때문에 버터에 그대로 저장
	{
		Send_buff[bufPos++] = strTx[i];
	}
	Send_buff[bufPos++] = '\r';
	Send_buff[bufPos++] = '\n';


	int etc = bufPos % 8;
	//포트에 데이터를 8개씩 쓰기 위해
	//데이터의 길이가 8의 배수가 아니면 나머지 데이터는 따로 보내줌
	for (int j = 0; j < bufPos - etc; j += 8)
	{
		m_hCommPort.WriteComm(&Send_buff[j], 8);
	}
	if (etc != 0)//나머지 데이터 전송
	{
		m_hCommPort.WriteComm(&Send_buff[bufPos - etc], etc);
	}
	delete[] Send_buff;
	return nSize;
}

BYTE CHerkulexDlg::doHexData2AsciiValue(char cData)
{
	//이 함수는 char문자를 hex값으로 변경해 주는 함수 입니다.
	BYTE byAsciiValue;
	if (('0' <= cData) && (cData <= '9'))
		byAsciiValue = cData - '0';
	else if (('A' <= cData) && (cData <= 'F'))
		byAsciiValue = (cData - 'A') + 10;
	else if (('a' <= cData) && (cData <= 'f'))
		byAsciiValue = (cData - 'a') + 10;
	else
		byAsciiValue = 0;

	return byAsciiValue;
}

void CHerkulexDlg::OnBnClickedConnect()
{
	UpdateData();

	CString strCOMNum, strBaudrate;
	//Serial Port번호 가져오기//
	//if (m_regedit_COM == _T(""))
	//	m_comport.GetLBText(m_comport.GetCurSel(), strCOMNum);
	//else
	//	strCOMNum = m_regedit_COM;

	m_comport.GetLBText(m_comport.GetCurSel(), strCOMNum);
	strCOMNum.Replace("COM", "");
	m_iComport = atoi(strCOMNum);

	//Baudrate가져오기//
	//if (m_regedit_Baudrate == _T(""))
	//	m_baudrate.GetLBText(m_baudrate.GetCurSel(), strBaudrate);
	//else
	//	strBaudrate = m_regedit_Baudrate;

	m_baudrate.GetLBText(m_baudrate.GetCurSel(), strBaudrate);
	m_iBaudrate = atoi(strBaudrate);


	//Serial연결정보 쓰기
	WriteDataToRegistry_Serial((_T("COM") + strCOMNum), strBaudrate);

	// RS232 Connect//
	OpenPort(m_iComport, m_iBaudrate);

	writeMessageBox("Serial Port Connect", BLUE);

	//30ms간격의 Timer
	SetTimer(10, 30, NULL);

	ex_bFlag_Connect = true;

	//Main UI버튼들의 활성화//
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON11)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON12)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON13)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON14)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON15)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON17)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON18)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON22)->EnableWindow(TRUE);
}


void CHerkulexDlg::OnBnClickedDisconnect()
{
	// RS232 Disconnect//
	ClosePort();
	writeMessageBox("Serial Port Disconnect", RED);

	KillTimer(1);

	ex_bFlag_Connect = false;

	//Main UI버튼들의 비활성화//
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON11)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON12)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON13)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON14)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON15)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON17)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON18)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON22)->EnableWindow(FALSE);
}

/////////List Box////////
void CHerkulexDlg::writeMessageBox(CString strMsg, COLORREF crText)
{
	CString strTime;
	SYSTEMTIME st;
	GetLocalTime(&st);

	strTime.Format("[%02d:%02d:%02d]  ", st.wHour, st.wMinute, st.wSecond);
	strMsg = strTime + strMsg;
	m_ctrlMsgList.AddString(strMsg, crText);

	int nCount = m_ctrlMsgList.GetCount();
	if (nCount > 0)
		m_ctrlMsgList.SetCurSel(nCount - 1);
}

void CHerkulexDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_hCommPort.m_bConnected)
	{
		m_hCommPort.ClosePort();
		TRACE("[COM]: 통신해제");
	}

}

void CHerkulexDlg::OnBnClickedButton2()
{
	CString strTemp;
	if (ex_bFlagModal_Map)
		strTemp = _T("1");
	else
		strTemp = _T("0");

	writeMessageBox(strTemp, RED);

}

void CHerkulexDlg::OnBnClickedButton3()
{
	UpdateData();

	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	//RAM Read (ex)
	//nPacketLength = set_ram_read_cmd(szSendBuffer, m_imotor_ID, RAM_ID, sizeof(szIDs));
	nPacketLength = set_ram_map_read_cmd(szSendBuffer, m_imotor_ID, RAM_ID, sizeof(szIDs));
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);


}

void CHerkulexDlg::OnBnClickedButton4()
{
	UpdateData();
	if (!ex_bFlag_Connect)
	{
		AfxMessageBox("Please make a communication connection first!");
		return;
	}
	//Servo On
	Herkulex_Servo_Enable(m_imotor_ID, 1);
}

void CHerkulexDlg::OnBnClickedButton5()
{
	UpdateData();
	if (!ex_bFlag_Connect)
	{
		AfxMessageBox("Please make a communication connection first!");
		return;
	}
	// Servo Off
	Herkulex_Servo_Enable(m_imotor_ID, 2);
}

void CHerkulexDlg::OnBnClickedButton26()
{
	//Add_brake On
	UpdateData();
	if (!ex_bFlag_Connect)
	{
		AfxMessageBox("Please make a communication connection first!");
		return;
	}
	// Brake On
	Herkulex_Servo_Enable(m_imotor_ID, 0);

}

BOOL CHerkulexDlg::Herkulex_ErrorClear(unsigned char cID)
{
	bool bResult = false;
	
	// 에러 초기화
	memset(szSendBuffer, 0, sizeof(szSendBuffer));

	nPacketLength = set_ram_write_cmd(szSendBuffer, cID, RAM_STATUS_ERROR, &ucValue);
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	// 에러 상세 초기화
	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	nPacketLength = set_ram_write_cmd(szSendBuffer, cID, RAM_STATUS_DETAIL, &ucValue);
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);


	bResult = true;
	return bResult;
}

BOOL CHerkulexDlg::Herkulex_Servo_Enable(unsigned char cID, unsigned int uiMode)
{
	bool bResult = false;

	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	switch (uiMode)
	{
	case 0:
		ucValue = TORQUE_CONTROL_BRAKEON;
		nPacketLength = set_ram_write_cmd(szSendBuffer, cID, RAM_TORQUE_CONTROL, &ucValue);
		m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

		if (ex_bFlag_ViewModaless) //Packet View에 출력
			Send_PrintData(szSendBuffer, nPacketLength);

		m_bFlag_Servo_ON = FALSE;
		break;
	case 1:
		ucValue = TORQUE_CONTROL_TORQUEON;
		nPacketLength = set_ram_write_cmd(szSendBuffer, cID, RAM_TORQUE_CONTROL, &ucValue);
		m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

		if (ex_bFlag_ViewModaless) //Packet View에 출력
			Send_PrintData(szSendBuffer, nPacketLength);

		m_bFlag_Servo_ON = TRUE;
		break;
	case 2:
		ucValue = TORQUE_CONTROL_FREE;
		nPacketLength = set_ram_write_cmd(szSendBuffer, cID, RAM_TORQUE_CONTROL, &ucValue);
		m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

		if (ex_bFlag_ViewModaless) //Packet View에 출력
			Send_PrintData(szSendBuffer, nPacketLength);

		m_bFlag_Servo_ON = FALSE;
		break;

	}

	bResult = true;
	return bResult;
}



void CHerkulexDlg::OnBnClickedButton1()
{
	// Position Move Test
	UpdateData();

	//Torque On Flag
	if (strDetail[6] == _T("0"))
	{
		//Servo On
		AfxMessageBox("Press the Servo On button first ! ");
		//Herkulex_Servo_Enable(m_imotor_ID, 1);
	}

	//Select Mode
	if (IsDlgButtonChecked(IDC_RADIO1))//Position Mode
	{
		if(IsDlgButtonChecked(IDC_M_SJOG))
			sjogs[m_imotor_ID - 1].InfiniteTurn = 0x00;

		if (IsDlgButtonChecked(IDC_M_IJOG))
			ijogs[m_imotor_ID - 1].InfiniteTurn = 0x00;

		if (IsDlgButtonChecked(IDC_M_BJOG))
			msjogs[m_imotor_ID - 1].InfiniteTurn = 0x00;

		if (IsDlgButtonChecked(IDC_M_BJOG2))
			mijogs[m_imotor_ID - 1].InfiniteTurn = 0x00;

		bmoveMode = false;
	}
	else //Velocity Mode
	{
		if (IsDlgButtonChecked(IDC_M_SJOG))
			sjogs[m_imotor_ID - 1].InfiniteTurn = 0x01;

		if (IsDlgButtonChecked(IDC_M_IJOG))
			ijogs[m_imotor_ID - 1].InfiniteTurn = 0x01;

		if (IsDlgButtonChecked(IDC_M_BJOG))
			msjogs[m_imotor_ID - 1].InfiniteTurn = 0x01;

		if (IsDlgButtonChecked(IDC_M_BJOG2))
			mijogs[m_imotor_ID - 1].InfiniteTurn = 0x01;

		bmoveMode = true;
	}

	if (IsDlgButtonChecked(IDC_M_SJOG))
	{
		// S_JOG 값 초기화
		sjogs[m_imotor_ID - 1].Value = 0;
		sjogs[m_imotor_ID - 1].Stop = 0;
		sjogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
		sjogs[m_imotor_ID - 1].NoAction = 0;
		sjogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
		if (IsDlgButtonChecked(IDC_PROFILE11))
		{
			sjogs[m_imotor_ID - 1].Profile = 1;
		}
		else
		{
			sjogs[m_imotor_ID - 1].Profile = 0;
		}
	}

	if (IsDlgButtonChecked(IDC_M_IJOG))
	{
		// I_JOG 값 초기화
		ijogs[m_imotor_ID - 1].Value = 0;
		ijogs[m_imotor_ID - 1].Stop = 0;
		ijogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
		ijogs[m_imotor_ID - 1].NoAction = 0;
		ijogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
		if (IsDlgButtonChecked(IDC_PROFILE11))
		{
			ijogs[m_imotor_ID - 1].Profile = 1;
		}
		else
		{
			ijogs[m_imotor_ID - 1].Profile = 0;
		}
	}

	if (IsDlgButtonChecked(IDC_M_BJOG))
	{
		// MS_JOG 값 초기화
		msjogs[m_imotor_ID - 1].Value = 0;
		msjogs[m_imotor_ID - 1].Stop = 0;
		msjogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
		msjogs[m_imotor_ID - 1].NoAction = 0;
		msjogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
		if (IsDlgButtonChecked(IDC_PROFILE11))
		{
			msjogs[m_imotor_ID - 1].Profile = 1;
		}
		else
		{
			msjogs[m_imotor_ID - 1].Profile = 0;
		}
	}

	if (IsDlgButtonChecked(IDC_M_BJOG2))
	{
		// MI_JOG 값 초기화
		mijogs[m_imotor_ID - 1].Value = 0;
		mijogs[m_imotor_ID - 1].Stop = 0;
		mijogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
		mijogs[m_imotor_ID - 1].NoAction = 0;
		mijogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
		if (IsDlgButtonChecked(IDC_PROFILE11))
		{
			mijogs[m_imotor_ID - 1].Profile = 1;
		}
		else
		{
			mijogs[m_imotor_ID - 1].Profile = 0;
		}
	}

	//구동
	if (!bmoveMode)
	{
		//Position Mode//
		//Select Position Command Type// IDC_RADIO3
		if (IsDlgButtonChecked(IDC_RADIO3))
		{
			//Target Command -> Count
			if (IsDlgButtonChecked(IDC_M_SJOG))
				sjogs[m_imotor_ID - 1].Value = (int)m_dmotor_Target;
			if (IsDlgButtonChecked(IDC_M_IJOG))
				ijogs[m_imotor_ID - 1].Value = (int)m_dmotor_Target;
			if (IsDlgButtonChecked(IDC_M_BJOG))
				msjogs[m_imotor_ID - 1].Value = (int)m_dmotor_Target;
			if (IsDlgButtonChecked(IDC_M_BJOG2))
				mijogs[m_imotor_ID - 1].Value = (int)m_dmotor_Target;

		}
		else
		{
			//Target Command -> Degree
			//Angle을 Count로 환산//
			int m_imotor_Count = 0;
			switch (ex_DRS_Model_Num)
			{
				case 0:
					m_imotor_Count = (int)(m_dmotor_Target / 0.325) + 512; //0101
					break;
				case 1:
					m_imotor_Count = (int)(m_dmotor_Target / 0.02778) + 16384; //0102
					break;
				case 2:
					m_imotor_Count = (int)(m_dmotor_Target / 0.325) + 512; //0201
					break;
				/////////////////////New HerkuleX////////////////////////////////
				case 3:
					m_imotor_Count = (int)(m_dmotor_Target / 0.325) + 512; //0301
					break;
				case 4:
					m_imotor_Count = (int)(m_dmotor_Target / 0.325) + 512; //0302
					break;
				case 5:
					m_imotor_Count = (int)(m_dmotor_Target / 0.325) + 512; //0303
					break;
				/////////////////////////////////////////////////////////////////
				case 6:
					m_imotor_Count = (int)(m_dmotor_Target / 0.163) + 1024; //0401
					break;
				case 7:
					m_imotor_Count = (int)(m_dmotor_Target / 0.02778) + 16384; //0402
					break;
				case 8:
					m_imotor_Count = (int)(m_dmotor_Target / 0.163) + 1024; //0601
					break;
				case 9:
					m_imotor_Count = (int)(m_dmotor_Target / 0.02778) + 16384; //0602
					break;
			}
			if (IsDlgButtonChecked(IDC_M_SJOG))
				sjogs[m_imotor_ID - 1].Value = m_imotor_Count;
			if (IsDlgButtonChecked(IDC_M_IJOG))
				ijogs[m_imotor_ID - 1].Value = m_imotor_Count;
			if (IsDlgButtonChecked(IDC_M_BJOG))
				msjogs[m_imotor_ID - 1].Value = m_imotor_Count;
			if (IsDlgButtonChecked(IDC_M_BJOG2))
				mijogs[m_imotor_ID - 1].Value = m_imotor_Count;


		}
	}
	else
	{
		//Velocity Mode//
		if (IsDlgButtonChecked(IDC_M_SJOG))
			sjogs[m_imotor_ID - 1].Value = (int)m_dmotor_Target;
		if (IsDlgButtonChecked(IDC_M_IJOG))
			ijogs[m_imotor_ID - 1].Value = (int)m_dmotor_Target;
		if (IsDlgButtonChecked(IDC_M_BJOG))
			msjogs[m_imotor_ID - 1].Value = (int)m_dmotor_Target;
		if (IsDlgButtonChecked(IDC_M_BJOG2))
			mijogs[m_imotor_ID - 1].Value = (int)m_dmotor_Target;
	}

	if (!ex_bFlag_Connect)
	{
		AfxMessageBox("Please make a communication connection first!");
		return;
	}

	memset(szSendBuffer, 0, sizeof(szSendBuffer));

	if (IsDlgButtonChecked(IDC_M_SJOG))
		nPacketLength = set_s_jog_cmd(szSendBuffer, m_imotor_ID, m_iSpeedTime, &sjogs[m_imotor_ID - 1], 1);
	if (IsDlgButtonChecked(IDC_M_IJOG))
	{
		ijogs[m_imotor_ID - 1].PlayTime_ms = m_iSpeedTime;
		nPacketLength = set_i_jog_cmd(szSendBuffer, m_imotor_ID, &ijogs[m_imotor_ID - 1], 1);
	}
	if (IsDlgButtonChecked(IDC_M_BJOG))
	{
		if (IsDlgButtonChecked(IDC_MS))
		{
			nPacketLength = set_ms_jog_cmd(szSendBuffer, m_imotor_ID, m_iSpeedTime, &msjogs[m_imotor_ID - 1], 1, m_iTurn, true);
		}
		else
		{
			nPacketLength = set_ms_jog_cmd(szSendBuffer, m_imotor_ID, m_iSpeedTime, &msjogs[m_imotor_ID - 1], 1, m_iTurn, false);
		}
	}
	if (IsDlgButtonChecked(IDC_M_BJOG2))
	{
		mijogs[m_imotor_ID - 1].PlayTime_ms = m_iSpeedTime;
		if (IsDlgButtonChecked(IDC_MI))
		{
			nPacketLength = set_mi_jog_cmd(szSendBuffer, m_imotor_ID, &mijogs[m_imotor_ID - 1], 1, m_iTurn, true);
		}
		else
		{
			nPacketLength = set_mi_jog_cmd(szSendBuffer, m_imotor_ID, &mijogs[m_imotor_ID - 1], 1, m_iTurn, false);
		}
	}

	//Send//
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	if (ex_bFlag_ViewModaless) //Packet View에 출력
		Send_PrintData(szSendBuffer, nPacketLength);
}


void CHerkulexDlg::OnBnClickedButton6()
{
	UpdateData();

	//선택된 모터의 Error Clear  단,Servo Off를 한 후에 호출해야 함.
	// Servo Off
	Herkulex_Servo_Enable(m_imotor_ID, 2);
	//Error Clear
	Herkulex_ErrorClear(m_imotor_ID);
	Sleep(500);
	// Servo On
	Herkulex_Servo_Enable(m_imotor_ID, 1);
	
}


void CHerkulexDlg::OnTimer(UINT_PTR nIDEvent)
{
	//Timer Loop//
	//To do...
	if (nIDEvent == 10)
	{
		if (ex_bFlagSCAN)
		{
			//RAM All Read//
			RAM_Register_ReadALL();

			//if (ex_bFlagMainUI)
			{
				//Graph Display//
				switch (ex_DRS_Model_Num)
				{
				case 0: //0101
					m_dGraphData[0] = (double)(RAM[m_imotor_ID].usCalibratedPosition & 0x1FFF);
					m_dGraphData[1] = (double)(RAM[m_imotor_ID].usAbsoluteDesiredTrajectoryPosition & 0x1FFF);
					break;
				case 1: //0102
					m_dGraphData[0] = (double)(RAM[m_imotor_ID].usCalibratedPosition & 0x7FFF);
					m_dGraphData[1] = (double)(RAM[m_imotor_ID].usAbsoluteDesiredTrajectoryPosition & 0x7FFF);
					break;
				case 2: //0201
					m_dGraphData[0] = (double)(RAM[m_imotor_ID].usCalibratedPosition & 0x1FFF);
					m_dGraphData[1] = (double)(RAM[m_imotor_ID].usAbsoluteDesiredTrajectoryPosition & 0x1FFF);
					break;
				case 3: //0301
					m_dGraphData[0] = (double)RAM[m_imotor_ID].usCalibratedPosition;
					m_dGraphData[1] = (double)RAM[m_imotor_ID].usAbsoluteDesiredTrajectoryPosition;
					break;
				case 4: //0302
					m_dGraphData[0] = (double)RAM[m_imotor_ID].usCalibratedPosition;
					m_dGraphData[1] = (double)RAM[m_imotor_ID].usAbsoluteDesiredTrajectoryPosition;
					break;
				case 5: //0303
					m_dGraphData[0] = (double)RAM[m_imotor_ID].usCalibratedPosition;
					m_dGraphData[1] = (double)RAM[m_imotor_ID].usAbsoluteDesiredTrajectoryPosition;
					break;
				case 6: //0401
					m_dGraphData[0] = (double)(RAM[m_imotor_ID].usCalibratedPosition & 0x7FFF);
					m_dGraphData[1] = (double)(RAM[m_imotor_ID].usAbsoluteDesiredTrajectoryPosition & 0x7FFF);
					break;
				case 7: //0402
					m_dGraphData[0] = (double)(RAM[m_imotor_ID].usCalibratedPosition & 0x7FFF);
					m_dGraphData[1] = (double)(RAM[m_imotor_ID].usAbsoluteDesiredTrajectoryPosition & 0x7FFF);
					break;
				case 8: //0601
					m_dGraphData[0] = (double)(RAM[m_imotor_ID].usCalibratedPosition & 0x7FFF);
					m_dGraphData[1] = (double)(RAM[m_imotor_ID].usAbsoluteDesiredTrajectoryPosition & 0x7FFF);
					break;
				case 9: //0602
					m_dGraphData[0] = (double)(RAM[m_imotor_ID].usCalibratedPosition & 0x7FFF);
					m_dGraphData[1] = (double)(RAM[m_imotor_ID].usAbsoluteDesiredTrajectoryPosition & 0x7FFF);
					break;
				}

				//m_dGraphData[1] = (double)(RAM[m_imotor_ID].usAbsoluteDesiredTrajectoryPosition & 0x1FFF); //usAbsoluteGoalPosition;
				_rtGraph->AppendPoints(m_dGraphData);

			}

			//Status Update//
			ex_bFlag_Status = Status_Display();
			

			//Mode Select Display//
			if (ex_bFlag_ServoON)
			{
				GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);

				GetDlgItem(IDC_M_SJOG)->EnableWindow(FALSE);
				GetDlgItem(IDC_M_IJOG)->EnableWindow(FALSE);
				GetDlgItem(IDC_M_BJOG)->EnableWindow(FALSE);
				GetDlgItem(IDC_M_BJOG2)->EnableWindow(FALSE);
				GetDlgItem(IDC_MS)->EnableWindow(FALSE);
				GetDlgItem(IDC_MI)->EnableWindow(FALSE);
			}
			else
			{
				GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);

				GetDlgItem(IDC_M_SJOG)->EnableWindow(TRUE);
				GetDlgItem(IDC_M_IJOG)->EnableWindow(TRUE);
				GetDlgItem(IDC_M_BJOG)->EnableWindow(TRUE);
				GetDlgItem(IDC_M_BJOG2)->EnableWindow(TRUE);
				GetDlgItem(IDC_MS)->EnableWindow(TRUE);
				GetDlgItem(IDC_MI)->EnableWindow(TRUE);
			}

			//EEP All Read//
			//EEP_Register_ReadALL();
		}

	}

	CDialogEx::OnTimer(nIDEvent);
}


void CHerkulexDlg::OnBnClickedButton7()
{
	UpdateData();
	//LED Setting//
	int m_iRGB_Color[3] = { 0, };
	//LED Check Box관련//
	CButton *pChecBox1 = (CButton*)GetDlgItem(IDC_CHECK2);
	CButton *pChecBox2 = (CButton*)GetDlgItem(IDC_CHECK3);
	CButton *pChecBox3 = (CButton*)GetDlgItem(IDC_CHECK4);

	if (m_iLEDCheck[0] = pChecBox1->GetCheck()) //GREEN Enable
		m_iRGB_Color[0] = 1;
	else
		m_iRGB_Color[0] = 0;

	if (m_iLEDCheck[1] = pChecBox2->GetCheck()) //BLUE Enable
		m_iRGB_Color[1] = 2;
	else
		m_iRGB_Color[1] = 0;

	if (m_iLEDCheck[2] = pChecBox3->GetCheck()) //RED Enable
		m_iRGB_Color[2] = 4;
	else
		m_iRGB_Color[2] = 0;


	RAM[m_imotor_ID - 1].ucID = szIDs[m_imotor_ID - 1];
	//RGB색상 정보 Update//
	m_iRGB_SUM = m_iRGB_Color[0] + m_iRGB_Color[1] + m_iRGB_Color[2];
	RAM[m_imotor_ID - 1].ucLEDControl = m_iRGB_SUM;

	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_LED_CONTROL, &RAM[m_imotor_ID - 1].ucLEDControl);
	//Send//
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	if (ex_bFlag_ViewModaless) //Packet View에 출력
		Send_PrintData(szSendBuffer, nPacketLength);


}


void CHerkulexDlg::OnCbnSelchangeDsrModel()
{
	//DSR Model Type
	CString m_strModel_Type = _T("");
	int m_iModel;
	//Get Combo Box Sel_Number//
	m_iModel = m_cmdModel.GetCurSel();
	switch (m_iModel)
	{
		case 0:
			m_strModel_Type = _T("DRS-0101");
			ex_DRS_Model_Num = 0;
			break;
		case 1:
			m_strModel_Type = _T("DRS-0102");
			ex_DRS_Model_Num = 1;
			break;
		case 2:
			m_strModel_Type = _T("DRS-0201");
			ex_DRS_Model_Num = 2;
			break;
			///////////New HerkuleX//////////////
		case 3:
			m_strModel_Type = _T("DRS-0301");
			ex_DRS_Model_Num = 3;
			break;
		case 4:
			m_strModel_Type = _T("DSR-0302");
			ex_DRS_Model_Num = 4;
			break;
		case 5:
			m_strModel_Type = _T("DRS-0303");
			ex_DRS_Model_Num = 5;
			break;
			/////////////////////////////////////
		case 6:
			m_strModel_Type = _T("DRS-0401");
			ex_DRS_Model_Num = 6;
			break;
		case 7:
			m_strModel_Type = _T("DRS-0402");
			ex_DRS_Model_Num = 7;
			break;
		case 8:
			m_strModel_Type = _T("DRS-0601");
			ex_DRS_Model_Num = 8;
			break;
		case 9:
			m_strModel_Type = _T("DRS-0602");
			ex_DRS_Model_Num = 9;
			break;
		
	}

}


void CHerkulexDlg::OnBnClickedButton8()
{
	// 현재 위치값 읽어오기
	UpdateData();

	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	//Read (ex)
	//nPacketLength = set_ram_read_cmd(szSendBuffer, m_imotor_ID, RAM_ABSOLUTE_POSITION, sizeof(szIDs));
	//nPacketLength = set_ram_read_cmd(szSendBuffer, m_imotor_ID, RAM_ID, 60);
	nPacketLength = set_ram_map_read_cmd(szSendBuffer, m_imotor_ID, RAM_ID, sizeof(szIDs));
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	if (ex_bFlag_ViewModaless) //Packet View에 출력
		Send_PrintData(szSendBuffer, nPacketLength);

	m_bCheck_AbsolutePoseFlag = true;
}

void CHerkulexDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	*pResult = 0;
}


void CHerkulexDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nSBCode == SB_ENDSCROLL)
		return;

	if (pScrollBar == (CScrollBar*)&m_sliderCtrl)
	{
		if (!ex_bFlag_Connect)
		{
			AfxMessageBox("Please make a communication connection first!");
			return;
		}

		//Torque On Flag
		if (strDetail[6] == _T("0"))
		{
			//Servo On
			Herkulex_Servo_Enable(m_imotor_ID, 1);
		}

		m_iSlider_Data = m_sliderCtrl.GetPos();

		CString strTemp;
		strTemp.Format("%d", m_iSlider_Data);
		GetDlgItem(IDC_EDIT5)->SetWindowText(strTemp);

		UpdateData(FALSE);

		if (IsDlgButtonChecked(IDC_RADIO1))
		{
			if (IsDlgButtonChecked(IDC_M_SJOG))
			{
				sjogs[m_imotor_ID - 1].InfiniteTurn = 0x00;//Position Mode
				// S_JOG 값 초기화
				sjogs[m_imotor_ID - 1].Value = 0;
				sjogs[m_imotor_ID - 1].Stop = 0;
				sjogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
				sjogs[m_imotor_ID - 1].NoAction = 0;
				sjogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
				sjogs[m_imotor_ID - 1].Value = (int)m_iSlider_Data;
				if (IsDlgButtonChecked(IDC_PROFILE11))
				{
					sjogs[m_imotor_ID - 1].Profile = 1;
				}
				else
				{
					sjogs[m_imotor_ID - 1].Profile = 0;
				}
			}
			if (IsDlgButtonChecked(IDC_M_IJOG))
			{
				ijogs[m_imotor_ID - 1].InfiniteTurn = 0x00;//Position Mode
				// I_JOG 값 초기화
				ijogs[m_imotor_ID - 1].Value = 0;
				ijogs[m_imotor_ID - 1].Stop = 0;
				ijogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
				ijogs[m_imotor_ID - 1].NoAction = 0;
				ijogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
				ijogs[m_imotor_ID - 1].PlayTime_ms = m_iSpeedTime;
				ijogs[m_imotor_ID - 1].Value = (int)m_iSlider_Data;
				if (IsDlgButtonChecked(IDC_PROFILE11))
				{
					ijogs[m_imotor_ID - 1].Profile = 1;
				}
				else
				{
					ijogs[m_imotor_ID - 1].Profile = 0;
				}
			}

			if (IsDlgButtonChecked(IDC_M_BJOG))
			{
				msjogs[m_imotor_ID - 1].InfiniteTurn = 0x00;
				// MS_JOG 값 초기화
				msjogs[m_imotor_ID - 1].Value = 0;
				msjogs[m_imotor_ID - 1].Stop = 0;
				msjogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
				msjogs[m_imotor_ID - 1].NoAction = 0;
				msjogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
				if (IsDlgButtonChecked(IDC_PROFILE11))
				{
					msjogs[m_imotor_ID - 1].Profile = 1;
				}
				else
				{
					msjogs[m_imotor_ID - 1].Profile = 0;
				}
			}

			if (IsDlgButtonChecked(IDC_M_BJOG2))
			{
				mijogs[m_imotor_ID - 1].InfiniteTurn = 0x00;
				// MI_JOG 값 초기화
				mijogs[m_imotor_ID - 1].Value = 0;
				mijogs[m_imotor_ID - 1].Stop = 0;
				mijogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
				mijogs[m_imotor_ID - 1].NoAction = 0;
				mijogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
				if (IsDlgButtonChecked(IDC_PROFILE11))
				{
					mijogs[m_imotor_ID - 1].Profile = 1;
				}
				else
				{
					mijogs[m_imotor_ID - 1].Profile = 0;
				}
			}

			bmoveMode = false;
		}
		else
		{
			if (IsDlgButtonChecked(IDC_M_SJOG))
			{
				sjogs[m_imotor_ID - 1].InfiniteTurn = 0x01; //Velocity Mode
				// S_JOG 값 초기화
				sjogs[m_imotor_ID - 1].Value = 0;
				sjogs[m_imotor_ID - 1].Stop = 0;
				sjogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
				sjogs[m_imotor_ID - 1].NoAction = 0;
				sjogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
				sjogs[m_imotor_ID - 1].Value = (int)m_iSlider_Data;
				if (IsDlgButtonChecked(IDC_PROFILE11))
				{
					sjogs[m_imotor_ID - 1].Profile = 1;
				}
				else
				{
					sjogs[m_imotor_ID - 1].Profile = 0;
				}
			}
			if (IsDlgButtonChecked(IDC_M_IJOG))
			{
				ijogs[m_imotor_ID - 1].InfiniteTurn = 0x01; //Velocity Mode
				// I_JOG 값 초기화
				ijogs[m_imotor_ID - 1].Value = 0;
				ijogs[m_imotor_ID - 1].Stop = 0;
				ijogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
				ijogs[m_imotor_ID - 1].NoAction = 0;
				ijogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
				ijogs[m_imotor_ID - 1].Value = (int)m_iSlider_Data;
				if (IsDlgButtonChecked(IDC_PROFILE11))
				{
					ijogs[m_imotor_ID - 1].Profile = 1;
				}
				else
				{
					ijogs[m_imotor_ID - 1].Profile = 0;
				}
			}

			if (IsDlgButtonChecked(IDC_M_BJOG))
			{
				msjogs[m_imotor_ID - 1].InfiniteTurn = 0x01;
				// MS_JOG 값 초기화
				msjogs[m_imotor_ID - 1].Value = 0;
				msjogs[m_imotor_ID - 1].Stop = 0;
				msjogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
				msjogs[m_imotor_ID - 1].NoAction = 0;
				msjogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
				if (IsDlgButtonChecked(IDC_PROFILE11))
				{
					msjogs[m_imotor_ID - 1].Profile = 1;
				}
				else
				{
					msjogs[m_imotor_ID - 1].Profile = 0;
				}
			}

			if (IsDlgButtonChecked(IDC_M_BJOG2))
			{
				mijogs[m_imotor_ID - 1].InfiniteTurn = 0x01;
				// MI_JOG 값 초기화
				mijogs[m_imotor_ID - 1].Value = 0;
				mijogs[m_imotor_ID - 1].Stop = 0;
				mijogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
				mijogs[m_imotor_ID - 1].NoAction = 0;
				mijogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
				if (IsDlgButtonChecked(IDC_PROFILE11))
				{
					mijogs[m_imotor_ID - 1].Profile = 1;
				}
				else
				{
					mijogs[m_imotor_ID - 1].Profile = 0;
				}
			}

			bmoveMode = true;
		}

		memset(szSendBuffer, 0, sizeof(szSendBuffer));

		if (IsDlgButtonChecked(IDC_M_SJOG))
			nPacketLength = set_s_jog_cmd(szSendBuffer, 0xFE, m_iSpeedTime, &sjogs[m_imotor_ID - 1], 1);
		if (IsDlgButtonChecked(IDC_M_IJOG))
			nPacketLength = set_i_jog_cmd(szSendBuffer, 0xFE, &ijogs[m_imotor_ID - 1], 1);
		if (IsDlgButtonChecked(IDC_M_BJOG))
		{
			if (IsDlgButtonChecked(IDC_MS))
			{
				nPacketLength = set_ms_jog_cmd(szSendBuffer, m_imotor_ID, m_iSpeedTime, &msjogs[m_imotor_ID - 1], 1, m_iTurn, true);
			}
			else
			{
				nPacketLength = set_ms_jog_cmd(szSendBuffer, m_imotor_ID, m_iSpeedTime, &msjogs[m_imotor_ID - 1], 1, m_iTurn, false);
			}
		}
		if (IsDlgButtonChecked(IDC_M_BJOG2))
		{
			mijogs[m_imotor_ID - 1].PlayTime_ms = m_iSpeedTime;
			if (IsDlgButtonChecked(IDC_MI))
			{
				nPacketLength = set_mi_jog_cmd(szSendBuffer, m_imotor_ID, &mijogs[m_imotor_ID - 1], 1, m_iTurn, true);
			}
			else
			{
				nPacketLength = set_mi_jog_cmd(szSendBuffer, m_imotor_ID, &mijogs[m_imotor_ID - 1], 1, m_iTurn, false);
			}
		}

		//Send//
		m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

		if (ex_bFlag_ViewModaless) //Packet View에 출력
			Send_PrintData(szSendBuffer, nPacketLength);

	}
	else if (pScrollBar == (CScrollBar*)&m_Slider_Zoom)
	{
		m_iZoomData = m_Slider_Zoom.GetPos();

		if (m_iZoomData >= 0) //Zoom in
		{
			if (m_iZoomData == 0)
				m_iZoomData = 1;
			else
				m_dZooming = m_iZoomData;

			_rtGraph->SetRanges(-ex_dMaxPosition * m_dZooming, ex_dMaxPosition * m_dZooming);
		}
		else //Zoom out
		{
			//m_dZooming = 0.01 *  (11.0 + m_iZoomData);
			//_rtGraph->SetRanges(-ex_dMaxPosition * m_dZooming, ex_dMaxPosition * m_dZooming);
			m_dZooming = -1.0 *  m_iZoomData;
			_rtGraph->SetRanges(-ex_dMaxPosition / m_dZooming, ex_dMaxPosition / m_dZooming);
		}
		
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CHerkulexDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CHerkulexDlg::OnCbnDropdownCombo1()
{
	HKEY hKey;
	TCHAR szData[20], szName[100];
	DWORD index = 0, dwSize = 100, dwSize2 = 20, dwType = REG_SZ;
	//시리얼 포트가 저장된 곳
	RegOpenKey(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), &hKey);

	memset(szData, 0x00, sizeof(szData));
	memset(szName, 0x00, sizeof(szName));
	m_comport.ResetContent();

	while (ERROR_SUCCESS == RegEnumValue(hKey, index, szName, &dwSize, NULL, NULL, NULL, NULL))
	{
		index++;

		RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);
		m_comport.AddString(CString(szData));
		memset(szData, 0x00, sizeof(szData));
		memset(szName, 0x00, sizeof(szName));
		dwSize = 100;
		dwSize2 = 20;
	}

	RegCloseKey(hKey);

}

void CHerkulexDlg::OnCbnSelchangeCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CHerkulexDlg::OnBnClickedButton9()
{
	//레지스터 상세속성 페이지//
	UpdateData();

	if (!ex_bFlagModal_Map) //중복 실행을 막는다.
	{
		delete _pMapDlg;
		//동적 메모리 할당을 한 후에
		_pMapDlg = new CRegisterMAP(this);
		//모달리스 대화상자를 생성하고
		_pMapDlg->Create(IDD_REGISTERMAP, this);
		//화면에 나타내기 위해 ShowWindow() 함수를 호출
		_pMapDlg->ShowWindow(SW_SHOW);

		ex_bFlagModal_Map = true;
	}

}

BOOL CHerkulexDlg::RAM_Register_ReadALL()
{
	BOOL bResult = FALSE;

	//RAM Register Read....
	//UpdateData();

	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	//Read (ex)
	//nPacketLength = set_ram_read_cmd(szSendBuffer, m_imotor_ID, RAM_ID, 60);
	nPacketLength = set_ram_map_read_cmd(szSendBuffer, m_imotor_ID, RAM_ID, sizeof(szIDs));
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	bResult = TRUE;

	return bResult;
}

BOOL CHerkulexDlg::EEP_Register_ReadALL()
{
	BOOL bResult = FALSE;

	//EEP Register Read....
	UpdateData();

	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	//Read (ex)
	nPacketLength = set_eep_read_cmd(szSendBuffer, m_imotor_ID, EEP_MODEL_NO_1);
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	bResult = TRUE;

	return bResult;
}

void CHerkulexDlg::OnBnClickedButton11()
{
	UpdateData();

	//Torque On Flag
	if (strDetail[6] == _T("0"))
	{
		//Servo On
		Herkulex_Servo_Enable(m_imotor_ID, 1);
	}

	m_sliderCtrl.SetPos(m_iSlider_Data);

	if (IsDlgButtonChecked(IDC_RADIO1))
	{
		if (IsDlgButtonChecked(IDC_M_SJOG))
		{
			sjogs[m_imotor_ID - 1].InfiniteTurn = 0x00;//Position Mode
			// S_JOG 값 초기화
			sjogs[m_imotor_ID - 1].Value = 0;
			sjogs[m_imotor_ID - 1].Stop = 0;
			sjogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
			sjogs[m_imotor_ID - 1].NoAction = 0;
			sjogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
			sjogs[m_imotor_ID - 1].Value = (int)m_iSlider_Data;
			if (IsDlgButtonChecked(IDC_PROFILE11))
			{
				sjogs[m_imotor_ID - 1].Profile = 1;
			}
			else
			{
				sjogs[m_imotor_ID - 1].Profile = 0;
			}
		}
		if (IsDlgButtonChecked(IDC_M_IJOG))
		{
			ijogs[m_imotor_ID - 1].InfiniteTurn = 0x00;//Position Mode
			// I_JOG 값 초기화
			ijogs[m_imotor_ID - 1].Value = 0;
			ijogs[m_imotor_ID - 1].Stop = 0;
			ijogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
			ijogs[m_imotor_ID - 1].NoAction = 0;
			ijogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
			ijogs[m_imotor_ID - 1].PlayTime_ms = m_iSpeedTime;
			ijogs[m_imotor_ID - 1].Value = (int)m_iSlider_Data;
			if (IsDlgButtonChecked(IDC_PROFILE11))
			{
				ijogs[m_imotor_ID - 1].Profile = 1;
			}
			else
			{
				ijogs[m_imotor_ID - 1].Profile = 0;
			}
		}
		if (IsDlgButtonChecked(IDC_M_BJOG))
		{
			msjogs[m_imotor_ID - 1].InfiniteTurn = 0x00;
			// MS_JOG 값 초기화
			msjogs[m_imotor_ID - 1].Value = 0;
			msjogs[m_imotor_ID - 1].Stop = 0;
			msjogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
			msjogs[m_imotor_ID - 1].NoAction = 0;
			msjogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
			msjogs[m_imotor_ID - 1].Value = (int)m_iSlider_Data;
			if (IsDlgButtonChecked(IDC_PROFILE11))
			{
				msjogs[m_imotor_ID - 1].Profile = 1;
			}
			else
			{
				msjogs[m_imotor_ID - 1].Profile = 0;
			}
		}

		if (IsDlgButtonChecked(IDC_M_BJOG2))
		{
			mijogs[m_imotor_ID - 1].InfiniteTurn = 0x00;
			// MI_JOG 값 초기화
			mijogs[m_imotor_ID - 1].Value = 0;
			mijogs[m_imotor_ID - 1].Stop = 0;
			mijogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
			mijogs[m_imotor_ID - 1].NoAction = 0;
			mijogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
			mijogs[m_imotor_ID - 1].PlayTime_ms = m_iSpeedTime;
			mijogs[m_imotor_ID - 1].Value = (int)m_iSlider_Data;
			if (IsDlgButtonChecked(IDC_PROFILE11))
			{
				mijogs[m_imotor_ID - 1].Profile = 1;
			}
			else
			{
				mijogs[m_imotor_ID - 1].Profile = 0;
			}
		}

		bmoveMode = false;
	}
	else
	{
		if (IsDlgButtonChecked(IDC_M_SJOG))
		{
			sjogs[m_imotor_ID - 1].InfiniteTurn = 0x01; //Velocity Mode
			// S_JOG 값 초기화
			sjogs[m_imotor_ID - 1].Value = 0;
			sjogs[m_imotor_ID - 1].Stop = 0;
			sjogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
			sjogs[m_imotor_ID - 1].NoAction = 0;
			sjogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
			sjogs[m_imotor_ID - 1].Value = (int)m_iSlider_Data;
			if (IsDlgButtonChecked(IDC_PROFILE11))
			{
				sjogs[m_imotor_ID - 1].Profile = 1;
			}
			else
			{
				sjogs[m_imotor_ID - 1].Profile = 0;
			}
		}
		if (IsDlgButtonChecked(IDC_M_IJOG))
		{
			ijogs[m_imotor_ID - 1].InfiniteTurn = 0x01; //Velocity Mode
			// I_JOG 값 초기화
			ijogs[m_imotor_ID - 1].Value = 0;
			ijogs[m_imotor_ID - 1].Stop = 0;
			ijogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
			ijogs[m_imotor_ID - 1].NoAction = 0;
			ijogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
			ijogs[m_imotor_ID - 1].Value = (int)m_iSlider_Data;
			if (IsDlgButtonChecked(IDC_PROFILE11))
			{
				ijogs[m_imotor_ID - 1].Profile = 1;
			}
			else
			{
				ijogs[m_imotor_ID - 1].Profile = 0;
			}
		}
		if (IsDlgButtonChecked(IDC_M_BJOG))
		{
			msjogs[m_imotor_ID - 1].InfiniteTurn = 0x01;
			// MS_JOG 값 초기화
			msjogs[m_imotor_ID - 1].Value = 0;
			msjogs[m_imotor_ID - 1].Stop = 0;
			msjogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
			msjogs[m_imotor_ID - 1].NoAction = 0;
			msjogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
			msjogs[m_imotor_ID - 1].Value = (int)m_iSlider_Data;
			if (IsDlgButtonChecked(IDC_PROFILE11))
			{
				msjogs[m_imotor_ID - 1].Profile = 1;
			}
			else
			{
				msjogs[m_imotor_ID - 1].Profile = 0;
			}
		}

		if (IsDlgButtonChecked(IDC_M_BJOG2))
		{
			mijogs[m_imotor_ID - 1].InfiniteTurn = 0x01;
			// MI_JOG 값 초기화
			mijogs[m_imotor_ID - 1].Value = 0;
			mijogs[m_imotor_ID - 1].Stop = 0;
			mijogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
			mijogs[m_imotor_ID - 1].NoAction = 0;
			mijogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
			mijogs[m_imotor_ID - 1].Value = (int)m_iSlider_Data;
			if (IsDlgButtonChecked(IDC_PROFILE11))
			{
				mijogs[m_imotor_ID - 1].Profile = 1;
			}
			else
			{
				mijogs[m_imotor_ID - 1].Profile = 0;
			}
		}

		bmoveMode = true;
	}

	memset(szSendBuffer, 0, sizeof(szSendBuffer));

	//if (IsDlgButtonChecked(IDC_M_SJOG))
	//	nPacketLength = set_s_jog_cmd(szSendBuffer, 0xFE, m_iSpeedTime, &sjogs[m_imotor_ID - 1], 1);
	//if (IsDlgButtonChecked(IDC_M_IJOG))
	//	nPacketLength = set_i_jog_cmd(szSendBuffer, 0xFE, &ijogs[m_imotor_ID - 1], 1);
	//if (IsDlgButtonChecked(IDC_M_BJOG))
	//	TRACE("do something...");

	if (IsDlgButtonChecked(IDC_M_SJOG))
		nPacketLength = set_s_jog_cmd(szSendBuffer, m_imotor_ID, m_iSpeedTime, &sjogs[m_imotor_ID - 1], 1);
	if (IsDlgButtonChecked(IDC_M_IJOG))
		nPacketLength = set_i_jog_cmd(szSendBuffer, m_imotor_ID, &ijogs[m_imotor_ID - 1], 1);
	if (IsDlgButtonChecked(IDC_M_BJOG))
		nPacketLength = set_ms_jog_cmd(szSendBuffer, m_imotor_ID, m_iSpeedTime, &msjogs[m_imotor_ID - 1], 1, m_iTurn, false);
	if (IsDlgButtonChecked(IDC_M_BJOG2))
		nPacketLength = set_mi_jog_cmd(szSendBuffer, m_imotor_ID, &mijogs[m_imotor_ID - 1], 1, m_iTurn, false);


	//Send//
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	if (ex_bFlag_ViewModaless) //Packet View에 출력
		Send_PrintData(szSendBuffer, nPacketLength);

}

void CHerkulexDlg::OnBnClickedButton12()
{
	if (!ex_bFlag_Connect)
	{
		AfxMessageBox("Please make a communication connection first!");
		return;
	}


	memset(&EEP, 0, sizeof(EEP));
	Sleep(500);
	// 연결된 HerkuleX ID Scan을 위한 Progress Dlg호출//
	SetRedraw(FALSE);
	m_listctl_ID.DeleteAllItems();
	SetRedraw(TRUE);

	ex_bFlagSCAN = false;

	CProgressDlg _pProgressDlg;

	_pProgressDlg.DoModal();

}

BOOL CHerkulexDlg::Herkulex_IDScan(int iMotor_ID)
{
	BOOL bResult = FALSE;

	ex_bFlag_EEPReadAckCallback = false;

	//Herkulex ID Scan...
	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	nPacketLength = set_eep_read_cmd(szSendBuffer, iMotor_ID, EEP_MODEL_NO_1);
	//nPacketLength = set_eep_map_read_cmd(szSendBuffer, iMotor_ID, EEP_MODEL_NO_1, 60);
	
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	//Sleep(10);
	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	//nPacketLength = set_ram_read_cmd(szSendBuffer, iMotor_ID, RAM_ID, 60);
	nPacketLength = set_ram_map_read_cmd(szSendBuffer, iMotor_ID, RAM_ID, 73);
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);
	Sleep(10);


	bResult = TRUE;
	return bResult;
}


void CHerkulexDlg::OnLvnItemchangedListId(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	*pResult = 0;
}

void CHerkulexDlg::Init_ID_ListCtrlCols(void)
{
	CRect rect;
	m_listctl_ID.GetClientRect(&rect);

	double nColInterval = rect.Width() / 10.0;

	m_listctl_ID.InsertColumn(0, _T("ID"), LVCFMT_CENTER, (int)(nColInterval * 3.0));
	m_listctl_ID.InsertColumn(1, _T("Model"), LVCFMT_CENTER, (int)(nColInterval * 7.0));

}

void CHerkulexDlg::Init_InsertItem_ID(int iID, CString strModelName, bool bOK)
{
	// Use the LV_ITEM structure to insert the items
	CString strID, strModel_Part;
	LVITEM lvi;

	int nItem = m_listctl_ID.GetItemCount();

	//리스트 업데이트를 위한 그리기//
	m_iSelectList_ID = nItem;

	lvi.iItem = nItem;
	lvi.mask = LVIF_IMAGE | LVIF_TEXT;

	// Set subitem 1
	(bOK == 1) ? lvi.iImage = 0 : lvi.iImage = 2;

	strID.Format("%2d", iID);
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strID);
	m_listctl_ID.InsertItem(&lvi);

	lvi.mask = LVIF_TEXT;
	// Set subitem 2
	lvi.iSubItem = 1;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strModelName);
	m_listctl_ID.SetItem(&lvi);

	int nCount = m_listctl_ID.GetItemCount();
	if (nCount > 0)
		m_listctl_ID.EnsureVisible(nCount - 1, TRUE);
}


void CHerkulexDlg::InsertItem_ID(int iID, int iModel1, int iModel2, bool bOK)
{
	// Use the LV_ITEM structure to insert the items
	CString strID, strModel1, strModel2, strModel_Part;
	//LVITEM lvi;

	int nItem = m_listctl_ID.GetItemCount();
	
	//리스트 업데이트를 위한 그리기//
	m_iSelectList_ID = nItem;

	lvi_list.iItem = nItem;
	lvi_list.mask = LVIF_IMAGE | LVIF_TEXT;

	(bOK == 1) ? lvi_list.iImage = 0 : lvi_list.iImage = 2;
	// Set subitem 1
	strID.Format("%2d", iID);
	lvi_list.iSubItem = 0;
	lvi_list.pszText = (LPTSTR)(LPCTSTR)(strID);
	m_listctl_ID.InsertItem(&lvi_list);


	lvi_list.mask = LVIF_TEXT;
	// Set subitem 2
	strModel1.Format("%02d", iModel1);
	strModel2.Format("%02d", iModel2);
	strModel_Part = _T("DRS-") + strModel1 + strModel2;
	lvi_list.iSubItem = 1;
	lvi_list.pszText = (LPTSTR)(LPCTSTR)(strModel_Part);
	m_listctl_ID.SetItem(&lvi_list);

	//레지스트리에 검색된 Herkulex 정보쓰기
	WriteDataToRegistry(strModel_Part, iID, nItem);

	int nCount = m_listctl_ID.GetItemCount();
	if (nCount > 0)
		m_listctl_ID.EnsureVisible(nCount - 1, TRUE);
}

void CHerkulexDlg::OnNMClickListId(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
	int index = pNMView->iItem;

	//리스트 업데이트를 위한 그리기//
	m_iSelectList_ID = index;
	CString strID, strModel;
	strID = m_listctl_ID.GetItemText(index, 0);
	strModel = m_listctl_ID.GetItemText(index, 1);
	writeMessageBox(("DRS_Model: " + strModel), BLACK);


	//UI Data Update//
	m_imotor_ID = atoi(strID);
	if (strModel == "DRS-0101")
	{
		m_cmdModel.SetCurSel(0);
		ex_DRS_Model_Num = 0;
		_rtGraph->SetRanges(-1024.0, 1024.0);
		GetDlgItem(IDC_TEMPER)->SetWindowTextA(_T("ºC"));
		GetDlgItem(IDC_M_BJOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_M_BJOG)->ShowWindow(0);
		GetDlgItem(IDC_M_BJOG2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M_BJOG2)->ShowWindow(0);
		GetDlgItem(IDC_MS)->EnableWindow(FALSE);
		GetDlgItem(IDC_MS)->ShowWindow(0);
		GetDlgItem(IDC_MI)->EnableWindow(FALSE);
		GetDlgItem(IDC_MI)->ShowWindow(0);
	}
	else if (strModel == "DRS-0102")
	{
		m_cmdModel.SetCurSel(1);
		ex_DRS_Model_Num = 1;
		_rtGraph->SetRanges(-1024.0, 1024.0);
		GetDlgItem(IDC_TEMPER)->SetWindowTextA(_T("ºC"));
		GetDlgItem(IDC_M_BJOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_M_BJOG)->ShowWindow(0);
		GetDlgItem(IDC_M_BJOG2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M_BJOG2)->ShowWindow(0);
		GetDlgItem(IDC_MS)->EnableWindow(FALSE);
		GetDlgItem(IDC_MS)->ShowWindow(0);
		GetDlgItem(IDC_MI)->EnableWindow(FALSE);
		GetDlgItem(IDC_MI)->ShowWindow(0);
	}
	else if (strModel == "DRS-0201")
	{
		m_cmdModel.SetCurSel(2);
		ex_DRS_Model_Num = 2;
		_rtGraph->SetRanges(-1024.0, 1024.0);
		GetDlgItem(IDC_TEMPER)->SetWindowTextA(_T("ºC"));
		GetDlgItem(IDC_M_BJOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_M_BJOG)->ShowWindow(0);
		GetDlgItem(IDC_M_BJOG2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M_BJOG2)->ShowWindow(0);
		GetDlgItem(IDC_MS)->EnableWindow(FALSE);
		GetDlgItem(IDC_MS)->ShowWindow(0);
		GetDlgItem(IDC_MI)->EnableWindow(FALSE);
		GetDlgItem(IDC_MI)->ShowWindow(0);
	}
	//////////////New HerkuleX////////////////////////
	else if (strModel == "DRS-0301")
	{
		m_cmdModel.SetCurSel(3);
		ex_DRS_Model_Num = 3;
		_rtGraph->SetRanges(-1024.0, 1024.0);
		GetDlgItem(IDC_TEMPER)->SetWindowTextA(_T("ºC"));
		GetDlgItem(IDC_M_BJOG)->EnableWindow(TRUE);
		GetDlgItem(IDC_M_BJOG)->ShowWindow(1);
		GetDlgItem(IDC_M_BJOG2)->EnableWindow(TRUE);
		GetDlgItem(IDC_M_BJOG2)->ShowWindow(1);
		GetDlgItem(IDC_MS)->EnableWindow(TRUE);
		GetDlgItem(IDC_MS)->ShowWindow(1);
		GetDlgItem(IDC_MI)->EnableWindow(TRUE);
		GetDlgItem(IDC_MI)->ShowWindow(1);
	}
	else if (strModel == "DRS-0302")
	{
		m_cmdModel.SetCurSel(4);
		ex_DRS_Model_Num = 4;
		_rtGraph->SetRanges(-1024.0, 1024.0);
		GetDlgItem(IDC_TEMPER)->SetWindowTextA(_T("ºC"));
		GetDlgItem(IDC_M_BJOG)->EnableWindow(TRUE);
		GetDlgItem(IDC_M_BJOG)->ShowWindow(1);
		GetDlgItem(IDC_M_BJOG2)->EnableWindow(TRUE);
		GetDlgItem(IDC_M_BJOG2)->ShowWindow(1);
		GetDlgItem(IDC_MS)->EnableWindow(TRUE);
		GetDlgItem(IDC_MS)->ShowWindow(1);
		GetDlgItem(IDC_MI)->EnableWindow(TRUE);
		GetDlgItem(IDC_MI)->ShowWindow(1);
	}
	else if (strModel == "DRS-0303")
	{
		m_cmdModel.SetCurSel(5);
		ex_DRS_Model_Num = 5;
		_rtGraph->SetRanges(-1024.0, 1024.0);
		GetDlgItem(IDC_TEMPER)->SetWindowTextA(_T("ºC"));
		GetDlgItem(IDC_M_BJOG)->EnableWindow(TRUE);
		GetDlgItem(IDC_M_BJOG)->ShowWindow(1);
		GetDlgItem(IDC_M_BJOG2)->EnableWindow(TRUE);
		GetDlgItem(IDC_M_BJOG2)->ShowWindow(1);
		GetDlgItem(IDC_MS)->EnableWindow(TRUE);
		GetDlgItem(IDC_MS)->ShowWindow(1);
		GetDlgItem(IDC_MI)->EnableWindow(TRUE);
		GetDlgItem(IDC_MI)->ShowWindow(1);
	}
	//////////////////////////////////////////////////
	else if (strModel == "DRS-0401")
	{
		m_cmdModel.SetCurSel(6);
		ex_DRS_Model_Num = 6;
		_rtGraph->SetRanges(-2048.0, 2048.0);
		GetDlgItem(IDC_TEMPER)->SetWindowTextA(_T("ºC"));
		GetDlgItem(IDC_M_BJOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_M_BJOG)->ShowWindow(0);
		GetDlgItem(IDC_M_BJOG2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M_BJOG2)->ShowWindow(0);
		GetDlgItem(IDC_MS)->EnableWindow(FALSE);
		GetDlgItem(IDC_MS)->ShowWindow(0);
		GetDlgItem(IDC_MI)->EnableWindow(FALSE);
		GetDlgItem(IDC_MI)->ShowWindow(0);
	}
	else if (strModel == "DRS-0402")
	{
		m_cmdModel.SetCurSel(7);
		ex_DRS_Model_Num = 7;
		_rtGraph->SetRanges(9903.0, 22865.0);
		GetDlgItem(IDC_TEMPER)->SetWindowTextA(_T("ºC"));
		GetDlgItem(IDC_M_BJOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_M_BJOG)->ShowWindow(0);
		GetDlgItem(IDC_M_BJOG2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M_BJOG2)->ShowWindow(0);
		GetDlgItem(IDC_MS)->EnableWindow(FALSE);
		GetDlgItem(IDC_MS)->ShowWindow(0);
		GetDlgItem(IDC_MI)->EnableWindow(FALSE);
		GetDlgItem(IDC_MI)->ShowWindow(0);
	}
	else if (strModel == "DRS-0601")
	{
		m_cmdModel.SetCurSel(8);
		ex_DRS_Model_Num = 8;
		_rtGraph->SetRanges(-2048.0, 2048.0);
		GetDlgItem(IDC_TEMPER)->SetWindowTextA(_T("ºC"));
		GetDlgItem(IDC_M_BJOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_M_BJOG)->ShowWindow(0);
		GetDlgItem(IDC_M_BJOG2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M_BJOG2)->ShowWindow(0);
		GetDlgItem(IDC_MS)->EnableWindow(FALSE);
		GetDlgItem(IDC_MS)->ShowWindow(0);
		GetDlgItem(IDC_MI)->EnableWindow(FALSE);
		GetDlgItem(IDC_MI)->ShowWindow(0);
	}
	else if (strModel == "DRS-0602")
	{
		m_cmdModel.SetCurSel(9);
		ex_DRS_Model_Num = 9;
		_rtGraph->SetRanges(9903.0, 22865.0);
		GetDlgItem(IDC_M_BJOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_M_BJOG)->ShowWindow(0);
		GetDlgItem(IDC_M_BJOG2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M_BJOG2)->ShowWindow(0);
		GetDlgItem(IDC_MS)->EnableWindow(FALSE);
		GetDlgItem(IDC_MS)->ShowWindow(0);
		GetDlgItem(IDC_MI)->EnableWindow(FALSE);
		GetDlgItem(IDC_MI)->ShowWindow(0);
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		m_iSlider_Data = m_sliderCtrl.GetPos();

		CString strTemp;
		strTemp.Format("%d", m_iSlider_Data);
		GetDlgItem(IDC_EDIT5)->SetWindowText(strTemp);
	*/
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	

	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	//Read
	//nPacketLength = set_ram_read_cmd(szSendBuffer, m_imotor_ID, RAM_MIN_POSITION, sizeof(szIDs));
	nPacketLength = set_ram_map_read_cmd(szSendBuffer, m_imotor_ID, RAM_MIN_POSITION, sizeof(szIDs));
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);
	Sleep(10);
	//nPacketLength = set_ram_read_cmd(szSendBuffer, m_imotor_ID, RAM_MAX_POSITION, sizeof(szIDs));
	nPacketLength = set_ram_map_read_cmd(szSendBuffer, m_imotor_ID, RAM_MAX_POSITION, sizeof(szIDs));
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);
	Sleep(10);


	UpdateData(false);

	*pResult = 0;
}


void CHerkulexDlg::RAM_RegisterData_Write(unsigned int iAddr, unsigned int cData)
{
	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	
	switch (iAddr)
	{
	case 0:
		RAM[m_imotor_ID - 1].ucID = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_ID, &RAM[m_imotor_ID - 1].ucID);
		break;
	case 1:
		RAM[m_imotor_ID - 1].ucAckPolicy = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_ACK_POLICY, &RAM[m_imotor_ID - 1].ucAckPolicy);
		break;
	case 2:
		RAM[m_imotor_ID - 1].ucAlarmLEDPolicy = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_ALARM_LED_POLICY, &RAM[m_imotor_ID - 1].ucAlarmLEDPolicy);
		break;
	case 3:
		RAM[m_imotor_ID - 1].ucTorquePolicy = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_TORQUE_POLICY, &RAM[m_imotor_ID - 1].ucTorquePolicy);
		break;
	case 5:
		RAM[m_imotor_ID - 1].ucMaxTemperature = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_MAX_TEMPERATURE, &RAM[m_imotor_ID - 1].ucMaxTemperature);
		break;
	case 6:
		RAM[m_imotor_ID - 1].ucMinVoltage = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_MIN_VOLTAGE, &RAM[m_imotor_ID - 1].ucMinVoltage);
		break;
	case 7:
		RAM[m_imotor_ID - 1].ucMaxVoltage = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_MAX_VOLTAGE, &RAM[m_imotor_ID - 1].ucMaxVoltage);
		break;
	case 8:
		RAM[m_imotor_ID - 1].ucAccelerationRatio = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_ACCELERATION_RATIO, &RAM[m_imotor_ID - 1].ucAccelerationRatio);
		break;
	case 9:
		RAM[m_imotor_ID - 1].ucMaxAccelerationTime = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_MAX_ACCELERATION_TIME, &RAM[m_imotor_ID - 1].ucMaxAccelerationTime);
		break;
	case 10:
		RAM[m_imotor_ID - 1].ucDeadZone = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_DEAD_ZONE, &RAM[m_imotor_ID - 1].ucDeadZone);
		break;
	case 11:
		RAM[m_imotor_ID - 1].ucSaturatorOffset = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_SATURATOR_OFFSET, &RAM[m_imotor_ID - 1].ucSaturatorOffset);
		break;
	case 12:
		RAM[m_imotor_ID - 1].usSaturatorSlope = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_SATURATOR_SLOPE, &RAM[m_imotor_ID - 1].usSaturatorSlope);
		break;
	case 14:
		RAM[m_imotor_ID - 1].cPWMOffset = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_PWM_OFFSET, &RAM[m_imotor_ID - 1].cPWMOffset);
		break;
	case 15:
		RAM[m_imotor_ID - 1].ucMinPWM = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_MIN_PWM, &RAM[m_imotor_ID - 1].ucMinPWM);
		break;
	case 16:
		RAM[m_imotor_ID - 1].usMaxPWM = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_MAX_PWM, &RAM[m_imotor_ID - 1].usMaxPWM);
		break;
	case 18:
		RAM[m_imotor_ID - 1].usOverloadPWMThreshold = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_OVERLOAD_PWM_THRESHOLD, &RAM[m_imotor_ID - 1].usOverloadPWMThreshold);
		break;
	case 20:
		RAM[m_imotor_ID - 1].usMinPosition = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_MIN_POSITION, &RAM[m_imotor_ID - 1].usMinPosition);
		break;
	case 22:
		RAM[m_imotor_ID - 1].usMaxPosition = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_MAX_POSITION, &RAM[m_imotor_ID - 1].usMaxPosition);
		break;
	case 24:
		RAM[m_imotor_ID - 1].usPositionKp = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_POSITION_KP, &RAM[m_imotor_ID - 1].usPositionKp);
		break;
	case 26:
		RAM[m_imotor_ID - 1].usPositionKd = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_POSITION_KD, &RAM[m_imotor_ID - 1].usPositionKd);
		break;
	case 28:
		RAM[m_imotor_ID - 1].usPositionKi = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_POSITION_KI, &RAM[m_imotor_ID - 1].usPositionKi);
		break;
	case 30:
		RAM[m_imotor_ID - 1].usPositionFeedforward1stGain = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_POSITION_FEEDFORWARD_1ST_GAIN, &RAM[m_imotor_ID - 1].usPositionFeedforward1stGain);
		break;
	case 32:
		RAM[m_imotor_ID - 1].usPositionFeedforward2ndGain = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_VELOCITY_KP, &RAM[m_imotor_ID - 1].usPositionFeedforward2ndGain);
		break;
	case 34:
		RAM[m_imotor_ID - 1].usVelocityKd = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_VELOCITY_KD, &RAM[m_imotor_ID - 1].usVelocityKd);
		break;
	case 36:
		RAM[m_imotor_ID - 1].usVelocityKi = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_VELOCITY_KI, &RAM[m_imotor_ID - 1].usVelocityKi);
		break;
	case 38:
		RAM[m_imotor_ID - 1].ucLEDBlinkPeriod = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_LED_BLINK_PERIOD, &RAM[m_imotor_ID - 1].ucLEDBlinkPeriod);
		break;
	case 39:
		RAM[m_imotor_ID - 1].ucADCFaultCheckPeriod = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_ADC_FAULT_CHECK_PERIOD, &RAM[m_imotor_ID - 1].ucADCFaultCheckPeriod);
		break;
	case 40:
		RAM[m_imotor_ID - 1].ucPacketGarbageCheckPeriod = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_PACKET_GARBAGE_CHECK_PERIOD, &RAM[m_imotor_ID - 1].ucPacketGarbageCheckPeriod);
		break;
	case 41:
		RAM[m_imotor_ID - 1].ucStopDetectionPeriod = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_STOP_DETECTION_PERIOD, &RAM[m_imotor_ID - 1].ucStopDetectionPeriod);
		break;
	case 42:
		RAM[m_imotor_ID - 1].ucOverloadDetectionPeriod = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_OVELOAD_DETECTION_PERIOD, &RAM[m_imotor_ID - 1].ucOverloadDetectionPeriod);
		break;
	case 43:
		RAM[m_imotor_ID - 1].ucStopThreshold = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_STOP_THRESHOLD, &RAM[m_imotor_ID - 1].ucStopThreshold);
		break;
	case 44:
		RAM[m_imotor_ID - 1].ucInpositionMargin = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_INPOSITION_MARGIN, &RAM[m_imotor_ID - 1].ucInpositionMargin);
		break;
	case 45:
		RAM[m_imotor_ID - 1].ucTurn = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_TURN, &RAM[m_imotor_ID - 1].ucTurn);
		break;
	case 46:
		RAM[m_imotor_ID - 1].cCalibrationDifference_L = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_CALIBRATION__DIFFERENCE_L, &RAM[m_imotor_ID - 1].cCalibrationDifference_L);
		break;
	case 47:
		RAM[m_imotor_ID - 1].cCalibrationDifference_H = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_CALIBRATION__DIFFERENCE_H, &RAM[m_imotor_ID - 1].cCalibrationDifference_H);
		break;
	case 52:
		RAM[m_imotor_ID - 1].ucTorqueControl = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_TORQUE_CONTROL, &RAM[m_imotor_ID - 1].ucTorqueControl);
		break;
	case 53:
		RAM[m_imotor_ID - 1].ucLEDControl = cData;
		nPacketLength = set_ram_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], RAM_LED_CONTROL, &RAM[m_imotor_ID - 1].ucLEDControl);
		break;

	default:
		AfxMessageBox("This is a read-only address !");
		break;

	}

	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);
}

void CHerkulexDlg::EEP_RegisterData_Write(unsigned int iAddr, unsigned int cData)
{
	memset(szSendBuffer, 0, sizeof(szSendBuffer));

	switch (iAddr)
	{
	case 4:
		EEP.ucBaudRate = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_BAUD_RATE, &EEP.ucBaudRate);
		break;
	case 6:
		EEP.ucID = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_ID, &EEP.ucID);
		break;
	case 7:
		EEP.ucAckPolicy = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_ACK_POLICY, &EEP.ucAckPolicy);
		break;
	case 8:
		EEP.ucAlarmLEDPolicy = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_ALARM_LED_POLICY, &EEP.ucAlarmLEDPolicy);
		break;
	case 9:
		EEP.ucTorquePolicy = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_TORQUE_POLICY, &EEP.ucTorquePolicy);
		break;
	case 11:
		EEP.ucMaxTemperature = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_MAX_TEMPERATURE, &EEP.ucMaxTemperature);
		break;
	case 12:
		EEP.ucMinVoltage = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_MIN_VOLTAGE, &EEP.ucMinVoltage);
		break;
	case 13:
		EEP.ucMaxVoltage = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_MAX_VOLTAGE, &EEP.ucMaxVoltage);
		break;
	case 14:
		EEP.ucAccelerationRatio = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_ACCELERATION_RATIO, &EEP.ucAccelerationRatio);
		break;
	case 15:
		EEP.ucMaxAccelerationTime = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_MAX_ACCELERATION_TIME, &EEP.ucMaxAccelerationTime);
		break;
	case 16:
		EEP.ucDeadZone = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_DEAD_ZONE, &EEP.ucDeadZone);
		break;
	case 17:
		EEP.ucSaturatorOffset = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_SATURATOR_OFFSET, &EEP.ucSaturatorOffset);
		break;
	case 18:
		EEP.usSaturatorSlope = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_SATURATOR_SLOPE, &EEP.usSaturatorSlope);
		break;
	case 20:
		EEP.cPWMOffset = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_PWM_OFFSET, &EEP.cPWMOffset);
		break;
	case 21:
		EEP.ucMinPWM = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_MIN_PWM, &EEP.ucMinPWM);
		break;
	case 22:
		EEP.usMaxPWM = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_MAX_PWM, &EEP.usMaxPWM);
		break;
	case 24:
		EEP.usOverloadPWMThreshold = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_OVERLOAD_PWM_THRESHOLD, &EEP.usOverloadPWMThreshold);
		break;
	case 26:
		EEP.usMinPosition = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_MIN_POSITION, &EEP.usMinPosition);
		break;
	case 28:
		EEP.usMaxPosition = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_MAX_POSITION, &EEP.usMaxPosition);
		break;
	case 30:
		EEP.usPositionKp = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_POSITION_KP, &EEP.usPositionKp);
		break;
	case 32:
		EEP.usPositionKd = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_POSITION_KD, &EEP.usPositionKd);
		break;
	case 34:
		EEP.usPositionKi = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_POSITION_KI, &EEP.usPositionKi);
		break;
	case 36:
		EEP.usPositionFeedforward1stGain = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_POSITION_FEEDFORWARD_1ST_GAIN, &EEP.usPositionFeedforward1stGain);
		break;
	case 38:
		EEP.usPositionFeedforward2ndGain = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_VELOCITY_KP, &EEP.usPositionFeedforward2ndGain); //->usVelocityKp사용
		break;
	case 40:
		EEP.usVelocityKd = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_VELOCITY_KD, &EEP.usVelocityKd);
		break;
	case 42:
		EEP.usVelocityKi = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_VELOCITY_KI, &EEP.usVelocityKi);
		break;
	case 44:
		EEP.ucLEDBlinkPeriod = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_LED_BLINK_PERIOD, &EEP.ucLEDBlinkPeriod);
		break;
	case 45:
		EEP.ucADCFaultCheckPeriod = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_ADC_FAULT_CHECK_PERIOD, &EEP.ucADCFaultCheckPeriod);
		break;
	case 46:
		EEP.ucPacketGarbageCheckPeriod = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_PACKET_GARBAGE_CHECK_PERIOD, &EEP.ucPacketGarbageCheckPeriod);
		break;
	case 47:
		EEP.ucStopDetectionPeriod = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_STOP_DETECTION_PERIOD, &EEP.ucStopDetectionPeriod);
		break;
	case 48:
		EEP.ucOverloadDetectionPeriod = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_OVELOAD_DETECTION_PERIOD, &EEP.ucOverloadDetectionPeriod);
		break;
	case 49:
		EEP.ucStopThreshold = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_STOP_THRESHOLD, &EEP.ucStopThreshold);
		break;
	case 50:
		EEP.ucInpositionMargin = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_INPOSITION_MARGIN, &EEP.ucInpositionMargin);
		break;
	case 51:
		EEP.ucReserved5 = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_RESERVED_5, &EEP.ucReserved5);
		break;
	case 52:
		EEP.cCalibrationDifference_L = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_RESERVED_6, &EEP.cCalibrationDifference_L);
		break;
	case 53:
		EEP.cCalibrationDifference_H = cData;
		nPacketLength = set_eep_write_cmd(szSendBuffer, szIDs[m_imotor_ID - 1], EEP_CALIBRATION_DIFFERENCE, &EEP.cCalibrationDifference_H);
		break;

	default:
		AfxMessageBox("This is a read-only address !");
		break;

	}

	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

}



void CHerkulexDlg::OnBnClickedButton13()
{
	//Packet Viewer
	UpdateData();

	if (!ex_bFlagModal_View) //중복 실행을 막는다.
	{
		delete _pViewDlg;

		//동적 메모리 할당을 한 후에
		_pViewDlg = new CPacketView(this);
		//모달리스 대화상자를 생성하고
		_pViewDlg->Create(IDD_PACKETVIEW, this);
		//화면에 나타내기 위해 ShowWindow() 함수를 호출
		_pViewDlg->ShowWindow(SW_SHOW);

		ex_bFlagModal_View = true;
	}

}

BOOL CHerkulexDlg::Send_PrintData(unsigned char *cBuffer, int iLength)
{
	bool bResult = false;

	if (ex_bFlag_WriteView)
	{
		CString strTemp, strPacket_temp;

		for (int i = 0; i < iLength; i++)
		{
			strTemp.Format("%02x", cBuffer[i]);
			strPacket_temp += (strTemp + _T(" "));
		}

		//Packst View에 전달...
		_pViewDlg->writeMessageBox2(_T("[Send]: "), strPacket_temp, BLUE);
	}

	bResult = true;
	return bResult;
}

void CHerkulexDlg::Send_PrintData2(CString strPacket)
{
	int iSize = 0;
	const char* str2;
	str2 = (CStringA)strPacket;

	iSize = strPacket.GetLength();

		CString strTemp, strPacket_temp;

		for (int i = 0; i < iSize; i++)
		{
			strTemp.Format("%c", str2[i]);
			if(i%2)
				strPacket_temp += (strTemp + _T(" "));
			else
				strPacket_temp += strTemp;
			
		}

		//Packst View에 전달...
		_pViewDlg->writeMessageBox2(_T("[Manual Send]: "), strPacket_temp, GRAY);
}


BOOL CHerkulexDlg::Read_PrintData(unsigned char *cBuffer, int iLength)
{
	bool bResult = false;

	if (ex_bFlag_ReadView)
	{
		CString strTemp, strPacket_temp;

		for (int i = 0; i < iLength; i++)
		{
			strTemp.Format("%02x", cBuffer[i]);
			strPacket_temp += (strTemp + _T(" "));
		}

		//Packst View에 전달...
		_pViewDlg->writeMessageBox2(_T("[Read]: "), strPacket_temp, BLACK);

	}

	bResult = true;
	return bResult;
}

void CHerkulexDlg::OnStnClickedLogo1()
{
	//회사 홈페이지 서비스로봇 자료시 링크 이동
	ShellExecute(NULL, "open", "iexplore", "http://hovis.co.kr/guide/main_kor.html", NULL, SW_SHOW);
}


void CHerkulexDlg::OnBnClickedButton14()
{
	//모터점검 Dialog_DoModal
	UpdateData();
	//CMotorTest _pTestDlg;
	//_pTestDlg.DoModal();

	if (!ex_bFlagModal_Test) //중복 실행을 막는다.
	{
		delete _pTestDlg;

		//동적 메모리 할당을 한 후에
		_pTestDlg = new CMotorTest(this);
		//모달리스 대화상자를 생성하고
		_pTestDlg->Create(IDD_MOTORTEST, this);
		//화면에 나타내기 위해 ShowWindow() 함수를 호출
		_pTestDlg->ShowWindow(SW_SHOW);

		ex_bFlagModal_Test = true;
	}

	//ex_bFlagMainUI = false;
}

BOOL CHerkulexDlg::Position_Move(unsigned char cID, unsigned int iLED, unsigned int iPlayTime, int iTargetPos, int iJogMode, int iprofile, bool bMulti, int turn)
{
	bool bResult = false;

	m_imotor_ID = cID;

	switch (iJogMode)
	{
	case 0: //S_JOG
		// S_JOG 값 초기화
		sjogs[cID - 1].Value = 0;
		sjogs[cID - 1].Stop = 0;
		sjogs[cID - 1].LED = iLED;
		sjogs[cID - 1].NoAction = 0;
		sjogs[cID - 1].ID = szIDs[cID - 1];
		sjogs[cID - 1].InfiniteTurn = 0x00;//Position Mode
		sjogs[cID - 1].Profile = iprofile; //추가된 프로파일 모드

		//Target Command -> Count
		sjogs[cID - 1].Value = iTargetPos;

		memset(szSendBuffer, 0, sizeof(szSendBuffer));
		nPacketLength = set_s_jog_cmd(szSendBuffer, cID, iPlayTime, &sjogs[cID - 1], 1);
		break;
	case 1: //I_JOG
		// I_JOG 값 초기화
		ijogs[cID - 1].Value = 0;
		ijogs[cID - 1].Stop = 0;
		ijogs[cID - 1].LED = iLED;
		ijogs[cID - 1].NoAction = 0;
		ijogs[cID - 1].ID = szIDs[cID - 1];
		ijogs[cID - 1].InfiniteTurn = 0x00;//Position Mode
		ijogs[cID - 1].Profile = iprofile; //추가된 프로파일 모드

		//Target Command -> Count
		ijogs[cID - 1].Value = iTargetPos;

		//Play time//
		ijogs[cID - 1].PlayTime_ms = iPlayTime;

		memset(szSendBuffer, 0, sizeof(szSendBuffer));
		nPacketLength = set_i_jog_cmd(szSendBuffer, cID, &ijogs[cID - 1], 1);
		break;
	case 2: //MS_JOG
		// MS_JOG 값 초기화
		msjogs[cID - 1].Value = 0;
		msjogs[cID - 1].Stop = 0;
		msjogs[cID - 1].LED = iLED;
		msjogs[cID - 1].NoAction = 0;
		msjogs[cID - 1].ID = szIDs[cID - 1];
		msjogs[cID - 1].InfiniteTurn = 0x00;//Position Mode
		msjogs[cID - 1].Profile = iprofile; //추가된 프로파일 모드

		//Target Command -> Count
		msjogs[cID - 1].Value = iTargetPos;

		memset(szSendBuffer, 0, sizeof(szSendBuffer));
		if(bMulti)
			nPacketLength = set_ms_jog_cmd(szSendBuffer, cID, iPlayTime, &msjogs[cID - 1], 1, turn, true);
		else
			nPacketLength = set_ms_jog_cmd(szSendBuffer, cID, iPlayTime, &msjogs[cID - 1], 1, turn, false);
		
		break;
	case 3: //MI_JOG
		// MI_JOG 값 초기화
		mijogs[cID - 1].Value = 0;
		mijogs[cID - 1].Stop = 0;
		mijogs[cID - 1].LED = iLED;
		mijogs[cID - 1].NoAction = 0;
		mijogs[cID - 1].ID = szIDs[cID - 1];
		mijogs[cID - 1].InfiniteTurn = 0x00;//Position Mode
		mijogs[cID - 1].Profile = iprofile; //추가된 프로파일 모드

		//Target Command -> Count
		mijogs[cID - 1].Value = iTargetPos;
		//Play time//
		mijogs[cID - 1].PlayTime_ms = iPlayTime;

		memset(szSendBuffer, 0, sizeof(szSendBuffer));
		if(bMulti)
			nPacketLength = set_mi_jog_cmd(szSendBuffer, cID, &mijogs[cID - 1], 1, turn, true);
		else
			nPacketLength = set_mi_jog_cmd(szSendBuffer, cID, &mijogs[cID - 1], 1, turn, false);
		break;
	}

	//Send//
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	if (ex_bFlag_ViewModaless) //Packet View에 출력
		Send_PrintData(szSendBuffer, nPacketLength);


	bResult = true;
	return bResult;
}

BOOL CHerkulexDlg::Velocity_Move(unsigned char cID, unsigned int iLED, int iTargetVel, int iJogMode, int iprofile, bool bMulti)
{
	bool bResult = false;

	m_imotor_ID = cID;

	switch (iJogMode)
	{
	case 0: //S_JOG
		// S_JOG 값 초기화
		sjogs[cID - 1].Value = 0;
		sjogs[cID - 1].Stop = 0;
		sjogs[cID - 1].LED = iLED;
		sjogs[cID - 1].NoAction = 0;
		sjogs[cID - 1].ID = szIDs[cID - 1];
		sjogs[cID - 1].InfiniteTurn = 0x01;//Velocity Mode
		sjogs[cID - 1].Profile = iprofile; //추가된 프로파일 모드

		//Target Command -> Count
		sjogs[cID - 1].Value = iTargetVel;

		memset(szSendBuffer, 0, sizeof(szSendBuffer));
		nPacketLength = set_s_jog_cmd(szSendBuffer, cID, 10, &sjogs[cID - 1], 1);
		break;
	case 1: //I_JOG
		// I_JOG 값 초기화
		ijogs[cID - 1].Value = 0;
		ijogs[cID - 1].Stop = 0;
		ijogs[cID - 1].LED = iLED;
		ijogs[cID - 1].NoAction = 0;
		ijogs[cID - 1].ID = szIDs[cID - 1];
		ijogs[cID - 1].InfiniteTurn = 0x01;//Velocity Mode
		ijogs[cID - 1].Profile = iprofile; //추가된 프로파일 모드

		//Target Command -> Count
		ijogs[cID - 1].Value = iTargetVel;

		memset(szSendBuffer, 0, sizeof(szSendBuffer));
		nPacketLength = set_i_jog_cmd(szSendBuffer, cID, &ijogs[cID - 1], 1);
		break;
	case 2: //MS_JOG
		// MS_JOG 값 초기화
		msjogs[cID - 1].Value = 0;
		msjogs[cID - 1].Stop = 0;
		msjogs[cID - 1].LED = iLED;
		msjogs[cID - 1].NoAction = 0;
		msjogs[cID - 1].ID = szIDs[cID - 1];
		msjogs[cID - 1].InfiniteTurn = 0x01;//Velocity Mode
		msjogs[cID - 1].Profile = iprofile; //추가된 프로파일 모드

		//Target Command -> Count
		msjogs[cID - 1].Value = iTargetVel;

		memset(szSendBuffer, 0, sizeof(szSendBuffer));
		if (bMulti)
			nPacketLength = set_ms_jog_cmd(szSendBuffer, cID, 10, &msjogs[cID - 1], 1, 0, true);
		else
			nPacketLength = set_ms_jog_cmd(szSendBuffer, cID, 10, &msjogs[cID - 1], 1, 0, false);

		break;
	case 3: //MI_JOG
		// MI_JOG 값 초기화
		mijogs[cID - 1].Value = 0;
		mijogs[cID - 1].Stop = 0;
		mijogs[cID - 1].LED = iLED;
		mijogs[cID - 1].NoAction = 0;
		mijogs[cID - 1].ID = szIDs[cID - 1];
		mijogs[cID - 1].InfiniteTurn = 0x01;//Velocity Mode
		mijogs[cID - 1].Profile = iprofile; //추가된 프로파일 모드

		//Target Command -> Count
		mijogs[cID - 1].Value = iTargetVel;

		memset(szSendBuffer, 0, sizeof(szSendBuffer));
		if (bMulti)
		 nPacketLength = set_mi_jog_cmd(szSendBuffer, cID, &mijogs[cID - 1], 1, 0, true);
		else
			nPacketLength = set_mi_jog_cmd(szSendBuffer, cID, &mijogs[cID - 1], 1, 0, false);

		break;
	}

	//Send//
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	if (ex_bFlag_ViewModaless) //Packet View에 출력
		Send_PrintData(szSendBuffer, nPacketLength);


	bResult = true;
	return bResult;
}


void CHerkulexDlg::OnBnClickedButton15()
{
	//Multi Move Dialog _ DoModal
	UpdateData();

	//CMultiMove _pMultiDlg;
	//_pMultiDlg.DoModal();
	if (!ex_bFlagModal_MultiMove) //중복 실행을 막는다.
	{
		delete _pMultiDlg;

		//동적 메모리 할당을 한 후에
		_pMultiDlg = new CMultiMove(this);
		//모달리스 대화상자를 생성하고
		_pMultiDlg->Create(IDD_MULTIMOVE, this);
		//화면에 나타내기 위해 ShowWindow() 함수를 호출
		_pMultiDlg->ShowWindow(SW_SHOW);

		ex_bFlagModal_MultiMove = true;
	}

}

BOOL CHerkulexDlg::S_JOG_MOVE(unsigned int iPlayTime, unsigned int iTotal_Axis)
{
	bool bResult = false;

	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	nPacketLength = set_s_jog_cmd(szSendBuffer, 0xFE, iPlayTime, sjogs, iTotal_Axis);
	//Send//
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	if (ex_bFlag_ViewModaless) //Packet View에 출력
		Send_PrintData(szSendBuffer, nPacketLength);

	bResult = true;
	return bResult;
}

BOOL CHerkulexDlg::I_JOG_MOVE(unsigned int iTotal_Axis)
{
	bool bResult = false;

	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	nPacketLength = set_i_jog_cmd(szSendBuffer, 0xFE, ijogs, iTotal_Axis);
	//Send//
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	if (ex_bFlag_ViewModaless) //Packet View에 출력
		Send_PrintData(szSendBuffer, nPacketLength);


	bResult = true;
	return bResult;
}

BOOL CHerkulexDlg::MS_JOG_MOVE(unsigned int iPlayTime, unsigned int iTotal_Axis, bool bMulti, int turn)
{
	bool bResult = false;

	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	nPacketLength = set_ms_jog_cmd(szSendBuffer, 0xFE, iPlayTime, msjogs, iTotal_Axis, turn, bMulti);
	//Send//
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	if (ex_bFlag_ViewModaless) //Packet View에 출력
		Send_PrintData(szSendBuffer, nPacketLength);

	bResult = true;
	return bResult;
}

BOOL CHerkulexDlg::MI_JOG_MOVE(unsigned int iTotal_Axis, bool bMulti, int turn)
{
	bool bResult = false;

	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	nPacketLength = set_mi_jog_cmd(szSendBuffer, 0xFE, mijogs, iTotal_Axis, turn, bMulti);
	//Send//
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	if (ex_bFlag_ViewModaless) //Packet View에 출력
		Send_PrintData(szSendBuffer, nPacketLength);


	bResult = true;
	return bResult;
}

BOOL CHerkulexDlg::Status_Display() //UI 하단에 BMP이미지 Update//
{
	bool bResult = false;

	//Error Check
	for (int i = 0; i < 7; i++)
	{
		if (strErorr[i] == _T("0"))
			((CStatic *)GetDlgItem(IDC_STATUS1+i))->SetBitmap(m_bmpOff);
		else
		{
			((CStatic*)GetDlgItem(IDC_STATUS1 + i))->SetBitmap(m_bmpOn);
			bResult = true;
		}

	}
	//Detail Check//////////////////////////////////////////////////////
	//Packet Error Check Detail
	for (int j = 0; j < 4; j++)
	{
		if (strDetail[j+2] == _T("0"))
			((CStatic *)GetDlgItem(IDC_STATUS8 + j))->SetBitmap(m_bmpOff);
		else
		{
			((CStatic*)GetDlgItem(IDC_STATUS8 + j))->SetBitmap(m_bmpOn);
			bResult = true;
		}
	}

	//Moving Flag
	if (strDetail[0] == _T("0"))
		((CStatic *)GetDlgItem(IDC_STATUS12))->SetBitmap(m_bmpOff);
	else
		((CStatic *)GetDlgItem(IDC_STATUS12))->SetBitmap(m_bmpOn2);

	//Inposition Flag
	if (strDetail[1] == _T("0"))
		((CStatic *)GetDlgItem(IDC_STATUS13))->SetBitmap(m_bmpOff);
	else
		((CStatic *)GetDlgItem(IDC_STATUS13))->SetBitmap(m_bmpOn2);

	//Torque On Flag
	if (strDetail[6] == _T("0"))
	{
		((CStatic*)GetDlgItem(IDC_STATUS14))->SetBitmap(m_bmpOff);
		ex_bFlag_ServoON = false;
	}
	else
	{
		((CStatic*)GetDlgItem(IDC_STATUS14))->SetBitmap(m_bmpOn2);
		ex_bFlag_ServoON = true;
	}


	//Error에 대한 Edit Update//
	m_strErrorMargin.Format("%d", RAM[m_imotor_ID].ucInpositionMargin);
	GetDlgItem(IDC_EDIT8)->SetWindowText(m_strErrorMargin);
 
	m_strErrorPosition.Format("%d", (RAM[m_imotor_ID].usAbsolutePosition - RAM[m_imotor_ID].usAbsoluteDesiredTrajectoryPosition));
	GetDlgItem(IDC_EDIT9)->SetWindowText(m_strErrorPosition);

	//Feedback Position Update//
	m_sliderCtrl2.SetPos(RAM[m_imotor_ID].usAbsolutePosition);

	//Get Turn
	if (ex_DRS_Model_Num == 3 || ex_DRS_Model_Num == 4 || ex_DRS_Model_Num == 5)
	{
		//03시리즈의 경우....
		strTurn.Format("%d", RAM[m_imotor_ID].ucTurn);
		GetDlgItem(IDC_TURNCNT)->SetWindowText(strTurn);
	}
	else
	{
		GetDlgItem(IDC_TURNCNT)->SetWindowText(_T("0"));
	}

	return bResult;
}


void CHerkulexDlg::FactoryReset(unsigned char cID, int iID_Skip, int iBaudrate_Skip)
{
	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	nPacketLength = set_rollback_cmd(szSendBuffer, cID, iID_Skip, iBaudrate_Skip);
	//Send//
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	if (ex_bFlag_ViewModaless) //Packet View에 출력
		Send_PrintData(szSendBuffer, nPacketLength);

}

void CHerkulexDlg::Reboot(unsigned char cID)
{
	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	nPacketLength = set_reboot_cmd(szSendBuffer, cID);
	//Send//
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	if (ex_bFlag_ViewModaless) //Packet View에 출력
		Send_PrintData(szSendBuffer, nPacketLength);

}

void CHerkulexDlg::CALSET(unsigned char cID)
{
	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	nPacketLength = set_calset_cmd(szSendBuffer, cID);
	//Send//
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	if (ex_bFlag_ViewModaless) //Packet View에 출력
		Send_PrintData(szSendBuffer, nPacketLength);

}



void CHerkulexDlg::OnOK()
{
	//엔터막기


	//CDialogEx::OnOK();
}


HBRUSH CHerkulexDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_SLIDER2) //Slider bar 2번
	{
		pDC->SetBkMode(GRAY_BRUSH);
		return (HBRUSH)::GetStockObject(GRAY_BRUSH);
	}

	if (pWnd->GetDlgCtrlID() == IDC_CHECK2)
	{
		pDC->SetTextColor(GREEN);
		pDC->SetBkMode(DKGRAY_BRUSH);   // static text 배경색
		return (HBRUSH)::GetStockObject(DKGRAY_BRUSH);
	}

	if (pWnd->GetDlgCtrlID() == IDC_CHECK3)
	{
		pDC->SetTextColor(BLUE);
		pDC->SetBkMode(DKGRAY_BRUSH);   // static text 배경색
		return (HBRUSH)::GetStockObject(DKGRAY_BRUSH);
	}

	if (pWnd->GetDlgCtrlID() == IDC_CHECK4)
	{
		pDC->SetTextColor(RED);
		pDC->SetBkMode(DKGRAY_BRUSH);   // static text 배경색
		return (HBRUSH)::GetStockObject(DKGRAY_BRUSH);
	}



	// TODO:  여기서 DC의 특성을 변경합니다.
	switch (nCtlColor) 
	{
		case CTLCOLOR_DLG:   /// 다이얼로그 배경색
		{
			return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
			break;
		}
		case CTLCOLOR_BTN:  
		{
			//pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)::GetStockObject(DKGRAY_BRUSH);
		}
		case CTLCOLOR_STATIC:
		{
			pDC->SetTextColor(RGB(255, 255, 255));  // static text 글자색 변경
			pDC->SetBkMode(DKGRAY_BRUSH);   // static text 배경색
			return (HBRUSH)::GetStockObject(DKGRAY_BRUSH);
		}
	}


	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CHerkulexDlg::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

void CHerkulexDlg::Total_LoadDataFromRegistry(void)
{
	CWinApp *pApp = AfxGetApp();

	m_regedit_TotalCnt = pApp->GetProfileInt("HERKULEX", "TOTAL", 0);
	TRACE("m_regedit_TotalCnt = %d", m_regedit_TotalCnt);
}

void CHerkulexDlg::LoadDataFromRegistry(int iIndex)
{
	CWinApp *pApp = AfxGetApp();
	CString strKey;
	// Load inspection data from registry
	strKey.Format("HERKULEX\\%d", iIndex);

	m_regedit_Model_Name = pApp->GetProfileString(strKey, "MODEL", _T(""));
	m_regedit_Model_ID = pApp->GetProfileInt(strKey, "ID", 0); //int

}

void CHerkulexDlg::WriteDataToRegistry(CString strModelName, int iID, int iIndex)
{
	CWinApp *pApp = AfxGetApp();
	CString strKey;

	strKey.Format("HERKULEX\\%d", iIndex);

	pApp->WriteProfileString(strKey, "MODEL", strModelName);
	pApp->WriteProfileInt(strKey, "ID", iID);

	//Toal개수
	pApp->WriteProfileInt("HERKULEX", "TOTAL", iIndex+1);
	
}
void CHerkulexDlg::WriteDataToRegistry_Serial(CString strCOM, CString strBaudrate)
{
	CWinApp *pApp = AfxGetApp();
	
	//통신연결 정보
	pApp->WriteProfileString("HERKULEX", "COMPORT", strCOM);
	pApp->WriteProfileString("HERKULEX", "BAUDRATE", strBaudrate);

}

void CHerkulexDlg::Serial_LoadDataFromRegistry(void)
{
	CWinApp *pApp = AfxGetApp();

	m_regedit_COM = pApp->GetProfileString("HERKULEX", "COMPORT", _T(""));
	m_regedit_Baudrate = pApp->GetProfileString("HERKULEX", "BAUDRATE", _T(""));


}


void CHerkulexDlg::InitImageList(void)
{
	HIMAGELIST hList = ImageList_Create(16, 16, ILC_COLOR8 | ILC_MASK, 8, 1);
	m_lstImage.Attach(hList);

	// Load the small icons
	CBitmap bmpIcons;
	bmpIcons.LoadBitmap(IDB_LISTIMAGES);
	m_lstImage.Add(&bmpIcons, RGB(255, 0, 255));
	//bmpIcons.DeleteObject();

	// Attach them
	m_listctl_ID.SetImageList(&m_lstImage, LVSIL_SMALL);
}

void CHerkulexDlg::OnBnClickedButton18()
{
	// Herkulex 펌웨어 업데이트 기능//
	UpdateData();
	//Timer Stop//
	ex_bFlagSCAN = false;

	if (!ex_bFlagModal_Update)
	{
		delete _pFirmDlg;

		//동적 메모리 할당을 한 후에
		_pFirmDlg = new CFirmwareUpdate(this);
		//모달리스 대화상자를 생성하고
		_pFirmDlg->Create(IDD_UPDATE, this);
		//화면에 나타내기 위해 ShowWindow() 함수를 호출
		_pFirmDlg->ShowWindow(SW_SHOW);



		ex_bFlagModal_Update = true;
	}

	//CFirmwareUpdate _pFWDlg;
	//_pFWDlg.DoModal();
	
	//ex_bFlagModal_Update

}

void CHerkulexDlg::Sendpacket_Manual(CString strPacket)
{

	//Send//
	SendHexadecimalData(strPacket);

	if (ex_bFlag_ViewModaless) //Packet View에 출력
		Send_PrintData2(strPacket);

}


void CHerkulexDlg::OnBnClickedButton22()
{
	// Parameter Setting기능 Dialog_Domodal
	UpdateData();

	if (!ex_bFlagModal_Parameter) //중복 실행을 막는다.
	{
		delete _pParamDlg;
		//동적 메모리 할당을 한 후에
		_pParamDlg = new CParameterDlg(this);
		//모달리스 대화상자를 생성하고
		_pParamDlg->Create(IDD_PARAMETER, this);
		//화면에 나타내기 위해 ShowWindow() 함수를 호출
		_pParamDlg->ShowWindow(SW_SHOW);

		ex_bFlagModal_Parameter = true;
	}


}


void CHerkulexDlg::OnBnClickedButton17()
{
	// Home Position
	UpdateData();

	//Torque On Flag
	if (strDetail[6] == _T("0"))
	{
		//Servo On
		Herkulex_Servo_Enable(m_imotor_ID, 1);
	}

	switch (ex_DRS_Model_Num)
	{
		case 0: //0101
			m_iSlider_Data = 512;
			m_sliderCtrl.SetPos(m_iSlider_Data);
			break;
		case 1: //0102
			m_iSlider_Data = 512;
			m_sliderCtrl.SetPos(m_iSlider_Data);
			break;
		case 2: //0201
			m_iSlider_Data = 512;
			m_sliderCtrl.SetPos(m_iSlider_Data);
			break;
		case 3: //0301
			m_iSlider_Data = 512;
			m_sliderCtrl.SetPos(m_iSlider_Data);
			break;
		case 4: //0302
			m_iSlider_Data = 512;
			m_sliderCtrl.SetPos(m_iSlider_Data);
			break;
		case 5: //0303
			m_iSlider_Data = 512;
			m_sliderCtrl.SetPos(m_iSlider_Data);
			break;
		case 6: //0401
			m_iSlider_Data = 1024;
			m_sliderCtrl.SetPos(m_iSlider_Data);
			break;
		case 7: //0402
			m_iSlider_Data = 16384;
			m_sliderCtrl.SetPos(m_iSlider_Data);
			break;
		case 8: //0601
			m_iSlider_Data = 1024;
			m_sliderCtrl.SetPos(m_iSlider_Data);
			break;
		case 9: //0602
			m_iSlider_Data = 16384;
			m_sliderCtrl.SetPos(m_iSlider_Data);
			break;
	}


	sjogs[m_imotor_ID - 1].InfiniteTurn = 0x00;//Position Mode
	// S_JOG 값 초기화
	sjogs[m_imotor_ID - 1].Value = 0;
	sjogs[m_imotor_ID - 1].Stop = 0;
	sjogs[m_imotor_ID - 1].LED = m_iRGB_SUM;
	sjogs[m_imotor_ID - 1].NoAction = 0;
	sjogs[m_imotor_ID - 1].ID = szIDs[m_imotor_ID - 1];
	sjogs[m_imotor_ID - 1].Value = m_iSlider_Data; 

	bmoveMode = false;
	

	memset(szSendBuffer, 0, sizeof(szSendBuffer));
	//nPacketLength = set_s_jog_cmd(szSendBuffer, 0xFE, m_iSpeedTime, sjogs, m_imotor_ID); //sizeof(szIDs)
	nPacketLength = set_s_jog_cmd(szSendBuffer, m_imotor_ID, m_iSpeedTime, &sjogs[m_imotor_ID - 1], 1);
	//Send//
	m_hCommPort.WriteComm(szSendBuffer, nPacketLength);

	if (ex_bFlag_ViewModaless) //Packet View에 출력
		Send_PrintData(szSendBuffer, nPacketLength);

	CString strTemp;
	strTemp.Format("%d", m_iSlider_Data);
	GetDlgItem(IDC_EDIT5)->SetWindowText(strTemp);
}


void CHerkulexDlg::OnBnClickedButton24()
{
	m_Slider_Zoom.SetPos(1);
	_rtGraph->SetRanges(-ex_dMaxPosition, ex_dMaxPosition);

}


void CHerkulexDlg::OnBnClickedButton25()
{
	// Zoom In

}



/*
void CHerkulexDlg::OnEnChangeEdit29()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
*/


void CHerkulexDlg::OnNMCustomdrawZoom(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	*pResult = 0;
}

void CHerkulexDlg::MemorySet()
{
	memset(RAM, 0, sizeof(RAM));
	memset(&EEP, 0, sizeof(EEP));
}

void CHerkulexDlg::OnBnClickedRadio4()
{
	// Angle
	GetDlgItem(IDC_TARGET)->SetWindowText(_T("Angle(deg):"));
}


void CHerkulexDlg::OnBnClickedRadio3()
{
	// Count
	GetDlgItem(IDC_TARGET)->SetWindowText(_T("Count:"));
}

double CHerkulexDlg::dfCalcTempCenigrade(double dfResOfTherm, int iBConstant, int iR0, int iT0)//T0 : centigrade
{
	double dfCentigrade;

	if (dfResOfTherm == 0)
		dfCentigrade = 350;//max temperature
	else
	{
		dfCentigrade = (log(dfResOfTherm / iR0) + (double)iBConstant / (iT0 + 273.15)) / iBConstant;    // natural logarithm
		dfCentigrade = 1 / dfCentigrade - 273.15;
	}

	return dfCentigrade;
}