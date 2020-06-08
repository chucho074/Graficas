/**
* @LC		: 08/06/2020
* @file		: CSwapChain.h
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
#include "CTexture2D.h"

/**
* @brief	: SwapChain Descriptor.
* @bug		: No Bugs known.
**/
struct SwapChainDesc {
	unsigned int bufferCount;
	unsigned int W;
	unsigned int H;
	FORMAT format;
	unsigned int refreshNumerator;
	unsigned int refreshDenominator;
	unsigned int bufferUsage;
	unsigned int outputWND;
	unsigned int count;
	unsigned int quality;
	bool windowed;
};

/**
* @brief	: SwapChain Class.
* @bug		: No Bugs known.
**/
class CSwapChain {
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs known.
	**/
	CSwapChain();
	
	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CSwapChain();

	/**
	* @brief	: Initializer.
	* @param	: SwapChainDesc.
	* @bug		: No Bugs known.
	**/
	void init(SwapChainDesc s);

	/**
	* @brief	: Getter for the SC.
	* @bug		: No Bugs known.
	**/
	void * getSwapChain();

	/**
	* @brief	: Getter for BackBuffer.
	* @param	: CTexture2D.
	* @bug		: No Bugs known.
	**/
	HRESULT getBuffer(CTexture2D & inTexture);


	void operator = (CSwapChain const&) = delete;


#ifdef D_DIRECTX
	IDXGISwapChain * m_SwapChain;
	DXGI_SWAP_CHAIN_DESC m_SCDesc;
#endif
};