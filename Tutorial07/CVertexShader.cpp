/**
* @LC		: 10/06/2020
* @file		: CVertexShader.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 04/06/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CVertexShader.h"

CVertexShader::CVertexShader() {
#ifdef D_DIRECTX
	m_Blob = NULL;
	m_VertexShader = NULL;
#endif
}

void * CVertexShader::getBlob() {
#ifdef D_DIRECTX
	return m_Blob;
#else
	return nullptr;
#endif
}

void * CVertexShader::getShader() {
#ifdef D_DIRECTX
	return m_VertexShader;
#else
	return nullptr;
#endif
}


