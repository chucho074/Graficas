/**
* @LC		: 04/06/2020
* @file		: CVertexShader.h
* @Author	: Jes�s Alberto Del Moral Cupil
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
* @brief	: Class for Vertex Shader abstraction.
* @bug		: No Bugs known.
**/
class CVertexShader : public CShaders {
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
	void * getShader();

	
#ifdef D_DIRECTX
	ID3D11VertexShader * m_VertexShader;
#endif
};