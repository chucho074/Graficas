//--------------------------------------------------------------------------------------
// File: Tutorial07.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include <vector>
#include "resource.h"
#include "CCameraFP.h"
#include "CDevice.h"
#include "CSwapChain.h"
#include "CDeviceContext.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CTexture2D.h"
#include "CDepthStencilView.h"
#include "CVertexShader.h"
#include "CPixelShader.h"
#include "CViewPort.h"
#include "CRenderTargetView.h"
#include "CSamplerState.h"
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

CDevice * CDevice::m_DeviceInstance = nullptr;
CSwapChain * CSwapChain::m_pSCInstance = nullptr;
CDeviceContext * CDeviceContext::m_DCInstance = nullptr;

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
//Singletons
CDevice *							g_pDevice = CDevice::getInstance();
CSwapChain *						g_SwapChain = CSwapChain::getInstance();
CDeviceContext *					g_DeviceContext = CDeviceContext::getInstance();

CVertexBuffer						g_VertexBuffer;
CIndexBuffer						g_IndexBuffer;
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
CVertexBuffer						g_BoardVB;
CIndexBuffer						g_BoardIB;

glm::vec3 boardpos(-5, 1, 0);

#ifdef D_DIRECTX
ID3D11Device * ptrDevice = static_cast<ID3D11Device*>(g_pDevice->getDevice());
ID3D11DeviceContext * ptrDC = static_cast<ID3D11DeviceContext*>(g_DeviceContext->getDeviceContext());
IDXGISwapChain* ptrSC = static_cast<IDXGISwapChain*>(g_SwapChain->getSwapChain());

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

void framebuffer_size_callback(GLFWwindow* window, int width, int heigth)
{
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Close app
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	//Key presses
	if (action == GLFW_PRESS)
	{
		ActiveCamera->getKeyPress(key);
	}
	//Key release
	if (action == GLFW_RELEASE)
	{
		ActiveCamera->getKeyRelease(key);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			ActiveCamera->InitPos = { xpos, ypos, 0.f };
			ActiveCamera->mIsClicked = true;
		}
		else if (action == GLFW_RELEASE)
		{
			ActiveCamera->mIsClicked = false;
		}
	}
}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (ActiveCamera->mIsClicked)
	{
		ActiveCamera->EndPos = { xpos, ypos, 0.f };
		glfwSetCursorPos(window, ActiveCamera->InitPos.x, ActiveCamera->InitPos.y);
		ActiveCamera->mDir = ActiveCamera->InitPos - ActiveCamera->EndPos;
		ActiveCamera->rotate(ActiveCamera->mDir);
	}
}

#endif


#ifdef D_DIRECTX
HRESULT CreateInputLayoutDescFromVertexShaderSignature(ID3DBlob* pShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout)
{
	// Reflect shader info
	ID3D11ShaderReflection* pVertexShaderReflection = NULL;
	if (FAILED(D3DReflect(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pVertexShaderReflection)))
	{
		return S_FALSE;
	}

	// Get shader info
	D3D11_SHADER_DESC shaderDesc;
	pVertexShaderReflection->GetDesc(&shaderDesc);

	// Read input layout description from shader info
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	int offset = 0;
	for (int i = 0; i < shaderDesc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

		// fill out input element desc
		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = offset;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		// determine DXGI format
		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT; offset += 12;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		//save element desc
		inputLayoutDesc.push_back(elementDesc);
	}

	// Try to create Input Layout
	HRESULT hr = pD3DDevice->CreateInputLayout(&inputLayoutDesc[0], inputLayoutDesc.size(), pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), pInputLayout);

	//Free allocation shader reflection memory
	pVertexShaderReflection->Release();
	return hr;
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
			ImVec2 ImgDimension(imguiWindowW / 5, imguiWindowH / 5);

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			ImGui::Begin("Inactive Camera", nullptr, 8);
			{
				ImGui::SetWindowSize(ImVec2(0, 0));

				ImGui::Image(InactiveSRV, ImgDimension);

				ImGui::GetIO().FontGlobalScale;
				if (ImGui::Button("Change"))
				{
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
	if (window == NULL)
	{
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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
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
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	}
	//Pixel Shader
	int pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(pixelShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(pixelShader);
	//PS error check
	glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(pixelShader, 512, NULL, infoLog);
	}
	//Link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, pixelShader);
	glLinkProgram(shaderProgram);
	//Linking error check
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
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
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
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

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		//Update
		if (ActiveCamera->mForward || ActiveCamera->mBack || ActiveCamera->mLeft || ActiveCamera->mRight || ActiveCamera->mUp || ActiveCamera->mDown)
		{
			ActiveCamera->move();
		}
		if (ActiveCamera->mRotateLeft || ActiveCamera->mRotateRight)
		{
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
		ImGui::Begin("Inactive Camera", nullptr, 8);
		{
			ImGui::SetWindowSize(ImVec2(0,0));
			ImGui::Image((void*)textureColorbuffer, ImVec2(imguiWindowW / 4, imguiWindowH / 4));
			if (ImGui::Button("Change Camera"))
			{
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
#ifdef D_DIRECTX
HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut ) {
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;


    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
    if( FAILED(hr) )
    {
        if( pErrorBlob != NULL )
            OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
        if( pErrorBlob ) pErrorBlob->Release();
        return hr;
    }
    if( pErrorBlob ) pErrorBlob->Release();

    return S_OK;
}
#endif

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

	g_pDevice->init(T);

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

	g_SwapChain->init(S);

	for (unsigned int driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
		g_pDevice->Desc.DriverType = g_pDevice->Desc.DriverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, (D3D_DRIVER_TYPE)g_pDevice->Desc.DriverType, NULL, g_pDevice->Desc.DeviceFlags, (D3D_FEATURE_LEVEL *)g_pDevice->Desc.FeatureLevels, g_pDevice->Desc.numFeatureLevels,
			D3D11_SDK_VERSION, &g_SwapChain->m_sd, &ptrSC, &ptrDevice, (D3D_FEATURE_LEVEL *)&featureLevel, &ptrDC);
		if (SUCCEEDED(hr)) {
			break;
		}
	}
	if (FAILED(hr)) {
		return hr;
	}
	// Create a render target view
	CTexture2D BackBuffer;
	hr = ptrSC->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer.m_pTexture);
	if (FAILED(hr)) {
		return hr;
	}
	hr = ptrDevice->CreateRenderTargetView(BackBuffer.m_pTexture, NULL, &g_RenderTargetView.m_pRTV);
	BackBuffer.m_pTexture->Release();
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

	hr = ptrDevice->CreateTexture2D(&g_DepthStencil.m_Desc, NULL, &g_DepthStencil.m_pTexture);
	if (FAILED(hr)) {
		return hr;
	}
	// Create the depth stencil view
	DepthStencilViewDesc DSV;
	DSV.format = g_DepthStencil.m_Data.format;
	DSV.viewDimension = DSV_DIMENSION_TEXTURE2D;
	DSV.texture2D.mipSlice = 0;

	DepthStencilViewFree.init(DSV, (FORMAT)g_DepthStencil.m_Desc.Format);

	hr = ptrDevice->CreateDepthStencilView(g_DepthStencil.m_pTexture, &DepthStencilViewFree.m_Desc, &DepthStencilViewFree.m_pDepthStencilView);
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

	CViewPort tempVP;
	tempVP.init(vpStruct);
	ptrDC->RSSetViewports(1, &tempVP.m_Viewport);

	// Compile the vertex shader
	hr = CompileShaderFromFile(L"Tutorial07.fx", "VS", "vs_4_0", &g_VertexShader.m_pVSBlob);
	if (FAILED(hr)) {
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
	hr = ptrDevice->CreateVertexShader(g_VertexShader.m_pVSBlob->GetBufferPointer(), g_VertexShader.m_pVSBlob->GetBufferSize(), NULL, &g_VertexShader.m_pVertexShader);
	if (FAILED(hr)) {
		g_VertexShader.m_pVSBlob->Release();
		return hr;
	}

	//Create input layout from compiled VS
	hr = CreateInputLayoutDescFromVertexShaderSignature(g_VertexShader.m_pVSBlob, ptrDevice, &g_VertexShader.m_pInputLayout);
	if (FAILED(hr)) {
		return hr;
	}
	// Set the input layout
	ptrDC->IASetInputLayout(g_VertexShader.m_pInputLayout);

	// Compile the pixel shader
	hr = CompileShaderFromFile(L"Tutorial07.fx", "PS", "ps_4_0", &g_PixelShader.m_pPSBlob);
	if (FAILED(hr)){
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = ptrDevice->CreatePixelShader(g_PixelShader.m_pPSBlob->GetBufferPointer(), g_PixelShader.m_pPSBlob->GetBufferSize(), NULL, &g_PixelShader.m_pPixelShader);
	g_PixelShader.m_pPSBlob->Release();
	if (FAILED(hr)) {
		return hr;
	}
	// Create vertex buffer
	SimpleVertex vertices[] = {
		{ glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },
	};

	//											NEW TESTING

	//BManager.init();
	BufferDesc bufferstrct;
	bufferstrct.usage = USAGE_DEFAULT;
	bufferstrct.byteWidth = sizeof(SimpleVertex) * 24;
	bufferstrct.bindFlags = 1;			// D3D11_BIND_VERTEX_BUFFER;
	bufferstrct.cpuAccessFlags = 0;

	//BManager.updateDesc(sizeof(SimpleVertex) * 24);
	SubresourceData subrsrcData;
	subrsrcData.psysMem = vertices;
	g_VertexBuffer.init(subrsrcData, bufferstrct);
	//BManager.initVB(subrsrcData);
	
	hr = ptrDevice->CreateBuffer(&g_VertexBuffer.Buffer.m_bd, &g_VertexBuffer.Data, &g_VertexBuffer.Buffer.Buffer);
	//hr = ptrDevice->CreateBuffer(&BManager.getVB()->Buffer.m_bd, &BManager.getVB()->Data, &BManager.getVB()->Buffer.Buffer);
	if (FAILED(hr)) {
		return hr;
	}
    // Set vertex buffer
    UINT stride = sizeof( SimpleVertex );
    UINT offset = 0;
	ptrDC->IASetVertexBuffers( 0, 1, &g_VertexBuffer.Buffer.Buffer, &stride, &offset );
	//ptrDC->IASetVertexBuffers( 0, 1, &BManager.getVB()->Buffer.Buffer, &stride, &offset );

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
	//BManager.updateDesc(sizeof(WORD) * 36);

	subrsrcData.psysMem = indices;
	//BManager.initIB(subrsrcData);
	g_IndexBuffer.init(subrsrcData, bufferstrct);

    hr = ptrDevice->CreateBuffer( &g_IndexBuffer.Buffer.m_bd, &g_IndexBuffer.m_Data, &g_IndexBuffer.Buffer.Buffer );
	//hr = ptrDevice->CreateBuffer(&BManager.getIB()->Buffer.m_bd, &BManager.getIB()->m_Data, &BManager.getIB()->Buffer.Buffer);
	if (FAILED(hr)) {
		return hr;
	}
    // Set index buffer
	ptrDC->IASetIndexBuffer(g_IndexBuffer.Buffer.Buffer, DXGI_FORMAT_R16_UINT, 0 );
	//ptrDC->IASetIndexBuffer(BManager.getIB()->Buffer.Buffer, DXGI_FORMAT_R16_UINT, 0);
    
	//Create billboard VertexBuffer
	SimpleVertex boardVertex[] =
	{
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

	hr = ptrDevice->CreateBuffer(&g_BoardVB.Buffer.m_bd, &g_BoardVB.Data, &g_BoardVB.Buffer.Buffer);
	if (FAILED(hr))
	{
		return hr;
	}

	//Set billboard VB
	stride = sizeof(SimpleVertex);
	offset = 0;
	ptrDC->IASetVertexBuffers(0, 1, &g_BoardVB.Buffer.Buffer, &stride, &offset);

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
	hr = ptrDevice->CreateBuffer(&g_BoardIB.Buffer.m_bd, &g_BoardIB.m_Data, &g_BoardIB.Buffer.Buffer);
	if (FAILED(hr))
	{
		return hr;
	}

	//Set billboard IB
	ptrDC->IASetIndexBuffer(g_BoardIB.Buffer.Buffer, DXGI_FORMAT_R16_UINT, 0);

	ptrDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Create the constant buffers
	bufferstrct.usage = USAGE_DEFAULT;
	bufferstrct.byteWidth = sizeof(CBNeverChanges);
	bufferstrct.bindFlags = 4;		// D3D11_BIND_CONSTANT_BUFFER;
	bufferstrct.cpuAccessFlags = 0;

	//NeverChanges

	//Free Camera
	Camera.m_CBNeverChanges.init(bufferstrct);
    hr = ptrDevice->CreateBuffer( &Camera.m_CBNeverChanges.m_bd, NULL, &Camera.m_CBNeverChanges.Buffer );
	if (FAILED(hr)) {
		return hr;
	}
	//FPS Camera
	FirstPerson.m_CBNeverChanges.init(bufferstrct);
	hr = ptrDevice->CreateBuffer(&FirstPerson.m_CBNeverChanges.m_bd, NULL, &FirstPerson.m_CBNeverChanges.Buffer);
	if (FAILED(hr)) {
		return hr;
	}
	//ChangeOnResize
	bufferstrct.byteWidth = sizeof(CBChangeOnResize);
	//Free Camera
	Camera.m_CBChangesOnResize.init(bufferstrct);
    hr = ptrDevice->CreateBuffer( &Camera.m_CBChangesOnResize.m_bd, NULL, &Camera.m_CBChangesOnResize.Buffer );
	if (FAILED(hr)) {
		return hr;
	}
	//FPS Camera
	FirstPerson.m_CBChangesOnResize.init(bufferstrct);
	hr = ptrDevice->CreateBuffer(&FirstPerson.m_CBChangesOnResize.m_bd, NULL, &FirstPerson.m_CBChangesOnResize.Buffer);
	if (FAILED(hr)) {
		return hr;
	}
	//ChangeEveryFrame
	bufferstrct.byteWidth = sizeof(CBChangesEveryFrame);
	//Free Camera
	Camera.m_CBChangesEveryFrame.init(bufferstrct);
    hr = ptrDevice->CreateBuffer( &Camera.m_CBChangesEveryFrame.m_bd, NULL, &Camera.m_CBChangesEveryFrame.Buffer );
	if (FAILED(hr)) {
		return hr;
	}
	//FPS Camera
	FirstPerson.m_CBChangesEveryFrame.init(bufferstrct);
	hr = ptrDevice->CreateBuffer(&FirstPerson.m_CBChangesEveryFrame.m_bd, NULL, &FirstPerson.m_CBChangesEveryFrame.Buffer);
	if (FAILED(hr)) {
		return hr;
	}
    // Load the Texture 
    hr = D3DX11CreateShaderResourceViewFromFile( ptrDevice, L"seafloor.dds", NULL, NULL, &g_pTextureRV, NULL );
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

    hr = ptrDevice->CreateSamplerState( &g_SamplerState.m_Desc, &g_SamplerState.m_pSamplerLinear );
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
	ptrDC->UpdateSubresource(Camera.m_CBNeverChanges.Buffer, 0, NULL, &cbNeverChanges, 0, 0);
#endif

	//Set FPS Camera VM
	CBNeverChanges cbNeverChanges2;
	cbNeverChanges2.mView = FirstPerson.getVM();
#ifdef D_DIRECTX
	ptrDC->UpdateSubresource(FirstPerson.m_CBNeverChanges.Buffer, 0, NULL, &cbNeverChanges2, 0, 0);
#endif

    // Initialize Free Camera PM    
    CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = glm::transpose(Camera.getPM());
#ifdef D_DIRECTX
	ptrDC->UpdateSubresource( Camera.m_CBChangesOnResize.Buffer, 0, NULL, &cbChangesOnResize, 0, 0 );
#endif

	//Initialize FPS Camera PM
	CBChangeOnResize cbChangesOnResize2;
	cbChangesOnResize2.mProjection = glm::transpose(FirstPerson.getPM());
#ifdef D_DIRECTX
	ptrDC->UpdateSubresource(FirstPerson.m_CBChangesOnResize.Buffer, 0, NULL, &cbChangesOnResize2, 0, 0);
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
	hr = ptrDevice->CreateTexture2D(&InactiveCameraTexture.m_Desc, NULL, &InactiveCameraTexture.m_pTexture);
	if (FAILED(hr))
		return hr;
#endif

	//Render Target View
	RenderTargetViewDesc rtDesc;
	rtDesc.format = D.format;
	rtDesc.viewDimension = RTV_DIMENSION_TEXTURE2D;
	rtDesc.texture2D.mipSlice = 0;

	SecondRTV.init(rtDesc);
#ifdef D_DIRECTX
	hr = ptrDevice->CreateRenderTargetView(InactiveCameraTexture.m_pTexture, &SecondRTV.m_Desc, &SecondRTV.m_pRTV);
	if (FAILED(hr))
		return hr;
#endif

#ifdef D_DIRECTX
	D3D11_SHADER_RESOURCE_VIEW_DESC view;
	view.Format = (DXGI_FORMAT)D.format;
	view.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	view.Texture2D.MostDetailedMip = 0;
	view.Texture2D.MipLevels = 1;

	hr = ptrDevice->CreateShaderResourceView(InactiveCameraTexture.m_pTexture, &view, &InactiveSRV);
	if (FAILED(hr))
		return hr;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX11_Init(ptrDevice,ptrDC);
	ImGui::StyleColorsDark();

	g_pDevice->Device = ptrDevice;
	g_DeviceContext->m_DeviceContext = ptrDC;
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
    if( ptrDC) ptrDC->ClearState();
    if( g_SamplerState.m_pSamplerLinear ) g_SamplerState.m_pSamplerLinear->Release();
    if( g_pTextureRV ) g_pTextureRV->Release();
    if( Camera.m_CBNeverChanges.Buffer ) Camera.m_CBNeverChanges.Buffer->Release();
    if( Camera.m_CBChangesOnResize.Buffer ) Camera.m_CBChangesOnResize.Buffer->Release();
    if( Camera.m_CBChangesEveryFrame.Buffer ) Camera.m_CBChangesEveryFrame.Buffer->Release();
    if( g_VertexBuffer.Buffer.Buffer) g_VertexBuffer.Buffer.Buffer->Release();
	if (g_BoardVB.Buffer.Buffer) g_BoardVB.Buffer.Buffer->Release();
    if( g_IndexBuffer.Buffer.Buffer ) g_IndexBuffer.Buffer.Buffer->Release();
	if (g_BoardIB.Buffer.Buffer) g_BoardIB.Buffer.Buffer->Release();
    if( g_VertexShader.m_pInputLayout ) g_VertexShader.m_pInputLayout->Release();
    if( g_VertexShader.m_pVertexShader ) g_VertexShader.m_pVertexShader->Release();
    if( g_PixelShader.m_pPixelShader) g_PixelShader.m_pPixelShader->Release();
    if( g_DepthStencil.m_pTexture) g_DepthStencil.m_pTexture->Release();
    if( DepthStencilViewFree.m_pDepthStencilView ) DepthStencilViewFree.m_pDepthStencilView->Release();
    if( g_RenderTargetView.m_pRTV ) g_RenderTargetView.m_pRTV->Release();
    if( ptrSC) ptrSC->Release();
	if (FirstPerson.m_CBNeverChanges.Buffer) FirstPerson.m_CBNeverChanges.Buffer->Release();
	if (FirstPerson.m_CBChangesOnResize.Buffer) FirstPerson.m_CBChangesOnResize.Buffer->Release();
	if (FirstPerson.m_CBChangesEveryFrame.Buffer) FirstPerson.m_CBChangesEveryFrame.Buffer->Release();
    if( ptrDC) ptrDC->Release();
    if( ptrDevice ) ptrDevice->Release();	
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
			if (g_DeviceContext->m_DeviceContext != nullptr){
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
				ptrDC->UpdateSubresource(ActiveCamera->m_CBChangesOnResize.Buffer, 0, NULL, &cbChangesOnResize, 0, 0);
				InactiveCamera->setHeigth(height);
				InactiveCamera->setWidth(width);
				InactiveCamera->updatePM();
				cbChangesOnResize.mProjection = glm::transpose(InactiveCamera->PM);
				ptrDC->UpdateSubresource(InactiveCamera->m_CBChangesOnResize.Buffer, 0, NULL, &cbChangesOnResize, 0, 0);
				if (ptrSC) {
					HRESULT h;
					InactiveCameraTexture.m_pTexture->Release();
					InactiveSRV->Release();
					SecondRTV.m_pRTV->Release();
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

					h = g_pDevice->Device->CreateTexture2D(&InactiveCameraTexture.m_Desc, NULL, &InactiveCameraTexture.m_pTexture);
					RenderTargetViewDesc RTV;
					RTV.format = T.format;
					RTV.viewDimension = RTV_DIMENSION_TEXTURE2D;
					RTV.texture1D.mipSlice = 0;
					SecondRTV.init(RTV);
					h = ptrDevice->CreateRenderTargetView(InactiveCameraTexture.m_pTexture, &SecondRTV.m_Desc, &SecondRTV.m_pRTV);
					D3D11_SHADER_RESOURCE_VIEW_DESC SRV;
					SRV.Format = (DXGI_FORMAT)T.format;
					SRV.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
					SRV.Texture2D.MostDetailedMip = 0;
					SRV.Texture2D.MipLevels = 1;
					h = g_pDevice->Device->CreateShaderResourceView(InactiveCameraTexture.m_pTexture, &SRV, &InactiveSRV);
					ptrDC->OMSetRenderTargets(0, 0, 0);
					g_RenderTargetView.m_pRTV->Release();
					h = ptrSC->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
					CBuffer tempBack;
					h = ptrSC->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&tempBack.Buffer);
					h = ptrDevice->CreateRenderTargetView(tempBack.Buffer, NULL, &g_RenderTargetView.m_pRTV);
					tempBack.Buffer->Release();
					g_DepthStencil.m_pTexture->Release();
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
					h = g_pDevice->Device->CreateTexture2D(&g_DepthStencil.m_Desc, NULL, &g_DepthStencil.m_pTexture);
					DepthStencilViewDesc DSV;
					DSV.format = g_DepthStencil.m_Data.format;
					DSV.viewDimension = DSV_DIMENSION_TEXTURE2D;
					DSV.texture2D.mipSlice = 0;
					DepthStencilViewFree.m_pDepthStencilView->Release();
					DepthStencilViewFree.init(DSV, (FORMAT)g_DepthStencil.m_Desc.Format);
					h = g_pDevice->Device->CreateDepthStencilView(g_DepthStencil.m_pTexture, &DepthStencilViewFree.m_Desc, &DepthStencilViewFree.m_pDepthStencilView);
					g_DeviceContext->m_DeviceContext->OMSetRenderTargets(1, &g_RenderTargetView.m_pRTV, DepthStencilViewFree.m_pDepthStencilView);
					ViewPortDesc V;
					V.W = width;
					V.H = height;
					V.minDepth = 0.f;
					V.maxDepth = 1.f;
					V.topLeftX = 0;
					V.topLeftY = 0;
					CViewPort ViewP;
					ViewP.init(V);
					g_DeviceContext->m_DeviceContext->RSSetViewports(1, &ViewP.m_Viewport);
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
				g_DeviceContext->m_DeviceContext->UpdateSubresource(ActiveCamera->m_CBNeverChanges.Buffer, 0, NULL, &cbNeverChanges, 0, 0);
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
    if( g_pDevice->Desc.DriverType == D3D_DRIVER_TYPE_REFERENCE ) {
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
		g_DeviceContext->m_DeviceContext->UpdateSubresource(ActiveCamera->m_CBNeverChanges.Buffer, 0, NULL, &cbNeverChanges, 0, 0);
	}

    // Modify the color
	g_MeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
	g_MeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
	g_MeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; 
	g_DeviceContext->m_DeviceContext->OMSetRenderTargets(1, &SecondRTV.m_pRTV, DepthStencilViewFree.m_pDepthStencilView);
	g_DeviceContext->m_DeviceContext->ClearRenderTargetView(SecondRTV.m_pRTV, ClearColor);
	g_DeviceContext->m_DeviceContext->ClearDepthStencilView(DepthStencilViewFree.m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	unsigned int stride = sizeof(SimpleVertex);
	unsigned int offset = 0;
	g_DeviceContext->m_DeviceContext->IASetVertexBuffers(0, 1, &g_VertexBuffer.Buffer.Buffer, &stride, &offset);
	g_DeviceContext->m_DeviceContext->IASetIndexBuffer(g_IndexBuffer.Buffer.Buffer, DXGI_FORMAT_R16_UINT, 0);
	CBChangesEveryFrame cb;
	g_World = glm::mat4(1.f);
	g_World = glm::translate(g_World,ActiveCamera->getPos());
	cb.mWorld = glm::transpose(g_World);
	cb.vMeshColor = g_MeshColor;
	g_DeviceContext->m_DeviceContext->UpdateSubresource(InactiveCamera->m_CBChangesEveryFrame.Buffer, 0, NULL, &cb, 0, 0);



	

	g_World = glm::mat4(1.f);
	
	cb.mWorld = glm::transpose(g_World);
	cb.vMeshColor = g_MeshColor;
	g_DeviceContext->m_DeviceContext->UpdateSubresource(InactiveCamera->m_CBChangesEveryFrame.Buffer, 0, NULL, &cb, 0, 0);

	g_DeviceContext->m_DeviceContext->VSSetShader(g_VertexShader.m_pVertexShader, NULL, 0);
	g_DeviceContext->m_DeviceContext->VSSetConstantBuffers(0, 1, &InactiveCamera->m_CBNeverChanges.Buffer);
	g_DeviceContext->m_DeviceContext->VSSetConstantBuffers(1, 1, &InactiveCamera->m_CBChangesOnResize.Buffer);
	g_DeviceContext->m_DeviceContext->VSSetConstantBuffers(2, 1, &InactiveCamera->m_CBChangesEveryFrame.Buffer);
	g_DeviceContext->m_DeviceContext->PSSetShader(g_PixelShader.m_pPixelShader, NULL, 0);
	g_DeviceContext->m_DeviceContext->PSSetConstantBuffers(2, 1, &InactiveCamera->m_CBChangesEveryFrame.Buffer);
	g_DeviceContext->m_DeviceContext->PSSetShaderResources(0, 1, &g_pTextureRV);
	g_DeviceContext->m_DeviceContext->PSSetSamplers(0, 1, &g_SamplerState.m_pSamplerLinear);
	g_DeviceContext->m_DeviceContext->DrawIndexed(36, 0, 0);
	ID3D11ShaderResourceView* temp = NULL;
	g_DeviceContext->m_DeviceContext->PSSetShaderResources(0, 1, &temp);
	

	CBChangesEveryFrame cbMesh;
	cbMesh.mWorld = {
		1, 0, 0, ActiveCamera->getPos().x,
		0, 1, 0, ActiveCamera->getPos().y,
		0, 0, 1, ActiveCamera->getPos().z,
		0, 0, 0, 1
	};

	cbMesh.vMeshColor = { 1, 0, 0, 1 };
	g_DeviceContext->m_DeviceContext->UpdateSubresource(InactiveCamera->m_CBChangesEveryFrame.Buffer, 0, NULL, &cbMesh, 0, 0);
	/*for (int i = 0; i < SCManager.m_MeshList.size(); i++) {
		g_DeviceContext->m_DeviceContext->VSSetConstantBuffers(2, 1, &InactiveCamera->m_CBChangesEveryFrame.Buffer);
		g_DeviceContext->m_DeviceContext->PSSetShaderResources(0, 1, &SCManager.m_MeshList[i]->Materials->m_TextureDiffuse);
		g_DeviceContext->m_DeviceContext->VSSetShaderResources(0, 1, &SCManager.m_MeshList[i]->Materials->m_TextureDiffuse);
		
		g_DeviceContext->m_DeviceContext->IASetVertexBuffers(0, 1, &SCManager.m_MeshList[i]->VB->Buffer, &stride, &offset);
		g_DeviceContext->m_DeviceContext->IASetIndexBuffer(SCManager.m_MeshList[i]->IB->Buffer, DXGI_FORMAT_R16_UINT, 0);
		g_DeviceContext->m_DeviceContext->DrawIndexed(SCManager.m_MeshList[i]->INum, 0, 0);
	}*/

	//Set backbuffer and main DSV
	g_DeviceContext->m_DeviceContext->OMSetRenderTargets(1, &g_RenderTargetView.m_pRTV, DepthStencilViewFree.m_pDepthStencilView);
	g_DeviceContext->m_DeviceContext->ClearRenderTargetView(g_RenderTargetView.m_pRTV, ClearColor);
	g_DeviceContext->m_DeviceContext->ClearDepthStencilView( DepthStencilViewFree.m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
	g_DeviceContext->m_DeviceContext->IASetVertexBuffers(0, 1, &g_VertexBuffer.Buffer.Buffer, &stride, &offset);
	g_DeviceContext->m_DeviceContext->IASetIndexBuffer(g_IndexBuffer.Buffer.Buffer, DXGI_FORMAT_R16_UINT, 0);
	
    //
    // Update variables that change once per frame
    //
	
		
	g_World = glm::mat4(1.f);

	cb.mWorld = glm::transpose(g_World);
	cb.vMeshColor = g_MeshColor;
	g_DeviceContext->m_DeviceContext->UpdateSubresource(ActiveCamera->m_CBChangesEveryFrame.Buffer, 0, NULL, &cb, 0, 0);
	g_DeviceContext->m_DeviceContext->VSSetShader(g_VertexShader.m_pVertexShader, NULL, 0);
	g_DeviceContext->m_DeviceContext->VSSetConstantBuffers(0, 1, &ActiveCamera->m_CBNeverChanges.Buffer);
	g_DeviceContext->m_DeviceContext->VSSetConstantBuffers(1, 1, &ActiveCamera->m_CBChangesOnResize.Buffer);
	g_DeviceContext->m_DeviceContext->VSSetConstantBuffers(2, 1, &ActiveCamera->m_CBChangesEveryFrame.Buffer);
	g_DeviceContext->m_DeviceContext->PSSetShader( g_PixelShader.m_pPixelShader, NULL, 0);
	g_DeviceContext->m_DeviceContext->PSSetConstantBuffers(2, 1, &ActiveCamera->m_CBChangesEveryFrame.Buffer);
	g_DeviceContext->m_DeviceContext->PSSetShaderResources(0, 1, &InactiveSRV);
	g_DeviceContext->m_DeviceContext->PSSetSamplers(0, 1, &g_SamplerState.m_pSamplerLinear);
	g_DeviceContext->m_DeviceContext->DrawIndexed(36, 0, 0);
	temp = NULL;
	g_DeviceContext->m_DeviceContext->PSSetShaderResources(0, 1, &temp);
	

	g_DeviceContext->m_DeviceContext->IASetVertexBuffers(0, 1, &g_BoardVB.Buffer.Buffer, &stride, &offset);
	g_DeviceContext->m_DeviceContext->IASetIndexBuffer(g_BoardIB.Buffer.Buffer, DXGI_FORMAT_R16_UINT, 0);

	glm::vec3 boardLook = glm::normalize(ActiveCamera->getPos() - boardpos);
	glm::vec3 boardRight = glm::cross(glm::normalize(ActiveCamera->Up), boardLook);
	glm::vec3 boardUp = glm::cross(boardLook, boardRight);

	glm::mat4 boarMat(boardRight.x, boardRight.y, boardRight.z, 0, boardUp.x, boardUp.y, boardUp.z, 0, boardLook.x, boardLook.y, boardLook.z, 0, boardpos.x, boardpos.y, boardpos.z, 1);

	g_World = boarMat;

	cb.mWorld = glm::transpose(g_World);
	cb.vMeshColor = g_MeshColor;
	g_DeviceContext->m_DeviceContext->UpdateSubresource(ActiveCamera->m_CBChangesEveryFrame.Buffer, 0, NULL, &cb, 0, 0);

	g_DeviceContext->m_DeviceContext->VSSetShader(g_VertexShader.m_pVertexShader, NULL, 0);
	g_DeviceContext->m_DeviceContext->VSSetConstantBuffers(0, 1, &ActiveCamera->m_CBNeverChanges.Buffer);
	g_DeviceContext->m_DeviceContext->VSSetConstantBuffers(1, 1, &ActiveCamera->m_CBChangesOnResize.Buffer);
	g_DeviceContext->m_DeviceContext->VSSetConstantBuffers(2, 1, &ActiveCamera->m_CBChangesEveryFrame.Buffer);
	g_DeviceContext->m_DeviceContext->PSSetShader(g_PixelShader.m_pPixelShader, NULL, 0);
	g_DeviceContext->m_DeviceContext->PSSetConstantBuffers(2, 1, &ActiveCamera->m_CBChangesEveryFrame.Buffer);
	g_DeviceContext->m_DeviceContext->PSSetShaderResources(0, 1, &InactiveSRV);
	g_DeviceContext->m_DeviceContext->PSSetSamplers(0, 1, &g_SamplerState.m_pSamplerLinear);
	g_DeviceContext->m_DeviceContext->DrawIndexed(6, 0, 0);
	temp = NULL;
	g_DeviceContext->m_DeviceContext->PSSetShaderResources(0, 1, &temp);

    //
    // Present our back buffer to our front buffer
    //
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	ptrSC->Present( 0, 0 );
#endif
}