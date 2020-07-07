#include "CSamplerState.h"

CSamplerState::CSamplerState() {
	m_Sampler = NULL;
}

CSamplerState::~CSamplerState() {
	if(m_Sampler) {
		m_Sampler->Release();
		m_Sampler = nullptr;
	}
}

void CSamplerState::setDesc(SamplerDesc inDesc) {
	m_Desc = inDesc;
}

void * CSamplerState::getSampler() {
	return m_Sampler;
}

