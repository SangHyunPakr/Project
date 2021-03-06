#pragma once


// CDlgBottom 대화 상자

class CDlgBottom : public CBkDialogST
{
	DECLARE_DYNAMIC(CDlgBottom)

public:
	CDlgBottom(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgBottom();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_BOTTOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
private:
	afx_msg void OnBnClickedButtonBottomMainGroup(UINT ID);
	afx_msg void OnBnClickedButtonExit();

	virtual BOOL OnInitDialog();
private:

	CButtonST m_ctrlBtBottomMain[NUMBER_MAIN_BUTTON];
	CButtonST m_ctrlBtBottomMainExit;
};
