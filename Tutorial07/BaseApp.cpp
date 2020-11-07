#include "BaseApp.h"


BaseApp::~BaseApp() {
}

int BaseApp::run() {
	createWindow();
	initSystems();
	//Send message to device
	onCreate();
	//ImGUI
	
	//Main Loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			//Eventos propios
			onEvent(msg.message, msg.wParam);
		}
		else {

			//Update Time
			static float t = 0.0f;
			static int dwTimeStart = 0;
			int dwTimeCur = GetTickCount();
			if (dwTimeStart == 0) {
				dwTimeStart = dwTimeCur;
			}
			t = (dwTimeCur - dwTimeStart) / 1000.0f;
			//Update Game Logic
			update(t);
			//Render Frame
			render();
		}
	}
	onDestroy();

	
	return 0;
}

//void BaseApp::onCreate() {
//
//
//}

void BaseApp::onDestroy() {
}

void BaseApp::onRender() {
}

void BaseApp::onEvent(UINT inMsg, WPARAM inwParam) {

}

bool BaseApp::createWindow() {
	//Create the instance for the window
	auto hInstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr));
	
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = handleWindowEvent;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"TutorialWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_APPLICATION);
	if (!RegisterClassEx(&wcex)) {
		return E_FAIL;
	}

	RECT rc = { 0, 0, m_Width, m_Height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hWd;
	hWd = CreateWindow(L"TutorialWindowClass",
					   L"Tutorial07",
					   WS_OVERLAPPEDWINDOW,
					   CW_USEDEFAULT,
					   CW_USEDEFAULT,
					   rc.right - rc.left,
					   rc.bottom - rc.top,
					   nullptr,
					   nullptr,
					   hInstance,
					   nullptr);

	//Check if the window was created correctly
	if (!hWd) {
		return false;
	}

	RECT clientRect;
	GetClientRect(hWd, &clientRect);
	m_Width = clientRect.right - clientRect.left;
	m_Height = clientRect.bottom - clientRect.top;
	m_window = reinterpret_cast<void*>(hWd);
	ShowWindow(hWd, 10);

	return false;
}

void BaseApp::update(float inDeltaTime) {
	onUpdate(inDeltaTime);
}

void BaseApp::render() {
	onRender();
	//Set RT
	//Present

}

void BaseApp::initSystems() {
	CGraphicsAPI::Prepare();
	g_GraphicsAPI().init(m_window, m_Width, m_Height);
}

void BaseApp::destroySystems() {
	CGraphicsAPI::ShutDown();
}

LRESULT BaseApp::handleWindowEvent(HWND inHw, UINT inMsg, WPARAM inwParam, LPARAM inlParam) {
	
	PAINTSTRUCT ps;
	HDC hdc;
	switch (inMsg) {
	case WM_PAINT: {
		hdc = BeginPaint(inHw, &ps);
		EndPaint(inHw, &ps);
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	
	
	default: {
		
		return DefWindowProc(inHw, inMsg, inwParam, inlParam);
		break;
	}
	}


}

CGraphicsAPI& g_GraphicsAPI() {
	return CGraphicsAPI::getSingleton();
}
