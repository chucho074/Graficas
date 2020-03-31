/**
* @LC		: 24/02/2020
* @file		: CPixelShader.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 19/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CPixelShader.h"

CPixelShader::CPixelShader() {
#ifdef D_DIRECTX
	m_pPSBlob = NULL;
	m_pPixelShader = NULL;
#endif 
}

CPixelShader::~CPixelShader() {

}

void * CPixelShader::getPS() {
#ifdef D_DIRECTX
	return m_pPixelShader;
#else
	return nullptr;
#endif 
}
