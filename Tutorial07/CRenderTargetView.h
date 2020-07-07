/**
* @LC		: 02/07/2020
* @file		: CRenderTargetView.h
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
#if (defined D_DirectX || defined R_DirectX) 
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#endif
#include "Defines.h"

/**
* @brief	: Desc for RenderTargetView.
* @bug		: No Bugs known.
**/
struct RenderTargetViewDesc {
	FORMAT format;
	RTV_DIMENSION viewDimension;
	union {
		BUFFER_RTV buffer;
		TEX1D_RTV texture1D;
		TEX1D_ARRAY_RTV texture1DArray;
		TEX2D_RTV texture2D;
		TEX2D_ARRAY_RTV texture2DArray;
		TEX2DMS_RTV texture2DMS;
		TEX2DMS_ARRAY_RTV texture2DMSArray;
		TEX3D_RTV texture3D;
	};
};

/**
* @brief	: Abstraction for texture 2D.
* @bug		: No Bugs known.
**/
class CRenderTargetView {
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs known.
	**/
	CRenderTargetView();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CRenderTargetView();

	/**
	* @brief	: setDesc.
	* @param	: RenderTargetViewDesc.
	* @bug		: No Bugs known.
	**/
	void setDesc(RenderTargetViewDesc inDesc);

	/**
	* @brief	: Getter for the RenderTargetView.
	* @bug		: No Bugs known.
	**/
	void * getRTV();

	void destroy();

//private:
	RenderTargetViewDesc m_Desc;
#if (defined D_DirectX || defined R_DirectX) 
	ID3D11RenderTargetView * m_RTV;
#endif
};

