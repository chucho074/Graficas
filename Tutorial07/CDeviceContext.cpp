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


void CDeviceContext::zeroRT() {
#ifdef D_DIRECTX
	m_DeviceContext->OMSetRenderTargets(0, 0, 0);
#endif
}


void CDeviceContext::setRTarget(unsigned int inNumViews, CRenderTargetView & inRTV, CDepthStencilView & inDSV) {
#ifdef D_DIRECTX
	m_DeviceContext->OMSetRenderTargets(inNumViews, &inRTV.m_RTV, inDSV.m_pDepthStencilView);
		
#endif
}


void CDeviceContext::clearRTV(CRenderTargetView & inRTV, float & inColor) {
#ifdef D_DIRECTX
	m_DeviceContext->ClearRenderTargetView(inRTV.m_RTV, &inColor);
#endif
}


void CDeviceContext::clearDSV(CDepthStencilView & inDSV, unsigned int inFlags, float inDepth, unsigned int inStencil) {
#ifdef D_DIRECTX
	m_DeviceContext->ClearDepthStencilView(inDSV.m_pDepthStencilView, inFlags, inDepth, inStencil);
#endif
}


void CDeviceContext::setVS(CVertexShader & inShader) {
	m_DeviceContext->VSSetShader(inShader.m_VertexShader, NULL, 0);
}


void CDeviceContext::setPS(CPixelShader & inShader) {
	m_DeviceContext->PSSetShader(inShader.m_PixelShader, NULL, 0);
}


#ifdef D_DIRECTX
void CDeviceContext::setSResource(ID3D11ShaderResourceView * inSRV) {
	m_DeviceContext->PSSetShaderResources(0, 1, &inSRV);
}
#endif


void CDeviceContext::setSampler(CSamplerState & inSampler) {
	m_DeviceContext->PSSetSamplers(0, 1, &inSampler.m_pSamplerLinear);
}


void CDeviceContext::setDrawIndexed(int inIndex) {
	m_DeviceContext->DrawIndexed(inIndex, 0, 0);
}


void CDeviceContext::setVPorts(unsigned int inNumViews, CViewPort & inVP) {
#ifdef D_DIRECTX
	m_DeviceContext->RSSetViewports(inNumViews, &inVP.m_Viewport);
#endif
}
