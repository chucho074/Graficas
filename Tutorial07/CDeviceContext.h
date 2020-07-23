/**
* @LC		: 06/07/2020
* @file		: CDeviceContext.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 06/07/2020
* @brief	: A class for the abstraction of the Device Context.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#if (defined D_DirectX || defined R_DirectX)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#endif
#include "Defines.h"
#include "CBuffer.h"
#include "CRenderTargetView.h"
#include "CDepthStencilView.h"
#include "CViewport.h"
#include "CInputLayout.h"
#include "CVertexShader.h"
#include "CPixelShader.h"
#include "CSamplerState.h"

class CDeviceContext {
public:
	/**
	* @brief	: Constructor of the class.
	* @bug		: No Bugs known.
	**/
	CDeviceContext();
	/**
	* @brief	: Destructor of the class.
	* @bug		: No Bugs known.
	**/
	~CDeviceContext();
	/**
	* @brief	: Sets Vertex Buffer.
	* param		: startSlot, Size, VertexBuffer
	* @bug		: No Bugs known.
	**/
	void setVBuffer(unsigned int inStartSlot, unsigned int inSize, CBuffer & inVBuffer);
	/**
	* @brief	: Sets Index Buffer.
	* param		: Format, IndexBuffer.
	* @bug		: No Bugs known.
	**/
	void setIBuffer(int inFormat, CBuffer * inIBuffer);
	/**
	* @brief	: Sets VertexShader ConstatnBuffer.
	* param		: startSlot, CBuffer.
	* @bug		: No Bugs known.
	**/
	void setVSConstBuffer(unsigned int inStartSlot, CBuffer & inConstBuffer);
	/**
	* @brief	: Sets PixelShader ConstatnBuffer.
	* param		: startSlot, CBuffer.
	* @bug		: No Bugs known.
	**/
	void setPSConstBuffer(unsigned int inStartSlot, CBuffer & inConstBuffer);
	/**
	* @brief	: Update SubResource.
	* param		: Data, Buffer to update.
	* @bug		: No Bugs known.
	**/
	void updateBuffer(void * inData, CBuffer inBuffer);
	/**
	* @brief	: Sets the render target.
	* param		: num of views, RTV, DSV.
	* @bug		: No Bugs known.
	**/
	void setRTargets(unsigned int inNumViews, CRenderTargetView & inRTV, CDepthStencilView & inDSV);
	/**
	* @brief	: Sets the render target.
	* param		: CViewport.
	* @bug		: No Bugs known.
	**/
	void setVP(CViewport inVP);
	/**
	* @brief	: Sets the render target.
	* param		: CInputLayout.
	* @bug		: No Bugs known.
	**/
	void setVP(CInputLayout inIL);
	/**
	* @brief	: Sets the topology.
	* param		: D3D_PRIMITIVE_TOPOLOGY.
	* @bug		: No Bugs known.
	**/
	void setTopology(D3D_PRIMITIVE_TOPOLOGY inTopology);
	/**
	* @brief	: Sets the Vertex Shader.
	* param		: CVertexShader.
	* @bug		: No Bugs known.
	**/
	void setVS(CVertexShader inVS);
	/**
	* @brief	: Sets the Pixel Shader.
	* param		: CPixelShader.
	* @bug		: No Bugs known.
	**/
	void setPS(CPixelShader inPS);
	/**
	* @brief	: Sets the Shader Resource.
	* param		: ID3D11ShaderResourceView.
	* @bug		: No Bugs known.
	**/
	void setSResourceView(ID3D11ShaderResourceView * inSRV);
	/**
	* @brief	: Sets the SamplerState.
	* param		: CSamplerState.
	* @bug		: No Bugs known.
	**/
	void setSamplerState(CSamplerState * inSS);
	/**
	* @brief	: Clear RTV.
	* param		: CSamplerState.
	* @bug		: No Bugs known.
	**/
	void clearRTV(CRenderTargetView * inRTV, float inColor[4]);


	void render(unsigned int inNumIndex);

private:
	ID3D11DeviceContext * m_DeviceContext;

};

