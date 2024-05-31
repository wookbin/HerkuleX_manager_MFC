#pragma once
#include "stdafx.h"
#include "ColorListBox.h"

// CPacketView 대화 상자

class CPacketView : public CDialogEx
{
	DECLARE_DYNAMIC(CPacketView)

public:
	CPacketView(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CPacketView();

public:
	//Color List Box사용//
	CColorListBox	m_ctrlMsgList2;


public:
	void writeMessageBox2(CString strTag, CString strMsg, COLORREF crText);



// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PACKETVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeMsglist2();
	afx_msg void OnBnClickedCheckView1();
	afx_msg void OnBnClickedCheckView2();
	virtual void OnOK();
	CString m_strPacket;
	afx_msg void OnBnClickedButton2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
};
