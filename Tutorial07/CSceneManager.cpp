/**
* @LC		: 30/03/2020
* @file		: CSceneManager.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/03/2020
* @brief	:.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CSceneManager.h"

#ifdef D_DIRECTX
CSceneManager::CSceneManager() {

}

CSceneManager::~CSceneManager() {

}

void CSceneManager::addMesh(CMesh * inMesh) {
	inMesh->setSceneID(m_ID);
	m_ID++;
	m_MeshList.push_back(inMesh);
}

CMesh *& CSceneManager::getMesh(int ID) {
	for (int i = 0; i < m_MeshList.size(); i++) {
		if (m_MeshList[i]->getIndexNum() == ID) {
			return m_MeshList[i];
		}
	}
}

void CSceneManager::update() {
	for (int i = 0; i < m_MeshList.size(); i++) {
		m_MeshList[i]->update();
	}
}

void CSceneManager::render(CDeviceContext * inDC, CBuffer * inBuffer, CDevice * inDevice ){
	for (int i = 0; i < m_MeshList.size(); i++) {
		m_MeshList[i]->render(inDC, inBuffer, inDevice);
	}
}

void CSceneManager::shutdown() {
	for (int i = 0; i < m_MeshList.size(); i++) {
		m_MeshList[i]->Delete();
	}
}
#endif