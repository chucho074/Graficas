/**
* @LC		: 04/06/2020
* @file		: CPixelShader.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 02/06/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include "Defines.h"
#include "Includes.h"

class CShaders {
public:
	
	virtual void * getShader() = 0;


	virtual void * getBlob() { 
	#ifdef D_DIRECTX
			return m_Blob;
	#else
			return nullptr;
	#endif
	}

#ifdef D_DIRECTX

	ID3DBlob * m_Blob;

	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel) {
		HRESULT hr = S_OK;

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3DCOMPILE_DEBUG;

		ID3DBlob* pErrorBlob;
		hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
			dwShaderFlags, 0, NULL, &this->m_Blob, &pErrorBlob, NULL);
		if (FAILED(hr)) {
			if (pErrorBlob != NULL) {
				OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
			}
			if (pErrorBlob) {
				pErrorBlob->Release();
			}
			return hr;
			//Sends a message if cant be compiled
			MessageBox(NULL, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);

		}
		if (pErrorBlob) {
			pErrorBlob->Release();
		}

		return S_OK;
	}

	
#endif
};

