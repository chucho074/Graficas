#include "DirectXApp.h"



DirectXApp::DirectXApp() {

}

DirectXApp::~DirectXApp() {

}

void DirectXApp::onCreate() {


	GAPI.init(m_window, 640, 480);

	GAPI.m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer.m_Texture);

	//backBuffer = GAPI.createTex2D();
	DepthStencilViewDesc descDepth;
	descDepth.format = 45;
	descDepth.mipSlice = 0;
	descDepth.viewDimension = 3;

	DS = GAPI.createDSV(descDepth);

	RTV1 = GAPI.createRTV(backBuffer);

	VP.m_VP.Width = (FLOAT)m_Width;
	VP.m_VP.Height = (FLOAT)m_Height;
	VP.m_VP.MinDepth = 0.0f;
	VP.m_VP.MaxDepth = 1.0f;
	VP.m_VP.TopLeftX = 0;
	VP.m_VP.TopLeftY = 0;
	
	GAPI.setVP(VP);

	GAPI.createVS(L"Tutorial07.fx", "VS", "vs_4_0");

	std::vector<InputLayoutDesc> layoutDesc;
	layoutDesc.resize(2);
	// Positions
	layoutDesc[0].semanticName = "POSITION";
	layoutDesc[0].semanticIndex = 0;
	layoutDesc[0].format = DXGI_FORMAT_R32G32B32_FLOAT;
	layoutDesc[0].inputSlot = 0;
	layoutDesc[0].alignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	layoutDesc[0].inputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[0].instanceDataStepRate = 0;
	// texcoords
	layoutDesc[1].semanticName = "TEXCOORD";
	layoutDesc[1].semanticIndex = 0;
	layoutDesc[1].format = DXGI_FORMAT_R32G32_FLOAT;
	layoutDesc[1].inputSlot = 0;
	layoutDesc[1].alignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	layoutDesc[1].inputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[1].instanceDataStepRate = 0;

	IL.init(&layoutDesc[0], 2);

	GAPI.createPS(L"Tutorial07.fx", "PS", "ps_4_0");


	SimpleVertex vertices[] =
	{
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
	};

	VB = GAPI.createBuffer(sizeof(SimpleVertex) * 24, 0x1L, 0, vertices);
	//GAPI.m_


}

void DirectXApp::onDestroy() {

}

void DirectXApp::onUpdate(float inDeltaTime) {

}

void DirectXApp::onRender() {

}
