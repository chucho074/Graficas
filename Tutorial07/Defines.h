#pragma once


/**
* @brief	: .
* @bug		: No Bugs known.
**/
struct SubresourceData {
	const void * psysMem = nullptr;
	unsigned int sysMemPitch = 0;
	unsigned int sysMemSlicePitch = 0;
};

/**
* @brief	: Descriptor for Buffers.
* @bug		: No Bugs known.
**/
struct BufferDesc {
	unsigned int byteWidth = 0;
	unsigned short usage = 0;
	unsigned int bindFlags = 0;
	unsigned int cpuAccessFlags = 0;
	unsigned int miscFlags = 0;
	unsigned int structureByteStride = 0;
	SubresourceData SRD;
};