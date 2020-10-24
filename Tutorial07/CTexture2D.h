#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"

struct TextureDesc {
	unsigned int W;
	unsigned int H;
	unsigned int mipLevels;
	unsigned int arraySize;
	unsigned int format;
	unsigned int sampleDescCount;
	unsigned int sampleDescQuality;
	unsigned int usage;
	unsigned int flags;
	unsigned int cpuAccessFlags;
	unsigned int miscFlags;
};

class CTexture2D {
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs known.
	**/
	CTexture2D();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CTexture2D();	

	/**
	* @brief	: Object for direct management of the texture.
	* @bug		: No Bugs known.
	**/
	ID3D11ShaderResourceView* getSRV() { return m_SRV; }
protected:
	friend class CGraphicsAPI;

	ID3D11Texture2D * m_Texture = nullptr;
	TextureDesc m_TexDesc;							//no debe de existir
	ID3D11ShaderResourceView * m_SRV = nullptr;
	ID3D11DepthStencilView* m_DSV = nullptr;
	ID3D11RenderTargetView* m_RTV = nullptr;

private:
};

