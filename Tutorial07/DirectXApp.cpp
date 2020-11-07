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

	//Create Vertex Shader 
	m_VS_Reflect = GAPI.createVS(L"Tutorial07.fx", "VS_REFLECT", "vs_4_0");

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

	m_InputLayout = GAPI.createIL(layoutDesc, m_VS);

	//Create Pixel Shader
	m_PS = GAPI.createPS(L"Tutorial07.fx", "PS", "ps_4_0");

	//Create Pixel Shader for the Reflection
	m_PS_Reflect = GAPI.createPS(L"Tutorial07.fx", "PS_REFLECT", "ps_4_0");


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

	//Plane
	SimpleVertex vertices4Plane[] = {
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
	};
	//Create VB
	m_PlaneVB = GAPI.createBuffer(sizeof(SimpleVertex) * 4, 0x1L, 0, vertices4Plane);

	


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
	
	
	//Plane
	WORD indices4Plane[] = {
		3,1,0,
		2,1,3
	};

	//Create IB
	m_PlaneIB = GAPI.createBuffer(sizeof(WORD) * 6, 0x2L, 0, indices4Plane);

	//Set Topology
	GAPI.setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Create CB for Never Change
	m_CB_NC = GAPI.createBuffer(sizeof(CBNeverChanges), 0x4L, 0, nullptr);
	//Create CB for Change on Resize
	m_CB_COR = GAPI.createBuffer(sizeof(CBChangeOnResize), 0x4L, 0, nullptr);
	//Create CB for Change Every Frame
	m_CB_CEF = GAPI.createBuffer(sizeof(CBChangesEveryFrame), 0x4L, 0, nullptr);

	//Load Texture
	CImageLoader imgLoader;
	imgLoader.loadBMP("Test.bmp");
	m_ColorTexture = GAPI.createTex2D(imgLoader.getWidth(),
									  imgLoader.getHeight(),
									  0,
									  DXGI_FORMAT_R8G8B8A8_UNORM,
									  D3D11_BIND_SHADER_RESOURCE);
									//0xaabbggrr
	GAPI.updateTexture(m_ColorTexture, 
					   imgLoader.getImgData(), 
					   imgLoader.getPitch(), 
					   imgLoader.getImgSize());


	//Create Sampler
	SamplerDesc sampDesc;
	sampDesc.filter = 21;
	sampDesc.addressU = 1;
	sampDesc.addressV = 1;
	sampDesc.addressW = 1;
	sampDesc.comparisonFunc = 1;
	sampDesc.minLOD = 0;
	sampDesc.maxLOD = 3.402823466e+38f;
	m_Sampler = GAPI.createSampler(sampDesc);

	//Initialize world matrix
	m_World = XMMatrixIdentity();

	//Initialize Camera
	m_MainCamera.init(XM_PIDIV4, (m_Width/m_Height), 0.01f, 100.0f);
	
	GAPI.updateSubresource(m_CB_NC, &m_MainCamera.m_NC, sizeof(m_MainCamera.m_NC));

	GAPI.updateSubresource(m_CB_COR, &m_MainCamera.m_COR, sizeof(m_MainCamera.m_COR));

	//Other Render Target
	m_MyRenderTarget = GAPI.createTex2D(m_Width,
					   				    m_Height,
					   				    1,
					   				    DXGI_FORMAT_R8G8B8A8_UNORM,
					   				    D3D11_BIND_RENDER_TARGET | 
										D3D11_BIND_SHADER_RESOURCE);
	
}


void DirectXApp::onDestroy() {

}


void DirectXApp::onUpdate(float inDeltaTime) {
	//Movimiento de objetos
	//m_World = XMMatrixRotationY(inDeltaTime);
}


void DirectXApp::onRender() {

	auto& GAPI = g_GraphicsAPI();

	//Set Render Target & Depth Stencil
	GAPI.omSetRenderTarget(GAPI.getDefaultRenderTarget(), GAPI.getDefaultDephtStencil());
	//GAPI.omSetRenderTarget(m_MyRenderTarget);
	
	//Set Input Layout
	GAPI.aiSetInputLayout(m_InputLayout);

	// Clear the back buffer
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
	GAPI.clearRTV(GAPI.getDefaultRenderTarget(), ClearColor);
	GAPI.clearRTV(m_MyRenderTarget, ClearColor);

	// Clear the depth buffer to 1.0 (max depth)
	GAPI.clearDSV(GAPI.getDefaultDephtStencil());

	// Update variables that change once per frame
	CBChangesEveryFrame cb;
	m_World = XMMatrixIdentity();
	cb.mWorld = XMMatrixTranspose(m_World);
	cb.vMeshColor = m_MeshColor;
	GAPI.updateSubresource(m_CB_CEF, &cb, sizeof(cb));

	// Render the cube
	GAPI.vsSetShader(m_VS);
	GAPI.vsSetConstantBuffer(0, m_CB_NC);
	GAPI.vsSetConstantBuffer(1, m_CB_COR);
	GAPI.vsSetConstantBuffer(2, m_CB_CEF);
	GAPI.psSetShader(m_PS);
	GAPI.psSetConstantBuffer(2, m_CB_CEF);
	GAPI.psSetShaderResource(0, m_ColorTexture);
	GAPI.psSetSampler(0, 1, m_Sampler);
	
	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	GAPI.setVertexBuffer(m_VB, stride);

	//Set IB
	GAPI.setIndexBuffer(m_IB, DXGI_FORMAT_R16_UINT);

	GAPI.draw(36, 0);
	
					//Render to the other Render Target
	GAPI.omSetRenderTarget(m_MyRenderTarget);

	m_World = XMMatrixIdentity();
	XMVECTOR tmpVect = { 0.f, 1.f, 0.f };
	m_World *= XMMatrixReflect(tmpVect);

	GAPI.draw(36, 0);

	GAPI.omSetRenderTarget(GAPI.getDefaultRenderTarget(), GAPI.getDefaultDephtStencil());


	//Set vertex buffer
	GAPI.setVertexBuffer(m_PlaneVB, stride);
	
	//Set IB
	GAPI.setIndexBuffer(m_PlaneIB, DXGI_FORMAT_R16_UINT);

	m_World = XMMatrixIdentity();
	m_World *= XMMatrixScaling(2.f, 2.f, 2.f);
	//m_World *= XMMatrixRotationY(45);
	m_World *= XMMatrixTranslation(0.f, -3.0f, -2.f);

	cb.mWorld = XMMatrixTranspose(m_World);
	cb.vMeshColor = m_MeshColor;
	GAPI.updateSubresource(m_CB_CEF, &cb, sizeof(cb));
	GAPI.vsSetConstantBuffer(2, m_CB_CEF);
	GAPI.psSetConstantBuffer(2, m_CB_CEF);
	
	//GAPI.clearRTV(m_MyRenderTarget, ClearColor);
	//GAPI.omSetRenderTarget(GAPI.getDefaultRenderTarget(), GAPI.getDefaultDephtStencil());
	//GAPI.clearRTV(GAPI.getDefaultRenderTarget(), ClearColor);
	///GAPI.psSetShaderResource(0, m_MyRenderTarget);
	///GAPI.vsSetShader(m_VS_Reflect);
	///GAPI.psSetShader(m_PS_Reflect);
	GAPI.draw(6, 0);
	
	//Make it show
	GAPI.show();
}


void DirectXApp::onEvent(UINT inMsg, WPARAM inwParam) {

	auto& GAPI = g_GraphicsAPI();

	switch (inMsg) {
	case WM_KEYDOWN: {
		if ((inwParam == VK_UP) || (inwParam == 'W' || inwParam == 'w')) {
			XMVECTOR tmpVect = { 0.f, 0.f, 0.1f };
			m_MainCamera.move(tmpVect);
		}
		else if ((inwParam == VK_DOWN) || (inwParam == 'S' || inwParam == 's')) {
			XMVECTOR tmpVect = { 0.f, 0.f, -0.1f };
			m_MainCamera.move(tmpVect);
		}
		if ((inwParam == VK_LEFT) || (inwParam == 'A' || inwParam == 'a')) {
			XMVECTOR tmpVect = { -0.1f, 0.f, 0.f };
			m_MainCamera.move(tmpVect);
		}
		else if ((inwParam == VK_RIGHT) || (inwParam == 'D' || inwParam == 'd')) {
			XMVECTOR tmpVect = { 0.1f, 0.f, 0.f };
			m_MainCamera.move(tmpVect);
		}
		if (inwParam == 'E' || inwParam == 'e') {
			XMVECTOR tmpVect = { 0.f, 0.1f, 0.f };
			m_MainCamera.move(tmpVect);
		}
		else if (inwParam == 'Q' || inwParam == 'q') {
			XMVECTOR tmpVect = { 0.f, -0.1f, 0.f };
			m_MainCamera.move(tmpVect);
		}

		GAPI.updateSubresource(m_CB_NC, &m_MainCamera.m_NC, sizeof(m_MainCamera.m_NC));
	}
	default:
		break;
	}
	
}


CGraphicsAPI& g_GraphicsAPI() {
	return CGraphicsAPI::getSingleton();
}


