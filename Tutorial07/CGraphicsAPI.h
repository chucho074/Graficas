/**
* @LC		: 08/06/2020
* @file		: CGraphicsAPI.h
* @Author	: Jes�s Alberto Del Moral Cupil
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
#include "CDevice.h"
#include "CSwapChain.h"
#include "CDeviceContext.h"
#include "CBuffer.h"
#include "CTexture2D.h"
#include "CDepthStencilView.h"
#include "CVertexShader.h"
#include "CPixelShader.h"
#include "CViewPort.h"
#include "CRenderTargetView.h"
#include "CSamplerState.h"
#include "CInputLayout.h"



/**
* @brief	: CGraphicAPI is the management of the Device, Device Context & SwapChain.
* @bug		: No Bugs known.
**/
class CGraphicsAPI {
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
	* @brief	: Compile and create a Vertex Shader.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	HRESULT createVShader(CVertexShader & inVShader);

	/**
	* @brief	: Create and Set the InputLayout.
	* @param	: CVertexShader, CInputLayout.
	* @bug		: No Bugs known.
	**/
	HRESULT createILayout(CVertexShader & inVShader, CInputLayout & inIL);

	/**
	* @brief	: Compile and create a Pixel Shader.
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
	* @brief	: Sets the RenderTargets in the DeviceCotext.
	* @param	: unsigned int, CRenderTargetView, CDepthStencilView.
	* @bug		: No Bugs known.
	**/
	void setRTargets(unsigned int inNumViews, CRenderTargetView & inRTV, CDepthStencilView & inDSV);
	
	/**
	* @brief	: Sets in 0's the renderTargets.
	* @bug		: No Bugs known.
	**/
	void setZeroRTargets();

	/**
	* @brief	: Clears the Render Target Views.
	* @param	: CRenderTargetView, float.
	* @bug		: No Bugs known.
	**/
	void clearRTV(CRenderTargetView & inRTV, float & inColor);
	
	/**
	* @brief	: Clears the DepthStencilView.
	* @param	: CRenderTargetView, unsigned int, float, unsigned int.
	* @bug		: No Bugs known.
	**/
	void clearDSV(CDepthStencilView & inDSV, unsigned int inFlags, float inDepth, unsigned int inStencil);


	/**
	* @brief	: Sets the Viewports in the DeviceCotext.
	* @param	: unsigned int, CViewport.
	* @bug		: No Bugs known.
	**/
	void setVPorts(unsigned int inNumViews, CViewPort & inVP);

	/**
	* @brief	: Sets VertexShader.
	* @param	: CVertexShader.
	* @bug		: No Bugs known.
	**/
	void setVShader(CVertexShader & inShader);
	
	/**
	* @brief	: Sets PixelShader.
	* @param	: CPixelShader.
	* @bug		: No Bugs known.
	**/
	void setPShader(CPixelShader & inShader);
	
	/**
	* @brief	: Set ShaderResources.
	* @param	: ID3D11ShaderResourceView.
	* @bug		: No Bugs known.
	**/
	void setSResource(ID3D11ShaderResourceView * inSRV);
	
	/**
	* @brief	: Sets the Sampler to the DeviceContext.
	* @param	: CSamplerState.
	* @bug		: No Bugs known.
	**/
	void setSampler(CSamplerState & inSampler);
	
	/**
	* @brief	: Sets the Draw indexes to the Device Context.
	* @param	: int.
	* @bug		: No Bugs known.
	**/
	void setDrawIndex(int inIndex);


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

};

