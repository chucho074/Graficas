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
	m_DeviceContext = nullptr;
#endif
}


CDeviceContext::~CDeviceContext() {

}

void * CDeviceContext::getDeviceContext() {
#ifdef D_DIRECTX
	return m_DeviceContext;
#else
	return nullptr;
#endif
}


void CDeviceContext::setViewport(CViewPort inVP) {
#ifdef D_DIRECTX
	m_DeviceContext->RSSetViewports(1, &inVP.m_Viewport);
#endif
}


void CDeviceContext::setILayout(CVertexShader & inVS) {
#ifdef D_DIRECTX
	m_DeviceContext->IASetInputLayout(inVS.m_InputLayout);
#endif
}
