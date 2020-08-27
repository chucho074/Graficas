#pragma once
#include "CShader.h"
class CPixelShader : public CShader {
public:
	CPixelShader();
	~CPixelShader();
	void init(
		WCHAR* inFileName,
		LPCSTR inEntryPoint,
		LPCSTR inShaderModel) override;


	ID3D11PixelShader * m_PS;
	ID3DBlob * m_CompiledPShader;

};

