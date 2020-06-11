/**
* @LC		: 08/06/2020
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

#include "CRenderTargetView.h"
#include "CTexture2D.h"
#include "CDepthStencilView.h"
#include "CVertexShader.h"
#include "CPixelShader.h"
#include "CInputLayout.h"


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

#ifdef D_DIRECTX
	/**
	* @brief	: Getter for the device.
	* @bug		: No Bugs known.
	**/
	void * getDevice();
#endif

	/**
	* @brief	: Create a Render Target View.
	* @param	: CTexture2D, CRenderTargetView.
	* @bug		: No Bugs known.
	**/
	HRESULT createRTV(CTexture2D & inTexture, CRenderTargetView & inRTV);

	/**
	* @brief	: Create a Texture in the Device.
	* @param	: CTexture2D.
	* @bug		: No Bugs known.
	**/
	HRESULT createTexture(CTexture2D & inTexture);

	/**
	* @brief	: Create a DepthStencilView in the Device.
	* @param	: CTexture2D, CDepthStencilView.
	* @bug		: No Bugs known.
	**/
	HRESULT createDSV(CTexture2D & inDStencil, CDepthStencilView & inDSView);
	
	/**
	* @brief	: Create a Vertex Shader in the Device.
	* @param	: CVertexShader.
	* @bug		: No Bugs known.
	**/
	HRESULT createVShader(CVertexShader & inVS);
	
	/**
	* @brief	: Create a Pixel Shader in the Device.
	* @param	: CPixelShader.
	* @bug		: No Bugs known.
	**/
	HRESULT createPShader(CPixelShader & inPS);

	/**
	* @brief	: Create a Pixel Shader in the Device.
	* @param	: CPixelShader.
	* @bug		: No Bugs known.
	**/
	HRESULT createInputLayoutDescFromVertexShaderSignature(CVertexShader & inVS, CInputLayout &inIL);


	void operator = (CDevice const&) = delete;
	

	DeviceDesc Desc;

#ifdef D_DIRECTX
	ID3D11Device * Device;
#endif 

};