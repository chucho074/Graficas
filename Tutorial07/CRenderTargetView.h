#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "resource.h"

/**
* @brief	: Abstraction for texture 2D.
* @bug		: No Bugs known.
**/
class CRenderTargetView {
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs known.
	**/
	CRenderTargetView();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CRenderTargetView();


	ID3D11RenderTargetView * m_RTV;
private:

protected:

};

