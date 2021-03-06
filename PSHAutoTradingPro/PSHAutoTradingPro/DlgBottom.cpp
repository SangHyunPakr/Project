// CDlgBottom.cpp: 구현 파일
//

#include "stdafx.h"
#include "PSHAutoTradingPro.h"
#include "DlgBottom.h"
#include "afxdialogex.h"
#include "DlgRight01.h"

// CDlgBottom 대화 상자

IMPLEMENT_DYNAMIC(CDlgBottom, CBkDialogST)

CDlgBottom::CDlgBottom(CWnd* pParent /*=nullptr*/)
	: CBkDialogST(IDD_DLG_BOTTOM, pParent)
{

}

CDlgBottom::~CDlgBottom()
{
}

void CDlgBottom::DoDataExchange(CDataExchange* pDX)
{
	CBkDialogST::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BOTTOM_MAIN_01, m_ctrlBtBottomMain[0]);
	DDX_Control(pDX, IDC_BUTTON_BOTTOM_MAIN_02, m_ctrlBtBottomMain[1]);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_ctrlBtBottomMainExit);
}


BEGIN_MESSAGE_MAP(CDlgBottom, CBkDialogST)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_BOTTOM_MAIN_01, IDC_BUTTON_BOTTOM_MAIN_02, OnBnClickedButtonBottomMainGroup)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CDlgBottom::OnBnClickedButtonExit)
END_MESSAGE_MAP()


// CDlgBottom 메시지 처리기


BOOL CDlgBottom::OnInitDialog()
{
	CBkDialogST::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetMode(BKDLGST_MODE_STRETCH);
	SetBitmap(IDB_BITMAP_PLATFORM_BOTTOM);

	//m_ctrlBtRightSub[0].SetBitmaps(IDB_BMP_???, 0, 0);
	//m_ctrlBtRightSub[1].SetBitmaps(IDB_BMP_???, 0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}




void CDlgBottom::OnBnClickedButtonExit()
{
	if (MessageBox(_T("Do you want Exit?"), _T("Exit"), MB_ICONASTERISK | MB_YESNO) == IDYES)
		AfxGetApp()->GetMainWnd()->PostMessage(WM_CLOSE);
}


void CDlgBottom::OnBnClickedButtonBottomMainGroup(UINT ID)
{
	if (DialogUtil::GetLastBottomBtnID() == ID) return;

	DialogUtil::SetLastBottomBtnID(ID);
	DialogUtil::ShowDialog(ClickStep(ID, 1001));

	CDlgRight01 * dlg = (CDlgRight01*)DialogUtil::GetDialog(IDD_DLG_RIGHT01);

	switch (ID)
	{
	case IDC_BUTTON_BOTTOM_MAIN_01:
		dlg->ShowButtonControl(2);
		break;
	case IDC_BUTTON_BOTTOM_MAIN_02:
		dlg->ShowButtonControl(1);
		break;
	}
}
