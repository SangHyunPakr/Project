#include "stdafx.h"
#include "StringUtil.h"

namespace StringUtil
{

int TokenizeString( LPCTSTR src , TCHAR step , std::list< CString >& list )
{
	int index = 0;
	
	CString token;

	do
	{
		AfxExtractSubString( token , src , index++ , step );
		if ( token.IsEmpty() ) break;

		list.push_back( token );

	}while( true );
	
	return (int)list.size();
}


CString IntergetToString(int data)
{
	CString strResult;
	strResult.Format("%d", data);
	return strResult;
}
};