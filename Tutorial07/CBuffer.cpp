#include "CBuffer.h"

CBuffer::CBuffer() {
	m_Buffer = nullptr;
	m_BufferData = nullptr;
	memset(&m_Desc, 0, sizeof(m_Desc));
}

CBuffer::~CBuffer() {
	SAFE_RELEASE(m_Buffer);
}

void CBuffer::init(BufferDesc inDesc) {
	m_Desc.Usage = (D3D11_USAGE)inDesc.usage;
	m_Desc.ByteWidth = inDesc.byteWidth;
	m_Desc.BindFlags = inDesc.bindFlags;
	m_Desc.CPUAccessFlags = inDesc.CPUAccessFlags;

	if (inDesc.SRD != nullptr) {
		m_SRD.pSysMem = inDesc.SRD;
		m_StartSlot = inDesc.startSlot;
		m_NumBuffer = inDesc.numBuffers;
		m_Stride = inDesc.stride;
		m_Offset = inDesc.offset;
	}
	else {
		m_BufferData = inDesc.SRD;
	}
}


