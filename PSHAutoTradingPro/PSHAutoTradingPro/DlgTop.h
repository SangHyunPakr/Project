#pragma once


// CDlgTop 대화 상자

class CDlgTop : public CBkDialogST
{
	DECLARE_DYNAMIC(CDlgTop)

public:
	CDlgTop(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgTop();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_TOP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
