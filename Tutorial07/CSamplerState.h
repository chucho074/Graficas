#pragma once
#if (defined D_DirectX || defined R_DirectX)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#endif
#include "Defines.h"

class CSamplerState {
public:
	CSamplerState();
	~CSamplerState();
	void setDesc(SamplerDesc inDesc);
	void * getSampler();
private:
	SamplerDesc m_Desc;
	ID3D11SamplerState * m_Sampler;
};

