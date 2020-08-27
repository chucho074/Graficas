#pragma once
#include "CShader.h"
class CVertexShader : public CShader {
public:
	CVertexShader();
	~CVertexShader();
	void init(
		WCHAR* inFileName,
		LPCSTR inEntryPoint,
		LPCSTR inShaderModel) override;


	ID3D11VertexShader * m_VS;
	ID3DBlob * m_CompiledVShader;

};

