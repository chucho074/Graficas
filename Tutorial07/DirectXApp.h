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

struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
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
	CBuffer VB = CBuffer();
	CBuffer IB = CBuffer();
	CBuffer CB = CBuffer();

};

