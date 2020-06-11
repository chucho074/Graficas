/**
* @LC		: 10/06/2020
* @file		: CInputLayout.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 4/06/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CInputLayout.h"

CInputLayout::CInputLayout() {
#ifdef D_DIRECTX
	m_InputLayout = NULL;
#endif
}


CInputLayout::~CInputLayout() {

}


void * CInputLayout::getInputLayout() {
#ifdef D_DIRECTX
	return m_InputLayout;
#else
	return nullptr;
#endif
}

