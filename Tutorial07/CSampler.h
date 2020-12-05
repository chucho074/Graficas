#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "resource.h"
#include "Defines.h"


struct SamplerDesc {
	unsigned int filter;
	unsigned int addressU;
	unsigned int addressV;
	unsigned int addressW;
	unsigned int comparisonFunc;
	float minLOD;
	float maxLOD;
};


class CSampler {
public:
	CSampler();
	~CSampler();
	void init(SamplerDesc inDesc);


	ID3D11SamplerState * m_Sampler;
	D3D11_SAMPLER_DESC m_Desc;
private:

protected:


};

