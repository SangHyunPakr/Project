#pragma once


// CDlgMain02_01 대화 상자

class CDlgMain02_01 : public CBkDialogST
{
	DECLARE_DYNAMIC(CDlgMain02_01)

public:
	CDlgMain02_01(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgMain02_01();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MAIN02 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
