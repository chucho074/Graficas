//--------------------------------------------------------------------------------------
// File: Tutorial07.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include <windows.h>

#if(defined D_DirectX || defined R_DirectX)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#endif

#if(defined D_OpenGL || defined R_OpenGL)
#include <glad.h>
#include <GLFW/glfw3.h>
#endif

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"

//#include "CBuffer.h"
#include "CGraphicsAPI.h"
#include "CDepthStencilView.h"
#include "CTexture2D.h"
#include "CRenderTargetView.h"

using namespace glm;


//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
#if(defined D_DirectX || defined R_DirectX)
struct SimpleVertex
{
    vec3 Pos;
    vec2 Tex;
};

struct CBNeverChanges
{
    mat4 mView;
};

struct CBChangeOnResize
{
    mat4 mProjection;
};

struct CBChangesEveryFrame
{
    mat4 mWorld;
    vec4 vMeshColor;
};
#endif


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE                           g_hInst = NULL;
HWND                                g_hWnd = NULL;
//D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
//D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;
//ID3D11Device*                       g_pd3dDevice = NULL;
//ID3D11DeviceContext*                g_pImmediateContext = NULL;
//IDXGISwapChain*                     g_pSwapChain = NULL;
CGraphicsAPI				* g_GAPI;
CBuffer                       g_pVertexBuffer;
CBuffer                       g_pIndexBuffer;
CBuffer                       g_pCBNeverChanges;
CBuffer                       g_pCBChangeOnResize;
CBuffer                       g_pCBChangesEveryFrame;
CDepthStencilView             g_pDepthStencilView;
CTexture2D                    g_pDepthStencil;
CRenderTargetView             g_pRenderTargetView;
#if(defined D_DirectX || defined R_DirectX)
//ID3D11RenderTargetView*             g_pRenderTargetView = NULL;
//ID3D11Texture2D*                    g_pDepthStencil = NULL;
//ID3D11DepthStencilView*             g_pDepthStencilView = NULL;
ID3D11VertexShader*                 g_pVertexShader = NULL;
ID3D11PixelShader*                  g_pPixelShader = NULL;
ID3D11InputLayout*                  g_pVertexLayout = NULL;
ID3D11ShaderResourceView*           g_pTextureRV = NULL;
ID3D11SamplerState*                 g_pSamplerLinear = NULL;
mat4                            g_World;
mat4                            g_View;
mat4                            g_Projection;
vec4                            g_vMeshColor( 0.7f, 0.7f, 0.7f, 1.0f );
#endif

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
void Render();


#if (defined D_OpenGL || defined R_OpenGL)
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ) {
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

#if (defined D_OpenGL || defined R_OpenGL)
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	if (FAILED(InitWindow(hInstance, nCmdShow))) {
		return 0;
	}

    if( FAILED( InitDevice() ) ) {
        CleanupDevice();
        return 0;
    }

//#elif (defined D_DirectX || defined R_DirectX)
    // Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message ) {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else {
            Render();
        }
    }

    CleanupDevice();

    return ( int )msg.wParam;
//#endif
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow ) {
#if(defined D_DirectX || defined R_Directx)
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"TutorialWindowClass";
    wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
	if (!RegisterClassEx(&wcex)) {
		return E_FAIL;
	}
    // Create window
    g_hInst = hInstance;
    RECT rc = { 0, 0, 640, 480 };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    g_hWnd = CreateWindow( L"TutorialWindowClass", L"Direct3D 11 Tutorial 7", WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
                           NULL );

	if (!g_hWnd) {
		return E_FAIL;
	}
    ShowWindow( g_hWnd, nCmdShow );

    return S_OK;

#elif (defined D_OpenGL || defined R_OpenGL)
	//Initialize GLFW window
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL GLFW Tutorial 7", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return E_FAIL;
	}
	glfwMakeContextCurrent(window);
	
	return S_OK;
#endif
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
#if (defined D_DirectX || defined R_DirectX)
HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut ) {
#if (defined D_DirectX || R_DirectX)
	HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined D_Directx || defined( DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
    if( FAILED(hr) ) {
		if (pErrorBlob != NULL) {
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		}
		if (pErrorBlob) {
			pErrorBlob->Release();
		}
        return hr;
    }
	if (pErrorBlob) {
		pErrorBlob->Release();
	}
    return S_OK;
#endif
}
#endif

//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice() {
	g_GAPI = new CGraphicsAPI();
#if (defined D_OpenGL || R_OpenGL)
	//if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	//	return -1;
	//}
#endif 

	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef D_DirectX
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif


#if (defined D_DirectX || defined R_DirectX)
	//Initialize SwapChain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = g_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	
	hr = g_GAPI->init(createDeviceFlags, sd);

	if (FAILED(hr)) {
		return hr;
	}
#endif

	// Create a render target view for backBuffer
#if (defined D_DirectX || defined R_DirectX)
	CTexture2D pBackBuffer;
	
	hr = g_GAPI->createRTV(pBackBuffer, g_pRenderTargetView);
	//pBackBuffer->Release();
	if (FAILED(hr)) {
		return hr;
	}
#endif

	// Create depth stencil texture
#if (defined D_DirectX || defined R_DirectX)
	
	TextureDesc descDepth;
	descDepth.W = width;
	descDepth.H = height;
	descDepth.mipLevels = 1;
	descDepth.arraySize = 1;
	descDepth.format = FORMAT_D24_UNORM_S8_UINT;
	descDepth.sampleDesc.count = 1;
	descDepth.sampleDesc.quality = 0;
	descDepth.usage = USAGE_DEFAULT;
	descDepth.flags = 64;
	descDepth.cpuAccessFlags = 0;
	descDepth.miscFlags = 0;

	//g_pDepthStencil.setDesc(descDepth);

	hr = g_GAPI->createTex2D(descDepth, g_pDepthStencil);
	if (FAILED(hr)) {
		return hr;
	}
#endif 

	// Create the depth stencil view
#if (defined D_DirectX || defined R_DirectX)
	//D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	//ZeroMemory(&descDSV, sizeof(descDSV));
	//descDSV.Format = descDepth.Format;
	//descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//descDSV.Texture2D.MipSlice = 0;
	DepthStencilViewDesc descDSV;
	descDSV.format = descDepth.format;
	descDSV.viewDimension = DSV_DIMENSION_TEXTURE2D;
	descDSV.texture2D.mipSlice = 0;
	hr = g_GAPI->createDSV(g_pDepthStencil, descDSV, g_pDepthStencilView);
	if (FAILED(hr)) {
		return hr;
	}
	g_GAPI->setRTargets(1, g_pRenderTargetView, g_pDepthStencilView);

#endif

	// Setup the viewport
#if (defined D_DirectX || defined R_DirectX)
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_GAPI->setVPort(vp);
#endif

	// Compile the vertex shader
#if (defined D_DirectX || defined R_DirectX)
	ID3DBlob* pVSBlob = NULL;
	hr = CompileShaderFromFile(L"Tutorial07.fx", "VS", "vs_4_0", &pVSBlob);
	if (FAILED(hr)) {
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}
#endif

	// Create the vertex shader
#if (defined D_DirectX || defined R_DirectX)
	hr = g_GAPI->createVS(pVSBlob, NULL, g_pVertexShader);
	if (FAILED(hr)) {
		pVSBlob->Release();
		return hr;
	}
#endif

	// Define the input layout
#if (defined D_DirectX || defined R_DirectX)
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
#endif

	// Create the input layout
#if (defined D_DirectX || defined R_DirectX)
	hr = g_GAPI->createIL(layout, numElements, pVSBlob, g_pVertexLayout);
	pVSBlob->Release();
	if (FAILED(hr)) {
		return hr;
	}
#endif

	// Set the input layout
#if (defined D_DirectX || defined R_DirectX)
	//g_pImmediateContext->IASetInputLayout(g_pVertexLayout);
	g_GAPI->setIL(g_pVertexLayout);
#endif

	// Compile the pixel shader
#if (defined D_DirectX || defined R_DirectX)
	ID3DBlob* pPSBlob = NULL;
	hr = CompileShaderFromFile(L"Tutorial07.fx", "PS", "ps_4_0", &pPSBlob);
	if (FAILED(hr)) {
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}
#endif

	// Create the pixel shader
#if (defined D_DirectX || defined R_DirectX)
	//hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);
	hr = g_GAPI->createPS(pPSBlob, NULL, g_pPixelShader);
	pPSBlob->Release();
	if (FAILED(hr)) {
		return hr;
	}
#endif

	// Create vertex buffer
#if (defined D_DirectX || defined R_DirectX)
	SimpleVertex vertices[] = {
		{ vec3(-1.0f, 1.0f, -1.0f), vec2(0.0f, 0.0f) },
		{ vec3(1.0f, 1.0f, -1.0f), vec2(1.0f, 0.0f) },
		{ vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f) },
		{ vec3(-1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f) },

		{ vec3(-1.0f, -1.0f, -1.0f), vec2(0.0f, 0.0f) },
		{ vec3(1.0f, -1.0f, -1.0f), vec2(1.0f, 0.0f) },
		{ vec3(1.0f, -1.0f, 1.0f), vec2(1.0f, 1.0f) },
		{ vec3(-1.0f, -1.0f, 1.0f), vec2(0.0f, 1.0f) },

		{ vec3(-1.0f, -1.0f, 1.0f), vec2(0.0f, 0.0f) },
		{ vec3(-1.0f, -1.0f, -1.0f), vec2(1.0f, 0.0f) },
		{ vec3(-1.0f, 1.0f, -1.0f), vec2(1.0f, 1.0f) },
		{ vec3(-1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f) },

		{ vec3(1.0f, -1.0f, 1.0f), vec2(0.0f, 0.0f) },
		{ vec3(1.0f, -1.0f, -1.0f), vec2(1.0f, 0.0f) },
		{ vec3(1.0f, 1.0f, -1.0f), vec2(1.0f, 1.0f) },
		{ vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f) },

		{ vec3(-1.0f, -1.0f, -1.0f), vec2(0.0f, 0.0f) },
		{ vec3(1.0f, -1.0f, -1.0f), vec2(1.0f, 0.0f) },
		{ vec3(1.0f, 1.0f, -1.0f), vec2(1.0f, 1.0f) },
		{ vec3(-1.0f, 1.0f, -1.0f), vec2(0.0f, 1.0f) },

		{ vec3(-1.0f, -1.0f, 1.0f), vec2(0.0f, 0.0f) },
		{ vec3(1.0f, -1.0f, 1.0f), vec2(1.0f, 0.0f) },
		{ vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f) },
		{ vec3(-1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f) },
	};

		
	BufferDesc desc;
	desc.usage = D3D11_USAGE_DEFAULT;
	desc.byteWidth = sizeof(SimpleVertex) * 24;
	desc.bindFlags = 1;
	desc.cpuAccessFlags = 0;
	desc.SRD.psysMem = vertices;

	//hr = g_pVertexBuffer.setDesc(desc);		//Directo al GAPI
	hr = g_GAPI->createBuffer(g_pVertexBuffer, desc);
#endif

	// Set vertex buffer
#if (defined D_DirectX || defined R_DirectX)
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	//g_pImmediateContext->IASetVertexBuffers( 0, 1, &g_pVertexBuffer.m_Buffer, &stride, &offset );
	g_GAPI->setVBuffer(0, 1, g_pVertexBuffer);
	if (FAILED(hr)) {
		return hr;
	}
#endif


	// Create index buffer
	// Create vertex buffer
#if (defined D_DirectX || defined R_DirectX)
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

	
	desc.usage = 0; //D3D11_USAGE_DEFAULT
	desc.byteWidth = sizeof(WORD) * 36;
	desc.bindFlags = 2; //D3D11_BIND_INDEX_BUFFER
	desc.cpuAccessFlags = 0;
	desc.SRD.psysMem = indices;
	//hr = g_pIndexBuffer.setDesc(desc);
	hr = g_GAPI->createBuffer(g_pIndexBuffer, desc);
	if (FAILED(hr)) {
		return hr;
	}
#endif

	// Set index buffer
#if (defined D_DirectX || defined R_DirectX) 
	g_GAPI->setIBuffer(DXGI_FORMAT_R16_UINT, &g_pIndexBuffer);
#endif

	// Set primitive topology
#if (defined D_DirectX || defined R_DirectX)
	g_GAPI->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
#endif

	// Create the constant buffers
#if (defined D_DirectX || defined R_DirectX)
	desc.usage = 0; //D3D11_USAGE_DEFAULT
	desc.byteWidth = sizeof(CBNeverChanges);
	desc.bindFlags = 0x4L;//4; //D3D11_BIND_CONSTANT_BUFFER
	desc.cpuAccessFlags = 0;
	desc.SRD.psysMem = nullptr;
	//g_pCBNeverChanges.setDesc(desc);
	hr = g_GAPI->createBuffer(g_pCBNeverChanges, desc);
	if (FAILED(hr)) {
		return hr;
	}

	desc.byteWidth = sizeof(CBChangeOnResize);
	//hr = g_pCBChangeOnResize.setDesc(desc);

	hr = g_GAPI->createBuffer(g_pCBChangeOnResize, desc);
	if (FAILED(hr)) {
		return hr;
	}

	desc.byteWidth = sizeof(CBChangesEveryFrame);
	//hr = g_pCBChangesEveryFrame.setDesc(desc);

	hr = g_GAPI->createBuffer(g_pCBChangesEveryFrame, desc);
	if (FAILED(hr)) {
		return hr;
	}
#endif


	// Load the Texture
#if (defined D_DirectX || defined R_DirectX)
	hr = D3DX11CreateShaderResourceViewFromFile(g_GAPI->getDev(), L"seafloor.dds", NULL, NULL, &g_pTextureRV, NULL);
	if (FAILED(hr)) {
		return hr;
	}
#endif

    // Create the sample state
#if (defined D_DirectX || defined R_DirectX)
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory( &sampDesc, sizeof(sampDesc) );
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = g_GAPI->createSState(sampDesc, g_pSamplerLinear);
	if (FAILED(hr)) {
		return hr;
	}
#endif

    // Initialize the world matrices
#if (defined D_DirectX || defined R_DirectX)
    g_World = mat4(1);


    // Initialize the view matrix
    vec3 Eye( 0.0f, 3.0f, -6.0f );
    vec3 At( 0.0f, 1.0f, 0.0f );
    vec3 Up( 0.0f, 1.0f, 0.0f );
    //g_View = XMMatrixLookAtLH( Eye, At, Up );
	g_View = lookAtLH(Eye, At, Up);

    CBNeverChanges cbNeverChanges;
    cbNeverChanges.mView = transpose( g_View );
    g_GAPI->updateBuffer(&cbNeverChanges, g_pCBNeverChanges);


    // Initialize the projection matrix
    //g_Projection = XMMatrixPerspectiveFovLH( XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f );
	g_Projection = perspectiveFovLH(0.785398163f, (float)width, (float)height, 0.01f, 100.0f);
    CBChangeOnResize cbChangesOnResize;
    cbChangesOnResize.mProjection = transpose( g_Projection );
    g_GAPI->updateBuffer(&cbChangesOnResize,  g_pCBChangeOnResize);
#endif
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice() {
    //if( g_pImmediateContext ) g_pImmediateContext->ClearState();
#if(defined D_DirectX || defined R_DirectX)
    if( g_pSamplerLinear ) g_pSamplerLinear->Release();
    if( g_pTextureRV ) g_pTextureRV->Release();
    if( g_pVertexLayout ) g_pVertexLayout->Release();
    if( g_pVertexShader ) g_pVertexShader->Release();
    if( g_pPixelShader ) g_pPixelShader->Release();
    //if( g_pDepthStencil ) g_pDepthStencil->Release();
    //if( g_pDepthStencilView ) g_pDepthStencilView->Release();
    //if( g_pRenderTargetView ) g_pRenderTargetView->Release();
#elif(defined D_OpenGL|| defined R_OpenGL)
	glfwTerminate();
#endif
    
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message ) {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render() {
#if (defined D_DirectX || defined R_DirectX)
    // Update our time
    //static float t = 0.0f;
    float t = 0.0f;
    if( g_GAPI->getDriverType() == D3D_DRIVER_TYPE_REFERENCE ) {
        t += ( float )XM_PI * 0.0125f;
    }
    else {
        static DWORD dwTimeStart = 0;
        DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0) {
			dwTimeStart = dwTimeCur;
		}
        t = ( dwTimeCur - dwTimeStart ) / 1000.0f;
    }

    // Rotate cube around the origin
    //g_World = XMMatrixRotationY( t );
	rotate(g_World, t, vec3());
    // Modify the color
    g_vMeshColor.x = ( sinf( t * 1.0f ) + 1.0f ) * 0.5f;
    g_vMeshColor.y = ( cosf( t * 3.0f ) + 1.0f ) * 0.5f;
    g_vMeshColor.z = ( sinf( t * 5.0f ) + 1.0f ) * 0.5f;

    //
    // Clear the back buffer
    //
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
	g_GAPI->clearRTV(g_pRenderTargetView, ClearColor);
    //
    // Clear the depth buffer to 1.0 (max depth)
    //
    g_GAPI->clearDSV(g_pDepthStencilView, D3D11_CLEAR_DEPTH);
    //
    // Update variables that change once per frame
    //
    CBChangesEveryFrame cb;
    cb.mWorld = transpose( g_World );
    cb.vMeshColor = g_vMeshColor;
    g_GAPI->updateBuffer(&cb, g_pCBChangesEveryFrame);
	

    //
    // Render the cube
    //
   	g_GAPI->setShaders(g_pVertexShader, g_pPixelShader);
	g_GAPI->setConstBuffer(0, false, g_pCBNeverChanges);
	g_GAPI->setConstBuffer(1, false, g_pCBChangeOnResize);
	g_GAPI->setConstBuffer(2, true, g_pCBChangeOnResize);
	g_GAPI->setSResource(g_pTextureRV);
	g_GAPI->setSampler(g_pSamplerLinear);
	g_GAPI->draw(36);


    //
    // Present our back buffer to our front buffer
    //
    g_GAPI->show();
#elif (defined D_OpenGL || R_OpenGL)
	//glfwSwapBuffers(window);
	//glfwPollEvents();
	////Bind to Framebuffer and draw inactive camera
	//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	////Clear FBO content and set background color
	//glClearColor(0.f, 0.f, 0.5f, 1.f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	////Use linked shader
	//glUseProgram(shaderProgram);
#endif
}
