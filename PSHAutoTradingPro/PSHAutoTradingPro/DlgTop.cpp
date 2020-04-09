// CDlgTop.cpp: 구현 파일
//

#include "stdafx.h"
#include "PSHAutoTradingPro.h"
#include "DlgTop.h"
#include "afxdialogex.h"


// CDlgTop 대화 상자

IMPLEMENT_DYNAMIC(CDlgTop, CBkDialogST)

CDlgTop::CDlgTop(CWnd* pParent /*=nullptr*/)
	: CBkDialogST(IDD_DLG_TOP, pParent)
{

}

CDlgTop::~CDlgTop()
{
}

void CDlgTop::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTop, CBkDialogST)
END_MESSAGE_MAP()


// CDlgTop 메시지 처리기


BOOL CDlgTop::OnInitDialog()
{
	CBkDialogST::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetMode(BKDLGST_MODE_STRETCH);
	SetBitmap(IDB_BITMAP_PLATFORM_TOP);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
