#include "CDevice.h"

CDevice::CDevice() {
	m_Device = NULL;
}

CDevice::~CDevice() {

}

HRESULT CDevice::createBuffer(CBuffer & inBuffer, D3D11_BUFFER_DESC inDesc, D3D11_SUBRESOURCE_DATA inSRD) {
	HRESULT hr = S_OK;
	//D3D11_BUFFER_DESC TempDesc = createDesc(inDesc);
	ID3D11Buffer * BufferTemp = inBuffer.m_Buffer;
	if (inBuffer.m_Desc.SRD.psysMem == NULL) {
		hr = m_Device->CreateBuffer(&inDesc, NULL, &inBuffer.m_Buffer);
	}
	else {
		//D3D11_SUBRESOURCE_DATA  TempSRD = createSRD(inDesc);
		hr = m_Device->CreateBuffer(&inDesc, &inSRD, &inBuffer.m_Buffer);
	}
	return hr;
}

HRESULT CDevice::createRTV(CTexture2D & inTexture, CRenderTargetView & inRTV) {
	HRESULT hr = S_OK;
	hr = m_Device->CreateRenderTargetView(inTexture.m_Texture, NULL, &inRTV.m_RTV);
	return hr;
}

HRESULT CDevice::createTexture(CTexture2D & inTexture, D3D11_TEXTURE2D_DESC inDesc) {
	HRESULT hr = S_OK;
	hr = m_Device->CreateTexture2D(&inDesc, NULL, &inTexture.m_Texture);
	return hr;
}

HRESULT CDevice::createDSV(CTexture2D & inDStencil, CDepthStencilView & inDSView, D3D11_DEPTH_STENCIL_VIEW_DESC inDesc) {
	HRESULT hr = S_OK;
	hr = m_Device->CreateDepthStencilView(inDStencil.m_Texture, &inDesc, &inDSView.m_pDepthStencilView);
	return hr;
}

HRESULT CDevice::createVShader(ID3DBlob * inBlob, ID3D11ClassLinkage * inClass, ID3D11VertexShader *& inVS) {
	HRESULT hr = S_OK;
	hr = m_Device->CreateVertexShader(inBlob->GetBufferPointer(), inBlob->GetBufferSize(), inClass, &inVS);
	return hr;
	
}

HRESULT CDevice::createILayout(D3D11_INPUT_ELEMENT_DESC * inILDesc, unsigned int inNumElem, ID3DBlob *& inBlob, ID3D11InputLayout *& inIL) {
	HRESULT hr = S_OK;
	hr = m_Device->CreateInputLayout(inILDesc, inNumElem, inBlob->GetBufferPointer(),
		inBlob->GetBufferSize(), &inIL);
	return hr;
}

HRESULT CDevice::createPShader(ID3DBlob * inBlob, ID3D11PixelShader * inPS) {
	HRESULT hr = S_OK;
	hr = m_Device->CreatePixelShader(inBlob->GetBufferPointer(), inBlob->GetBufferSize(), NULL, &inPS);
	return hr;
}

HRESULT CDevice::createSampler(D3D11_SAMPLER_DESC inDesc, CSamplerState & inSampler) {
	HRESULT hr = S_OK;
	//hr = m_Device->CreateSamplerState(&inDesc, (ID3D11SamplerState *)inSampler.getSampler());
	return hr;
}
