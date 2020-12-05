/**
* @file		CMesh.cpp
* @author	Jesús Alberto Del Moral Cupil
* @e	    idv18c.jmoral@uartesdigitales.edu.mx
* @date		28/11/2020
* @brief	This class have the funtionality for load models.
* @bug		No know Bugs.
**/

#pragma once
#include <string>
#include "CGraphicsAPI.h"

class CBuffer;


/**
* @class    CMesh.
* @brief    This class have the funtionality for load models.
* @bug      No know Bugs.
**/
class CMesh {
public:
	CMesh() = default;
	~CMesh();

	void loadModel(std::string inFileName);

	void drawModel();

	std::vector<std::string> getTextures() { return m_TexturesNames; }

	unsigned int getNumTextures() { return m_TexturesNames.size(); }

private:
	int m_IndexNum;
	
	CBuffer* m_IndexBuffer;

	int m_VertexNum;
	
	CBuffer* m_VertexBuffer;

	//Obtener los nombres de las texturas a cargar por el modelo
	std::vector<std::string> m_TexturesNames;

};

