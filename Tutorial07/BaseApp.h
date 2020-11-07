#pragma once
#include "CGraphicsAPI.h"

class BaseApp {
public:
	BaseApp() = default;
	~BaseApp();

	int run();

protected:
	/*
	* @brief	: Virtual Method in charge of creating a virtual method.
	*/
	virtual void onCreate() = 0;
	/*
	* @brief	: Virtual Method in charge of destroying the settings and members.
	*/
	virtual void onDestroy();
	/*
	* @brief	: Virtual method in charge to updating the logical information.
	* @param	: inDeltaTime for update the game time.
	*/
	virtual void onUpdate(float inDeltaTime = 0) { (void)inDeltaTime; };
	/*
	* @brief	: Virtual method in charge of drawing on screen all the visual info.
	*/
	virtual void onRender();

	virtual void onEvent(UINT inMsg, WPARAM inwParam);

private:
	/*
	* @brief	: Method in charge of drawing on the screen all the visual info.
	*/
	bool createWindow();
	/*
	* @brief	: Method in charge of updates the logic info.
	*/
	void update(float inDeltaTime);
	/*
	* @brief	: Method that draw the information Not Modified Func.
	*/
	void render();
	/*
	* @brief	: Method that initialize the modules and plug-ins for the engine.
	*/
	void initSystems();
	/*
	* @brief	: Method that destroys the systems of the engine.
	*/
	void destroySystems();


public:
	//CallBack
	/*
	* @brief	: Method that set the events and messages for the game.
	*/
	static LRESULT CALLBACK handleWindowEvent(HWND inHw, UINT msg, WPARAM wParam, LPARAM lParam);

	int m_Width = 640;
	int m_Height = 480;
	void * m_window = nullptr;
private:


};

