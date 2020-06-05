/**
* @LC		: 24/02/2020
* @file		: CVertexBuffer.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#pragma once
#include "CBuffer.h"
#include "Includes.h"


/**
* @brief	: Class for Vertex Buffer.
* @bug		: No Bugs known.
**/
class CVertexBuffer {
public:

	/**
	* @brief	: Initializer.
	* @bug		: No Bugs known.
	**/
	CVertexBuffer();
	
	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CVertexBuffer();
	/**
	* @brief	: Init for the class.
	* @param	: SubresourceData, BufferDesc
	* @bug		: No Bugs known.
	**/
	void init(SubresourceData inSD, BufferDesc inDesc);

	/**
	* @brief	: Getter for the Vertex Buffer.
	* @bug		: No Bugs known.
	**/
	void * getVB();

	CBuffer Buffer;
#ifdef D_DIRECTX
	D3D11_SUBRESOURCE_DATA Data;
#endif
};