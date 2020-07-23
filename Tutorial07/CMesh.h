#pragma once
#include "CTransform.h"
#include "CBuffer.h"
#include "Defines.h"

class CMesh {
public:
	CMesh();
	~CMesh();

	PRIMITIVE_TOPOLOGY *getTopolgy();
	CTransform *getTransform();
	CBuffer * getVB();
	CBuffer * getIB();
	mat4 * getFinalMatrix();

	void setTopology(PRIMITIVE_TOPOLOGY inTopology);
	void setFinalMatrix(mat4 inMatrix);
private:
	CBuffer m_VBuffer;
	CBuffer m_IBuffer;
	PRIMITIVE_TOPOLOGY m_Topology;
	CTransform m_LocalTransform;
	mat4 m_Final;
};

