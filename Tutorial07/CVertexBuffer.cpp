/**
* @LC		: 24/02/2020
* @file		: CVertexBuffer.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#include "CVertexBuffer.h"

CVertexBuffer::CVertexBuffer() {

}

CVertexBuffer::~CVertexBuffer() {

}

void CVertexBuffer::init(SubresourceData inSD, BufferDesc inDesc) {
	Buffer.init(inDesc);
#ifdef D_DIRECTX
	ZeroMemory(&Data, sizeof(Data));
	Data.pSysMem = inSD.psysMem;
#endif
}

void * CVertexBuffer::getVB() {
#ifdef D_DIRECTX
	return Buffer.getBuffer();
#else
	return nullptr;
#endif
}
