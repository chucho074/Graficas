/**
* @LC		: 24/02/2020
* @file		: CIndexBuffer.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#include "CIndexBuffer.h"

CIndexBuffer::CIndexBuffer() {

}

CIndexBuffer::~CIndexBuffer() {

}

void CIndexBuffer::init(SubresourceData s, BufferDesc b) {
	Buffer.init(b);
#ifdef D_DIRECTX
	ZeroMemory(&m_Data, sizeof(m_Data));
	m_Data.pSysMem = s.psysMem;
#endif
}

void * CIndexBuffer::getIB() {
#ifdef D_DIRECTX
	return Buffer.getBuffer();
#else
	return nullptr;
#endif
}
