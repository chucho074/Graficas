//--------------------------------------------------------------------------------------
// File: Tutorial07.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
/*
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

//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, unsigned int msg, WPARAM wParam, LPARAM lParam);

//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------

HINSTANCE                           g_hInst = NULL;
HWND                                g_hWnd = NULL;
#ifdef D_DIRECTX
ID3D11ShaderResourceView*           g_pTextureRV = NULL;
//ID3D11ShaderResourceView*           InactiveSRV = NULL;
#endif
glm::vec4							g_MeshColor { 0.0f, 0.8f, 0.1f, 1.0f };
CCamera								Camera;
//CCameraFP							FirstPerson;
//CTexture2D							InactiveCameraTexture;
//CDepthStencilView					DepthStencilViewFP;
//CRenderTargetView					SecondRTV;
glm::mat4							g_World;
FEATURE_LEVEL						featureLevel = FEATURE_LEVEL_11_0;
CGraphicsAPI						g_GAPI;
CBuffer								g_VertexBuffer;
CBuffer								g_IndexBuffer;
CTexture2D							g_DepthStencil;
CDepthStencilView					DepthStencilViewFree;
CInputLayout						g_ILayout;
CVertexShader						g_VertexShader;
CPixelShader						g_PixelShader;
CRenderTargetView					g_RenderTargetView;
CSamplerState						g_SamplerState;
//CCamera *							ActiveCamera = NULL;
//CCamera *							InactiveCamera = NULL;
//unsigned int						imguiWindowW;
//unsigned int						imguiWindowH;
//CBuffer								g_BoardVB;
//CBuffer								g_BoardIB;

//glm::vec3 boardpos(-5, 1, 0);

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
LRESULT CALLBACK WndProc(HWND, unsigned int, WPARAM, LPARAM);
void Render();
#endif*/

/*
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
*/

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
/*
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
		
		//unsigned int location = glGetUniformLocation(shaderProgram, "texture_diffuse1");
		//glUniform1i(location, 0);

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

*/

//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
/*
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
*/

//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
/*
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
	DepthDesc.format = FORMAT_D24_UNORM_S8_unsigned int;
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

	hr = g_GAPI.createILayout(g_VertexShader, g_ILayout);
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
*/

//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
/*
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
    if( g_ILayout.m_InputLayout )					{ g_ILayout.m_InputLayout->Release();						}
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
	if( g_GAPI.m_Device.Device)						{ g_GAPI.m_Device.Device->Release();						}	//WIP
#endif
}
*/

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
/*
LRESULT CALLBACK WndProc( HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam ) {
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
				unsigned int width = imguiWindowW = rc.right - rc.left;
				unsigned int height = imguiWindowH = rc.bottom - rc.top;
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
					DepthDesc.format = FORMAT_D24_UNORM_S8_unsigned int;
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
*/


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
/*
void Render() {																				//WIP
#ifdef D_DIRECTX
	// Update our time
	static float t = 0.0f;
	if (g_GAPI.m_Device.Desc.DriverType == D3D_DRIVER_TYPE_REFERENCE) {
		t += (float)XM_PI * 0.0125f;
	}
	else {
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}


	if (ActiveCamera->mForward || ActiveCamera->mBack || ActiveCamera->mLeft || ActiveCamera->mRight || ActiveCamera->mUp || ActiveCamera->mDown || ActiveCamera->mRotateLeft || ActiveCamera->mRotateRight) {
		ActiveCamera->move();
		ActiveCamera->rotate();
		CBNeverChanges cbNeverChanges;
		cbNeverChanges.mView = ActiveCamera->VM;
		g_GAPI.updateSResource(ActiveCamera->m_CBNeverChanges, &cbNeverChanges);
	}

	// Rotate cube around the origin

	// Modify the color
	g_MeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
	g_MeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
	g_MeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

	//
	// Clear the back buffer
	//
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
	g_GAPI.setRTargets(1, SecondRTV, DepthStencilViewFree);

	//
	// Clear the depth buffer to 1.0 (max depth)
	//
	g_GAPI.clearRTV(SecondRTV, *ClearColor);
	g_GAPI.clearDSV(DepthStencilViewFree, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//
	// Update variables that change once per frame
	//
	CBChangesEveryFrame cb;
	g_World = glm::mat4(1.f);
	g_World = glm::translate(g_World, ActiveCamera->getPos());
	cb.mWorld = glm::transpose(g_World);
	cb.vMeshColor = g_MeshColor;
	g_GAPI.updateSResource(InactiveCamera->m_CBChangesEveryFrame, &cb);

	//
	// Render the cube
	//
	g_GAPI.setVShader(g_VertexShader);
	g_GAPI.setCBuffer(0, InactiveCamera->m_CBNeverChanges);
	g_GAPI.setCBuffer(1, InactiveCamera->m_CBChangesOnResize);
	g_GAPI.setCBuffer(2, InactiveCamera->m_CBChangesEveryFrame);
	g_GAPI.setPShader(g_PixelShader);
	g_GAPI.setCBuffer(2, InactiveCamera->m_CBChangesEveryFrame);
	g_GAPI.setSResource(g_pTextureRV);
	g_GAPI.setSampler(g_SamplerState);
	g_GAPI.setDrawIndex(36);

	//
	// Present our back buffer to our front buffer
	//
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	g_GAPI.show();
#endif
}
*/



//--------------------------------------------------------------------------------------//
//										Testing											//
//--------------------------------------------------------------------------------------//

/*
//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

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
			Render();
		}
	}

	CleanupDevice();

	return (int)msg.wParam;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow) {

	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"TutorialWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// Create window
	g_hInst = hInstance;
	RECT rc = { 0, 0, 640, 480 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindow(L"TutorialWindowClass", L"Direct3D 11 Tutorial 7", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL);
	if (!g_hWnd)
		return E_FAIL;

	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut) {
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef D_DIRECTX
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
#endif
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice() {

	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	unsigned int width = rc.right - rc.left;
	unsigned int height = rc.bottom - rc.top;

	
#ifdef D_DIRECTX || R_DIRECTX
	DeviceDesc T;
	T.DeviceFlags = 0;
#ifdef D_DIRECTX
	T.DeviceFlags |= 2;
#endif


	T.DriverTypes[0] = DRIVER_TYPE_HARDWARE;
	T.DriverTypes[1] = DRIVER_TYPE_WARP;
	T.DriverTypes[2] = DRIVER_TYPE_REFERENCE;

	unsigned int numDriverTypes = ARRAYSIZE(T.DriverTypes);
	
	T.FeatureLevels[0] = FEATURE_LEVEL_11_0;
	T.FeatureLevels[1] = FEATURE_LEVEL_10_1;
	T.FeatureLevels[2] = FEATURE_LEVEL_10_0;

	T.numFeatureLevels = ARRAYSIZE(T.FeatureLevels);
	 

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
	
	g_GAPI.init(T,S);

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

	//DepthStencilViewFree.init(DSV, (FORMAT)g_DepthStencil.m_Desc.Format);
	DepthStencilViewFree.init(DSV);
	if (FAILED(hr)) {
		return hr;
	}
	hr = g_GAPI.createDSV(g_DepthStencil, DepthStencilViewFree);

	g_GAPI.setRTargets(1, g_RenderTargetView, DepthStencilViewFree);
	
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
	hr = g_GAPI.createILayout(g_VertexShader, g_ILayout);
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
		{ glm::vec3(-1.0f, 1.0f, -1.0f),		glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, -1.0f),			glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, 1.0f),			glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, 1.0f),			glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, -1.0f),		glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, -1.0f),		glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, 1.0f),			glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, -1.0f, 1.0f),		glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, 1.0f),		glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(-1.0f, -1.0f, -1.0f),		glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(-1.0f, 1.0f, -1.0f),		glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, 1.0f),			glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(1.0f, -1.0f, 1.0f),			glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, -1.0f),		glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, -1.0f),			glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(1.0f, 1.0f, 1.0f),			glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, -1.0f),		glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, -1.0f),		glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, -1.0f),			glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, -1.0f),		glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, 1.0f),		glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, 1.0f),			glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, 1.0f),			glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, 1.0f),			glm::vec2(0.0f, 1.0f) },
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
	g_GAPI.setVBuffer(&g_VertexBuffer);
	
	// Create index buffer
	// Create vertex buffer
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
	bufferstrct.byteWidth = sizeof(WORD) * 36;
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

	// Set primitive topology
	g_GAPI.setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create the constant buffers
	bufferstrct.usage = USAGE_DEFAULT;
	bufferstrct.byteWidth = sizeof(CBNeverChanges);
	bufferstrct.bindFlags = 4;		// D3D11_BIND_CONSTANT_BUFFER;
	bufferstrct.cpuAccessFlags = 0;

	Camera.m_CBNeverChanges.init(bufferstrct);
	hr = g_GAPI.createBuffer(Camera.m_CBNeverChanges, false);
	if (FAILED(hr)) {
		return hr;
	}

	bufferstrct.byteWidth = sizeof(CBChangeOnResize);
	Camera.m_CBChangesOnResize.init(bufferstrct);
	hr = g_GAPI.createBuffer(Camera.m_CBChangesOnResize, false);
	if (FAILED(hr)) {
		return hr;
	}

	bufferstrct.byteWidth = sizeof(CBChangesEveryFrame);
	Camera.m_CBChangesEveryFrame.init(bufferstrct);
	hr = g_GAPI.createBuffer(Camera.m_CBChangesEveryFrame, false);
	if (FAILED(hr)) {
		return hr;
	}

	// Load the Texture
	hr = g_GAPI.createSRViewFFile(&g_pTextureRV);
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
	g_GAPI.createSState(g_SamplerState);

	if (FAILED(hr)) {
		return hr;
	}
#endif
	// Initialize the world matrices
	g_World = glm::mat4(1.0f);

	// Initialize the view matrix
	DescCamera MyDesc;
	MyDesc.Pos = { 0.f, 3.f, -6.f };
	MyDesc.LAt = { 0.f, 1.f, 0.f };
	MyDesc.Up_desc = { 0.f, 1.f, 0.f };
	MyDesc.FOV = PIDIV4;
	MyDesc.Width = width;
	MyDesc.Height = height;
	MyDesc.Near = 0.01f;
	MyDesc.FarPlane = 100.f;

	Camera.init(MyDesc);

	CBNeverChanges cbNeverChanges;
	cbNeverChanges.mView = Camera.getVM();
#ifdef D_DIRECTX
	g_GAPI.updateSResource(Camera.m_CBNeverChanges, &cbNeverChanges);
#endif

	CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = glm::transpose(Camera.getPM());
#ifdef D_DIRECTX
	g_GAPI.updateSResource(Camera.m_CBChangesOnResize, &cbChangesOnResize);
#endif
	
	return S_OK;

}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice() {
	if (g_GAPI.m_DContx.m_DeviceContext)			{ g_GAPI.m_DContx.m_DeviceContext->ClearState(); }
	if (g_SamplerState.m_pSamplerLinear)			{ g_SamplerState.m_pSamplerLinear->Release(); }
	if (g_pTextureRV)								{ g_pTextureRV->Release(); }
	if (Camera.m_CBNeverChanges.Buffer)				{ Camera.m_CBNeverChanges.Buffer->Release(); }
	if (Camera.m_CBChangesOnResize.Buffer)			{ Camera.m_CBChangesOnResize.Buffer->Release(); }
	if (Camera.m_CBChangesEveryFrame.Buffer)		{ Camera.m_CBChangesEveryFrame.Buffer->Release(); }
	if (g_VertexBuffer.Buffer)						{ g_VertexBuffer.Buffer->Release(); }
	if (g_IndexBuffer.Buffer)						{ g_IndexBuffer.Buffer->Release(); }
	if (g_ILayout.m_InputLayout)					{ g_ILayout.m_InputLayout->Release(); }
	if (g_VertexShader.m_VertexShader)				{ g_VertexShader.m_VertexShader->Release(); }
	if (g_PixelShader.m_PixelShader)				{ g_PixelShader.m_PixelShader->Release(); }
	if (g_DepthStencil.m_Texture)					{ g_DepthStencil.m_Texture->Release(); }
	if (DepthStencilViewFree.m_pDepthStencilView)	{ DepthStencilViewFree.m_pDepthStencilView->Release(); }
	if (g_RenderTargetView.m_RTV)					{ g_RenderTargetView.m_RTV->Release(); }
	if (g_GAPI.m_SChain.m_SwapChain)				{ g_GAPI.m_SChain.m_SwapChain->Release(); }
	if (g_GAPI.m_DContx.m_DeviceContext)			{ g_GAPI.m_DContx.m_DeviceContext->Release(); }
	if (g_GAPI.m_Device.Device)						{ g_GAPI.m_Device.Device->Release(); }
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render() {
	// Update our time
	static float t = 0.0f;
	if (g_GAPI.m_Device.Desc.DriverType == D3D_DRIVER_TYPE_REFERENCE) {
		t += (float)XM_PI * 0.0125f;
	}
	else {
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}

	// Rotate cube around the origin
	//g_World = XMMatrixRotationY(t);
	

	// Modify the color
	g_MeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
	g_MeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
	g_MeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

	//
	// Clear the back buffer
	//
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
	g_GAPI.clearRTV(g_RenderTargetView, *ClearColor);

	//
	// Clear the depth buffer to 1.0 (max depth)
	//
	g_GAPI.clearDSV(DepthStencilViewFree, D3D11_CLEAR_DEPTH, 1.0f, 0);
	
	//
	// Update variables that change once per frame
	//
	CBChangesEveryFrame cb;
	cb.mWorld = glm::transpose(g_World);
	cb.vMeshColor = g_MeshColor;
	g_GAPI.updateSResource(Camera.m_CBChangesEveryFrame, &cb);

	//
	// Render the cube
	//
	g_GAPI.setVShader(g_VertexShader);
	g_GAPI.setVCBuffer(0, Camera.m_CBNeverChanges);
	g_GAPI.setVCBuffer(1, Camera.m_CBChangesOnResize);
	g_GAPI.setVCBuffer(2, Camera.m_CBChangesEveryFrame);
	g_GAPI.setPShader(g_PixelShader);
	g_GAPI.setPCBuffer(2, Camera.m_CBChangesEveryFrame);
	g_GAPI.setSResource(g_pTextureRV);
	g_GAPI.setSampler(g_SamplerState);
	g_GAPI.setDrawIndex(36);

	//
	// Present our back buffer to our front buffer
	//
	g_GAPI.show();
}
*/


//--------------------------------------------------------------------------------------
// File: Tutorial07.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"


//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
};

struct CBNeverChanges
{
	XMMATRIX mView;
};

struct CBChangeOnResize
{
	XMMATRIX mProjection;
};

struct CBChangesEveryFrame
{
	XMMATRIX mWorld;
	XMFLOAT4 vMeshColor;
};


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE                           g_hInst = NULL;
HWND                                g_hWnd = NULL;
D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11Device*                       g_pd3dDevice = NULL;
ID3D11DeviceContext*                g_pImmediateContext = NULL;
IDXGISwapChain*                     g_pSwapChain = NULL;
ID3D11RenderTargetView*             g_pRenderTargetView = NULL;
ID3D11Texture2D*                    g_pDepthStencil = NULL;
ID3D11DepthStencilView*             g_pDepthStencilView = NULL;
ID3D11VertexShader*                 g_pVertexShader = NULL;
ID3D11PixelShader*                  g_pPixelShader = NULL;
ID3D11InputLayout*                  g_pVertexLayout = NULL;
ID3D11Buffer*                       g_pVertexBuffer = NULL;
ID3D11Buffer*                       g_pIndexBuffer = NULL;
ID3D11Buffer*                       g_pCBNeverChanges = NULL;
ID3D11Buffer*                       g_pCBChangeOnResize = NULL;
ID3D11Buffer*                       g_pCBChangesEveryFrame = NULL;
ID3D11ShaderResourceView*           g_pTextureRV = NULL;
ID3D11SamplerState*                 g_pSamplerLinear = NULL;
XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);


//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void Render();


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (FAILED(InitWindow(hInstance, nCmdShow)))
		return 0;

	if (FAILED(InitDevice()))
	{
		CleanupDevice();
		return 0;
	}

	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Render();
		}
	}

	CleanupDevice();

	return (int)msg.wParam;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"TutorialWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// Create window
	g_hInst = hInstance;
	RECT rc = { 0, 0, 640, 480 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindow(L"TutorialWindowClass", L"Direct3D 11 Tutorial 7", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL);
	if (!g_hWnd)
		return E_FAIL;

	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

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

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = g_pd3dDevice->CreateTexture2D(&descDepth, NULL, &g_pDepthStencil);
	if (FAILED(hr))
		return hr;

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = g_pd3dDevice->CreateDepthStencilView(g_pDepthStencil, &descDSV, &g_pDepthStencilView);
	if (FAILED(hr))
		return hr;

	g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pImmediateContext->RSSetViewports(1, &vp);

	// Compile the vertex shader
	ID3DBlob* pVSBlob = NULL;
	hr = CompileShaderFromFile(L"Tutorial07.fx", "VS", "vs_4_0", &pVSBlob);
	if (FAILED(hr))
	{
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
	hr = g_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader);
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &g_pVertexLayout);
	pVSBlob->Release();
	if (FAILED(hr))
		return hr;

	// Set the input layout
	g_pImmediateContext->IASetInputLayout(g_pVertexLayout);

	// Compile the pixel shader
	ID3DBlob* pPSBlob = NULL;
	hr = CompileShaderFromFile(L"Tutorial07.fx", "PS", "ps_4_0", &pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);
	pPSBlob->Release();
	if (FAILED(hr))
		return hr;

	// Create vertex buffer
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

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
	if (FAILED(hr))
		return hr;

	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// Create index buffer
	// Create vertex buffer
	WORD indices[] =
	{
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

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 36;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices;
	hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
	if (FAILED(hr))
		return hr;

	// Set index buffer
	g_pImmediateContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology
	g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create the constant buffers
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CBNeverChanges);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = g_pd3dDevice->CreateBuffer(&bd, NULL, &g_pCBNeverChanges);
	if (FAILED(hr))
		return hr;

	bd.ByteWidth = sizeof(CBChangeOnResize);
	hr = g_pd3dDevice->CreateBuffer(&bd, NULL, &g_pCBChangeOnResize);
	if (FAILED(hr))
		return hr;

	bd.ByteWidth = sizeof(CBChangesEveryFrame);
	hr = g_pd3dDevice->CreateBuffer(&bd, NULL, &g_pCBChangesEveryFrame);
	if (FAILED(hr))
		return hr;

	// Load the Texture
	hr = D3DX11CreateShaderResourceViewFromFile(g_pd3dDevice, L"seafloor.dds", NULL, NULL, &g_pTextureRV, NULL);
	if (FAILED(hr))
		return hr;

	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = g_pd3dDevice->CreateSamplerState(&sampDesc, &g_pSamplerLinear);
	if (FAILED(hr))
		return hr;

	// Initialize the world matrices
	g_World = XMMatrixIdentity();

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	g_View = XMMatrixLookAtLH(Eye, At, Up);

	CBNeverChanges cbNeverChanges;
	cbNeverChanges.mView = XMMatrixTranspose(g_View);
	g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);

	// Initialize the projection matrix
	g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);

	CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
	g_pImmediateContext->UpdateSubresource(g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0);

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
	if (g_pImmediateContext) g_pImmediateContext->ClearState();

	if (g_pSamplerLinear) g_pSamplerLinear->Release();
	if (g_pTextureRV) g_pTextureRV->Release();
	if (g_pCBNeverChanges) g_pCBNeverChanges->Release();
	if (g_pCBChangeOnResize) g_pCBChangeOnResize->Release();
	if (g_pCBChangesEveryFrame) g_pCBChangesEveryFrame->Release();
	if (g_pVertexBuffer) g_pVertexBuffer->Release();
	if (g_pIndexBuffer) g_pIndexBuffer->Release();
	if (g_pVertexLayout) g_pVertexLayout->Release();
	if (g_pVertexShader) g_pVertexShader->Release();
	if (g_pPixelShader) g_pPixelShader->Release();
	if (g_pDepthStencil) g_pDepthStencil->Release();
	if (g_pDepthStencilView) g_pDepthStencilView->Release();
	if (g_pRenderTargetView) g_pRenderTargetView->Release();
	if (g_pSwapChain) g_pSwapChain->Release();
	if (g_pImmediateContext) g_pImmediateContext->Release();
	if (g_pd3dDevice) g_pd3dDevice->Release();
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
	// Update our time
	static float t = 0.0f;
	if (g_driverType == D3D_DRIVER_TYPE_REFERENCE)
	{
		t += (float)XM_PI * 0.0125f;
	}
	else
	{
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}

	// Rotate cube around the origin
	g_World = XMMatrixRotationY(t);

	// Modify the color
	g_vMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
	g_vMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
	g_vMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

	//
	// Clear the back buffer
	//
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
	g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, ClearColor);

	//
	// Clear the depth buffer to 1.0 (max depth)
	//
	g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//
	// Update variables that change once per frame
	//
	CBChangesEveryFrame cb;
	cb.mWorld = XMMatrixTranspose(g_World);
	cb.vMeshColor = g_vMeshColor;
	g_pImmediateContext->UpdateSubresource(g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0);

	//
	// Render the cube
	//
	g_pImmediateContext->VSSetShader(g_pVertexShader, NULL, 0);
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pCBNeverChanges);
	g_pImmediateContext->VSSetConstantBuffers(1, 1, &g_pCBChangeOnResize);
	g_pImmediateContext->VSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
	g_pImmediateContext->PSSetShader(g_pPixelShader, NULL, 0);
	g_pImmediateContext->PSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
	g_pImmediateContext->PSSetShaderResources(0, 1, &g_pTextureRV);
	g_pImmediateContext->PSSetSamplers(0, 1, &g_pSamplerLinear);
	g_pImmediateContext->DrawIndexed(36, 0, 0);

	//
	// Present our back buffer to our front buffer
	//
	g_pSwapChain->Present(0, 0);




	


}
