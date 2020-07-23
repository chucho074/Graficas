#pragma once
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

class CTransform {
public:
	CTransform();
	~CTransform();

private:
	vec3 m_Rot;
	vec3 m_Scale;
	vec3 m_Tras;

public:
	
	mat4 getMatrix();
	void setRot(float inX, float inY, float inZ);
	void setScale(vec3 inScale);
	void setTras(vec3 inTras);

};

