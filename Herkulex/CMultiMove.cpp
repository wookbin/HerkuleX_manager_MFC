// CMultiMove.cpp: 구현 파일
//

#include "stdafx.h"
#include "Herkulex.h"
#include "CMultiMove.h"
#include "afxdialogex.h"
#include "HerkulexDlg.h"


// CMultiMove 대화 상자
unsigned char m_szIDs[254] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
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
							  0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe };

int		m_iJOG_Type = 0;  // 0: S_JOG   1: I_JOG  2: B_JOG
int		m_iProfile_Type = 1;  // 0: 사다리꼴   1: S자 
BOOL	m_bMOVE_Type = false; // 1: Position Move   0: Velocity Move
CString m_strMoveType = _T("");

int		m_iLEDCheck[3];
int		m_iLED_SUM;
int		iSelect_IndexItem;

IMPLEMENT_DYNAMIC(CMultiMove, CDialogEx)

CMultiMove::CMultiMove(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MULTIMOVE, pParent)
	, m_rSel_JOG(0)
	, M_strID(_T("1"))
	, M_strPlayTime(_T("60"))
	, M_strTarget(_T("512"))
{

}

CMultiMove::~CMultiMove()
{
}

void CMultiMove::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MULTI, m_MultiList);
	DDX_Radio(pDX, IDC_M_S_JOG, m_rSel_JOG);
	DDX_Text(pDX, IDC_M_ID, M_strID);
	DDX_Text(pDX, IDC_M_PTIME, M_strPlayTime);
	DDX_Text(pDX, IDC_M_TARGET, M_strTarget);
	DDX_Control(pDX, IDC_COMBO_MODE, m_combo_Mode);
}


BEGIN_MESSAGE_MAP(CMultiMove, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MULTI, &CMultiMove::OnLvnItemchangedListMulti)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CMultiMove::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON10, &CMultiMove::OnBnClickedButton10)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MULTI, &CMultiMove::OnNMClickListMulti)
	ON_BN_CLICKED(IDC_MUTI_SERVO_ON, &CMultiMove::OnBnClickedMutiServoOn)
	ON_BN_CLICKED(IDC_MUTI_SERVO_OFF, &CMultiMove::OnBnClickedMutiServoOff)
	ON_BN_CLICKED(IDC_MUTI_MOVE, &CMultiMove::OnBnClickedMutiMove)
	ON_BN_CLICKED(IDC_MUTI_MOVE2, &CMultiMove::OnBnClickedMutiMove2)
	ON_BN_CLICKED(IDC_M_S_JOG, &CMultiMove::OnBnClickedMSJog)
	ON_BN_CLICKED(IDC_M_I_JOG, &CMultiMove::OnBnClickedMIJog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_MUTI_MOVE3, &CMultiMove::OnBnClickedMutiMove3)
	ON_BN_CLICKED(IDC_BUTTON23, &CMultiMove::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_M_I_JOG2, &CMultiMove::OnBnClickedMIJog2)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_MUTI_SERVO_OFF2, &CMultiMove::OnBnClickedMutiServoOff2)
	ON_BN_CLICKED(IDC_MUTI_MOVE4, &CMultiMove::OnBnClickedMutiMove4)
END_MESSAGE_MAP()


// CMultiMove 메시지 처리기


void CMultiMove::OnLvnItemchangedListMulti(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


*pResult = 0;
}


BOOL CMultiMove::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CFont	m_fontList;

	//List Control Setting//
	InitListCtrlCols();
	m_fontList.CreatePointFont(100, _T("Arial"));
	m_MultiList.SetFont(&m_fontList);
	m_MultiList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	//시작 시 S_JOG Mode로 Radio button 강제Check//
	CButton* pButton = (CButton*)GetDlgItem(IDC_M_S_JOG);
	pButton->SetCheck(true);

	//시작 시 사다리 프로파일 Mode로 Radio button 강제Check//
	CButton* pButton2 = (CButton*)GetDlgItem(IDC_PROFILE222);
	pButton2->SetCheck(true);
	
	m_combo_Mode.SetCurSel(0);

	GetDlgItem(IDC_MUTI_MOVE3)->EnableWindow(FALSE);
	GetDlgItem(IDC_MUTI_MOVE4)->EnableWindow(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMultiMove::InitListCtrlCols() //List control 컬럼 그리기//
{
	CRect rect;
	m_MultiList.GetClientRect(&rect);

	double nColInterval = rect.Width() / 10.0;

	m_MultiList.InsertColumn(0, _T("ID"), LVCFMT_CENTER, (int)nColInterval * 1.5);
	m_MultiList.InsertColumn(1, _T("Mode"), LVCFMT_CENTER, (int)(nColInterval * 2.0));
	m_MultiList.InsertColumn(2, _T("Paly_Time"), LVCFMT_CENTER, (int)(nColInterval * 2.5));
	m_MultiList.InsertColumn(3, _T("Target"), LVCFMT_CENTER, (int)(nColInterval * 2.0));
	m_MultiList.InsertColumn(4, _T("LED"), LVCFMT_CENTER, (int)(nColInterval * 2.0));

}


void CMultiMove::InsertItem(CString strID, bool bMode, CString strPaly_Time, CString strTarget, int iLED)
{
	// Use the LV_ITEM structure to insert the items
	CString strLED_Data;
	CString strMode;
	LVITEM lvi;

	int nItem = m_MultiList.GetItemCount();

	lvi.iItem = nItem;
	lvi.mask = LVIF_IMAGE | LVIF_TEXT;

	// Set subitem 1
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strID);
	m_MultiList.InsertItem(&lvi);

	// Set subitem 2
	lvi.iSubItem = 1;
	if (bMode)
		strMode = _T("Position");
	else
		strMode = _T("Velocity");

	lvi.pszText = (LPTSTR)(LPCTSTR)(strMode);
	m_MultiList.SetItem(&lvi);

	// Set subitem 3
	lvi.iSubItem = 2;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strPaly_Time);
	m_MultiList.SetItem(&lvi);

	// Set subitem 4
	lvi.iSubItem = 3;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strTarget);
	m_MultiList.SetItem(&lvi);

	// Set subitem 5
	strLED_Data.Format("%d", iLED);
	lvi.iSubItem = 4;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strLED_Data);
	m_MultiList.SetItem(&lvi);


	int nCount = m_MultiList.GetItemCount();
	if (nCount > 0)
		m_MultiList.EnsureVisible(nCount - 1, TRUE);
}


void CMultiMove::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ex_bFlagModal_MultiMove = false;

	DestroyWindow();
}





void CMultiMove::OnBnClickedButton1()
{
	UpdateData();

	//Select Jog Type
	if (IsDlgButtonChecked(IDC_M_S_JOG))
		m_iJOG_Type = 0; //S_JOG
	if(IsDlgButtonChecked(IDC_M_I_JOG))
		m_iJOG_Type = 1; //I_JOG
	if (IsDlgButtonChecked(IDC_M_I_JOG2))
		m_iJOG_Type = 2; //B_JOG

	//Select Profile Mode
	if (IsDlgButtonChecked(IDC_PROFILE111))
		m_iProfile_Type = 1; //S자
	else
		m_iProfile_Type = 0; //사다리꼴


	//Select Move Type 
	int iIndex = m_combo_Mode.GetCurSel();
	if (!iIndex)
		m_bMOVE_Type = true;
	else
		m_bMOVE_Type = false;

	//LED Setting
	int m_iRGB_Color[3] = { 0, };
	//LED Check Box관련//
	CButton *pChecBox1 = (CButton*)GetDlgItem(IDC_CHECK_LED1);
	CButton *pChecBox2 = (CButton*)GetDlgItem(IDC_CHECK_LED2);
	CButton *pChecBox3 = (CButton*)GetDlgItem(IDC_CHECK_LED3);

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

	//RGB색상 정보 Update//
	m_iLED_SUM = m_iRGB_Color[0] + m_iRGB_Color[1] + m_iRGB_Color[2];
	//Add Item//
	InsertItem(M_strID, m_bMOVE_Type, M_strPlayTime, M_strTarget, m_iLED_SUM);
}


void CMultiMove::OnBnClickedButton10()
{
	// Modify Item
	UpdateData();

	CString strMode;
	CString strLED_Data;
	//index별 Item수정//
	m_MultiList.SetItem(iSelect_IndexItem, 0, LVIF_TEXT, M_strID, NULL, NULL, NULL, NULL); //ID
	//Select Move Type 
	int iIndex = m_combo_Mode.GetCurSel();
	if (!iIndex)
		m_bMOVE_Type = true;
	else
		m_bMOVE_Type = false;

	if (m_bMOVE_Type)
		strMode = _T("Position");
	else
		strMode = _T("Velocity");

	m_MultiList.SetItem(iSelect_IndexItem, 1, LVIF_TEXT, strMode, NULL, NULL, NULL, NULL); //Mode Type
	m_MultiList.SetItem(iSelect_IndexItem, 2, LVIF_TEXT, M_strPlayTime, NULL, NULL, NULL, NULL); //Play Time
	m_MultiList.SetItem(iSelect_IndexItem, 3, LVIF_TEXT, M_strTarget, NULL, NULL, NULL, NULL); //Target
	
	//LED Setting																						 
	int m_iRGB_Color[3] = { 0, };
	//LED Check Box관련//
	CButton *pChecBox1 = (CButton*)GetDlgItem(IDC_CHECK_LED1);
	CButton *pChecBox2 = (CButton*)GetDlgItem(IDC_CHECK_LED2);
	CButton *pChecBox3 = (CButton*)GetDlgItem(IDC_CHECK_LED3);

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

	//RGB색상 정보 Update//
	m_iLED_SUM = m_iRGB_Color[0] + m_iRGB_Color[1] + m_iRGB_Color[2];

	strLED_Data.Format("%d", m_iLED_SUM);
	m_MultiList.SetItem(iSelect_IndexItem, 4, LVIF_TEXT, strLED_Data, NULL, NULL, NULL, NULL); //LED

}



void CMultiMove::OnNMClickListMulti(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	NM_LISTVIEW *pNMVIEW = (NM_LISTVIEW*)pNMHDR;
	iSelect_IndexItem = pNMVIEW->iItem;

	
	GetDlgItem(IDC_M_ID)->SetWindowText(m_MultiList.GetItemText(iSelect_IndexItem, 0));


	*pResult = 0;
}


void CMultiMove::OnBnClickedMutiServoOn()
{
	//Servo On
	UpdateData();
	CString strID;
	int iID = 0;

	int iTotal_Item = m_MultiList.GetItemCount();
	//TRACE("iTotal_Item = %d", iTotal_Item);

	for (int i = 0; i < iTotal_Item; i++)
	{
		strID = m_MultiList.GetItemText(i, 0);
		iID = atoi(strID);

		((CHerkulexDlg *)GetParent())->Herkulex_Servo_Enable(iID, 1);
	}
	
}


void CMultiMove::OnBnClickedMutiServoOff()
{
	//Servo Off
	UpdateData();
	CString strID;
	int iID = 0;

	int iTotal_Item = m_MultiList.GetItemCount();
	//TRACE("iTotal_Item = %d", iTotal_Item);

	for (int i = 0; i < iTotal_Item; i++)
	{
		strID = m_MultiList.GetItemText(i, 0);
		iID = atoi(strID);

		((CHerkulexDlg *)GetParent())->Herkulex_Servo_Enable(iID, 2);
	}
	
}

void CMultiMove::OnBnClickedMutiServoOff2()
{
	// Add Brake On
	UpdateData();
	CString strID;
	int iID = 0;

	int iTotal_Item = m_MultiList.GetItemCount();
	//TRACE("iTotal_Item = %d", iTotal_Item);

	for (int i = 0; i < iTotal_Item; i++)
	{
		strID = m_MultiList.GetItemText(i, 0);
		iID = atoi(strID);

		((CHerkulexDlg*)GetParent())->Herkulex_Servo_Enable(iID, 0);
	}
}


void CMultiMove::OnBnClickedMutiMove()
{
	// Multi S_JOG Move
	UpdateData();

	bool m_bMoveType = false;
	int iPlayTime = 0;
	int iID = 0;

	//Item의 Total개수 가져오기
	int iTotal_Item = m_MultiList.GetItemCount();

	for (int i = 0; i < iTotal_Item; i++)
	{
		//Item의 ID가져오기
		CString strID = m_MultiList.GetItemText(i, 0);
		iID = atoi(strID);
		//Item의 Move Type가져오기
		CString strType = m_MultiList.GetItemText(i, 1);
		if (strType == _T("Position"))
		{
			//Position
			((CHerkulexDlg *)GetParent())->sjogs[iID - 1].InfiniteTurn = 0x00;//Position Mode
		}
		else
		{
			//Velocity
			((CHerkulexDlg *)GetParent())->sjogs[iID - 1].InfiniteTurn = 0x01;//Velocity Mode
		}

		//Play Time가져오기
		CString strPlayTime = m_MultiList.GetItemText(i, 2);
		iPlayTime = atoi(strPlayTime);


		//Target값 가져오기
		CString strTarget = m_MultiList.GetItemText(i, 3);
		int iTarget = atoi(strTarget);
		((CHerkulexDlg *)GetParent())->sjogs[iID - 1].Value = iTarget;

		//LED값 가져오기
		CString strLED = m_MultiList.GetItemText(i, 4);
		int iLED = atoi(strLED);
		((CHerkulexDlg *)GetParent())->sjogs[iID - 1].LED = iLED;

		// S_JOG 값 초기화
		((CHerkulexDlg *)GetParent())->sjogs[iID - 1].Stop = 0;
		((CHerkulexDlg *)GetParent())->sjogs[iID - 1].NoAction = 0;
		((CHerkulexDlg *)GetParent())->sjogs[iID - 1].ID = m_szIDs[iID - 1];

		if (IsDlgButtonChecked(IDC_PROFILE111))
		{
			((CHerkulexDlg *)GetParent())->sjogs[iID - 1].Profile = 1; //S자
		}
		else
		{
			((CHerkulexDlg *)GetParent())->sjogs[iID - 1].Profile = 0; //사다리꼴
		}

	}

	//S_JOG Move//
	((CHerkulexDlg *)GetParent())->S_JOG_MOVE(iPlayTime, iID); //마지막 iID값을 이용하여 S_Jog의 총 개수 호출

}


void CMultiMove::OnBnClickedMutiMove2()
{
	// Multi I_JOG MOVE
	UpdateData();

	bool m_bMoveType = false;
	int iPlayTime = 0;
	int iID = 0;

	//Item의 Total개수 가져오기
	int iTotal_Item = m_MultiList.GetItemCount();

	for (int i = 0; i < iTotal_Item; i++)
	{
		//Item의 ID가져오기
		CString strID = m_MultiList.GetItemText(i, 0);
		iID = atoi(strID);
		//Item의 Move Type가져오기
		CString strType = m_MultiList.GetItemText(i, 1);
		if (strType == _T("Position"))
		{
			//Position
			((CHerkulexDlg *)GetParent())->ijogs[iID - 1].InfiniteTurn = 0x00;//Position Mode
		}
		else
		{
			//Velocity
			((CHerkulexDlg *)GetParent())->ijogs[iID - 1].InfiniteTurn = 0x01;//Velocity Mode
		}

		//Play Time가져오기
		CString strPlayTime = m_MultiList.GetItemText(i, 2);
		iPlayTime = atoi(strPlayTime);
		((CHerkulexDlg *)GetParent())->ijogs[iID - 1].PlayTime_ms = iPlayTime;


		//Target값 가져오기
		CString strTarget = m_MultiList.GetItemText(i, 3);
		int iTarget = atoi(strTarget);
		((CHerkulexDlg *)GetParent())->ijogs[iID - 1].Value = iTarget;

		//LED값 가져오기
		CString strLED = m_MultiList.GetItemText(i, 4);
		int iLED = atoi(strLED);
		((CHerkulexDlg *)GetParent())->ijogs[iID - 1].LED = iLED;


		// I_JOG 값 초기화
		((CHerkulexDlg *)GetParent())->ijogs[iID - 1].Stop = 0;
		((CHerkulexDlg *)GetParent())->ijogs[iID - 1].NoAction = 0;
		((CHerkulexDlg *)GetParent())->ijogs[iID - 1].ID = m_szIDs[iID - 1];

		if (IsDlgButtonChecked(IDC_PROFILE111))
		{
			((CHerkulexDlg *)GetParent())->ijogs[iID - 1].Profile = 1; //S자
		}
		else
		{
			((CHerkulexDlg *)GetParent())->ijogs[iID - 1].Profile = 0; //사다리꼴
		}

	}

	//I_JOG Move//
	((CHerkulexDlg *)GetParent())->I_JOG_MOVE(iID); //마지막 iID값을 이용하여 I_JOG의 총 개수 호출//

}


void CMultiMove::OnBnClickedMSJog()
{
	// S_JOG Select
	GetDlgItem(IDC_MUTI_MOVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_MUTI_MOVE2)->EnableWindow(FALSE);
	GetDlgItem(IDC_MUTI_MOVE3)->EnableWindow(FALSE);
}


void CMultiMove::OnBnClickedMIJog()
{
	// I_JOG Select
	GetDlgItem(IDC_MUTI_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MUTI_MOVE2)->EnableWindow(TRUE);
	GetDlgItem(IDC_MUTI_MOVE3)->EnableWindow(FALSE);

}

void CMultiMove::OnBnClickedMIJog2()
{
	// B_JOG Select
	GetDlgItem(IDC_MUTI_MOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MUTI_MOVE2)->EnableWindow(FALSE);
	GetDlgItem(IDC_MUTI_MOVE3)->EnableWindow(TRUE);
}


void CMultiMove::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.


}


HBRUSH CMultiMove::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_CHECK_LED1)
	{
		pDC->SetTextColor(GREEN);
		pDC->SetBkMode(DKGRAY_BRUSH);   // static text 배경색
		return (HBRUSH)::GetStockObject(DKGRAY_BRUSH);
	}

	if (pWnd->GetDlgCtrlID() == IDC_CHECK_LED2)
	{
		pDC->SetTextColor(BLUE);
		pDC->SetBkMode(DKGRAY_BRUSH);   // static text 배경색
		return (HBRUSH)::GetStockObject(DKGRAY_BRUSH);
	}

	if (pWnd->GetDlgCtrlID() == IDC_CHECK_LED3)
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


void CMultiMove::OnBnClickedMutiMove3()
{
	// Multi MS_JOG MOVE
	UpdateData();

	bool m_bMoveType = false;
	int iPlayTime = 0;
	int iID = 0;

	//Item의 Total개수 가져오기
	int iTotal_Item = m_MultiList.GetItemCount();

	for (int i = 0; i < iTotal_Item; i++)
	{
		//Item의 ID가져오기
		CString strID = m_MultiList.GetItemText(i, 0);
		iID = atoi(strID);
		//Item의 Move Type가져오기
		CString strType = m_MultiList.GetItemText(i, 1);
		if (strType == _T("Position"))
		{
			//Position
			((CHerkulexDlg*)GetParent())->msjogs[iID - 1].InfiniteTurn = 0x00;//Position Mode
		}
		else
		{
			//Velocity
			((CHerkulexDlg*)GetParent())->msjogs[iID - 1].InfiniteTurn = 0x01;//Velocity Mode
		}

		//Play Time가져오기
		CString strPlayTime = m_MultiList.GetItemText(i, 2);
		iPlayTime = atoi(strPlayTime);


		//Target값 가져오기
		CString strTarget = m_MultiList.GetItemText(i, 3);
		int iTarget = atoi(strTarget);
		((CHerkulexDlg*)GetParent())->msjogs[iID - 1].Value = iTarget;
		//LED값 가져오기
		CString strLED = m_MultiList.GetItemText(i, 4);
		int iLED = atoi(strLED);
		((CHerkulexDlg*)GetParent())->msjogs[iID - 1].LED = iLED;
		// S_JOG 값 초기화
		((CHerkulexDlg*)GetParent())->msjogs[iID - 1].Stop = 0;
		((CHerkulexDlg*)GetParent())->msjogs[iID - 1].NoAction = 0;
		((CHerkulexDlg*)GetParent())->msjogs[iID - 1].ID = m_szIDs[iID - 1];

		if (IsDlgButtonChecked(IDC_PROFILE111))
		{
			((CHerkulexDlg*)GetParent())->msjogs[iID - 1].Profile = 1; //S자
		}
		else
		{
			((CHerkulexDlg*)GetParent())->msjogs[iID - 1].Profile = 0; //사다리꼴
		}

	}

	//MS_JOG Move//
	if(IsDlgButtonChecked(IDC_MS3))
		((CHerkulexDlg*)GetParent())->MS_JOG_MOVE(iPlayTime, iID, true, 0); //마지막 iID값을 이용하여 S_Jog의 총 개수 호출
	else
		((CHerkulexDlg*)GetParent())->MS_JOG_MOVE(iPlayTime, iID, false, 0); //마지막 iID값을 이용하여 S_Jog의 총 개수 호출

}

void CMultiMove::OnBnClickedMutiMove4()
{
	// Multi MI_JOG MOVE
	UpdateData();

	bool m_bMoveType = false;
	int iPlayTime = 0;
	int iID = 0;

	//Item의 Total개수 가져오기
	int iTotal_Item = m_MultiList.GetItemCount();

	for (int i = 0; i < iTotal_Item; i++)
	{
		//Item의 ID가져오기
		CString strID = m_MultiList.GetItemText(i, 0);
		iID = atoi(strID);
		//Item의 Move Type가져오기
		CString strType = m_MultiList.GetItemText(i, 1);
		if (strType == _T("Position"))
		{
			//Position
			((CHerkulexDlg*)GetParent())->mijogs[iID - 1].InfiniteTurn = 0x00;//Position Mode
		}
		else
		{
			//Velocity
			((CHerkulexDlg*)GetParent())->mijogs[iID - 1].InfiniteTurn = 0x01;//Velocity Mode
		}

		//Play Time가져오기
		CString strPlayTime = m_MultiList.GetItemText(i, 2);
		iPlayTime = atoi(strPlayTime);
		((CHerkulexDlg*)GetParent())->mijogs[iID - 1].PlayTime_ms = iPlayTime;


		//Target값 가져오기
		CString strTarget = m_MultiList.GetItemText(i, 3);
		int iTarget = atoi(strTarget);
		((CHerkulexDlg*)GetParent())->mijogs[iID - 1].Value = iTarget;

		//LED값 가져오기
		CString strLED = m_MultiList.GetItemText(i, 4);
		int iLED = atoi(strLED);
		((CHerkulexDlg*)GetParent())->mijogs[iID - 1].LED = iLED;


		// I_JOG 값 초기화
		((CHerkulexDlg*)GetParent())->mijogs[iID - 1].Stop = 0;
		((CHerkulexDlg*)GetParent())->mijogs[iID - 1].NoAction = 0;
		((CHerkulexDlg*)GetParent())->mijogs[iID - 1].ID = m_szIDs[iID - 1];

		if (IsDlgButtonChecked(IDC_PROFILE111))
		{
			((CHerkulexDlg*)GetParent())->mijogs[iID - 1].Profile = 1; //S자
		}
		else
		{
			((CHerkulexDlg*)GetParent())->mijogs[iID - 1].Profile = 0; //사다리꼴
		}

	}

	//I_JOG Move//
	if (IsDlgButtonChecked(IDC_MI3))
		((CHerkulexDlg*)GetParent())->MI_JOG_MOVE(iID, true, 0); //마지막 iID값을 이용하여 I_JOG의 총 개수 호출//
	else
		((CHerkulexDlg*)GetParent())->MI_JOG_MOVE(iID, false, 0); //마지막 iID값을 이용하여 I_JOG의 총 개수 호출//

}


void CMultiMove::OnBnClickedButton23()
{
	//아이템지우기
	UpdateData();

	m_MultiList.DeleteItem(iSelect_IndexItem);

}



void CMultiMove::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//delete this;
}


void CMultiMove::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	OnDestroy();

	CDialogEx::OnClose();
}



