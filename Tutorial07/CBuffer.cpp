/**
* @LC		: 29/06/2020
* @file		: CBuffer.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 20/06/2020
* @brief	: A class for Buffers.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CBuffer.h"


CBuffer::CBuffer() {
#if (defined D_DirectX || defined R_DirectX) 
	m_Buffer = nullptr;
#endif
}


HRESULT CBuffer::setDesc(BufferDesc inDesc) {
	m_Desc = inDesc;
	// Clean memory and asign data for the Description	//Pasarlo a GAPI
#if (defined D_DirectX || defined R_DirectX) 
	ZeroMemory(&m_DxDesc, sizeof(m_DxDesc));
	m_DxDesc.Usage = (D3D11_USAGE)m_Desc.usage;
	m_DxDesc.ByteWidth = m_Desc.byteWidth;
	m_DxDesc.BindFlags = m_Desc.bindFlags;
	m_DxDesc.CPUAccessFlags = m_Desc.cpuAccessFlags;
	// Case if use a SRD
	if (inDesc.SRD.psysMem != nullptr) {
		// Clean memory and asign data for the SRD
		ZeroMemory(&m_SRD, sizeof(m_SRD));
		m_SRD.pSysMem = m_Desc.SRD.psysMem;		
	} 	
#endif
	return false;
}


/*HRESULT CBuffer::update(void * inData, ID3D11DeviceContext *inDC) {
	// Compare the size of the Buffer and the input data
	if (sizeof(m_Desc.SRD.psysMem) == sizeof(inData)) {
		//Funcion de update subresource data 
		inDC->UpdateSubresource(m_Buffer, 0, NULL, &inData, 0, 0);
		return S_OK;
	}
	else {
		return false;
	}
}


HRESULT CBuffer::render(int inStartSlot, unsigned int inSize, int inFormat, bool inSetBoth, ID3D11DeviceContext *inDC) {
	switch (m_Desc.bindFlags) {
	// If is a Vertex Buffer
	case 1: {
		unsigned int offset = 0;
		inDC->IASetVertexBuffers(inStartSlot, 1, &m_Buffer, &inSize, &offset);
		break;
	}
	// If is a Index Buffer
	case 2: {
		inDC->IASetIndexBuffer(m_Buffer, (DXGI_FORMAT)inFormat, 0);
		break;
	}
	// If is a Constant Buffer
	case 0x4L: {

		inDC->VSSetConstantBuffers(inStartSlot, 1, &m_Buffer);
		if (inSetBoth) {
			inDC->PSSetConstantBuffers(inStartSlot, 1, &m_Buffer);
		}
		break;
	}
	default: {
		return false;
		break;
	}
	}
	
	return S_OK;
} */

void CBuffer::destroy() {
#if (defined D_DirectX || defined R_DirectX) 
	if (m_Buffer) { 
		m_Buffer->Release(); 
		m_Buffer = nullptr;
	}
#endif
}

#if (defined D_DirectX || defined R_DirectX) 
D3D11_BUFFER_DESC CBuffer::getDxDesc() {
	return  m_DxDesc;
}

D3D11_SUBRESOURCE_DATA CBuffer::getDxSRD() {
	return m_SRD;
}

ID3D11Buffer * CBuffer::getBuffer() {
	return m_Buffer;
}
#endif

CBuffer::~CBuffer() {
	destroy();
}