#include "CDeviceContext.h"

CDeviceContext::CDeviceContext() {

}

CDeviceContext::~CDeviceContext() {
	if (m_DeviceContext) {
		m_DeviceContext->ClearState();
	}
	if (m_DeviceContext) {
		m_DeviceContext->Release();
		m_DeviceContext = nullptr;
	}
}

void CDeviceContext::setVBuffer(unsigned int inStartSlot, unsigned int inSize, CBuffer & inVBuffer) {
	unsigned int offset = 0;
	ID3D11Buffer * BufferTemp = inVBuffer.getBuffer();
	m_DeviceContext->IASetVertexBuffers(inStartSlot, 1, &BufferTemp, &inSize, &offset);
}
