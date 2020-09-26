#pragma once
#include "Module.h"
#include <vector>
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"

class CTexture2D;
class CDepthStencilView;
class CRenderTargetView;
class CViewPort;
class CVertexShader;
class CPixelShader;
class CBuffer;
class CInputLayout;
class CSampler;

struct TextureDesc;
struct DepthStencilViewDesc;
struct InputLayoutDesc;
struct SamplerDesc;


class CGraphicsAPI : public Module<CGraphicsAPI> {
public:
	CGraphicsAPI();
	~CGraphicsAPI();
	/**
	* @brief	:
	**/
	virtual void onPrepare() override {};
	/**
	* @brief	:
	**/
	virtual void onShutDown() override {};
	/**
	* @brief	: In charge of the creation of the device & SwapChain
	**/
	void init(void * inWindow, int inWidth, int inHeight);
	/**
	* @brief	: In Charge to create the device and the swapchain
	**/
	bool createDeviceAndSwpaChain(void * inWindow);
	/**
	* @brief	: Creates the texture in the Device
	**/
	CTexture2D & CGraphicsAPI::createTex2D(TextureDesc inDesc);
	/**
	* @brief	: Creates the DSV in the Device
	**/
	CDepthStencilView & CGraphicsAPI::createDSV(DepthStencilViewDesc inDesc);
	/**
	* @brief	: Creates the RTV in the Device
	**/
	CRenderTargetView & CGraphicsAPI::createRTV(CTexture2D inBackBuffer);
	/**
	* @brief	: Creates the VP in the Device
	**/
	CViewPort & CGraphicsAPI::createVP();
	/**
	* @brief	: Sets the VP in the DeviceContext
	**/
	void CGraphicsAPI::setVP(CViewPort &inVP);
	/**
	* @brief	: Sets the VP in the DeviceContext
	**/
	CVertexShader CGraphicsAPI::createVS(WCHAR* inFileName,
									     LPCSTR inEntryPoint,
									     LPCSTR inShaderModel);
	/**
	* @brief	: Sets the VP in the DeviceContext
	**/
	CPixelShader CGraphicsAPI::createPS(WCHAR* inFileName,
									     LPCSTR inEntryPoint,
									     LPCSTR inShaderModel);
	/**
	* @brief	: Creates the InputLayout
	**/
	CInputLayout & createIL(InputLayoutDesc * inDesc, int inNumElements);

	/**
	* @brief	: Creates a buffer
	**/
	CBuffer & createBuffer(unsigned int inByteWidth, unsigned int inBindFlags, 
						   unsigned int inOffset, void * inBufferData);
	
	/**
	* @brief	: Creates a Sampler
	**/
	CSampler createSampler(SamplerDesc inDesc);

	

	IDXGISwapChain * m_SwapChain;
	ID3D11DeviceContext * m_DContext;
	unsigned int m_Width;	//Needs to be private
	unsigned int m_Height;	//Needs to be private
private:
	ID3D11Device * m_Device;

};

