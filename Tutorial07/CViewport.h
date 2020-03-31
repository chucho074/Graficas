/**
* @LC		: 24/02/2020
* @file		: CViewPort.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 18/02/2020
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
* @brief	: Description for a ViewPort.
* @bug		: No Bugs known.
**/
struct ViewPortDesc {
	float topLeftX;
	float topLeftY;
	float W;
	float H;
	float minDepth;
	float maxDepth;
};

/**
* @brief	: Class for ViewPort abstraction.
* @bug		: No Bugs known.
**/
class CViewPort {
public:

	/**
	* @brief	: Constructor of the class.
	* @bug		: No Bugs known.
	**/
	CViewPort();
	
	/**
	* @brief	: Destructor of the class.
	* @bug		: No Bugs known.
	**/
	~CViewPort();

	/**
	* @brief	: Init of the class.
	* @param	: ViewPortDesc.
	* @bug		: No Bugs known.
	**/
	void init(ViewPortDesc inDesc);

#ifdef D_DIRECTX
	D3D11_VIEWPORT m_Viewport;
#endif 
};