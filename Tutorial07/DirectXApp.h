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
	CGraphicsAPI GAPI;
	CTexture2D backBuffer = CTexture2D();
	CDepthStencilView DS = CDepthStencilView();
	CRenderTargetView RTV1 = CRenderTargetView();
	CViewPort VP = CViewPort();
	CInputLayout IL = CInputLayout();
	CSampler Sampler = CSampler();
	CBuffer VB = CBuffer();
	CBuffer IB = CBuffer();
	CBuffer CB_NC = CBuffer();	//CCamera?
	CBuffer CB_COR = CBuffer();	//CCamera
	CBuffer CB_CEF = CBuffer();
	XMMATRIX World;
	XMMATRIX VM;				//CCamera
	XMMATRIX PM;				//CCamera
};

