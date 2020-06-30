/**
* @LC		: 25/06/2020
* @file		: CGraphicsAPI.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 23/06/2020
* @brief	: A class for the control of the Device, DevContext and SwapChain.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include <windows.h>
#if (defined D_DirectX || defined R_DirectX)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#endif
#include "CBuffer.h"

/**
* @brief	: Abstraction for Graphics API.
* @bug		: No Bugs known.
**/
class CGraphicsAPI {
public:
	/**
	* @brief	: Sets everythin in Null.
	* @bug		: No Bugs known.
	**/
	CGraphicsAPI();
	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CGraphicsAPI();
	/**
	* @brief	: Create Device & SwapChain.
	* param		: DeviceFlags, Swapchain Desc.
	* @bug		: No Bugs known.
	**/
#if (defined D_DirectX || defined R_DirectX) 
	HRESULT init(unsigned int inDevFlag, DXGI_SWAP_CHAIN_DESC inSCDesc);
#endif
	/**
	* @brief	: Update.
	* param		: .
	* @bug		: No Bugs known.
	**/
	int update();
	/**
	* @brief	: Render.
	* param		: .
	* @bug		: No Bugs known.
	**/
	void render();
	/**
	* @brief	: Release and sets in null.
	* @bug		: No Bugs known.
	**/
	void destroy();
	/**
	* @brief	: Create a buffer.
	* param		: A descriptor for the buffer.
	* @bug		: No Bugs known.
	**/
	HRESULT createBuffer(CBuffer &inBuffer, BufferDesc inDesc);
	/**
	* @brief	: Sets Vertex Buffer.
	* param		: startSlot, Size, VertexBuffer
	* @bug		: No Bugs known.
	**/
	void setVBuffer(int inStartSlot, unsigned int inSize, CBuffer * inVBuffer);
	/**
	* @brief	: Sets Index Buffer.
	* param		: Format, IndexBuffer.
	* @bug		: No Bugs known.
	**/
	void setIBuffer(int inFormat, CBuffer * inIBuffer);
	/**
	* @brief	: Sets ConstatnBuffer.
	* param		: startSlot, set in Vertex and Pixel?, Constant Buffer
	* @bug		: No Bugs known.
	**/
	void setConstBuffer(int inStartSlot, bool inSetBoth, CBuffer * inConstBuffer);
	/**
	* @brief	: Update SubResource.
	* param		: Data, Buffer to update.
	* @bug		: No Bugs known.
	**/
	void updateBuffer(void * inData, CBuffer inBuffer);
	/**
	* @brief	: Sets teh num of indexes to draw.
	* param		: Num of indexes to draw.
	* @bug		: No Bugs known.
	**/
	void draw(unsigned int inNumIndex);
	/**
	* @brief	: Make the present from the SwapChain.
	* @bug		: No Bugs known.
	**/
	void show();

#if (defined D_DirectX || defined R_DirectX) 
	/**
	* @brief	: Create a render target view with the device.
	* param		: Texture2D, Render Target View
	* @bug		: No Bugs known.
	**/
	HRESULT createRTV(ID3D11Texture2D *& inBBuffer, ID3D11RenderTargetView *& inRTV);
	/**
	* @brief	: Create a texture with the device.
	* param		: Texture desc, Texture2d. 
	* @bug		: No Bugs known.
	**/
	HRESULT createTex2D(D3D11_TEXTURE2D_DESC inDesc, ID3D11Texture2D *& inTex);
	/**
	* @brief	: Create a depth Stencil View with the device.
	* param		: Texture2D, DSV Desc, depth stencil View.
	* @bug		: No Bugs known.
	**/
	HRESULT createDSV(ID3D11Texture2D *& inDS, D3D11_DEPTH_STENCIL_VIEW_DESC inDSVDesc, ID3D11DepthStencilView *& inDSV);
	/**
	* @brief	: Sets the render target.
	* param		: num of views, RTV, DSV.
	* @bug		: No Bugs known.
	**/
	void setRTargets(unsigned int inNumViews, ID3D11RenderTargetView * inRTV, ID3D11DepthStencilView * inDSV);
	
	/**
	* @brief	: Sets the Viewport to the DeviceContext.
	* param		: Viewport.
	* @bug		: No Bugs known.
	**/
	void setVPort(D3D11_VIEWPORT inVP);
	/**
	* @brief	: Create the Vertex Shader.
	* param		: Blob, ClassLinkage, VertexShader.
	* @bug		: No Bugs known.
	**/
	HRESULT createVS(ID3DBlob *& inBlob, ID3D11ClassLinkage * inClass, ID3D11VertexShader *& inVS);
	/**
	* @brief	: Create Input Layout.
	* param		: IL Desc, num of elements, blob, IL.
	* @bug		: No Bugs known.
	**/
	HRESULT createIL(D3D11_INPUT_ELEMENT_DESC * inILDesc, unsigned int inNumElem, ID3DBlob *& inBlob, ID3D11InputLayout *& inIL);
	/**
	* @brief	: Sets the Input Layout.
	* param		: InputLayout.
	* @bug		: No Bugs known.
	**/
	void setIL(ID3D11InputLayout * inIL);
	/**
	* @brief	: Create Pixel Shader.
	* param		: Blob, ClassLinkage, PixelShader.
	* @bug		: No Bugs known.
	**/
	HRESULT createPS(ID3DBlob *& inBlob, ID3D11ClassLinkage * inClass, ID3D11PixelShader *& inPS);

	/**
	* @brief	: Set the topology.
	* param		: DirectX Topology value
	* @bug		: No Bugs known.
	**/
	void setTopology(D3D_PRIMITIVE_TOPOLOGY inTopology);
	/**
	* @brief	: Create the sampler State.
	* param		: Sampler Desc, SamplerState.
	* @bug		: No Bugs known.
	**/
	HRESULT createSState(D3D11_SAMPLER_DESC inSSDesc, ID3D11SamplerState *&inSampler);
	/**
	* @brief	: Sets the Vertex and pixel Shader.
	* param		: Vertex shader, Pixel Shader.
	* @bug		: No Bugs known.
	**/
	void setShaders(ID3D11VertexShader * inVS, ID3D11PixelShader * inPS);
	/**
	* @brief	: Sets shader Resource View.
	* param		: ShaderResource View.
	* @bug		: No Bugs known.
	**/
	void setSResource(ID3D11ShaderResourceView * inSRV);
	/**
	* @brief	: Set the Sampler State.
	* param		: Sampler State.
	* @bug		: No Bugs known.
	**/
	void setSampler(ID3D11SamplerState * inSS);
	/**
	* @brief	: Return the device.
	* @bug		: No Bugs known.
	**/ 
	ID3D11Device* getDev();
	/**
	* @brief	: Return the Driver Type.
	* @bug		: No Bugs known.
	**/
	D3D_DRIVER_TYPE getDriverType();
	/**
	* @brief	: Clears the render Target View.
	* param		: RenderTarget view, color.
	* @bug		: No Bugs known.
	**/
	void clearRTV(ID3D11RenderTargetView * inRTV, float inColor[4]);
	/**
	* @brief	: Clears the DepthStencil View.
	* param		: DSV, ClearFlag
	* @bug		: No Bugs known.
	**/
	void clearDSV(ID3D11DepthStencilView * inDSV, D3D11_CLEAR_FLAG inFlag);
#endif
private:
#if (defined D_DirectX || defined R_DirectX) 
	/**
	* @brief	: Device of DX.
	* @bug		: No Bugs known.
	**/
	ID3D11Device * m_Device;
	/**
	* @brief	: DeviceContext of DX.
	* @bug		: No Bugs known.
	**/
	ID3D11DeviceContext * m_DeviceContext;
	/**
	* @brief	: SwapChain of DX.
	* @bug		: No Bugs known.
	**/
	IDXGISwapChain * m_SwapChain;
	/**
	* @brief	: The driver type used.
	* @bug		: No Bugs known.
	**/
	D3D_DRIVER_TYPE m_driverType;
	/**
	* @brief	: The feature Lvl used.
	* @bug		: No Bugs known.
	**/
	D3D_FEATURE_LEVEL m_featureLevel;
#endif
};

