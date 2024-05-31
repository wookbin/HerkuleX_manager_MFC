// CFirmwareUpdate.cpp: 구현 파일
//
#pragma warning(disable:4996)

#include "stdafx.h"
#include "Herkulex.h"
#include "CFirmwareUpdate.h"
#include "afxdialogex.h"
#include "HerkulexDlg.h"



CString strFirmwear_Ver1 = _T("");
CString strFirmwear_Ver2 = _T("");
CString strVersion = _T("");
CString strPeriod = _T(".");



// CFirmwareUpdate 대화 상자

IMPLEMENT_DYNAMIC(CFirmwareUpdate, CDialogEx)

CFirmwareUpdate::CFirmwareUpdate(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPDATE, pParent)
{
	ex_bFlagSCAN = false;
}

CFirmwareUpdate::~CFirmwareUpdate()
{
	

}

void CFirmwareUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_BMPBUTTON_Open);
	DDX_Control(pDX, IDC_BUTTON2, m_BMPBUTTON_Update);
	DDX_Control(pDX, IDC_BUTTON4, m_BMPBUTTON_Status);
	DDX_Control(pDX, IDC_BUTTON20, m_BMPBUTTON_Status2);
	DDX_Control(pDX, IDC_BUTTON21, m_BMPBUTTON_Status3);
	DDX_Control(pDX, IDC_MSGLIST3, m_ctrlMsgList3);
}


BEGIN_MESSAGE_MAP(CFirmwareUpdate, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON3, &CFirmwareUpdate::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CFirmwareUpdate::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFirmwareUpdate::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CFirmwareUpdate::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CFirmwareUpdate::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON19, &CFirmwareUpdate::OnBnClickedButton19)
	ON_LBN_SELCHANGE(IDC_MSGLIST3, &CFirmwareUpdate::OnLbnSelchangeMsglist3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON4, &CFirmwareUpdate::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON20, &CFirmwareUpdate::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON21, &CFirmwareUpdate::OnBnClickedButton21)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CFirmwareUpdate 메시지 처리기


void CFirmwareUpdate::OnOK()
{
	//Enter Key무시

}


BOOL CFirmwareUpdate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_bmp_BG_FW.LoadBitmap(IDB_BG_FW);

	m_BMPBUTTON_Open.LoadBitmaps(IDB_BOOT_OPEN, NULL, NULL, NULL);
	m_BMPBUTTON_Open.SizeToContent();

	m_BMPBUTTON_Update.LoadBitmaps(IDB_UPDATE, NULL, NULL, NULL);
	m_BMPBUTTON_Update.SizeToContent();

	//GetDlgItem(IDC_BUTTON4)->ShowWindow(FALSE);
	//GetDlgItem(IDC_BUTTON20)->ShowWindow(FALSE);
	//GetDlgItem(IDC_BUTTON21)->ShowWindow(FALSE);

	m_hexPath = _T("");
	m_hexFileName = _T("");

	((CHerkulexDlg *)GetParent())->EEP_Register_ReadALL();

	SetTimer(1024, 100, NULL);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CFirmwareUpdate::GetFirmwear_Ver(CString strVer1, CString strVer2)
{
	char szHex1[16];
	char szHex2[16];
	
	int iVer1 = atoi(strVer1);
	int iVer2 = atoi(strVer2);

	_ltoa(iVer1, szHex1, 16);
	_ltoa(iVer2, szHex2, 16);

	strFirmwear_Ver1 = szHex1;
	strFirmwear_Ver2 = szHex2;


	strVersion = strFirmwear_Ver1 + strPeriod + strFirmwear_Ver2;
	
	GetDlgItem(IDC_FW_VER)->SetWindowText(strVersion);
}


void CFirmwareUpdate::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CHerkulexDlg *)GetParent())->EEP_Register_ReadALL();

	GetFirmwear_Ver(ex_strVersion1, ex_strVersion2);
}


void CFirmwareUpdate::OnBnClickedButton1()
{
	//View
	writeMessageBox3(_T("File Open"), BLACK);


	// Hex file open
	CFileDialog dlg(TRUE, _T("bin"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("bin File(*.bin)|*.bin|"));
	if (IDOK == dlg.DoModal())
	{
		m_hexPath = dlg.GetPathName();
		m_hexFileName = dlg.GetFileName();

		Invalidate(FALSE);

		////Open OK후에 이미지 변환//
		m_BMPBUTTON_Open.LoadBitmaps(IDB_BOOT_OPEN2, NULL, NULL, NULL);
		m_BMPBUTTON_Open.SizeToContent();

	
	}



}


void CFirmwareUpdate::OnBnClickedButton2()
{
	// Firmwear Update Go//
	m_BMPBUTTON_Update.LoadBitmaps(IDB_UPDATE2, NULL, NULL, NULL);
	m_BMPBUTTON_Update.SizeToContent();

	ex_bFlagYmodem_Mode = true;

	writeMessageBox3(_T("Packet 1 Send"), BLACK);

	CString strPacket = _T("1");
	((CHerkulexDlg*)GetParent())->SendASCIIData(strPacket);

}



void CFirmwareUpdate::OnBnClickedButton5()
{
	GetDlgItem(IDC_BUTTON4)->ShowWindow(TRUE);
	// TEST1
	//m_BMPBUTTON_Status.LoadBitmaps(IDB_REBOOT, NULL, NULL, NULL);
	//m_BMPBUTTON_Status.SizeToContent();
}


void CFirmwareUpdate::OnBnClickedButton6()
{
	GetDlgItem(IDC_BUTTON20)->ShowWindow(TRUE);
	// TEST2
	//m_BMPBUTTON_Status2.LoadBitmaps(IDB_BOOTLOADER, NULL, NULL, NULL);
	//m_BMPBUTTON_Status2.SizeToContent();
}


void CFirmwareUpdate::OnBnClickedButton19()
{
	GetDlgItem(IDC_BUTTON21)->ShowWindow(TRUE);
	// TEST3
	//m_BMPBUTTON_Status3.LoadBitmaps(IDB_FUSING, NULL, NULL, NULL);
	//m_BMPBUTTON_Status3.SizeToContent();
}


/////////List Box////////
void CFirmwareUpdate::writeMessageBox3(CString strMsg, COLORREF crText)
{
	m_ctrlMsgList3.AddString(strMsg, crText);

	int nCount = m_ctrlMsgList3.GetCount();
	if (nCount > 0)
		m_ctrlMsgList3.SetCurSel(nCount - 1);
}

void CFirmwareUpdate::OnLbnSelchangeMsglist3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CFirmwareUpdate::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1024)
	{
		//Timer Loop _ 100ms


	}


	CDialogEx::OnTimer(nIDEvent);
}


void CFirmwareUpdate::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	writeMessageBox3(_T("Rebooting"), BLUE);

	// Rebooting
	((CHerkulexDlg*)GetParent())->Reboot(((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].ucID);

}


void CFirmwareUpdate::OnBnClickedButton20()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CFirmwareUpdate::OnBnClickedButton21()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strPacket = _T("A");
	((CHerkulexDlg*)GetParent())->SendASCIIData(strPacket);
}


void CFirmwareUpdate::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ex_bFlagSCAN = true;
	ex_bFlagYmodem_Mode = false;
	ex_bFlagModal_Update = false;

}



