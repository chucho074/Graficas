/**
* @LC		: 04/06/2020
* @file		: CGraphicsAPI.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 28/05/2020
* @brief	: A basic description of the what do the doc.
* @bug		: Instancias Device, SChain, DContxt.
**/

/**
* Headers
**/
#include "CGraphicsAPI.h"


CGraphicsAPI::CGraphicsAPI() {
	
}


CGraphicsAPI::~CGraphicsAPI() {


}


int CGraphicsAPI::init(DeviceDesc &inDevDesc, SwapChainDesc &inSCDesc) {
	m_Device->init(inDevDesc);
	m_SChain->init(inSCDesc);
#ifdef D_DIRECTX
	m_ptrDevice = static_cast<ID3D11Device*>(m_Device->getDevice());
	m_ptrDContx = static_cast<ID3D11DeviceContext*>(m_DContx->getDeviceContext());
	m_ptrSChain = static_cast<IDXGISwapChain*>(m_SChain->getSwapChain());

#endif

	return 0;
}





void CGraphicsAPI::setDriverType(unsigned int inDriverType) {
	m_Device->Desc.DriverType = m_Device->Desc.DriverTypes[inDriverType];
}


HRESULT CGraphicsAPI::createDevnSC(FEATURE_LEVEL inFeatureLvl) {
#ifdef D_DIRECTX
	
	return D3D11CreateDeviceAndSwapChain(NULL, (D3D_DRIVER_TYPE)m_Device->Desc.DriverType, NULL, 
			m_Device->Desc.DeviceFlags, (D3D_FEATURE_LEVEL *)m_Device->Desc.FeatureLevels, m_Device->Desc.numFeatureLevels,
			D3D11_SDK_VERSION, &m_SChain->m_sd, &m_ptrSChain, &m_ptrDevice, (D3D_FEATURE_LEVEL *)&inFeatureLvl, &m_ptrDContx);
#else
	return false;
#endif
}


HRESULT CGraphicsAPI::createRTV(CTexture2D inTexture, CRenderTargetView inRTV) {
#ifdef D_DIRECTX
	if (FAILED(m_ptrSChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&inTexture.m_pTexture))) {
		return false;
	}
	else if (FAILED(m_ptrDevice->CreateRenderTargetView(inTexture.m_pTexture, NULL, &inRTV.m_pRTV))) {
		return false;
	}
	else { return S_OK; }
#else
	return false;
#endif
}


HRESULT CGraphicsAPI::createTexture(CTexture2D inTexture) {
#ifdef D_DIRECTX
	if (FAILED(m_ptrDevice->CreateTexture2D(&inTexture.m_Desc, NULL, &inTexture.m_pTexture))){
		return false;
	}
	else { return S_OK; }
#else
	return false;
#endif
}


HRESULT CGraphicsAPI::createDSV(CTexture2D inDStencil, CDepthStencilView inDSView) {
#ifdef D_DIRECTX
	if (FAILED(m_ptrDevice->CreateDepthStencilView(inDStencil.m_pTexture, &inDSView.m_Desc, &inDSView.m_pDepthStencilView))) {
		return false;
	}
	else { return S_OK; }
#else
	return false;
#endif
}


void CGraphicsAPI::createVPort(ViewPortDesc inVPDesc) {
	CViewPort tempVP;
	tempVP.init(inVPDesc);
#ifdef D_DIRECTX
	m_ptrDContx->RSSetViewports(1, &tempVP.m_Viewport);
#endif
}


HRESULT CGraphicsAPI::createVShader(CVertexShader inVShader) {

#ifdef D_DIRECTX
		if (FAILED(m_ptrDevice->CreateVertexShader(inVShader.m_Blob->GetBufferPointer(),
					inVShader.m_Blob->GetBufferSize(), NULL, &inVShader.m_VertexShader))) {
			return false;
		}
		else { return S_OK; }
#else
		return false;
#endif
}


HRESULT CGraphicsAPI::createILayout(CVertexShader inVShader) {
	
#ifdef D_DIRECTX
	if (FAILED(CreateInputLayoutDescFromVertexShaderSignature(inVShader.m_Blob, m_ptrDevice, 
					&inVShader.m_InputLayout))) {
		return false;
	}
	else { 
		//Se settea el InputLayout
		m_ptrDContx->IASetInputLayout(inVShader.m_InputLayout);
		return S_OK; 
	}
#else
	return false;
#endif

}


HRESULT CGraphicsAPI::createPShader(CPixelShader inPShader) {
#ifdef D_DIRECTX
	if (FAILED(m_ptrDevice->CreatePixelShader(inPShader.m_Blob->GetBufferPointer(), 
				inPShader.m_Blob->GetBufferSize(), NULL, &inPShader.m_PixelShader))) {
		return false;
	}
	else { return S_OK; }
#else
	return false;
#endif
}


HRESULT CGraphicsAPI::createBuffer(CBuffer inBuffer, bool inUseSRD) {
	
#ifdef D_DIRECTX
	switch (inUseSRD) {
	case true: {
		if (FAILED(m_ptrDevice->CreateBuffer(&inBuffer.m_bd, &inBuffer.m_Data, &inBuffer.Buffer))) {
			return false;
		}
		else { return S_OK; }
		break;
	}
	case false: {
		if (FAILED(m_ptrDevice->CreateBuffer(&inBuffer.m_bd, NULL, &inBuffer.Buffer))) {
			return false;
		}
		else { return S_OK; }
		break;
	}
	default:
		return false;
		break;
	}
		
#else
		return false;
#endif
}


void CGraphicsAPI::setVBuffer(CBuffer inVBuffer) {
	unsigned int stride = sizeof(SimpleVertex);
	unsigned int offset = 0;
#ifdef D_DIRECTX
	m_ptrDContx->IASetVertexBuffers(0, 1, &inVBuffer.Buffer, &stride, &offset);

#endif
}


void CGraphicsAPI::setIBuffer(CBuffer inVBuffer) {
#ifdef D_DIRECTX
	m_ptrDContx->IASetIndexBuffer(inVBuffer.Buffer, DXGI_FORMAT_R16_UINT, 0);
#endif
}

void CGraphicsAPI::setCBuffer(unsigned int inStartLot,CBuffer inCBuffer) {
#ifdef D_DIRECTX
	m_ptrDContx->VSSetConstantBuffers(inStartLot, 1, &inCBuffer.Buffer);
#endif
}

HRESULT CGraphicsAPI::createSState(CSamplerState inSampler) {

#ifdef D_DIRECTX
		if (FAILED(m_ptrDevice->CreateSamplerState(&inSampler.m_Desc, &inSampler.m_pSamplerLinear))) {
			return false;
		}
		else { return S_OK; }
#else
		return false;
#endif
}

HRESULT CGraphicsAPI::resizeBuffers() {
	
#ifdef D_DIRECTX
		if (FAILED(m_ptrSChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0))) {
			return false;
		}
		else { return S_OK; }
#else
		return false;
#endif
	return E_NOTIMPL;
}



void CGraphicsAPI::mergePtrs() {
	m_Device->Device = m_ptrDevice;
	m_DContx->m_DeviceContext = m_ptrDContx;
}

void CGraphicsAPI::show() {
	m_ptrSChain->Present(0,0);

	
}


#ifdef D_DIRECTX
void CGraphicsAPI::setTopology(D3D11_PRIMITIVE_TOPOLOGY inTopology) {
	m_ptrDContx->IASetPrimitiveTopology(inTopology);
}
HRESULT CGraphicsAPI::createSRViewFFile(ID3D11ShaderResourceView *inSRView) {
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(m_ptrDevice, L"seafloor.dds", NULL, NULL, &inSRView, NULL))) {
		return false;
	}
	else { return S_OK; }

}

HRESULT CGraphicsAPI::createSRView(CTexture2D inTexture, D3D11_SHADER_RESOURCE_VIEW_DESC inDesc, ID3D11ShaderResourceView * inSRView) {
	
		if (FAILED(m_ptrDevice->CreateShaderResourceView(inTexture.m_pTexture, &inDesc, &inSRView))) {
			return false;
		}
		else { return S_OK; }
}

 void CGraphicsAPI::updateSResource(CBuffer inResource, const void* inData) {
	 m_ptrDContx->UpdateSubresource(inResource.Buffer, 0, NULL, &inData, 0, 0);
}
#endif