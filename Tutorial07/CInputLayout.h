#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "resource.h"
#include "Defines.h"
#include <string>
#include <vector>

struct InputLayoutDesc {
	std::string semanticName;
	unsigned int semanticIndex;
	unsigned int format;
	unsigned int inputSlot;
	unsigned int alignedByteOffset;
	unsigned int inputSlotClass;
	unsigned int instanceDataStepRate;
};

class CInputLayout {
public:
	CInputLayout();
	~CInputLayout();
	void init(const std::vector<InputLayoutDesc> & inDesc);

protected:
	friend class CGraphicsAPI;

	ID3D11InputLayout * m_InputLayout;
	std::vector<D3D11_INPUT_ELEMENT_DESC> m_Descriptors;

private:

};

