/**
* @LC		: 06/07/2020
* @file		: CTexture.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 01/07/2020
* @brief	: .
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CTexture2D.h"

CTexture2D::CTexture2D() {
#if (defined D_DirectX || defined R_DirectX) 
	m_Texture = NULL;
#endif
}

CTexture2D::~CTexture2D() {
	destroy();
}

void CTexture2D::setDesc(TextureDesc inDesc) {
	m_Desc = inDesc;
}

void * CTexture2D::getTexture() {
#if (defined D_DirectX || defined R_DirectX) 
	return m_Texture;
#endif
}

void CTexture2D::destroy() {
#if (defined D_DirectX || defined R_DirectX) 
	if (m_Texture) {
		m_Texture->Release();
		m_Texture = nullptr;
	}
#endif

}
