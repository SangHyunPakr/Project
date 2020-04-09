#pragma once

struct LoggingSetting
{
	BOOL	write_date_;
	int     period_;
	CString	root_directory_;
};

namespace Log
{
	// Log ��Ͻÿ��� �Ʒ� �Լ��� ����Ѵ�. ( InitLog , DeleteLog , WriteLog )
	// ���� Logging Ŭ�������� ���� �Ҽ� ������, �Ű澲�� �ʾƵ� �ȴ�.

	// ���α׷� ����� �ѹ��� ȣ���Ѵ�.
	void    InitLog( int Period , LPCTSTR Folder ); // ���� ���α׷��� �������� ��ġ�� �α� ��Ʈ ���丮�� �ȴ�.
	void    InitLog( LPCTSTR RootDirectory , int Period );
	
	// �α׿� ��¥�� ����Ұ��ΰ� ?
	void    SetWriteDate( BOOL Write );

	// �ΰſ� ���õ� ������
	LoggingSetting GetLoggingSetting();
	void           SetLoggingSetting( LoggingSetting* p );

	// ���α׷� ����� �ѹ��� ȣ���Ѵ�.
	void	DeleteLog();

	// InitLog �Լ����� ȣ��� RootDirectory + LogCategory ���丮�� ���ں��� �αװ� ��ϵȴ�.
	HRESULT WriteLog( LPCTSTR LogCategory , LPCTSTR LogText , ... );

	namespace LogUtil
	{
		CString GetFullDirectoryPath();
	};
};