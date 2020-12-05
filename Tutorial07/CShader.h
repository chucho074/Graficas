#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "resource.h"


class CShader {
public:
	CShader() = default;
	~CShader() = default;

	virtual void init(
		WCHAR* inFileName,
		LPCSTR inEntryPoint,
		LPCSTR inShaderModel) {};

	bool CompileShaderFromFile(WCHAR* szFileName,
							   LPCSTR szEntryPoint,
							   LPCSTR szShaderModel,
							   ID3DBlob** ppBlobOut);

};

