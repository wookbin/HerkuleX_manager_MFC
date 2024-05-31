#pragma once
#include "stdafx.h"
//#include "HerkulexDlg.h"


// CRegisterMAP 대화 상자
class CRegisterMAP : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterMAP)

public:
	CRegisterMAP(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CRegisterMAP();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

public: //변수
	int m_iItem;
	int m_iSubitem;
	int m_iItem2;
	int m_iSubitem2;

public: //함수

	void InitListCtrlCols(void);
	void InsertItem_RAM(int iAddr, int iValue, CString strDescription, int iData);
	void InsertItem_EEP(int iAddr, int iValue, CString strDescription, int iData);


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTERMAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	CListCtrl m_EEPMAP_List;
	afx_msg void OnLvnItemchangedEepmap(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_RAMMAP_List;
	afx_msg void OnLvnItemchangedRammap(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnNMDblclkRammap(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkEepmap(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedRollback();
	virtual void OnOK();
	afx_msg void OnNMCustomdrawEepmap(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawRammap(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedRollback2();
	afx_msg void OnDestroy();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
};
