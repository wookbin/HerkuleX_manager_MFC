#pragma once
#include "stdafx.h"
#include "ColorListBox.h"



// CFirmwareUpdate 대화 상자

class CFirmwareUpdate : public CDialogEx
{
	DECLARE_DYNAMIC(CFirmwareUpdate)

public:
	CFirmwareUpdate(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFirmwareUpdate();


public:
	CBitmap		m_bmp_BG_FW;
	CString		m_hexFileName;
	CString		m_hexPath;

	CColorListBox		m_ctrlMsgList3;

public:
	void GetFirmwear_Ver(CString strVer1, CString strVer2);
	void writeMessageBox3(CString strMsg, COLORREF crText);


	//Ymodem


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CBitmapButton m_BMPBUTTON_Open;
	CBitmapButton m_BMPBUTTON_Update;
	CBitmapButton m_BMPBUTTON_Status;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton19();
	CBitmapButton m_BMPBUTTON_Status2;
	CBitmapButton m_BMPBUTTON_Status3;
	//CListBox m_ctrlMsgList3;
	afx_msg void OnLbnSelchangeMsglist3();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnDestroy();
};
