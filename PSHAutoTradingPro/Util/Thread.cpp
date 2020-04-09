#include "stdafx.h"
#include "Thread.h"
#include <process.h>

SyncMap< DWORD , CThread* > CThread::m_ThreadMap;

CThread* CThread::ConvertIdToThreadObject( DWORD ThreadId ) 
{ 
	if ( !m_ThreadMap.Has( ThreadId ) ) return NULL;

	return m_ThreadMap.Get( ThreadId ); 
}

void CThread::DeleteThreadObject( DWORD ThreadId )
{ 
	m_ThreadMap.Delete( ThreadId ); 
}

void CThread::MappingThreadObject( DWORD ThreadId , CThread* Object )
{ 
	m_ThreadMap.Set( ThreadId , Object );
}

CThread::CThread() 
{
	m_CurRequest  = REQUEST_NONE;
	m_CurResponse = RESPONSE_NONE;

	m_hThread = INVALID_HANDLE_VALUE;
	m_pFun    = NULL;
	m_pParm   = NULL;

	m_dwSleepTick = 0;
}

CThread::~CThread()
{
	try
	{
		Exit( INFINITE );
	}
	catch(...) { /*Do Noting*/ }
}

unsigned int __stdcall CThread::ThreadFunStub( void* param )
{
	CThread* this_ = (CThread*)param;
	return this_->ThreadFun();
}

// ∑Á«¡
unsigned int CThread::ThreadFun()
{
	if ( !m_pFun ) return -1;

	while ( m_CurRequest != REQUEST_TERMINATING )
	{
		if ( m_CurRequest == REQUEST_SLEEP )
		{
			m_CurResponse = RESPONSE_SLEEPING;
			SleepEx( m_dwSleepTick , TRUE );
		}

		if ( m_CurRequest == REQUEST_WORKING )
			m_pFun( m_pParm );
		
		m_CurResponse = RESPONSE_WORKING;
		//Sleep(5000);
	}

	m_CurResponse = RESPONSE_TERMINATED;

	CThread::DeleteThreadObject( GetCurrentThreadId() );

	return 0;
}

BOOL CThread::Start( _beginthreadex_proc_type pFunctionProc , void* pParm , BOOL Suspend )
{
	if ( !pFunctionProc  ) return FALSE;

	Exit( INFINITE );

	m_pFun  = pFunctionProc;
	m_pParm = pParm;
	
	if ( Suspend )
	{
		m_CurRequest = REQUEST_SLEEP;
		m_dwSleepTick = INFINITE;
	}
	else
	{
		m_CurRequest = REQUEST_WORKING;
	}

	DWORD ThreadId = 0;
	m_hThread = (HANDLE)_beginthreadex( NULL , 0 , ThreadFunStub , this , 0 , (unsigned int*)&ThreadId );

	CThread::MappingThreadObject( ThreadId , this );

	return TRUE;
}

void CThread::Exit( DWORD WaitTick )
{
	if ( m_hThread == INVALID_HANDLE_VALUE ) return;

	m_CurRequest = REQUEST_TERMINATING;
	QueueUserAPC( CThread::WakeUpFn , m_hThread ,  NULL );

	WaitForSingleObject( m_hThread , WaitTick );

	CloseHandle( m_hThread );

	m_hThread = INVALID_HANDLE_VALUE;
	m_pParm   = NULL;
}

void CThread::Suspend( DWORD dwSleepTick )
{
	m_dwSleepTick = dwSleepTick;
	m_CurRequest = REQUEST_SLEEP;
}

void CThread::Resume()
{
	m_CurRequest = REQUEST_WORKING;
	m_dwSleepTick = 0;

	if ( m_hThread == INVALID_HANDLE_VALUE ) return;
	QueueUserAPC( CThread::WakeUpFn , m_hThread ,  NULL );
}
