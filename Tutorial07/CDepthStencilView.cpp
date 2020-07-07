/**
* @LC		: 02/07/2020
* @file		: CDepthStencilView.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 01/07/2020
* @brief	: .
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CDepthStencilView.h"

CDepthStencilView::CDepthStencilView() {
	m_pDepthStencilView = NULL;
}

CDepthStencilView::~CDepthStencilView() {

}

void CDepthStencilView::setDesc(DepthStencilViewDesc inDesc) {
	m_Desc = inDesc;
}

void * CDepthStencilView::getDSV() {
	return m_pDepthStencilView;
}
