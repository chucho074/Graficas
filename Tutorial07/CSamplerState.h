/**
* @LC		: 24/02/2020
* @file		: CSamplerState.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/02/2020
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
* @brief	: Description of the Sampler.
* @bug		: No Bugs known.
**/
struct SamplerDesc {
	FILTER filter;
	TEXTURE_ADDRESS_MODE addresU;
	TEXTURE_ADDRESS_MODE addresV;
	TEXTURE_ADDRESS_MODE addresW;
	float mipLODBias;
	unsigned int maxAnisotropy;
	COMPARISON_FUNC comparisonFunc;
	float borderColor[4];
	float minLOD;
	float maxLOD;
};

/**
* @brief	: Short description of function.
* @bug		: No Bugs known.
**/
class CSamplerState {
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs known.
	**/
	CSamplerState();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CSamplerState();

	/**
	* @brief	: Initializer.
	* @param	: SamplerDesc.
	* @bug		: No Bugs known.
	**/
	void init(SamplerDesc inDesc);

	/**
	* @brief	: Getter the Sampler.
	* @bug		: No Bugs known.
	**/
	void * getSampler();

#ifdef D_DIRECTX
	ID3D11SamplerState * m_pSamplerLinear;
	D3D11_SAMPLER_DESC m_Desc;
#endif
};