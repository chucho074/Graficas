/**
* @LC		: 24/02/2020
* @file		: CBuffer.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A base class for Buffers.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#include "CBuffer.h"

CBuffer::CBuffer() {
#ifdef D_DIRECTX
	Buffer = NULL;
#endif
}

void CBuffer::init(BufferDesc inDesc) {
	Desc = inDesc;
#ifdef D_DIRECTX
	ZeroMemory(&m_bd, sizeof(m_bd));
	m_bd.Usage = (D3D11_USAGE)Desc.usage;
	m_bd.ByteWidth = Desc.byteWidth;
	m_bd.BindFlags = Desc.bindFlags;
	m_bd.CPUAccessFlags = Desc.cpuAccessFlags;
#endif
}

void CBuffer::init(SubresourceData inSD, BufferDesc inDesc) {
	Desc = inDesc;
#ifdef D_DIRECTX
	ZeroMemory(&m_bd, sizeof(m_bd));
	m_bd.Usage = (D3D11_USAGE)Desc.usage;
	m_bd.ByteWidth = Desc.byteWidth;
	m_bd.BindFlags = Desc.bindFlags;
	m_bd.CPUAccessFlags = Desc.cpuAccessFlags;
	ZeroMemory(&m_Data, sizeof(m_Data));
	m_Data.pSysMem = inSD.psysMem;
#endif
}

void * CBuffer::getBuffer() {
#ifdef D_DIRECTX
	return Buffer;
#else
	return nullptr;
#endif	
}

void CBuffer::clear() {
	Buffer->Release();
}

void CBuffer::xfunc(int inNum, void * inPtr, D3D11_CLEAR_FLAG inFlag) {

}



#ifdef D_DIRECTX
void CBuffer::createVertexBuffer(int numVertex, const aiScene * model, SimpleVertex * vertex, ID3D11Buffer *& buffer, ID3D11Device * Dev) {

	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * numVertex;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = vertex;
	HRESULT hr = Dev->CreateBuffer(&bd, &data, &buffer);
	if (FAILED(hr)) {
		return;
	}


}

void CBuffer::createIndexBuffer(int numIndex, const aiScene * model, WORD * index, ID3D11Buffer *& buffer, ID3D11Device * Dev) {
	
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * numIndex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = index;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;
	HRESULT hr = Dev->CreateBuffer(&bd, &data, &buffer);
	if (FAILED(hr)) {
		return;
	}
}
#endif