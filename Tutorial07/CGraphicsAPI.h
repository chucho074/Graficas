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
	CTexture2D * CGraphicsAPI::createTex2D(int inWidth,
										   int inHeigh,
										   int inMipLevels,
										   DXGI_FORMAT inFormat,
										   int inBindFlags);
	
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
	CInputLayout * createIL(std::vector<InputLayoutDesc> & inDesc, CVertexShader * inShader);

	/**
	* @brief	: Creates a buffer
	**/
	CBuffer * createBuffer(unsigned int inByteWidth, unsigned int inBindFlags, 
						   unsigned int inOffset, void * inBufferData);
	
	/**
	* @brief	: Creates a Sampler
	**/
	CSampler * createSampler(SamplerDesc inDesc);

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
	void updateSubresource(CBuffer * inBuffer, void * inData, unsigned int inPitch);

	//Clear RTV
	void clearRTV(CTexture2D* inRTV, float inColor[4] );

	//Clear DSV
	void clearDSV(CTexture2D* inDSV);

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

	//IASetInputLayout
	void aiSetInputLayout(CInputLayout * inInputLayout);

	//OMSetRenderTargets
	void omSetRenderTarget(CTexture2D * inRT, CTexture2D* inDS);

	//DrawIndex
	void draw(unsigned int inNumIndexes, unsigned int inStartLocation);

	CTexture2D* getDefaultRenderTarget() { return m_backBuffer; }
	CTexture2D* getDefaultDephtStencil() { return m_defaultDSV; }

  private:
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_DContext;
	IDXGISwapChain* m_SwapChain;

	CTexture2D  * m_backBuffer = nullptr;
	CTexture2D  * m_defaultDSV = nullptr;
	CViewPort * m_defaultVP = nullptr;
};

static CGraphicsAPI& g_GraphicsAPI();
