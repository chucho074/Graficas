/**
* @LC		: 10/06/2020
* @file		: CInputLayout.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 4/06/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include "Defines.h"
#include "Includes.h"
#include "CVertexShader.h"
#include <vector>

	/**
	* @brief	: Abstraction for the Input Layout.
	* @bug		: No Bugs known.
	**/
class CInputLayout {
public:
	/**
	* @brief	: Sets values to something safe.
	* @bug		: No Bugs known.
	**/
	CInputLayout();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CInputLayout();

	/**
	* @brief	: Getter for the Input Layout.
	* @bug		: No Bugs known.
	**/
	void * getInputLayout();


#ifdef D_DIRECTX
	/**
	* @brief	: Input Layout for DirectX.
	* @bug		: No Bugs known.
	**/
	ID3D11InputLayout * m_InputLayout;
#endif
};
