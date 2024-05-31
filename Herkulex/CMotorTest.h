#pragma once
#include "stdafx.h"
//#include "HerkulexDlg.h"

#include "OScopeCtrl.h" //Graph


// CMotorTest 대화 상자

class CMotorTest : public CDialogEx
{
	DECLARE_DYNAMIC(CMotorTest)

public:
	CMotorTest(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMotorTest();


public: //변수정의
	int m_iLEDCheck1[3];
	int m_iLEDCheck2[3];
	int m_iLEDCheck3[3];

	//Graph
	COScopeCtrl		*_rtGraph2;

public: //함수정의
	void SetLED();
	void A_POSE_MOVE();
	void B_POSE_MOVE();
	void C_POSE_MOVE();




// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOTORTEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_iPOES_A;
	int m_iPOES_B;
	int m_iPOES_C;
	int m_iPlaytime_A;
	int m_iPlaytime_B;
	int m_iPlaytime_C;
	int m_iErrorMargin;
	CString m_strErrorMargin;
	int m_iPoseError;
	CString m_strPoseError;
	int m_iSamplingTime;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton10();
	int m_TEST_ID;
	afx_msg void OnDestroy();
	int m_rMove_Sel;
	virtual void OnOK();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton16();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedCheck13();
	afx_msg void OnBnClickedCheck14();
	afx_msg void OnBnClickedCheck15();
	afx_msg void OnBnClickedCheck16();
	int m_rJOG_Sel;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
	int m_iTurn_A;
	afx_msg void OnEnChangeTurn1();
	int m_iTurn_B;
	afx_msg void OnEnChangeTurn2();
	int m_iTurn_C;
	afx_msg void OnEnChangeTurn3();
	double m_dScale;
	afx_msg void OnEnChangeEdit1();
	CSliderCtrl m_Slider_Zoom2;
	afx_msg void OnNMCustomdrawZoom2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
