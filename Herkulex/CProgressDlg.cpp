// CProgressDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Herkulex.h"
#include "CProgressDlg.h"
#include "afxdialogex.h"


bool m_bOneTimeFlag;

// CProgressDlg 대화 상자
IMPLEMENT_DYNAMIC(CProgressDlg, CDialogEx)

CProgressDlg::CProgressDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROGRESSDLG, pParent)
{

}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressCtl);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CProgressDlg::OnNMCustomdrawProgress1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CProgressDlg::OnBnClickedButton1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, &CProgressDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CProgressDlg 메시지 처리기


void CProgressDlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_ProgressCtl.SetRange(0, 100);

	*pResult = 0;
}


BOOL CProgressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_bScanCheck = false;
	m_iScanCnt = 0;
	m_iOld_ID = -1;

	m_bOneTimeFlag = true;

	SetTimer(1, 50, NULL);

	OnBnClickedButton1();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
	// 100ms간격의 Timer Loop
	if (nIDEvent == 1)
	{
		if(m_bScanCheck)
		{
			if (m_bOneTimeFlag)
			{
				
				m_iScanCnt = 252;
				((CHerkulexDlg*)GetParent())->Herkulex_IDScan(m_iScanCnt + 1);

				//ID가 0인경우 제외//
				if (((CHerkulexDlg*)GetParent())->EEP.ucID == 0)
				{
					TRACE("ID가 0인경우 제외함");
					//m_iOld_ID++;
				}
				else
				{
					//List Control에 검색된 ID의 추가//
					((CHerkulexDlg*)GetParent())->InsertItem_ID(((CHerkulexDlg*)GetParent())->EEP.ucID,
																							((CHerkulexDlg*)GetParent())->EEP.ucModelNo1,
																							((CHerkulexDlg*)GetParent())->EEP.ucModelNo2, true);
				}

				m_iScanCnt = 0;
				m_bOneTimeFlag = false;
			}
			else
			{
				if (m_iScanCnt < 253)
				{
					TRACE("***************m_iScanCnt = %d", m_iScanCnt);
					((CHerkulexDlg*)GetParent())->Herkulex_IDScan(m_iScanCnt );
					TRACE("[%d]SCAN ID = %d  || m_iOld_ID = %d", (m_iScanCnt ), ((CHerkulexDlg*)GetParent())->EEP.ucID, m_iOld_ID);

				
					//ID중복이면 Scan Stop
					if (((CHerkulexDlg*)GetParent())->EEP.ucID == m_iOld_ID)
					{
						TRACE("[중복]SCAN ID = %d  || m_iOld_ID = %d", ((CHerkulexDlg*)GetParent())->EEP.ucID, m_iOld_ID);

						//Progress Bar Update//
						m_ProgressCtl.SetPos((m_iScanCnt / 253.0) * 100.0);
						m_iScanCnt++;
						return;
					}
					

					if (((CHerkulexDlg*)GetParent())->EEP.ucModelNo1 == 00)
					{
						TRACE("모델번호가 없으면 PASS!!");
					}
					else
					{
						//List Control에 검색된 ID의 추가//
						((CHerkulexDlg*)GetParent())->InsertItem_ID(((CHerkulexDlg*)GetParent())->EEP.ucID,
							((CHerkulexDlg*)GetParent())->EEP.ucModelNo1,
							((CHerkulexDlg*)GetParent())->EEP.ucModelNo2, true);
					}

					m_iOld_ID = ((CHerkulexDlg*)GetParent())->EEP.ucID;

					//Progress Bar Update//
					m_ProgressCtl.SetPos((m_iScanCnt / 253.0) * 100.0);
					m_iScanCnt++;

				}
				else
				{
					m_bScanCheck = false;
					Kill_ProgressDlg_Timer();
					m_iScanCnt = 0;
					m_iOld_ID = -1;
				}
			}
		}
	}


	CDialogEx::OnTimer(nIDEvent);
}


void CProgressDlg::OnBnClickedButton1()
{
	//TEST
	//((CHerkulexDlg *)GetParent())->Herkulex_IDScan(1);

	m_bScanCheck = true;

}

void CProgressDlg::Kill_ProgressDlg_Timer()
{
	KillTimer(1);
	
	//Progress bar 강제 Update//
	m_ProgressCtl.SetPos(254);

	CString strTemp = _T("HerkuleX ID검색이 완료되었습니다.");
	GetDlgItem(IDC_SCANTEXT)->SetWindowText(strTemp);

	OnBnClickedCancel();
}


void CProgressDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	KillTimer(1);
	m_iScanCnt = 0;
	m_iOld_ID = -1;
	//TRACE("검색 종료!!!!!");
	ex_bFlagSCAN = true;

}


void CProgressDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ex_bFlagSCAN = true;

	CDialogEx::OnCancel();
}
