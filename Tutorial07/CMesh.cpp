/**
* @LC		: 30/03/2020
* @file		: CMesh.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/03/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CMesh.h"

#ifdef D_DIRECTX
CMesh::CMesh() {
	VB = nullptr;
	IB = nullptr;
	SVertex = nullptr;
	Index = nullptr;
	VNum = 0;
	INum = 0;
	SceneID = -1;

	VB = new CBuffer();
	IB = new CBuffer();
	Materials = new CMaterial();
	MeshData.mWorld = {
		1, 0, 0, .010,
		0, 1, 0, .010,
		0, 0, 1, .010,
		0, 0, 0, 1
	};
	MeshData.vMeshColor = { 1, 0, 0, 1 };
}

CMesh::~CMesh() {

}

void CMesh::init() {
	VB = new CBuffer();
	IB = new CBuffer();
}

void CMesh::update() {
}

void CMesh::render(CDeviceContext * DC, CBuffer * bufferData, CDevice * D) {
	MeshData.mWorld = {
		1, 0, 0, .010,
		0, 1, 0, .010,
		0, 0, 1, .010,
		0, 0, 0, 1
	};
	MeshData.vMeshColor = { 1, 0, 0, 1 };
#ifdef D_DIRECTX
	DC->m_DeviceContext->PSSetShaderResources(0, 1, &Materials->m_TextureDiffuse);
	DC->m_DeviceContext->VSSetShaderResources(0, 1, &Materials->m_TextureDiffuse);
#endif


	string title;
	string title2;

	std::stringstream ss;

	ss << "mesh ";
	ss << SceneID;
	ss >> title;
	ss >> title2;

	title += " ";
	title += title2;

	unsigned int stride = sizeof(SimpleVertex);
	unsigned int offset = 0;

#ifdef D_DIRECTX
	DC->m_DeviceContext->IASetVertexBuffers(0, 1, &VB->Buffer, &stride, &offset);
	DC->m_DeviceContext->IASetIndexBuffer(IB->Buffer, (DXGI_FORMAT)FORMAT_R16_UINT, 0);

	DC->m_DeviceContext->DrawIndexed(INum, 0, 0);
#endif
}

void CMesh::Delete() {
	Materials->shutdown();
	if (VB != nullptr) {
		delete VB;
		VB = nullptr;
	}
	if (IB != nullptr) {
		delete IB;
		IB = nullptr;
	}
	if (SVertex != nullptr) {
		delete SVertex;
		SVertex = nullptr;
	}
	if (Index != nullptr) {
		delete Index;
		Index = nullptr;
	}
}

void CMesh::addChildren(CMesh * M) {
	Children.push_back(M);
}

void CMesh::setParent(CMesh * P) {
	Parent = P;
}

void CMesh::setVertex(SimpleVertex * V, int num) {
	VNum = num;
	SVertex = V;
}

void CMesh::setIndexList(WORD * I, int num) {
	INum = num;
	Index = I;
}

WORD *& CMesh::getIndexList(SimpleVertex * V, int num) {
	return Index;
}

SimpleVertex * CMesh::getVertex() {
	return SVertex;
}

int CMesh::getVertexNum() {
	return VNum;
}

int CMesh::getIndexNum() {
	return INum;
}

CBuffer *& CMesh::getVB() {
	return VB;
}

CBuffer *& CMesh::getIB() {
	return IB;
}

void CMesh::setVB(CBuffer * pVB) {
	VB = pVB;
}

void CMesh::setIB(CBuffer * pIB) {
	IB = pIB;
}

void CMesh::setSceneID(int ID) {
	SceneID = ID;
}

int CMesh::getSceneID() {
	return SceneID;
}

#elif OPENGL
CMesh::CMesh(std::vector<Vertex> v, std::vector<unsigned int> i, std::vector<Texture> t) {
	this->vertex = v;
	this->index = i;
	this->tex = t;
	setupMesh();
}

void CMesh::Draw(int shaderID)
{
	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < tex.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = tex[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++); // transfer unsigned int to stream
		else if (name == "texture_normal")
			number = std::to_string(normalNr++); // transfer unsigned int to stream
		else if (name == "texture_height")
			number = std::to_string(heightNr++); // transfer unsigned int to stream

		// now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shaderID, (name + number).c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, tex[i].id);
	}

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}
void CMesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), &index[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);
}
#endif