/**
* @LC		: 24/02/2020
* @file		: CRenderTargetView.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#include "CRenderTargetView.h"

CRenderTargetView::CRenderTargetView() {
#ifdef D_DIRECTX
	m_pRTV = NULL;
#endif
}

CRenderTargetView::~CRenderTargetView() {

}

void CRenderTargetView::init(RenderTargetViewDesc inDesc) {
#ifdef D_DIRECTX
	ZeroMemory(&m_Desc, sizeof(m_Desc));
	m_Desc.Format = (DXGI_FORMAT)inDesc.format;
	m_Desc.ViewDimension = (D3D11_RTV_DIMENSION)inDesc.viewDimension;
	m_Desc.Texture2D.MipSlice = inDesc.texture2D.mipSlice;
#endif
}

void * CRenderTargetView::getRTV() {
#ifdef D_DIRECTX
	return m_pRTV;
#else
	return nullptr;
#endif
}
