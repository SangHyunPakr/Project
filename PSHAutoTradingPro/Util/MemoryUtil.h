#pragma once

//--------------------------------------------------------------------------------------------------
// 김동현 2018-04-17 09:46:38 RAII 클래스 추가
template< typename T > struct DummyCtor{ inline void operator()( T* obj ) const {} };
template< typename T > struct DummyDtor{ inline void operator()( T* obj ) const {} };

template< typename T >
struct ArrayDtor
{
	inline void operator()( T* ArrayObject ) const { delete[] ArrayObject; }
};

template< typename T , typename C = DummyCtor<T> , typename D = DummyDtor<T> >
class ObjectPtr /* it's like the std::unique_ptr object */
{
public:

	explicit ObjectPtr() : obj_( NULL ) {}
	explicit ObjectPtr(T* obj) : obj_(obj) { c( obj ); }

	/*non explicit*/ObjectPtr( ObjectPtr&& rhs ) : obj_( rhs.Reset() ) {}

	~ObjectPtr() { d( obj_ ); }

	T* Set( T* obj )
	{
		T* temp = obj_;
		obj_ = obj;

		return temp;
	}

	inline T* Reset(){ return Set( NULL ); }

	inline T* operator->() const { return obj_;    }
	inline T* get()		   const { return obj_;    }

private:

	ObjectPtr( const ObjectPtr& rhs ) = delete; // not implement

private:

	T* obj_;

	C c;
	D d;
};
//--------------------------------------------------------------------------------------------------