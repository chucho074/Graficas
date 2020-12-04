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

struct SimpleVertex {
	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
	XMFLOAT3 Nor;
};

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

	std::string getTexture() { return m_TextureName; }

private:
	int m_IndexNum;
	
	CBuffer* m_IndexBuffer;

	int m_VertexNum;
	
	CBuffer* m_VertexBuffer;

	//Obtener los nombres de las texturas a cargar por el modelo
	std::string m_TextureName;

};

