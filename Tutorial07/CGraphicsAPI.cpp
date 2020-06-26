/**
* @LC		: 15/06/2020
* @file		: CGraphicsAPI.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 28/05/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CGraphicsAPI.h"


CGraphicsAPI::CGraphicsAPI() {
	
}


CGraphicsAPI::~CGraphicsAPI() {


}


int CGraphicsAPI::init(DeviceDesc & inDevDesc, SwapChainDesc & inSCDesc) {
	m_Device.init(inDevDesc);
	m_SChain.init(inSCDesc);
#ifdef D_DIRECTX
	

#endif

	return 0;
}


void CGraphicsAPI::setDriverType(unsigned int inDriverType) {
	m_Device.Desc.DriverType = m_Device.Desc.DriverTypes[inDriverType];
}


HRESULT CGraphicsAPI::createDevnSC(FEATURE_LEVEL inFeatureLvl) {
#ifdef D_DIRECTX
	
	return D3D11CreateDeviceAndSwapChain(NULL, (D3D_DRIVER_TYPE)m_Device.Desc.DriverType, NULL, 
			m_Device.Desc.DeviceFlags, (D3D_FEATURE_LEVEL *)m_Device.Desc.FeatureLevels, m_Device.Desc.numFeatureLevels,
			D3D11_SDK_VERSION, &m_SChain.m_SCDesc, &m_SChain.m_SwapChain, &m_Device.Device, (D3D_FEATURE_LEVEL *)&inFeatureLvl, &m_DContx.m_DeviceContext);
#else
	return false;
#endif
}


HRESULT CGraphicsAPI::createRTV(CTexture2D & inTexture, CRenderTargetView & inRTV) {
#ifdef D_DIRECTX
	if (FAILED(m_SChain.getBuffer(inTexture))) {
		return false;
	}
	else if (FAILED(m_Device.createRTV(inTexture, inRTV))) {
		return false;
	}
	else { return S_OK; }
#else
	return false;
#endif
}


HRESULT CGraphicsAPI::createTexture(CTexture2D & inTexture) {
#ifdef D_DIRECTX
	if (FAILED(m_Device.createTexture(inTexture))){
		return false;
	}
	else { return S_OK; }
#else
	return false;
#endif
}


HRESULT CGraphicsAPI::createDSV(CTexture2D & inDStencil, CDepthStencilView & inDSView) {
#ifdef D_DIRECTX
	return m_Device.createDSV(inDStencil, inDSView);
#else
	return false;
#endif
}


void CGraphicsAPI::createVPort(ViewPortDesc inVPDesc) {
	CViewPort tempVP;
	tempVP.init(inVPDesc);
#ifdef D_DIRECTX
	m_DContx.setViewport(tempVP);
#endif
}


HRESULT CGraphicsAPI::createVShader(CVertexShader & inVShader) {

#ifdef D_DIRECTX

		if (FAILED(inVShader.CompileShaderFromFile(L"Tutorial07.fx", "VS", "vs_4_0"))) {
			return false;
		}
		else if (FAILED(m_Device.createVShader(inVShader))) {
			inVShader.m_Blob->Release();
			return false;
		}
		else { return S_OK; }
#else
		return false;
#endif
}


HRESULT CGraphicsAPI::createILayout(CVertexShader & inVShader, CInputLayout & inILayout) {		//WIP
	
#ifdef D_DIRECTX
	if (FAILED(m_Device.createInputLayoutDescFromVertexShaderSignature(inVShader, inILayout))) {
		return false;
	}
	else { 
		//Se settea el InputLayout
		m_DContx.setILayout(inILayout);
		return S_OK; 
	}
#else
	return false;
#endif

}


HRESULT CGraphicsAPI::createPShader(CPixelShader & inPShader) {
#ifdef D_DIRECTX
	if (FAILED(inPShader.CompileShaderFromFile(L"Tutorial07.fx", "PS", "ps_4_0"))) {
		return false;
	}
	else if (FAILED(m_Device.createPShader(inPShader))) {
		return false;
	}
	else { 
		inPShader.m_Blob->Release();
		return S_OK; 
	}
#else
	return false;
#endif
}


HRESULT CGraphicsAPI::createBuffer(CBuffer & inBuffer, bool inUseSRD) {
	
#ifdef D_DIRECTX
	switch (inUseSRD) {
	case true: {
		if (FAILED(m_Device.Device->CreateBuffer(&inBuffer.m_bd, &inBuffer.m_Data, &inBuffer.Buffer))) {
			return false;
		}
		else { return S_OK; }
		break;
	}
	case false: {
		if (FAILED(m_Device.Device->CreateBuffer(&inBuffer.m_bd, NULL, &inBuffer.Buffer))) {
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


void CGraphicsAPI::setVBuffer(CBuffer * inVBuffer) {
	unsigned int stride = sizeof(SimpleVertex);
	unsigned int offset = 0;
#ifdef D_DIRECTX
	m_DContx.m_DeviceContext->IASetVertexBuffers(0, 1, &inVBuffer->Buffer, &stride, &offset);

#endif
}


void CGraphicsAPI::setIBuffer(CBuffer & inVBuffer) {
#ifdef D_DIRECTX
	m_DContx.m_DeviceContext->IASetIndexBuffer(inVBuffer.Buffer, DXGI_FORMAT_R16_UINT, 0);
#endif
}


void CGraphicsAPI::setVCBuffer(unsigned int inStartLot, CBuffer & inCBuffer) {
#ifdef D_DIRECTX
	m_DContx.m_DeviceContext->VSSetConstantBuffers(inStartLot, 1, &inCBuffer.Buffer);
#endif
}


void CGraphicsAPI::setPCBuffer(unsigned int inStartLot, CBuffer & inCBuffer) {
#ifdef D_DIRECTX
	m_DContx.m_DeviceContext->PSSetConstantBuffers(inStartLot, 1, &inCBuffer.Buffer);
#endif
}


HRESULT CGraphicsAPI::createSState(CSamplerState & inSampler) {

#ifdef D_DIRECTX
		if (FAILED(m_Device.Device->CreateSamplerState(&inSampler.m_Desc, &inSampler.m_pSamplerLinear))) {
			return false;
		}
		else { return S_OK; }
#else
		return false;
#endif
}


HRESULT CGraphicsAPI::resizeBuffers() {
	
#ifdef D_DIRECTX
		if (FAILED(m_SChain.m_SwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0))) {
			return false;
		}
		else { return S_OK; }
#else
		return false;
#endif
	return E_NOTIMPL;
}


void CGraphicsAPI::setRTargets(unsigned int inNumViews, CRenderTargetView & inRTV, CDepthStencilView & inDSV) {
#ifdef D_DIRECTX
	m_DContx.setRTarget(inNumViews, inRTV, inDSV);


#endif
	
}


void CGraphicsAPI::setZeroRTargets() {
	m_DContx.zeroRT();
}


void CGraphicsAPI::clearRTV(CRenderTargetView & inRTV, float & inColor) {
	m_DContx.clearRTV(inRTV, inColor);

}


void CGraphicsAPI::clearDSV(CDepthStencilView & inDSV, unsigned int inFlags, float inDepth, unsigned int inStencil) {
	m_DContx.clearDSV(inDSV, inFlags, inDepth, inStencil);

}


void CGraphicsAPI::setVPorts(unsigned int inNumViews, CViewPort & inVP) {
#ifdef D_DIRECTX
	m_DContx.setVPorts(inNumViews, inVP);

#endif
}


void CGraphicsAPI::setVShader(CVertexShader & inShader) {
	m_DContx.setVS(inShader);
}


void CGraphicsAPI::setPShader(CPixelShader & inShader) {
	m_DContx.setPS(inShader);
}


void CGraphicsAPI::setSResource(ID3D11ShaderResourceView *inSRV) {
	m_DContx.setSResource(inSRV);
}


void CGraphicsAPI::setSampler(CSamplerState & inSampler) {
	m_DContx.setSampler(inSampler);
}


void CGraphicsAPI::setDrawIndex(int inIndex) {
	m_DContx.setDrawIndexed(inIndex);
}


void CGraphicsAPI::show() {
	m_SChain.m_SwapChain->Present(0, 0);
}


#ifdef D_DIRECTX
void CGraphicsAPI::setTopology(D3D11_PRIMITIVE_TOPOLOGY inTopology) {
	m_DContx.m_DeviceContext->IASetPrimitiveTopology(inTopology);
}


HRESULT CGraphicsAPI::createSRViewFFile(ID3D11ShaderResourceView **inSRView) {
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(m_Device.Device, L"seafloor.dds", NULL, NULL, inSRView, NULL))) {
		return false;
	}
	else { return S_OK; }

}


HRESULT CGraphicsAPI::createSRView(CTexture2D & inTexture, D3D11_SHADER_RESOURCE_VIEW_DESC inDesc, ID3D11ShaderResourceView * inSRView) {
	
		if (FAILED(m_Device.Device->CreateShaderResourceView(inTexture.m_Texture, &inDesc, &inSRView))) {
			return false;
		}
		else { return S_OK; }
}


 void CGraphicsAPI::updateSResource(CBuffer & inResource, const void* inData) {
	 m_DContx.m_DeviceContext->UpdateSubresource(inResource.Buffer, 0, NULL, &inData, 0, 0);
}
#endif