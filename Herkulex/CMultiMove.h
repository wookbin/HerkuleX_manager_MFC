#pragma once
#include "stdafx.h"
//#include "HerkulexDlg.h"

// CMultiMove 대화 상자

class CMultiMove : public CDialogEx
{
	DECLARE_DYNAMIC(CMultiMove)

public:
	CMultiMove(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMultiMove();

public:
	void InitListCtrlCols();
	void InsertItem(CString strID, bool bMode, CString strPaly_Time, CString strTarget, int iLED);


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MULTIMOVE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_MultiList;
	afx_msg void OnLvnItemchangedListMulti(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	int m_rSel_JOG;
	CString M_strID;
	CString M_strPlayTime;
	CString M_strTarget;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton10();
	CComboBox m_combo_Mode;
	afx_msg void OnNMClickListMulti(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedMutiServoOn();
	afx_msg void OnBnClickedMutiServoOff();
	afx_msg void OnBnClickedMutiMove();
	afx_msg void OnBnClickedMutiMove2();
	afx_msg void OnBnClickedMSJog();
	afx_msg void OnBnClickedMIJog();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedMutiMove3();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedMIJog2();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
	afx_msg void OnBnClickedMutiServoOff2();
	afx_msg void OnBnClickedMutiMove4();
};
