#include "stdafx.h"
#include "deviceData.h"

//------------------------------------------------------------------------------------------------------------------------

DeviceData::DeviceData() = default;
DeviceData::~DeviceData() = default;
DeviceData::DeviceData( const DeviceData& rhs ) = default;

void	DeviceData::SetDate( LPCTSTR Date ) { date_ = Date; }
LPCTSTR DeviceData::GetDate() { return (LPCTSTR)date_; }

float DeviceData::operator[]( int DeviceName ) const  
{ 
	return const_cast<DeviceData*>(this)->GetDeviceDataMap()[DeviceName];
}
//------------------------------------------------------------------------------------------------------------------------
//DeviceDataProxy::DeviceDataProxy( DeviceDataMap& map , int key ) : map_( map ) , key_(key)  {}
//DeviceDataProxy::~DeviceDataProxy() = default;
//
//DeviceDataProxy::operator float() const
//{
//	return map_[key_];
//}
//
//float DeviceDataProxy::operator=( float data )
//{
//	map_[key_] = data;
//	
//	return data;
//}
//------------------------------------------------------------------------------------------------------------------------