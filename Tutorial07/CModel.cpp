#include "CModel.h"

CModel::CModel() {

}

CModel::~CModel() {
	destroy();
}

void CModel::init() {
	
}

void CModel::update() {

	for (int i = 0; i < m_MeshList.size(); i++) {
		m_ModelSpace.getMatrix();
	
	}
}

void CModel::destroy() {
	
}

void CModel::render() {
	update();
}

void CModel::addMeshToList(CMesh inMesh) {
	m_MeshList.push_back(&inMesh);
}

CMesh CModel::getMesh(unsigned int inID) {
	return *m_MeshList[inID];
}
