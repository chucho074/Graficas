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
	//m_pSwapChain = nullptr;
#endif
}

CSwapChain::~CSwapChain() {


}

void CSwapChain::init(SwapChainDesc inDesc) {
#ifdef D_DIRECTX
	ZeroMemory(&m_sd, sizeof(m_sd));
	m_sd.BufferCount = inDesc.bufferCount;
	m_sd.BufferDesc.Width = inDesc.W;
	m_sd.BufferDesc.Height = inDesc.H;
	m_sd.BufferDesc.Format = (DXGI_FORMAT)inDesc.format;
	m_sd.BufferDesc.RefreshRate.Numerator = inDesc.refreshNumerator;
	m_sd.BufferDesc.RefreshRate.Denominator = inDesc.refreshDenominator;
	m_sd.BufferUsage = inDesc.bufferUsage;
	m_sd.OutputWindow = (HWND)inDesc.outputWND;
	m_sd.SampleDesc.Count = inDesc.count;
	m_sd.SampleDesc.Quality = inDesc.quality;
	m_sd.Windowed = inDesc.windowed;
#endif
}

CSwapChain * CSwapChain::getInstance() {
	if (m_pSCInstance == nullptr) {
		m_pSCInstance = new CSwapChain();
	}
	return m_pSCInstance;
}

void * CSwapChain::getSwapChain() {
#ifdef D_DIRECTX
	return m_pSwapChain;
#else
	return nullptr;
#endif
}
