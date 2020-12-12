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
#include "CImageLoader.h"
#include "CObjectLoader.h"
#include "CCamera.h"
#include "CMesh.h"
#include "CModel.h"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx11.h"
#include "ImGUI/imgui_impl_win32.h"



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
	void onEvent(UINT inMsg, WPARAM inwParam) override;

private:

	CCamera m_MainCamera;
	CInputLayout * m_InputLayout = nullptr;
	CSampler * m_Sampler = nullptr;
	CBuffer * m_VB = nullptr;
	CBuffer * m_IB = nullptr;
	CBuffer * m_CB_NC = nullptr;	
	CBuffer * m_CB_COR = nullptr;	
	CBuffer * m_CB_CEF = nullptr;
	CVertexShader * m_VS = nullptr;
	CVertexShader * m_VS_Reflect = nullptr;
	CPixelShader * m_PS = nullptr;
	CPixelShader * m_PS_Reflect = nullptr;
	XMMATRIX m_World;
	XMFLOAT4 m_MeshColor;
	
	CModel m_Yoshi;
	CTexture2D * m_ColorTexture = nullptr;

	CModel m_Peach;
	CTexture2D * m_PeachTexture = nullptr;

	CBuffer * m_PlaneVB = nullptr;
	CBuffer * m_PlaneIB = nullptr;

	CTexture2D * m_MyRenderTarget = nullptr;
};

