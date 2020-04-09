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

	THREAD_REQUEST  m_CurRequest;  // Thread 에게 요청시에 대입한다.
	THREAD_RESPONSE m_CurResponse; // Thread 의 현재 상태 값이다.

	HANDLE m_hThread;	// 스레드 핸들

	_beginthreadex_proc_type m_pFun; // 호출할 함수 포인터 주소
	void*  m_pParm;					 // 호출할 함수의 추가 파라미터

	DWORD m_dwSleepTick;			// REQUEST_SLEEP 요청을 받았을때 얼마만큼 대기 할것인지를 결정하는 변수

	static SyncMap< DWORD , CThread* > m_ThreadMap; // GetCurrentThreadId 함수를 통해서 CThread* 객체 핸들을 얻어올때 사용하는 함수
};