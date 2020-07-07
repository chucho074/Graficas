#include "CPixelShader.h"

CPixelShader::CPixelShader() {
	m_Blob = NULL;
	m_PixelShader = NULL;
}

CPixelShader::~CPixelShader() {
	if (m_Blob) {
		m_Blob->Release();
		m_Blob = nullptr;
	}
	if (m_PixelShader) {
		m_PixelShader->Release();
		m_PixelShader = nullptr;
	}
}

void * CPixelShader::getBlob() {
	return m_Blob;
}

void * CPixelShader::getPS() {
	return m_PixelShader;
}
