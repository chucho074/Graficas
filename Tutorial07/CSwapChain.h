#pragma once
#if (defined D_DirectX || defined R_DirectX)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#endif
#include "Defines.h"
#include "CTexture2D.h"

class CSwapChain {
public:
	CSwapChain();
	~CSwapChain();
	/*
	* @brief	: Make the present.
	* @param	: CBuffer.
	* @bug		: No Bugs known.
	*/
	HRESULT getBBuffer(CTexture2D & inBBuffer);
	/*
	* @brief	: Make the present.
	* @bug		: No Bugs known.
	*/
	void render();
private:
	IDXGISwapChain * m_SwapChain;
};

