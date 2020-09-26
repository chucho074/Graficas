#include "DirectXApp.h"



DirectXApp::DirectXApp() {

}


DirectXApp::~DirectXApp() {

}


void DirectXApp::onCreate() {


	GAPI.init(m_window, 640, 480);

	GAPI.m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), 
							   (LPVOID*)&backBuffer.m_Texture);

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


	SimpleVertex vertices[] = {
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
	//Create VB
	VB = GAPI.createBuffer(sizeof(SimpleVertex) * 24, 0x1L, 0, vertices);
	
	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	GAPI.m_DContext->IASetVertexBuffers(0, 1, &VB.m_Buffer, &stride, &offset);


	WORD indices[] = {
		3,1,0,
		2,1,3,

		6,4,5,
		7,4,6,

		11,9,8,
		10,9,11,

		14,12,13,
		15,12,14,

		19,17,16,
		18,17,19,

		22,20,21,
		23,20,22
	};
	//Create IB
	IB = GAPI.createBuffer(sizeof(WORD) * 36, 0x2L, 0, indices);
	//Set IB
	GAPI.m_DContext->IASetIndexBuffer(IB.m_Buffer, DXGI_FORMAT_R16_UINT, 0);
	
	//Set Topology
	GAPI.m_DContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Create CB for Never Change
	CB_NC = GAPI.createBuffer(sizeof(CBNeverChanges), 0x4L, 0, nullptr);
	//Create CB for Change on Resize
	CB_COR = GAPI.createBuffer(sizeof(CBChangeOnResize), 0x4L, 0, nullptr);
	//Create CB for Change Every Frame
	CB_CEF = GAPI.createBuffer(sizeof(CBChangesEveryFrame), 0x4L, 0, nullptr);

	//Load Texture
	//No se xd

	//Create Sampler
	SamplerDesc sampDesc;
	sampDesc.filter = 21;
	sampDesc.addressU = 1;
	sampDesc.addressV = 1;
	sampDesc.addressW = 1;
	sampDesc.comparisonFunc = 1;
	sampDesc.minLOD = 0;
	sampDesc.maxLOD = 3.402823466e+38f;
	GAPI.createSampler(sampDesc);

	//Initialize world matrix
	World = XMMatrixIdentity();

	//Initialize Camera
	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	VM = XMMatrixLookAtLH(Eye, At, Up);

	CBNeverChanges cbNeverChanges;
	cbNeverChanges.mView = XMMatrixTranspose(VM);
	GAPI.m_DContext->UpdateSubresource(CB_NC.m_Buffer, 0, NULL, &cbNeverChanges, 0, 0);

	// Initialize the projection matrix
	PM = XMMatrixPerspectiveFovLH(XM_PIDIV4, GAPI.m_Width / (FLOAT)GAPI.m_Height, 0.01f, 100.0f);

	CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = XMMatrixTranspose(PM);
	GAPI.m_DContext->UpdateSubresource(CB_COR.m_Buffer, 0, NULL, &cbChangesOnResize, 0, 0);

}


void DirectXApp::onDestroy() {

}


void DirectXApp::onUpdate(float inDeltaTime) {

}


void DirectXApp::onRender() {

}
