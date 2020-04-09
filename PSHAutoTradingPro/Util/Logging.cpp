#include "stdafx.h"
#include "logging.h"
#include <strsafe.h>
#include "syncobject.h"
#include <list>

namespace {

#define LOG_FILE_EXTENSION			_T("csv")
#define LOG_FILE_EXTENSION_WITH_DOT _T(".csv")
#define MAX_BUF_SIZE 4086

//--------------------------------------------------------------------------------------------------------------
// ��ƿ��Ƽ �Լ�
void make_directory(LPCTSTR full_path)
{
	TCHAR	temp[256] = { 0 , };
	LPTSTR	sp = NULL;

	_tcscpy_s(temp, full_path);
	sp = temp; 

	while( sp = _tcschr( sp, _T('\\') ) )
	{
		if( sp > temp && *(sp - 1) != _T(':') ) 
		{ 
			*sp = _T('\0'); 
			
			CreateDirectory( temp , NULL );			

			*sp = _T('\\'); 
		}

		++sp; 
	}
}

CString time_to_string_date( CTime& time )
{
	CString date_string;
	date_string.Format( _T("%04d-%02d-%02d") ,  time.GetYear() , time.GetMonth()  , time.GetDay() );
	return date_string;
}

CString time_to_string_date_time( CTime& time )
{
	CString datetime_string;
	datetime_string.Format( _T("%04d-%02d-%02d %02d:%02d:%02d") ,  time.GetYear() , time.GetMonth()  , time.GetDay() , 
																	time.GetHour() , time.GetMinute() , time.GetSecond() );
	return datetime_string;
}

inline CTime add_day( CTime& time , int day ) {  return ( time + CTimeSpan( day , 0 , 0 , 0 ) ); }

int get_file_name_in_directory( std::list<CString>& file_name_list , const CString& directory , LPCTSTR file_extension/*���� Ȯ����*/ )
{
	if ( directory.IsEmpty() ) return 0;

	CString path = directory;

	if ( !file_extension )	path = directory + _T("*.*");
	else					path = directory + _T("*.") + file_extension;
		
	CFileFind finder;
	BOOL	  keep_going = finder.FindFile( path );

	while( keep_going )
	{
		keep_going = finder.FindNextFile();
			
		if ( !finder.IsArchived() ) continue;

		CString file_name = finder.GetFileName();

		if ( file_name.IsEmpty() || file_name == _T(".") || file_name == _T("..") ) continue;

		file_name_list.push_back( file_name );
	}

	return (int)file_name_list.size();
}


BOOL is_exist_name_into_list( std::list< CString >& list , const CString& name )
{
	std::list< CString >::iterator cur = list.begin();
	std::list< CString >::iterator end = list.end();

	for ( ; cur != end ; ++cur )
		if ( (*cur) == name ) return TRUE;
		
	return FALSE;
}

BOOL write_file( const CString& path , LPCTSTR log , int len , DWORD* error_code )
{
	HANDLE h = CreateFile( path , GENERIC_READ|GENERIC_WRITE , FILE_SHARE_READ , NULL , OPEN_ALWAYS , FILE_ATTRIBUTE_NORMAL , NULL );
	if ( error_code ) *error_code = GetLastError();

	if ( h == INVALID_HANDLE_VALUE ) return FALSE;

	SetFilePointer( h , 0 , NULL , FILE_END );
	
	DWORD written_byte = 0;
	if ( !WriteFile( h , log , len * sizeof( TCHAR ) , &written_byte , NULL ) )
	{
		if ( error_code ) *error_code = GetLastError();

		CloseHandle( h );
		return FALSE;
	}

	CloseHandle( h );
	return TRUE;
}

void make_full_directoy_name( CString& directory )
{
	if ( directory.IsEmpty() ) return;

	int   last_index = directory.GetLength() - 1;
	TCHAR ch		 = directory.GetAt( last_index );

	if ( ch != _T('\\') )
		directory.AppendChar( _T('\\') );
}
//--------------------------------------------------------------------------------------------------------------
};


namespace Log
{
	namespace // �̸� ���� ���ӽ����̽� �ȿ� �ִ� ������ �Ű澲�� �ʾƵ� �ȴ�.
	{
		class Logging
		{
		public:

			// Logging ��ü ���� ������ ȣ��
			static Logging* CreateLoggingInstance( const CString& LogDirectory , int Period , BOOL WriteDate ) { return ( new Logging( LogDirectory , Period , WriteDate ) ); }

			// Logging ��ü ������
			void DeleteLoggingInstance(){ delete this; }

			// �αװ� ����� ������ ��ġ
			void SetLogDirectory( const CString& LogDirectory )
			{
				log_directory_ = LogDirectory; 

				make_full_directoy_name( log_directory_ );
				make_directory( log_directory_ );
			}

			// �α׸� ���� �������� ����
			void SetMaintenancePeriod( int Period ) { period_ = Period; }

			// �α� ��Ͻ� ��¥�� ����� ���ΰ�
			void SetWriteDate( BOOL WriteDate ) { write_date_ = WriteDate; }

			// �α� ���
			HRESULT Log( LPCTSTR LogText , va_list ap )
			{
				CriticalSectionRAII RAII( cs_ );

				update_now_time(); // �α� ����� ���� ���� ȣ�� �Ǿ�� �Ѵ�.

				if ( period_ > 0 )
					delete_file_in_not_period(); // �Ⱓ�� ���� �α� ������ ���� �Ѵ�.

				TCHAR log[MAX_BUF_SIZE] = { 0 , };
				TCHAR buffer[MAX_BUF_SIZE] = { 0 , };

				_vstprintf_s(buffer, LogText, ap);

				HRESULT ret = 0;

				if ( write_date_ )
				{
					log[0] = _T('[');

					ret = StringCchCat( log , MAX_BUF_SIZE , time_to_string_date_time( get_now_time() ) );
					if ( FAILED( ret ) ) return ret;

					ret = StringCchCat( log , MAX_BUF_SIZE , _T("] ") );
					if ( FAILED( ret ) ) return ret;
				}

				ret = StringCchCat( log , MAX_BUF_SIZE , buffer );
				if ( FAILED( ret ) ) return ret;

				ret = StringCchCat( log , MAX_BUF_SIZE , _T("\r\n") );
				if ( FAILED( ret ) ) return ret;
	
				DWORD last_error = 0;
				write_file( log_directory_ + get_now_file_name() + LOG_FILE_EXTENSION_WITH_DOT , log , _tcslen( log ) , &last_error );

				return HRESULT_FROM_WIN32(last_error);
			}

			HRESULT Log( LPCTSTR LogText , ... )
			{
				va_list ap;
				va_start(ap, LogText );

				return Log( LogText , ap );
			}

		private:

			// ��ü�� ������ �Ҹ��� CreateLoggingInstance �� DeleteLoggingInstance ���ؼ��� �����ϴ�.
			Logging( const CString& LogDirectory , int Period , BOOL WriteDate )
			{
				ZeroMemory( &cs_ , sizeof( CRITICAL_SECTION ) );

				InitializeLogging( LogDirectory , Period , WriteDate );
			}

			~Logging() { DeleteLogging(); }

			Logging( const Logging& rhs ) = delete;			  // ���� ������ ������
			Logging& operator=(const Logging& rhs ) = delete; // ���� ������ ������

			BOOL InitializeLogging( const CString& LogDirectory , int Period , BOOL WriteDate )
			{
				DeleteLogging();
				InitializeCriticalSectionAndSpinCount( &cs_ , 1000 );

				SetLogDirectory( LogDirectory );
				SetMaintenancePeriod( Period );
				SetWriteDate( WriteDate );

				return TRUE;
			}

			void DeleteLogging()
			{
				if ( cs_.SpinCount == 0 ) return;

				DeleteCriticalSection( &cs_ );
			}

			CTime get_begin_time()
			{
				CTime&	time			= get_now_time();
				CTime	round_down_time = CTime( time.GetYear() , time.GetMonth() , time.GetDay() , 0 , 0 , 1 );

				return add_day( round_down_time , -(period_-1) );
			}

			CTime get_end_time()
			{
				CTime& time = get_now_time();
				return CTime( time.GetYear() , time.GetMonth() , time.GetDay() , 23 , 59 , 59 );
			}

			CString get_now_file_name()
			{
				return time_to_string_date( get_now_time() ); 
			}

			void delete_file_in_not_period()
			{
				if ( log_directory_.IsEmpty() ) return;

				std::list< CString > all_file_name_list;
				if ( !get_file_name_in_directory( all_file_name_list , log_directory_ , LOG_FILE_EXTENSION )) return;
		
				std::list< CString > period_file_name_list;
				if ( !get_period_file_name( period_file_name_list ) ) return;

				std::list< CString >::iterator cur = all_file_name_list.begin();
				std::list< CString >::iterator end = all_file_name_list.end();

				for ( ; cur != end ; ++cur )
				{
					CString file_name = (*cur);
					if ( !is_exist_name_into_list( period_file_name_list , file_name ) )
						DeleteFile( log_directory_ + file_name );
				}
			}

			int	get_period_file_name( std::list< CString >& file_name_list )
			{
				CTime cur = get_begin_time();
				CTime end = get_end_time();

				for ( ; cur <= end ; cur = add_day( cur , 1  ) )
					file_name_list.push_back( time_to_string_date( cur ) + LOG_FILE_EXTENSION_WITH_DOT );

				return (int)file_name_list.size();
			}

			inline void	  update_now_time() { now_ = CTime::GetCurrentTime(); }
			inline CTime& get_now_time()	{ return now_; }

		private:

			CRITICAL_SECTION cs_;
			CTime	now_;

			int		period_;		/*����ġ �α׸� ������ ���ΰ�*/
			BOOL	write_date_;	/*�α� ��Ͻ� ��¥�� ����� ���ΰ�*/
			CString log_directory_; /*�αװ� ����� ���丮��, �α� �̸��� YYYY-MM-DD.log�� ����ȴ�.*/
		};
		//--------------------------------------------------------------------------------------------------------------

		SyncMap< LPCTSTR , Logging* > log_map_;
		CRITICAL_SECTION cs_;

		LoggingSetting setting_;

		struct ReleaseLoggingEntry
		{
			inline void operator()( std::pair< LPCTSTR const , Logging* >& Entry ) const
			{
				Entry.second->DeleteLoggingInstance();
			}
		};

		Logging* GetLogInstance( LPCTSTR LogCategory )
		{
			if ( log_map_.Has( LogCategory ) )
				return log_map_.Get( LogCategory );

			CriticalSectionRAII RAII( cs_ );

			if ( log_map_.Has( LogCategory ) )
				return log_map_.Get( LogCategory );

			if ( setting_.root_directory_.IsEmpty() ) return NULL;

			Logging* log = Logging::CreateLoggingInstance( setting_.root_directory_ + LogCategory , setting_.period_ , setting_.write_date_ );
			log_map_.Set( LogCategory , log );

			return log;
		}
	};

	//------------------------------------------------------------------------------------
	// �ܺη� ����� �Լ���
	void InitLog( LPCTSTR RootDirectory , int Period )
	{
		setting_.root_directory_ = RootDirectory;
		setting_.period_ = Period;

		make_full_directoy_name( setting_.root_directory_ );
		make_directory( setting_.root_directory_ );

		InitializeCriticalSectionAndSpinCount( &cs_ , 3000 );
		SetWriteDate( TRUE );
	}

	void InitLog( int Period , LPCTSTR Folder )
	{
		CString exe_path = LogUtil::GetFullDirectoryPath();

		if ( Folder )
			exe_path += Folder;

		InitLog( exe_path , Period );
		SetWriteDate( TRUE );
	}

	void DeleteLog()
	{
		DeleteCriticalSection( &cs_ );

		if ( log_map_.Count() <= 0 ) return;

		ReleaseContainer( log_map_ , ReleaseLoggingEntry() );
		log_map_.Clear();
		setting_.root_directory_.Empty();
	}

	// InitLog �Լ����� ȣ��� RootDirectory + LogCategory ���丮�� ���ں��� �αװ� ��ϵȴ�.
	HRESULT WriteLog( LPCTSTR LogCategory , LPCTSTR LogText , ... )
	{
		va_list ap;
		va_start( ap, LogText );

		Logging* log = GetLogInstance( LogCategory );

		return log->Log( LogText , ap );
	}

	void SetWriteDate( BOOL Write )
	{
		setting_.write_date_ = Write;
	}

	BOOL GetWriteDate()
	{
		return setting_.write_date_;
	}

	void SetLoggingSetting( LoggingSetting* p )
	{
		setting_ = *p;
		
		make_full_directoy_name( setting_.root_directory_ );
		make_directory( setting_.root_directory_ );

		log_map_.Enter();

		std::map< LPCTSTR , Logging* >::iterator cur = log_map_.begin();
		std::map< LPCTSTR , Logging* >::iterator end = log_map_.end();

		std::for_each( cur , end , [&]( std::pair< const LPCTSTR , Logging* >& data )
		{
			data.second->SetLogDirectory( setting_.root_directory_ );
			data.second->SetMaintenancePeriod( setting_.period_ );
			data.second->SetWriteDate( setting_.write_date_ );
		});

		log_map_.Leave();
	}

	LoggingSetting GetLoggingSetting()
	{
		return setting_;
	}

	//------------------------------------------------------------------------------------

	namespace LogUtil
	{
		CString GetFullDirectoryPath()
		{
			TCHAR exe_path[MAX_PATH] = { 0 , };
			::GetModuleFileName( NULL , exe_path , MAX_PATH );
			PathRemoveFileSpec(exe_path);

			return CString( exe_path );
		}
	};
}