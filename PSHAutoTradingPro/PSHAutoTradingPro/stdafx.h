
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원




struct STRUCT_IO_Data
{
	explicit STRUCT_IO_Data(int Command = 0, LPCTSTR Data = NULL) : iCommand(Command), strData(Data) {}

	int	iCommand;
	CString strData;

	// std::string sData;
};

#define PLC_ON  _T("ON")
#define PLC_OFF _T("OFF")

#include <strsafe.h>

// dh.kim 2018-08-06 10:48:17 : sqlite 파일 추가
#include "..\SQLite\sqlite3.h"
#pragma comment( lib , "..\\SQLite\\sqlite3.lib" )

#include "..\Util\SyncObject.h"
#include "..\Util\ColorStatic.h"
#include "..\Util\BKDialogST.h"
#include "..\Util\FontManager.h"
#include "..\Util\DialogUtil.h"
#include "..\Util\BtnST.h"
#include <algorithm> 
#include <limits.h>
#include "..\Util\FileSystemUtil.h"
#include "..\Util\DateUtil.h"
#include "..\Util\DeviceData.h"
#include "..\Util\ScrollWindow.h"
#include "..\Util\Logging.h"
#include "..\Util\Thread.h"
#include "..\Util\StringUtil.h"
#include "..\Util\Minidumphelp.h"

// Device Control
#include "..\Util\ianalogoutputx.h"
#include "..\Util\irotationdisplayx1.h"
#include "..\Util\iledrectanglex1.h"
#include "..\Util\iswitchledx8.h"
#include "..\Util\ianalogdisplayx.h"
#include "..\Util\iValveX.h"
#include "..\Util\iEditX.h"
#include "..\Util\ipipex.h"
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>


//#import "..\Software FX Shared\ChartFX.ClientServer.core.dll"  rename_namespace("Cfx62") rename("min","minX") rename("max","maxX") exclude("_CollectionBase","_Component","CollectionBase","Component")






/*window size*/
#define	RIGHT_HEIGHT			100
#define	RIGHT_WIDTH				150
#define	TITLE_HEIGHT			100
#define	TITLE_WIDTH				100

/*button number*/
#define NUMBER_MAIN_BUTTON		5
#define NUMBER_SUB_01_BUTTON	5
#define NUMBER_SUB_02_BUTTON	4

// controller
#define PUMP_NUMBER				7

#define SEND_MSG_MAX_SIZE		1024
#define IO_MAX_SIZE				4192
#define RECEIVE_DATA_SPLIT		3
#define BIT_08					8
#define BIT_16					16
#define PORT_PLC				1



#include "..\OpenAPI\KHOpenAPICtrl.h"
#include "..\Util\GridCtrl\GridCtrl.h"

#define OP_ERR_SISE_OVERFLOW	-200			//"시세조회 과부하"
#define OP_ERR_RQ_STRUCT_FAIL	-201		//"REQUEST_INPUT_st Failed"
#define OP_ERR_RQ_STRING_FAIL	-202			//"요청 전문 작성 실패"
#define OP_ERR_NO_DATA			-203			//"데이터가 존재하지 않습니다."
#define OP_ERR_OVER_MAX_DATA	-204			//"한번에 조회 가능한 종목개수는 최대 100종목 입니다."


#define OP_ERR_ORD_WRONG_INPUT	-300			//"입력값 오류"
#define OP_ERR_ORD_WRONG_ACCNO	-301			//"계좌비밀번호를 입력하십시오."
#define OP_ERR_OTHER_ACC_USE	-302			//"타인계좌는 사용할 수 없습니다."
#define OP_ERR_MIS_2BILL_EXC	-303			//"주문가격이 20억원을 초과합니다."
#define OP_ERR_MIS_5BILL_EXC	-304			//"주문가격이 50억원을 초과합니다."
#define OP_ERR_MIS_1PER_EXC		-305			//"주문수량이 총발행주수의 1%를 초과합니다."
#define OP_ERR_MIS_3PER_EXC		-306			//"주문수량은 총발행주수의 3%를 초과할 수 없습니다."
#define OP_ERR_SEND_FAIL		-307			//"주문전송실패"
#define OP_ERR_ORD_OVERFLOW		-308			//"주문전송 과부하"

#define UM_SCRENN_CLOSE		1000
#define SCREEN_TYPE			1000

#define FIDLIST_CONDITION	_T("9001;302;10;11;25;12;13;16;17;18")
#define FIDLIST_JANGO		_T("9001;302;10;930;931;8019")//종목코드,종목명, 현재가,보유수량, 매입단가,손익율

#define TR_OPT10001		"OPT10001"
#define TR_OPT10003		"OPT10003"
#define TR_OPT10004		"OPT10004"
#define TR_OPT10006		"OPT10006"
#define TR_OPT10007		"OPT10007"
#define TR_OPT10075		"OPT10075"
#define TR_OPW00018		"OPW00018"

#define DT_NONE			0		// 기본문자 형식
#define DT_DATE			1		// 일자 형식
#define DT_TIME			2		// 시간 형식
#define DT_NUMBER		3		// 콤마 숫자 형식
#define DT_ZERO_NUMBER	4		// 콤마 숫자(0표시) 형식
#define DT_SIGN			5		// 대비기호 형식

typedef struct
{
	CString		strKey;				// 조회 키
	CString		strRealKey;			// 리얼 키
	int			nRow;				// 그리드 행
	int			nCol;				// 그리드 열
	int			nDataType;			// 데이타 타입(0:기본문자, 1:일자, 2:시간, 3:콤파 숫자, 4:콤파 숫자(0표시), 5:대비기호)
	BOOL		bTextColor;			// 문자열 색 변경(상승, 하락색)
	UINT		nAlign;				// 문자열 정렬(DT_LEFT, DT_CENTER, DT_RIGHT)
	CString		strBeforeData;		// 문자열 앞 문자 넣기
	CString		strAfterData;		// 문자열 뒤 문자 넣기
} stGRID;
// {조회 키,			리얼 키,	행, 열, 타입,			색 변경,정렬,		앞 문자,	뒷 문자}
const stGRID lstOPTSBFID[] =
{
	{"종목코드",		"9001",		-1,	0,	DT_NONE,		FALSE,	DT_LEFT,	"",			""},
	{"종목명",			"302",		-1,	1,	DT_NONE,		FALSE,	DT_LEFT,	"",			""},
	{"현재가",			"10",		-1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",			""},
	{"전일대비기호",	"25",		-1,	3,	DT_SIGN,		TRUE,	DT_CENTER,	"",			""},
	{"전일대비",		"11",		-1,	4,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",			""},
	{"등락율",			"12",		-1,	5,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",			"%"},
	{"거래량",			"13",		-1,	6,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",			""},
	{"시가",			"16",		-1,	7,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",			""},
	{"고가",			"17",		-1,	8,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",			""},
	{"저가",			"18",		-1,	9,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",			""},
};

//잔고
const stGRID lstOPW00018[] =
{
	{ "종목번호",		"-1",	-1,	0,	DT_NONE,		FALSE,	DT_CENTER,	"",	"" },
	{ "종목명",			"-1",	-1,	1,	DT_NONE,		FALSE,	DT_CENTER,	"",	"" },
	{ "평가손익",		"-1",	-1,	2,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
	{ "수익률(%)",		"-1",	-1,	3,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
	{ "보유수량",		"-1",	-1,	4,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
	{ "현재가",			"-1",	-1,	5,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
	{ "매입가",			"-1",	-1,	6,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
};

// 체결
const stGRID lstOPT10075[] =
{
	{ "주문번호",		"-1",	-1,	0,	DT_NONE,		FALSE,	DT_CENTER,	"",	"" },
	{ "종목코드",		"-1",	-1,	1,	DT_NONE,		FALSE,	DT_CENTER,	"",	"" },
	{ "종목명",			"-1",	-1,	2,	DT_NONE,		FALSE,	DT_CENTER,	"",	"" },
	{ "미체결수량",		"-1",	-1,	3,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
	{ "원주문번호",		"-1",	-1,	4,	DT_NONE,		FALSE,	DT_CENTER,	"",	"" },
	{ "주문구분",		"-1",	-1,	5,	DT_NONE,		FALSE,	DT_CENTER,	"",	"" },

};

//const stGRID lstFIDLIST_JANGO[] =
//{
//	{ "종목코드",		"9001",	-1,	0,	DT_NONE,		FALSE,	DT_CENTER,	"",	"" },
//	{ "종목명",			"302",	-1,	1,	DT_NONE,		TRUE,	DT_CENTER,	"",	"" },
//	{ "현재가",			"10",	-1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"" },
//	{ "보유수량",		"930",	-1,	3,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
//	{ "매입단가",		"931",	-1,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"" },
//	{ "손익율",			"8019",	-1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"" },
//};