#include "CCamera.h"

CCamera::CCamera() {
	m_Front = XMVector3Normalize(m_At - m_Eye);
	m_Right = XMVector3Normalize(XMVector3Cross(m_Up, m_Front));
	m_Up2 = XMVector3Normalize(XMVector3Cross(m_Front, m_Right));
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
	updateVM();

	m_PM = XMMatrixPerspectiveFovLH(m_Angle, m_AspectRatio, m_Near, m_Far);
	m_PM = XMMatrixTranspose(m_PM);
}

void CCamera::updateVM() {
	m_Right = XMVectorSet(m_VM._11, m_VM._12, m_VM._13, 0);
	m_Up2 = XMVectorSet(m_VM._21, m_VM._22, m_VM._23, 0);
	m_Front = XMVectorSet(m_VM._31, m_VM._32, m_VM._33, 0);
	m_At = m_Front + m_Eye;
}

void CCamera::move(XMVECTOR inVect) {
	XMFLOAT3 tmpVect;
	XMStoreFloat3(&tmpVect, inVect);
	if (tmpVect.x != 0.f) {
		m_Eye += (m_Right * tmpVect.x);
	}
	if (tmpVect.y != 0.f) {
		m_Eye += (m_Up2 * tmpVect.y);
	}
	if (tmpVect.z != 0.f) {
		m_Eye += (m_Front * tmpVect.z);
	}

	m_Up2 = XMVector3Normalize(m_Up2);
	m_Right = XMVector3Normalize(m_Right);
	m_Front = XMVector3Normalize(m_Front);

	XMFLOAT3 tmpRight;
	XMFLOAT3 tmpUp;
	XMFLOAT3 tmpFront;
	XMStoreFloat3(&tmpRight, m_Right);
	XMStoreFloat3(&tmpUp, m_Up2);
	XMStoreFloat3(&tmpFront, m_Front);

	XMMATRIX Axis {
		tmpRight.x,	tmpRight.y,	tmpRight.z,		0,
		tmpUp.x,	tmpUp.y,	tmpUp.z,		0,
		tmpFront.x,	tmpFront.y,	tmpFront.z,		0,
		0,			0,			0,				1
	};

	XMFLOAT3 tmpEye;
	XMStoreFloat3(&tmpEye, m_Eye);

	XMMATRIX Pos{
		1,0,0,-tmpEye.x,
		0,1,0,-tmpEye.y,
		0,0,1,-tmpEye.z,
		0,0,0,1
	};
	Pos *= Axis;
	m_VM = Pos;
}

XMMATRIX CCamera::getViewMatrix() {
	//Process - update
	return m_VM;
}

XMMATRIX CCamera::getProyectionMatrix() {
	//Update the matrix
	return m_PM;
}
