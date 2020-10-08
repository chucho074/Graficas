#include "DirectXApp.h"

DirectXApp App;
int WINAPI wWinMain(HINSTANCE hInstance, 
				    HINSTANCE hPrevInstance, 
				    LPWSTR lpCmdLine, 
				    int nCmdShow) {
	return App.run();
}
