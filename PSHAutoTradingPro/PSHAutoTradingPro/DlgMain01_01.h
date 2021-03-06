#pragma once


// CDlgMain01_01 대화 상자

class CDlgMain01_01 : public CBkDialogST
{
	DECLARE_DYNAMIC(CDlgMain01_01)

public:
	CDlgMain01_01(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgMain01_01();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MAIN01 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonCurrent();
	afx_msg void OnBnClickedButtonOrder();
	afx_msg void OnBnClickedButtonInterest();


	/****************************************************************************/
	/****************************************************************************/
	/****************************************************************************/
	CWnd*					m_pParent;
	CString					m_strScrNo;
	CString					m_strCurConditionName;	//현재 조건명
	int						m_nCurConditionIndex;	//현재 조건명 인덱스
	CString					m_strPreConditionName;		//이전 조건명
	int						m_nPreConditionIndex;		//이전 조건명 인덱스

	CMapStringToString		m_mapRealRegiCode;		// 리얼등록 종목
	CMapStringToString		m_mapConditionNameList;	// 조건검색명리스트
	CMapStringToString		m_mapJanGoList;			// 잔고 목록들
	CMapStringToString		m_mapDealingList;		// 거래중인 목록들
	CMapStringToString		m_mapDealNumberList;	// 거래중인 목록들


	CCellID					m_cellSelect;			// 종목 그리드 선택 행
	CGridCtrl				m_gridConditionList;	// 종목 그리드
	CGridCtrl				m_gridJanGoList;		// 잔고확인 그리드
	CGridCtrl				m_gridDealingList;		// 미체결 그리드
	CComboBox				m_ctrlComboCondition;	// 조건검색명 콤보
	CListBox				m_ctrlListInsert;
	CListBox				m_ctrlListDelete;
	CListBox				m_ctrlListOrderInfo;

	void					InitGridConditionList();
	void					InitGridJanGoList();
	void					SetDataJanGoGrid(CStringArray &strArray);
	void					InitGridDealingList();
	void					SetDataDealingGrid(CStringArray &strArray);

	//afx_msg void			OnBnClickedConditionSearch();
	afx_msg void			OnBnClickedButtonDownloadConditionList();
	afx_msg void			OnBnClickedButtonConditionSearchRt();
	afx_msg void			OnBnClickedButtonConditionRealtimeStop();
	afx_msg void			OnBnClickedButtonSiseRegistration();
	afx_msg void			OnBnClickedButtonSiseUnregistration();
	afx_msg void			OnBnClickedButtonAllUnregistration();

	void					OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void					OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	void					OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg);
	void					OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList);
	void					OnReceiveRealCondition(LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex);				//조건검색 실시간 삽입,삭제되는 종목을 받는다
	void					OnReceiveTrCondition(LPCTSTR sScrNo, LPCTSTR strCodeList, LPCTSTR strConditionName, int nIndex, int nNext);	   //조건검색 종목리스트를 받는다.
	void					OnReceiveConditionVer(long bRet, LPCTSTR sMsg);
	// 그리드 데이타 설정(주식기본정보 설정)
	void					SetDataRealAddGrid(CStringArray &arrData, CString strRealType = "");

	CThread							m_ThreadOrder;
	BOOL							m_bThreadOrderRun;
	BOOL							m_bThreadContinue;	/*쓰레드 계속 진행,시세조회응답 완료?*/
	static unsigned int __stdcall	ThreadOrder(void* Param);

	CThread							m_ThreadOrderSale;
	static unsigned int __stdcall	ThreadOrderSale(void* Param);
	/****************************************************************************/
	/****************************************************************************/
	/****************************************************************************/
	/****************************************************************************/
	/****************************************************************************/


	afx_msg void OnClose();

	afx_msg void OnBnClickedButtonAutoOrder();
	afx_msg void OnBnClickedButtonOrderSale();
	afx_msg void OnBnClickedButtonCheckJango();
	afx_msg void OnBnClickedButtonNotContract();
	afx_msg void OnBnClickedButtonOrderAllSale();
	afx_msg void OnBnClickedButtonAllCancle();
};

