#include "stdafx.h"
#include "DateUtil.h"

namespace DateUtil
{

CString GetNowFileName(const CTime& time)
{
	CString file_string;
	file_string.Format( _T("%04d-%02d-%02d_%02d%02d%02d") ,  time.GetYear() , time.GetMonth()  , time.GetDay() , 
																	time.GetHour() , time.GetMinute() , time.GetSecond() );
	return file_string;
}

CString GetNowDateTime(const CTime& time)
{
	CString datetime_string;
	datetime_string.Format( _T("%04d-%02d-%02d %02d:%02d:%02d") ,  time.GetYear() , time.GetMonth()  , time.GetDay() , 
																	time.GetHour() , time.GetMinute() , time.GetSecond() );
	return datetime_string;
}

CString GetNowTime(const CTime& time)
{
	CString time_string;
	time_string.Format( _T("%02d:%02d:%02d") , time.GetHour() , time.GetMinute() , time.GetSecond() );
	return time_string;
}

CString GetNowDate(const CTime& time)
{
	CString date_string;
	date_string.Format( _T("%04d-%02d-%02d") ,  time.GetYear() , time.GetMonth()  , time.GetDay() );
	return date_string;
}

FILETIME GetNowFileTime()
{
	SYSTEMTIME st = GetNowSystemTime();

	return SystemTimeToFileTime( &st );
}

SYSTEMTIME GetNowSystemTime()
{
	SYSTEMTIME st = { 0 , };
	::GetLocalTime( &st );

	return st;
}

ULARGE_INTEGER  GetNowULargeInteger()
{
	FILETIME ft = GetNowFileTime();

	ULARGE_INTEGER ret;
	ret.LowPart  = ft.dwLowDateTime;
	ret.HighPart = ft.dwHighDateTime;

	return ret;
}

FILETIME SystemTimeToFileTime( const SYSTEMTIME* st )
{
	FILETIME   ft = { 0 , };
	::SystemTimeToFileTime( st , &ft );

	return ft;
}

ULARGE_INTEGER	SystemTimeToULargeInteger( const SYSTEMTIME* st )
{
	FILETIME   ft = { 0 , };
	::SystemTimeToFileTime( st , &ft );

	ULARGE_INTEGER ret;
	ret.LowPart  = ft.dwLowDateTime;
	ret.HighPart = ft.dwHighDateTime;

	return ret;
}

CString ULargeIntegerToDateTime( const ULARGE_INTEGER* ui )
{
	FILETIME   ft = { ui->u.LowPart , ui->u.HighPart };
	SYSTEMTIME st = { 0 , };

	FileTimeToSystemTime( &ft , &st );

	CString DateTime;
	DateTime.Format( _T("%04d-%02d-%02d %02d:%02d:%02d") , st.wYear , st.wMonth  , st.wDay , 
														   st.wHour , st.wMinute , st.wSecond );

	return DateTime;
}

ULARGE_INTEGER  CTimeToULargeInteger(const CTime& time)
{
	SYSTEMTIME st = { 0 , };
	time.GetAsSystemTime( st );

	return SystemTimeToULargeInteger( &st );
}



CTime AddHour( const CTime& Now , int Hour )
{
	return CTime( Now + CTimeSpan( 0 , Hour , 0 , 0 ) );
}

int GetCountOfDay( const CTime& lhs , const CTime& rhs )
{
	CTimeSpan Gap = rhs - lhs;
	return (int)Gap.GetDays();
}

void RoundUpHourSystemTime( SYSTEMTIME& st , int Hour )
{
	st.wHour = Hour;
	st.wMinute = 59;
	st.wSecond = 59;
	st.wMilliseconds = 999;
}

void RoundDownHourSystemTime( SYSTEMTIME& st , int Hour )
{
	st.wHour = Hour;
	st.wMinute = 0;
	st.wSecond = 0;
	st.wMilliseconds = 0;
}

CString RemoveDate( LPCTSTR DateTime )
{
	int Year = 0;
	int Month = 0;
	int Day = 0;
	int Hour = 0;
	int Min = 0;
	int Sec = 0;

	_stscanf_s( DateTime , _T("%d-%d-%d %d:%d:%d") , &Year , &Month , &Day , &Hour , &Min , &Sec );
	
	SYSTEMTIME st = { 0 , };

	st.wYear = Year;
	st.wMonth = Month;
	st.wDay = Day;
	st.wHour = Hour;
	st.wMinute = Min;
	st.wSecond = Sec;

	return GetNowTime( CTime( st ) );
}

};