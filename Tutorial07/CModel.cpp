#include "CModel.h"

void CModel::loadModel(std::string inFileName) {
	CMesh * tmpMesh = new CMesh();
	tmpMesh->loadModel(inFileName);
	m_Meshes.push_back(tmpMesh);
}
