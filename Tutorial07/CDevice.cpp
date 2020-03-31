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

}

CDevice::~CDevice() {

}

CDevice * CDevice::getInstance() {
	 if (m_DeviceInstance == nullptr) {
		 m_DeviceInstance = new CDevice();
	 }
	 return m_DeviceInstance;
}

void CDevice::init(DeviceDesc inDesc) {
	 Desc = inDesc;
}

void * CDevice::getDevice() {
#ifdef D_DIRECTX
	 return Device;
#else
	 return nullptr;
#endif
}
