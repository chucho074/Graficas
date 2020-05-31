#include "CResource.h"
#ifdef D_DIRECTX
CResource::CResource() {}

CResource::~CResource() {}

bool CResource::loadMesh(const char * path, CSceneManager * SM, const aiScene * model, CDeviceContext * DC, Assimp::Importer * importer, CDevice * dev)
{
	model = importer->ReadFile(path, aiProcessPreset_TargetRealtime_Fast | aiProcess_ConvertToLeftHanded | aiProcess_FindInstances
		| aiProcess_ValidateDataStructure | aiProcess_OptimizeMeshes | aiProcess_Debone);

	if (model == nullptr)
	{
		return false;
	}

	CMesh * newMesh = new CMesh();
	char * token = NULL;
	char * nexttoken = NULL;
	string spath = path;

	token = strtok_s((char*)spath.c_str(), "/", &nexttoken);
	string texturesFolder = token;
	texturesFolder += "\\";
	token = (char*)texturesFolder.c_str();
	newMesh->Materials->TextureDir = token;

	string dirName = newMesh->Materials->TextureDir;

	meshRead(model, newMesh, 0, dev);
	readMeshTexture(model, newMesh, 0, dev);
	SM->addMesh(newMesh);

	if (model->mNumMeshes > 1)
	{
		for (int i = 1; i < model->mNumMeshes; i++)
		{
			CMesh* childMesh = new CMesh();
			childMesh->setParent(newMesh);
			newMesh->addChildren(childMesh);
			childMesh->Materials->TextureDir = dirName;
			meshRead(model, childMesh, i, dev);
			SM->addMesh(childMesh);
		}
	}
	return true;
}

void CResource::meshRead(const aiScene * model, CMesh * mesh, int index, CDevice * dev)
{
	std::vector <std::uint32_t> indis;
	indis.reserve(model->mMeshes[index]->mNumFaces * 3);
	int numVertex = model->mMeshes[index]->mNumVertices;
	int numIndex = model->mMeshes[index]->mNumFaces * 3;
	for (std::uint32_t faceIdx = 0u; faceIdx < model->mMeshes[index]->mNumFaces; faceIdx++)
	{
		indis.push_back(model->mMeshes[index]->mFaces[faceIdx].mIndices[0u]);
		indis.push_back(model->mMeshes[index]->mFaces[faceIdx].mIndices[1u]);
		indis.push_back(model->mMeshes[index]->mFaces[faceIdx].mIndices[2u]);
	}

	SimpleVertex* meshVertex = new SimpleVertex[numVertex];
	WORD* meshIndex = new WORD[numIndex];

	for (int i = 0; i < numVertex; i++)
	{
		meshVertex[i].Pos.x = model->mMeshes[index]->mVertices[i].x;
		meshVertex[i].Pos.y = model->mMeshes[index]->mVertices[i].y;
		meshVertex[i].Pos.z = model->mMeshes[index]->mVertices[i].z;
		meshVertex[i].Tex.x = model->mMeshes[index]->mTextureCoords[0][i].x;
		meshVertex[i].Tex.y = model->mMeshes[index]->mTextureCoords[0][i].y;
	}

	mesh->setVertex(meshVertex, numVertex);
#ifdef D_DIRECTX
	//Create VB
	CBuffer::createVertexBuffer(numVertex, model, meshVertex, mesh->getVB()->Buffer, dev->Device);
#endif

	for (int i = 0; i < numIndex; i++)
	{
		meshIndex[i] = (WORD)indis[i];
	}

	mesh->setIndexList(meshIndex, numIndex);
#ifdef D_DIRECTX
	//Create IB
	CBuffer::createIndexBuffer(numIndex, model, meshIndex, mesh->getIB()->Buffer, dev->Device);
#endif
}

void CResource::readMeshTexture(const aiScene * model, CMesh * mesh, int index, CDevice * dev)
{
	const aiMaterial* pMaterial = model->mMaterials[model->mMeshes[index]->mMaterialIndex];

	//Diffuse texture
	if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
	{
		aiString Path;
		mesh->Materials->HasDiffuse = true;
		if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
		{
			mesh->Materials->Diffuse = mesh->Materials->TextureDir;
			mesh->Materials->Diffuse += (string)Path.data;
			wchar_t wtext[50];
			char* token = NULL;
			char* nextToken = NULL;
			token = strtok_s((char*)mesh->Materials->Diffuse.c_str(), ".", &nextToken);
			std::string pngextention = token;
			pngextention += ".png";
			token = (char*)pngextention.c_str();

			LPCSTR direcTexture = token;
			LPCWSTR dir = (LPCWSTR)pngextention.c_str();

			int stringLength = MultiByteToWideChar(CP_ACP, 0, pngextention.data(), pngextention.length(), 0, 0);
			std::wstring wstr(stringLength, 0);
			MultiByteToWideChar(CP_ACP, 0, pngextention.data(), pngextention.length(), &wstr[0], stringLength);
			dir = (LPCWSTR)wstr.c_str();

#ifdef D_DIRECTX
			D3DX11CreateShaderResourceViewFromFile(dev->Device, dir, NULL, NULL, &mesh->Materials->m_TextureDiffuse, NULL);
#endif 
		}
	}
}
#endif 