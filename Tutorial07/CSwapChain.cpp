#include "CSwapChain.h"

CSwapChain::CSwapChain() {
	m_SwapChain = NULL;
}

CSwapChain::~CSwapChain() {
	if (m_SwapChain) {
		m_SwapChain->Release();
		m_SwapChain = nullptr;
	}
}

HRESULT CSwapChain::getBBuffer(CTexture2D & inBBuffer) {
	HRESULT hr = S_OK;
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&inBBuffer.m_Texture);
	return hr;
}

void CSwapChain::render() {
	m_SwapChain->Present(0, 0);
}
