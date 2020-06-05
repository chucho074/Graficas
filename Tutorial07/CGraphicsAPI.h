/**
* @LC		: 01/06/2020
* @file		: CGraphicsAPI.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 28/05/2020
* @brief	: A basic description of the what do the doc.
* @bug		: Instancias Device, SChain, DContxt.
**/

/**
* Headers
**/
#pragma once
#include <vector>
#include "CManager.h"
#include "CDevice.h"
#include "CSwapChain.h"
#include "CDeviceContext.h"
#include "CBuffer.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CTexture2D.h"
#include "CDepthStencilView.h"
#include "CVertexShader.h"
#include "CPixelShader.h"
#include "CViewPort.h"
#include "CRenderTargetView.h"
#include "CSamplerState.h"


/*	TODO LIST:
 *	Quitar los singletons de Device, DeviceContext Swapchain
*/




/**
* @brief	: CGraphicAPI is the management of the Device, Device Context & SwapChain.
* @bug		: No Bugs known.
**/
class CGraphicsAPI /*: public CManager*/ {
public:
	/**
	* @brief	: Constructor of the class.
	* @bug		: No Bugs known.
	**/
	CGraphicsAPI();

	/**
	* @brief	: Destructor of the class.
	* @bug		: No Bugs known.
	**/
	~CGraphicsAPI();

	/**
	* @brief	: Initializer.
	* @param	: DeviceDesc, SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	int init(DeviceDesc &inDevDesc, SwapChainDesc &inSCDesc);

	/**
	* @brief	: Setter for the DriverType.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	void setDriverType(unsigned int inDriverType);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	HRESULT createDevnSC(FEATURE_LEVEL inFeatureLvl);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	HRESULT createRTV(CTexture2D inTexture, CRenderTargetView inRTV);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	HRESULT createTexture(CTexture2D inTexture);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	HRESULT createDSV(CTexture2D inDStencil, CDepthStencilView inDSView);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	void createVPort(ViewPortDesc inVPDesc);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	HRESULT createVShader(CVertexShader inVShader);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	HRESULT createILayout(CVertexShader inVShader);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	HRESULT createPShader(CPixelShader inPShader);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	HRESULT createBuffer(CBuffer inBuffer, bool inUseSRD);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	void setVBuffer(CBuffer inVBuffer);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	void setIBuffer(CBuffer inVBuffer);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	void setCBuffer(unsigned int inStartLot, CBuffer inCBuffer);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	HRESULT createSState(CSamplerState inSampler);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	HRESULT resizeBuffers();

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	void mergePtrs();

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	void show();

#ifdef D_DIRECTX
	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	void setTopology(D3D11_PRIMITIVE_TOPOLOGY inTopology);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	HRESULT createSRViewFFile(ID3D11ShaderResourceView * inSRView);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	HRESULT createSRView(CTexture2D inTexture, D3D11_SHADER_RESOURCE_VIEW_DESC inDesc, ID3D11ShaderResourceView * inSRView);

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	void updateSResource(CBuffer inResource, const void* inData);
#endif
//private:

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	CDevice				m_Device;

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	CDeviceContext		m_DContx;

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	CSwapChain			m_SChain;

public:
#ifdef D_DIRECTX
	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	ID3D11Device		* m_ptrDevice;

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	ID3D11DeviceContext * m_ptrDContx;

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	IDXGISwapChain		* m_ptrSChain;
#endif

private:
#ifdef D_DIRECTX
	HRESULT CreateInputLayoutDescFromVertexShaderSignature(ID3DBlob* pShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout) {
		// Reflect shader info
		ID3D11ShaderReflection* pVertexShaderReflection = NULL;
		if (FAILED(D3DReflect(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pVertexShaderReflection))) {
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
		HRESULT hr = pD3DDevice->CreateInputLayout(&inputLayoutDesc[0], inputLayoutDesc.size(), pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), pInputLayout);

		//Free allocation shader reflection memory
		pVertexShaderReflection->Release();
		return hr;
	}
#endif

};

