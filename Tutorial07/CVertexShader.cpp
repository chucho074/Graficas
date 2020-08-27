#include "CVertexShader.h"

CVertexShader::CVertexShader() {
	m_VS = nullptr;
	m_CompiledVShader = nullptr;
}

CVertexShader::~CVertexShader()
{
}

void CVertexShader::init(WCHAR* inFileName,
						 LPCSTR inEntryPoint,
						 LPCSTR inShaderModel) {

	CompileShaderFromFile(inFileName, inEntryPoint, inShaderModel, &m_CompiledVShader);
}


