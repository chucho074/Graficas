/**
* @LC		: 24/02/2020
* @file		: CTexture2D.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 13/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CTexture2D.h"

CTexture2D::CTexture2D() {
#ifdef D_DIRECTX
	m_pTexture = NULL;
#endif
}

CTexture2D::~CTexture2D() {

}

void CTexture2D::init(TextureDesc inDesc) {
	m_Data = inDesc;
#ifdef D_DIRECTX
	ZeroMemory(&m_Desc, sizeof(m_Desc));

	m_Desc.Width = m_Data.W;
	m_Desc.Height = m_Data.H;
	m_Desc.MipLevels = m_Data.mipLevels;
	m_Desc.ArraySize = m_Data.arraySize;
	m_Desc.Format = (DXGI_FORMAT)m_Data.format;
	m_Desc.SampleDesc.Count = m_Data.sampleDesc.count;
	m_Desc.SampleDesc.Quality = m_Data.sampleDesc.quality;
	m_Desc.Usage = (D3D11_USAGE)m_Data.usage;
	m_Desc.BindFlags = m_Data.flags;
	m_Desc.CPUAccessFlags = m_Data.cpuAccessFlags;
	m_Desc.MiscFlags = m_Data.miscFlags;
#endif
}

void * CTexture2D::getTexture() {
#ifdef D_DIRECTX
	return m_pTexture;
#else
	return nullptr;
#endif
}
