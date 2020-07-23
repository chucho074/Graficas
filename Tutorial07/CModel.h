#pragma once
#include <vector>
#include "CMesh.h"
#include "CTransform.h"

class CModel {
public:
	CModel();
	~CModel();
	void init();
	void update();
	void destroy();
	void render();

	void addMeshToList(CMesh inMesh);
	CMesh getMesh(unsigned int inID);
private:
	std::vector<CMesh*> m_MeshList;
	CTransform m_ModelSpace;
};

