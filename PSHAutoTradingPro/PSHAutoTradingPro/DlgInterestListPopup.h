#pragma once


// CDlgInterestListPopup 대화 상자

class CDlgInterestListPopup : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInterestListPopup)

public:
	CDlgInterestListPopup(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgInterestListPopup();




public:
	CWnd * m_pParent;
	CString					m_strScrNo;
	CMapStringToString		m_mapJongCode;		// 관심종목

	CCellID					m_cellSelect;		// 관심 그리드 선택 행
	CGridCtrl				m_grdKwanSim;		// 관심 그리드
	void InitKwanSimGrid();						// 관심 그리드 초기 처리
	void SetKwanSimJong();						// 관심 그리드에 종목 설정 처리
												// 종목 조회 요청
	void SendJongSearch(int nCodeCount = 0, CString strCodeList = "");

	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg);
	void OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList);

	// 그리드 데이타 설정(주식기본정보 설정)
	void SetDataKwanSimGrid(CStringArray &arrData, CString strRealType = "");





// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_INTERESTLIST_POPUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBtnJongAdd();
	afx_msg void OnBtnJongDelete();
	afx_msg void OnBtnJongAllDelete();
	afx_msg void OnBtnSearch();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
