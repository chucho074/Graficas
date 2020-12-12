#include "CModel.h"

CModel::CModel()
{
}


CModel::~CModel()
{
}


void CModel::loadModel(std::string inFileName) {

	auto& GAPI = g_GraphicsAPI();

	CObjectLoader tmpObjectLoader;
	tmpObjectLoader.loadObject(inFileName);

	//Texture name
	m_TexturesNames = tmpObjectLoader.getTextureName();


	auto numVertex = tmpObjectLoader.getNumVertex();
	auto& faces = tmpObjectLoader.getFaces();
	auto numIndices = faces.size() * 3;


	m_Meshes = tmpObjectLoader.getMapMesh();

	//Load every mesh into the map
	for (auto iter : m_Meshes) {
		iter.second->loadMesh();
	}


	m_VertexNum = numVertex;
	m_IndexNum = numIndices;


}


void CModel::drawModel() {

	auto& GAPI = g_GraphicsAPI();

	//Draw every mesh into the map
	for (auto iter : m_Meshes) {
		iter.second->drawMesh();
	}
}


CGraphicsAPI& g_GraphicsAPI() {
	return CGraphicsAPI::getSingleton();
}