#pragma once


// CDlgMain01_02 대화 상자

class CDlgMain01_02 : public CBkDialogST
{
	DECLARE_DYNAMIC(CDlgMain01_02)

public:
	CDlgMain01_02(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgMain01_02();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MAIN01_02 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
