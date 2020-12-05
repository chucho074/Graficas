/**
* @LC		: 22/08/2020
* @file		: CDepthStencilView.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 22/08/2020
* @brief	: .
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "resource.h"

/**
* @brief	: DepthStencilViewDesc.
* @bug		: No Bugs Known.
**/
struct DepthStencilViewDesc {
	unsigned int format;
	unsigned int viewDimension;
	unsigned int mipSlice;
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

	ID3D11DepthStencilView * m_DSV;
	DepthStencilViewDesc m_DSVDesc;
private:

};

