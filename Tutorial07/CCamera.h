#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#include "Defines.h"

struct CBNeverChanges {
	XMMATRIX mView;
};

struct CBChangeOnResize {
	XMMATRIX mProjection;
};


class CCamera {
public:
	CCamera();
	~CCamera();

	void init(float inAngle, float inAR, float inNear, float inFar);
	void update();

	void updateVM();

	void move(XMVECTOR inVect);

	CBNeverChanges m_NC;
	CBChangeOnResize m_COR;

	XMMATRIX getViewMatrix();
	XMMATRIX getProyectionMatrix();
private:
	float m_Angle = 0;
	float m_AspectRatio = 0;
	float m_Near = 0;
	float m_Far = 0;
	XMVECTOR m_Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 1.0f);	//En posicion del mundo
	XMVECTOR m_At = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);	//En posicion del mundo
	XMVECTOR m_Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);	//Up del mundo
	XMMATRIX m_VM;
	XMMATRIX m_PM;
	XMVECTOR m_Right;
	XMVECTOR m_Up2;		//Up de la camara
	XMVECTOR m_Front;
	

	
protected:


};

