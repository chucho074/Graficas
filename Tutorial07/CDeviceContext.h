/**
* @LC		: 24/02/2020
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
	* @brief	: Getter forthe Device Context.
	* @bug		: No Bugs known.
	**/
	void * getDeviceContext();

	/**
	* @brief	: Getter for the instance.
	* @bug		: No Bugs known.
	**/
	//static CDeviceContext * getInstance();

	void operator = (CDeviceContext const&) = delete;

#ifdef D_DIRECTX
	ID3D11DeviceContext * m_DeviceContext;
#endif

private:
	//static CDeviceContext * m_DCInstance;
};