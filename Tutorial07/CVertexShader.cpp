/**
* @LC		: 24/02/2020
* @file		: CVertexShader.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 19/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CVertexShader.h"

CVertexShader::CVertexShader() {
#ifdef D_DIRECTX
	m_pVSBlob = NULL;
	m_pVertexShader = NULL;
	m_pInputLayout = NULL;
#endif
}

void * CVertexShader::getBlob() {
#ifdef D_DIRECTX
	return m_pVSBlob;
#else
	return nullptr;
#endif
}

void * CVertexShader::getVS() {
#ifdef D_DIRECTX
	return m_pVertexShader;
#else
	return nullptr;
#endif
}

void * CVertexShader::getInputLayout() {
#ifdef D_DIRECTX
	return m_pInputLayout;
#else
	return nullptr;
#endif
}
