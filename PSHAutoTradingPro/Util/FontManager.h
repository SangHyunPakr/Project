#pragma once

#include "SyncObject.h"

typedef SyncMap< int/*FontSize*/ , CFont* > FontEntry;
typedef SyncMap< CString/*Font Name*/ , FontEntry* > FontTable;

class CFontManager
{
public:

	static CFontManager* GetInstance();
	static void			 ReleaseInstance();

	CFont* GetFont( int Size);
	CFont* GetFont( int Size , const CString& FontName );

private:

	CFontManager();
	~CFontManager();

private:

	static CFontManager* m_p;

	FontTable m_Table; 
};
