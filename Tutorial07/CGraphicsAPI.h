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
	void onPrepare() override {};
	/**
	* @brief	:
	**/
	void onShutDown() override {};
	/**
	* @brief	: In charge of the creation of the device & SwapChain
	**/
	void init(void * inWindow, int inWidth, int inHeight);
	/**
	* @brief	: In Charge to create the device and the swap chain
	**/
	HRESULT createDeviceAndSwpaChain(void * inWindow, int inWidth, int inHeight);
	/**
	* @brief	: Creates the texture in the Device
	**/
	CTexture2D * CGraphicsAPI::createTex2D(TextureDesc inDesc);
	/**
	* @brief	: Creates the DSV in the Device
	**/
	CDepthStencilView * CGraphicsAPI::createDSV(DepthStencilViewDesc inDesc);
	/**
	* @brief	: Creates the RTV in the Device
	**/
	CRenderTargetView * CGraphicsAPI::createRTV(CTexture2D *inBackBuffer);
	/**
	* @brief	: Creates the VP in the Device
	**/
	CViewPort * CGraphicsAPI::createVP(int inWidth, int inHeight);
	/**
	* @brief	: Sets the VP in the DeviceContext
	**/
	void CGraphicsAPI::setVP(CViewPort &inVP);
	/**
	* @brief	: Sets the VP in the DeviceContext
	**/
	CVertexShader *CGraphicsAPI::createVS(WCHAR* inFileName,
									     LPCSTR inEntryPoint,
									     LPCSTR inShaderModel);
	/**
	* @brief	: Sets the VP in the DeviceContext
	**/
	CPixelShader * CGraphicsAPI::createPS(WCHAR* inFileName,
									     LPCSTR inEntryPoint,
									     LPCSTR inShaderModel);
	/**
	* @brief	: Creates the InputLayout
	**/
	CInputLayout * createIL(InputLayoutDesc * inDesc, int inNumElements);

	/**
	* @brief	: Creates a buffer
	**/
	CBuffer * createBuffer(unsigned int inByteWidth, unsigned int inBindFlags, 
						   unsigned int inOffset, void * inBufferData);
	
	/**
	* @brief	: Creates a Sampler
	**/
	CSampler createSampler(SamplerDesc inDesc);

	/**
	* @brief	: Creates a Sampler
	**/
	void show();

	//Set VertexBuffer
	void setVertexBuffer(CBuffer * inBuffer, unsigned int inStride);

	//Set IndexBuffer
	void setIndexBuffer(CBuffer * inBuffer, DXGI_FORMAT inFormat);

	//Set PrimitiveTopology
	void setTopology(D3D_PRIMITIVE_TOPOLOGY inTopotology);

	//Update Subresource
	void updateSubresource(CBuffer * inBuffer, void * inData);

	//Clear RTV
	void clearRTV(CRenderTargetView * inRTV, float inColor[4] );

	//Clear DSV
	void clearDSV(CDepthStencilView * inDSV);

	//VSSetShader
	void vsSetShader(CVertexShader * inVShader);

	//VSSetConstantBuffer
	void vsSetConstantBuffer(unsigned int inSlot, CBuffer * inBuffer);

	//PSSetShader
	void psSetShader(CPixelShader * inPShader);

	//PSSetConstantBuffer
	void psSetConstantBuffer(unsigned int inSlot, CBuffer * inBuffer);

	//PSSetShaderResource
	void psSetShaderResource(unsigned int inSlot, ID3D11ShaderResourceView * inSRV);

	//PSSetSamplers
	void psSetSampler(unsigned int inSlot, 
					  unsigned int inNumSamplers, 
					  CSampler * inSampler);

	//DrawIndex
	void draw(unsigned int inNumIndexes, unsigned int inStartLocation);

  private:
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_DContext;
	IDXGISwapChain* m_SwapChain;

	CTexture2D  * m_backBuffer = nullptr;
	CRenderTargetView * m_defaultRTV = nullptr;
	CDepthStencilView * m_defaultDSV = nullptr;
	CViewPort * m_defaultVP = nullptr;
};

static CGraphicsAPI& g_GraphicsAPI();
