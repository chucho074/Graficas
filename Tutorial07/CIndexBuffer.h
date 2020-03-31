/**
* @LC		: 24/02/2020
* @file		: CIndexBuffer.h
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
* @brief	: Class for Index Buffer.
* @bug		: No Bugs known.
**/
class CIndexBuffer {
public:

	/**
	* @brief	: Init of the class.
	* @param	: DescBuffer.
	* @bug		: No Bugs known.
	**/
	void init(SubresourceData s, BufferDesc b);
	
	/**
	* @brief	: Getter for the Buffer.
	* @bug		: No Bugs known.
	**/
	void * getIB();
	
	CBuffer Buffer;
#ifdef D_DIRECTX
	D3D11_SUBRESOURCE_DATA m_Data;
#endif 
};