// CPacketView.cpp: 구현 파일
//

#include "stdafx.h"
#include "Herkulex.h"
#include "CPacketView.h"
#include "afxdialogex.h"
#include "HerkulexDlg.h"

CButton *pCheckBox_WRITE;
CButton *pCheckBox_READ;
// CPacketView 대화 상자

IMPLEMENT_DYNAMIC(CPacketView, CDialogEx)

CPacketView::CPacketView(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PACKETVIEW, pParent)
	, m_strPacket(_T(""))
{

}

CPacketView::~CPacketView()
{
	ex_bFlag_ViewModaless = false;
}

void CPacketView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSGLIST2, m_ctrlMsgList2);
	DDX_Text(pDX, IDC_MPACKET, m_strPacket);
}


BEGIN_MESSAGE_MAP(CPacketView, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CPacketView::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_MSGLIST2, &CPacketView::OnLbnSelchangeMsglist2)
	ON_BN_CLICKED(IDC_CHECK_VIEW1, &CPacketView::OnBnClickedCheckView1)
	ON_BN_CLICKED(IDC_CHECK_VIEW2, &CPacketView::OnBnClickedCheckView2)
	ON_BN_CLICKED(IDC_BUTTON2, &CPacketView::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPacketView 메시지 처리기


void CPacketView::OnBnClickedButton1()
{
	//List Box내용 초기화//
	m_ctrlMsgList2.ResetContent();

}


BOOL CPacketView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	ex_bFlag_ViewModaless = true;


	pCheckBox_WRITE = (CButton*)GetDlgItem(IDC_CHECK_VIEW1);
	pCheckBox_READ = (CButton*)GetDlgItem(IDC_CHECK_VIEW2);

	pCheckBox_WRITE->SetCheck(true);
	pCheckBox_READ->SetCheck(false);

	//쓰기보기가 기본//
	ex_bFlag_WriteView = true;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

/////////List Box////////
void CPacketView::writeMessageBox2(CString strTag, CString strMsg, COLORREF crText)
{
	strMsg = strTag + strMsg;
	m_ctrlMsgList2.AddString(strMsg, crText);

	int nCount = m_ctrlMsgList2.GetCount();

	if (nCount > 0)
		m_ctrlMsgList2.SetCurSel(nCount - 1);

	CString str;
	CSize sz;
	int dx = 0;
	CDC* pDC = m_ctrlMsgList2.GetDC();
	for (int i = 0; i < m_ctrlMsgList2.GetCount(); i++)
	{
		m_ctrlMsgList2.GetText(i, str);
		sz = pDC->GetTextExtent(str);

		if (sz.cx > dx)
			dx = sz.cx;
	}
	m_ctrlMsgList2.ReleaseDC(pDC);

	// Set the horizontal extent so every character of all strings 
	// can be scrolled to.
	m_ctrlMsgList2.SetHorizontalExtent(dx);
}



void CPacketView::OnLbnSelchangeMsglist2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CPacketView::OnBnClickedCheckView1()
{
	// 쓰기 보기
	if (pCheckBox_WRITE->GetCheck())
		ex_bFlag_WriteView = true;
	else
		ex_bFlag_WriteView = false;
	
}


void CPacketView::OnBnClickedCheckView2()
{
	//읽기 보기
	if (pCheckBox_READ->GetCheck())
		ex_bFlag_ReadView = true;
	else
		ex_bFlag_ReadView = false;

}


void CPacketView::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.


}




void CPacketView::OnBnClickedButton2()
{
	//Send Packet Manual Mode
	UpdateData();

	((CHerkulexDlg *)GetParent())->Sendpacket_Manual(m_strPacket);

}


HBRUSH CPacketView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CPacketView::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ex_bFlagModal_View = false;

	//DestroyWindow();

}


void CPacketView::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//delete this;
}


void CPacketView::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	OnDestroy();

	CDialogEx::OnClose();
}
