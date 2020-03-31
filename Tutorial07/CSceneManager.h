/**
* @LC		: 30/03/2020
* @file		: CSceneManager.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/03/2020
* @brief	:.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include "CMesh.h"

/**
* @brief	: Class for Scene managment.
* @bug		: No Bugs Known.
**/
class CSceneManager {
#ifdef D_DIRECTX
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs Known.
	**/
	CSceneManager();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs Known.
	**/
	~CSceneManager();

	/**
	* @brief	: Add a mesh.
	* @param	: CMesh.
	* @bug		: No Bugs Known.
	**/
	void addMesh(CMesh * M);

	/**
	* @brief	: Getter for the mesh.
	* @param	: int for ID.
	* @bug		: No Bugs Known.
	**/
	CMesh*& getMesh(int ID);

	/**
	* @brief	: Update of the class.
	* @bug		: No Bugs Known.
	**/
	void update();

	/**
	* @brief	: Short description of function.
	* @param	: CDeviceContext, CBuffer, CDevice.
	* @bug		: No Bugs Known.
	**/
	void render(CDeviceContext * inDC, CBuffer* inBuffer, CDevice* inDevide);

	/**
	* @brief	: Shutdown of the class.
	* @bug		: No Bugs Known.
	**/
	void shutdown();

	CBuffer * m_meshData;
	std::vector<CMesh*> m_MeshList;
	int m_ID;
#endif
};