/**
* @LC		: 24/02/2020
* @file		: CPixelShader.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 19/02/2020
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
* @brief	: Class for Pixel Shader abstraction.
* @bug		: No Bugs known.
**/
class CPixelShader {
public:
	/**
	* @brief	: Constructor of the class.
	* @bug		: No Bugs known.
	**/
	CPixelShader();

	/**
	* @brief	: Destructor of the class.
	* @bug		: No Bugs known.
	**/
	~CPixelShader();

	/**
	* @brief	: Getter the PixelShader.
	* @bug		: No Bugs known.
	**/
	void * getPS();
#ifdef D_DIRECTX
	ID3DBlob * m_pPSBlob;
	ID3D11PixelShader * m_pPixelShader;
#endif
};