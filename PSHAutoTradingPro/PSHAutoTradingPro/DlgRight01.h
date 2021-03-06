#pragma once


// CDlgRight01 대화 상자

class CDlgRight01 : public CBkDialogST
{
	DECLARE_DYNAMIC(CDlgRight01)

public:
	CDlgRight01(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgRight01();
	void ShowButtonControl(int iCount);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_RIGHT01 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg void OnBnClickedButtonRightSubGroup(UINT ID);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

private:
	CButtonST m_ctrlBtRightSub[NUMBER_SUB_01_BUTTON];
};
