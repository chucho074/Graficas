/**
* @LC		: 06/07/2020
* @file		: CVertexShader.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 05/07/2020
* @brief	: A class for the abstraction of the Vertex Shader.
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

/**
* @brief	: Class for Vertex Shader abstraction.
* @bug		: No Bugs known.
**/
class CVertexShader {
public:
	CVertexShader();
	~CVertexShader();
	void * getBlob();
	void * getVS();
private:
	ID3DBlob * m_Blob;
	ID3D11VertexShader * m_VertexShader;
};

