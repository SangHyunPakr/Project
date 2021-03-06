// CDlgRight01.cpp: 구현 파일
//

#include "stdafx.h"
#include "PSHAutoTradingPro.h"
#include "DlgRight01.h"
#include "afxdialogex.h"


// CDlgRight01 대화 상자

IMPLEMENT_DYNAMIC(CDlgRight01, CBkDialogST)

CDlgRight01::CDlgRight01(CWnd* pParent /*=nullptr*/)
	: CBkDialogST(IDD_DLG_RIGHT01, pParent)
{

}

CDlgRight01::~CDlgRight01()
{
}

void CDlgRight01::DoDataExchange(CDataExchange* pDX)
{
	CBkDialogST::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON_RIGHT_SUB_01, m_ctrlBtRightSub[0]);
	DDX_Control(pDX, IDC_BUTTON_RIGHT_SUB_02, m_ctrlBtRightSub[1]);
	DDX_Control(pDX, IDC_BUTTON_RIGHT_SUB_03, m_ctrlBtRightSub[2]);
	DDX_Control(pDX, IDC_BUTTON_RIGHT_SUB_04, m_ctrlBtRightSub[3]);
	DDX_Control(pDX, IDC_BUTTON_RIGHT_SUB_05, m_ctrlBtRightSub[4]);
}


BEGIN_MESSAGE_MAP(CDlgRight01, CBkDialogST)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_RIGHT_SUB_01, IDC_BUTTON_RIGHT_SUB_02, OnBnClickedButtonRightSubGroup)
END_MESSAGE_MAP()


// CDlgRight01 메시지 처리기


BOOL CDlgRight01::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetMode(BKDLGST_MODE_STRETCH);
	SetBitmap(IDB_BITMAP_PLATFORM_COMMAND);
	
	//ShowButtonControl(2);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgRight01::OnBnClickedButtonRightSubGroup(UINT ID)
{
	DialogUtil::SetLastRightBtnID(ID);
	DialogUtil::ShowDialog(ClickStep(DialogUtil::GetLastBottomBtnID(), ID));

	//m_ctrlBtRightSub[0].SetBitmaps(IDB_BITMAP_MAIN01, 0, 0);
	//m_ctrlBtRightSub[1].SetBitmaps(IDB_BITMAP_MAIN02, 0, 0);

	//switch (ID)
	//{
	//case IDC_BUTTON_RIGHT_SUB_01:
	//	m_ctrlBtRightSub[0].SetBitmaps(IDB_BMP_MAIN01, 0, 0);
	//	break;

	//case IDC_BUTTON_RIGHT_SUB_02:
	//	m_ctrlBtRightSub[1].SetBitmaps(IDB_BMP_MAIN02, 0, 0);
	//	break;
	//}
}

void CDlgRight01::ShowButtonControl(int iCount)
{
	for (int i = 0; i < iCount; i++)
	{
		m_ctrlBtRightSub[i].ShowWindow(SW_SHOW);
	}
	for (int i = iCount; i < NUMBER_SUB_01_BUTTON; i++)
	{
		m_ctrlBtRightSub[i].ShowWindow(SW_HIDE);
	}
}