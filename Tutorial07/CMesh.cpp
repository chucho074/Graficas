#include "CMesh.h"

CMesh::CMesh()
{
}

CMesh::~CMesh()
{
}

PRIMITIVE_TOPOLOGY * CMesh::getTopolgy() {
	return &m_Topology;
}

CTransform * CMesh::getTransform() {
	return &m_LocalTransform;
}

CBuffer * CMesh::getVB() {
	return &m_VBuffer;
}

CBuffer * CMesh::getIB() {
	return &m_IBuffer;
}

mat4 * CMesh::getFinalMatrix() {
	return &m_Final;
}

void CMesh::setTopology(PRIMITIVE_TOPOLOGY inTopology) {
	m_Topology = inTopology;
}

void CMesh::setFinalMatrix(mat4 inMatrix) {
	m_Final = inMatrix;
}
