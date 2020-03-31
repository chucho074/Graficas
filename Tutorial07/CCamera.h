/**
* @LC		: 30/03/2020
* @file		: CCamera.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#pragma once
#include <windows.h>
#include "CBuffer.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

#define steps 0.025f
#define stepsRotation 0.25f

/**
* @brief	: CameraDesc.
* @bug		: No Bugs Known.
**/
struct DescCamera {
	vec3 Pos;	
	vec3 LAt;
	vec3 Up_desc;
	float Near;
	float FarPlane;
	float FOV;
	float Width;
	float Height;
};

/**
* @brief	: Class camera.
* @bug		: No Bugs Known.
**/
class CCamera {
public:
	
	/**
	* @brief	: Constructor of the class.
	* @bug		: No Bugs known.
	**/
	CCamera();

	/**
	* @brief	: Destroy of the class.
	* @bug		: No Bugs known.
	**/
	~CCamera();

	/**
	* @brief	: Initializer.
	* @param	: Needs a Camera Description.
	* @bug		: No Bugs known.
	**/
	int init(DescCamera Ref);

	vec3 Up;
	mat4 VM;
	mat4 PM;
	vec3 Front;
	vec3 Right;

	DescCamera Desc;

public:
	vec3 InitPos;
	vec3 EndPos;
	vec3 mDir;

	bool mIsClicked;
	bool mForward;
	bool mBack;
	bool mLeft;
	bool mRight;
	bool mUp;
	bool mDown;
	bool mRotateLeft;
	bool mRotateRight;

//--------------------------------------------------------------------------------------
// Setters
//--------------------------------------------------------------------------------------

	/**
	* @brief	: Setter for the position.
	* @param	: glm::vec3 for the pos.
	* @bug		: No Bugs known.
	**/
	void setPos(vec3 inPos);

	/**
	* @brief	: Setter for the look at.
	* @param	: glm::vec3 for the lAt.
	* @bug		: No Bugs known.
	**/
	void setLAt(vec3 inLAt);

	/**
	* @brief	: Setter for the Up.
	* @param	: glm::vec3 for the Up.
	* @bug		: No Bugs known.
	**/
	void setUp(vec3 inUp);

	/**
	* @brief	: Setter for the Front.
	* @param	: glm::vec3 for lAt & Pos.
	* @bug		: No Bugs known.
	**/
	void setFront(vec3 inAt, vec3 inPos);

	/**
	* @brief	: Setter for the Right.
	* @param	: glm::vec3 for Up & Front.
	* @bug		: No Bugs known.
	**/
	void setRight(vec3 inUp, vec3 inFront);

	/**
	* @brief	: Setter for the Up.
	* @param	: glm::vec3 for Front & Right.
	* @bug		: No Bugs known.
	**/
	void setUp(vec3 inFront, vec3 inRight);

	/**
	* @brief	: Setter for the FOV.
	* @param	: float for FOV	.
	* @bug		: No Bugs known.
	**/
	void setFOV(float inFOV);
	
	/**
	* @brief	: Setter for the Width.
	* @param	: float for Width.
	* @bug		: No Bugs known.
	**/
	void setWidth(float inWidth);
	
	/**
	* @brief	: Setter for the Height.
	* @param	: float for Height.
	* @bug		: No Bugs known.
	**/
	void setHeigth(float inHeigth);

	/**
	* @brief	: Setter for the Near.
	* @param	: float for Near.
	* @bug		: No Bugs known.
	**/
	void setNear(float inNear);

	/**
	* @brief	: Setter for the Far.
	* @param	: float for Far.
	* @bug		: No Bugs known.
	**/
	void setFar(float inFar);


//--------------------------------------------------------------------------------------
// Getters
//--------------------------------------------------------------------------------------


	/**
	* @brief	: Getter for the position.
	* @bug		: No Bugs known.
	**/
	vec3 getPos();
	
	/**
	* @brief	: Getter for the look at.
	* @bug		: No Bugs known.
	**/
	vec3 getLAt();
	
	/**
	* @brief	: Getter for the Up.
	* @bug		: No Bugs known.
	**/
	vec3 getUp();
	
	/**
	* @brief	: Getter for the FOV.
	* @bug		: No Bugs known.
	**/
	float getFOV();
	
	/**
	* @brief	: Getter for the Width.
	* @bug		: No Bugs known.
	**/
	float getWidth();
	
	/**
	* @brief	: Getter for the Height.
	* @bug		: No Bugs known.
	**/
	float getHeigth();
	
	/**
	* @brief	: Getter for the Near.
	* @bug		: No Bugs known.
	**/
	float getNear();
	
	/**
	* @brief	: Getter for the Far.
	* @bug		: No Bugs known.
	**/
	float getFar();

	/**
	* @brief	: Getter for the View Matrix.
	* @bug		: No Bugs known.
	**/
	mat4 getVM();


	/**
	* @brief	: Getter for the Projection Matrix.
	* @bug		: No Bugs known.
	**/
	mat4 getPM();


	//Functions

	/**
	* @brief	: Create the View Matrix.
	* @bug		: No Bugs known.
	**/
	virtual void updateVM();

	/**
	* @brief	: Move the VM.
	* @bug		: No Bugs known.
	**/
	virtual void move();

	/**
	* @brief	: Rotate the VM to right.
	* @param	: glm::vec3 for direction.
	* @bug		: No Bugs known.
	**/
	virtual void rotateRight(vec3 inDir);

	/**
	* @brief	: Rotate the VM to front.
	* @param	: glm::vec3 for direction.
	* @bug		: No Bugs known.
	**/
	virtual void rotateFront(vec3 inDir);

	/**
	* @brief	: Create the Projection Matrix.
	* @bug		: Can't use it 4 create de PM, have a error from the Lib.
	**/
	void updatePM();

	/**
	* @brief	: Rotate.
	* @bug		: No Bugs known.
	**/
	void rotate();

	/**
	* @brief	: Rotate.
	* @param	: glm::vec3 for mouseDirection.
	* @bug		: No Bugs known.
	**/
	void rotate(vec3 inDir);

	/**
	* @brief	: Rotate to Up.
	* @param	: glm::vec3 for mouseDirection.
	* @bug		: No Bugs known.
	**/
	void rotateUp(vec3 inDir);

	/**
	* @brief	: Create the View Matrix.
	* @bug		: No Bugs known.
	**/
	void createVM();

	/**
	* @brief	: Pressed key.
	* @param	: WPARAM for get the key.
	* @bug		: No Bugs known.
	**/
	void getKeyPress(WPARAM inKey);
	
	/**
	* @brief	: Release key.
	* @param	: WPARAM for get the key.
	* @bug		: No Bugs known.
	**/
	void getKeyRelease(WPARAM inKey);


	CBuffer m_CBNeverChanges;
	CBuffer m_CBChangesEveryFrame;
	CBuffer m_CBChangesOnResize;
};