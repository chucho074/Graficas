/**
* @LC		: 30/03/2020
* @file		: CCameraFP.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/02/2020
* @brief	: .
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include "CCamera.h"

/**
* @brief	: Class camera first person.
* @bug		: No Bugs Known.
**/
class CCameraFP : public CCamera {
public:
	/**
	* @brief	: Constructor of the class.
	* @bug		: No Bugs known.
	**/
	CCameraFP();

	/**
	* @brief	: Move the VM.
	* @bug		: No Bugs known.
	**/
	void move();

	/**
	* @brief	: Pressed key.
	* @param	: WPARAM for get the key.
	* @bug		: No Bugs known.
	**/
	void getKeyPress(WPARAM key);

	/**
	* @brief	: Release key.
	* @param	: WPARAM for get the key.
	* @bug		: No Bugs known.
	**/
	void getKeyRelease(WPARAM key);

	/**
	* @brief	: Rotate the VM to front.
	* @param	: glm::vec3 for direction.
	* @bug		: No Bugs known.
	**/
	void rotateFront(glm::vec3 Dir);
	
	/**
	* @brief	: Rotate the VM to right.
	* @param	: glm::vec3 for direction.
	* @bug		: No Bugs known.
	**/
	void rotateRight(glm::vec3 Dir);

	float m_maxFrontRotation;
	float m_maxRightRotation;
	float m_RightRotation;
	float m_FrontRotation;
};