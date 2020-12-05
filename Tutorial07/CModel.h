#pragma once
#include <vector>
#include "CMesh.h"

class CModel {
public:
	CModel();
	~CModel();

	void loadModel(std::string inFileName);
private:
	std::vector<CMesh*> m_Meshes;
};

