#include "stdafx.h"
#include "FileSystemUtil.h"

namespace FileSystemUtil
{

BOOL WriteFileLn( LPCTSTR path , LPCTSTR log , int len , DWORD* error_code )
{
	HandlePtr handle = GetFileHandle( path );
	if ( error_code ) *error_code = GetLastError();
	
	return WriteFileLn( handle.GetHandle() , log , len , error_code );
}

BOOL WriteFileLn( HANDLE h , LPCTSTR log , int len , DWORD* error_code )
{
	SetFilePointer( h , 0 , NULL , FILE_END );

	DWORD written_byte = 0;
	if ( !WriteFile( h , log , len * sizeof( TCHAR ) , &written_byte , NULL ) )
	{
		if ( error_code ) *error_code = GetLastError();
		return FALSE;
	}

	return TRUE;
}

HandlePtr GetFileHandle( LPCTSTR path )
{
	return HandlePtr( CreateFile( path , GENERIC_READ|GENERIC_WRITE , FILE_SHARE_READ , NULL , OPEN_ALWAYS , FILE_ATTRIBUTE_NORMAL , NULL ) );
}

CString GetFullDirectoryPath()
{
	TCHAR exe_path[MAX_PATH] = { 0 , };
	::GetModuleFileName( NULL , exe_path , MAX_PATH );
	PathRemoveFileSpec(exe_path);

	return CString( exe_path );
}


int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    switch (uMsg) 
	{    
    case BFFM_INITIALIZED:
		{
			if ( lpData )
				SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
		}
        break;
    }
    return 0;
}

CString ShowFolderSelectDialog( HWND Parent , LPCTSTR Title , LPCTSTR FirstFolderPath )
{
	BROWSEINFO  BrInfo = { 0 , };
	TCHAR		pszPathname[MAX_PATH] = { 0 , };
	
    BrInfo.hwndOwner	  = Parent;
    BrInfo.pszDisplayName = pszPathname;
    BrInfo.lpszTitle	  = Title;
    BrInfo.ulFlags		  = BIF_RETURNONLYFSDIRS;
	BrInfo.lpfn			  = BrowseCallbackProc;
	BrInfo.lParam		  = (LPARAM)FirstFolderPath;

    ITEMIDLIST* pidlBrowse = ::SHBrowseForFolder( &BrInfo );

    if ( pidlBrowse )
		SHGetPathFromIDList( pidlBrowse , pszPathname );
    
    return pszPathname;
}

};

static INIEntry tokenize_key_value( LPCTSTR src )
{
	CString key;
	CString value;

	AfxExtractSubString( key , src , 0 , _T('=') );
	AfxExtractSubString( value , src , 1 , _T('=') );

	return std::make_pair( key , value );
}

namespace INIFile
{

int ReadSection( LPCTSTR FilePath , std::list< CString >& out )
{
	if ( !FilePath ) return 0;

	TCHAR buffer[4096]={ 0 , };
	GetPrivateProfileString( NULL , _T("") , _T("") , buffer , 4096 , FilePath );

	StringUtil::TokenizeString( buffer , _T('\0') , out );
	return (int)out.size();
}

int ReadSectionEntry( LPCTSTR Section , LPCTSTR FilePath , std::list< INIEntry >& out )
{
	if ( !Section && !FilePath ) return 0;

	TCHAR buffer[4096]={ 0 , };
	GetPrivateProfileSection( Section , buffer , 4096 , FilePath );
	
	std::list< CString > key_value_list;
	if ( !StringUtil::TokenizeString( buffer , _T('\0') , key_value_list ) ) return 0;

	std::list< CString >::iterator cur = key_value_list.begin();
	std::list< CString >::iterator end = key_value_list.end();

	for ( ; cur != end ; ++cur )
	{
		CString& item = (*cur);
		out.push_back( tokenize_key_value( item ) );
	}

	return (int)out.size();
}

CString ReadString( LPCTSTR Section , LPCTSTR Key , LPCTSTR FilePath )
{
	if ( !Section && !FilePath ) return _T("");

	TCHAR buffer[1024] = { 0 , };
	GetPrivateProfileString( Section , Key , NULL , buffer , 1024 , FilePath );

	return buffer;
}

UINT ReadInt( LPCTSTR Section , LPCTSTR Key , LPCTSTR FilePath )
{
	if ( !Section && !FilePath ) return 0;

	return GetPrivateProfileInt( Section , Key , 0 , FilePath );
}

double  ReadDouble( LPCTSTR Section , LPCTSTR Key , LPCTSTR FilePath )
{
	if ( !Section && !FilePath ) return 0;

	return _ttof( ReadString( Section , Key , FilePath ) );
}

BOOL WriteString( LPCTSTR Section , LPCTSTR Key , LPCTSTR Value , LPCTSTR FilePath )
{
	if ( !Section && !Key && !Value && !FilePath ) return FALSE;

	return WritePrivateProfileString( Section , Key , Value , FilePath );
}

BOOL WriteInt( LPCTSTR Section , LPCTSTR Key , int Value , LPCTSTR FilePath )
{
	CString Data;
	Data.Format( _T("%d") , Value );
	return WriteString( Section , Key , Data , FilePath );
}

BOOL WriteDouble( LPCTSTR Section , LPCTSTR Key , double Value , LPCTSTR FilePath )
{
	CString Data;
	Data.Format( _T("%f") , Value );
	return WriteString( Section , Key , Data , FilePath );
}

};