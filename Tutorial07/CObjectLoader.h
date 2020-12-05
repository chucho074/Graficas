/**
* @file		CObjectLoader.h
* @author	Jesús Alberto Del Moral Cupil
* @e	    idv18c.jmoral@uartesdigitales.edu.mx
* @date		11/11/2020
* @brief	This class read info from a .obj file.
* @bug		No know Bugs.
**/
#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdio.h>

#include <DirectXMath.h>

using namespace DirectX;

struct SimpleVertex {
	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
	XMFLOAT3 Nor;
};



/**
* @class    CObjectLoader.
* @brief    This class read info from a .obj file.
* @bug      No know Bugs.
**/
class CObjectLoader {
public:
	CObjectLoader();
	~CObjectLoader();

	bool loadObject(std::string inFileName);

	std::vector<std::vector<float>> & getVertex() { return m_VertexList; }
	std::vector<std::vector<float>> & getTextureCoords() { return m_TextureCoordsList; }
	std::vector<std::vector<float>> & getVertexNormal() { return m_VertexNormalList; }
	std::vector<std::vector<unsigned short>> & getFaces() { return m_FacesList; }

	int getNumVertex() { return m_VertexList.size(); }
	int getNumUV() { return m_TextureCoordsList.size(); }
	int getNumNormals() { return m_VertexNormalList.size(); }
	int getNumFaces() { return m_FacesList.size(); }

	std::vector<std::string> & getTextureName() { return m_TextureFiles; }

	std::vector<SimpleVertex> getVertBuffer() { return m_VertexBuffer; }
private:
	bool readLineObj(std::string inLine);
	bool readLineMtl(std::string inLine);

	

	std::vector<std::string> m_TextureFiles;
	std::string m_MTLFile = " ";

	std::vector<std::vector<float>> m_VertexList;
	std::vector<std::vector<float>> m_TextureCoordsList;
	std::vector<std::vector<float>> m_VertexNormalList;
	std::vector<std::vector<unsigned short>> m_FacesList;
	std::vector<SimpleVertex> m_VertexBuffer;

};


