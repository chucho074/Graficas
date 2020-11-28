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
	//Mandar referencias del vector
	std::vector<std::vector<float>> & getVertex() { return m_VertexList; }
	std::vector<std::vector<float>> & getTextureCoords() { return m_TextureCoordsList; }
	std::vector<std::vector<float>> & getVertexNormal() { return m_VertexNormalList; }
	std::vector<std::vector<unsigned short>> & getFaces() { return m_FacesList; }

	int getNumVertex() { return m_VertexList.size(); }
	int getNumUV() { return m_TextureCoordsList.size(); }
	int getNumNormals() { return m_VertexNormalList.size(); }
	int getNumFaces() { return m_FacesList.size(); }

	std::string getTextureName() { return m_TextureFile; }

private:
	bool readLineObj(std::string inLine);

	

	std::string m_TextureFile;

	std::vector<std::vector<float>> m_VertexList;
	std::vector<std::vector<float>> m_TextureCoordsList;
	std::vector<std::vector<float>> m_VertexNormalList;
	std::vector<std::vector<unsigned short>> m_FacesList;

};


