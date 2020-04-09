#pragma once

#include <list>

namespace StringUtil
{

int		TokenizeString( LPCTSTR src , TCHAR step , std::list< CString >& list );
CString IntergetToString(int data);

};
