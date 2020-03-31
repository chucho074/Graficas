/**
* @LC		: 24/02/2020
* @file		: CVertexShader.h
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
* @brief	: Class for Vertex Shader abstraction.
* @bug		: No Bugs known.
**/
class CVertexShader {
public:

	/**
	* @brief	: Constructor of the class.
	* @bug		: No Bugs known.
	**/
	CVertexShader();

	/**
	* @brief	: Getter for the Blob.
	* @bug		: No Bugs known.
	**/
	void * getBlob();

	/**
	* @brief	: Getter for the Vertex Shader.
	* @bug		: No Bugs known.
	**/
	void * getVS();

	/**
	* @brief	: Getter for the Input Layout.
	* @bug		: No Bugs known.
	**/
	void * getInputLayout();

#ifdef D_DIRECTX
	ID3DBlob * m_pVSBlob;
	ID3D11VertexShader * m_pVertexShader;
	ID3D11InputLayout * m_pInputLayout;
#endif
};