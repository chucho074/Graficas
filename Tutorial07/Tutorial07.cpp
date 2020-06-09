//--------------------------------------------------------------------------------------
// File: Tutorial07.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "resource.h"
#include "CCameraFP.h"
#include "CGraphicsAPI.h"
#include "amgui/imgui.h"

#include "CResource.h"
#include <iostream>

#ifdef OPENGL
#include "amgui/imgui_impl_glfw.h"
#include "amgui/imgui_impl_opengl3.h"
#include "CModel.h"
#elif D_DIRECTX
#include "amgui/imgui_impl_dx11.h"
#include "amgui/imgui_impl_win32.h"
#include "CModel.h"
#endif 
#define FIRSTW 800.f
#define FIRSTH 600.f



extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE                           g_hInst = NULL;
HWND                                g_hWnd = NULL;
#ifdef D_DIRECTX
ID3D11ShaderResourceView*           g_pTextureRV = NULL;
ID3D11ShaderResourceView*           InactiveSRV = NULL;
#endif
glm::vec4							g_MeshColor { 0.0f, 0.8f, 0.1f, 1.0f };
CCamera								Camera;
CCameraFP							FirstPerson;
CTexture2D							InactiveCameraTexture;
CDepthStencilView					DepthStencilViewFP;
CRenderTargetView					SecondRTV;
glm::mat4							g_World;
FEATURE_LEVEL						featureLevel = FEATURE_LEVEL_11_0;
CGraphicsAPI						g_GAPI;
CBuffer								g_VertexBuffer;
CBuffer								g_IndexBuffer;
CTexture2D							g_DepthStencil;
CDepthStencilView					DepthStencilViewFree;
CVertexShader						g_VertexShader;
CPixelShader						g_PixelShader;
CRenderTargetView					g_RenderTargetView;
CSamplerState						g_SamplerState;
CCamera *							ActiveCamera = NULL;
CCamera *							InactiveCamera = NULL;
unsigned int						imguiWindowW;
unsigned int						imguiWindowH;
CBuffer								g_BoardVB;
CBuffer								g_BoardIB;

glm::vec3 boardpos(-5, 1, 0);

#ifdef D_DIRECTX

//CResource						graphicApi;
//CSceneManager						SCManager;
#elif OPENGL
unsigned int framebuffer;
unsigned int textureColorbuffer;
unsigned int rbo;
#endif 

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
#ifdef D_DIRECTX
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void Render();


#elif OPENGL
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aNormal;\n"
"layout(location = 2) in vec2 aTexCoords;\n"

"out vec2 TexCoords;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
	"gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
	"TexCoords = aTexCoords;\n"
"}\n";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoords;\n"
"uniform sampler2D texture_diffuse1;\n"
"void main()\n"
"{\n"
	"FragColor = texture(texture_diffuse1, TexCoords);\n"
"}\n;";

void framebuffer_size_callback(GLFWwindow* window, int width, int heigth) {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, width, heigth);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, width, heigth);

	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, heigth, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, heigth);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	InactiveCamera->setWidth(width);
	InactiveCamera->setHeigth(heigth);
	ActiveCamera->setWidth(width);
	ActiveCamera->setHeigth(heigth);
	InactiveCamera->updatePM();
	ActiveCamera->updatePM();
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	imguiWindowW = width;
	imguiWindowH = heigth;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//Close app
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	//Key presses
	if (action == GLFW_PRESS) {
		ActiveCamera->getKeyPress(key);
	}
	//Key release
	if (action == GLFW_RELEASE) {
		ActiveCamera->getKeyRelease(key);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			ActiveCamera->InitPos = { xpos, ypos, 0.f };
			ActiveCamera->mIsClicked = true;
		}
		else if (action == GLFW_RELEASE){
			ActiveCamera->mIsClicked = false;
		}
	}
}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos) {
	if (ActiveCamera->mIsClicked) {
		ActiveCamera->EndPos = { xpos, ypos, 0.f };
		glfwSetCursorPos(window, ActiveCamera->InitPos.x, ActiveCamera->InitPos.y);
		ActiveCamera->mDir = ActiveCamera->InitPos - ActiveCamera->EndPos;
		ActiveCamera->rotate(ActiveCamera->mDir);
	}
}

#endif


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef D_DIRECTX
	if (FAILED(InitWindow(hInstance, nCmdShow)))
		return 0;

	if (FAILED(InitDevice())) {
		CleanupDevice();
		return 0;
	}

	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			ImVec2 ImgDimension(imguiWindowW / 5, imguiWindowH / 5);

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			ImGui::Begin("Inactive Camera", nullptr, 8); {
				ImGui::SetWindowSize(ImVec2(0, 0));

				ImGui::Image(InactiveSRV, ImgDimension);

				ImGui::GetIO().FontGlobalScale;
				if (ImGui::Button("Change")) {
					CCamera * temp = InactiveCamera;
					InactiveCamera = ActiveCamera;
					ActiveCamera = temp;
				}
			}
			ImGui::End();
			Render();
		}
	}
	CleanupDevice();
	return (int)msg.wParam;
#elif OPENGL

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Tutorial 07", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	//Callbacks set
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_move_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	glEnable(GL_DEPTH_TEST);
	//Vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//VS error check
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	}
	//Pixel Shader
	int pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(pixelShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(pixelShader);
	//PS error check
	glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(pixelShader, 512, NULL, infoLog);
	}
	//Link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, pixelShader);
	glLinkProgram(shaderProgram);
	//Linking error check
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(pixelShader);

	DescCamera MyDesc;
	MyDesc.Pos = { 0.f, 0.f, 3.f };
	MyDesc.LAt = { 0.f, 0.f, 0.f };
	MyDesc.Up_desc = { 0.f, 1.f, 0.f };
	MyDesc.FOV = PIDIV4;
	MyDesc.Width = 800;
	MyDesc.Height = 600;
	MyDesc.Near = 0.01f;
	MyDesc.FarPlane = 100.f;

	Camera.init(MyDesc);
	FirstPerson.init(MyDesc);

	ActiveCamera = &Camera;
	InactiveCamera = &FirstPerson;

	CModel nano("Models/Scene/Scene.fbx");

	//Framebuffer configuration
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	//Create a color attachment texture	
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FIRSTW, FIRSTH, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	//Create a RenderBufferObject for depth and stencil attachment	
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, FIRSTW, FIRSTH);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	//Check for errors
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		return -1;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	imguiWindowH = FIRSTH;
	imguiWindowW = FIRSTW;

	float vertices[] = {
		// positions         // texture coords
		 1.f,  1.f, 0.0f,  0.0f, 0.0f, // top right
		 1.f, -1.f, 0.0f,  0.0f, 1.0f, // bottom right
		-1.f, -1.f, 0.0f,  1.0f, 1.0f, // bottom left
		-1.f,  1.f, 0.0f,  1.0f, 0.0f  // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	glm::vec3 boardpos(-5,1,0);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		//Update
		if (ActiveCamera->mForward || ActiveCamera->mBack || ActiveCamera->mLeft || ActiveCamera->mRight || ActiveCamera->mUp || ActiveCamera->mDown) {
			ActiveCamera->move();
		}
		if (ActiveCamera->mRotateLeft || ActiveCamera->mRotateRight) {
			ActiveCamera->rotate();
		}

		//Render
		//Bind to Framebuffer and draw inactive camera
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		//Clear FBO content and set background color
		glClearColor(0.f, 0.f, 0.5f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Use linked shader
		glUseProgram(shaderProgram);
		//Create matrix for 3D rendering
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		//glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 view = glm::transpose(InactiveCamera->getVM());
		//glm::mat4 projection = glm::mat4(1.0f);

		glm::mat4 projection = glm::scale(InactiveCamera->getPM(), glm::vec3(1, -1, 1));

		//model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		
		//Get uniforms from shader
		unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
		unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
		unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
		
		// pass them to the shaders (3 different ways)
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

		//Draw models
		nano.Draw(shaderProgram);
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.f, 0.0f, 0.5f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec3 boardLook = glm::normalize(ActiveCamera->getPos() - boardpos);
		glm::vec3 boardRight = glm::cross(glm::normalize(ActiveCamera->Up), boardLook);
		glm::vec3 boardUp = glm::cross(boardLook, boardRight);

		glm::mat4 boarMat(boardRight.x, boardRight.y, boardRight.z, 0, boardUp.x, boardUp.y, boardUp.z, 0, boardLook.x, boardLook.y, boardLook.z, 0, boardpos.x, boardpos.y, boardpos.z, 1);

		model = glm::mat4(1.0f);
		view = glm::transpose(ActiveCamera->getVM());
		projection = ActiveCamera->getPM();

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

		nano.Draw(shaderProgram);
		glBindVertexArray(VAO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		model = boarMat;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
		
		/*unsigned int location = glGetUniformLocation(shaderProgram, "texture_diffuse1");
		glUniform1i(location, 0);*/

		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		//Draw ImGui elements
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Inactive Camera", nullptr, 8); {
			ImGui::SetWindowSize(ImVec2(0,0));
			ImGui::Image((void*)textureColorbuffer, ImVec2(imguiWindowW / 4, imguiWindowH / 4));
			if (ImGui::Button("Change Camera")) {
				CCamera * temp = ActiveCamera;
				ActiveCamera = InactiveCamera;
				InactiveCamera = temp;
			}
		}
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);		
	}
	//Free resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
#endif   
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow ) {
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
#ifdef D_DIRECTX
    wcex.lpfnWndProc = WndProc;
#endif
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
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
//#ifdef D_DIRECTX
//HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut ) {
//    HRESULT hr = S_OK;
//
//    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
//
//    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
//    // Setting this flag improves the shader debugging experience, but still allows 
//    // the shaders to be optimized and to run exactly the way they will run in 
//    // the release configuration of this program.
//    dwShaderFlags |= D3DCOMPILE_DEBUG;
//
//
//    ID3DBlob* pErrorBlob;
//    hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
//        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
//    if( FAILED(hr) ) {
//		if (pErrorBlob != NULL) {
//			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
//		}
//		if (pErrorBlob) {
//			pErrorBlob->Release();
//		}
//        return hr;
//    }
//	if (pErrorBlob) {
//		pErrorBlob->Release();
//	}
//
//    return S_OK;
//}
//#endif

//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice() {
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	unsigned int width = imguiWindowW = rc.right - rc.left;
	unsigned int height = imguiWindowH = rc.bottom - rc.top;

#ifdef D_DIRECTX
	DeviceDesc T;
	
	T.DeviceFlags = 0;
#ifdef D_DIRECTX
	T.DeviceFlags |= 2;
#endif 

	T.DriverTypes[0] = DRIVER_TYPE_HARDWARE;
	T.DriverTypes[1] = DRIVER_TYPE_WARP;
	T.DriverTypes[2] = DRIVER_TYPE_REFERENCE;

	T.FeatureLevels[0] = FEATURE_LEVEL_11_0;
	T.FeatureLevels[1] = FEATURE_LEVEL_10_1;
	T.FeatureLevels[2] = FEATURE_LEVEL_10_0;

	T.numFeatureLevels = ARRAYSIZE(T.FeatureLevels);

	unsigned int numDriverTypes = ARRAYSIZE(T.DriverTypes);

	//g_pDevice->init(T);

	SwapChainDesc S;

	S.bufferCount = 1;
	S.W = width;
	S.H = height;
	S.format = FORMAT_R8G8B8A8_UNORM;
	S.refreshNumerator = 60;
	S.refreshDenominator = 1;
	S.bufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	S.outputWND = (unsigned int)g_hWnd;
	S.count = 1;
	S.quality = 0;
	S.windowed = TRUE;

	g_GAPI.init(T, S);

	for (unsigned int driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
		g_GAPI.setDriverType(driverTypeIndex);
		hr = g_GAPI.createDevnSC(featureLevel);
		if (SUCCEEDED(hr)) {
			break;
		}
	}

	if (FAILED(hr)) {
		return hr;
	}
	// Create a render target view
	CTexture2D BackBuffer;
	hr = g_GAPI.createRTV(BackBuffer, g_RenderTargetView);
	BackBuffer.m_Texture->Release();
	if (FAILED(hr)) {
		return hr;
	}

	// Create depth stencil texture
	TextureDesc DepthDesc;
	DepthDesc.W = width;
	DepthDesc.H = height;
	DepthDesc.mipLevels = 1;
	DepthDesc.arraySize = 1;
	DepthDesc.format = FORMAT_D24_UNORM_S8_UINT;
	DepthDesc.sampleDesc.count = 1;
	DepthDesc.sampleDesc.quality = 0;
	DepthDesc.usage = USAGE_DEFAULT;
	DepthDesc.flags = 64;				//D3D11_BIND_DEPTH_STENCIL;
	DepthDesc.cpuAccessFlags = 0;
	DepthDesc.miscFlags = 0;

	g_DepthStencil.init(DepthDesc);

	hr = g_GAPI.createTexture(g_DepthStencil);
	if (FAILED(hr)) {
		return hr;
	}
	// Create the depth stencil view
	DepthStencilViewDesc DSV;
	DSV.format = g_DepthStencil.m_Data.format;
	DSV.viewDimension = DSV_DIMENSION_TEXTURE2D;
	DSV.texture2D.mipSlice = 0;

	DepthStencilViewFree.init(DSV, (FORMAT)g_DepthStencil.m_Desc.Format);

	hr = g_GAPI.createDSV(g_DepthStencil, DepthStencilViewFree);
	if (FAILED(hr)) {
		return hr;
	}

	// Setup the viewport
	ViewPortDesc vpStruct;
	vpStruct.W = width;
	vpStruct.H = height;
	vpStruct.minDepth = 0.0f;
	vpStruct.maxDepth = 1.0f;
	vpStruct.topLeftX = 0;
	vpStruct.topLeftY = 0;

	g_GAPI.createVPort(vpStruct);

	// Compile the vertex shader
	// Create the vertex shader
	hr = g_GAPI.createVShader(g_VertexShader);
	if (FAILED(hr)) {
		return hr;
	}

	//Create input layout from compiled VS
	// Set the input layout
	hr = g_GAPI.createILayout(g_VertexShader);
	if (FAILED(hr)) {
		return hr;
	}
	

	// Compile the pixel shader
	// Create the pixel shader
	hr = g_GAPI.createPShader(g_PixelShader);
	if (FAILED(hr)) {
		return hr;
	}

	// Create vertex buffer
	SimpleVertex vertices[] = {
		{ glm::vec3(-1.0f, 1.0f, -1.0f),	glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, -1.0f),		glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, 1.0f),		glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, -1.0f),	glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, -1.0f),	glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, 1.0f),		glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, -1.0f, 1.0f),	glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, 1.0f),	glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(-1.0f, -1.0f, -1.0f),	glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(-1.0f, 1.0f, -1.0f),	glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, 1.0f),		glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(1.0f, -1.0f, 1.0f),		glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, -1.0f),	glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, -1.0f),		glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, -1.0f),	glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, -1.0f),	glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, -1.0f),		glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, -1.0f),	glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, 1.0f),	glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, 1.0f),		glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, 1.0f),		glm::vec2(0.0f, 1.0f) },
	};



	BufferDesc bufferstrct;
	bufferstrct.usage = USAGE_DEFAULT;
	bufferstrct.byteWidth = sizeof(SimpleVertex) * 24;
	bufferstrct.bindFlags = 1;			// D3D11_BIND_VERTEX_BUFFER;
	bufferstrct.cpuAccessFlags = 0;
	
	SubresourceData subrsrcData;
	subrsrcData.psysMem = vertices;
	g_VertexBuffer.init(subrsrcData, bufferstrct);

	
	hr = g_GAPI.createBuffer(g_VertexBuffer, true);
	if (FAILED(hr)) {
		return hr;
	}

    // Set vertex buffer
	g_GAPI.setVBuffer(g_VertexBuffer);

    // Create index buffer
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

	bufferstrct.usage = USAGE_DEFAULT;
	bufferstrct.byteWidth = sizeof( WORD ) * 36;
	bufferstrct.bindFlags = 2;		// D3D11_BIND_INDEX_BUFFER;
	bufferstrct.cpuAccessFlags = 0;

	subrsrcData.psysMem = indices;
	g_IndexBuffer.init(subrsrcData, bufferstrct);

    hr = g_GAPI.createBuffer(g_IndexBuffer, true);
	if (FAILED(hr)) {
		return hr;
	}

    // Set index buffer
	g_GAPI.setIBuffer(g_IndexBuffer);

	//Create billboard VertexBuffer
	SimpleVertex boardVertex[] = {
		{glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 0.f)},
		{glm::vec3(1.f, -1.f, 0.f),		glm::vec2(1.f, 1.f)},
		{glm::vec3(-1.f, -1.f, 0.f),	glm::vec2(0.f, 1.f)},
		{glm::vec3(-1.f, 1.f, 0.f),		glm::vec2(0.f, 0.f)}

	};

	bufferstrct.usage = USAGE_DEFAULT;
	bufferstrct.byteWidth = sizeof(SimpleVertex) * 4;
	bufferstrct.bindFlags = 1;
	bufferstrct.cpuAccessFlags = 0;

	subrsrcData.psysMem = boardVertex;
	g_BoardVB.init(subrsrcData, bufferstrct);

	hr = g_GAPI.createBuffer(g_BoardVB, true);
	if (FAILED(hr)) {
		return hr;
	}

	//Set billboard VB
	g_GAPI.setVBuffer(g_BoardVB);

	//Create billboard IB
	WORD boardIndices[] = {
		3,1,0,
		2,1,3
	};

	bufferstrct.usage = USAGE_DEFAULT;
	bufferstrct.byteWidth = sizeof(WORD) * 6;
	bufferstrct.bindFlags = 2;
	bufferstrct.cpuAccessFlags = 0;
	subrsrcData.psysMem = boardIndices;
	g_BoardIB.init(subrsrcData, bufferstrct);
	
	hr = g_GAPI.createBuffer(g_BoardIB, true);
	if (FAILED(hr)) {
		return hr;
	}

	//Set billboard IB
	g_GAPI.setIBuffer(g_BoardIB);
	g_GAPI.setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Create the constant buffers
	bufferstrct.usage = USAGE_DEFAULT;
	bufferstrct.byteWidth = sizeof(CBNeverChanges);
	bufferstrct.bindFlags = 4;		// D3D11_BIND_CONSTANT_BUFFER;
	bufferstrct.cpuAccessFlags = 0;

	//NeverChanges

	//Free Camera
	Camera.m_CBNeverChanges.init(bufferstrct);
   hr = g_GAPI.createBuffer(Camera.m_CBNeverChanges, false);
	if (FAILED(hr)) {
		return hr;
	}
	//FPS Camera
	FirstPerson.m_CBNeverChanges.init(bufferstrct);
	hr = g_GAPI.createBuffer(FirstPerson.m_CBNeverChanges, false);
	if (FAILED(hr)) {
		return hr;
	}

	//ChangeOnResize
	
	bufferstrct.byteWidth = sizeof(CBChangeOnResize);
	//Free Camera
	Camera.m_CBChangesOnResize.init(bufferstrct);
    hr = g_GAPI.createBuffer(Camera.m_CBChangesOnResize, false);
	if (FAILED(hr)) {
		return hr;
	}
	//FPS Camera
	FirstPerson.m_CBChangesOnResize.init(bufferstrct);
	hr = g_GAPI.createBuffer(FirstPerson.m_CBChangesOnResize, false);
	if (FAILED(hr)) {
		return hr;
	}

	//ChangeEveryFrame
	
	bufferstrct.byteWidth = sizeof(CBChangesEveryFrame);
	//Free Camera
	Camera.m_CBChangesEveryFrame.init(bufferstrct);
	hr = g_GAPI.createBuffer(Camera.m_CBChangesEveryFrame, false);
	if (FAILED(hr)) {
		return hr;
	}
	//FPS Camera
	FirstPerson.m_CBChangesEveryFrame.init(bufferstrct);
	hr = g_GAPI.createBuffer(FirstPerson.m_CBChangesEveryFrame, false);
	if (FAILED(hr)) {
		return hr;
	}

    // Load the Texture 
    hr = g_GAPI.createSRViewFFile(g_pTextureRV);
	if (FAILED(hr)) {
		return hr;
	}

    // Create the sample state
	SamplerDesc samplerDsc;
	ZeroMemory(&samplerDsc, sizeof(samplerDsc));
	samplerDsc.filter = FILTER_MIN_MAG_MIP_LINEAR;
	samplerDsc.addresU = TEXTURE_ADDRESS_WRAP;
	samplerDsc.addresV = TEXTURE_ADDRESS_WRAP;
	samplerDsc.addresW = TEXTURE_ADDRESS_WRAP;
	samplerDsc.comparisonFunc = COMPARISON_NEVER;
	samplerDsc.minLOD = 0;
	samplerDsc.maxLOD = D3D11_FLOAT32_MAX;

	g_SamplerState.init(samplerDsc);

    hr = g_GAPI.createSState(g_SamplerState);
	if (FAILED(hr)) {
		return hr;
	}
#endif
    // Initialize the world matrix
	g_World = glm::mat4(1.0f);

    // Initialize VM and PM of cameras
	DescCamera MyDesc;
	MyDesc.Pos = { 0.f, 5.f, -6.f };
	MyDesc.LAt = { 0.f, 1.f, 0.f };
	MyDesc.Up_desc = { 0.f, 1.f, 0.f };
	MyDesc.FOV = PIDIV4;
	MyDesc.Width = width;
	MyDesc.Height = height;
	MyDesc.Near = 0.01f;
	MyDesc.FarPlane = 100.f;

	Camera.init(MyDesc);
	FirstPerson.init(MyDesc);

	// Set Free Camera VM

    CBNeverChanges cbNeverChanges;
	cbNeverChanges.mView = Camera.getVM();
#ifdef D_DIRECTX
	g_GAPI.updateSResource(Camera.m_CBNeverChanges, &cbNeverChanges);
#endif

	//Set FPS Camera VM
	CBNeverChanges cbNeverChanges2;
	cbNeverChanges2.mView = FirstPerson.getVM();
#ifdef D_DIRECTX
	g_GAPI.updateSResource(FirstPerson.m_CBNeverChanges, &cbNeverChanges2);
#endif

    // Initialize Free Camera PM    
    CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = glm::transpose(Camera.getPM());
#ifdef D_DIRECTX
	g_GAPI.updateSResource(Camera.m_CBChangesOnResize, &cbChangesOnResize);
#endif

	//Initialize FPS Camera PM
	CBChangeOnResize cbChangesOnResize2;
	cbChangesOnResize2.mProjection = glm::transpose(FirstPerson.getPM());
#ifdef D_DIRECTX
	g_GAPI.updateSResource(FirstPerson.m_CBChangesOnResize, &cbChangesOnResize2);
#endif

	//Initialize texture, SRV and RTV for inactive camera

	//Texture
	TextureDesc D;
	ZeroMemory(&D, sizeof(D));
	D.W = width;
	D.H = height;
	D.mipLevels = D.arraySize = 1;
	D.format = FORMAT_R8G8B8A8_UNORM;
	D.sampleDesc.count = 1;
	D.usage = USAGE_DEFAULT;
	D.flags = 8 | 32;		//D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	D.cpuAccessFlags = 65536;//D3D11_CPU_ACCESS_WRITE;
	D.miscFlags = 0;

	InactiveCameraTexture.init(D);
#ifdef D_DIRECTX
	hr = g_GAPI.createTexture(InactiveCameraTexture);
	if (FAILED(hr)) {
		return hr;
	}
#endif

	//Render Target View
	RenderTargetViewDesc rtDesc;
	rtDesc.format = D.format;
	rtDesc.viewDimension = RTV_DIMENSION_TEXTURE2D;
	rtDesc.texture2D.mipSlice = 0;

	SecondRTV.init(rtDesc);
#ifdef D_DIRECTX
	hr = g_GAPI.createRTV(InactiveCameraTexture, SecondRTV);
	if (FAILED(hr)) {
		return hr;
	}
#endif

#ifdef D_DIRECTX
	D3D11_SHADER_RESOURCE_VIEW_DESC view;
	view.Format = (DXGI_FORMAT)D.format;
	view.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	view.Texture2D.MostDetailedMip = 0;
	view.Texture2D.MipLevels = 1;

	hr = g_GAPI.createSRView(InactiveCameraTexture, view, InactiveSRV);
	if (FAILED(hr)) {
		return hr;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX11_Init(g_GAPI.m_Device.Device, g_GAPI.m_DContx.m_DeviceContext);		//WIP
	ImGui::StyleColorsDark();

	//graphicApi.loadMesh("Models/Scene/Reflect.fbx", &SCManager, graphicApi.m_Model, g_DeviceContext, graphicApi.m_Importer, g_pDevice);

#endif

	//Set active and inactive camera
	ActiveCamera = &Camera;
	InactiveCamera = &FirstPerson;

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice() {
#ifdef D_DIRECTX
    if( g_GAPI.m_DContx.m_DeviceContext)			{ g_GAPI.m_DContx.m_DeviceContext->ClearState();			}	//WIP
    if( g_SamplerState.m_pSamplerLinear )			{ g_SamplerState.m_pSamplerLinear->Release();				}
    if( g_pTextureRV )								{ g_pTextureRV->Release();									}
    if( Camera.m_CBNeverChanges.Buffer )			{ Camera.m_CBNeverChanges.clear();							}
    if( Camera.m_CBChangesOnResize.Buffer )			{ Camera.m_CBChangesOnResize.clear();						}
    if( Camera.m_CBChangesEveryFrame.Buffer )		{ Camera.m_CBChangesEveryFrame.clear();						}
	if( g_VertexBuffer.Buffer)						{ g_VertexBuffer.clear();									}
	if( g_BoardVB.Buffer)							{ g_BoardVB.clear();										}
	if( g_IndexBuffer.Buffer)						{ g_IndexBuffer.clear();									}
	if( g_BoardIB.Buffer)							{ g_BoardIB.clear();										}
    if( g_VertexShader.m_InputLayout )				{ g_VertexShader.m_InputLayout->Release();					}
    if( g_VertexShader.m_VertexShader )				{ g_VertexShader.m_VertexShader->Release();					}
    if( g_PixelShader.m_PixelShader)				{ g_PixelShader.m_PixelShader->Release();					}
    if( g_DepthStencil.m_Texture)					{ g_DepthStencil.m_Texture->Release();						}
    if( DepthStencilViewFree.m_pDepthStencilView )	{ DepthStencilViewFree.m_pDepthStencilView->Release();		}
    if( g_RenderTargetView.m_RTV )					{ g_RenderTargetView.m_RTV->Release();						}
    if( g_GAPI.m_SChain.m_SwapChain)				{ g_GAPI.m_SChain.m_SwapChain->Release();					}	//WIP
	if( FirstPerson.m_CBNeverChanges.Buffer)		{ FirstPerson.m_CBNeverChanges.clear();						}
	if( FirstPerson.m_CBChangesOnResize.Buffer)		{ FirstPerson.m_CBChangesOnResize.clear();					}
	if( FirstPerson.m_CBChangesEveryFrame.Buffer)	{ FirstPerson.m_CBChangesEveryFrame.clear();				}
    if( g_GAPI.m_DContx.m_DeviceContext)			{ g_GAPI.m_DContx.m_DeviceContext->Release();				}	//WIP
	if (g_GAPI.m_Device.Device)						{ g_GAPI.m_Device.Device->Release();						}	//WIP
#endif
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) {
		return true;
	}

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

		case WM_SIZE: {
#ifdef D_DIRECTX
			if (g_GAPI.m_DContx.m_DeviceContext != nullptr) {		
				RECT rc;
				GetClientRect(hWnd, &rc);
				UINT width = imguiWindowW = rc.right - rc.left;
				UINT height = imguiWindowH = rc.bottom - rc.top;
				g_World = glm::mat4(1.0f);
				ActiveCamera->setHeigth(height);
				ActiveCamera->setWidth(width);
				ActiveCamera->updatePM();
				CBChangeOnResize cbChangesOnResize;
				cbChangesOnResize.mProjection = glm::transpose(ActiveCamera->PM);
				g_GAPI.updateSResource(ActiveCamera->m_CBChangesOnResize, &cbChangesOnResize);
				InactiveCamera->setHeigth(height);
				InactiveCamera->setWidth(width);
				InactiveCamera->updatePM();
				cbChangesOnResize.mProjection = glm::transpose(InactiveCamera->PM);
				g_GAPI.updateSResource(InactiveCamera->m_CBChangesOnResize, &cbChangesOnResize);
				if (g_GAPI.m_SChain.m_SwapChain) {							
					HRESULT h;
					InactiveCameraTexture.m_Texture->Release();
					InactiveSRV->Release();
					SecondRTV.m_RTV->Release();
					TextureDesc T;
					ZeroMemory(&T, sizeof(T));
					T.W = width;
					T.H = height;
					T.mipLevels = T.arraySize = 1;
					T.format = FORMAT_R8G8B8A8_UNORM;
					T.sampleDesc.count = 1;
					T.usage = USAGE_DEFAULT;
					T.flags = 8 | 32;
					T.cpuAccessFlags = 65536;
					T.miscFlags = 0;
					InactiveCameraTexture.init(T);

					h = g_GAPI.createTexture(InactiveCameraTexture);
					if (FAILED(h)) {
						return h;
					}

					RenderTargetViewDesc RTV;
					RTV.format = T.format;
					RTV.viewDimension = RTV_DIMENSION_TEXTURE2D;
					RTV.texture1D.mipSlice = 0;
					SecondRTV.init(RTV);
					h = g_GAPI.createRTV(InactiveCameraTexture, SecondRTV);
					if (FAILED(h)) {
						return h;
					}
					D3D11_SHADER_RESOURCE_VIEW_DESC SRV;
					SRV.Format = (DXGI_FORMAT)T.format;
					SRV.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
					SRV.Texture2D.MostDetailedMip = 0;
					SRV.Texture2D.MipLevels = 1;
					h = g_GAPI.createSRView(InactiveCameraTexture, SRV, InactiveSRV);
					g_GAPI.setZeroRTargets();
					g_RenderTargetView.m_RTV->Release();
					h = g_GAPI.resizeBuffers();
					if (FAILED(h)) {
						return h;
					}
					
					CTexture2D tempBack;
					h = g_GAPI.createRTV(tempBack, g_RenderTargetView);
					if (FAILED(h)) {
						return h;
					}
					tempBack.m_Texture->Release();
					g_DepthStencil.m_Texture->Release();

					TextureDesc DepthDesc;
					DepthDesc.W = width;
					DepthDesc.H = height;
					DepthDesc.mipLevels = 1;
					DepthDesc.arraySize = 1;
					DepthDesc.format = FORMAT_D24_UNORM_S8_UINT;
					DepthDesc.sampleDesc.count = 1;
					DepthDesc.sampleDesc.quality = 0;
					DepthDesc.usage = USAGE_DEFAULT;
					DepthDesc.flags = D3D11_BIND_DEPTH_STENCIL;
					DepthDesc.cpuAccessFlags = 0;
					DepthDesc.miscFlags = 0;
					g_DepthStencil.init(DepthDesc);
					h = g_GAPI.createTexture(g_DepthStencil);
					if (FAILED(h)) {
						return h;
					}
					DepthStencilViewDesc DSV;
					DSV.format = g_DepthStencil.m_Data.format;
					DSV.viewDimension = DSV_DIMENSION_TEXTURE2D;
					DSV.texture2D.mipSlice = 0;
					DepthStencilViewFree.m_pDepthStencilView->Release();
					DepthStencilViewFree.init(DSV, (FORMAT)g_DepthStencil.m_Desc.Format);
					h = g_GAPI.createDSV(g_DepthStencil, DepthStencilViewFree);
					if (FAILED(h)) {
						return h;
					}
					g_GAPI.setRTargets(1, g_RenderTargetView, DepthStencilViewFree);
					ViewPortDesc V;
					V.W = width;
					V.H = height;
					V.minDepth = 0.f;
					V.maxDepth = 1.f;
					V.topLeftX = 0;
					V.topLeftY = 0;
					CViewPort ViewP;
					ViewP.init(V);		
					g_GAPI.setVPorts(1, ViewP);
				}
				ImGui::GetStyle().ScaleAllSizes(1);
			}
			
#endif
			break;
		}
		case WM_KEYDOWN:
			ActiveCamera->getKeyPress(wParam);
			break;			
		case WM_KEYUP:
			ActiveCamera->getKeyRelease(wParam);
			break;
		case WM_RBUTTONDOWN:{
			POINT MousePoint;
			GetCursorPos(&MousePoint);
			ActiveCamera->InitPos = {MousePoint.x, MousePoint.y, 0.f};
			ActiveCamera->mIsClicked = true;
			break;
		}
		case WM_MOUSEMOVE: {
			if (ActiveCamera->mIsClicked) {
				POINT EndPoint;
				GetCursorPos(&EndPoint);
				ActiveCamera->EndPos = {EndPoint.x, EndPoint.y, 0.f};
				SetCursorPos(ActiveCamera->InitPos.x, ActiveCamera->InitPos.y);
				ActiveCamera->mDir = ActiveCamera->InitPos - ActiveCamera->EndPos;
				ActiveCamera->rotate(ActiveCamera->mDir);
				CBNeverChanges cbNeverChanges;
				cbNeverChanges.mView = ActiveCamera->getVM();
#ifdef D_DIRECTX
				g_GAPI.updateSResource(ActiveCamera->m_CBNeverChanges, &cbNeverChanges);
#endif
			}
			break;
		}
		case WM_RBUTTONUP:
			ActiveCamera->mIsClicked = false;
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
#ifdef D_DIRECTX
    // Update our time
    static float t = 0.0f;
    if( g_GAPI.m_Device.Desc.DriverType == D3D_DRIVER_TYPE_REFERENCE ) {
        t += ( float )XM_PI * 0.0125f;
    }
    else {
        static DWORD dwTimeStart = 0;
        DWORD dwTimeCur = GetTickCount();
        if( dwTimeStart == 0 )
            dwTimeStart = dwTimeCur;
        t = ( dwTimeCur - dwTimeStart ) / 1000.0f;
    }

	if (ActiveCamera->mForward || ActiveCamera->mBack || ActiveCamera->mLeft || ActiveCamera->mRight || ActiveCamera->mUp || ActiveCamera->mDown || ActiveCamera->mRotateLeft || ActiveCamera->mRotateRight) {
		ActiveCamera->move();
		ActiveCamera->rotate();
		CBNeverChanges cbNeverChanges;
		cbNeverChanges.mView = ActiveCamera->VM;
		g_GAPI.updateSResource(ActiveCamera->m_CBNeverChanges, &cbNeverChanges);
	}

    // Modify the color
	g_MeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
	g_MeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
	g_MeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; 
	g_GAPI.setRTargets(1, SecondRTV, DepthStencilViewFree);

	g_GAPI.clearRTV(SecondRTV, *ClearColor);													//WIP
	g_GAPI.clearDSV(DepthStencilViewFree, D3D11_CLEAR_DEPTH, 1.0f, 0);
	unsigned int stride = sizeof(SimpleVertex);
	unsigned int offset = 0;
	g_GAPI.setVBuffer(g_VertexBuffer);
	g_GAPI.setIBuffer(g_IndexBuffer);
	CBChangesEveryFrame cb;
	g_World = glm::mat4(1.f);
	g_World = glm::translate(g_World,ActiveCamera->getPos());
	cb.mWorld = glm::transpose(g_World);
	cb.vMeshColor = g_MeshColor;
	g_GAPI.updateSResource(InactiveCamera->m_CBChangesEveryFrame, &cb);	

	g_World = glm::mat4(1.f);
	
	cb.mWorld = glm::transpose(g_World);
	cb.vMeshColor = g_MeshColor;
	g_GAPI.updateSResource(InactiveCamera->m_CBChangesEveryFrame, &cb);
					
	g_GAPI.setVShader(g_VertexShader);
	g_GAPI.setCBuffer(0, InactiveCamera->m_CBNeverChanges);
	g_GAPI.setCBuffer(1, InactiveCamera->m_CBChangesOnResize);
	g_GAPI.setCBuffer(2, InactiveCamera->m_CBChangesEveryFrame);
	g_GAPI.setPShader(g_PixelShader);
	g_GAPI.setCBuffer(2, InactiveCamera->m_CBChangesEveryFrame);
	g_GAPI.setSResource(g_pTextureRV);
	g_GAPI.setSampler(g_SamplerState);
	g_GAPI.setDrawIndex(36);

	


	ID3D11ShaderResourceView* temp = NULL;
	g_GAPI.setSResource(temp);																	

	CBChangesEveryFrame cbMesh;
	cbMesh.mWorld = {
		1, 0, 0, ActiveCamera->getPos().x,
		0, 1, 0, ActiveCamera->getPos().y,
		0, 0, 1, ActiveCamera->getPos().z,
		0, 0, 0, 1
	};

	cbMesh.vMeshColor = { 1, 0, 0, 1 };
	g_GAPI.updateSResource(InactiveCamera->m_CBChangesEveryFrame, &cbMesh);
	/*for (int i = 0; i < SCManager.m_MeshList.size(); i++) {
		g_DeviceContext->m_DeviceContext->VSSetConstantBuffers(2, 1, &InactiveCamera->m_CBChangesEveryFrame.Buffer);
		g_DeviceContext->m_DeviceContext->PSSetShaderResources(0, 1, &SCManager.m_MeshList[i]->Materials->m_TextureDiffuse);
		g_DeviceContext->m_DeviceContext->VSSetShaderResources(0, 1, &SCManager.m_MeshList[i]->Materials->m_TextureDiffuse);
		
		g_DeviceContext->m_DeviceContext->IASetVertexBuffers(0, 1, &SCManager.m_MeshList[i]->VB->Buffer, &stride, &offset);
		g_DeviceContext->m_DeviceContext->IASetIndexBuffer(SCManager.m_MeshList[i]->IB->Buffer, DXGI_FORMAT_R16_UINT, 0);
		g_DeviceContext->m_DeviceContext->DrawIndexed(SCManager.m_MeshList[i]->INum, 0, 0);
	}*/

	//Set backbuffer and main DSV
	
	 g_GAPI.setRTargets(1, g_RenderTargetView, DepthStencilViewFree);
	 g_GAPI.clearRTV(g_RenderTargetView, *ClearColor);											//WIP
	 g_GAPI.clearDSV(DepthStencilViewFree, D3D11_CLEAR_DEPTH, 1.0f, 0);
	 g_GAPI.setVBuffer(g_VertexBuffer);
	 g_GAPI.setIBuffer(g_IndexBuffer);


    //
    // Update variables that change once per frame
    //
	
		
	g_World = glm::mat4(1.f);

	cb.mWorld = glm::transpose(g_World);
	cb.vMeshColor = g_MeshColor;
	
	g_GAPI.updateSResource(ActiveCamera->m_CBChangesEveryFrame, &cb);
	g_GAPI.setVShader(g_VertexShader);
	g_GAPI.setCBuffer(0, ActiveCamera->m_CBNeverChanges);
	g_GAPI.setCBuffer(1, ActiveCamera->m_CBChangesOnResize);
	g_GAPI.setCBuffer(2, ActiveCamera->m_CBChangesEveryFrame);
	g_GAPI.setPShader(g_PixelShader);
	g_GAPI.setCBuffer(2, ActiveCamera->m_CBChangesEveryFrame);
	g_GAPI.setSResource(InactiveSRV);
	g_GAPI.setSampler(g_SamplerState);
	g_GAPI.setDrawIndex(36);
	


	temp = NULL;
	g_GAPI.setSResource(temp);

	g_GAPI.setVBuffer(g_BoardVB);
	g_GAPI.setIBuffer(g_BoardIB);

	glm::vec3 boardLook = glm::normalize(ActiveCamera->getPos() - boardpos);
	glm::vec3 boardRight = glm::cross(glm::normalize(ActiveCamera->Up), boardLook);
	glm::vec3 boardUp = glm::cross(boardLook, boardRight);

	glm::mat4 boarMat(boardRight.x, boardRight.y, boardRight.z, 0, boardUp.x, boardUp.y, boardUp.z, 0, boardLook.x, boardLook.y, boardLook.z, 0, boardpos.x, boardpos.y, boardpos.z, 1);

	g_World = boarMat;

	cb.mWorld = glm::transpose(g_World);
	cb.vMeshColor = g_MeshColor;

	g_GAPI.updateSResource(ActiveCamera->m_CBChangesEveryFrame, &cb);
	g_GAPI.setVShader(g_VertexShader);
	g_GAPI.setCBuffer(0, ActiveCamera->m_CBNeverChanges);
	g_GAPI.setCBuffer(1, ActiveCamera->m_CBChangesOnResize);
	g_GAPI.setCBuffer(2, ActiveCamera->m_CBChangesEveryFrame);
	g_GAPI.setPShader(g_PixelShader);
	g_GAPI.setCBuffer(2, ActiveCamera->m_CBChangesEveryFrame);
	g_GAPI.setSResource(InactiveSRV);
	g_GAPI.setSampler(g_SamplerState);
	g_GAPI.setDrawIndex(6);

	temp = NULL;
	g_GAPI.setSResource(temp);

    //
    // Present our back buffer to our front buffer
    //
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	g_GAPI.show();
#endif
}
