#include "CPixelShader.h"

CPixelShader::CPixelShader() {
	m_PS = nullptr;
	m_CompiledPShader = nullptr;
}

CPixelShader::~CPixelShader()
{
}

void CPixelShader::init(WCHAR* inFileName,
						 LPCSTR inEntryPoint,
						 LPCSTR inShaderModel) {

	CompileShaderFromFile(inFileName, inEntryPoint, inShaderModel, &m_CompiledPShader);
}