/**
* @LC		: 24/02/2020
* @file		: CDevice.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CDevice.h"

CDevice::CDevice() {
#ifdef D_DIRECTX
	Device = nullptr;
	
#endif
}


CDevice::~CDevice() {

}


//CDevice * CDevice::getInstance() {
//	 if (m_DeviceInstance == nullptr) {
//		 m_DeviceInstance = new CDevice();
//	 }
//	 return m_DeviceInstance;
//}


void CDevice::init(DeviceDesc inDesc) {
	//Desc = inDesc;

	DeviceDesc xDesc;


	Desc.DriverType = inDesc.DriverType;
	Desc.DeviceFlags = inDesc.DeviceFlags;
	Desc.DriverTypes[0] = inDesc.DriverTypes[0];
	Desc.DriverTypes[1] = inDesc.DriverTypes[1];
	Desc.DriverTypes[2] = inDesc.DriverTypes[2];
	Desc.FeatureLevels[0] = inDesc.FeatureLevels[0];
	Desc.FeatureLevels[1] = inDesc.FeatureLevels[1];
	Desc.FeatureLevels[2] = inDesc.FeatureLevels[2];
	Desc.numFeatureLevels = inDesc.numFeatureLevels;

}


void * CDevice::getDevice() {
#ifdef D_DIRECTX
	 return Device;
#else
	 return nullptr;
#endif
}
