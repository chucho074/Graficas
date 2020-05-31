/**
* @LC		: 30/03/2020
* @file		: CResource.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 13/03/2020
* @brief	: .
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include "CSceneManager.h"
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/**
* @brief	: Class for Graphics.
* @bug		: No Bugs Known.
**/
class CResource {
#ifdef D_DIRECTX
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs Known.
	**/
	CResource();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs Known.
	**/
	~CResource();

	/**
	* @brief	: Load a mesh.
	* @bug		: No Bugs Known.
	**/
	bool loadMesh(const char* path, CSceneManager* SM, const aiScene* model, CDeviceContext* DC, Assimp::Importer* importer, CDevice *dev);
	
	const aiScene* m_Model = new const aiScene();
	Assimp::Importer* m_Importer = new Assimp::Importer();


private:
	void meshRead(const aiScene* model, CMesh* mesh, int index, CDevice * dev);
	void readMeshTexture(const aiScene* model, CMesh* mesh, int index, CDevice* dev);
#endif
};