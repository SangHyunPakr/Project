// DlgMain01_02.cpp: 구현 파일
//

#include "stdafx.h"
#include "PSHAutoTradingPro.h"
#include "DlgMain01_02.h"
#include "afxdialogex.h"


// CDlgMain01_02 대화 상자

IMPLEMENT_DYNAMIC(CDlgMain01_02, CBkDialogST)

CDlgMain01_02::CDlgMain01_02(CWnd* pParent /*=nullptr*/)
	: CBkDialogST(IDD_DLG_MAIN01_02, pParent)
{

}

CDlgMain01_02::~CDlgMain01_02()
{
}

void CDlgMain01_02::DoDataExchange(CDataExchange* pDX)
{
	CBkDialogST::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMain01_02, CBkDialogST)
END_MESSAGE_MAP()


// CDlgMain01_02 메시지 처리기


BOOL CDlgMain01_02::OnInitDialog()
{
	CBkDialogST::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetMode(BKDLGST_MODE_STRETCH);
	SetBitmap(IDB_BITMAP_PLATFORM_INFORMATION);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
