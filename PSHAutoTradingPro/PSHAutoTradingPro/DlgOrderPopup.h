#pragma once


// CDlgOrderPopup 대화 상자

class CDlgOrderPopup : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOrderPopup)

public:
	CDlgOrderPopup(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgOrderPopup();




public:
	CWnd * m_pParent;
	CString		m_strScrNo;
	CString		m_strJongCode;

	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg);
	void OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList);

public:
	CListBox m_listCtl;


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ORDER_POPUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnOrder();
	virtual void OnOK();
};
