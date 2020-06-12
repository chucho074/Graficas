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
	//   g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView)
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

HRESULT CDevice::createInputLayoutDescFromVertexShaderSignature(CVertexShader & inVS, CInputLayout & inIL) {
	
	// Reflect shader info
	ID3D11ShaderReflection* pVertexShaderReflection = NULL;
	if (FAILED(D3DReflect(inVS.m_Blob->GetBufferPointer(), inVS.m_Blob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pVertexShaderReflection))) {
		return S_FALSE;
	}

	// Get shader info
	D3D11_SHADER_DESC shaderDesc;
	pVertexShaderReflection->GetDesc(&shaderDesc);

	// Read input layout description from shader info
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	int offset = 0;
	for (int i = 0; i < shaderDesc.InputParameters; i++) {
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

		// fill out input element desc
		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = offset;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		// determine DXGI format
		if (paramDesc.Mask == 1) {
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3) {
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 15) {
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT; offset += 12;
		}
		else if (paramDesc.Mask <= 7) {
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		//save element desc
		inputLayoutDesc.push_back(elementDesc);
	}


	// Try to create Input Layout
	HRESULT hr = Device->CreateInputLayout(&inputLayoutDesc[0], inputLayoutDesc.size(), inVS.m_Blob->GetBufferPointer(), inVS.m_Blob->GetBufferSize(), &inIL.m_InputLayout);

	//Free allocation shader reflection memory
	pVertexShaderReflection->Release();
	return hr;
	}


