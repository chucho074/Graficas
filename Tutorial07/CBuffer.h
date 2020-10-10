#pragma once
#include "Defines.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"

struct BufferDesc {
	unsigned int byteWidth = 0;
	unsigned short usage = 0;
	unsigned int bindFlags = 0;
	unsigned int startSlot = 0;
	unsigned int numBuffers = 0;
	unsigned int CPUAccessFlags = 0;
	unsigned int stride = 0;
	unsigned int offset = 0;
	void * SRD = nullptr;
	unsigned int memPitch = 0;
	unsigned int memSlicePitch = 0;
};

class CBuffer {
public:
	CBuffer();
	~CBuffer();
	void init(BufferDesc inDesc);

	
	ID3D11Buffer * m_Buffer;
	//No deberian existir aqui / 
	D3D11_BUFFER_DESC m_Desc;
	D3D11_SUBRESOURCE_DATA m_SRD;
private:
	unsigned int m_StartSlot;
	unsigned int m_NumBuffer;
	unsigned int m_Stride;
	unsigned int m_Offset;

};

