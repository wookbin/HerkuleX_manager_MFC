#pragma once
#include "stdafx.h"
#include "HerkulexDlg.h"

// CProgressDlg 대화 상자

class CProgressDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProgressDlg)

public:
	CProgressDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CProgressDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROGRESSDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int		m_iScanCnt;
	BOOL	m_bScanCheck;
	int		m_iOld_ID;

	CProgressCtrl m_ProgressCtl;
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	void		 Kill_ProgressDlg_Timer();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedCancel();
};
