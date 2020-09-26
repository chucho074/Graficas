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
	m_Width = inWidth;

	createDeviceAndSwpaChain(inWindow);
}

bool CGraphicsAPI::createDeviceAndSwpaChain(void * inWindow) {
	HRESULT hr = true;
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
	sd.BufferDesc.Width = m_Width;
	sd.BufferDesc.Height = m_Height;
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
		if (hr) {
			break;
		}
	}


	return hr;
}

CTexture2D & CGraphicsAPI::createTex2D(TextureDesc inDesc) {
	
	CTexture2D temp;
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
	m_Device->CreateTexture2D(&tempDesc, nullptr, &temp.m_Texture);
	
	return temp;
	
}

CDepthStencilView & CGraphicsAPI::createDSV(DepthStencilViewDesc inDesc) {
	CTexture2D DepthStencil; 
	CDepthStencilView tempDSV;
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	memset(&descDSV, 0, sizeof(descDSV));
	descDSV.Format = (DXGI_FORMAT)inDesc.format;
	descDSV.ViewDimension = (D3D11_DSV_DIMENSION)inDesc.viewDimension;
	descDSV.Texture2D.MipSlice = inDesc.mipSlice;

	m_Device->CreateDepthStencilView(DepthStencil.m_Texture, &descDSV, 
									&tempDSV.m_pDepthStencilView);

	return tempDSV;
}

CRenderTargetView & CGraphicsAPI::createRTV(CTexture2D inBackBuffer) {
	CRenderTargetView RTV;
	m_Device->CreateRenderTargetView(inBackBuffer.m_Texture, nullptr, &RTV.m_RTV);
	return RTV;
}

CViewPort & CGraphicsAPI::createVP() {
	CViewPort temp;
	temp.m_VP.Width = (FLOAT)m_Width;
	temp.m_VP.Height = (FLOAT)m_Height;
	temp.m_VP.MinDepth = 0.0f;
	temp.m_VP.MaxDepth = 1.0f;
	temp.m_VP.TopLeftX = 0;
	temp.m_VP.TopLeftY = 0;
	return temp;
	
}

void CGraphicsAPI::setVP(CViewPort &inVP) {
	m_DContext->RSSetViewports(1, &inVP.m_VP);
}

CVertexShader CGraphicsAPI::createVS(WCHAR * inFileName, 
									 LPCSTR inEntryPoint, 
									 LPCSTR inShaderModel) {

	CVertexShader tempVS;
	tempVS.init(inFileName, inEntryPoint, inShaderModel);
	m_Device->CreateVertexShader(tempVS.m_CompiledVShader->GetBufferPointer(),
								 tempVS.m_CompiledVShader->GetBufferSize(), 
								 nullptr, 
								 &tempVS.m_VS);

	return tempVS;
}

CPixelShader CGraphicsAPI::createPS(WCHAR * inFileName, 
									LPCSTR inEntryPoint, 
									LPCSTR inShaderModel) {
	CPixelShader tempPS;
	tempPS.init(inFileName, inEntryPoint, inShaderModel);
	m_Device->CreatePixelShader(tempPS.m_CompiledPShader->GetBufferPointer(),
								tempPS.m_CompiledPShader->GetBufferSize(),
								nullptr,
								&tempPS.m_PS);

	return tempPS;
}

CInputLayout & CGraphicsAPI::createIL(InputLayoutDesc * inDesc, int inNumElements) {
	CInputLayout tempIL;
	tempIL.init(inDesc, inNumElements);
	return tempIL;
}


CBuffer & CGraphicsAPI::createBuffer(unsigned int inByteWidth, 
									 unsigned int inBindFlags, 
									 unsigned int inOffset, 
									 void * inBufferData) {
	//SmartPointers 
	/*auto buffer = std::make_shared<CBuffer>();
	auto tempBuffer = reinterpret_cast<CBuffer*>(buffer.get());*/
	CBuffer tempBuffer;
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
	tempBuffer.init(tempDesc);
	if (nullptr == tempBuffer.m_BufferData) {
		m_Device->CreateBuffer(&tempBuffer.m_Desc,
							   &tempBuffer.m_SRD,
							   &tempBuffer.m_Buffer);
		return tempBuffer;
	}
	else {
		m_Device->CreateBuffer(&tempBuffer.m_Desc,
							   nullptr,
							   &tempBuffer.m_Buffer);
		return tempBuffer;
	}
		return tempBuffer;
}


CSampler CGraphicsAPI::createSampler(SamplerDesc inDesc) {
	CSampler tmpSampler;
	tmpSampler.init(inDesc);
	m_Device->CreateSamplerState(&tmpSampler.m_Desc, &tmpSampler.m_Sampler);
	return tmpSampler;
}

