// CMotorTest.cpp: 구현 파일
//

#include "stdafx.h"
#include "Herkulex.h"
#include "CMotorTest.h"
#include "afxdialogex.h"
#include "HerkulexDlg.h"


double m_dZooming2 = 1.0;
int			m_iZoomData2 = 0;

double m_dNewScale = 0.0;
double m_dNewScale1 = 0.0;
double m_dOld_DesiredVelocity = 0.0;

bool bCheckView[4] = { false, };

CButton *pCheckBox_ActualPose;
CButton *pCheckBox_CommandPose;
CButton *pCheckBox_PWM;
CButton *pCheckBox_DesiredVelocity;

int		m_iZoom = 0;

CString strMSB = _T(" ");
CString strLSB = _T(" ");
CString strValue = _T(" ");
int iValue = 0;

// CMotorTest 대화 상자
double m_dGraphData2[4]; //Graph Display Data//

int m_iRGB_SUM_A = 0;
int m_iRGB_SUM_B = 0;
int m_iRGB_SUM_C = 0;

BOOL m_bFlag_Play_Move = false;
int  m_iCountTime = 0;
int  m_iCnt = 0;

BOOL m_bCheckMode = true;
BOOL m_bCheckMulti = false;

int  m_iCheckJOG = 0;
int  m_iProfileMode = 1; //S자프로파일(1) 과 사다리꼴프로파일(0)

IMPLEMENT_DYNAMIC(CMotorTest, CDialogEx)

CMotorTest::CMotorTest(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOTORTEST, pParent)
	, m_iPOES_A(124)
	, m_iPOES_B(512)
	, m_iPOES_C(900)
	, m_iPlaytime_A(60)
	, m_iPlaytime_B(60)
	, m_iPlaytime_C(60)
	, m_iErrorMargin(0)
	, m_iPoseError(0)
	, m_iSamplingTime(1000)
	, m_TEST_ID(0)
	, m_rMove_Sel(0)
	, m_rJOG_Sel(0)
	, m_iTurn_A(0)
	, m_iTurn_B(0)
	, m_iTurn_C(0)
	, m_dScale(0)
{

}

CMotorTest::~CMotorTest()
{
	
}

void CMotorTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_POS1, m_iPOES_A);
	DDX_Text(pDX, IDC_POS2, m_iPOES_B);
	DDX_Text(pDX, IDC_POS3, m_iPOES_C);
	DDX_Text(pDX, IDC_PLAYTIME1, m_iPlaytime_A);
	DDX_Text(pDX, IDC_PLAYTIME2, m_iPlaytime_B);
	DDX_Text(pDX, IDC_PLAYTIME3, m_iPlaytime_C);
	DDX_Text(pDX, IDC_EDIT3, m_iErrorMargin);
	DDX_Text(pDX, IDC_EDIT6, m_iPoseError);
	DDX_Text(pDX, IDC_EDIT7, m_iSamplingTime);
	DDX_Text(pDX, IDC_EDIT4, m_TEST_ID);
	DDX_Radio(pDX, IDC_PMOVE, m_rMove_Sel);
	DDX_Radio(pDX, IDC_SJOG, m_rJOG_Sel);
	DDX_Text(pDX, IDC_TURN1, m_iTurn_A);
	DDX_Text(pDX, IDC_TURN2, m_iTurn_B);
	DDX_Text(pDX, IDC_TURN3, m_iTurn_C);
	DDX_Text(pDX, IDC_EDIT1, m_dScale);
	DDX_Control(pDX, IDC_ZOOM2, m_Slider_Zoom2);
}


BEGIN_MESSAGE_MAP(CMotorTest, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CMotorTest::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON10, &CMotorTest::OnBnClickedButton10)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON2, &CMotorTest::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMotorTest::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON16, &CMotorTest::OnBnClickedButton16)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK13, &CMotorTest::OnBnClickedCheck13)
	ON_BN_CLICKED(IDC_CHECK14, &CMotorTest::OnBnClickedCheck14)
	ON_BN_CLICKED(IDC_CHECK15, &CMotorTest::OnBnClickedCheck15)
	ON_BN_CLICKED(IDC_CHECK16, &CMotorTest::OnBnClickedCheck16)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON4, &CMotorTest::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMotorTest::OnBnClickedButton5)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_TURN1, &CMotorTest::OnEnChangeTurn1)
	ON_EN_CHANGE(IDC_TURN2, &CMotorTest::OnEnChangeTurn2)
	ON_EN_CHANGE(IDC_TURN3, &CMotorTest::OnEnChangeTurn3)
	ON_EN_CHANGE(IDC_EDIT1, &CMotorTest::OnEnChangeEdit1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ZOOM2, &CMotorTest::OnNMCustomdrawZoom2)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CMotorTest 메시지 처리기


BOOL CMotorTest::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	//Graph Display//
	CRect rtGraph2;
	GetDlgItem(IDC_STATIC_RT_GRAPH2)->GetWindowRect(rtGraph2);
	ScreenToClient(rtGraph2);

	_rtGraph2 = new COScopeCtrl(4);		//4개의 그래프 예약
	_rtGraph2->Create(WS_VISIBLE | WS_CHILD, rtGraph2, this, IDC_STATIC_RT_GRAPH2);
	//Max Position에 따라서 Y Scale변경
	_rtGraph2->SetRanges(-ex_dMaxPosition, ex_dMaxPosition);
	_rtGraph2->autofitYscale = true;
	_rtGraph2->SetYUnits("Data");
	_rtGraph2->SetXUnits("Time");
	_rtGraph2->SetLegendLabel("Actual Pose", 0);
	_rtGraph2->SetLegendLabel("Desired Trajectory Pose", 1);
	_rtGraph2->SetLegendLabel("Current", 2);
	_rtGraph2->SetLegendLabel("DesiredVelocity", 3);
	_rtGraph2->SetPlotColor(RED, 0);
	_rtGraph2->SetPlotColor(GREEN, 1);
	_rtGraph2->SetPlotColor(BLUE, 2);
	_rtGraph2->SetPlotColor(YELLOW, 3);
	_rtGraph2->InvalidateCtrl();

	m_TEST_ID = ((CHerkulexDlg *)GetParent())->m_imotor_ID; //Scan후 선택한 ID 계승

	//Model별로 Test위치값 변경
	if (ex_DRS_Model_Num <= 5) //01~02~03
	{
		m_iPOES_A = 124;
		m_iPOES_B = 512;
		m_iPOES_C = 900;
	}
	else if (ex_DRS_Model_Num == 6 || ex_DRS_Model_Num == 8) //0401, 0601
	{
		m_iPOES_A = 42;
		m_iPOES_B = 1024;
		m_iPOES_C = 2004;

	}
	else //0402, 0602
	{
		m_iPOES_A = 10627;
		m_iPOES_B = 16384;
		m_iPOES_C = 22129;
	}

	//Grapth scale control
	m_Slider_Zoom2.SetRange(-100, 100);
	m_Slider_Zoom2.SetLineSize(1);
	m_Slider_Zoom2.SetPageSize(1);
	m_Slider_Zoom2.SetPos(1);

	//03시리즈 인지 확인하여 Window수정//
	switch (ex_DRS_Model_Num)
	{
	case 0:
		GetDlgItem(IDC_BJOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_BJOG)->ShowWindow(0);
		GetDlgItem(IDC_BJOG2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BJOG2)->ShowWindow(0);
		GetDlgItem(IDC_MS1)->EnableWindow(FALSE);
		GetDlgItem(IDC_MS1)->ShowWindow(0);
		GetDlgItem(IDC_MI2)->EnableWindow(FALSE);
		GetDlgItem(IDC_MI2)->ShowWindow(0);
		break;
	case 1:
		GetDlgItem(IDC_BJOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_BJOG)->ShowWindow(0);
		GetDlgItem(IDC_BJOG2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BJOG2)->ShowWindow(0);
		GetDlgItem(IDC_MS1)->EnableWindow(FALSE);
		GetDlgItem(IDC_MS1)->ShowWindow(0);
		GetDlgItem(IDC_MI2)->EnableWindow(FALSE);
		GetDlgItem(IDC_MI2)->ShowWindow(0);
		break;
	case 2:
		GetDlgItem(IDC_BJOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_BJOG)->ShowWindow(0);
		GetDlgItem(IDC_BJOG2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BJOG2)->ShowWindow(0);
		GetDlgItem(IDC_MS1)->EnableWindow(FALSE);
		GetDlgItem(IDC_MS1)->ShowWindow(0);
		GetDlgItem(IDC_MI2)->EnableWindow(FALSE);
		GetDlgItem(IDC_MI2)->ShowWindow(0);
		break;
	case 3:
		GetDlgItem(IDC_BJOG)->EnableWindow(TRUE);
		GetDlgItem(IDC_BJOG)->ShowWindow(1);
		GetDlgItem(IDC_BJOG2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BJOG2)->ShowWindow(1);
		GetDlgItem(IDC_MS1)->EnableWindow(TRUE);
		GetDlgItem(IDC_MS1)->ShowWindow(1);
		GetDlgItem(IDC_MI2)->EnableWindow(TRUE);
		GetDlgItem(IDC_MI2)->ShowWindow(1);
		break;
	case 4:
		GetDlgItem(IDC_BJOG)->EnableWindow(TRUE);
		GetDlgItem(IDC_BJOG)->ShowWindow(1);
		GetDlgItem(IDC_BJOG2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BJOG2)->ShowWindow(1);
		GetDlgItem(IDC_MS1)->EnableWindow(TRUE);
		GetDlgItem(IDC_MS1)->ShowWindow(1);
		GetDlgItem(IDC_MI2)->EnableWindow(TRUE);
		GetDlgItem(IDC_MI2)->ShowWindow(1);
		break;
	case 5:
		GetDlgItem(IDC_BJOG)->EnableWindow(TRUE);
		GetDlgItem(IDC_BJOG)->ShowWindow(1);
		GetDlgItem(IDC_BJOG2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BJOG2)->ShowWindow(1);
		GetDlgItem(IDC_MS1)->EnableWindow(TRUE);
		GetDlgItem(IDC_MS1)->ShowWindow(1);
		GetDlgItem(IDC_MI2)->EnableWindow(TRUE);
		GetDlgItem(IDC_MI2)->ShowWindow(1);
		break;
	case 6:
		GetDlgItem(IDC_BJOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_BJOG)->ShowWindow(0);
		GetDlgItem(IDC_BJOG2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BJOG2)->ShowWindow(0);
		GetDlgItem(IDC_MS1)->EnableWindow(FALSE);
		GetDlgItem(IDC_MS1)->ShowWindow(0);
		GetDlgItem(IDC_MI2)->EnableWindow(FALSE);
		GetDlgItem(IDC_MI2)->ShowWindow(0);
		break;
	case 7:
		GetDlgItem(IDC_BJOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_BJOG)->ShowWindow(0);
		GetDlgItem(IDC_BJOG2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BJOG2)->ShowWindow(0);
		GetDlgItem(IDC_MS1)->EnableWindow(FALSE);
		GetDlgItem(IDC_MS1)->ShowWindow(0);
		GetDlgItem(IDC_MI2)->EnableWindow(FALSE);
		GetDlgItem(IDC_MI2)->ShowWindow(0);
		break;
	case 8:
		GetDlgItem(IDC_BJOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_BJOG)->ShowWindow(0);
		GetDlgItem(IDC_BJOG2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BJOG2)->ShowWindow(0);
		GetDlgItem(IDC_MS1)->EnableWindow(FALSE);
		GetDlgItem(IDC_MS1)->ShowWindow(0);
		GetDlgItem(IDC_MI2)->EnableWindow(FALSE);
		GetDlgItem(IDC_MI2)->ShowWindow(0);
		break;
	case 9:
		GetDlgItem(IDC_BJOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_BJOG)->ShowWindow(0);
		GetDlgItem(IDC_BJOG2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BJOG2)->ShowWindow(0);
		GetDlgItem(IDC_MS1)->EnableWindow(FALSE);
		GetDlgItem(IDC_MS1)->ShowWindow(0);
		GetDlgItem(IDC_MI2)->EnableWindow(FALSE);
		GetDlgItem(IDC_MI2)->ShowWindow(0);
		break;
	}



	UpdateData(FALSE);

	//시작 시 Position Mode로 Radio button 강제Check//
	CButton* pButton = (CButton*)GetDlgItem(IDC_PMOVE);
	pButton->SetCheck(true);

	//시작 시 J_JOG Mode로 Radio button 강제Check//
	CButton* pButton1 = (CButton*)GetDlgItem(IDC_SJOG);
	pButton1->SetCheck(true);

	//시작 시 사다리 프로파일 모드로 Radio button 강제Check//
	CButton* pButton2 = (CButton*)GetDlgItem(IDC_PROFILE2);
	pButton2->SetCheck(true);


	//View Cehck //
	pCheckBox_ActualPose = (CButton*)GetDlgItem(IDC_CHECK13);
	pCheckBox_CommandPose = (CButton*)GetDlgItem(IDC_CHECK14);
	pCheckBox_PWM = (CButton*)GetDlgItem(IDC_CHECK15);
	pCheckBox_DesiredVelocity = (CButton*)GetDlgItem(IDC_CHECK16);

	pCheckBox_ActualPose->SetCheck(true);
	pCheckBox_CommandPose->SetCheck(true);

	if (ex_DRS_Model_Num == 3 || ex_DRS_Model_Num == 4 || ex_DRS_Model_Num == 5)
	{
		GetDlgItem(IDC_CHECK15)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK15)->ShowWindow(1);

		pCheckBox_PWM->SetCheck(true);
	}
	else
	{

		GetDlgItem(IDC_CHECK15)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK15)->ShowWindow(0);
	}

	pCheckBox_DesiredVelocity->SetCheck(true);

	SetTimer(5, 10, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMotorTest::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 5)
	{
		if (m_bFlag_Play_Move)
		{
			if (m_iCountTime >= (m_iSamplingTime / 10.0))
			{
				m_iCountTime = 0;

				//Select Mode
				if (IsDlgButtonChecked(IDC_PMOVE))
				{
					//Position Mode
					m_bCheckMode = true;
				}
				else
				{
					//Velocity Mode
					m_bCheckMode = false;
				}

				//Select Profile Mode
				if (IsDlgButtonChecked(IDC_PROFILE1))
				{
					//S자 프로파일
					m_iProfileMode = 1;
				}
				else
				{
					//사다리꼴 프로파일
					m_iProfileMode = 0;
				}


				//Select JOG Mode
				if (IsDlgButtonChecked(IDC_SJOG))
				{
					m_iCheckJOG = 0; //S_JOG Mode
				}
				if (IsDlgButtonChecked(IDC_IJOG))
				{
					m_iCheckJOG = 1; //I_JOG Mode
				}
				if (IsDlgButtonChecked(IDC_BJOG))
				{
					m_iCheckJOG = 2; //B_JOG Mode
				}

				//Play Move A, B ,C Pose
				switch (m_iCnt)
				{
				case 0:
					A_POSE_MOVE();
					GetDlgItem(IDC_STATIC_A)->SetWindowTextA(_T("A POSE..."));
					GetDlgItem(IDC_STATIC_B)->SetWindowTextA(_T(" - "));
					GetDlgItem(IDC_STATIC_C)->SetWindowTextA(_T(" - "));
					break;
				case 1:
					B_POSE_MOVE();
					GetDlgItem(IDC_STATIC_A)->SetWindowTextA(_T(" - "));
					GetDlgItem(IDC_STATIC_B)->SetWindowTextA(_T("B POSE..."));
					GetDlgItem(IDC_STATIC_C)->SetWindowTextA(_T(" - "));
					break;
				case 2:
					C_POSE_MOVE();
					GetDlgItem(IDC_STATIC_A)->SetWindowTextA(_T(" - "));
					GetDlgItem(IDC_STATIC_B)->SetWindowTextA(_T(" - "));
					GetDlgItem(IDC_STATIC_C)->SetWindowTextA(_T("C POSE..."));
					break;
				default:
					break;
				}

			}
			else
			{
				m_iCountTime++;
			}
		}

		//Error Display////////////////////////////////////////
		m_iErrorMargin = ((CHerkulexDlg *)GetParent())->RAM[m_TEST_ID].ucInpositionMargin;
		m_strErrorMargin.Format("%d", m_iErrorMargin);
		GetDlgItem(IDC_EDIT3)->SetWindowText(m_strErrorMargin);
		m_iPoseError = (((CHerkulexDlg *)GetParent())->RAM[m_TEST_ID].usAbsolutePosition) - (((CHerkulexDlg *)GetParent())->RAM[m_TEST_ID].usAbsoluteDesiredTrajectoryPosition);
		m_strPoseError.Format("%d", m_iPoseError);
		GetDlgItem(IDC_EDIT6)->SetWindowText(m_strPoseError);


		//Graph Display///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (!bCheckView[0])
		{
			//m_dGraphData2[0] = (double)((CHerkulexDlg *)GetParent())->RAM[m_TEST_ID].usCalibratedPosition; //usAbsolutePosition;
			switch (ex_DRS_Model_Num)
			{
			case 0: //0101
				m_dGraphData2[0] = (double)(((CHerkulexDlg *)GetParent())->RAM[m_TEST_ID].usCalibratedPosition & 0x1FFF);
				break;
			case 1: //0102
				m_dGraphData2[0] = (double)(((CHerkulexDlg *)GetParent())->RAM[m_TEST_ID].usCalibratedPosition & 0x7FFF);
				break;
			case 2: //0201
				m_dGraphData2[0] = (double)(((CHerkulexDlg *)GetParent())->RAM[m_TEST_ID].usCalibratedPosition & 0x1FFF);
				break;
			case 3: //0301
				m_dGraphData2[0] = (double)((CHerkulexDlg *)GetParent())->RAM[m_TEST_ID].usCalibratedPosition;
				break;
			case 4: //0302
				m_dGraphData2[0] = (double)((CHerkulexDlg *)GetParent())->RAM[m_TEST_ID].usCalibratedPosition;
				break;
			case 5: //0303
				m_dGraphData2[0] = (double)((CHerkulexDlg *)GetParent())->RAM[m_TEST_ID].usCalibratedPosition;
				break;
			case 6: //0401
				m_dGraphData2[0] = (double)(((CHerkulexDlg *)GetParent())->RAM[m_TEST_ID].usCalibratedPosition & 0x7FFF);
				break;
			case 7: //0402
				m_dGraphData2[0] = (double)(((CHerkulexDlg *)GetParent())->RAM[m_TEST_ID].usCalibratedPosition & 0x7FFF);
				break;
			case 8: //0601
				m_dGraphData2[0] = (double)(((CHerkulexDlg *)GetParent())->RAM[m_TEST_ID].usCalibratedPosition & 0x7FFF);
				break;
			case 9: //0602
				m_dGraphData2[0] = (double)(((CHerkulexDlg *)GetParent())->RAM[m_TEST_ID].usCalibratedPosition & 0x7FFF);
				break;
			}


		}
		else
			m_dGraphData2[0] = 0.0;

		if (!bCheckView[1])
		{
			//m_dGraphData2[1] = (double)((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].usAbsoluteDesiredTrajectoryPosition;
			switch (ex_DRS_Model_Num)
			{
			case 0: //0101
				m_dGraphData2[1] = (double)(((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].usAbsoluteDesiredTrajectoryPosition & 0x1FFF);
				break;
			case 1: //0102
				m_dGraphData2[1] = (double)(((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].usAbsoluteDesiredTrajectoryPosition & 0x7FFF);
				break;
			case 2: //0201
				m_dGraphData2[1] = (double)(((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].usAbsoluteDesiredTrajectoryPosition & 0x1FFF);
				break;
			case 3: //0301
				m_dGraphData2[1] = (double)((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].usAbsoluteDesiredTrajectoryPosition;
				break;
			case 4: //0302
				m_dGraphData2[1] = (double)((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].usAbsoluteDesiredTrajectoryPosition;
				break;
			case 5: //0303
				m_dGraphData2[1] = (double)((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].usAbsoluteDesiredTrajectoryPosition;
				break;
			case 6: //0401
				m_dGraphData2[1] = (double)(((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].usAbsoluteDesiredTrajectoryPosition & 0x7FFF);
				break;
			case 7: //0402
				m_dGraphData2[1] = (double)(((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].usAbsoluteDesiredTrajectoryPosition & 0x7FFF);
				break;
			case 8: //0601
				m_dGraphData2[1] = (double)(((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].usAbsoluteDesiredTrajectoryPosition & 0x7FFF);
				break;
			case 9: //0602
				m_dGraphData2[1] = (double)(((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].usAbsoluteDesiredTrajectoryPosition & 0x7FFF);
				break;
			}
		}
		else
			m_dGraphData2[1] = 0.0;

		if (!bCheckView[2])
		{
			//m_dGraphData2[2] = (double)((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].usPWM;
			//Current View
			//TRACE("ucReserved7 = %02x, ucReserved8 = %02x", ((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].ucReserved7, ((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].ucReserved8);
			strMSB.Format("%02x", ((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].ucReserved7);
			strLSB.Format("%02x", ((CHerkulexDlg*)GetParent())->RAM[m_TEST_ID].ucReserved8);
			strValue = strLSB + strMSB;
			//TRACE("strValue = %s", strValue);
			iValue = strtol(strValue, NULL, 16);
			//TRACE("iValue = %d", iValue);
			m_dGraphData2[2] = (double)iValue;
		}
		else
			m_dGraphData2[2] = 0.0;

		if (!bCheckView[3])
		{
			m_dGraphData2[3] = (double)((CHerkulexDlg *)GetParent())->RAM[m_TEST_ID].sDesiredVelocity;

			//그래프 스케일 조정//////////////////////////////////////////////////////////////////////////////////////
			//m_dNewScale1 = (m_dOld_DesiredVelocity > m_dGraphData2[3] ? m_dOld_DesiredVelocity : m_dGraphData2[3]);

			//m_dNewScale = (ex_dMaxPosition > m_dNewScale1 ? ex_dMaxPosition : m_dNewScale1);

			//_rtGraph2->SetRanges(-m_dNewScale, m_dNewScale);

			//if (m_dOld_DesiredVelocity < m_dGraphData2[3])
			//	m_dOld_DesiredVelocity = m_dGraphData2[3];
			//////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		else
		{
			m_dGraphData2[3] = 0.0;
			//_rtGraph2->SetRanges(-ex_dMaxPosition, ex_dMaxPosition);
		}
		

		_rtGraph2->AppendPoints(m_dGraphData2);

		//Mode Select Display//
		if (ex_bFlag_ServoON)
		{
			GetDlgItem(IDC_PMOVE)->EnableWindow(FALSE);
			GetDlgItem(IDC_VMOVE)->EnableWindow(FALSE);

			GetDlgItem(IDC_SJOG)->EnableWindow(FALSE);
			GetDlgItem(IDC_IJOG)->EnableWindow(FALSE);
			GetDlgItem(IDC_BJOG)->EnableWindow(FALSE);
			GetDlgItem(IDC_BJOG2)->EnableWindow(FALSE);
			GetDlgItem(IDC_MS1)->EnableWindow(FALSE);
			GetDlgItem(IDC_MI2)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDC_PMOVE)->EnableWindow(TRUE);
			GetDlgItem(IDC_VMOVE)->EnableWindow(TRUE);

			GetDlgItem(IDC_SJOG)->EnableWindow(TRUE);
			GetDlgItem(IDC_IJOG)->EnableWindow(TRUE);
			GetDlgItem(IDC_BJOG)->EnableWindow(TRUE);
			GetDlgItem(IDC_BJOG2)->EnableWindow(TRUE);
			GetDlgItem(IDC_MS1)->EnableWindow(TRUE);
			GetDlgItem(IDC_MI2)->EnableWindow(TRUE);
		}

	}

	CDialogEx::OnTimer(nIDEvent);
}




void CMotorTest::OnBnClickedButton1()
{
	// Start
	UpdateData();

	//Servo On//
	((CHerkulexDlg *)GetParent())->Herkulex_Servo_Enable(m_TEST_ID, 1);

	m_bFlag_Play_Move = true;

}


void CMotorTest::OnBnClickedButton10()
{
	// Stop
	UpdateData();

	//Servo Off//
	((CHerkulexDlg *)GetParent())->Herkulex_Servo_Enable(m_TEST_ID, 0);

	m_bFlag_Play_Move = false;

	GetDlgItem(IDC_STATIC_A)->SetWindowTextA(_T("A POSE"));
	GetDlgItem(IDC_STATIC_B)->SetWindowTextA(_T("B POSE"));
	GetDlgItem(IDC_STATIC_C)->SetWindowTextA(_T("C POSE"));

}



void CMotorTest::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	OnBnClickedButton10();

	KillTimer(5);

	//delete _rtGraph2;

	_rtGraph2->Reset();

	//ex_bFlagMainUI = true;
	ex_bFlagModal_Test = false;

	DestroyWindow();
}


void CMotorTest::SetLED()
{
	int m_iRGB_Color_A[3] = { 0, };
	int m_iRGB_Color_B[3] = { 0, };
	int m_iRGB_Color_C[3] = { 0, };

	////A_POSE////////////////////////////////////////////////////////////////////////
	CButton *pChecBox1A = (CButton*)GetDlgItem(IDC_CHECK1);
	CButton *pChecBox2A = (CButton*)GetDlgItem(IDC_CHECK5);
	CButton *pChecBox3A = (CButton*)GetDlgItem(IDC_CHECK6);

	if (m_iLEDCheck1[0] = pChecBox1A->GetCheck()) //GREEN Enable
		m_iRGB_Color_A[0] = 1;
	else
		m_iRGB_Color_A[0] = 0;

	if (m_iLEDCheck1[1] = pChecBox2A->GetCheck()) //BLUE Enable
		m_iRGB_Color_A[1] = 2;
	else
		m_iRGB_Color_A[1] = 0;

	if (m_iLEDCheck1[2] = pChecBox3A->GetCheck()) //RED Enable
		m_iRGB_Color_A[2] = 4;
	else
		m_iRGB_Color_A[2] = 0;

	m_iRGB_SUM_A = m_iRGB_Color_A[0] + m_iRGB_Color_A[1] + m_iRGB_Color_A[2];

	////B_POSE////////////////////////////////////////////////////////////////////////
	CButton *pChecBox1B = (CButton*)GetDlgItem(IDC_CHECK7);
	CButton *pChecBox2B = (CButton*)GetDlgItem(IDC_CHECK8);
	CButton *pChecBox3B = (CButton*)GetDlgItem(IDC_CHECK9);

	if (m_iLEDCheck2[0] = pChecBox1B->GetCheck()) //GREEN Enable
		m_iRGB_Color_B[0] = 1;
	else
		m_iRGB_Color_B[0] = 0;

	if (m_iLEDCheck2[1] = pChecBox2B->GetCheck()) //BLUE Enable
		m_iRGB_Color_B[1] = 2;
	else
		m_iRGB_Color_B[1] = 0;

	if (m_iLEDCheck2[2] = pChecBox3B->GetCheck()) //RED Enable
		m_iRGB_Color_B[2] = 4;
	else
		m_iRGB_Color_B[2] = 0;

	m_iRGB_SUM_B = m_iRGB_Color_B[0] + m_iRGB_Color_B[1] + m_iRGB_Color_B[2];

	////C_POSE////////////////////////////////////////////////////////////////////////
	CButton *pChecBox1C = (CButton*)GetDlgItem(IDC_CHECK10);
	CButton *pChecBox2C = (CButton*)GetDlgItem(IDC_CHECK11);
	CButton *pChecBox3C = (CButton*)GetDlgItem(IDC_CHECK12);

	if (m_iLEDCheck3[0] = pChecBox1C->GetCheck()) //GREEN Enable
		m_iRGB_Color_C[0] = 1;
	else
		m_iRGB_Color_C[0] = 0;

	if (m_iLEDCheck3[1] = pChecBox2C->GetCheck()) //BLUE Enable
		m_iRGB_Color_C[1] = 2;
	else
		m_iRGB_Color_C[1] = 0;

	if (m_iLEDCheck3[2] = pChecBox3C->GetCheck()) //RED Enable
		m_iRGB_Color_C[2] = 4;
	else
		m_iRGB_Color_C[2] = 0;

	m_iRGB_SUM_C = m_iRGB_Color_C[0] + m_iRGB_Color_C[1] + m_iRGB_Color_C[2];

}

void CMotorTest::A_POSE_MOVE()
{
	SetLED();
	//Select Mode
	if (IsDlgButtonChecked(IDC_PMOVE))
	{
		//Position Mode
		m_bCheckMode = true;
	}
	else
	{
		//Velocity Mode
		m_bCheckMode = false;
	}

	//Select Profile Mode
	if (IsDlgButtonChecked(IDC_PROFILE1))
	{
		//S자 프로파일
		m_iProfileMode = 1;
	}
	else
	{
		//사다리꼴 프로파일
		m_iProfileMode = 0;
	}

	//Select JOG Mode
	if (IsDlgButtonChecked(IDC_SJOG))
	{
		m_iCheckJOG = 0; //S_JOG Mode
	}
	if (IsDlgButtonChecked(IDC_IJOG))
	{
		m_iCheckJOG = 1; //I_JOG Mode
	}
	if (IsDlgButtonChecked(IDC_BJOG))
	{
		m_iCheckJOG = 2; //MS_JOG Mode
		if (IsDlgButtonChecked(IDC_MS1))
			m_bCheckMulti = true;
		else
			m_bCheckMulti = false;
	}
	if (IsDlgButtonChecked(IDC_BJOG2))
	{
		m_iCheckJOG = 3; //MI_JOG Mode
		if (IsDlgButtonChecked(IDC_MI2))
			m_bCheckMulti = true;
		else
			m_bCheckMulti = false;
	}

	//Move Command//
	if (m_bCheckMode)
	{
		((CHerkulexDlg*)GetParent())->Position_Move(m_TEST_ID, m_iRGB_SUM_A, m_iPlaytime_A, m_iPOES_A, m_iCheckJOG, m_iProfileMode, m_bCheckMulti, m_iTurn_A);
	}
	else
	{
		((CHerkulexDlg*)GetParent())->Velocity_Move(m_TEST_ID, m_iRGB_SUM_A, m_iPOES_A, m_iCheckJOG, m_iProfileMode, m_bCheckMulti);
	}
	

	m_iCnt = 1;

}

void CMotorTest::B_POSE_MOVE()
{
	SetLED();
	//Select Mode
	if (IsDlgButtonChecked(IDC_PMOVE))
	{
		//Position Mode
		m_bCheckMode = true;
	}
	else
	{
		//Velocity Mode
		m_bCheckMode = false;
	}

	//Select Profile Mode
	if (IsDlgButtonChecked(IDC_PROFILE1))
	{
		//S자 프로파일
		m_iProfileMode = 1;
	}
	else
	{
		//사다리꼴 프로파일
		m_iProfileMode = 0;
	}

	//Select JOG Mode
	if (IsDlgButtonChecked(IDC_SJOG))
	{
		m_iCheckJOG = 0; //S_JOG Mode
	}
	if (IsDlgButtonChecked(IDC_IJOG))
	{
		m_iCheckJOG = 1; //I_JOG Mode
	}
	if (IsDlgButtonChecked(IDC_BJOG))
	{
		m_iCheckJOG = 2; //MS_JOG Mode
		if (IsDlgButtonChecked(IDC_MS1))
			m_bCheckMulti = true;
		else
			m_bCheckMulti = false;
	}
	if (IsDlgButtonChecked(IDC_BJOG2))
	{
		m_iCheckJOG = 3; //MI_JOG Mode
		if (IsDlgButtonChecked(IDC_MI2))
			m_bCheckMulti = true;
		else
			m_bCheckMulti = false;
	}

	//Move Command//
	if (m_bCheckMode)
		((CHerkulexDlg *)GetParent())->Position_Move(m_TEST_ID, m_iRGB_SUM_B, m_iPlaytime_B, m_iPOES_B, m_iCheckJOG, m_iProfileMode, m_bCheckMulti, m_iTurn_B);
	else
		((CHerkulexDlg *)GetParent())->Velocity_Move(m_TEST_ID, m_iRGB_SUM_B, m_iPOES_B, m_iCheckJOG, m_iProfileMode, m_bCheckMulti);

	m_iCnt = 2;
}

void CMotorTest::C_POSE_MOVE()
{
	SetLED();
	//Select Mode
	if (IsDlgButtonChecked(IDC_PMOVE))
	{
		//Position Mode
		m_bCheckMode = true;
	}
	else
	{
		//Velocity Mode
		m_bCheckMode = false;
	}

	//Select Profile Mode
	if (IsDlgButtonChecked(IDC_PROFILE1))
	{
		//S자 프로파일
		m_iProfileMode = 1;
	}
	else
	{
		//사다리꼴 프로파일
		m_iProfileMode = 0;
	}

	//Select JOG Mode
	if (IsDlgButtonChecked(IDC_SJOG))
	{
		m_iCheckJOG = 0; //S_JOG Mode
	}
	if (IsDlgButtonChecked(IDC_IJOG))
	{
		m_iCheckJOG = 1; //I_JOG Mode
	}
	if (IsDlgButtonChecked(IDC_BJOG))
	{
		m_iCheckJOG = 2; //MS_JOG Mode
		if (IsDlgButtonChecked(IDC_MS1))
			m_bCheckMulti = true;
		else
			m_bCheckMulti = false;
	}
	if (IsDlgButtonChecked(IDC_BJOG2))
	{
		m_iCheckJOG = 3; //MI_JOG Mode
		if (IsDlgButtonChecked(IDC_MI2))
			m_bCheckMulti = true;
		else
			m_bCheckMulti = false;
	}

	//Move Command//
	if (m_bCheckMode)
		((CHerkulexDlg *)GetParent())->Position_Move(m_TEST_ID, m_iRGB_SUM_C, m_iPlaytime_C, m_iPOES_C, m_iCheckJOG, m_iProfileMode, m_bCheckMulti, m_iTurn_C);
	else
		((CHerkulexDlg *)GetParent())->Velocity_Move(m_TEST_ID, m_iRGB_SUM_C, m_iPOES_C, m_iCheckJOG, m_iProfileMode, m_bCheckMulti);
	

	m_iCnt = 0;
}



void CMotorTest::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.


}


void CMotorTest::OnBnClickedButton2()
{
	UpdateData();
	//Servo On//
	((CHerkulexDlg *)GetParent())->Herkulex_Servo_Enable(m_TEST_ID, 1);

	// A Pose Test
	A_POSE_MOVE();

	//m_bFlag_Play_Move = false;

	GetDlgItem(IDC_STATIC_A)->SetWindowTextA(_T("A POSE"));
	GetDlgItem(IDC_STATIC_B)->SetWindowTextA(_T("B POSE"));
	GetDlgItem(IDC_STATIC_C)->SetWindowTextA(_T("C POSE"));

}


void CMotorTest::OnBnClickedButton3()
{
	UpdateData();
	//Servo On//
	((CHerkulexDlg *)GetParent())->Herkulex_Servo_Enable(m_TEST_ID, 1);

	// B Pose Test
	B_POSE_MOVE();

	//m_bFlag_Play_Move = false;

	GetDlgItem(IDC_STATIC_A)->SetWindowTextA(_T("A POSE"));
	GetDlgItem(IDC_STATIC_B)->SetWindowTextA(_T("B POSE"));
	GetDlgItem(IDC_STATIC_C)->SetWindowTextA(_T("C POSE"));

}


void CMotorTest::OnBnClickedButton16()
{
	UpdateData();
	//Servo On//
	((CHerkulexDlg *)GetParent())->Herkulex_Servo_Enable(m_TEST_ID, 1);

	// C Pose Test
	C_POSE_MOVE();

	//m_bFlag_Play_Move = false;

	GetDlgItem(IDC_STATIC_A)->SetWindowTextA(_T("A POSE"));
	GetDlgItem(IDC_STATIC_B)->SetWindowTextA(_T("B POSE"));
	GetDlgItem(IDC_STATIC_C)->SetWindowTextA(_T("C POSE"));

}


HBRUSH CMotorTest::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_CHECK1 || pWnd->GetDlgCtrlID() == IDC_CHECK7 || pWnd->GetDlgCtrlID() == IDC_CHECK10)
	{
		pDC->SetTextColor(GREEN);
		pDC->SetBkMode(DKGRAY_BRUSH);   // static text 배경색
		return (HBRUSH)::GetStockObject(DKGRAY_BRUSH);
	}

	if (pWnd->GetDlgCtrlID() == IDC_CHECK5 || pWnd->GetDlgCtrlID() == IDC_CHECK8 || pWnd->GetDlgCtrlID() == IDC_CHECK11)
	{
		pDC->SetTextColor(BLUE);
		pDC->SetBkMode(DKGRAY_BRUSH);   // static text 배경색
		return (HBRUSH)::GetStockObject(DKGRAY_BRUSH);
	}

	if (pWnd->GetDlgCtrlID() == IDC_CHECK6 || pWnd->GetDlgCtrlID() == IDC_CHECK9 || pWnd->GetDlgCtrlID() == IDC_CHECK12)
	{
		pDC->SetTextColor(RED);
		pDC->SetBkMode(DKGRAY_BRUSH);   // static text 배경색
		return (HBRUSH)::GetStockObject(DKGRAY_BRUSH);
	}


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


void CMotorTest::OnBnClickedCheck13()
{
	// View_Actual Pose
	if (pCheckBox_ActualPose->GetCheck())
		bCheckView[0] = false;
	else
		bCheckView[0] = true;

}


void CMotorTest::OnBnClickedCheck14()
{
	// View_Command Pose
	if (pCheckBox_CommandPose->GetCheck())
		bCheckView[1] = false;
	else
		bCheckView[1] = true;

}


void CMotorTest::OnBnClickedCheck15()
{
	// View_PWM
	if (pCheckBox_PWM->GetCheck())
		bCheckView[2] = false;
	else
		bCheckView[2] = true;

}


void CMotorTest::OnBnClickedCheck16()
{
	// View_DesiredVelocity
	if (pCheckBox_DesiredVelocity->GetCheck())
		bCheckView[3] = false;
	else
		bCheckView[3] = true;
}



void CMotorTest::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nID == SC_CLOSE)
	{
		OnDestroy();

		//delete _rtGraph2;

		//ex_bFlagMainUI = true;
	}

	CDialogEx::OnSysCommand(nID, lParam);
}


void CMotorTest::OnBnClickedButton4()
{
	UpdateData();

	// Zoom Out
	m_Slider_Zoom2.SetPos(1);
	_rtGraph2->SetRanges(-ex_dMaxPosition, ex_dMaxPosition);


}


void CMotorTest::OnBnClickedButton5()
{
	UpdateData();

	// Zoom In


}


void CMotorTest::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//delete this;
}


void CMotorTest::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//OnDestroy();

	CDialogEx::OnClose();
}


void CMotorTest::OnEnChangeTurn1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMotorTest::OnEnChangeTurn2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMotorTest::OnEnChangeTurn3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMotorTest::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMotorTest::OnNMCustomdrawZoom2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CMotorTest::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nSBCode == SB_ENDSCROLL)
		return;

	if (pScrollBar == (CScrollBar*)&m_Slider_Zoom2)
	{
		m_iZoomData2 = m_Slider_Zoom2.GetPos();

		if (m_iZoomData2 >= 0) //Zoom in
		{
			if (m_iZoomData2 == 0)
				m_iZoomData2 = 1;
			else
				m_dZooming2 = m_iZoomData2;

			_rtGraph2->SetRanges(-ex_dMaxPosition * m_dZooming2, ex_dMaxPosition * m_dZooming2);
		}
		else //Zoom out
		{
			m_dZooming2 = -1.0 * m_iZoomData2;
			_rtGraph2->SetRanges(-ex_dMaxPosition / m_dZooming2, ex_dMaxPosition / m_dZooming2);
		}
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
