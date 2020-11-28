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
#include "CImageLoader.h"
#include <intrin.h>

CGraphicsAPI::CGraphicsAPI() {
	m_Device = nullptr;
	m_DContext = nullptr;
	m_SwapChain = nullptr;
}

CGraphicsAPI::~CGraphicsAPI() {
	delete m_backBuffer;
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
	m_backBuffer = new CTexture2D();

	//Get a texture from Swap Chain
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_backBuffer->m_Texture);

	//Create RTV
	if (FAILED(m_Device->CreateRenderTargetView(m_backBuffer->m_Texture,
	/******************************************/nullptr,
	/******************************************/&m_backBuffer->m_RTV))) {

		__debugbreak();
	}
	

	
	//Create DSV
	m_defaultDSV = createTex2D(inWidth, 
							   inHeight, 
							   1, 
							   DXGI_FORMAT_D24_UNORM_S8_UINT,
							   D3D11_BIND_DEPTH_STENCIL);

	//Create and set a ViewPort
	m_defaultVP = createVP(inWidth, inHeight);


	return hr;
}


CTexture2D * CGraphicsAPI::createTex2D(int inWidth,
/*************************************/int inHeigh,
/*************************************/int inMipLevels,
/*************************************/DXGI_FORMAT inFormat,
/*************************************/int inBindFlags) {
	
	
	CTexture2D *temp = new CTexture2D();
	CD3D11_TEXTURE2D_DESC tempDesc;
	memset(&tempDesc, 0, sizeof(tempDesc));
	tempDesc.Width = inWidth;
	tempDesc.Height = inHeigh;
	tempDesc.MipLevels = inMipLevels;
	tempDesc.ArraySize = 1;
	tempDesc.Format = inFormat;
	tempDesc.SampleDesc.Count = 1;
	tempDesc.SampleDesc.Quality = 0;
	tempDesc.Usage = D3D11_USAGE_DEFAULT;
	tempDesc.BindFlags = (D3D11_BIND_FLAG)inBindFlags;
	tempDesc.CPUAccessFlags = 0;
	tempDesc.MiscFlags = 0;

	if (FAILED(m_Device->CreateTexture2D(&tempDesc, nullptr, &temp->m_Texture))) {
		//Send error message
		//Pone un breakpoint cuando llegue aqui
		__debugbreak();
		return nullptr;
	}

	if (D3D11_BIND_RENDER_TARGET & inBindFlags) {
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		memset(&rtvDesc, 0, sizeof(rtvDesc));
		rtvDesc.Format = tempDesc.Format;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		//rtvDesc.Texture2D.MipSlice = tempDesc.MipLevels;
		rtvDesc.Texture2D.MipSlice = 0;
		if (FAILED(m_Device->CreateRenderTargetView(temp->m_Texture, nullptr, &temp->m_RTV))) {
			__debugbreak();
			return nullptr;
		}

	}

	if (D3D11_BIND_DEPTH_STENCIL & inBindFlags) {
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		memset(&dsvDesc, 0, sizeof(dsvDesc));
		dsvDesc.Format = tempDesc.Format;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		//dsvDesc.Texture2D.MipSlice = tempDesc.MipLevels;
		dsvDesc.Texture2D.MipSlice = 0;
		if (FAILED(m_Device->CreateDepthStencilView(temp->m_Texture, nullptr, &temp->m_DSV))) {
			__debugbreak();
			return nullptr;
		}
	}

	if (D3D11_BIND_SHADER_RESOURCE & inBindFlags) {
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		memset(&srvDesc, 0, sizeof(srvDesc));
		srvDesc.Format = tempDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		//srvDesc.Texture2D.MipLevels = tempDesc.MipLevels;
		srvDesc.Texture2D.MipLevels = 0;
		srvDesc.Texture2D.MostDetailedMip = 0;
		if (FAILED(m_Device->CreateShaderResourceView(temp->m_Texture, nullptr, &temp->m_SRV))) {
			__debugbreak();
			return nullptr;
		}
	}
	
	return temp;
	
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
/************************************/LPCSTR inEntryPoint, 
/************************************/LPCSTR inShaderModel) {

	CVertexShader * tempVS = new CVertexShader();
	tempVS->init(inFileName, inEntryPoint, inShaderModel);
	if(FAILED(m_Device->CreateVertexShader(tempVS->m_CompiledVShader->GetBufferPointer(),
										   tempVS->m_CompiledVShader->GetBufferSize(), 
										   nullptr, 
										   &tempVS->m_VS))) {
	
		__debugbreak();
		return nullptr;
	}


	return tempVS;
}

CPixelShader *CGraphicsAPI::createPS(WCHAR * inFileName, 
/***********************************/LPCSTR inEntryPoint, 
/***********************************/LPCSTR inShaderModel) {
	CPixelShader *tempPS = new CPixelShader();
	tempPS->init(inFileName, inEntryPoint, inShaderModel);
	if(FAILED(m_Device->CreatePixelShader(tempPS->m_CompiledPShader->GetBufferPointer(),
								tempPS->m_CompiledPShader->GetBufferSize(),
								nullptr,
								&tempPS->m_PS))){

		__debugbreak();
		return nullptr;
	}

	return tempPS;
}

CInputLayout * CGraphicsAPI::createIL(std::vector<InputLayoutDesc> & inDesc, 
/************************************/CVertexShader* inShader) {

	CInputLayout *tempIL = new CInputLayout();
	tempIL->init(inDesc);
	if(FAILED(m_Device->CreateInputLayout(tempIL->m_Descriptors.data(), 
									 inDesc.size(), 
									 inShader->m_CompiledVShader->GetBufferPointer(),
									 inShader->m_CompiledVShader->GetBufferSize(),
									 &tempIL->m_InputLayout))) {
		__debugbreak();
		return nullptr;
	}
	return tempIL;
}


CBuffer * CGraphicsAPI::createBuffer(unsigned int inByteWidth, 
/***********************************/unsigned int inBindFlags, 
/***********************************/unsigned int inOffset, 
/***********************************/void * inBufferData) {
	//SmartPointers 
	/*auto buffer = std::make_shared<CBuffer>();
	auto tempBuffer = reinterpret_cast<CBuffer*>(buffer.get());*/
	CBuffer * tmpBuffer = new CBuffer();
	CD3D11_BUFFER_DESC tmpDesc(inByteWidth, inBindFlags);
	D3D11_SUBRESOURCE_DATA tmpData;
	tmpData.pSysMem = inBufferData;
	tmpData.SysMemPitch = inByteWidth;
	tmpData.SysMemSlicePitch = 0;
	
	if(FAILED(m_Device->CreateBuffer(&tmpDesc,
	/*******************************/(inBufferData == nullptr ? nullptr : &tmpData),
	/*******************************/&tmpBuffer->m_Buffer))) {
	
		__debugbreak();
		return nullptr;
	}	
	
	return tmpBuffer;
}


CSampler * CGraphicsAPI::createSampler(SamplerDesc inDesc) {
	CSampler *tmpSampler = new CSampler();
	tmpSampler->init(inDesc);
	if(FAILED(m_Device->CreateSamplerState(&tmpSampler->m_Desc, &tmpSampler->m_Sampler))) {
		__debugbreak();
		return nullptr;
	}
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

void CGraphicsAPI::updateSubresource(CBuffer* inBuffer, void* inData, unsigned int inPitch) {
	m_DContext->UpdateSubresource(inBuffer->m_Buffer, 0, NULL, inData, inPitch, 0);
}

void CGraphicsAPI::updateTexture(CTexture2D* inTexture, 
/*******************************/const void* inData, 
/*******************************/unsigned int inPitch, 
/*******************************/unsigned int inDepthPitch) {

	m_DContext->UpdateSubresource(inTexture->m_Texture, 
								  0, 
								  NULL, 
								  inData, 
								  inPitch, 
								  inDepthPitch);
}

void CGraphicsAPI::clearRTV(CTexture2D* inRTV, float inColor[4]) {
	m_DContext->ClearRenderTargetView(inRTV->m_RTV, inColor);
}

void CGraphicsAPI::clearDSV(CTexture2D* inDSV) {
	m_DContext->ClearDepthStencilView(inDSV->m_DSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void CGraphicsAPI::vsSetShader(CVertexShader* inVShader) {

	ID3D11VertexShader* tmpVShader = nullptr;
	if (nullptr != inVShader) {
		tmpVShader = inVShader->m_VS;
	}
	m_DContext->VSSetShader(tmpVShader, NULL, 0);
}

void CGraphicsAPI::vsSetConstantBuffer(unsigned int inSlot, CBuffer* inBuffer) {
	ID3D11Buffer* tmpBuffer = nullptr;
	if (nullptr != inBuffer) {
		tmpBuffer = inBuffer->m_Buffer;
	}
	m_DContext->VSSetConstantBuffers(inSlot, 1, &tmpBuffer);
}

void CGraphicsAPI::psSetShader(CPixelShader* inPShader) {
	
	ID3D11PixelShader* tmpPShader = nullptr;
	if (nullptr != inPShader) {
		tmpPShader = inPShader->m_PS;
	}

	m_DContext->PSSetShader(tmpPShader, NULL, 0);
}

void CGraphicsAPI::psSetConstantBuffer(unsigned int inSlot, CBuffer* inBuffer) {
	m_DContext->PSSetConstantBuffers(inSlot, 1, &inBuffer->m_Buffer);
}

void CGraphicsAPI::psSetShaderResource(unsigned int inSlot, CTexture2D* inTexture) {
	
	ID3D11ShaderResourceView *  tmpSRV = nullptr;
	if (nullptr != inTexture) {
		tmpSRV = inTexture->getSRV();
	}

	m_DContext->PSSetShaderResources(inSlot, 1, &tmpSRV);
}

void CGraphicsAPI::psSetSampler(unsigned int inSlot, unsigned int inNumSamplers, CSampler* inSampler) {
	m_DContext->PSSetSamplers(inSlot, inNumSamplers, &inSampler->m_Sampler);
}

void CGraphicsAPI::aiSetInputLayout(CInputLayout* inInputLayout) {
	m_DContext->IASetInputLayout(inInputLayout->m_InputLayout);
}

void CGraphicsAPI::omSetRenderTarget(CTexture2D* inRT, CTexture2D* inDS) {

	ID3D11RenderTargetView* tmpRTV[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
	for (int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) {
		tmpRTV[i] = nullptr;
	}


	ID3D11DepthStencilView* tmpDSV = nullptr;

	if (nullptr != inDS) {
		tmpDSV = inDS->m_DSV;
	}

	if (nullptr != inRT) {
		tmpRTV[0] = inRT->m_RTV;
	}
	else {
		m_DContext->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, 
									   tmpRTV, 
									   tmpDSV);
		return;
	}
	

	m_DContext->OMSetRenderTargets(1, tmpRTV, tmpDSV);

}

void CGraphicsAPI::draw(unsigned int inNumIndexes, unsigned int inStartLocation) {
	m_DContext->DrawIndexed(inNumIndexes, inStartLocation, 0);
}

CGraphicsAPI& g_GraphicsAPI() {
	return CGraphicsAPI::getSingleton();
}
