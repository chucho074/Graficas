/**
* @file		CMesh.cpp
* @author	Jesús Alberto Del Moral Cupil
* @e	    idv18c.jmoral@uartesdigitales.edu.mx
* @date		28/11/2020
* @brief	This class have the funtionality for load models.
* @bug		No know Bugs.
**/

#include "CMesh.h"
#include "CObjectLoader.h"


CMesh::~CMesh() {

}


void CMesh::loadModel(std::string inFileName) {

	auto& GAPI = g_GraphicsAPI();

	CObjectLoader tmpObjectLoader;
	tmpObjectLoader.loadObject(inFileName);

	std::vector<SimpleVertex> tmpVertList;
	auto numVertex = tmpObjectLoader.getNumVertex();
	tmpVertList.reserve(numVertex);

	for (int i = 0; i<numVertex; ++i) {
		tmpVertList.emplace_back();
		SimpleVertex& tmpVertex = tmpVertList.back();
		auto& objVertex = tmpObjectLoader.getVertex()[i];
		auto& texCoord = tmpObjectLoader.getTextureCoords()[i];
		auto& normals = tmpObjectLoader.getVertexNormal()[i];

		tmpVertex.Pos = XMFLOAT3(objVertex[0],
								 objVertex[1],
								 objVertex[2]);

		tmpVertex.Tex = XMFLOAT2(texCoord[0],
								 texCoord[1]);

		tmpVertex.Nor = XMFLOAT3(normals[0],
								 normals[1],
								 normals[2]);
	}

	m_VertexBuffer = GAPI.createBuffer(sizeof(SimpleVertex) * tmpVertList.size(),
									   0x1L, 
									   0,
									   tmpVertList.data());


	auto& faces = tmpObjectLoader.getFaces();
	auto numIndices = faces.size() * 3;
	std::vector<unsigned short> tmpIndices;
	tmpIndices.reserve(numIndices);

	for(auto& face : faces) {
	  tmpIndices.push_back(face[0]);
	  tmpIndices.push_back(face[3]);
	  tmpIndices.push_back(face[6]);
	}

	m_IndexBuffer = GAPI.createBuffer(sizeof(unsigned short) * tmpIndices.size(),
									  0x2L, 
									  0, 
									  tmpIndices.data());

	m_VertexNum = numVertex;
	m_IndexNum = numIndices;


}

void CMesh::drawModel() {

	auto& GAPI = g_GraphicsAPI();

	UINT stride = sizeof(SimpleVertex);

	//Set vertex buffer
	GAPI.setVertexBuffer(m_VertexBuffer, stride);

	//Set IB
	GAPI.setIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT);

	//Draw
	GAPI.draw(m_IndexNum, 0);
}


CGraphicsAPI& g_GraphicsAPI() {
	return CGraphicsAPI::getSingleton();
}
