#pragma once

#include <windows.h>
#include <list>
#include <map>

struct movable_critical_section
{
	movable_critical_section() : moved_( FALSE ) {}

	CRITICAL_SECTION cs_;
	BOOL			 moved_;
};

class CriticalSectionRAII
{
public:

	CriticalSectionRAII(CRITICAL_SECTION& cs) : cs_(cs) { EnterCriticalSection(&cs_); }
	~CriticalSectionRAII() { LeaveCriticalSection(&cs_); }

private:

	CRITICAL_SECTION & cs_;
};

template< typename T >
class SyncList
{
public:

	SyncList() { InitializeCriticalSectionAndSpinCount(&m_NowUse , 3000); }
	~SyncList() { DeleteCriticalSection(&m_NowUse); }

	void PushBack(const T& Data)
	{
		CriticalSectionRAII obj(m_NowUse);

		m_List.push_back(Data);
	}

	void PushFront(const T& Data)
	{
		CriticalSectionRAII obj(m_NowUse);

		m_List.push_front(Data);
	}

	BOOL PopBack(T& t)
	{
		CriticalSectionRAII obj(m_NowUse);

		if ( Count() <= 0 ) return FALSE;

		t = Back();
		m_List.pop_back();

		return TRUE;
	}

	BOOL PopFront(T& t)
	{
		CriticalSectionRAII obj(m_NowUse);

		if ( Count() <= 0 ) return FALSE;

		t = Front();
		m_List.pop_front();

		return TRUE;
	}

	T& Front()
	{
		CriticalSectionRAII obj(m_NowUse);

		return m_List.front();
	}

	T& Back()
	{
		CriticalSectionRAII obj(m_NowUse);

		return m_List.back();
	}

	int Count()
	{
		CriticalSectionRAII obj(m_NowUse);

		return (int)m_List.size();
	}

	bool Empty()
	{
		CriticalSectionRAII obj(m_NowUse);

		return m_List.empty();
	}

private:

	CRITICAL_SECTION m_NowUse;
	std::list< T >   m_List;
};

template< typename KEY , typename VALUE >
class SyncMap
{
public:

	SyncMap()
	{
		InitializeCriticalSectionAndSpinCount( &m_cs.cs_ , 2000 );
	}

	~SyncMap()
	{
		if ( !m_cs.moved_ )
			DeleteCriticalSection(&m_cs.cs_);

		m_map.clear();
	}

	SyncMap( SyncMap&& rhs )
	{
		if ( !rhs.m_cs.moved_ ) 
			m_cs = rhs.m_cs;
		else					
			InitializeCriticalSectionAndSpinCount(&m_cs.cs_ , 2000);
		
		rhs.m_cs.moved_ = true;
		m_map = std::move( rhs.m_map );
	}

	SyncMap( const SyncMap& rhs )
	{
		InitializeCriticalSectionAndSpinCount(&m_cs.cs_ , 2000);
		
		m_map = rhs.m_map;
	}

	BOOL Has(const KEY& k)
	{
		CriticalSectionRAII obj(m_cs.cs_);

		std::map< KEY , VALUE >::iterator result = m_map.find(k);
		return (result != m_map.end());
	}

	VALUE& Get(const KEY& k)
	{
		CriticalSectionRAII obj(m_cs.cs_);

		return m_map[k];
	}

	void Set(const KEY& k , const VALUE& v)
	{
		CriticalSectionRAII obj(m_cs.cs_);

		m_map[k] = v;
	}

	int Count() const
	{
		CriticalSectionRAII obj(m_cs.cs_);

		return (int)m_map.size();
	}

	BOOL Delete(const KEY& k)
	{
		CriticalSectionRAII obj(m_cs.cs_);

		std::map< KEY , VALUE >::iterator result = m_map.find(k);

		if ( result == m_map.end() ) return false;

		m_map.erase( result );

		return true;
	}

	void Clear()
	{
		CriticalSectionRAII obj(m_cs.cs_);

		m_map.clear();
	}

	inline VALUE& operator[]( const KEY& k ) { return Get( k ); }

	inline void Enter() { EnterCriticalSection(&m_cs.cs_); }
	inline void Leave() { LeaveCriticalSection(&m_cs.cs_); }

	typename std::map< KEY , VALUE >::iterator begin() { return m_map.begin(); }
	typename std::map< KEY , VALUE >::iterator end()   { return m_map.end(); }

private:

	mutable movable_critical_section m_cs;
	std::map< KEY , VALUE > m_map;
};

template< typename C , typename D >
void ReleaseContainer( C& c , D d )
{
	c.Enter();

	auto cur = c.begin();
	auto end = c.end();

	for ( ; cur != end ; ++cur )
		d( (*cur) );

	c.Leave();
}
