#pragma once
#include "stdafx.h"

// CParameterDlg 대화 상자

class CParameterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParameterDlg)

public:
	CParameterDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CParameterDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARAMETER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CSliderCtrl m_SliderCtrl_1;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_2;
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_3;
	afx_msg void OnNMCustomdrawSlider4(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_4;
	afx_msg void OnNMCustomdrawSlider5(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_5;
	afx_msg void OnNMCustomdrawSlider6(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_6;
	afx_msg void OnNMCustomdrawSlider7(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_7;
	afx_msg void OnNMCustomdrawSlider8(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_8;
	afx_msg void OnNMCustomdrawSlider9(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_9;
	afx_msg void OnNMCustomdrawSlider10(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_10;
	afx_msg void OnNMCustomdrawSlider11(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_11;
	afx_msg void OnNMCustomdrawSlider12(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_12;
	afx_msg void OnNMCustomdrawSlider13(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_13;
	afx_msg void OnNMCustomdrawSlider14(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_14;
	afx_msg void OnNMCustomdrawSlider15(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_15;
	afx_msg void OnNMCustomdrawSlider16(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_16;
	afx_msg void OnNMCustomdrawSlider17(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_17;
	afx_msg void OnNMCustomdrawSlider18(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_18;
	afx_msg void OnNMCustomdrawSlider19(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_19;
	afx_msg void OnNMCustomdrawSlider20(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_20;
	afx_msg void OnNMCustomdrawSlider21(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_21;
	afx_msg void OnNMCustomdrawSlider22(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_22;
	afx_msg void OnNMCustomdrawSlider23(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_23;
	afx_msg void OnNMCustomdrawSlider24(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_24;
	afx_msg void OnNMCustomdrawSlider25(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_25;
	afx_msg void OnNMCustomdrawSlider26(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_26;
	afx_msg void OnNMCustomdrawSlider27(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton40();
	CComboBox m_cmBaudrateList;
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedButton41();
	afx_msg void OnBnClickedButton39();
	unsigned int m_uiValue1;
	afx_msg void OnEnChangeEdit1();
	unsigned int m_uiValue2;
	afx_msg void OnEnChangeEdit2();
	unsigned int m_uiValue3;
	afx_msg void OnEnChangeEdit10();
	unsigned int m_uiValue4;
	afx_msg void OnEnChangeEdit11();
	unsigned int m_uiValue5;
	afx_msg void OnEnChangeEdit12();
	unsigned int m_uiValue6;
	afx_msg void OnEnChangeEdit13();
	unsigned int m_uiValue7;
	afx_msg void OnEnChangeEdit14();
	unsigned int m_uiValue8;
	afx_msg void OnEnChangeEdit15();
	unsigned int m_uiValue9;
	afx_msg void OnEnChangeEdit16();
	unsigned int m_uiValue10;
	afx_msg void OnEnChangeEdit17();
	unsigned int m_uiValue11;
	afx_msg void OnEnChangeEdit18();
	unsigned int m_uiValue12;
	afx_msg void OnEnChangeEdit19();
	unsigned int m_uiValue13;
	afx_msg void OnEnChangeEdit20();
	unsigned int m_uiValue14;
	afx_msg void OnEnChangeEdit21();
	unsigned int m_uiValue15;
	afx_msg void OnEnChangeEdit22();
	unsigned int m_uiValue16;
	afx_msg void OnEnChangeEdit23();
	unsigned int m_uiValue17;
	afx_msg void OnEnChangeEdit24();
	unsigned int m_uiValue18;
	afx_msg void OnEnChangeEdit25();
	unsigned int m_uiValue19;
	afx_msg void OnEnChangeEdit26();
	unsigned int m_uiValue20;
	afx_msg void OnEnChangeEdit27();
	unsigned int m_uiValue21;
	afx_msg void OnEnChangeEdit28();
	unsigned int m_uiValue22;
	afx_msg void OnEnChangeEdit29();
	unsigned int m_uiValue23;
	afx_msg void OnEnChangeEdit30();
	unsigned int m_uiValue24;
	afx_msg void OnEnChangeEdit31();
	unsigned int m_uiValue25;
	afx_msg void OnEnChangeEdit32();
	unsigned int m_uiValue26;
	afx_msg void OnEnChangeEdit33();
	unsigned int m_uiValue27;
	afx_msg void OnEnChangeEdit34();
	unsigned int m_uiValue28;
	afx_msg void OnEnChangeEdit35();
	unsigned int m_uiValue29;
	afx_msg void OnEnChangeEdit36();
	CSliderCtrl m_SliderCtrl_27;
	afx_msg void OnNMCustomdrawSlider28(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SliderCtrl_28;
	afx_msg void OnNMCustomdrawSlider29(NMHDR *pNMHDR, LRESULT *pResult);
	unsigned int m_uiValue30;
	afx_msg void OnEnChangeEdit37();
	afx_msg void OnBnClickedButton42();
	afx_msg void OnDestroy();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton43();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
