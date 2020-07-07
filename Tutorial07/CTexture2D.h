/**
* @LC		: 02/07/2020
* @file		: CTexture.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 01/07/2020
* @brief	: .
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#if (defined D_DirectX || defined R_DirectX) 
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#endif
#include "Defines.h"


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
	* @brief	: Set desc.
	* @param	: TextureDesc.
	* @bug		: No Bugs known.
	**/
	void setDesc(TextureDesc inDesc);

	/**
	* @brief	: Getter for the texture.
	* @bug		: No Bugs known.
	**/
	void * getTexture();

	void destroy();

//private:
	TextureDesc m_Desc;

#if (defined D_DirectX || defined R_DirectX) 
	ID3D11Texture2D * m_Texture;
#endif

};