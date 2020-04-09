#pragma once

//------------------------------------------------------------------------------------------------------------------------
class DeviceDataProxy;

template< typename KEY , typename VALUE > class SyncMap;
typedef SyncMap< int/*DeviceName*/ , float/*DeviceValue*/ > DeviceDataMap;
class DeviceData
{
public:

	DeviceData();
	~DeviceData();
	DeviceData( const DeviceData& rhs );

	float operator[]( int DeviceName ) const;

	void	SetDate( LPCTSTR Date );
	LPCTSTR GetDate();

	inline DeviceDataMap& GetDeviceDataMap() { return value_; }

private:

	CString date_;

	DeviceDataMap value_;
};
//------------------------------------------------------------------------------------------------------------------------
//class DeviceDataProxy
//{
//public:
//
//	explicit DeviceDataProxy( DeviceDataMap& map , int key );
//	~DeviceDataProxy();
//
//	operator float() const;
//	float operator=( float data );
//
//private:
//
//	DeviceDataMap& map_;
//	int key_;
//};
//------------------------------------------------------------------------------------------------------------------------