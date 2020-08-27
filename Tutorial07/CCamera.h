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



	CBNeverChanges m_NC;
	CBChangeOnResize m_COR;
private:
	float m_Angle;
	float m_AspectRatio;
	float m_Near;
	float m_Far;
	XMVECTOR m_Eye;
	XMVECTOR m_At;
	XMVECTOR m_Up;
	XMMATRIX m_VM;
	XMMATRIX m_PM;


	
protected:


};

