/**
* @LC		: 04/06/2020
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
	m_Blob = NULL;
	m_PixelShader = NULL;
#endif 
}


CPixelShader::~CPixelShader() {

}


void * CPixelShader::getBlob() {
#ifdef D_DIRECTX
	return m_Blob;
#else
	return nullptr;
#endif
}


void * CPixelShader::getShader() {
#ifdef D_DIRECTX
	return m_PixelShader;
#else
	return nullptr;
#endif 
}
