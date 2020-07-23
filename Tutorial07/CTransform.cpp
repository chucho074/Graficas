#include "CTransform.h"


CTransform::CTransform() {
	m_Rot = { 0.f, 0.f, 0.f };
	m_Scale = { 1.f, 1.f, 1.f };
	m_Tras = { 0.f, 0.f, 0.f };
}


CTransform::~CTransform() {

}


mat4 CTransform::getMatrix() {
	mat4 TranMatrix (1.f);
	//Multiply by rot in X
	TranMatrix[1][1] = TranMatrix[1][1] * cos(m_Rot.x);
	TranMatrix[2][1] = TranMatrix[2][1] * -sin(m_Rot.x);
	TranMatrix[1][2] = TranMatrix[1][2] * sin(m_Rot.x);
	TranMatrix[1][1] = TranMatrix[1][1] * cos(m_Rot.x);
	//Multiply by rot in Y
	TranMatrix[0][0] = TranMatrix[0][0] * cos(m_Rot.y);
	TranMatrix[2][0] = TranMatrix[2][0] * sin(m_Rot.y);
	TranMatrix[0][2] = TranMatrix[0][2] * -sin(m_Rot.y);
	TranMatrix[2][2] = TranMatrix[2][2] * cos(m_Rot.y);
	//Multiply by rot in Z
	TranMatrix[0][0] = TranMatrix[0][0] * cos(m_Rot.z);
	TranMatrix[1][0] = TranMatrix[1][0] * -sin(m_Rot.z);
	TranMatrix[0][1] = TranMatrix[0][1] * sin(m_Rot.z);
	TranMatrix[1][1] = TranMatrix[1][1] * cos(m_Rot.z);

	//Multiply by Scale
	TranMatrix[0][0] = TranMatrix[0][0] * m_Scale.x;
	TranMatrix[1][1] = TranMatrix[1][1] * m_Scale.y;
	TranMatrix[2][2] = TranMatrix[2][2] * m_Scale.z;
	//Multiply by Traslation
	TranMatrix[3][0] = TranMatrix[3][0] * m_Tras.x;
	TranMatrix[3][1] = TranMatrix[3][2] * m_Tras.y;
	TranMatrix[3][2] = TranMatrix[3][2] * m_Tras.z;



	return TranMatrix;
}


void CTransform::setRot(float inX, float inY,float inZ) {
	m_Rot.x = inX;
	m_Rot.y = inY;
	m_Rot.z = inZ;
}


void CTransform::setScale(vec3 inScale) {
	m_Scale = inScale;
}


void CTransform::setTras(vec3 inTras) {
	m_Tras = inTras;
}
