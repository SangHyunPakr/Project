#pragma once

#include "SyncObject.h"

class CThread
{
public:

	CThread();
	virtual ~CThread();

	BOOL Start( _beginthreadex_proc_type pFunctionProc , void* pParm , BOOL Suspend );
	void Exit( DWORD WaitTick );

	void Suspend( DWORD dwSleepTick = INFINITE );
	void Resume();

	static CThread* ConvertIdToThreadObject( DWORD ThreadId );

	inline HANDLE GetHandle() const { return m_hThread; }
	
private:

	static void DeleteThreadObject( DWORD ThreadId );
	static void MappingThreadObject( DWORD ThreadId , CThread* Object );

	static unsigned int __stdcall ThreadFunStub( void* param );
		unsigned int ThreadFun();

	static void __stdcall WakeUpFn( ULONG_PTR ) { /* do nothing */ }

private:

	enum THREAD_REQUEST
	{
		REQUEST_NONE,
		REQUEST_WORKING, 
		REQUEST_SLEEP,
		REQUEST_TERMINATING,
	};

	enum THREAD_RESPONSE
	{
		RESPONSE_NONE, 
		RESPONSE_WORKING, 
		RESPONSE_SLEEPING,
		RESPONSE_TERMINATED,
	};

	THREAD_REQUEST  m_CurRequest;  // Thread ���� ��û�ÿ� �����Ѵ�.
	THREAD_RESPONSE m_CurResponse; // Thread �� ���� ���� ���̴�.

	HANDLE m_hThread;	// ������ �ڵ�

	_beginthreadex_proc_type m_pFun; // ȣ���� �Լ� ������ �ּ�
	void*  m_pParm;					 // ȣ���� �Լ��� �߰� �Ķ����

	DWORD m_dwSleepTick;			// REQUEST_SLEEP ��û�� �޾����� �󸶸�ŭ ��� �Ұ������� �����ϴ� ����

	static SyncMap< DWORD , CThread* > m_ThreadMap; // GetCurrentThreadId �Լ��� ���ؼ� CThread* ��ü �ڵ��� ���ö� ����ϴ� �Լ�
};