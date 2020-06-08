/**
* @LC		: 08/06/2020
* @file		: CDeviceContext.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include "Defines.h"
#include "Includes.h"
#include "CViewport.h"
#include "CVertexShader.h"

/**
* @brief	: Abstraction for DeviceContext.
* @bug		: No Bugs known.
**/
class CDeviceContext {
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs known.
	**/
	CDeviceContext();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CDeviceContext();

	/**
	* @brief	: Getter for the Device Context.
	* @bug		: No Bugs known.
	**/
	void * getDeviceContext();

	/**
	* @brief	: Sets the VPorts to the DeviceContext.
	* @param	: CViewPort.
	* @bug		: No Bugs known.
	**/
	void setViewport(CViewPort inVP);

	/**
	* @brief	: Sets the ILayout in the DeviceCotext.
	* @param	: CVertexShader.
	* @bug		: No Bugs known.
	**/
	void setILayout(CVertexShader & inVS);



	void operator = (CDeviceContext const&) = delete;

#ifdef D_DIRECTX
	ID3D11DeviceContext * m_DeviceContext;
#endif
};