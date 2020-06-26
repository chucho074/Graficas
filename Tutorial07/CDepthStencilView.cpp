/**
* @LC		: 24/02/2020
* @file		: CDepthStencilView.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs
**/

/**
* Headers
**/
#include "CDepthStencilView.h"

CDepthStencilView::CDepthStencilView() {
#ifdef D_DIRECTX
	m_pDepthStencilView = NULL;
#endif 
}

void CDepthStencilView::init(DepthStencilViewDesc inDesc /*, FORMAT inFormat*/) {
#ifdef D_DIRECTX
	ZeroMemory(&m_pDepthStencilView, sizeof(m_pDepthStencilView));
	/*m_Desc.Format = (DXGI_FORMAT)inFormat;*/
	m_Desc.Format = (DXGI_FORMAT)inDesc.format;
	m_Desc.ViewDimension = (D3D11_DSV_DIMENSION)inDesc.viewDimension;
	m_Desc.Texture2D.MipSlice = inDesc.texture2D.mipSlice;
#endif
}

void * CDepthStencilView::getDSV() {
#ifdef D_DIRECTX
	return m_pDepthStencilView;
#else
	return nullptr;
#endif
}
