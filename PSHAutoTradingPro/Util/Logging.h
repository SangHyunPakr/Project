#pragma once

struct LoggingSetting
{
	BOOL	write_date_;
	int     period_;
	CString	root_directory_;
};

namespace Log
{
	// Log 기록시에는 아래 함수만 사용한다. ( InitLog , DeleteLog , WriteLog )
	// 실제 Logging 클래스에는 접근 할수 없으며, 신경쓰지 않아도 된다.

	// 프로그램 실행시 한번만 호출한다.
	void    InitLog( int Period , LPCTSTR Folder ); // 현재 프로그램이 실행중인 위치가 로그 루트 디렉토리가 된다.
	void    InitLog( LPCTSTR RootDirectory , int Period );
	
	// 로그에 날짜를 기록할것인가 ?
	void    SetWriteDate( BOOL Write );

	// 로거에 셋팅된 정보들
	LoggingSetting GetLoggingSetting();
	void           SetLoggingSetting( LoggingSetting* p );

	// 프로그램 종료시 한번만 호출한다.
	void	DeleteLog();

	// InitLog 함수에서 호출된 RootDirectory + LogCategory 디렉토리에 날자별로 로그가 기록된다.
	HRESULT WriteLog( LPCTSTR LogCategory , LPCTSTR LogText , ... );

	namespace LogUtil
	{
		CString GetFullDirectoryPath();
	};
};