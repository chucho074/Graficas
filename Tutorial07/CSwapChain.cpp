/**
* @LC		: 24/02/2020
* @file		: CSwapChain.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CSwapChain.h"

CSwapChain::CSwapChain() {
#ifdef D_DIRECTX
	m_SwapChain = nullptr;
#endif
}


CSwapChain::~CSwapChain() {


}


void CSwapChain::init(SwapChainDesc inDesc) {
#ifdef D_DIRECTX
	ZeroMemory(&m_SCDesc, sizeof(m_SCDesc));
	m_SCDesc.BufferCount = inDesc.bufferCount;
	m_SCDesc.BufferDesc.Width = inDesc.W;
	m_SCDesc.BufferDesc.Height = inDesc.H;
	m_SCDesc.BufferDesc.Format = (DXGI_FORMAT)inDesc.format;
	m_SCDesc.BufferDesc.RefreshRate.Numerator = inDesc.refreshNumerator;
	m_SCDesc.BufferDesc.RefreshRate.Denominator = inDesc.refreshDenominator;
	m_SCDesc.BufferUsage = inDesc.bufferUsage;
	m_SCDesc.OutputWindow = (HWND)inDesc.outputWND;
	m_SCDesc.SampleDesc.Count = inDesc.count;
	m_SCDesc.SampleDesc.Quality = inDesc.quality;
	m_SCDesc.Windowed = inDesc.windowed;
#endif
}


void * CSwapChain::getSwapChain() {
#ifdef D_DIRECTX
	return m_SwapChain;
#else
	return nullptr;
#endif
}


HRESULT CSwapChain::getBuffer(CTexture2D & inTexture) {
#ifdef D_DIRECTX
	if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&inTexture.m_Texture))) {
		return false;
	}
	else { 	return S_OK; 
	}
#endif
	return E_NOTIMPL;
}
