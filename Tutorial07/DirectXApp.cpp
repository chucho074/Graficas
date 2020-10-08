#include "DirectXApp.h"

DirectXApp::DirectXApp() {
  m_Width = 1280;
  m_Height = 720;
}

DirectXApp::~DirectXApp() {

}

void DirectXApp::onCreate() {

	auto& GAPI = g_GraphicsAPI();

	//Create Vertex Shader 
	m_VS = GAPI.createVS(L"Tutorial07.fx", "VS", "vs_4_0");

	//Create Input Layout
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
	//texcoords
	layoutDesc[1].semanticName = "TEXCOORD";
	layoutDesc[1].semanticIndex = 0;
	layoutDesc[1].format = DXGI_FORMAT_R32G32_FLOAT;
	layoutDesc[1].inputSlot = 0;
	layoutDesc[1].alignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	layoutDesc[1].inputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[1].instanceDataStepRate = 0;

	m_IL->init(&layoutDesc[0], 2);

	//Create Pixel Shader
	m_PS = GAPI.createPS(L"Tutorial07.fx", "PS", "ps_4_0");


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
	m_VB = GAPI.createBuffer(sizeof(SimpleVertex) * 24, 0x1L, 0, vertices);
	
	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	GAPI.setVertexBuffer(m_VB, stride);


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
	m_IB = GAPI.createBuffer(sizeof(WORD) * 36, 0x2L, 0, indices);
	//Set IB
	GAPI.setIndexBuffer(m_IB, DXGI_FORMAT_R16_UINT);
	
	//Set Topology
	GAPI.setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Create CB for Never Change
	m_CB_NC = GAPI.createBuffer(sizeof(CBNeverChanges), 0x4L, 0, nullptr);
	//Create CB for Change on Resize
	m_CB_COR = GAPI.createBuffer(sizeof(CBChangeOnResize), 0x4L, 0, nullptr);
	//Create CB for Change Every Frame
	m_CB_CEF = GAPI.createBuffer(sizeof(CBChangesEveryFrame), 0x4L, 0, nullptr);

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
	m_World = XMMatrixIdentity();

	//Initialize Camera
	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_VM = XMMatrixLookAtLH(Eye, At, Up);

	CBNeverChanges cbNeverChanges;
	cbNeverChanges.mView = XMMatrixTranspose(m_VM);
	GAPI.updateSubresource(m_CB_NC, &cbNeverChanges);

	// Initialize the projection matrix
	m_PM = XMMatrixPerspectiveFovLH(XM_PIDIV4, m_Width/m_Height, 0.01f, 100.0f);

	CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = XMMatrixTranspose(m_PM);
	GAPI.updateSubresource(m_CB_COR, &cbChangesOnResize);

}


void DirectXApp::onDestroy() {

}


void DirectXApp::onUpdate(float inDeltaTime) {
	//Movimiento de objetos
	m_World = XMMatrixRotationY(inDeltaTime);
}


void DirectXApp::onRender() {

	auto& GAPI = g_GraphicsAPI();

	// Clear the back buffer
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
	GAPI.clearRTV(nullptr, ClearColor);

	// Clear the depth buffer to 1.0 (max depth)
	GAPI.clearDSV(nullptr);

	// Update variables that change once per frame
	CBChangesEveryFrame cb;
	cb.mWorld = XMMatrixTranspose(m_World);
	cb.vMeshColor = m_MeshColor;
	GAPI.updateSubresource(m_CB_CEF, &cb);

	// Render the cube
	GAPI.vsSetShader(m_VS);
	GAPI.vsSetConstantBuffer(0, m_CB_NC);
	GAPI.vsSetConstantBuffer(1, m_CB_COR);
	GAPI.vsSetConstantBuffer(2, m_CB_CEF);
	GAPI.psSetShader(m_PS);
	GAPI.psSetConstantBuffer(2, m_CB_CEF);
	GAPI.psSetShaderResource(0, m_SRV);
	GAPI.psSetSampler(0, 1, m_Sampler);
	GAPI.draw(36, 0);

	//Make it show
	GAPI.show();
}

CGraphicsAPI& g_GraphicsAPI() {
	return CGraphicsAPI::getSingleton();
}
