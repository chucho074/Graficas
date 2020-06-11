/**
* @LC		: 08/06/2020
* @file		: CDeviceContext.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include "Defines.h"
#include "Includes.h"
#include "CViewport.h"
#include "CVertexShader.h"
#include "CPixelShader.h"
#include "CRenderTargetView.h"
#include "CDepthStencilView.h"
#include "CSamplerState.h"
#include "CInputLayout.h"


/**
* @brief	: Abstraction for DeviceContext.
* @bug		: No Bugs known.
**/
class CDeviceContext {
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs known.
	**/
	CDeviceContext();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CDeviceContext();

	/**
	* @brief	: Getter for the Device Context.
	* @bug		: No Bugs known.
	**/
	void * getDeviceContext();

	/**
	* @brief	: Sets the VPorts to the DeviceContext.
	* @param	: CViewPort.
	* @bug		: No Bugs known.
	**/
	void setViewport(CViewPort inVP);

	/**
	* @brief	: Sets the ILayout in the DeviceCotext.
	* @param	: CVertexShader.
	* @bug		: No Bugs known.
	**/
	void setILayout(CInputLayout & inVS);
	
	/**
	* @brief	: Clears the renderTargets of the DeviceContext.
	* @bug		: No Bugs known.
	**/
	void zeroRT();
	
	/**
	* @brief	: Sets the RenderTargets in the DeviceCotext.
	* @param	: unsigned int, CRenderTargetView, CDepthStencilView.
	* @bug		: No Bugs known.
	**/
	void setRTarget(unsigned int inNumViews, CRenderTargetView & inRTV, CDepthStencilView & inDSV);
	
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
	* @brief	: Sets VertexShader.
	* @param	: CVertexShader.
	* @bug		: No Bugs known.
	**/
	void setVS(CVertexShader & inShader);

	/**
	* @brief	: Sets PixelShader.
	* @param	: CPixelShader.
	* @bug		: No Bugs known.
	**/
	void setPS(CPixelShader & inShader);

#ifdef D_DIRECTX
	/**
	* @brief	: Set ShaderResources.
	* @param	: ID3D11ShaderResourceView.
	* @bug		: No Bugs known.
	**/
	void setSResource(ID3D11ShaderResourceView * inTexture);
#endif
	
	/**
	* @brief	: Set Sampler State.
	* @param	: CSamplerState.
	* @bug		: No Bugs known.
	**/
	void setSampler(CSamplerState & inSampler);
	
	/**
	* @brief	: Set Draw Indexes.
	* @param	: int.
	* @bug		: No Bugs known.
	**/
	void setDrawIndexed(int inIndex);


	/**
	* @brief	: Sets the Viewports in the DeviceCotext.
	* @param	: unsigned int, CViewport.
	* @bug		: No Bugs known.
	**/
	void setVPorts(unsigned int inNumViews, CViewPort & inVP);
	


	void operator = (CDeviceContext const&) = delete;

#ifdef D_DIRECTX
	ID3D11DeviceContext * m_DeviceContext;
#endif
};