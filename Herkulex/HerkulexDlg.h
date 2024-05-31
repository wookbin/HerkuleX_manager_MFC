
// HerkulexDlg.h: 헤더 파일
//

#include "stdafx.h"
#include "CommThread.h"
#include "ColorListBox.h"
#include <list>		// 2019.04.08 by Mini
#include "herkulexlib.h"

#include "OScopeCtrl.h" //Graph
#include "CPacketView.h"
#include "CParameterDlg.h"
#include "CMotorTest.h"
#include "CRegisterMAP.h"
#include "CMultiMove.h"

#include "CFirmwareUpdate.h"

#pragma once

#define    REG_ADCINFO_MAX			(255) //(256)
#define	    REG_ADC_THEMISTOR_B		3380
#define 	REG_ADC_THEMISTOR_R0	10000
#define 	REG_ADC_THEMISTOR_T0	25

// CHerkulexDlg 대화 상자
class CHerkulexDlg : public CDialogEx
{
// 생성입니다.
public:
	CHerkulexDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	RAMRegisterMap		RAM[255];//ID는 최대 254까지//
	EEPRegisterMap		EEP;

	SJog	sjogs[255];
	IJog		ijogs[255];
	MSJog	msjogs[255]; //Multi Turn Add
	MIJog	mijogs[255]; //Multi Turn Add

	CImageList	m_lstImage;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HERKULEX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

public: //변수정의//
	//USB to Serial 통신//
	int				m_iComport;
	int				m_iBaudrate;
	CCommThread		m_hCommPort;
	DWORD			m_dwBaudRate;
	int				m_iBufferData;
	CString			m_strBufferData;
	CString			m_strRXData;
	//Color List Box사용//
	CColorListBox	m_ctrlMsgList;
	
	std::list<BYTE> m_lstBuffer;
	//LED Check Box관련//
	int				m_iLEDCheck[3];
	//Flag List
	BOOL			m_bFlag_Servo_ON;
	//Graph
	COScopeCtrl		*_rtGraph;
	//Packet View
	CPacketView		*_pViewDlg;
	//Parameter Dialog
	CParameterDlg	*_pParamDlg;
	//Motor Test Dialog
	CMotorTest		*_pTestDlg;
	//Map Setting Dialog
	CRegisterMAP	*_pMapDlg;
	//MultiMove Dialog
	CMultiMove		*_pMultiDlg;
	//FirmwareUpdate Dialog
	CFirmwareUpdate* _pFirmDlg;

	//Status표시용 BMP
	CBitmap		m_bmpOn;
	CBitmap		m_bmpOn2;
	CBitmap		m_bmpOff;

public: //함수정의//
	//Serial통신
	BOOL	OpenPort(UINT uPortNo, DWORD uBaudRate);
	void	ClosePort(void);
	int		SendHexadecimalData(const CString& strTx);
	int		SendASCIIData(const CString& strTx);
	BYTE	doHexData2AsciiValue(char cData);
	//List Box Write//
	void	writeMessageBox(CString strMsg, COLORREF crText);

	//Herkulex command//
	BOOL	Herkulex_ErrorClear(unsigned char cID);
	BOOL	Herkulex_Servo_Enable(unsigned char cID, unsigned int uiMode);

	//RAM Register Read All
	BOOL	RAM_Register_ReadALL();
	//EEP Register Read All
	BOOL	EEP_Register_ReadALL();

	//HerkuleX ID Scan//
	BOOL	Herkulex_IDScan(int iMotor_ID);
	//HerkuleX List Control관련//
	void	Init_ID_ListCtrlCols(void);
	void	InsertItem_ID(int iID, int iModel1, int iModel2, bool bOK);
	void	Init_InsertItem_ID(int iID, CString strModelName, bool bOK);

	//RAM Data Write관련//
	void	RAM_RegisterData_Write(unsigned int iAddr, unsigned int cData);
	//EEP Data Write관련//
	void	EEP_RegisterData_Write(unsigned int iAddr, unsigned int cData);



	//Packet View에 Send data출력//
	BOOL	Send_PrintData(unsigned char *cBuffer, int iLength);
	//Packet View에 Rend data출력//
	BOOL	Read_PrintData(unsigned char *cBuffer, int iLength);

	//S_JOG_Move Commad//
	BOOL	Position_Move(unsigned char cID, unsigned int iLED, unsigned int iPlayTime, int iTargetPos, int iJogMode, int iprofile, bool bMulti, int turn);
	BOOL	Velocity_Move(unsigned char cID, unsigned int iLED, int iTargetVel, int iJogMode, int iprofile, bool bMulti);

	//JOG Move
	BOOL	S_JOG_MOVE(unsigned int iPlayTime, unsigned int iTotal_Axis);
	BOOL  I_JOG_MOVE(unsigned int iTotal_Axis);
	//Add New Multi JOG
	BOOL	MS_JOG_MOVE(unsigned int iPlayTime, unsigned int iTotal_Axis, bool bMulti, int turn);
	BOOL  MI_JOG_MOVE(unsigned int iTotal_Axis, bool bMulti, int turn);

	//Status Display//
	BOOL	Status_Display();

	//TEMPERATURE계산 함수_추가: wbjin_2020.05.21
	double dfCalcTempCenigrade(double dfResOfTherm, int iBConstant, int iR0, int iT0);


	//Rollback 
	void	FactoryReset(unsigned char cID, int iID_Skip, int iBaudrate_Skip);

	//Reboot
	void	Reboot(unsigned char cID);

	//Add CALSET
	void CALSET(unsigned char cID); 

	//초기에 SCAN완료한 Herkulex의 정보 Read & Write 관련//
	void	Total_LoadDataFromRegistry(void);
	void	LoadDataFromRegistry(int iIndex);
	void	WriteDataToRegistry(CString strModelName, int iID, int iIndex);
	//Serial통신 연결정보 관련//
	void	WriteDataToRegistry_Serial(CString strCOM, CString strBaudrate);
	void	Serial_LoadDataFromRegistry(void);

	//Listcontrol에 이미지 띄우기...
	void	InitImageList(void);

	//Send Packet Manual Mode//
	void	Sendpacket_Manual(CString strPacket);
	void	Send_PrintData2(CString strPacket);

	void MemorySet();

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg long OnCommunication(WPARAM wParam, LPARAM lParam); //Serial통신//
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedDisconnect();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton5();
	unsigned int m_imotor_ID;
	double m_dmotor_Target;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton6();
	int m_iSpeedTime;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton7();
	CComboBox m_cmdModel;
	afx_msg void OnCbnSelchangeDsrModel();
	afx_msg void OnBnClickedButton8();
	CSliderCtrl m_sliderCtrl;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	int m_iSlider_Data;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CComboBox m_comport;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnDropdownCombo1();
	CComboBox m_baudrate;
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	CListCtrl m_listctl_ID;
	afx_msg void OnLvnItemchangedListId(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListId(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton13();
	afx_msg void OnStnClickedLogo1();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CSliderCtrl m_sliderCtrl2;
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton24();
	afx_msg void OnBnClickedButton25();
	afx_msg void OnBnClickedButton26();
	int m_iTurn;
	//afx_msg void OnEnChangeEdit29();
	CSliderCtrl m_Slider_Zoom;
	afx_msg void OnNMCustomdrawZoom(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio3();
};
