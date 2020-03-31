/**
* @LC		: 24/02/2020
* @file		: CDepthStencilView.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs
**/

/**
* Headers
**/
#pragma once
#include "Defines.h"
#include "Includes.h"

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
	* @brief	: Initializer.
	* @param	: DepthStencilViewDesc, FORMAT.
	* @bug		: No Bugs Known.
	**/
	void init(DepthStencilViewDesc inDesc, FORMAT inFormat);

	/**
	* @brief	: Getter for the DepthStencilView.
	* @bug		: No Bugs Known.
	**/
	void * getDSV();

#ifdef D_DIRECTX
	ID3D11DepthStencilView * m_pDepthStencilView;
	D3D11_DEPTH_STENCIL_VIEW_DESC m_Desc;
#endif
};