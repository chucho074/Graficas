#include "CVertexShader.h"

CVertexShader::CVertexShader() {
	m_Blob = NULL;
	m_VertexShader = NULL;
}

CVertexShader::~CVertexShader() {
	if (m_Blob) {
		m_Blob->Release();
		m_Blob = nullptr;
	}
	if (m_VertexShader) {
		m_VertexShader->Release();
		m_VertexShader = nullptr;
	}
}

void * CVertexShader::getBlob() {
	return m_Blob;
}

void * CVertexShader::getVS() {
	return m_VertexShader;
}
