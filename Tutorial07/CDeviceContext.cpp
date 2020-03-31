/**
* @LC		: 24/02/2020
* @file		: CDeviceContext.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CDeviceContext.h"

CDeviceContext::CDeviceContext() {
#ifdef D_DIRECTX
	m_DeviceContext = NULL;
#endif
}

CDeviceContext::~CDeviceContext() {

}

CDeviceContext * CDeviceContext::getInstance() {
	if (m_DCInstance == nullptr) {
		m_DCInstance = new CDeviceContext();
	}
	return m_DCInstance;
}

void * CDeviceContext::getDeviceContext() {
#ifdef D_DIRECTX
	return m_DeviceContext;
#else
	return nullptr;
#endif
}
