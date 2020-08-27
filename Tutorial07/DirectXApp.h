#pragma once
#include "BaseApp.h"

class CGraphicsAPI;


class DirectXApp : public BaseApp {
public:
	DirectXApp();
	~DirectXApp();

	void onCreate() override;
	void onDestroy() override;
	void onUpdate(float inDeltaTime = 0) override;
	void onRender() override;


	
};

