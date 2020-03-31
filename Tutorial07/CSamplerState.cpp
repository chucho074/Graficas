/**
* @LC		: 24/02/2020
* @file		: CSamplerState.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#include "CSamplerState.h"

CSamplerState::CSamplerState() {
#ifdef D_DIRECTX
	m_pSamplerLinear = NULL;
#endif
}

CSamplerState::~CSamplerState() {

}

void CSamplerState::init(SamplerDesc inDesc) {
#ifdef D_DIRECTX
	ZeroMemory(&m_Desc, sizeof(m_Desc));
	m_Desc.Filter = (D3D11_FILTER)inDesc.filter;
	m_Desc.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)inDesc.addresU;
	m_Desc.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)inDesc.addresV;
	m_Desc.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)inDesc.addresW;
	m_Desc.ComparisonFunc = (D3D11_COMPARISON_FUNC)inDesc.comparisonFunc;
	m_Desc.MinLOD = inDesc.minLOD;
	m_Desc.MaxLOD = inDesc.maxLOD;
#endif
}

void * CSamplerState::getSampler() {
#ifdef D_DIRECTX
	return m_pSamplerLinear;
#else
	return nullptr;
#endif
}
