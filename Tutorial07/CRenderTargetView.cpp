/**
* @LC		: 06/07/2020
* @file		: CRenderTargetView.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 01/07/2020
* @brief	: .
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CRenderTargetView.h"


CRenderTargetView::CRenderTargetView() {
	m_RTV = NULL;
}


CRenderTargetView::~CRenderTargetView() {
	destroy();
}


void CRenderTargetView::setDesc(RenderTargetViewDesc inDesc) {
	m_Desc = inDesc;
}


void * CRenderTargetView::getRTV() {
	return m_RTV;
}



void CRenderTargetView::destroy() {
	if (m_RTV) {
		m_RTV->Release();
		m_RTV = nullptr;
	}
}
