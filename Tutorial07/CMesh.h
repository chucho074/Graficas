/**
* @LC		: 30/03/2020
* @file		: CCamera.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/03/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#pragma once
#include "Defines.h"
#include "Includes.h"
#include "CBuffer.h"
#include "CDevice.h"
#include "CDeviceContext.h"
#include "CMaterial.h"
#include <vector>
#include <Windows.h>


#ifdef D_DIRECTX


#elif OPENGL
/**
* @brief	: Vertex Desc.
* @bug		: No Bugs Known.
**/
struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
	vec3 Tangent;
	vec3 Bitangent;
};

/**
* @brief	: Texture Desc.
* @bug		: No Bugs Known.
**/
struct Texture {
	unsigned int id;
	string type;
	string path;
};
#endif

/**
* @brief	: Class Mesh.
* @bug		: No Bugs Known.
**/
class CMesh {
#ifdef D_DIRECTX
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs Known.
	**/
	CMesh();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs Known.
	**/
	~CMesh();

	/**
	* @brief	: Init.
	* @bug		: No Bugs Known.
	**/
	void init();

	/**
	* @brief	: Update.
	* @bug		: No Bugs Known.
	**/
	void update();

	/**
	* @brief	: Render.
	* @param	: CDeviceContext, CBuffer, CDevice.
	* @bug		: No Bugs Known.
	**/
	void render(CDeviceContext * inDC, CBuffer * inBuffer, CDevice * inDevice);

	/**
	* @brief	: Delete.
	* @bug		: No Bugs Known.
	**/
	void Delete();

	/**
	* @brief	: Add a child.
	* @param	: CMesh.
	* @bug		: No Bugs Known.
	**/
	void addChildren(CMesh * M);

	/**
	* @brief	: Setter for parent.
	* @param	: CMesh.
	* @bug		: No Bugs Known.
	**/
	void setParent(CMesh* P);

	/**
	* @brief	: Setter for vertex.
	* @param	: SimpleVertex, int.
	* @bug		: No Bugs Known.
	**/
	void setVertex(SimpleVertex* V, int num);

	/**
	* @brief	: Setter for index list.
	* @param	: WORD, int.
	* @bug		: No Bugs Known.
	**/
	void setIndexList(WORD* inWord, int inNum);

	/**
	* @brief	: Getter for the index list.
	* @param	: SimpleVertex, int.
	* @bug		: No Bugs Known.
	**/
	WORD*& getIndexList(SimpleVertex* inVertex, int inNum);

	/**
	* @brief	: Getter for the Vertex.
	* @bug		: No Bugs Known.
	**/
	SimpleVertex* getVertex();

	/**
	* @brief	: Getter for the num of Vertex.
	* @bug		: No Bugs Known.
	**/
	int getVertexNum();

	/**
	* @brief	: Getter for the num of Index.
	* @bug		: No Bugs Known.
	**/
	int getIndexNum();

	/**
	* @brief	: Getter for Vertex Buffer.
	* @bug		: No Bugs Known.
	**/
	CBuffer *& getVB();

	/**
	* @brief	: Getter for the Index Buffer.
	* @bug		: No Bugs Known.
	**/
	CBuffer *& getIB();

	/**
	* @brief	: Setter for the Vertex Buffer.
	* @param	: CBuffer.
	* @bug		: No Bugs Known.
	**/
	void setVB(CBuffer* pVB);

	/**
	* @brief	: Setter for the Index Buffer.
	* @param	: CBuffer.
	* @bug		: No Bugs Known.
	**/
	void setIB(CBuffer* pIB);

	/**
	* @brief	: Setter for the id to Scene.
	* @param	: Int for id.
	* @bug		: No Bugs Known.
	**/
	void setSceneID(int ID);

	/**
	* @brief	: Getter for the scene.
	* @bug		: No Bugs Known.
	**/
	int getSceneID();

	string DiffuseName;
	vec4 Transform;
	CMaterial* Materials;
	CMesh* Parent;
	std::vector<CMesh*> Children;
	CBuffer* VB;
	CBuffer* IB;
	SimpleVertex* SVertex;
	WORD* Index;
	int VNum;
	int INum;
	int SceneID;

	CBChangesEveryFrame	MeshData;
#elif OPENGL
public:
	std::vector<Vertex> vertex;
	std::vector<unsigned int> index;
	std::vector<Texture> tex;
	unsigned int VAO;

	/**
	* @brief	: Constructor with parameters.
	* @param	: Vector of Vertex, vector of UInts, vector of textures.
	* @bug		: No Bugs Known.
	**/
	CMesh(std::vector<Vertex>v, std::vector<unsigned int>i, std::vector<Texture>t);
	void Draw(int shaderID);

private:
	unsigned int VBO, EBO;

	void setupMesh();
#endif	
};