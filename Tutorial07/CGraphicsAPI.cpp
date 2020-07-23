/**
* @LC		: 06/07/2020
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
#if (defined D_DirectX || defined R_DirectX)
	m_Device = NULL;
	m_DeviceContext = NULL;
	m_SwapChain = NULL;

	m_driverType = D3D_DRIVER_TYPE_NULL;
	m_featureLevel = D3D_FEATURE_LEVEL_11_0;
#endif
}


CGraphicsAPI::~CGraphicsAPI() {
	destroy();
}


#if (defined D_DirectX || defined R_DirectX) 
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
#endif


int CGraphicsAPI::update() {

	return 0;
}


void CGraphicsAPI::render() {
	

}


void CGraphicsAPI::destroy() {
#if (defined D_DirectX || defined R_DirectX)
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
#endif
}


HRESULT CGraphicsAPI::createBuffer(CBuffer & inBuffer, BufferDesc inDesc) {
	HRESULT hr = S_OK;
	hr = inBuffer.setDesc(inDesc);
#if (defined D_DirectX || defined R_DirectX) 
	D3D11_BUFFER_DESC TempDesc = createDesc(inDesc);
	ID3D11Buffer * BufferTemp = inBuffer.m_Buffer;
	if (inBuffer.m_Desc.SRD.psysMem == NULL) {
		hr = m_Device->CreateBuffer(&TempDesc, NULL, &inBuffer.m_Buffer);
	}
	else {
		D3D11_SUBRESOURCE_DATA  TempSRD = createSRD(inDesc);
		hr = m_Device->CreateBuffer(&TempDesc, &TempSRD, &inBuffer.m_Buffer);
	}
#endif
	return hr;
}


void CGraphicsAPI::setVBuffer(unsigned int inStartSlot, unsigned int inSize, CBuffer & inVBuffer) {
	unsigned int offset = 0;
#if (defined D_DirectX || defined R_DirectX) 
	ID3D11Buffer * BufferTemp = inVBuffer.getBuffer();
	m_DeviceContext->IASetVertexBuffers(inStartSlot, 1, &BufferTemp, &inSize, &offset);
#endif
}


//void CGraphicsAPI::setIBuffer(int inFormat, CMesh & inMesh) {
void CGraphicsAPI::setIBuffer(int inFormat, CBuffer & inIBuffer) {
#if (defined D_DirectX || defined R_DirectX) 
	m_DeviceContext->IASetIndexBuffer((ID3D11Buffer*)inIBuffer.getBuffer(), (DXGI_FORMAT)inFormat, 0);
#endif
}


void CGraphicsAPI::setVSConstBuffer(unsigned int inStartSlot, CBuffer & inConstBuffer) {
#if (defined D_DirectX || defined R_DirectX) 
	if (inStartSlot == 0) {
		m_DeviceContext->VSSetConstantBuffers(0, 1, &inConstBuffer.m_Buffer);
	}
	else {
		m_DeviceContext->VSSetConstantBuffers(inStartSlot, 1, &inConstBuffer.m_Buffer);
	}
#endif
}


void CGraphicsAPI::setPSConstBuffer(unsigned int inStartSlot, CBuffer & inConstBuffer) {
#if (defined D_DirectX || defined R_DirectX) 
	m_DeviceContext->PSSetConstantBuffers(0, 1, &inConstBuffer.m_Buffer);
#endif
}


void CGraphicsAPI::updateBuffer(void * inData, CBuffer & inBuffer) {
	// Compare the size of the Buffer and the input data
#if (defined D_DirectX || defined R_DirectX) 
	if (sizeof(&inBuffer.m_Desc.SRD.psysMem) == sizeof(inData)) {
		//Function de update subresource data 
		m_DeviceContext->UpdateSubresource(inBuffer.m_Buffer, 0, NULL, &inData, 0, 0);
	}
#endif
}


void CGraphicsAPI::draw(unsigned int inNumIndex) {
#if (defined D_DirectX || defined R_DirectX)
	m_DeviceContext->DrawIndexed(inNumIndex, 0, 0);
#endif
}


void CGraphicsAPI::show() {
#if (defined D_DirectX || defined R_DirectX)
	m_SwapChain->Present(0, 0);
#endif
}



#if (defined D_DirectX || defined R_DirectX)
D3D11_BUFFER_DESC CGraphicsAPI::createDesc(BufferDesc inDesc) {
	D3D11_BUFFER_DESC temp;
	ZeroMemory(&temp, sizeof(temp));
	temp.Usage = (D3D11_USAGE)inDesc.usage;
	temp.ByteWidth = inDesc.byteWidth;
	temp.BindFlags = inDesc.bindFlags;
	temp.CPUAccessFlags = inDesc.cpuAccessFlags;
	return temp;
}


D3D11_SUBRESOURCE_DATA CGraphicsAPI::createSRD(BufferDesc inDesc) {
	D3D11_SUBRESOURCE_DATA  temp;
	ZeroMemory(&temp, sizeof(temp));
	temp.pSysMem = inDesc.SRD.psysMem;
	temp.SysMemPitch = inDesc.SRD.sysMemPitch;
	temp.SysMemSlicePitch = inDesc.SRD.sysMemSlicePitch;
	return temp;
}


HRESULT CGraphicsAPI::createRTV(CTexture2D & inBBuffer, CRenderTargetView & inRTV) {
	HRESULT hr = S_OK;
	//hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)((ID3D11Texture2D*)inBBuffer.getTexture()));
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&inBBuffer.m_Texture);
	if (FAILED(hr)) {
		return hr;
	}
	//hr = m_Device->CreateRenderTargetView((ID3D11Texture2D*)inBBuffer.m_Texture, NULL, (ID3D11RenderTargetView**)&inRTV.getRTV());
	hr = m_Device->CreateRenderTargetView(inBBuffer.m_Texture, NULL, &inRTV.m_RTV);
	if (FAILED(hr)) {
		return hr;
	}
	return hr;
}


HRESULT CGraphicsAPI::createTex2D(TextureDesc inDesc, CTexture2D & inTex) {
	HRESULT hr = S_OK;
	inTex.setDesc(inDesc);
	D3D11_TEXTURE2D_DESC tempDesc;
	ZeroMemory(&tempDesc, sizeof(tempDesc));
	tempDesc.Width = inTex.m_Desc.W;
	tempDesc.Height = inTex.m_Desc.H;
	tempDesc.MipLevels = inTex.m_Desc.mipLevels;
	tempDesc.ArraySize = inTex.m_Desc.arraySize;
	tempDesc.Format = (DXGI_FORMAT)inTex.m_Desc.format;
	tempDesc.SampleDesc.Count = inTex.m_Desc.sampleDesc.count;
	tempDesc.SampleDesc.Quality = inTex.m_Desc.sampleDesc.quality;
	tempDesc.Usage = (D3D11_USAGE)inTex.m_Desc.usage;
	tempDesc.BindFlags = (D3D11_BIND_FLAG)inTex.m_Desc.flags;
	tempDesc.CPUAccessFlags = inTex.m_Desc.cpuAccessFlags;
	tempDesc.MiscFlags = inTex.m_Desc.miscFlags;
	//hr = m_Device->CreateTexture2D(&tempDesc, NULL, (ID3D11Texture2D**)inTex.getTexture());
	hr = m_Device->CreateTexture2D(&tempDesc, NULL, &inTex.m_Texture);
	return hr;
}


HRESULT CGraphicsAPI::createDSV(CTexture2D & inDS, DepthStencilViewDesc inDSVDesc, CDepthStencilView & inDSV) {
	HRESULT hr = S_OK;
	
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = (DXGI_FORMAT)inDSVDesc.format;
	descDSV.ViewDimension = (D3D11_DSV_DIMENSION)inDSVDesc.viewDimension;
	descDSV.Texture2D.MipSlice = inDSVDesc.texture2D.mipSlice;
	//hr = m_Device->CreateDepthStencilView((ID3D11Texture2D *)inDS.getTexture(), &descDSV, (ID3D11DepthStencilView **)inDSV.getDSV());
	hr = m_Device->CreateDepthStencilView(inDS.m_Texture, &descDSV, &inDSV.m_pDepthStencilView);
	return hr;
}


void CGraphicsAPI::setRTargets(unsigned int inNumViews, CRenderTargetView & inRTV, CDepthStencilView & inDSV) {
	ID3D11RenderTargetView *tempRTV = (ID3D11RenderTargetView *)inRTV.getRTV();
	m_DeviceContext->OMSetRenderTargets(inNumViews, &tempRTV, (ID3D11DepthStencilView*)inDSV.getDSV());
}


void CGraphicsAPI::setVPort(D3D11_VIEWPORT inVP) {
	m_DeviceContext->RSSetViewports(1, &inVP);
}


HRESULT CGraphicsAPI::createVS(ID3DBlob * inBlob, ID3D11ClassLinkage * inClass, ID3D11VertexShader *& inVS) {
	HRESULT hr = S_OK;
	hr = m_Device->CreateVertexShader(inBlob->GetBufferPointer(), inBlob->GetBufferSize(), inClass, &inVS);
	return hr;
}


HRESULT CGraphicsAPI::createIL(D3D11_INPUT_ELEMENT_DESC * inILDesc, unsigned int inNumElem, ID3DBlob * inBlob, ID3D11InputLayout * inIL) {
	HRESULT hr = S_OK;
	hr = m_Device->CreateInputLayout(inILDesc, inNumElem, inBlob->GetBufferPointer(),
		inBlob->GetBufferSize(), &inIL);
	return hr;
}


void CGraphicsAPI::setIL(ID3D11InputLayout * inIL) {
	m_DeviceContext->IASetInputLayout(inIL);
}


HRESULT CGraphicsAPI::createPS(ID3DBlob * inBlob, ID3D11ClassLinkage * inClass, ID3D11PixelShader * inPS) {
	HRESULT hr = S_OK;
	hr = m_Device->CreatePixelShader(inBlob->GetBufferPointer(), inBlob->GetBufferSize(), inClass, &inPS);

	return hr;
}


void CGraphicsAPI::setTopology(D3D_PRIMITIVE_TOPOLOGY inTopology) {
	m_DeviceContext->IASetPrimitiveTopology(inTopology);
}


HRESULT CGraphicsAPI::createSState(D3D11_SAMPLER_DESC inSSDesc, ID3D11SamplerState * inSampler) {
	HRESULT hr = S_OK;
	hr = m_Device->CreateSamplerState(&inSSDesc, &inSampler);
	return hr;
}


void CGraphicsAPI::setVShader(ID3D11VertexShader * inVS) {	//Setear en distintas funciones
	m_DeviceContext->VSSetShader(inVS, NULL, 0);
	
}
void CGraphicsAPI::setPShader(ID3D11PixelShader * inPS) {	//Setear en distintas funciones
	
	m_DeviceContext->PSSetShader(inPS, NULL, 0);
}


void CGraphicsAPI::setSResource(ID3D11ShaderResourceView * inSRV) {
	m_DeviceContext->PSSetShaderResources(0, 1, &inSRV);
}


void CGraphicsAPI::setSampler(ID3D11SamplerState * inSS) {
	m_DeviceContext->PSSetSamplers(0, 1, &inSS);
}


ID3D11Device * CGraphicsAPI::getDev() {
	return m_Device;
}


D3D_DRIVER_TYPE CGraphicsAPI::getDriverType() {
	return m_driverType;
}


void CGraphicsAPI::clearRTV(CRenderTargetView & inRTV, float inColor[4]) {
	m_DeviceContext->ClearRenderTargetView((ID3D11RenderTargetView *)inRTV.getRTV(), inColor);

}


void CGraphicsAPI::clearDSV(CDepthStencilView & inDSV, D3D11_CLEAR_FLAG inFlag) {
	m_DeviceContext->ClearDepthStencilView((ID3D11DepthStencilView*)inDSV.getDSV(), inFlag, 1.0f, 0);
}

#endif