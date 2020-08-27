#include "CCamera.h"

CCamera::CCamera() {
	m_Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	m_At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
}

CCamera::~CCamera() {

}

void CCamera::init(float inAngle, float inAR, float inNear, float inFar) {
	m_Angle = inAngle;
	m_AspectRatio = inAR;
	m_Near = inNear;
	m_Far = inFar;
	update();
}

void CCamera::update() {
	m_VM = XMMatrixLookAtLH(m_Eye, m_At, m_Up);
	m_VM = XMMatrixTranspose(m_VM);
	m_NC.mView = m_VM;

	m_PM = XMMatrixPerspectiveFovLH(m_Angle, m_AspectRatio, m_Near, m_Far);
	m_PM = XMMatrixTranspose(m_PM);
	m_COR.mProjection = m_PM;
}
