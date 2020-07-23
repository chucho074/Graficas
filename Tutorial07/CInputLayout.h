/**
* @LC		: 06/07/2020
* @file		: CInputLayout.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 06/07/2020
* @brief	: A class for the abstraction of the Input Layout.
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

class CInputLayout {
public:
	CInputLayout();
	~CInputLayout();
	void * getIL();
private:
	ID3D11InputLayout * m_IL;

};

