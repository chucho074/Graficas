#include "CBuffer.h"

CBuffer::CBuffer() {

}

CBuffer::~CBuffer() {
	SAFE_RELEASE(m_Buffer);
}



