/**
* @LC		: 25/06/2020
* @file		: CGraphicsAPI.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 23/06/2020
* @brief	: A class for the control of the Device, DevContext and SwapChain.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CGraphicsAPI.h"


CGraphicsAPI::CGraphicsAPI() {
	m_Device = NULL;
	m_DeviceContext = NULL;
	m_SwapChain = NULL;

	m_driverType = D3D_DRIVER_TYPE_NULL;
	m_featureLevel = D3D_FEATURE_LEVEL_11_0;
}


CGraphicsAPI::~CGraphicsAPI() {
	destroy();
}


HRESULT CGraphicsAPI::init(unsigned int inDevFlag, DXGI_SWAP_CHAIN_DESC inSCDesc) {
	HRESULT hr = S_OK;
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);
	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_NULL;;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, driverType, NULL, inDevFlag, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &inSCDesc, &m_SwapChain, &m_Device, &m_featureLevel, &m_DeviceContext);
		if (SUCCEEDED(hr)) {
			break;
		}
	}
	m_driverType = driverType;
	return hr;
}


int CGraphicsAPI::update() {

	return 0;
}


void CGraphicsAPI::render() {
	

}


void CGraphicsAPI::destroy() {
	if (m_DeviceContext) {
		m_DeviceContext->ClearState();
	}
	if (m_SwapChain) {
		m_SwapChain->Release();
		m_SwapChain = nullptr;
	}
	if (m_DeviceContext) {
		m_DeviceContext->Release();
		m_DeviceContext = nullptr;
	}
	if (m_Device) {
		m_Device->Release();
		m_Device = nullptr;
	}

}


HRESULT CGraphicsAPI::createRTV(ID3D11Texture2D *& inBBuffer, ID3D11RenderTargetView *& inRTV) {
	HRESULT hr = S_OK;
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&inBBuffer);
	if (FAILED(hr)) {
		return hr;
	}
	hr = m_Device->CreateRenderTargetView(inBBuffer, NULL, &inRTV);
	return hr;
}


HRESULT CGraphicsAPI::createTex2D(D3D11_TEXTURE2D_DESC inDesc, ID3D11Texture2D *& inTex) {
	HRESULT hr = S_OK;
	hr = m_Device->CreateTexture2D(&inDesc, NULL, &inTex);
	return hr;
}


HRESULT CGraphicsAPI::createDSV(ID3D11Texture2D *& inDS, D3D11_DEPTH_STENCIL_VIEW_DESC inDSVDesc, ID3D11DepthStencilView *& inDSV) {
	HRESULT hr = S_OK;
	hr = m_Device->CreateDepthStencilView(inDS, &inDSVDesc, &inDSV);
	return hr;
}


void CGraphicsAPI::setRTargets(unsigned int inNumViews, ID3D11RenderTargetView * inRTV, ID3D11DepthStencilView * inDSV) {
	m_DeviceContext->OMSetRenderTargets(inNumViews, &inRTV, inDSV);
}


HRESULT CGraphicsAPI::createBuffer(CBuffer & inBuffer) {
	HRESULT hr = S_OK;
	
	hr = m_Device->CreateBuffer(&inBuffer.getDxDesc(), &inBuffer.getDxSRD(), &inBuffer.m_Buffer);
	
	return hr;
}


HRESULT CGraphicsAPI::createConstBuffer(CBuffer & inBuffer) {
	HRESULT hr = S_OK;

	hr = m_Device->CreateBuffer(&inBuffer.getDxDesc(), NULL, &inBuffer.m_Buffer);

	return hr;
}

void CGraphicsAPI::setVPort(D3D11_VIEWPORT inVP) {
	m_DeviceContext->RSSetViewports(1, &inVP);
}


HRESULT CGraphicsAPI::createVS(ID3DBlob *& inBlob, ID3D11ClassLinkage * inClass, ID3D11VertexShader *& inVS) {
	HRESULT hr = S_OK;
	hr = m_Device->CreateVertexShader(inBlob->GetBufferPointer(), inBlob->GetBufferSize(), inClass, &inVS);
	return hr;
}


HRESULT CGraphicsAPI::createIL(D3D11_INPUT_ELEMENT_DESC * inILDesc, unsigned int inNumElem, ID3DBlob *& inBlob, ID3D11InputLayout *& inIL) {
	HRESULT hr = S_OK;
	hr = m_Device->CreateInputLayout(inILDesc, inNumElem, inBlob->GetBufferPointer(),
		inBlob->GetBufferSize(), &inIL);
	return hr;
}


void CGraphicsAPI::setIL(ID3D11InputLayout * inIL) {
	m_DeviceContext->IASetInputLayout(inIL);
}


HRESULT CGraphicsAPI::createPS(ID3DBlob *& inBlob, ID3D11ClassLinkage * inClass, ID3D11PixelShader *& inPS) {
	HRESULT hr = S_OK;
	hr = m_Device->CreatePixelShader(inBlob->GetBufferPointer(), inBlob->GetBufferSize(), inClass, &inPS);

	return hr;
}


void CGraphicsAPI::setVBuffer(int inStartSlot, unsigned int inSize, CBuffer * inVBuffer) {
	unsigned int offset = 0;
	m_DeviceContext->IASetVertexBuffers(inStartSlot, 1, inVBuffer->getBuffer(), &inSize, &offset);
}


void CGraphicsAPI::setIBuffer(int inFormat, CBuffer * inIBuffer) {
	m_DeviceContext->IASetIndexBuffer(*inIBuffer->getBuffer(), (DXGI_FORMAT)inFormat, 0);
}


void CGraphicsAPI::setConstBuffer(int inStartSlot, bool inSetBoth, CBuffer * inConstBuffer) {
	m_DeviceContext->VSSetConstantBuffers(inStartSlot, 1, inConstBuffer->getBuffer());
	if (inSetBoth) {
		m_DeviceContext->PSSetConstantBuffers(inStartSlot, 1, inConstBuffer->getBuffer());
	}
}


void CGraphicsAPI::setTopology(D3D_PRIMITIVE_TOPOLOGY inTopology) {
	m_DeviceContext->IASetPrimitiveTopology(inTopology);
}


HRESULT CGraphicsAPI::createSState(D3D11_SAMPLER_DESC inSSDesc, ID3D11SamplerState *& inSampler) {
	HRESULT hr = S_OK;
	hr = m_Device->CreateSamplerState(&inSSDesc, &inSampler);
	return hr;
}


void CGraphicsAPI::updateBuffer(void * inData, CBuffer inBuffer) {
	// Compare the size of the Buffer and the input data
	if (sizeof(inBuffer.m_Desc.SRD.psysMem) == sizeof(inData)) {
		//Function de update subresource data 
		m_DeviceContext->UpdateSubresource(inBuffer.m_Buffer, 0, NULL, &inData, 0, 0);

	}
}

void CGraphicsAPI::setShaders(ID3D11VertexShader * inVS, ID3D11PixelShader * inPS) {	//Setear en distintas funciones
	m_DeviceContext->VSSetShader(inVS, NULL, 0);
	m_DeviceContext->PSSetShader(inPS, NULL, 0);
}

void CGraphicsAPI::setSResource(ID3D11ShaderResourceView * inSRV) {
	m_DeviceContext->PSSetShaderResources(0, 1, &inSRV);
}

void CGraphicsAPI::setSampler(ID3D11SamplerState * inSS) {
	m_DeviceContext->PSSetSamplers(0, 1, &inSS);
}

void CGraphicsAPI::draw(unsigned int inNumIndex) {
	m_DeviceContext->DrawIndexed(inNumIndex, 0, 0);
}

void CGraphicsAPI::show() {
	m_SwapChain->Present(0, 0);
}

ID3D11Device * CGraphicsAPI::getDev() {
	return m_Device;
}

D3D_DRIVER_TYPE CGraphicsAPI::getDriverType() {
	return m_driverType;
}

void CGraphicsAPI::clearRTV(ID3D11RenderTargetView * inRTV, float inColor[4]) {
	m_DeviceContext->ClearRenderTargetView(inRTV, inColor);
	
}

void CGraphicsAPI::clearDSV(ID3D11DepthStencilView * inDSV, D3D11_CLEAR_FLAG inFlag) {
	m_DeviceContext->ClearDepthStencilView(inDSV, inFlag, 1.0f, 0);
}

