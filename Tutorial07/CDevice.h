/**
* @LC		: 06/07/2020
* @file		: CDevice.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 04/07/2020
* @brief	: A class for the abstraction of the Device.
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
#include "CTexture2D.h"
#include "CRenderTargetView.h"
#include "CDepthStencilView.h"
#include "CSamplerState.h"

class CDevice {
public:
	/**
	* @brief	: Constructor of the class.
	* @bug		: No Bugs known.
	**/
	CDevice();
	/**
	* @brief	: Destructor of the class.
	* @bug		: No Bugs known.
	**/
	~CDevice();
	/**
	* @brief	: Create a Buffer.
	* @param	: .
	* @bug		: No Bugs known.
	**/
	///Create a Buffer
	HRESULT createBuffer(CBuffer & inBuffer, D3D11_BUFFER_DESC inDesc, D3D11_SUBRESOURCE_DATA inSRD);
	/**
	* @brief	: Create a Render Target View.
	* @param	: CTexture2D, CRenderTargetView.
	* @bug		: No Bugs known.
	**/
	HRESULT createRTV(CTexture2D & inTexture, CRenderTargetView & inRTV);
	/**
	* @brief	: Create a Texture in the Device.
	* @param	: CTexture2D.
	* @bug		: No Bugs known.
	**/
	HRESULT createTexture(CTexture2D & inTexture, D3D11_TEXTURE2D_DESC inDesc);
	/**
	* @brief	: Create a DepthStencilView in the Device.
	* @param	: CTexture2D, CDepthStencilView.
	* @bug		: No Bugs known.
	**/
	HRESULT createDSV(CTexture2D & inDStencil, CDepthStencilView & inDSView, D3D11_DEPTH_STENCIL_VIEW_DESC inDesc);

	///Create CVertexShader
	/**
	* @brief	: Create a Vertex Shader in the Device.
	* @param	: CVertexShader.
	* @bug		: No Bugs known.
	**/
	HRESULT createVShader(ID3DBlob * inBlob, ID3D11ClassLinkage * inClass, ID3D11VertexShader *& inVS);

	///Create Input Layout
	HRESULT createILayout(D3D11_INPUT_ELEMENT_DESC * inILDesc, unsigned int inNumElem, ID3DBlob *& inBlob, ID3D11InputLayout *& inIL);
	///Create Pixel Shader
	/**
	* @brief	: Create a Pixel Shader in the Device.
	* @param	: CPixelShader.
	* @bug		: No Bugs known.
	**/
	HRESULT createPShader(ID3DBlob * inBlob, ID3D11PixelShader * inPS);
	///Create SamplerState
	/**
	* @brief	: Create a Sampler State in the Device.
	* @param	: CSamplerState.
	* @bug		: No Bugs known.
	**/
	HRESULT createSampler(D3D11_SAMPLER_DESC inDesc, CSamplerState & inSampler);
	
private:
	DeviceDesc m_Desc;
	ID3D11Device * m_Device;
};

