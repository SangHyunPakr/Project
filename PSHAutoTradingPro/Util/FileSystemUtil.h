#pragma once

#include <list>
typedef std::pair< CString , CString > INIEntry;

class HandlePtr
{
public:

	explicit HandlePtr( HANDLE h ) : h_(h) {}
	~HandlePtr() { CloseHandle( h_ ); }

	HandlePtr( HandlePtr& rhs )
	{
		h_ = rhs.h_;
		rhs.h_ = NULL;
	}

	inline HANDLE GetHandle() const { return h_; }

private:

	HANDLE h_;
};

namespace FileSystemUtil
{

BOOL WriteFileLn( LPCTSTR path , LPCTSTR log , int len , DWORD* error_code );
BOOL WriteFileLn( HANDLE h	   , LPCTSTR log , int len , DWORD* error_code );

HandlePtr GetFileHandle( LPCTSTR path );

CString GetFullDirectoryPath();

CString ShowFolderSelectDialog( HWND Parent , LPCTSTR Title , LPCTSTR FirstFolderPath );

};

namespace INIFile
{

int ReadSection( LPCTSTR FilePath , std::list< CString >& out );
int ReadSectionEntry( LPCTSTR Section , LPCTSTR FilePath , std::list< INIEntry >& out );

CString ReadString( LPCTSTR Section , LPCTSTR Key , LPCTSTR FilePath );
UINT    ReadInt( LPCTSTR Section , LPCTSTR Key , LPCTSTR FilePath );
double  ReadDouble( LPCTSTR Section , LPCTSTR Key , LPCTSTR FilePath );

BOOL	WriteString( LPCTSTR Section , LPCTSTR Key , LPCTSTR Value , LPCTSTR FilePath );
BOOL	WriteInt( LPCTSTR Section , LPCTSTR Key , int Value , LPCTSTR FilePath );
BOOL	WriteDouble( LPCTSTR Section , LPCTSTR Key , double Value , LPCTSTR FilePath );

};
