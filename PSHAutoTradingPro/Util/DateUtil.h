#pragma once

namespace DateUtil
{
	CString GetNowFileName(const CTime& time);
	CString GetNowDateTime(const CTime& time);
	CString GetNowTime(const CTime& time);
	CString GetNowDate(const CTime& time);

	FILETIME		GetNowFileTime();
	SYSTEMTIME		GetNowSystemTime();
	ULARGE_INTEGER  GetNowULargeInteger();

	FILETIME		SystemTimeToFileTime( const SYSTEMTIME* st );
	ULARGE_INTEGER	SystemTimeToULargeInteger( const SYSTEMTIME* st );
	CString			ULargeIntegerToDateTime( const ULARGE_INTEGER* ui );
	ULARGE_INTEGER  CTimeToULargeInteger(const CTime& time);

	CTime AddHour( const CTime& Now , int Hour );
	int   GetCountOfDay( const CTime& lhs , const CTime& rhs );

	void RoundUpHourSystemTime( SYSTEMTIME& st , int Hour = 23 );
	void RoundDownHourSystemTime( SYSTEMTIME& st , int Hour = 0 );

	CString RemoveDate( LPCTSTR DateTime );
};
