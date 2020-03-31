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
#include "CMaterial.h"

CMaterial::CMaterial() {
#ifdef D_DIRECTX
	m_TextureDiffuse = NULL;
	m_TextureNormal = NULL;
#endif	
}

CMaterial::~CMaterial() {

}

void CMaterial::shutdown() {
#ifdef D_DIRECTX
	if (m_TextureDiffuse) {
		m_TextureDiffuse->Release();
	}
#endif
}
