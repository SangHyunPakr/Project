// DlgMain02.cpp: 구현 파일
//

#include "stdafx.h"
#include "PSHAutoTradingPro.h"
#include "DlgMain02_01.h"
#include "afxdialogex.h"


// CDlgMain02_01 대화 상자

IMPLEMENT_DYNAMIC(CDlgMain02_01, CBkDialogST)

CDlgMain02_01::CDlgMain02_01(CWnd* pParent /*=nullptr*/)
	: CBkDialogST(IDD_DLG_MAIN02, pParent)
{

}

CDlgMain02_01::~CDlgMain02_01()
{
}

void CDlgMain02_01::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMain02_01, CBkDialogST)
END_MESSAGE_MAP()


// CDlgMain02_01 메시지 처리기


BOOL CDlgMain02_01::OnInitDialog()
{
	CBkDialogST::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
