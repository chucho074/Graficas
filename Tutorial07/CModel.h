#pragma once
#include <vector>
#include <string>
#include <map>
#include "CMesh.h"
#include "CObjectLoader.h"
#include "CGraphicsAPI.h"

class CModel {
public:
	CModel();
	~CModel();

	void loadModel(std::string inFileName);

	void drawModel();
	

	int getNumTextures() { return m_TexturesNames.size(); }

	std::vector<std::string> getTextures() { return m_TexturesNames; }
private:
	int m_IndexNum;

	CBuffer* m_IndexBuffer;

	int m_VertexNum;

	CBuffer* m_VertexBuffer;

	//Obtener los nombres de las texturas a cargar por el modelo
	std::vector<std::string> m_TexturesNames;

	std::map<std::string, CMesh*> m_Meshes;
};

