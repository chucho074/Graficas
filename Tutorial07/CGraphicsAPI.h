/**
* @LC		: 08/06/2020
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
	* @param	: DriverType.
	* @bug		: No Bugs known.
	**/
	void setDriverType(unsigned int inDriverType);

	/**
	* @brief	: Create the Device and the Swapchain.
	* @param	: FeatureLevel.
	* @bug		: No Bugs known.
	**/
	HRESULT createDevnSC(FEATURE_LEVEL inFeatureLvl);

	/**
	* @brief	: Create the Render Target View.
	* @param	: CTexture2D, CRenderTargetView.
	* @bug		: No Bugs known.
	**/
	HRESULT createRTV(CTexture2D & inTexture, CRenderTargetView & inRTV);

	/**
	* @brief	: Create a texture.
	* @param	: CTexture2D.
	* @bug		: No Bugs known.
	**/
	HRESULT createTexture(CTexture2D & inTexture);

	/**
	* @brief	: Create a depth Stencil View.
	* @param	: CTexture2D, CDepthStencilView.
	* @bug		: No Bugs known.
	**/
	HRESULT createDSV(CTexture2D & inDStencil, CDepthStencilView & inDSView);

	/**
	* @brief	: Create a View Port and asign to the Dev context.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	void createVPort(ViewPortDesc inVPDesc);

	/**
	* @brief	: Create a Vertex Shader.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	HRESULT createVShader(CVertexShader & inVShader);

	/**
	* @brief	: Create and Set the InputLayout.
	* @param	: CVertexShader.
	* @bug		: No Bugs known.
	**/
	HRESULT createILayout(CVertexShader & inVShader);

	/**
	* @brief	: Create a Pixel Shader.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	HRESULT createPShader(CPixelShader &inPShader);

	/**
	* @brief	: Create a Buffer.
	* @param	: CBuffer, bool for have a SubResource Data.
	* @bug		: Needs to be change.
	**/
	HRESULT createBuffer(CBuffer & inBuffer, bool inUseSRD);

	/**
	* @brief	: Sets a Vertex Buffer.
	* @param	: CBuffer.
	* @bug		: No Bugs known.
	**/
	void setVBuffer(CBuffer & inVBuffer);

	/**
	* @brief	: Sets a Index Buffer.
	* @param	: CBuffer.
	* @bug		: No Bugs known.
	**/
	void setIBuffer(CBuffer & inVBuffer);

	/**
	* @brief	: Sets Constant Buffer.
	* @param	: unsigned int, CBuffer.
	* @bug		: No Bugs known.
	**/
	void setCBuffer(unsigned int inStartLot, CBuffer & inCBuffer);

	/**
	* @brief	: Create a SamplerState.
	* @param	: CSamplerState.
	* @bug		: No Bugs known.
	**/
	HRESULT createSState(CSamplerState & inSampler);

	/**
	* @brief	: Make a Resize to the buffers.
	* @bug		: No Bugs known.
	**/
	HRESULT resizeBuffers();

	/**
	* @brief	: Make the present.
	* @bug		: No Bugs known.
	**/
	void show();

#ifdef D_DIRECTX
	/**
	* @brief	: Sets the topology to the Device Context.
	* @param	: D3D11_PRIMITIVE_TOPOLOGY.
	* @bug		: No Bugs known.
	**/
	void setTopology(D3D11_PRIMITIVE_TOPOLOGY inTopology);

	/**
	* @brief	: Create a shader resource View form a file.
	* @param	: ID3D11ShaderResourceView.
	* @bug		: No Bugs known.
	**/
	HRESULT createSRViewFFile(ID3D11ShaderResourceView * inSRView);

	/**
	* @brief	: Create a shader Resource View.
	* @param	: CTexture2D, D3D11_SHADER_RESOURCE_VIEW_DESC, ID3D11ShaderResourceView.
	* @bug		: No Bugs known.
	**/
	HRESULT createSRView(CTexture2D & inTexture, D3D11_SHADER_RESOURCE_VIEW_DESC inDesc, ID3D11ShaderResourceView * inSRView);

	/**
	* @brief	: Make a update to the SubResource.
	* @param	: CBuffer, const void*.
	* @bug		: No Bugs known.
	**/
	void updateSResource(CBuffer &inResource, const void* inData);
#endif
//private:

	/**
	* @brief	: Access to the CDevice Class.
	* @bug		: No Bugs known.
	**/
	CDevice				m_Device;

	/**
	* @brief	: Access to the CDeviceContext Class.
	* @bug		: No Bugs known.
	**/
	CDeviceContext		m_DContx;

	/**
	* @brief	: Access to the CSwapChain Class.
	* @bug		: No Bugs known.
	**/
	CSwapChain			m_SChain;


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

