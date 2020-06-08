/**
* @LC		: 24/02/2020
* @file		: CRenderTargetView.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#pragma once
#include "Defines.h"
#include "Includes.h"

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
* @brief	: Short description of function.
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
	* @brief	: Initializer.
	* @param	: RenderTargetViewDesc.
	* @bug		: No Bugs known.
	**/
	void init(RenderTargetViewDesc inDesc);

	/**
	* @brief	: Getter for the RenderTargetView.
	* @bug		: No Bugs known.
	**/
	void * getRTV();

#ifdef D_DIRECTX
	ID3D11RenderTargetView * m_RTV;
	D3D11_RENDER_TARGET_VIEW_DESC m_Desc;
#endif 
};