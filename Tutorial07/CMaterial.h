/**
* @LC		: 30/03/2020
* @file		: CMaterial.h
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
#include "Includes.h"
#include <string>

using std::string;

/**
* @brief	: Class Material.
* @bug		: No Bugs Known.
**/
class CMaterial {
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs Known.
	**/
	CMaterial();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs Known.
	**/
	~CMaterial();

	/**
	* @brief	: Shutdown.
	* @bug		: No Bugs Known.
	**/
	void shutdown();
	
	
	string Normal;
	bool HasNormal;
	bool HasDiffuse;
	string TextureDir;
	string Diffuse;

#ifdef D_DIRECTX
	ID3D11ShaderResourceView*	m_TextureDiffuse;
	ID3D11ShaderResourceView*	m_TextureNormal;
#endif	
};