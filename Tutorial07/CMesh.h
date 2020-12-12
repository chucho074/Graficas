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
#include <map>
#include "CGraphicsAPI.h"

class CBuffer;
class CObjectLoader;
struct SimpleVertex;

/**
* @class    CMesh.
* @brief    This class have the funtionality for load models.
* @bug      No know Bugs.
**/
class CMesh {
public:
	CMesh() = default;
	~CMesh();

	void loadMesh();

	void drawMesh();


protected:

	CBuffer* m_VertexBuffer;

	std::vector<SimpleVertex> m_VertexVector;

	//std::vector<unsigned int> m_IndexBuffer;

	CBuffer* m_IndexBuffer;

	std::vector<std::vector<unsigned short>> m_FacesList;

	int m_IndexNum = 0;

private:	
	friend class CObjectLoader;
};

