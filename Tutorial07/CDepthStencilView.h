/**
* @LC		: 02/07/2020
* @file		: CDepthStencilView.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 01/07/2020
* @brief	: .
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include "Defines.h"
#if (defined D_DirectX || defined R_DirectX) 
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#endif

/**
* @brief	: DepthStencilViewDesc.
* @bug		: No Bugs Known.
**/
struct DepthStencilViewDesc {
	FORMAT format;
	DSV_DIMENSION viewDimension;
	unsigned int flags;
	union {
		TEX1D_DSV textureID;
		TEX1D_ARRAY_DSV texture1DArray;
		TEX2D_DSV texture2D;
		TEX2D_ARRAY_DSV texture2DArray;
		TEX2DMS_DSV texture2DMS;
		TEX2DMS_ARRAY_DSV texture2DMSArray;
	};
};

/**
* @brief	: Abstraction for DepthStencilView.
* @bug		: No Bugs Known.
**/
class CDepthStencilView {
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs Known.
	**/
	CDepthStencilView();

	/**
	* @brief	: Constructor.
	* @bug		: No Bugs Known.
	**/
	~CDepthStencilView();

	/**
	* @brief	: set Description and format.
	* @param	: DepthStencilViewDesc.
	* @bug		: No Bugs Known.
	**/
	void setDesc(DepthStencilViewDesc inDesc);

	/**
	* @brief	: Getter for the DepthStencilView.
	* @bug		: No Bugs Known.
	**/
	void * getDSV();

//private:
	DepthStencilViewDesc m_Desc;
#if (defined D_DirectX || defined R_DirectX) 
	ID3D11DepthStencilView * m_pDepthStencilView;
#endif
};

