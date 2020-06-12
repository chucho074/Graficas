/**
* @LC		: 24/02/2020
* @file		: CViewport.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 18/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CViewPort.h"

CViewPort::CViewPort() {

}

CViewPort::~CViewPort() {

}

void CViewPort::init(ViewPortDesc inDesc) {
#ifdef D_DIRECTX
	m_Viewport.Width	= inDesc.W;
	m_Viewport.Height	= inDesc.H;
	m_Viewport.MinDepth = inDesc.minDepth;
	m_Viewport.MaxDepth = inDesc.maxDepth;
	m_Viewport.TopLeftX = inDesc.topLeftX;
	m_Viewport.TopLeftY = inDesc.topLeftY;
#endif
}