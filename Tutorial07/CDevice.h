/**
* @LC		: 24/02/2020
* @file		: CDevice.h
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
#include "Defines.h"
#include "Includes.h"


/**
* @brief	: Device Desc.
* @bug		: No Bugs known.
**/
struct DeviceDesc {
	DeviceDesc::DeviceDesc() {
		DriverType = DRIVER_TYPE_UNKNOWN;
		DriverTypes[0] = DRIVER_TYPE_UNKNOWN;
		DriverTypes[1] = DRIVER_TYPE_UNKNOWN;
		DriverTypes[2] = DRIVER_TYPE_UNKNOWN;
		DeviceFlags = 0;
		FeatureLevels[0] = FEATURE_LEVEL_9_1;
		FeatureLevels[1] = FEATURE_LEVEL_9_1;
		FeatureLevels[2] = FEATURE_LEVEL_9_1;
		numFeatureLevels = 0;
	}
	DRIVER_TYPE		DriverType;
	DRIVER_TYPE		DriverTypes[3];
	unsigned int	DeviceFlags;
	FEATURE_LEVEL	FeatureLevels[3];
	unsigned int	numFeatureLevels;
};

/**
* @brief	: CDevice class.
* @bug		: No Bugs known.
**/
class CDevice {
public:	
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs known.
	**/
	CDevice();	

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CDevice();

	/**
	* @brief	: Initializer.
	* @bug		: No Bugs known.
	**/
	void init(DeviceDesc inDesc);

	/**
	* @brief	: Getter for the device.
	* @bug		: No Bugs known.
	**/
#ifdef D_DIRECTX
	void * getDevice();
#endif
	
	void operator = (CDevice const&) = delete;
	
	DeviceDesc Desc;

#ifdef D_DIRECTX
	ID3D11Device * Device;
#endif 

};