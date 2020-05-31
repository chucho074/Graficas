/**
* @LC		: 28/05/2020
* @file		: CBaseBuffer.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 27/05/2020
* @brief	: A base class for Buffers.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include "Defines.h"
#include "Includes.h"

struct BufferDesc {
	unsigned int byteWidth;
	USAGE usage;
	unsigned int bindFlags;
	unsigned int cpuAccessFlags;
	unsigned int miscFlags;
	unsigned int structureByteStride;
};

class CBaseBuffer {
public:
	
	virtual ~CBaseBuffer() = 0;

	virtual int init() = 0;

	virtual void getBuffer() = 0;


	BufferDesc Desc;

#ifdef D_DIRECTX
	D3D11_BUFFER_DESC m_bd;
	ID3D11Buffer * Buffer = nullptr;
#endif
};

