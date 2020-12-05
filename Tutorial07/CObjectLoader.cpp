/**
* @file		CObjectLoader.cpp
* @author	Jesús Alberto Del Moral Cupil
* @e	    idv18c.jmoral@uartesdigitales.edu.mx
* @date		11/11/2020
* @brief	This class read info from a .obj file.
* @bug		No know Bugs.
**/
#include "CObjectLoader.h"
#include <sstream>

CObjectLoader::CObjectLoader() {

}

CObjectLoader::~CObjectLoader() {

}

bool CObjectLoader::loadObject(std::string inFileName)	 {
	bool tmpIsReaded = true;
	int tmpLineIter = 0;
	std::ifstream FS;
	std::string tmpLine;
	FS.open(inFileName, std::ios::in);

	while (!FS.eof()) {
		std::getline(FS, tmpLine);
		tmpLineIter++;

		if (!readLineObj(tmpLine)) {
			tmpIsReaded = false;
			break;
		}

	}

	FS.close();

	if (" " != m_MTLFile) {
		FS.open(m_MTLFile, std::ios::in);
		while (!FS.eof()) {
			std::getline(FS, tmpLine);
			tmpLineIter++;

			if (!readLineMtl(tmpLine)) {
				tmpIsReaded = false;
				break;
			}

		}

		FS.close();
	}


	return tmpIsReaded;
}

bool CObjectLoader::readLineObj(std::string inLine) {

	//Comentary & spaces
	if ("#" == inLine.substr(0, 1)
		|| "o " == inLine.substr(0, 2)
		|| "g " == inLine.substr(0, 2)
		|| "usemtl " == inLine.substr(0, 7)
		|| "" == inLine.substr(0, 1)) {

		return true;
	}

	//Texture
	if ("mtllib " == inLine.substr(0, 7)) {
		std::stringstream tmpBuffer(inLine.substr(7));
		tmpBuffer >> m_MTLFile;
		return true;
	}

	//Vertex
	if ("v " == inLine.substr(0, 2)) {
		std::vector<float> tmpArrayData;
		float tmpData = 0;
		std::stringstream tmpBuffer(inLine.substr(2));

		unsigned short tmpIter = 0;
		while (tmpBuffer >> tmpData) {
			tmpArrayData.push_back(tmpData);
			if (2 == tmpIter) {
				m_VertexList.push_back(tmpArrayData);
				tmpIter = 0;
			}
			++tmpIter;
		}
		return true;
	}

	//Texture coords
	if ("vt " == inLine.substr(0, 3)) {
		std::vector<float> tmpArrayData;
		float tmpData;
		std::stringstream tmpBuffer(inLine.substr(3));

		unsigned short tmpIter = 0;
		while (tmpBuffer >> tmpData) {
			tmpArrayData.push_back(tmpData);
			if (1 == tmpIter) {
				m_TextureCoordsList.push_back(tmpArrayData);
				tmpIter = 0;
			}
			++tmpIter;
		}
		return true;
	}

	//Vertex Normals
	if ("vn " == inLine.substr(0, 3)) {
		std::vector<float> tmpArrayData;
		float tmpData;
		std::stringstream tmpBuffer(inLine.substr(3));

		unsigned short tmpIter = 0;
		while (tmpBuffer >> tmpData) {
			tmpArrayData.push_back(tmpData);
			if (2 == tmpIter) {
				m_VertexNormalList.push_back(tmpArrayData);
				tmpIter = 0;
			}
			++tmpIter;
		}
		return true;
	}

	//Faces
	
	std::vector<std::vector<float>> tmpTexCordsList = m_TextureCoordsList;
	if ("f " == inLine.substr(0, 2)) {
		std::vector<unsigned short> tmpArrayData;
		int tmpData;

		int a, b, c;
		int A1, B1, C1;
		int A2, B2, C2;
		const char* chh = inLine.c_str();
		sscanf_s(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i", 
			&a, &A1, &A2, &b, &B1, &B2, &c, &C1, &C2);

		tmpArrayData.push_back(a-1);
		tmpArrayData.push_back(A1-1);
		tmpArrayData.push_back(A2-1);
		tmpArrayData.push_back(b -1);
		tmpArrayData.push_back(B1-1);
		tmpArrayData.push_back(B2-1);
		tmpArrayData.push_back(c -1);
		tmpArrayData.push_back(C1-1);
		tmpArrayData.push_back(C2-1);
		m_FacesList.push_back(tmpArrayData);

		SimpleVertex tmpVertex;
		
		tmpVertex.Pos = XMFLOAT3(m_VertexList[a-1][0], m_VertexList[a-1][1], m_VertexList[a-1][2]);
		tmpVertex.Tex = XMFLOAT2(m_TextureCoordsList[A1-1][0], m_TextureCoordsList[A1-1][1]);
		m_VertexBuffer.push_back(tmpVertex);

		tmpVertex.Pos = XMFLOAT3(m_VertexList[b-1][0], m_VertexList[b-1][1], m_VertexList[b-1][2]);
		tmpVertex.Tex = XMFLOAT2(m_TextureCoordsList[B1-1][0], m_TextureCoordsList[B1-1][1]);
		m_VertexBuffer.push_back(tmpVertex);

		tmpVertex.Pos = XMFLOAT3(m_VertexList[c-1][0], m_VertexList[c-1][1], m_VertexList[c-1][2]);
		tmpVertex.Tex = XMFLOAT2(m_TextureCoordsList[C1-1][0], m_TextureCoordsList[C1-1][1]);
		m_VertexBuffer.push_back(tmpVertex);

		return true;
	}



	return false;
}

bool CObjectLoader::readLineMtl(std::string inLine) {
	//map_Kd
	if ("\t" == inLine.substr(0, 1)) {
		inLine.erase(inLine.begin());
	}

	if ("Ns " == inLine.substr(0, 3)
		|| "d " == inLine.substr(0, 2)
		|| "illum " == inLine.substr(0, 6)
		|| "newmtl " == inLine.substr(0, 7)
		|| "Kd " == inLine.substr(0, 3)
		|| "Ks " == inLine.substr(0, 3)
		|| "Ka " == inLine.substr(0, 3)
		|| "#" == inLine.substr(0, 1)
		|| "" == inLine.substr(0, 1)) {

		return true;
	}
	else if ("map_Kd " == inLine.substr(0, 7)) {
		std::string tmpString;
		std::stringstream tmpBuffer(inLine.substr(7));
		tmpBuffer >> tmpString;
		m_TextureFiles.push_back(tmpString);
		return true;
	}
	return false;
}
