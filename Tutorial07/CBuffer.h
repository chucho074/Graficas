/**
* @LC		: 24/02/2020
* @file		: CBuffer.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A base class for Buffers.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include "Defines.h"
#include "Includes.h"
#include "include/assimp/cimport.h"
#include "include/assimp/Importer.hpp"
#include "include/assimp/material.h"
#include "include/assimp/scene.h"
#include "include/assimp/postprocess.h"

/**
* @brief	: Descriptor for Buffers.
* @bug		: No Bugs known.
**/
struct BufferDesc {
	unsigned int byteWidth;
	USAGE usage;
	unsigned int bindFlags;
	unsigned int cpuAccessFlags;
	unsigned int miscFlags;
	unsigned int structureByteStride;
};


/**
* @brief	: Class for Buffers.
* @bug		: No Bugs knowns.
**/
class CBuffer {
public:
	/**
	* @brief	: Constructor of the class.
	* @bug		: No Bugs known.
	**/
	CBuffer();
	
	/**
	* @brief	: Initializer.
	* @param	: BufferDesc.
	* @bug		: No Bug known.
	**/
	void init(BufferDesc inDesc);

	/**
	* @brief	: Getter for the buffer.
	* @bug		: No Bug known.
	**/
	void * getBuffer();

	BufferDesc Desc;
	
	
#ifdef D_DIRECTX
	D3D11_BUFFER_DESC m_bd;
	ID3D11Buffer * Buffer;
	
	static void createVertexBuffer(int numVertex, const aiScene* model, SimpleVertex* vertex, ID3D11Buffer*& buffer, ID3D11Device* Dev);
	static void createIndexBuffer(int numIndex, const aiScene* model, WORD* index, ID3D11Buffer*& buffer, ID3D11Device* Dev);

#endif
};