/**
* @LC		: 08/06/2020
* @file		: CDevice.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CDevice.h"

CDevice::CDevice() {
#ifdef D_DIRECTX
	Device = nullptr;
	
#endif
}


CDevice::~CDevice() {

}


void CDevice::init(DeviceDesc inDesc) {
	Desc = inDesc;

	/*
	Desc.DriverType = inDesc.DriverType;
	Desc.DeviceFlags = inDesc.DeviceFlags;
	Desc.DriverTypes[0] = inDesc.DriverTypes[0];
	Desc.DriverTypes[1] = inDesc.DriverTypes[1];
	Desc.DriverTypes[2] = inDesc.DriverTypes[2];
	Desc.FeatureLevels[0] = inDesc.FeatureLevels[0];
	Desc.FeatureLevels[1] = inDesc.FeatureLevels[1];
	Desc.FeatureLevels[2] = inDesc.FeatureLevels[2];
	Desc.numFeatureLevels = inDesc.numFeatureLevels;*/

}


void * CDevice::getDevice() {
#ifdef D_DIRECTX
	 return Device;
#else
	 return nullptr;
#endif
}


HRESULT CDevice::createRTV(CTexture2D & inTexture, CRenderTargetView & inRTV) {
#ifdef D_DIRECTX
	if (FAILED(Device->CreateRenderTargetView(inTexture.m_Texture, NULL, &inRTV.m_RTV))) {
		return false;
	}
	else { return S_OK; }
#endif
	return false;
}


HRESULT CDevice::createTexture(CTexture2D & inTexture) {
#ifdef D_DIRECTX
	if (FAILED(Device->CreateTexture2D(&inTexture.m_Desc, NULL, &inTexture.m_Texture))) {
		return false;
	}
	else { return S_OK; }
#endif
	return false;
}


HRESULT CDevice::createDSV(CTexture2D & inDStencil, CDepthStencilView & inDSView) {
#ifdef D_DIRECTX
	if (FAILED(Device->CreateDepthStencilView(inDStencil.m_Texture, &inDSView.m_Desc, &inDSView.m_pDepthStencilView))) {
		return false;
	}
	else { return S_OK; }
#endif
	return false;
}


HRESULT CDevice::createVShader(CVertexShader & inVS) {
#ifdef D_DIRECTX
	if (FAILED(Device->CreateVertexShader(inVS.m_Blob->GetBufferPointer(),
		inVS.m_Blob->GetBufferSize(), NULL, &inVS.m_VertexShader))) {
		return false;
	}
	else { return S_OK; }
#endif
	return false;
}


HRESULT CDevice::createPShader(CPixelShader & inPS) {
#ifdef D_DIRECTX
	if (FAILED(Device->CreatePixelShader(inPS.m_Blob->GetBufferPointer(), inPS.m_Blob->GetBufferSize(), NULL, &inPS.m_PixelShader))) {
		return false;
	}
	else { return S_OK; }
#endif
	return false;
}
