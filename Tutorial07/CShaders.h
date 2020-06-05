/**
* @LC		: 04/06/2020
* @file		: CPixelShader.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 02/06/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include "Defines.h"
#include "Includes.h"

class CShaders {
public:
	
	virtual void * getShader() = 0;
	virtual void * getBlob() { 
	#ifdef D_DIRECTX
			return m_Blob;
	#else
			return nullptr;
	#endif
	}
	//virtual void * getInputLayout();

#ifdef D_DIRECTX
	ID3DBlob * m_Blob;
#endif
};

