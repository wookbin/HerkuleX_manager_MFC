// CParameterDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Herkulex.h"
#include "CParameterDlg.h"
#include "afxdialogex.h"
#include "HerkulexDlg.h"



int		m_iSilderValue[28] = { 0, };
CString m_strGetID = _T("");
CString m_strTemp[28] = { _T(""), };

CString m_strDifference = _T("");
CString m_strDifference_Offset = _T("");
int     m_iBaudrateValue = 0;

// CParameterDlg 대화 상자

IMPLEMENT_DYNAMIC(CParameterDlg, CDialogEx)

CParameterDlg::CParameterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PARAMETER, pParent)
	, m_uiValue1(0)
	, m_uiValue2(0)
	, m_uiValue3(0)
	, m_uiValue4(0)
	, m_uiValue5(0)
	, m_uiValue6(0)
	, m_uiValue7(0)
	, m_uiValue8(0)
	, m_uiValue9(0)
	, m_uiValue10(0)
	, m_uiValue11(0)
	, m_uiValue12(0)
	, m_uiValue13(0)
	, m_uiValue14(0)
	, m_uiValue15(0)
	, m_uiValue16(0)
	, m_uiValue17(0)
	, m_uiValue18(0)
	, m_uiValue19(0)
	, m_uiValue20(0)
	, m_uiValue21(0)
	, m_uiValue22(0)
	, m_uiValue23(0)
	, m_uiValue24(0)
	, m_uiValue25(0)
	, m_uiValue26(0)
	, m_uiValue27(0)
	, m_uiValue28(0)
	, m_uiValue29(0)
	, m_uiValue30(0)
{

}

CParameterDlg::~CParameterDlg()
{
}

void CParameterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_SliderCtrl_1);
	DDX_Control(pDX, IDC_SLIDER3, m_SliderCtrl_2);
	DDX_Control(pDX, IDC_SLIDER4, m_SliderCtrl_3);
	DDX_Control(pDX, IDC_SLIDER5, m_SliderCtrl_4);
	DDX_Control(pDX, IDC_SLIDER6, m_SliderCtrl_5);
	DDX_Control(pDX, IDC_SLIDER7, m_SliderCtrl_6);
	DDX_Control(pDX, IDC_SLIDER8, m_SliderCtrl_7);
	DDX_Control(pDX, IDC_SLIDER9, m_SliderCtrl_8);
	DDX_Control(pDX, IDC_SLIDER10, m_SliderCtrl_9);
	DDX_Control(pDX, IDC_SLIDER11, m_SliderCtrl_10);
	DDX_Control(pDX, IDC_SLIDER12, m_SliderCtrl_11);
	DDX_Control(pDX, IDC_SLIDER13, m_SliderCtrl_12);
	DDX_Control(pDX, IDC_SLIDER14, m_SliderCtrl_13);
	DDX_Control(pDX, IDC_SLIDER15, m_SliderCtrl_14);
	DDX_Control(pDX, IDC_SLIDER16, m_SliderCtrl_15);
	DDX_Control(pDX, IDC_SLIDER17, m_SliderCtrl_16);
	DDX_Control(pDX, IDC_SLIDER18, m_SliderCtrl_17);
	DDX_Control(pDX, IDC_SLIDER19, m_SliderCtrl_18);
	DDX_Control(pDX, IDC_SLIDER20, m_SliderCtrl_19);
	DDX_Control(pDX, IDC_SLIDER21, m_SliderCtrl_20);
	DDX_Control(pDX, IDC_SLIDER22, m_SliderCtrl_21);
	DDX_Control(pDX, IDC_SLIDER23, m_SliderCtrl_22);
	DDX_Control(pDX, IDC_SLIDER24, m_SliderCtrl_23);
	DDX_Control(pDX, IDC_SLIDER25, m_SliderCtrl_24);
	DDX_Control(pDX, IDC_SLIDER26, m_SliderCtrl_25);
	DDX_Control(pDX, IDC_SLIDER27, m_SliderCtrl_26);
	DDX_Control(pDX, IDC_COMBO3, m_cmBaudrateList);
	DDX_Text(pDX, IDC_EDIT1, m_uiValue1);
	DDX_Text(pDX, IDC_EDIT2, m_uiValue2);
	DDX_Text(pDX, IDC_EDIT10, m_uiValue3);
	DDX_Text(pDX, IDC_EDIT11, m_uiValue4);
	DDX_Text(pDX, IDC_EDIT12, m_uiValue5);
	DDX_Text(pDX, IDC_EDIT13, m_uiValue6);
	DDX_Text(pDX, IDC_EDIT14, m_uiValue7);
	DDX_Text(pDX, IDC_EDIT15, m_uiValue8);
	DDX_Text(pDX, IDC_EDIT16, m_uiValue9);
	DDX_Text(pDX, IDC_EDIT17, m_uiValue10);
	DDX_Text(pDX, IDC_EDIT18, m_uiValue11);
	DDX_Text(pDX, IDC_EDIT19, m_uiValue12);
	DDX_Text(pDX, IDC_EDIT20, m_uiValue13);
	DDX_Text(pDX, IDC_EDIT21, m_uiValue14);
	DDX_Text(pDX, IDC_EDIT22, m_uiValue15);
	DDX_Text(pDX, IDC_EDIT23, m_uiValue16);
	DDX_Text(pDX, IDC_EDIT24, m_uiValue17);
	DDX_Text(pDX, IDC_EDIT25, m_uiValue18);
	DDX_Text(pDX, IDC_EDIT26, m_uiValue19);
	DDX_Text(pDX, IDC_EDIT27, m_uiValue20);
	DDX_Text(pDX, IDC_EDIT28, m_uiValue21);
	DDX_Text(pDX, IDC_EDIT29, m_uiValue22);
	DDX_Text(pDX, IDC_EDIT30, m_uiValue23);
	DDX_Text(pDX, IDC_EDIT31, m_uiValue24);
	DDX_Text(pDX, IDC_EDIT32, m_uiValue25);
	DDX_Text(pDX, IDC_EDIT33, m_uiValue26);
	DDX_Text(pDX, IDC_EDIT34, m_uiValue27);
	DDX_Text(pDX, IDC_EDIT35, m_uiValue28);
	DDX_Text(pDX, IDC_EDIT36, m_uiValue29);
	DDX_Control(pDX, IDC_SLIDER28, m_SliderCtrl_27);
	DDX_Control(pDX, IDC_SLIDER29, m_SliderCtrl_28);
	DDX_Text(pDX, IDC_EDIT37, m_uiValue30);
}


BEGIN_MESSAGE_MAP(CParameterDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CParameterDlg::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CParameterDlg::OnNMCustomdrawSlider3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER4, &CParameterDlg::OnNMCustomdrawSlider4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, &CParameterDlg::OnNMCustomdrawSlider5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER6, &CParameterDlg::OnNMCustomdrawSlider6)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER7, &CParameterDlg::OnNMCustomdrawSlider7)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER8, &CParameterDlg::OnNMCustomdrawSlider8)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER9, &CParameterDlg::OnNMCustomdrawSlider9)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER10, &CParameterDlg::OnNMCustomdrawSlider10)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER11, &CParameterDlg::OnNMCustomdrawSlider11)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER12, &CParameterDlg::OnNMCustomdrawSlider12)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER13, &CParameterDlg::OnNMCustomdrawSlider13)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER14, &CParameterDlg::OnNMCustomdrawSlider14)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER15, &CParameterDlg::OnNMCustomdrawSlider15)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER16, &CParameterDlg::OnNMCustomdrawSlider16)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER17, &CParameterDlg::OnNMCustomdrawSlider17)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER18, &CParameterDlg::OnNMCustomdrawSlider18)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER19, &CParameterDlg::OnNMCustomdrawSlider19)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER20, &CParameterDlg::OnNMCustomdrawSlider20)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER21, &CParameterDlg::OnNMCustomdrawSlider21)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER22, &CParameterDlg::OnNMCustomdrawSlider22)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER23, &CParameterDlg::OnNMCustomdrawSlider23)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER24, &CParameterDlg::OnNMCustomdrawSlider24)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER25, &CParameterDlg::OnNMCustomdrawSlider25)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER26, &CParameterDlg::OnNMCustomdrawSlider26)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER27, &CParameterDlg::OnNMCustomdrawSlider27)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON40, &CParameterDlg::OnBnClickedButton40)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CParameterDlg::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_BUTTON41, &CParameterDlg::OnBnClickedButton41)
	ON_BN_CLICKED(IDC_BUTTON39, &CParameterDlg::OnBnClickedButton39)
	ON_EN_CHANGE(IDC_EDIT1, &CParameterDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CParameterDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT10, &CParameterDlg::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, &CParameterDlg::OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, &CParameterDlg::OnEnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT13, &CParameterDlg::OnEnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT14, &CParameterDlg::OnEnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, &CParameterDlg::OnEnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT16, &CParameterDlg::OnEnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT17, &CParameterDlg::OnEnChangeEdit17)
	ON_EN_CHANGE(IDC_EDIT18, &CParameterDlg::OnEnChangeEdit18)
	ON_EN_CHANGE(IDC_EDIT19, &CParameterDlg::OnEnChangeEdit19)
	ON_EN_CHANGE(IDC_EDIT20, &CParameterDlg::OnEnChangeEdit20)
	ON_EN_CHANGE(IDC_EDIT21, &CParameterDlg::OnEnChangeEdit21)
	ON_EN_CHANGE(IDC_EDIT22, &CParameterDlg::OnEnChangeEdit22)
	ON_EN_CHANGE(IDC_EDIT23, &CParameterDlg::OnEnChangeEdit23)
	ON_EN_CHANGE(IDC_EDIT24, &CParameterDlg::OnEnChangeEdit24)
	ON_EN_CHANGE(IDC_EDIT25, &CParameterDlg::OnEnChangeEdit25)
	ON_EN_CHANGE(IDC_EDIT26, &CParameterDlg::OnEnChangeEdit26)
	ON_EN_CHANGE(IDC_EDIT27, &CParameterDlg::OnEnChangeEdit27)
	ON_EN_CHANGE(IDC_EDIT28, &CParameterDlg::OnEnChangeEdit28)
	ON_EN_CHANGE(IDC_EDIT29, &CParameterDlg::OnEnChangeEdit29)
	ON_EN_CHANGE(IDC_EDIT30, &CParameterDlg::OnEnChangeEdit30)
	ON_EN_CHANGE(IDC_EDIT31, &CParameterDlg::OnEnChangeEdit31)
	ON_EN_CHANGE(IDC_EDIT32, &CParameterDlg::OnEnChangeEdit32)
	ON_EN_CHANGE(IDC_EDIT33, &CParameterDlg::OnEnChangeEdit33)
	ON_EN_CHANGE(IDC_EDIT34, &CParameterDlg::OnEnChangeEdit34)
	ON_EN_CHANGE(IDC_EDIT35, &CParameterDlg::OnEnChangeEdit35)
	ON_EN_CHANGE(IDC_EDIT36, &CParameterDlg::OnEnChangeEdit36)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER28, &CParameterDlg::OnNMCustomdrawSlider28)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER29, &CParameterDlg::OnNMCustomdrawSlider29)
	ON_EN_CHANGE(IDC_EDIT37, &CParameterDlg::OnEnChangeEdit37)
	ON_BN_CLICKED(IDC_BUTTON42, &CParameterDlg::OnBnClickedButton42)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON43, &CParameterDlg::OnBnClickedButton43)
END_MESSAGE_MAP()


// CParameterDlg 메시지 처리기


BOOL CParameterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CHerkulexDlg*)GetParent())->RAM_Register_ReadALL();
	Sleep(300);
	((CHerkulexDlg*)GetParent())->EEP_Register_ReadALL();

	//Settinhg//
	m_SliderCtrl_1.SetLineSize(1);
	m_SliderCtrl_1.SetPageSize(10);
	m_SliderCtrl_2.SetLineSize(1);
	m_SliderCtrl_2.SetPageSize(10);
	m_SliderCtrl_3.SetLineSize(1);
	m_SliderCtrl_3.SetPageSize(10);
	m_SliderCtrl_4.SetLineSize(1);
	m_SliderCtrl_4.SetPageSize(10);
	m_SliderCtrl_5.SetLineSize(1);
	m_SliderCtrl_5.SetPageSize(10);
	m_SliderCtrl_6.SetLineSize(1);
	m_SliderCtrl_6.SetPageSize(10);
	m_SliderCtrl_7.SetLineSize(1);
	m_SliderCtrl_7.SetPageSize(10);
	m_SliderCtrl_8.SetLineSize(1);
	m_SliderCtrl_8.SetPageSize(10);
	m_SliderCtrl_9.SetLineSize(1);
	m_SliderCtrl_9.SetPageSize(10);
	m_SliderCtrl_10.SetLineSize(1);
	m_SliderCtrl_10.SetPageSize(10);
	m_SliderCtrl_11.SetLineSize(1);
	m_SliderCtrl_11.SetPageSize(10);
	m_SliderCtrl_12.SetLineSize(1);
	m_SliderCtrl_12.SetPageSize(10);
	m_SliderCtrl_13.SetLineSize(1);
	m_SliderCtrl_13.SetPageSize(10);
	m_SliderCtrl_14.SetLineSize(1);
	m_SliderCtrl_14.SetPageSize(10);
	m_SliderCtrl_15.SetLineSize(1);
	m_SliderCtrl_15.SetPageSize(10);
	m_SliderCtrl_16.SetLineSize(1);
	m_SliderCtrl_16.SetPageSize(10);
	m_SliderCtrl_17.SetLineSize(1);
	m_SliderCtrl_17.SetPageSize(10);
	m_SliderCtrl_18.SetLineSize(1);
	m_SliderCtrl_18.SetPageSize(10);
	m_SliderCtrl_19.SetLineSize(1);
	m_SliderCtrl_19.SetPageSize(10);
	m_SliderCtrl_20.SetLineSize(1);
	m_SliderCtrl_20.SetPageSize(10);
	m_SliderCtrl_21.SetLineSize(1);
	m_SliderCtrl_21.SetPageSize(10);
	m_SliderCtrl_22.SetLineSize(1);
	m_SliderCtrl_22.SetPageSize(10);
	m_SliderCtrl_23.SetLineSize(1);
	m_SliderCtrl_23.SetPageSize(10);
	m_SliderCtrl_24.SetLineSize(1);
	m_SliderCtrl_24.SetPageSize(10);
	m_SliderCtrl_25.SetLineSize(1);
	m_SliderCtrl_25.SetPageSize(10);
	m_SliderCtrl_26.SetLineSize(1);
	m_SliderCtrl_26.SetPageSize(10);
	m_SliderCtrl_27.SetLineSize(1);
	m_SliderCtrl_27.SetPageSize(10);
	m_SliderCtrl_28.SetLineSize(1);
	m_SliderCtrl_28.SetPageSize(10);

	//Model에 따라서 +-Limit 값의 범위를 조정해야....
//Model별로 Test위치값 변경
	if (ex_DRS_Model_Num <= 5) //01~02~03 모델
	{
		//Position
		m_SliderCtrl_1.SetRange(0, 1023); //Position +Limit
		m_SliderCtrl_2.SetRange(0, 1023); //Position -Limit
		//Gain
		m_SliderCtrl_3.SetRange(0, 32767); //P Gain
		m_SliderCtrl_4.SetRange(0, 32767); //D Gain
		m_SliderCtrl_5.SetRange(0, 32767); //I Gain
		m_SliderCtrl_6.SetRange(0, 32767); //FF 1st Gain
		m_SliderCtrl_7.SetRange(0, 32767); //FF 2nd Gain -> usVelocityKp로 수정됨.
		//Add Velocity Gain
		m_SliderCtrl_27.SetRange(0, 32767); // usVelocityKd
		m_SliderCtrl_28.SetRange(0, 32767); // usVelocityKi

		//Accelation
		m_SliderCtrl_8.SetRange(0, 50);
		m_SliderCtrl_9.SetRange(0, 254);
		//Saturation
		m_SliderCtrl_10.SetRange(0, 254);
		m_SliderCtrl_11.SetRange(0, 254);
		m_SliderCtrl_12.SetRange(0, 32767);
		//Inposition
		m_SliderCtrl_13.SetRange(0, 254);
		m_SliderCtrl_14.SetRange(0, 254);
		//PWM
		m_SliderCtrl_15.SetRange(-127, 127);
		m_SliderCtrl_16.SetRange(0, 254);
		m_SliderCtrl_17.SetRange(0, 1023);
		m_SliderCtrl_18.SetRange(0, 1023);
		//Fault Check
		m_SliderCtrl_19.SetRange(0, 254);
		m_SliderCtrl_20.SetRange(0, 254);
		m_SliderCtrl_21.SetRange(0, 254);
		m_SliderCtrl_22.SetRange(0, 254);
		m_SliderCtrl_23.SetRange(0, 254);
		//ADC Limit
		m_SliderCtrl_24.SetRange(0, 254);
		m_SliderCtrl_25.SetRange(0, 254);
		m_SliderCtrl_26.SetRange(0, 254);
	}
	else //04~06 모델
	{
		//Position
		m_SliderCtrl_1.SetRange(0, 32767); //Position +Limit
		m_SliderCtrl_2.SetRange(0, 32767); //Position -Limit
		//Gain
		m_SliderCtrl_3.SetRange(0, 32767); //P Gain
		m_SliderCtrl_4.SetRange(0, 32767); //D Gain
		m_SliderCtrl_5.SetRange(0, 32767); //I Gain
		m_SliderCtrl_6.SetRange(0, 32767); //FF 1st Gain
		m_SliderCtrl_7.SetRange(0, 32767); //FF 2nd Gain -> usVelocityKp로 수정됨.
		//Add Velocity Gain
		m_SliderCtrl_27.SetRange(0, 32767); // usVelocityKd
		m_SliderCtrl_28.SetRange(0, 32767); // usVelocityKi

		//Accelation
		m_SliderCtrl_8.SetRange(0, 50);
		m_SliderCtrl_9.SetRange(0, 254);
		//Saturation
		m_SliderCtrl_10.SetRange(0, 254);
		m_SliderCtrl_11.SetRange(0, 254);
		m_SliderCtrl_12.SetRange(0, 32767);
		//Inposition
		m_SliderCtrl_13.SetRange(0, 254);
		m_SliderCtrl_14.SetRange(0, 254);
		//PWM
		m_SliderCtrl_15.SetRange(-127, 127);
		m_SliderCtrl_16.SetRange(0, 254);
		m_SliderCtrl_17.SetRange(0, 1023);
		m_SliderCtrl_18.SetRange(0, 1023);
		//Fault Check
		m_SliderCtrl_19.SetRange(0, 254);
		m_SliderCtrl_20.SetRange(0, 254);
		m_SliderCtrl_21.SetRange(0, 254);
		m_SliderCtrl_22.SetRange(0, 254);
		m_SliderCtrl_23.SetRange(0, 254);
		//ADC Limit
		m_SliderCtrl_24.SetRange(0, 110);
		m_SliderCtrl_25.SetRange(92, 200);
		m_SliderCtrl_26.SetRange(92, 200);
	}


	//Check ex_DRS_Model_Num = 03 series
	if (ex_DRS_Model_Num == 3 || ex_DRS_Model_Num == 4 || ex_DRS_Model_Num == 5)
	{
		GetDlgItem(IDC_FF1)->SetWindowText("Current_limit:");
		GetDlgItem(IDC_V_KP)->SetWindowText("Velocity_Kp:");
		GetDlgItem(IDC_V_KD)->SetWindowText("Velocity_Kd:");
		GetDlgItem(IDC_V_KI)->SetWindowText("Velocity_Ki:");

		GetDlgItem(IDC_TURN)->SetWindowText("Turn:");
	}
	else
	{
		GetDlgItem(IDC_FF1)->SetWindowText("FF 1st:");
		GetDlgItem(IDC_V_KP)->SetWindowText("FF 2nd:");
		GetDlgItem(IDC_V_KD)->SetWindowText("Reserved:");
		GetDlgItem(IDC_V_KI)->SetWindowText("Reserved:");

		GetDlgItem(IDC_TURN)->SetWindowText("Offset:");
	}


	//Main UI버튼들의 비활성화//
	GetDlgItem(IDC_BUTTON41)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CParameterDlg::OnOK()
{
	//Enter 무시//

}


HBRUSH CParameterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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



void CParameterDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider7(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider8(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider9(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider10(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider11(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider12(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider13(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider14(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider15(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider16(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider17(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider18(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider19(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider20(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider21(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider22(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider23(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider24(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider25(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider26(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider27(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (nSBCode == SB_ENDSCROLL)
		return;

	// Slider Bar Control//
	if (pScrollBar == (CScrollBar*)&m_SliderCtrl_1)
	{
		m_iSilderValue[0] = (m_SliderCtrl_1).GetPos();
		m_strTemp[0].Format("%d", m_iSilderValue[0]);
		GetDlgItem(IDC_EDIT1)->SetWindowText(m_strTemp[0]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_MAX_POSITION, m_uiValue1);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_2)
	{
		m_iSilderValue[1] = (m_SliderCtrl_2).GetPos();
		m_strTemp[1].Format("%d", m_iSilderValue[1]);
		GetDlgItem(IDC_EDIT2)->SetWindowText(m_strTemp[1]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_MIN_POSITION, m_uiValue2);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_3)
	{
		m_iSilderValue[2] = (m_SliderCtrl_3).GetPos();
		m_strTemp[2].Format("%d", m_iSilderValue[2]);
		GetDlgItem(IDC_EDIT10)->SetWindowText(m_strTemp[2]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_POSITION_KP, m_uiValue3);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_4)
	{
		m_iSilderValue[3] = (m_SliderCtrl_4).GetPos();
		m_strTemp[3].Format("%d", m_iSilderValue[3]);
		GetDlgItem(IDC_EDIT11)->SetWindowText(m_strTemp[3]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_POSITION_KD, m_uiValue4);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_5)
	{
		m_iSilderValue[4] = (m_SliderCtrl_5).GetPos();
		m_strTemp[4].Format("%d", m_iSilderValue[4]);
		GetDlgItem(IDC_EDIT12)->SetWindowText(m_strTemp[4]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_POSITION_KI, m_uiValue5);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_6)
	{
		m_iSilderValue[5] = (m_SliderCtrl_6).GetPos();
		m_strTemp[5].Format("%d", m_iSilderValue[5]);
		GetDlgItem(IDC_EDIT13)->SetWindowText(m_strTemp[5]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_POSITION_FEEDFORWARD_1ST_GAIN, m_uiValue6);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_7)
	{
		m_iSilderValue[6] = (m_SliderCtrl_7).GetPos();
		m_strTemp[6].Format("%d", m_iSilderValue[6]);
		GetDlgItem(IDC_EDIT14)->SetWindowText(m_strTemp[6]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_POSITION_FEEDFORWARD_2ND_GAIN, m_uiValue7);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_8)
	{
		m_iSilderValue[7] = (m_SliderCtrl_8).GetPos();
		m_strTemp[7].Format("%d", m_iSilderValue[7]);
		GetDlgItem(IDC_EDIT15)->SetWindowText(m_strTemp[7]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_ACCELERATION_RATIO, m_uiValue8);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_9)
	{
		m_iSilderValue[8] = (m_SliderCtrl_9).GetPos();
		m_strTemp[8].Format("%d", m_iSilderValue[8]);
		GetDlgItem(IDC_EDIT16)->SetWindowText(m_strTemp[8]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_MAX_ACCELERATION_TIME, m_uiValue9);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_10)
	{
		m_iSilderValue[9] = (m_SliderCtrl_10).GetPos();
		m_strTemp[9].Format("%d", m_iSilderValue[9]);
		GetDlgItem(IDC_EDIT17)->SetWindowText(m_strTemp[9]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_DEAD_ZONE, m_uiValue10);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_11)
	{
		m_iSilderValue[10] = (m_SliderCtrl_11).GetPos();
		m_strTemp[10].Format("%d", m_iSilderValue[10]);
		GetDlgItem(IDC_EDIT18)->SetWindowText(m_strTemp[10]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_SATURATOR_OFFSET, m_uiValue11);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_12)
	{
		m_iSilderValue[11] = (m_SliderCtrl_12).GetPos();
		m_strTemp[11].Format("%d", m_iSilderValue[11]);
		GetDlgItem(IDC_EDIT19)->SetWindowText(m_strTemp[11]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_SATURATOR_SLOPE, m_uiValue12);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_13)
	{
		m_iSilderValue[12] = (m_SliderCtrl_13).GetPos();
		m_strTemp[12].Format("%d", m_iSilderValue[12]);
		GetDlgItem(IDC_EDIT20)->SetWindowText(m_strTemp[12]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_STOP_THRESHOLD, m_uiValue13);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_14)
	{
		m_iSilderValue[13] = (m_SliderCtrl_14).GetPos();
		m_strTemp[13].Format("%d", m_iSilderValue[13]);
		GetDlgItem(IDC_EDIT21)->SetWindowText(m_strTemp[13]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_INPOSITION_MARGIN, m_uiValue14);


	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_15)
	{
		m_iSilderValue[14] = (m_SliderCtrl_15).GetPos();
		m_strTemp[14].Format("%d", m_iSilderValue[14]);
		GetDlgItem(IDC_EDIT22)->SetWindowText(m_strTemp[14]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_PWM_OFFSET, m_uiValue15);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_16)
	{
		m_iSilderValue[15] = (m_SliderCtrl_16).GetPos();
		m_strTemp[15].Format("%d", m_iSilderValue[15]);
		GetDlgItem(IDC_EDIT23)->SetWindowText(m_strTemp[15]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_MIN_PWM, m_uiValue16);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_17)
	{
		m_iSilderValue[16] = (m_SliderCtrl_17).GetPos();
		m_strTemp[16].Format("%d", m_iSilderValue[16]);
		GetDlgItem(IDC_EDIT24)->SetWindowText(m_strTemp[16]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_MAX_PWM, m_uiValue17);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_18)
	{
		m_iSilderValue[17] = (m_SliderCtrl_18).GetPos();
		m_strTemp[17].Format("%d", m_iSilderValue[17]);
		GetDlgItem(IDC_EDIT25)->SetWindowText(m_strTemp[17]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_OVERLOAD_PWM_THRESHOLD, m_uiValue18);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_19)
	{
		m_iSilderValue[18] = (m_SliderCtrl_19).GetPos();
		m_strTemp[18].Format("%d", m_iSilderValue[18]);
		GetDlgItem(IDC_EDIT26)->SetWindowText(m_strTemp[18]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_ADC_FAULT_CHECK_PERIOD, m_uiValue19);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_20)
	{
		m_iSilderValue[19] = (m_SliderCtrl_20).GetPos();
		m_strTemp[19].Format("%d", m_iSilderValue[19]);
		GetDlgItem(IDC_EDIT27)->SetWindowText(m_strTemp[19]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_LED_BLINK_PERIOD, m_uiValue20);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_21)
	{
		m_iSilderValue[20] = (m_SliderCtrl_21).GetPos();
		m_strTemp[20].Format("%d", m_iSilderValue[20]);
		GetDlgItem(IDC_EDIT28)->SetWindowText(m_strTemp[20]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_PACKET_GARBAGE_CHECK_PERIOD, m_uiValue21);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_22)
	{
		m_iSilderValue[21] = (m_SliderCtrl_22).GetPos();
		m_strTemp[21].Format("%d", m_iSilderValue[21]);
		GetDlgItem(IDC_EDIT29)->SetWindowText(m_strTemp[21]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_STOP_DETECTION_PERIOD, m_uiValue22);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_23)
	{
		m_iSilderValue[22] = (m_SliderCtrl_23).GetPos();
		m_strTemp[22].Format("%d", m_iSilderValue[22]);
		GetDlgItem(IDC_EDIT30)->SetWindowText(m_strTemp[22]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_OVELOAD_DETECTION_PERIOD, m_uiValue23);

	}
	//else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_24)
	//{
	//	m_iSilderValue[23] = (m_SliderCtrl_24).GetPos();
	//	m_strTemp[23].Format("%d", m_iSilderValue[23]);
	//	GetDlgItem(IDC_EDIT31)->SetWindowText(m_strTemp[23]);


	//}
	//else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_25)
	//{
	//	m_iSilderValue[24] = (m_SliderCtrl_25).GetPos();
	//	m_strTemp[24].Format("%d", m_iSilderValue[24]);
	//	GetDlgItem(IDC_EDIT32)->SetWindowText(m_strTemp[24]);

	//}
	//else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_26)
	//{
	//	m_iSilderValue[25] = (m_SliderCtrl_26).GetPos();
	//	m_strTemp[25].Format("%d", m_iSilderValue[25]);
	//	GetDlgItem(IDC_EDIT33)->SetWindowText(m_strTemp[25]);

	//}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_27)
	{
		m_iSilderValue[26] = (m_SliderCtrl_27).GetPos();
		m_strTemp[26].Format("%d", m_iSilderValue[26]);
		GetDlgItem(IDC_EDIT35)->SetWindowText(m_strTemp[26]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_VELOCITY_KD, m_uiValue28);

	}
	else if (pScrollBar == (CScrollBar*)&m_SliderCtrl_28)
	{
		m_iSilderValue[27] = (m_SliderCtrl_28).GetPos();
		m_strTemp[27].Format("%d", m_iSilderValue[27]);
		GetDlgItem(IDC_EDIT36)->SetWindowText(m_strTemp[27]);
		((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_VELOCITY_KI, m_uiValue29);
	}




	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CParameterDlg::OnBnClickedButton40()
{
	if (!ex_bFlag_Connect)
	{
		((CHerkulexDlg*)GetParent())->MemorySet();
		return;
	}
	CString m_strModel_Type = _T("");
	// UpdateData Edit Text Set//
	UpdateData();

	//ID
	m_strGetID.Format("%d", ((CHerkulexDlg*)GetParent())->RAM[((CHerkulexDlg*)GetParent())->m_imotor_ID].ucID);
	GetDlgItem(IDC_EDIT38)->SetWindowText(m_strGetID);
	//Model
	switch (ex_DRS_Model_Num)
	{
	case 0:
		m_strModel_Type = _T("DRS-0101");
		break;
	case 1:
		m_strModel_Type = _T("DRS-0102");
		break;
	case 2:
		m_strModel_Type = _T("DRS-0201");
		break;
		///////////New HerkuleX//////////////
	case 3:
		m_strModel_Type = _T("DRS-0301");
		break;
	case 4:
		m_strModel_Type = _T("DSR-0302");
		break;
	case 5:
		m_strModel_Type = _T("DRS-0303");
		break;
		/////////////////////////////////////
	case 6:
		m_strModel_Type = _T("DRS-0401");
		break;
	case 7:
		m_strModel_Type = _T("DRS-0402");
		break;
	case 8:
		m_strModel_Type = _T("DRS-0601");
		break;
	case 9:
		m_strModel_Type = _T("DRS-0602");
		break;
	}

	GetDlgItem(IDC_EDIT39)->SetWindowText(m_strModel_Type);

	//Position
	m_strTemp[0].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usMaxPosition);
	GetDlgItem(IDC_EDIT1)->SetWindowText(m_strTemp[0]);
	m_SliderCtrl_1.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usMaxPosition);

	m_strTemp[1].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usMinPosition);
	GetDlgItem(IDC_EDIT2)->SetWindowText(m_strTemp[1]);
	m_SliderCtrl_2.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usMinPosition);

	//Gain
	m_strTemp[2].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionKp);
	GetDlgItem(IDC_EDIT10)->SetWindowText(m_strTemp[2]);
	m_SliderCtrl_3.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionKp);

	m_strTemp[3].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionKd);
	GetDlgItem(IDC_EDIT11)->SetWindowText(m_strTemp[3]);
	m_SliderCtrl_4.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionKd);

	m_strTemp[4].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionKi);
	GetDlgItem(IDC_EDIT12)->SetWindowText(m_strTemp[4]);
	m_SliderCtrl_5.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionKi);

	m_strTemp[5].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionFeedforward1stGain);
	GetDlgItem(IDC_EDIT13)->SetWindowText(m_strTemp[5]);
	m_SliderCtrl_6.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionFeedforward1stGain);

	m_strTemp[6].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionFeedforward2ndGain);
	GetDlgItem(IDC_EDIT14)->SetWindowText(m_strTemp[6]);
	m_SliderCtrl_7.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usPositionFeedforward2ndGain);

	//Add Velocity Gain
	m_strTemp[26].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usVelocityKd);
	GetDlgItem(IDC_EDIT35)->SetWindowText(m_strTemp[26]);
	m_SliderCtrl_27.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usVelocityKd);

	m_strTemp[27].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usVelocityKi);
	GetDlgItem(IDC_EDIT36)->SetWindowText(m_strTemp[27]);
	m_SliderCtrl_28.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usVelocityKi);


	//Acceleration
	m_strTemp[7].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucAccelerationRatio);
	GetDlgItem(IDC_EDIT15)->SetWindowText(m_strTemp[7]);
	m_SliderCtrl_8.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucAccelerationRatio);

	m_strTemp[8].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMaxAccelerationTime);
	GetDlgItem(IDC_EDIT16)->SetWindowText(m_strTemp[8]);
	m_SliderCtrl_9.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMaxAccelerationTime);


	//Saturation
	m_strTemp[9].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucDeadZone);
	GetDlgItem(IDC_EDIT17)->SetWindowText(m_strTemp[9]);
	m_SliderCtrl_10.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucDeadZone);

	m_strTemp[10].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucSaturatorOffset);
	GetDlgItem(IDC_EDIT18)->SetWindowText(m_strTemp[10]);
	m_SliderCtrl_11.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucSaturatorOffset);

	m_strTemp[11].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usSaturatorSlope);
	GetDlgItem(IDC_EDIT19)->SetWindowText(m_strTemp[11]);
	m_SliderCtrl_12.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usSaturatorSlope);


	//Inposition
	m_strTemp[12].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucStopThreshold);
	GetDlgItem(IDC_EDIT20)->SetWindowText(m_strTemp[12]);
	m_SliderCtrl_13.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucStopThreshold);

	m_strTemp[13].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucInpositionMargin);
	GetDlgItem(IDC_EDIT21)->SetWindowText(m_strTemp[13]);
	m_SliderCtrl_14.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucInpositionMargin);


	//PWM
	m_strTemp[14].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].cPWMOffset);
	GetDlgItem(IDC_EDIT22)->SetWindowText(m_strTemp[14]);
	m_SliderCtrl_15.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].cPWMOffset);

	m_strTemp[15].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMinPWM);
	GetDlgItem(IDC_EDIT23)->SetWindowText(m_strTemp[15]);
	m_SliderCtrl_16.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMinPWM);

	m_strTemp[16].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usMaxPWM);
	GetDlgItem(IDC_EDIT24)->SetWindowText(m_strTemp[16]);
	m_SliderCtrl_17.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usMaxPWM);

	m_strTemp[17].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usOverloadPWMThreshold);
	GetDlgItem(IDC_EDIT25)->SetWindowText(m_strTemp[17]);
	m_SliderCtrl_18.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].usOverloadPWMThreshold);


	//Fault Check
	m_strTemp[18].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucADCFaultCheckPeriod);
	GetDlgItem(IDC_EDIT26)->SetWindowText(m_strTemp[18]);
	m_SliderCtrl_19.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucADCFaultCheckPeriod);

	m_strTemp[19].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucLEDBlinkPeriod);
	GetDlgItem(IDC_EDIT27)->SetWindowText(m_strTemp[19]);
	m_SliderCtrl_20.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucLEDBlinkPeriod);

	m_strTemp[20].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucPacketGarbageCheckPeriod);
	GetDlgItem(IDC_EDIT28)->SetWindowText(m_strTemp[20]);
	m_SliderCtrl_21.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucPacketGarbageCheckPeriod);

	m_strTemp[21].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucStopDetectionPeriod);
	GetDlgItem(IDC_EDIT29)->SetWindowText(m_strTemp[21]);
	m_SliderCtrl_22.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucStopDetectionPeriod);

	m_strTemp[22].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucOverloadDetectionPeriod);
	GetDlgItem(IDC_EDIT30)->SetWindowText(m_strTemp[22]);
	m_SliderCtrl_23.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucOverloadDetectionPeriod);


	//ADC Limit
	m_strTemp[23].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMaxTemperature);
	GetDlgItem(IDC_EDIT31)->SetWindowText(m_strTemp[23]);
	m_SliderCtrl_24.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMaxTemperature);

	m_strTemp[24].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMinVoltage);
	GetDlgItem(IDC_EDIT32)->SetWindowText(m_strTemp[24]);
	m_SliderCtrl_25.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMinVoltage);

	m_strTemp[25].Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMaxVoltage);
	GetDlgItem(IDC_EDIT33)->SetWindowText(m_strTemp[25]);
	m_SliderCtrl_26.SetPos(((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].ucMaxVoltage);

	//Difference
	m_strDifference.Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].cCalibrationDifference_H);
	GetDlgItem(IDC_EDIT34)->SetWindowText(m_strDifference);

	//Difference Offset
	m_strDifference_Offset.Format("%d", ((CHerkulexDlg *)GetParent())->RAM[((CHerkulexDlg *)GetParent())->m_imotor_ID].cCalibrationDifference_L);
	GetDlgItem(IDC_EDIT37)->SetWindowText(m_strDifference_Offset);

	//Baudrate 
	m_iBaudrateValue = ((CHerkulexDlg *)GetParent())->EEP.ucBaudRate;


	if (m_iBaudrateValue == 16) //115,200bps
	{
		m_cmBaudrateList.SetCurSel(0);
	}
	else if (m_iBaudrateValue == 34) //57,600bps
	{
		m_cmBaudrateList.SetCurSel(1);
	}

	//Main UI버튼들의 활성화//
	GetDlgItem(IDC_BUTTON41)->EnableWindow(TRUE);
}


void CParameterDlg::OnCbnSelchangeCombo3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnBnClickedButton41()
{
	//Save Parameter Data
	UpdateData();

	//((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write_ALL();
	
	//////////////////////////////////////RAM & EEP MAP Write//////////////////////////
	//Max Position
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MAX_POSITION, m_uiValue1);
	Sleep(10);
	//Min Position
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MIN_POSITION, m_uiValue2);
	Sleep(10);
	//Position Kp
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_POSITION_KP, m_uiValue3);
	Sleep(10);
	//Position Kd
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_POSITION_KD, m_uiValue4);
	Sleep(10);
	//Position Ki
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_POSITION_KI, m_uiValue5);
	Sleep(10);
	//Position Feedforward 1st Gain
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_POSITION_FEEDFORWARD_1ST_GAIN, m_uiValue6);
	Sleep(10);
	////Position Feedforward 2nd Gain
	//Velocity KP Gain
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_POSITION_FEEDFORWARD_2ND_GAIN, m_uiValue7);
	Sleep(10);
	//Velocity KD Gain
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_VELOCITY_KD, m_uiValue28);
	Sleep(10);
	//Velocity KI Gain
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_VELOCITY_KI, m_uiValue29);
	Sleep(10);
	//Acceleration Ratio
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_ACCELERATION_RATIO, m_uiValue8);
	Sleep(10);
	//Max Acceleration Time
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MAX_ACCELERATION_TIME, m_uiValue9);
	Sleep(10);
	//Dead Zone
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_DEAD_ZONE, m_uiValue10);
	Sleep(10);
	//Saturator Offset
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_SATURATOR_OFFSET, m_uiValue11);
	Sleep(10);
	//Saturator Slope
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_SATURATOR_SLOPE, m_uiValue12);
	Sleep(10);
	//Stop Threshold
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_STOP_THRESHOLD, m_uiValue13);
	Sleep(10);
	//Inposition Margin
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_INPOSITION_MARGIN, m_uiValue14);
	Sleep(10);
	//PWM Offset
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_PWM_OFFSET, m_uiValue15);
	Sleep(10);
	//Min PWM
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MIN_PWM, m_uiValue16);
	Sleep(10);
	//Max PWM
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MAX_PWM, m_uiValue17);
	Sleep(10);
	//Overload PWM Threshold
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_OVERLOAD_PWM_THRESHOLD, m_uiValue18);
	Sleep(10);
	//ADC Fault Check
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_ADC_FAULT_CHECK_PERIOD, m_uiValue19);
	Sleep(10);
	//LED Blink Peroid
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_LED_BLINK_PERIOD, m_uiValue20);
	Sleep(10);
	//Packet Garbage
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_PACKET_GARBAGE_CHECK_PERIOD, m_uiValue21);
	Sleep(10);
	//Stop Detection
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_STOP_DETECTION_PERIOD, m_uiValue22);
	Sleep(10);
	//Overload Detection
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_OVELOAD_DETECTION_PERIOD, m_uiValue23);
	Sleep(10);
	////Max Temperature
	//((CHerkulexDlg *)GetParent())->RAM_RegisterData_Write(RAM_MAX_TEMPERATURE, m_uiValue24);
	//((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MAX_TEMPERATURE, m_uiValue24);
	//Sleep(2);
	////Min Voltage
	//((CHerkulexDlg *)GetParent())->RAM_RegisterData_Write(RAM_MIN_VOLTAGE, m_uiValue25);
	//((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MIN_VOLTAGE, m_uiValue25);
	//Sleep(2);
	////Max Voltage
	//((CHerkulexDlg *)GetParent())->RAM_RegisterData_Write(RAM_MAX_VOLTAGE, m_uiValue26);
	//((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_MAX_VOLTAGE, m_uiValue26);
	//Sleep(2);
	//Calibration Difference
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_CALIBRATION_DIFFERENCE, m_uiValue27);
	Sleep(10);
	//Calibration Offset
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_RESERVED_5, m_uiValue30);
	Sleep(10);

	//Baudrate Setting //ucBaudRate 4 
	int iIndex = m_cmBaudrateList.GetCurSel();
	if (iIndex == 0)
	{
		((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_BAUD_RATE, 16); //115200
	}
	else
	{
		((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_BAUD_RATE, 34); //57600
	}
	

}


void CParameterDlg::OnBnClickedButton39()
{
	// Calibration Setting
	UpdateData();

	//Calibration Difference
	//RAM Write
	((CHerkulexDlg *)GetParent())->RAM_RegisterData_Write(RAM_CALIBRATION__DIFFERENCE_H, m_uiValue27);
	Sleep(10);
	//EEP Write
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_CALIBRATION_DIFFERENCE, m_uiValue27);
	Sleep(10);
}

void CParameterDlg::OnBnClickedButton42()
{
	// Calibration Offset Setting
	UpdateData();

	//Calibration Offset
	//RAM Write
	((CHerkulexDlg *)GetParent())->RAM_RegisterData_Write(RAM_CALIBRATION__DIFFERENCE_L, m_uiValue30); ////RAM_CALIBRATION_OFFSET = 45,	// DRS-0102, DRS-0202 only
	Sleep(10);
	//EEP Write
	((CHerkulexDlg *)GetParent())->EEP_RegisterData_Write(EEP_RESERVED_6, m_uiValue30); //EEP_CALIBRATION_OFFSET = 51, // DRS-0102, DRS-0202 only
	Sleep(10);
}

void CParameterDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit10()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit11()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit12()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit13()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit14()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit15()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit16()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit17()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit18()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit19()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit20()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit21()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit22()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit23()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit24()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit25()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit26()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit27()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit28()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit29()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit30()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit31()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit32()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit33()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit34()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit35()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnEnChangeEdit36()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CParameterDlg::OnNMCustomdrawSlider28(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnNMCustomdrawSlider29(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CParameterDlg::OnEnChangeEdit37()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



void CParameterDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ex_bFlagModal_Parameter = false;

	DestroyWindow();
}


void CParameterDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//delete this;
}


void CParameterDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	OnDestroy();


	CDialogEx::OnClose();
}


void CParameterDlg::OnBnClickedButton43()
{
	UpdateData();

	//CALSET Command
	((CHerkulexDlg*)GetParent())->CALSET(((CHerkulexDlg*)GetParent())->m_imotor_ID);

}


BOOL CParameterDlg::PreTranslateMessage(MSG* pMsg)
{
	// 엔터키 입력 확인//
	UpdateData();

	if (pMsg->message == WM_KEYDOWN)
	{
			int nFocusCtrl = GetFocus()->GetDlgCtrlID();

			switch (nFocusCtrl)
			{
			case 1008:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_MAX_POSITION, m_uiValue1);
				break;
			case 1009:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_MIN_POSITION, m_uiValue2);
				break;
			case 1010:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_POSITION_KP, m_uiValue3);
				break;
			case 1011:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_POSITION_KD, m_uiValue4);
				break;
			case 1012:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_POSITION_KI, m_uiValue5);
				break;
			case 1013:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_POSITION_FEEDFORWARD_1ST_GAIN, m_uiValue6);
				break;
			case 1014:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_POSITION_FEEDFORWARD_2ND_GAIN, m_uiValue7);
				break;
			case 1061:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_VELOCITY_KD, m_uiValue28);
				break;
			case 1063:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_VELOCITY_KI, m_uiValue29);
				break;
			case 1015:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_ACCELERATION_RATIO, m_uiValue8);
				break;
			case 1016:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_MAX_ACCELERATION_TIME, m_uiValue9);
				break;
			case 1017:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_DEAD_ZONE, m_uiValue10);
				break;
			case 1018:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_SATURATOR_OFFSET, m_uiValue11);
				break;
			case 1019:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_SATURATOR_SLOPE, m_uiValue12);
				break;
			case 1020:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_STOP_THRESHOLD, m_uiValue13);
				break;
			case 1021:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_INPOSITION_MARGIN, m_uiValue14);
				break;
			case 1022:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_PWM_OFFSET, m_uiValue15);
				break;
			case 1038:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_MIN_PWM, m_uiValue16);
				break;
			case 1040:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_MAX_PWM, m_uiValue17);
				break;
			case 1042:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_OVERLOAD_PWM_THRESHOLD, m_uiValue18);
				break;
			case 1044:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_ADC_FAULT_CHECK_PERIOD, m_uiValue19);
				break;
			case 1045:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_LED_BLINK_PERIOD, m_uiValue20);
				break;
			case 1048:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_PACKET_GARBAGE_CHECK_PERIOD, m_uiValue21);
				break;
			case 1049:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_STOP_DETECTION_PERIOD, m_uiValue22);
				break;
			case 1052:
				((CHerkulexDlg*)GetParent())->RAM_RegisterData_Write(RAM_OVELOAD_DETECTION_PERIOD, m_uiValue23);
				break;
			default:
				break;
			}
	
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
