/**
* @LC		: 04/06/2020
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
#include "CShaders.h"

/**
* @brief	: Class for Pixel Shader abstraction.
* @bug		: No Bugs known.
**/
class CPixelShader : public CShaders  {
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
	* @brief	: Getter for the Blob.
	* @bug		: No Bugs known.
	**/
	void * getBlob();

	/**
	* @brief	: Getter the PixelShader.
	* @bug		: No Bugs known.
	**/
	void * getShader();
#ifdef D_DIRECTX

	ID3D11PixelShader * m_PixelShader;
#endif
};