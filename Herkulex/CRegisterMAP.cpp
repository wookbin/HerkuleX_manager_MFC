// CRegisterMAP.cpp: 구현 파일
//

#include "stdafx.h"
#include "Herkulex.h"
#include "CRegisterMAP.h"
#include "afxdialogex.h"

#include "herkulexlib.h"
#include "HerkulexDlg.h"


CButton *pCheckBox_ID;
CButton *pCheckBox_Baud;
// CRegisterMAP 대화 상자

IMPLEMENT_DYNAMIC(CRegisterMAP, CDialogEx)

CRegisterMAP::CRegisterMAP(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGISTERMAP, pParent)
{

}

CRegisterMAP::~CRegisterMAP()
{
	
}

void CRegisterMAP::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EEPMAP, m_EEPMAP_List);
	DDX_Control(pDX, IDC_RAMMAP, m_RAMMAP_List);
}


BEGIN_MESSAGE_MAP(CRegisterMAP, CDialogEx)
	ON_WM_TIMER()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_EEPMAP, &CRegisterMAP::OnLvnItemchangedEepmap)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_RAMMAP, &CRegisterMAP::OnLvnItemchangedRammap)
	ON_BN_CLICKED(IDC_BUTTON10, &CRegisterMAP::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON1, &CRegisterMAP::OnBnClickedButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_RAMMAP, &CRegisterMAP::OnNMDblclkRammap)
	ON_NOTIFY(NM_DBLCLK, IDC_EEPMAP, &CRegisterMAP::OnNMDblclkEepmap)
	ON_BN_CLICKED(IDC_BUTTON2, &CRegisterMAP::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_ROLLBACK, &CRegisterMAP::OnBnClickedRollback)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_EEPMAP, &CRegisterMAP::OnNMCustomdrawEepmap)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_RAMMAP, &CRegisterMAP::OnNMCustomdrawRammap)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ROLLBACK2, &CRegisterMAP::OnBnClickedRollback2)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, &CRegisterMAP::OnBnClickedCancel)
END_MESSAGE_MAP()


// CRegisterMAP 메시지 처리기


void CRegisterMAP::OnTimer(UINT_PTR nIDEvent)
{
	//Timer 구간//



	CDialogEx::OnTimer(nIDEvent);
}


BOOL CRegisterMAP::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	InitListCtrlCols();

	CFont	m_font_EEP, m_font_RAM;

	m_font_EEP.CreatePointFont(120, _T("Arial"));
	m_EEPMAP_List.SetFont(&m_font_EEP);
	m_EEPMAP_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_font_RAM.CreatePointFont(120, _T("Arial"));
	m_RAMMAP_List.SetFont(&m_font_RAM);
	m_RAMMAP_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	//EditBox 숨기기//
	GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
	GetDlgItem(IDC_EDIT2)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);


	((CHerkulexDlg *)GetParent())->RAM_Register_ReadALL();
	Sleep(300);
	((CHerkulexDlg *)GetParent())->EEP_Register_ReadALL();

	pCheckBox_ID = (CButton*)GetDlgItem(IDC_SKIP1);
	pCheckBox_Baud = (CButton*)GetDlgItem(IDC_SKIP2);
	
	pCheckBox_ID->SetCheck(true);
	pCheckBox_Baud->SetCheck(true);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CRegisterMAP::OnLvnItemchangedEepmap(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	*pResult = 0;
}


void CRegisterMAP::OnLvnItemchangedRammap(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	*pResult = 0;
}

void CRegisterMAP::InitListCtrlCols(void) //List control 컬럼 그리기//
{
	CRect rect, rect2;
	m_EEPMAP_List.GetClientRect(&rect);
	m_RAMMAP_List.GetClientRect(&rect2);

	double nColInterval = rect.Width() / 10.0;
	double nColInterval2 = rect2.Width() / 10.0;

	m_EEPMAP_List.InsertColumn(0, _T("Addr"), LVCFMT_CENTER, (int)nColInterval * 1.0);
	m_EEPMAP_List.InsertColumn(1, _T("Byte"), LVCFMT_CENTER, (int)(nColInterval * 0.9));
	m_EEPMAP_List.InsertColumn(2, _T("Description"), LVCFMT_LEFT, (int)(nColInterval * 4.9));
	m_EEPMAP_List.InsertColumn(3, _T("DEC"), LVCFMT_CENTER, (int)(nColInterval * 1.5));
	m_EEPMAP_List.InsertColumn(4, _T("HEX"), LVCFMT_CENTER, (int)(nColInterval * 1.5));

	m_RAMMAP_List.InsertColumn(0, _T("Addr"), LVCFMT_CENTER, (int)nColInterval * 1.0);
	m_RAMMAP_List.InsertColumn(1, _T("Byte"), LVCFMT_CENTER, (int)(nColInterval * 0.9));
	m_RAMMAP_List.InsertColumn(2, _T("Description"), LVCFMT_LEFT, (int)(nColInterval * 4.9));
	m_RAMMAP_List.InsertColumn(3, _T("DEC"), LVCFMT_CENTER, (int)(nColInterval * 1.5));
	m_RAMMAP_List.InsertColumn(4, _T("HEX"), LVCFMT_CENTER, (int)(nColInterval * 1.5));

}


void CRegisterMAP::InsertItem_RAM(int iAddr, int iValue, CString strDescription, int iData)
{
	// Use the LV_ITEM structure to insert the items
	CString strAddr, strValue, strData;
	LVITEM lvi;

	int nItem = m_RAMMAP_List.GetItemCount();

	lvi.iItem = nItem;
	lvi.mask = LVIF_IMAGE | LVIF_TEXT;

	// Set subitem 1
	strAddr.Format("%2d", iAddr);
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strAddr);
	m_RAMMAP_List.InsertItem(&lvi);

	// Set subitem 2
	strValue.Format("%2d", iValue);
	lvi.iSubItem = 1;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strValue);
	m_RAMMAP_List.SetItem(&lvi);

	// Set subitem 3
	lvi.iSubItem = 2;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strDescription);
	m_RAMMAP_List.SetItem(&lvi);

	// Set subitem 4
	strData.Format("%2d", iData);
	lvi.iSubItem = 3;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strData);
	m_RAMMAP_List.SetItem(&lvi);

	// Set subitem 5
	strData.Format("%02x", iData);
	lvi.iSubItem = 4;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strData);
	m_RAMMAP_List.SetItem(&lvi);


	int nCount = m_RAMMAP_List.GetItemCount();
	if (nCount > 0)
		m_RAMMAP_List.EnsureVisible(nCount - 1, TRUE);
}

void CRegisterMAP::InsertItem_EEP(int iAddr, int iValue, CString strDescription, int iData)
{
	// Use the LV_ITEM structure to insert the items
	CString strAddr, strValue, strData;
	LVITEM lvi;

	int nItem = m_EEPMAP_List.GetItemCount();

	lvi.iItem = nItem;
	lvi.mask = LVIF_IMAGE | LVIF_TEXT;

	// Set subitem 1
	strAddr.Format("%2d", iAddr);
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strAddr);
	m_EEPMAP_List.InsertItem(&lvi);

	// Set subitem 2
	strValue.Format("%2d", iValue);
	lvi.iSubItem = 1;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strValue);
	m_EEPMAP_List.SetItem(&lvi);

	// Set subitem 3
	lvi.iSubItem = 2;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strDescription);
	m_EEPMAP_List.SetItem(&lvi);

	// Set subitem 4
	strData.Format("%2d", iData);
	lvi.iSubItem = 3;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strData);
	m_EEPMAP_List.SetItem(&lvi);

	// Set subitem 5
	strData.Format("%02x", iData);
	lvi.iSubItem = 4;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strData);
	m_EEPMAP_List.SetItem(&lvi);


	int nCount = m_EEPMAP_List.GetItemCount();
	if (nCount > 0)
		m_EEPMAP_List.EnsureVisible(nCount - 1, TRUE);
}


void CRegisterMAP::OnBnClickedButton10()
{
	SetRedraw(FALSE);
	//Item All Clear//
	m_RAMMAP_List.DeleteAllItems();
	SetRedraw(TRUE);

	if (!ex_bFlag_Connect)
	{
		((CHerkulexDlg*)GetParent())->MemorySet();
		return;
	}

	// RAM Register MAP Read
	((CHerkulexDlg *)GetParent())->RAM_Register_ReadALL();
	Sleep(300);


	//List Control -> Insert Item//
	InsertItem_RAM(0, 1, "ID", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucID);
	InsertItem_RAM(1, 1, "AckPolicy", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucAckPolicy);
	InsertItem_RAM(2, 1, "AlarmLEDPolicy", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucAlarmLEDPolicy);
	InsertItem_RAM(3, 1, "TorquePolicy", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucTorquePolicy);
	InsertItem_RAM(4, 1, "Reserved", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucReserved2);
	InsertItem_RAM(5, 1, "MaxTemperature", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMaxTemperature);
	InsertItem_RAM(6, 1, "MinVoltage", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMinVoltage);
	InsertItem_RAM(7, 1, "MaxVoltage", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMaxVoltage);
	InsertItem_RAM(8, 1, "AccelerationRatio", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucAccelerationRatio);
	InsertItem_RAM(9, 1, "MaxAccelerationTime", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMaxAccelerationTime);
	InsertItem_RAM(10, 1, "DeadZone", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucDeadZone);
	InsertItem_RAM(11, 1, "SaturatorOffset", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucSaturatorOffset);
	InsertItem_RAM(12, 2, "SaturatorSlope", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usSaturatorSlope);
	InsertItem_RAM(14, 1, "PWMOffset", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].cPWMOffset);
	InsertItem_RAM(15, 1, "MinPWM", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMinPWM);
	InsertItem_RAM(16, 2, "MaxPWM", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usMaxPWM);
	InsertItem_RAM(18, 2, "OverloadPWMThreshold", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usOverloadPWMThreshold);
	InsertItem_RAM(20, 2, "MinPosition", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usMinPosition);
	InsertItem_RAM(22, 2, "MaxPosition", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usMaxPosition);
	InsertItem_RAM(24, 2, "PositionKp", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionKp);
	InsertItem_RAM(26, 2, "PositionKd", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionKd);
	InsertItem_RAM(28, 2, "PositionKi", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionKi);
	InsertItem_RAM(30, 2, "PositionFeedforward1stGain", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionFeedforward1stGain);

	if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 03)
	{
		InsertItem_RAM(32, 2, "VelocityKp", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usPositionFeedforward2ndGain);
		InsertItem_RAM(34, 2, "VelocityKd", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usVelocityKd);
		InsertItem_RAM(36, 2, "VelocityKi", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usVelocityKi);
	}
	else if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 04)
	{
		InsertItem_RAM(32, 2, "PositionFeedforward2ndGain", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usPositionFeedforward2ndGain);
		InsertItem_RAM(34, 2, "VelocityKp", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usVelocityKd);
		InsertItem_RAM(36, 2, "VelocityKi", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usVelocityKi);
	}
	else if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 06)
	{
		InsertItem_RAM(32, 2, "PositionFeedforward2ndGain", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usPositionFeedforward2ndGain);
		InsertItem_RAM(34, 2, "VelocityKp", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usVelocityKd);
		InsertItem_RAM(36, 2, "VelocityKi", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usVelocityKi);
	}
	else
	{
		InsertItem_RAM(32, 2, "PositionFeedforward2ndGain", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usPositionFeedforward2ndGain);
		InsertItem_RAM(34, 2, "Reserved", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usVelocityKd);
		InsertItem_RAM(36, 2, "Reserved", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usVelocityKi);
	}
	
	InsertItem_RAM(38, 1, "LEDBlinkPeriod", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucLEDBlinkPeriod);
	InsertItem_RAM(39, 1, "ADCFaultCheckPeriod", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucADCFaultCheckPeriod);
	InsertItem_RAM(40, 1, "PacketGarbageCheckPeriod", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucPacketGarbageCheckPeriod);
	InsertItem_RAM(41, 1, "StopDetectionPeriod", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucStopDetectionPeriod);
	InsertItem_RAM(42, 1, "OverloadDetectionPeriod", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucOverloadDetectionPeriod);
	InsertItem_RAM(43, 1, "StopThreshold", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucStopThreshold);
	InsertItem_RAM(44, 1, "InpositionMargin", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucInpositionMargin);

	if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 03)
	{
		InsertItem_RAM(45, 1, "Turn Count", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].ucTurn);
		InsertItem_RAM(46, 1, "CalibrationDifference(L)", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].cCalibrationDifference_L);
		InsertItem_RAM(47, 1, "CalibrationDifference(H)", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].cCalibrationDifference_H);
	}
	else if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 04)
	{
		InsertItem_RAM(45, 1, "Reserved", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].ucTurn);
		InsertItem_RAM(46, 1, "CalibrationDifference(L)", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].cCalibrationDifference_L);
		InsertItem_RAM(47, 1, "CalibrationDifference(H)", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].cCalibrationDifference_H);
	}
	else if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 06)
	{
		InsertItem_RAM(45, 1, "Reserved", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].ucTurn);
		InsertItem_RAM(46, 1, "CalibrationDifference(L)", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].cCalibrationDifference_L);
		InsertItem_RAM(47, 1, "CalibrationDifference(H)", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].cCalibrationDifference_H);
	}
	else
	{
		InsertItem_RAM(45, 1, "Reserved", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].ucTurn);
		InsertItem_RAM(46, 1, "Reserved", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].cCalibrationDifference_L);
		InsertItem_RAM(47, 1, "CalibrationDifference", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].cCalibrationDifference_H);
	}

	InsertItem_RAM(48, 1, "StatusError", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucStatusError);
	InsertItem_RAM(49, 1, "StatusDetail", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucStatusDetail);

	//2019.08.19_전류 측정 기능 추가로 인한 수정
	if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 03)
	{
		InsertItem_RAM(50, 1, "CurrentLimit_1", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].ucReserved7);
		InsertItem_RAM(51, 1, "CurrentLimit_2", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].ucReserved8);
	}
	else  if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 04)
	{
		InsertItem_RAM(50, 1, "Aux 1", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].ucReserved7);
		InsertItem_RAM(51, 1, "Reserved", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].ucReserved8);
	}
	else  if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 06)
	{
		InsertItem_RAM(50, 1, "Aux 1", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].ucReserved7);
		InsertItem_RAM(51, 1, "Reserved", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].ucReserved8);
	}
	else
	{
		InsertItem_RAM(50, 1, "Reserved", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].ucReserved7);
		InsertItem_RAM(51, 1, "Reserved", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].ucReserved8);
	}

	InsertItem_RAM(52, 1, "TorqueControl", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucTorqueControl);
	InsertItem_RAM(53, 1, "LEDControl", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucLEDControl);
	InsertItem_RAM(54, 1, "Voltage", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucVoltage);
	InsertItem_RAM(55, 1, "Temperature", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucTemperature);
	InsertItem_RAM(56, 1, "CurrentControlMode", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucCurrentControlMode);
	InsertItem_RAM(57, 1, "Tick", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucTick);

	//Model별로 값이 다름...

	switch (ex_DRS_Model_Num)
	{
		case 0: //0101
			InsertItem_RAM(58, 2, "CalibratedPosition", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usCalibratedPosition & 0x1FFF);
			break;
		case 1: //0102
			InsertItem_RAM(58, 2, "CalibratedPosition", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usCalibratedPosition & 0x7FFF);
			break;
		case 2: //0201
			InsertItem_RAM(58, 2, "CalibratedPosition", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usCalibratedPosition & 0x1FFF);
			break;
		case 3: //0301
			InsertItem_RAM(58, 2, "CalibratedPosition", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usCalibratedPosition);
			break;
		case 4: //0302
			InsertItem_RAM(58, 2, "CalibratedPosition", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usCalibratedPosition);
			break;
		case 5: //0303
			InsertItem_RAM(58, 2, "CalibratedPosition", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usCalibratedPosition);
			break;
		case 6: //0401
			InsertItem_RAM(58, 2, "CalibratedPosition", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usCalibratedPosition & 0x7FFF);
			break;
		case 7: //0402
			InsertItem_RAM(58, 2, "CalibratedPosition", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usCalibratedPosition & 0x7FFF);
			break;
		case 8: //0601
			InsertItem_RAM(58, 2, "CalibratedPosition", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usCalibratedPosition & 0x7FFF);
			break;
		case 9: //0602
			InsertItem_RAM(58, 2, "CalibratedPosition", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].usCalibratedPosition & 0x7FFF);
			break;
	}

	InsertItem_RAM(60, 2, "AbsolutePosition", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usAbsolutePosition);
	InsertItem_RAM(62, 2, "DifferentialPosition", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].sDifferentialPosition);
	InsertItem_RAM(64, 2, "PWM", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPWM);
	InsertItem_RAM(66, 2, "Reserved", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usReserved9);
	InsertItem_RAM(68, 2, "AbsoluteGoalPosition", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usAbsoluteGoalPosition);
	InsertItem_RAM(70, 2, "AbsoluteDesiredTrajectoryPosition", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usAbsoluteDesiredTrajectoryPosition);
	InsertItem_RAM(72, 2, "DesiredVelocity", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].sDesiredVelocity);

	//List 상단으로 포커스 강제 이동
	m_RAMMAP_List.EnsureVisible(0, FALSE);
	m_RAMMAP_List.SetFocus();
}


void CRegisterMAP::OnBnClickedButton1()
{
	SetRedraw(FALSE);
	//Item All Clear//
	m_EEPMAP_List.DeleteAllItems();
	SetRedraw(TRUE);

	if (!ex_bFlag_Connect)
	{
		((CHerkulexDlg*)GetParent())->MemorySet();
		return;
	}


	// EEP Register MAP Read
	((CHerkulexDlg *)GetParent())->EEP_Register_ReadALL();
	Sleep(300);

	//List Control -> Insert Item//  
	InsertItem_EEP(0, 1, "Model No1", ((CHerkulexDlg *)GetParent())->EEP.ucModelNo1);
	InsertItem_EEP(1, 1, "Model No2", ((CHerkulexDlg *)GetParent())->EEP.ucModelNo2);
	InsertItem_EEP(2, 1, "Version1", ((CHerkulexDlg *)GetParent())->EEP.ucVersion1);
	InsertItem_EEP(3, 1, "Version2", ((CHerkulexDlg *)GetParent())->EEP.ucVersion2);
	InsertItem_EEP(4, 1, "BaudRate", ((CHerkulexDlg *)GetParent())->EEP.ucBaudRate);
	InsertItem_EEP(5, 1, "Reaserved", ((CHerkulexDlg *)GetParent())->EEP.ucReaserved1);
	InsertItem_EEP(6, 1, "ID", ((CHerkulexDlg *)GetParent())->EEP.ucID);
	InsertItem_EEP(7, 1, "AckPolicy", ((CHerkulexDlg *)GetParent())->EEP.ucAckPolicy);
	InsertItem_EEP(8, 1, "AlarmLEDPolicy", ((CHerkulexDlg *)GetParent())->EEP.ucAlarmLEDPolicy);
	InsertItem_EEP(9, 1, "TorquePolicy", ((CHerkulexDlg *)GetParent())->EEP.ucTorquePolicy);
	InsertItem_EEP(10, 1, "Reserved", ((CHerkulexDlg *)GetParent())->EEP.ucReserved2);
	InsertItem_EEP(11, 1, "MaxTemperature", ((CHerkulexDlg *)GetParent())->EEP.ucMaxTemperature);
	InsertItem_EEP(12, 1, "MinVoltage", ((CHerkulexDlg *)GetParent())->EEP.ucMinVoltage);
	InsertItem_EEP(13, 1, "MaxVoltage", ((CHerkulexDlg *)GetParent())->EEP.ucMaxVoltage);
	InsertItem_EEP(14, 1, "AccelerationRatio", ((CHerkulexDlg *)GetParent())->EEP.ucAccelerationRatio);
	InsertItem_EEP(15, 1, "MaxAccelerationTime", ((CHerkulexDlg *)GetParent())->EEP.ucMaxAccelerationTime);
	InsertItem_EEP(16, 1, "DeadZone", ((CHerkulexDlg *)GetParent())->EEP.ucDeadZone);
	InsertItem_EEP(17, 1, "SaturatorOffset", ((CHerkulexDlg *)GetParent())->EEP.ucSaturatorOffset);
	InsertItem_EEP(18, 2, "SaturatorSlope", ((CHerkulexDlg *)GetParent())->EEP.usSaturatorSlope);
	InsertItem_EEP(20, 1, "PWMOffset", ((CHerkulexDlg *)GetParent())->EEP.cPWMOffset);
	InsertItem_EEP(21, 1, "MinPWM", ((CHerkulexDlg *)GetParent())->EEP.ucMinPWM);
	InsertItem_EEP(22, 2, "MaxPWM", ((CHerkulexDlg *)GetParent())->EEP.usMaxPWM);
	InsertItem_EEP(24, 2, "OverloadPWMThreshold", ((CHerkulexDlg *)GetParent())->EEP.usOverloadPWMThreshold);
	InsertItem_EEP(26, 2, "MinPosition", ((CHerkulexDlg *)GetParent())->EEP.usMinPosition);
	InsertItem_EEP(28, 2, "MaxPosition", ((CHerkulexDlg *)GetParent())->EEP.usMaxPosition);
	InsertItem_EEP(30, 2, "PositionKp", ((CHerkulexDlg *)GetParent())->EEP.usPositionKp);
	InsertItem_EEP(32, 2, "PositionKd", ((CHerkulexDlg *)GetParent())->EEP.usPositionKd);
	InsertItem_EEP(34, 2, "PositionKi", ((CHerkulexDlg *)GetParent())->EEP.usPositionKi);
	InsertItem_EEP(36, 2, "PositionFeedforward1stGain", ((CHerkulexDlg *)GetParent())->EEP.usPositionFeedforward1stGain);

	if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 03)
	{
		InsertItem_EEP(38, 2, "VelocityKp", ((CHerkulexDlg*)GetParent())->EEP.usPositionFeedforward2ndGain);
		InsertItem_EEP(40, 2, "VelocityKd", ((CHerkulexDlg*)GetParent())->EEP.usVelocityKd);
		InsertItem_EEP(42, 2, "VelocityKi", ((CHerkulexDlg*)GetParent())->EEP.usVelocityKi);
	}
	else if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 04)
	{
		InsertItem_EEP(38, 2, "PositionFeedforward2ndGain", ((CHerkulexDlg*)GetParent())->EEP.usPositionFeedforward2ndGain);
		InsertItem_EEP(40, 2, "VelocityKp", ((CHerkulexDlg*)GetParent())->EEP.usVelocityKd);
		InsertItem_EEP(42, 2, "VelocityKi", ((CHerkulexDlg*)GetParent())->EEP.usVelocityKi);
	}
	else if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 06)
	{
		InsertItem_EEP(38, 2, "PositionFeedforward2ndGain", ((CHerkulexDlg*)GetParent())->EEP.usPositionFeedforward2ndGain);
		InsertItem_EEP(40, 2, "VelocityKp", ((CHerkulexDlg*)GetParent())->EEP.usVelocityKd);
		InsertItem_EEP(42, 2, "VelocityKi", ((CHerkulexDlg*)GetParent())->EEP.usVelocityKi);
	}
	else
	{
		InsertItem_EEP(38, 2, "PositionFeedforward2ndGain", ((CHerkulexDlg*)GetParent())->EEP.usPositionFeedforward2ndGain);
		InsertItem_EEP(40, 2, "Reserved", ((CHerkulexDlg*)GetParent())->EEP.usVelocityKd);
		InsertItem_EEP(42, 2, "Reserved", ((CHerkulexDlg*)GetParent())->EEP.usVelocityKi);
	}

	InsertItem_EEP(44, 1, "LEDBlinkPeriod", ((CHerkulexDlg *)GetParent())->EEP.ucLEDBlinkPeriod);
	InsertItem_EEP(45, 1, "ADCFaultCheckPeriod", ((CHerkulexDlg *)GetParent())->EEP.ucADCFaultCheckPeriod);
	InsertItem_EEP(46, 1, "PacketGarbageCheckPeriod", ((CHerkulexDlg *)GetParent())->EEP.ucPacketGarbageCheckPeriod);
	InsertItem_EEP(47, 1, "StopDetectionPeriod", ((CHerkulexDlg *)GetParent())->EEP.ucStopDetectionPeriod);
	InsertItem_EEP(48, 1, "OverloadDetectionPeriod", ((CHerkulexDlg *)GetParent())->EEP.ucOverloadDetectionPeriod);
	InsertItem_EEP(49, 1, "StopThreshold", ((CHerkulexDlg *)GetParent())->EEP.ucStopThreshold);
	InsertItem_EEP(50, 1, "InpositionMargin", ((CHerkulexDlg *)GetParent())->EEP.ucInpositionMargin);
	
	if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 03)
	{
		InsertItem_EEP(51, 2, "CalibrationOffset(L)", ((CHerkulexDlg*)GetParent())->EEP.ucReserved5);
		InsertItem_EEP(51, 2, "CalibrationOffset(H)", ((CHerkulexDlg*)GetParent())->EEP.cCalibrationDifference_L);
		InsertItem_EEP(53, 1, "CalibrationDifference(H)", ((CHerkulexDlg*)GetParent())->EEP.cCalibrationDifference_H);
	}
	else if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 04)
	{
		InsertItem_EEP(51, 1, "Reserved", ((CHerkulexDlg*)GetParent())->EEP.ucReserved5);
		InsertItem_EEP(52, 1, "CalibrationDifference(L)", ((CHerkulexDlg*)GetParent())->EEP.cCalibrationDifference_L);
		InsertItem_EEP(53, 1, "CalibrationDifference(H)", ((CHerkulexDlg*)GetParent())->EEP.cCalibrationDifference_H);
	}
	else if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 06)
	{
		InsertItem_EEP(51, 1, "Reserved", ((CHerkulexDlg*)GetParent())->EEP.ucReserved5);
		InsertItem_EEP(52, 1, "CalibrationDifference(L)", ((CHerkulexDlg*)GetParent())->EEP.cCalibrationDifference_L);
		InsertItem_EEP(53, 1, "CalibrationDifference(H)", ((CHerkulexDlg*)GetParent())->EEP.cCalibrationDifference_H);
	}
	else
	{
		InsertItem_EEP(51, 1, "Reserved", ((CHerkulexDlg*)GetParent())->EEP.ucReserved5);
		InsertItem_EEP(52, 1, "Reserved", ((CHerkulexDlg*)GetParent())->EEP.cCalibrationDifference_L);
		InsertItem_EEP(53, 1, "CalibrationDifference", ((CHerkulexDlg*)GetParent())->EEP.cCalibrationDifference_H);
	}

	//List 상단으로 포커스 강제 이동
	m_EEPMAP_List.EnsureVisible(0, FALSE);
	m_EEPMAP_List.SetFocus();


}


void CRegisterMAP::OnNMDblclkRammap(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPNMITEMACTIVATE pNMITEM = (LPNMITEMACTIVATE)pNMHDR;

	m_iItem = pNMITEM->iItem;
	m_iSubitem = pNMITEM->iSubItem;

	if (pNMITEM->iItem != -1 && m_iSubitem > 2)
	{
		CRect rect;

		if (pNMITEM->iSubItem == 0)
		{
			m_RAMMAP_List.GetItemRect(pNMITEM->iItem, rect, LVIR_BOUNDS);
			rect.right = rect.left + m_RAMMAP_List.GetColumnWidth(0);
		}
		else
		{
			m_RAMMAP_List.GetSubItemRect(pNMITEM->iItem, pNMITEM->iSubItem, LVIR_BOUNDS, rect);
		}

		m_RAMMAP_List.ClientToScreen(rect);
		this->ScreenToClient(rect);

		GetDlgItem(IDC_EDIT1)->SetWindowText(m_RAMMAP_List.GetItemText(pNMITEM->iItem, pNMITEM->iSubItem));
		GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
		GetDlgItem(IDC_EDIT1)->SetFocus();
	}

	*pResult = 0;
}

BOOL CRegisterMAP::PreTranslateMessage(MSG* pMsg)
{
	CString m_strEdit, m_strAddr;
	CString m_strEdit2, m_strAddr2;
	int m_iAddr = 0;
	int m_iData = 0;

	if (pMsg->message == WM_KEYDOWN)
	{
		UINT nChar = pMsg->wParam;
		if (nChar == VK_RETURN)
		{
			int nFocusCtrl = GetFocus()->GetDlgCtrlID();
			if (nFocusCtrl == IDC_EDIT1)
			{
				if (nChar == VK_RETURN)
				{
					if (pMsg->hwnd == GetDlgItem(IDC_EDIT1)->GetSafeHwnd())
					{
						GetDlgItemText(IDC_EDIT1, m_strEdit);
						m_RAMMAP_List.SetItemText(m_iItem, m_iSubitem, m_strEdit);
						GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);

						m_strAddr = m_RAMMAP_List.GetItemText(m_iItem, 0);
						m_iAddr = atoi(m_strAddr);

						if (m_iSubitem == 3) //DEC
						{
							m_iData = atoi(m_strEdit);
						}
						else if(m_iSubitem == 4) //HEX
						{
							m_iData = strtol(m_strEdit, NULL, 16);
						}
						
						((CHerkulexDlg *)GetParent())->RAM_RegisterData_Write(m_iAddr, m_iData);

						if (m_iAddr == 0) //ID를 수정시 ID업데이트를 위함
							((CHerkulexDlg *)GetParent())->m_imotor_ID = m_iData;

					}
					return TRUE; 
				}
			}
			if (nFocusCtrl == IDC_EDIT2)
			{
				if (nChar == VK_RETURN)
				{
					if (pMsg->hwnd == GetDlgItem(IDC_EDIT2)->GetSafeHwnd())
					{
						GetDlgItemText(IDC_EDIT2, m_strEdit2);
						m_EEPMAP_List.SetItemText(m_iItem2, m_iSubitem2, m_strEdit2);
						GetDlgItem(IDC_EDIT2)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
						//Date의 Update구문 추가 필요...
						m_strAddr2 = m_EEPMAP_List.GetItemText(m_iItem2, 0);
						m_iAddr = atoi(m_strAddr2);

						if (m_iSubitem2 == 3) //DEC
						{
							m_iData = atoi(m_strEdit2);
						}
						else if(m_iSubitem2 == 4) //HEX
						{
							m_iData = strtol(m_strEdit2, NULL, 16);
						}

						((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(m_iAddr, m_iData);

						if (m_iAddr == 0) //ID를 수정시 ID업데이트를 위함
							((CHerkulexDlg *)GetParent())->m_imotor_ID = m_iData;

					}
					return TRUE;
				}
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CRegisterMAP::OnNMDblclkEepmap(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPNMITEMACTIVATE pNMITEM = (LPNMITEMACTIVATE)pNMHDR;

	m_iItem2 = pNMITEM->iItem;
	m_iSubitem2 = pNMITEM->iSubItem;

	if (pNMITEM->iItem != -1 && m_iSubitem2 > 2)
	{
		CRect rect;

		if (pNMITEM->iSubItem == 0)
		{
			m_EEPMAP_List.GetItemRect(pNMITEM->iItem, rect, LVIR_BOUNDS);
			rect.right = rect.left + m_EEPMAP_List.GetColumnWidth(0);
		}
		else
		{
			m_EEPMAP_List.GetSubItemRect(pNMITEM->iItem, pNMITEM->iSubItem, LVIR_BOUNDS, rect);
		}

		m_EEPMAP_List.ClientToScreen(rect);
		this->ScreenToClient(rect);

		GetDlgItem(IDC_EDIT2)->SetWindowText(m_EEPMAP_List.GetItemText(pNMITEM->iItem, pNMITEM->iSubItem));
		GetDlgItem(IDC_EDIT2)->SetWindowPos(NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
		GetDlgItem(IDC_EDIT2)->SetFocus();
	}

	*pResult = 0;
}


void CRegisterMAP::OnBnClickedButton2()
{
	// RAM Data를 EEP에 복사하기//

	// RAM Register MAP Read
	((CHerkulexDlg *)GetParent())->RAM_Register_ReadALL();
	Sleep(300);
	
	//ID
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_ID, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucID);
	Sleep(2);
	//AckPolicy
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_ACK_POLICY, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucAckPolicy);
	Sleep(2);
	//Alam LED Policy
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_ALARM_LED_POLICY, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucAlarmLEDPolicy);
	Sleep(2);
	//Torque Policy
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_TORQUE_POLICY, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucTorquePolicy);
	Sleep(2);
	//Max Temperature
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MAX_TEMPERATURE, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMaxTemperature);
	Sleep(2);
	//Min Voltage
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MIN_VOLTAGE, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMinVoltage);
	Sleep(2);
	//Max Voltage
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MAX_VOLTAGE, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMaxVoltage);
	Sleep(2);
	//Acceleration Ratio
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_ACCELERATION_RATIO, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucAccelerationRatio);
	Sleep(2);
	//Max Acceleration Time
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MAX_ACCELERATION_TIME, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMaxAccelerationTime);
	Sleep(2);
	//Dead Zone
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_DEAD_ZONE, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucDeadZone);
	Sleep(2);
	//Saturator Offset
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_SATURATOR_OFFSET, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucSaturatorOffset);
	Sleep(2);
	//Saturator Slope
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_SATURATOR_SLOPE, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usSaturatorSlope);
	Sleep(2);
	//PWM Offset
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_PWM_OFFSET, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].cPWMOffset);
	Sleep(2);
	//Min PWM
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MIN_PWM, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMinPWM);
	Sleep(2);
	//Max PWM
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MAX_PWM, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usMaxPWM);
	Sleep(2);
	//Overload PWM Threshold
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_OVERLOAD_PWM_THRESHOLD, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usOverloadPWMThreshold);
	Sleep(2);
	//Min Position
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MIN_POSITION, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usMinPosition);
	Sleep(2);
	//Max Position
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MAX_POSITION, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usMaxPosition);
	Sleep(2);
	//Position Kp
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_POSITION_KP, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionKp);
	Sleep(2);
	//Position Kd
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_POSITION_KD, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionKd);
	Sleep(2);
	//Position Ki
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_POSITION_KI, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionKi);
	Sleep(2);
	//Position Feedforward 1st Gain
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_POSITION_FEEDFORWARD_1ST_GAIN, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionFeedforward1stGain);
	Sleep(2);
	//VelocityKp
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_POSITION_FEEDFORWARD_2ND_GAIN, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionFeedforward2ndGain);
	Sleep(2);
	//VelocityKd
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_VELOCITY_KD, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usVelocityKd);
	Sleep(2);
	//VelocityKi
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_VELOCITY_KI, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usVelocityKi);
	Sleep(2);
	//LED Blink Peroid
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_LED_BLINK_PERIOD, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucLEDBlinkPeriod);
	Sleep(2);
	//ADC Fault Check
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_ADC_FAULT_CHECK_PERIOD, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucADCFaultCheckPeriod);
	Sleep(2);
	//Packet Garbage
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_PACKET_GARBAGE_CHECK_PERIOD, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucPacketGarbageCheckPeriod);
	Sleep(2);
	//Stop Detection
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_STOP_DETECTION_PERIOD, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucStopDetectionPeriod);
	Sleep(2);
	//Overload Detection
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_OVELOAD_DETECTION_PERIOD, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucOverloadDetectionPeriod);
	Sleep(2);
	//Stop Threshold
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_STOP_THRESHOLD, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucStopThreshold);
	Sleep(2);
	//Inposition Margin
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_INPOSITION_MARGIN, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucInpositionMargin);
	Sleep(2);
	//Calibration Difference
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_CALIBRATION_DIFFERENCE, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].cCalibrationDifference_H);
	Sleep(2);
	//Calibration Offset
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_RESERVED_6, ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].cCalibrationDifference_L);
}


void CRegisterMAP::OnBnClickedRollback()
{
	if (IDYES == AfxMessageBox("Initialize HerkuleX's memory?", MB_YESNO))
	{
		int Check[2];
		// OK Action  
		Check[0] = pCheckBox_ID->GetCheck();
		Check[1] = pCheckBox_Baud->GetCheck();

		// Rollback fuction
		((CHerkulexDlg *)GetParent())->FactoryReset(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucID, Check[0], Check[1]);
		AfxMessageBox("HerkuleX's memory initialization is complete ! (Please turn power off then on)");
	}
	else if (IDNO)
	{
		// No Action
		AfxMessageBox("Memory initialization of HerkuleX has been canceled.");

	}
	
}


void CRegisterMAP::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	
}


void CRegisterMAP::OnNMCustomdrawEepmap(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	NMLVCUSTOMDRAW *pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;
	int iRow;

	switch (pLVCD->nmcd.dwDrawStage)
	{
		case CDDS_PREPAINT:
			*pResult = CDRF_NOTIFYITEMDRAW;
		break;
		case CDDS_ITEMPREPAINT:
			iRow = pLVCD->nmcd.dwItemSpec; // 행을 알수있다.
			if (iRow == 0 || iRow == 1 || iRow == 2 || iRow == 3)
			{
				pLVCD->clrText = BLACK; // 텍스트 색 지정
				pLVCD->clrTextBk = GRAY; // 텍스트 배경색 지정
			}

			 if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 04)
			{
				 if (iRow == 5 || iRow == 10 || iRow == 39)
				 {
					 pLVCD->clrText = YELLOW; // 텍스트 색 지정
					 pLVCD->clrTextBk = GRAY; // 텍스트 배경색 지정
				 }
			}
			else if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 06)
			{
				 if (iRow == 5 || iRow == 10 || iRow == 39)
				 {
					 pLVCD->clrText = YELLOW; // 텍스트 색 지정
					 pLVCD->clrTextBk = GRAY; // 텍스트 배경색 지정
				 }
			}
			else
			{
				if (iRow == 5 || iRow == 10 || iRow == 30 || iRow == 31 || iRow == 39 || iRow == 40)
				{
					pLVCD->clrText = YELLOW; // 텍스트 색 지정
					pLVCD->clrTextBk = GRAY; // 텍스트 배경색 지정
				}
			}

			*pResult = CDRF_DODEFAULT;
		break;
		default:
			*pResult = CDRF_DODEFAULT;
		break;
	}
}


void CRegisterMAP::OnNMCustomdrawRammap(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	NMLVCUSTOMDRAW *pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;
	int iRow;

	switch (pLVCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		iRow = pLVCD->nmcd.dwItemSpec; // 행을 알수있다.
	
		if (iRow == 42 || iRow == 43 || iRow == 44 || iRow == 45 || iRow == 46 || iRow == 47 || iRow == 48 || iRow == 49 || iRow == 50 || iRow == 51 || iRow == 52 || iRow == 53)
		{
			pLVCD->clrText = BLACK; // 텍스트 색 지정
			pLVCD->clrTextBk = GRAY; // 텍스트 배경색 지정
		}

		if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 03)
		{
			if (iRow == 4)
			{
				pLVCD->clrText = YELLOW; // 텍스트 색 지정
				pLVCD->clrTextBk = GRAY; // 텍스트 배경색 지정
			}
		}
		else if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 04)
		{
			if (iRow == 4 || iRow == 33 || iRow == 39)
			{
				pLVCD->clrText = YELLOW; // 텍스트 색 지정
				pLVCD->clrTextBk = GRAY; // 텍스트 배경색 지정
			}
		}
		else if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 06)
		{
			if (iRow == 4 || iRow == 33 || iRow == 39)
			{
				pLVCD->clrText = YELLOW; // 텍스트 색 지정
				pLVCD->clrTextBk = GRAY; // 텍스트 배경색 지정
			}
		}
		else
		{
			if (iRow == 4 || iRow == 24 || iRow == 25 || iRow == 33 || iRow == 34 || iRow == 38 || iRow == 39)
			{
				pLVCD->clrText = YELLOW; // 텍스트 색 지정
				pLVCD->clrTextBk = GRAY; // 텍스트 배경색 지정
			}
		}
		
		*pResult = CDRF_DODEFAULT;
		break;
	default:
		*pResult = CDRF_DODEFAULT;
		break;
	}
}


HBRUSH CRegisterMAP::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

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


void CRegisterMAP::OnBnClickedRollback2()
{
	// Rebooting
	((CHerkulexDlg *)GetParent())->Reboot(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucID);
}


void CRegisterMAP::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ex_bFlagModal_Map = false;

	DestroyWindow();
}


void CRegisterMAP::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//delete this;

	//CDialogEx::PostNcDestroy();
}


void CRegisterMAP::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	ex_bFlagModal_Map = false;

	OnDestroy();


	CDialogEx::OnClose();
}


void CRegisterMAP::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnClose();

	CDialogEx::OnCancel();
}
