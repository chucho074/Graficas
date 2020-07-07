/**
* @LC		: 24/06/2020
* @file		: CBuffer.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 20/06/2020
* @brief	: A class for Buffers.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include <windows.h>
#if (defined D_DirectX || defined R_DirectX) 
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#endif
#include "Defines.h"


/**
* @brief	: SubResource Data.
* @bug		: No Bugs known.
**/
struct SubresourceData {
	const void * psysMem = nullptr;
	unsigned int sysMemPitch = 0;
	unsigned int sysMemSlicePitch = 0;
};

/**
* @brief	: Descriptor for Buffers.
* @bug		: No Bugs known.
**/
struct BufferDesc {
	unsigned int byteWidth = 0;
	unsigned short usage = 0;
	unsigned int bindFlags = 0;
	unsigned int cpuAccessFlags = 0;
	unsigned int miscFlags = 0;
	unsigned int structureByteStride = 0;
	SubresourceData SRD;
};


/**
* @brief	: Buffer class.
* @bug		: No Bugs known.
**/
class CBuffer {
public:
	
	/**
	* @brief	: Descriptor for Buffers.
	* @bug		: No Bugs known.
	**/
	CBuffer();

	/**
	* @brief	: Destructor of the class.
	* @bug		: No Bugs known.
	**/
	~CBuffer();
	
	/**
	* @brief	: Descriptor for Buffers.
	* param		: A descriptor for the buffer. Temp D3D11DeviceContext
	* @bug		: No Bugs known.
	**/
	HRESULT setDesc(BufferDesc inDesc);
	
	/**
	* @brief	: Delete the Buffers.
	* param		: .
	* @bug		: No Bugs known.
	**/
	void destroy();

#if (defined D_DirectX || defined R_DirectX) 
	//D3D11_BUFFER_DESC getDxDesc();
	
	//D3D11_SUBRESOURCE_DATA getDxSRD();

	ID3D11Buffer * getBuffer();
	/**
	* @brief	: Update the resource for Buffers.
	* param		: .
	* @bug		: No Bugs known.
	**/
	//HRESULT update(void * inData, ID3D11DeviceContext *inDC);
	
	/**
	* @brief	: Sets the Buffers.
	* param		: .
	* @bug		: No Bugs known.
	**/
	//HRESULT render(int inStartSlot, unsigned int inSize, int inFormat, bool inSetBoth, ID3D11DeviceContext *inDC);
	

	

//private:

	//D3D11_BUFFER_DESC m_DxDesc;
	//D3D11_SUBRESOURCE_DATA  m_SRD;
	ID3D11Buffer * m_Buffer;
#endif
	BufferDesc m_Desc;
};
