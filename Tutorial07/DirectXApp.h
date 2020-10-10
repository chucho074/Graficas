#pragma once
#include "BaseApp.h"

#include "CGraphicsAPI.h"
#include "CTexture2D.h"
#include "CDepthStencilView.h"
#include "CRenderTargetView.h"
#include "CViewPort.h"
#include "CVertexShader.h"
#include "CPixelShader.h"
#include "CBuffer.h"
#include "CInputLayout.h"
#include "CSampler.h"
#include "CVertexShader.h"
#include "CPixelShader.h"


struct SimpleVertex {
	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
};

struct CBNeverChanges {
	XMMATRIX mView;
};

struct CBChangeOnResize {
	XMMATRIX mProjection;
};

struct CBChangesEveryFrame {
	XMMATRIX mWorld;
	XMFLOAT4 vMeshColor;
};

class DirectXApp : public BaseApp {
public:
	DirectXApp();
	~DirectXApp();

	void onCreate() override;
	void onDestroy() override;
	void onUpdate(float inDeltaTime = 0) override;
	void onRender() override;

private:

	CInputLayout * m_InputLayout = nullptr;
	CSampler *m_Sampler = nullptr;
	CBuffer * m_VB = nullptr;
	CBuffer * m_IB = nullptr;
	CBuffer * m_CB_NC = nullptr;	//CCamera?
	CBuffer * m_CB_COR = nullptr;	//CCamera?
	CBuffer * m_CB_CEF = nullptr;
	CVertexShader *m_VS = nullptr;
	CPixelShader * m_PS = nullptr;
	XMMATRIX m_World;
	XMMATRIX m_VM;				//CCamera?
	XMMATRIX m_PM;				//CCamera?
	XMFLOAT4 m_MeshColor;
	ID3D11ShaderResourceView* m_SRV = nullptr;
};

