/**
* @LC		: 24/02/2020
* @file		: CTexture.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 13/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#pragma once
#include "Defines.h"
#include "Includes.h"

/**
* @brief	: Texture Desc.
* @bug		: No Bugs known.
**/
struct TextureDesc {
	unsigned int W;
	unsigned int H;
	unsigned int mipLevels;
	unsigned int arraySize;
	FORMAT format;
	SAMPLEDESC sampleDesc;
	USAGE usage;
	unsigned int flags;
	unsigned int cpuAccessFlags;
	unsigned int miscFlags;
};

/**
* @brief	: Abstraction for texture 2D.
* @bug		: No Bugs known.
**/
class CTexture2D {
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs known.
	**/
	CTexture2D();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CTexture2D();

	/**
	* @brief	: Initializer.
	* @param	: TextureDesc.
	* @bug		: No Bugs known.
	**/
	void init(TextureDesc inDesc);

	/**
	* @brief	: Getter for the texture.
	* @bug		: No Bugs known.
	**/
	void * getTexture();
	
	
	TextureDesc m_Data;


#ifdef D_DIRECTX
	ID3D11Texture2D * m_Texture;
	D3D11_TEXTURE2D_DESC m_Desc;
#endif

};