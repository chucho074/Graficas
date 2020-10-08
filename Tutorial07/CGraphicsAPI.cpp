#include "CGraphicsAPI.h"
#include "CTexture2D.h"
#include "CDepthStencilView.h"
#include "CRenderTargetView.h"
#include "CViewPort.h"
#include "CVertexShader.h"
#include "CPixelShader.h"
#include "CBuffer.h"
#include "CInputLayout.h"
#include "CSampler.h"

CGraphicsAPI::CGraphicsAPI() {
	m_Device = nullptr;
	m_DContext = nullptr;
	m_SwapChain = nullptr;
}

CGraphicsAPI::~CGraphicsAPI() {

}

void CGraphicsAPI::init(void * inWindow, int inWidth, int inHeight) {
	createDeviceAndSwpaChain(inWindow, inWidth, inHeight);
}

HRESULT CGraphicsAPI::createDeviceAndSwpaChain(void* inWindow, int inWidth, int inHeight) {
	HRESULT hr = S_OK;
	unsigned int createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif 
	std::vector<D3D_DRIVER_TYPE> driverTypes = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	std::vector<D3D_FEATURE_LEVEL> featureLvl = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	DXGI_SWAP_CHAIN_DESC sd;
	memset(&sd, 0, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = inWidth;
	sd.BufferDesc.Height = inHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = reinterpret_cast<HWND>(inWindow);
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	D3D_FEATURE_LEVEL selectFeatureLvl;

	for (auto& driverType : driverTypes) {
		hr = D3D11CreateDeviceAndSwapChain(nullptr,
										   driverType,
										   nullptr,
										   (UINT)createDeviceFlags,
										   featureLvl.data(),
										   (UINT)featureLvl.size(),
										   (UINT)D3D11_SDK_VERSION,
										   &sd,
										   &m_SwapChain,
										   &m_Device,
										   &selectFeatureLvl,
										   &m_DContext);
		if (FAILED(hr)) {
			return hr;
		}
	}
	

	//Get a texture from Swap Chain
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_backBuffer->m_Texture);

	//Create RTV
	m_defaultRTV = createRTV(m_backBuffer);

	//Create DSV
	DepthStencilViewDesc descDepth;
	descDepth.format = 45;
	descDepth.mipSlice = 0;
	descDepth.viewDimension = 3;

	m_defaultDSV = createDSV(descDepth);

	//Create and set a ViewPort
	m_defaultVP = createVP(inWidth, inHeight);


	return hr;
}

CTexture2D * CGraphicsAPI::createTex2D(TextureDesc inDesc) {
	
	CTexture2D *temp = new CTexture2D();
	CD3D11_TEXTURE2D_DESC tempDesc;
	memset(&tempDesc, 0, sizeof(tempDesc));
	tempDesc.Width = inDesc.W;
	tempDesc.Height = inDesc.H;
	tempDesc.MipLevels = inDesc.mipLevels;
	tempDesc.ArraySize = inDesc.arraySize;
	tempDesc.Format = (DXGI_FORMAT)inDesc.format;
	tempDesc.SampleDesc.Count = inDesc.sampleDescCount;
	tempDesc.SampleDesc.Quality = inDesc.sampleDescQuality;
	tempDesc.Usage = (D3D11_USAGE)inDesc.usage;
	tempDesc.BindFlags = (D3D11_BIND_FLAG)inDesc.flags;
	tempDesc.CPUAccessFlags = inDesc.cpuAccessFlags;
	tempDesc.MiscFlags = inDesc.miscFlags;
	m_Device->CreateTexture2D(&tempDesc, nullptr, &temp->m_Texture);

	//Meter aqui los casos para las distintas creaciones de objetos que usen Texturas

	
	return temp;
	
}

CDepthStencilView * CGraphicsAPI::createDSV(DepthStencilViewDesc inDesc) {
	//Ya no va aqui
	CTexture2D * DepthStencil = new CTexture2D();
	CDepthStencilView *tempDSV = new CDepthStencilView();
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	memset(&descDSV, 0, sizeof(descDSV));
	descDSV.Format = (DXGI_FORMAT)inDesc.format;
	descDSV.ViewDimension = (D3D11_DSV_DIMENSION)inDesc.viewDimension;
	descDSV.Texture2D.MipSlice = inDesc.mipSlice;

	m_Device->CreateDepthStencilView(DepthStencil->m_Texture, &descDSV, 
									&tempDSV->m_DSV);

	return tempDSV;
}

CRenderTargetView * CGraphicsAPI::createRTV(CTexture2D * inBackBuffer) {
	CRenderTargetView * RTV = new CRenderTargetView();
	m_Device->CreateRenderTargetView(inBackBuffer->m_Texture, nullptr, &RTV->m_RTV);
	return RTV;
}

CViewPort *CGraphicsAPI::createVP(int inWidth, int inHeight) {
	CViewPort * temp = new CViewPort();
	temp->m_VP.Width = (float)inWidth;
	temp->m_VP.Height = (float)inHeight;
	temp->m_VP.MinDepth = 0.0f;
	temp->m_VP.MaxDepth = 1.0f;
	temp->m_VP.TopLeftX = 0;
	temp->m_VP.TopLeftY = 0;
	m_DContext->RSSetViewports(1, &temp->m_VP);
	return temp;
	
}

void CGraphicsAPI::setVP(CViewPort &inVP) {
	m_DContext->RSSetViewports(1, &inVP.m_VP);
}

CVertexShader *CGraphicsAPI::createVS(WCHAR * inFileName, 
									 LPCSTR inEntryPoint, 
									 LPCSTR inShaderModel) {

	CVertexShader * tempVS = new CVertexShader();
	tempVS->init(inFileName, inEntryPoint, inShaderModel);
	m_Device->CreateVertexShader(tempVS->m_CompiledVShader->GetBufferPointer(),
								 tempVS->m_CompiledVShader->GetBufferSize(), 
								 nullptr, 
								 &tempVS->m_VS);

	return tempVS;
}

CPixelShader *CGraphicsAPI::createPS(WCHAR * inFileName, 
									LPCSTR inEntryPoint, 
									LPCSTR inShaderModel) {
	CPixelShader *tempPS = new CPixelShader();
	tempPS->init(inFileName, inEntryPoint, inShaderModel);
	m_Device->CreatePixelShader(tempPS->m_CompiledPShader->GetBufferPointer(),
								tempPS->m_CompiledPShader->GetBufferSize(),
								nullptr,
								&tempPS->m_PS);

	return tempPS;
}

CInputLayout * CGraphicsAPI::createIL(InputLayoutDesc * inDesc, int inNumElements) {
	CInputLayout *tempIL = new CInputLayout();
	tempIL->init(inDesc, inNumElements);
	return tempIL;
}


CBuffer * CGraphicsAPI::createBuffer(unsigned int inByteWidth, 
									 unsigned int inBindFlags, 
									 unsigned int inOffset, 
									 void * inBufferData) {
	//SmartPointers 
	/*auto buffer = std::make_shared<CBuffer>();
	auto tempBuffer = reinterpret_cast<CBuffer*>(buffer.get());*/
	CBuffer * tempBuffer = new CBuffer();
	BufferDesc tempDesc;
	tempDesc.usage = D3D11_USAGE_DEFAULT;
	tempDesc.byteWidth = inByteWidth;
	tempDesc.bindFlags = inBindFlags;
	tempDesc.CPUAccessFlags = 0;
	tempDesc.startSlot = 0;
	tempDesc.numBuffers = 1;
	tempDesc.offset = inOffset;
	tempDesc.stride = 0;
	tempDesc.SRD = inBufferData;
	tempBuffer->init(tempDesc);
	if (nullptr != tempBuffer->m_BufferData) {
		m_Device->CreateBuffer(&tempBuffer->m_Desc,
							   &tempBuffer->m_SRD,
							   &tempBuffer->m_Buffer);
		//return tempBuffer;
	}
	else {
		m_Device->CreateBuffer(&tempBuffer->m_Desc,
							   nullptr,
							   &tempBuffer->m_Buffer);
		//return tempBuffer;
	}
	return tempBuffer;
}


CSampler CGraphicsAPI::createSampler(SamplerDesc inDesc) {
	CSampler tmpSampler;
	tmpSampler.init(inDesc);
	m_Device->CreateSamplerState(&tmpSampler.m_Desc, &tmpSampler.m_Sampler);
	return tmpSampler;
}

void CGraphicsAPI::show() {
	m_SwapChain->Present(0, 0);
}

void CGraphicsAPI::setVertexBuffer(CBuffer* inBuffer, unsigned int inStride) {
	UINT offset = 0;
	m_DContext->IASetVertexBuffers(0, 1, &inBuffer->m_Buffer, &inStride, &offset);
}

void CGraphicsAPI::setIndexBuffer(CBuffer* inBuffer, DXGI_FORMAT inFormat) {
	m_DContext->IASetIndexBuffer(inBuffer->m_Buffer, inFormat, 0);
}

void CGraphicsAPI::setTopology(D3D_PRIMITIVE_TOPOLOGY inTopotology) {
	m_DContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void CGraphicsAPI::updateSubresource(CBuffer* inBuffer, void* inData) {
	m_DContext->UpdateSubresource(inBuffer->m_Buffer, 0, NULL, inData, 0, 0);
}

void CGraphicsAPI::clearRTV(CRenderTargetView * inRTV, float inColor[4]) {
	//Case for default
	if (nullptr == inRTV) {
		m_DContext->ClearRenderTargetView(m_defaultRTV->m_RTV, inColor);
	}
	//Case for use the input
	else {
		m_DContext->ClearRenderTargetView(inRTV->m_RTV, inColor);
	}
}

void CGraphicsAPI::clearDSV(CDepthStencilView* inDSV) {
	//Case for default
	if (nullptr == inDSV) {
		m_DContext->ClearDepthStencilView(m_defaultDSV->m_DSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
	//Case for use the input
	else {
		m_DContext->ClearDepthStencilView(inDSV->m_DSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
}

void CGraphicsAPI::vsSetShader(CVertexShader* inVShader) {
	m_DContext->VSSetShader(inVShader->m_VS, NULL, 0);
}

void CGraphicsAPI::vsSetConstantBuffer(unsigned int inSlot, CBuffer* inBuffer) {
	m_DContext->VSSetConstantBuffers(inSlot, 1, &inBuffer->m_Buffer);
}

void CGraphicsAPI::psSetShader(CPixelShader* inPShader) {
	m_DContext->PSSetShader(inPShader->m_PS, NULL, 0);
}

void CGraphicsAPI::psSetConstantBuffer(unsigned int inSlot, CBuffer* inBuffer) {
	m_DContext->PSSetConstantBuffers(inSlot, 1, &inBuffer->m_Buffer);
}

void CGraphicsAPI::psSetShaderResource(unsigned int inSlot, ID3D11ShaderResourceView* inSRV) {
	m_DContext->PSSetShaderResources(inSlot, 1, &inSRV);
}

void CGraphicsAPI::psSetSampler(unsigned int inSlot, unsigned int inNumSamplers, CSampler* inSampler) {
	m_DContext->PSSetSamplers(inSlot, inNumSamplers, &inSampler->m_Sampler);
}

void CGraphicsAPI::draw(unsigned int inNumIndexes, unsigned int inStartLocation) {
	m_DContext->DrawIndexed(inNumIndexes, inStartLocation, 0);
}

CGraphicsAPI& g_GraphicsAPI() {
	return CGraphicsAPI::getSingleton();
}
