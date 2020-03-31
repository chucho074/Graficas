/**
* @LC		: 30/03/2020
* @file		: CCamera.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CCamera.h"

CCamera::CCamera() {
	mIsClicked = false;
	mForward = false;
	mBack = false;
	mLeft = false;
	mRight = false;
	mUp = false;
	mDown = false;
	mRotateLeft = false;
	mRotateRight = false;
}

CCamera::~CCamera(){

}

int CCamera::init(DescCamera Ref) {
	//Set common values
	setPos(Ref.Pos);
	setLAt(Ref.LAt);
	setUp(Ref.Up_desc);
	setFOV(Ref.FOV);
	setWidth(Ref.Width);
	setHeigth(Ref.Height);
	setNear(Ref.Near);
	setFar(Ref.FarPlane);

	//Set Front, Right & Up

	createVM();
	updateVM();
	updatePM();

	return 0;
}

void CCamera::setPos(vec3 rPos) {
	Desc.Pos = rPos;
}

void CCamera::setLAt(vec3 rLAt) {
	Desc.LAt = rLAt;
}

void CCamera::setUp(vec3 rUp) {
	Desc.Up_desc = rUp;
}

void CCamera::setFront(vec3 rAt, vec3 rPos) {
	Front = normalize(Desc.LAt - Desc.Pos);
}

void CCamera::setRight(vec3 rUp, vec3 rFront) {
	Right = normalize(cross(Desc.Up_desc, Front));
}

void CCamera::setUp(vec3 rFront, vec3 rRight) {
	Up = normalize(cross(Front, Right));
}

void CCamera::setFOV(float rFOV) {
	Desc.FOV = rFOV;
}

void CCamera::setWidth(float rWidth) {
	Desc.Width = rWidth;
}

void CCamera::setHeigth(float rHeigth) {
	Desc.Height = rHeigth;
}

void CCamera::setNear(float rNear) {
	Desc.Near = rNear;
}

void CCamera::setFar(float rFar) {
	Desc.FarPlane = rFar;
}

vec3 CCamera::getPos() {
	return Desc.Pos;
}

vec3 CCamera::getLAt() {
	return Desc.LAt;
}

vec3 CCamera::getUp() {
	return Up;
}

float CCamera::getFOV() {
	return Desc.FOV;
}

float CCamera::getWidth() {
	return Desc.Width;
}

float CCamera::getHeigth() {
	return Desc.Height;
}

float CCamera::getNear() {
	return Desc.Near;
}

float CCamera::getFar() {
	return Desc.FarPlane;
}

mat4 CCamera::getVM() {
	return VM;
}

mat4 CCamera::getPM() {
	return PM;
}

void CCamera::updateVM() {
	Right =	{ VM[0][0], VM[0][1], VM[0][2] };
	Up =			{ VM[1][0], VM[1][1], VM[1][2] };
	Front =	{ VM[2][0], VM[2][1], VM[2][2] };
	Desc.LAt = Front + Desc.Pos;
}

void CCamera::updatePM() {
	PM = perspectiveFovLH(Desc.FOV, Desc.Width, Desc.Height, Desc.Near, Desc.FarPlane);
}

void CCamera::move() {
	if (mForward) {
		Desc.Pos += (Front * steps);
	}
	if (mBack) {
		Desc.Pos += (Front * -steps);
	}

	if (mLeft) {
		Desc.Pos += (Right * -steps);
	}
	if (mRight) {
		Desc.Pos += (Right * steps);
	}
	
	if (mUp) {
		Desc.Pos += (Up * steps);
	}
	if (mDown) {
		Desc.Pos += (Up * -steps);
	}

	mat4 Axis {
		Right.x, Right.y, Right.z, 0,
		Up.x,		  Up.y,			Up.z		, 0,
		Front.x, Front.y, Front.z, 0,
		0,			  0,			0,			  1
	};

	mat4 Pos {
		1, 0, 0, -Desc.Pos.x,
		0, 1, 0, -Desc.Pos.y,
		0, 0, 1, -Desc.Pos.z,
		0, 0, 0, 1
	};

	Pos *= Axis;

	VM = Pos;

	updateVM();
}

void CCamera::rotate() {
	if (mRotateLeft) {
		rotateFront({0.f, 0.f, stepsRotation});
	}
	if (mRotateRight) {
		rotateFront({ 0.f, 0.f, -stepsRotation });
	}
}

void CCamera::rotate(vec3 mouseDir) {
	rotateUp(mouseDir);
	rotateRight(mouseDir);
}

void CCamera::rotateUp(vec3 Dir) {
	float camcos = cosf(Dir.x/100.f);
	float camsin = sinf(Dir.x/100.f);

	mat4 RotX {
		camcos,  0.f, camsin,	0.f,
		0.f,	 1.f, 0.f,		0.f,
		-camsin, 0.f, camcos,	0.f,
		0.f,	 0.f, 0.f,		1.f
	};
	VM *= RotX;
	updateVM();
}

void CCamera::rotateRight(vec3 Dir) {
	float camcos = cosf(Dir.y / 100.f);
	float camsin = sinf(Dir.y / 100.f);

	mat4 RotY {
		1.f, 0.f,	  0.f,	  0.f, 
		0.f, camcos, -camsin, 0.f,
		0.f, camsin, camcos,  0.f,
		0.f, 0.f,	 0.f,	  1.f
	};
	VM *= RotY;
	updateVM();
}

void CCamera::rotateFront(vec3 Dir) {
	float camcos = cosf(Dir.z / 100.f);
	float camsin = sinf(Dir.z / 100.f);

	mat4 RotZ {
		camcos, -camsin,	0,	0.f,
		camsin, camcos, 0.f,0.f,
		0.f, 0.f,1.f, 0.f,
		0.f, 0.f,	0.f,	1.f
	};
	VM *= RotZ;
	updateVM();
}

void CCamera::getKeyPress(WPARAM key) {
	//Z Movement
	if (key == 'W') {
		mForward = true;
	}
	else if (key == 'S') {
		mBack = true;
	}
	//X Movement
	if (key == 'A') {
		mLeft = true;
	}
	else if (key == 'D') {
		mRight = true;
	}
	//Y Movement
	if (key == 'Q') {
		mUp = true;
	}
	else if (key == 'E') {
		mDown = true;
	}
#ifdef D_DIRECTX
	if (key == VK_LEFT) {
		mRotateLeft = true;
	}
	else if (key == VK_RIGHT) {
		mRotateRight = true;
	}
#elif OPENGL
	if (key == 263) {
		mRotateLeft = true;
	}
	else if (key == 262) {
		mRotateRight = true;
	}
#endif
}

void CCamera::getKeyRelease(WPARAM key) {
	if (key == 'W') {
		mForward = false;
	}
	else if (key == 'S') {
		mBack = false;
	}
	if (key == 'A') {
		mLeft = false;
	}
	else if (key == 'D') {
		mRight = false;
	}
	if (key == 'Q') {
		mUp = false;
	}
	else if (key == 'E') {
		mDown = false;
	}
#ifdef D_DIRECTX
	if (key == VK_LEFT) {
		mRotateLeft = false;
	}
	else if (key == VK_RIGHT) {
		mRotateRight = false;
	}
#elif OPENGL
	if (key == 263) {
		mRotateLeft = false;
	}
	else if (key == 262) {
		mRotateRight = false;
	}
#endif
}

void CCamera::createVM() {
	setFront(getLAt(), getPos());
	setRight(getUp(), Front);
	setUp(Front, Right);

	mat4 Axis {
		Right.x, Right.y, Right.z, 0,
		Up.x,		  Up.y,			Up.z		, 0,
		Front.x, Front.y, Front.z, 0,
		0,			  0,			0,			  1
	};

	mat4 Pos {
		1, 0, 0, -Desc.Pos.x,
		0, 1, 0, -Desc.Pos.y,
		0, 0, 1, -Desc.Pos.z,
		0, 0, 0, 1
	};
	VM = Pos * Axis;
}