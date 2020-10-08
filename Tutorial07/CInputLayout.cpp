#include "CInputLayout.h"

CInputLayout::CInputLayout() {
	m_IL = nullptr;
}

CInputLayout::~CInputLayout() {
	SAFE_RELEASE(m_IL);
}

void CInputLayout::init(InputLayoutDesc * inDesc, int inNumElements) {
	for (int i = 0; i < inNumElements; i++) {
		D3D11_INPUT_ELEMENT_DESC layout;
		layout.SemanticName = inDesc[i].semanticName.c_str();
		layout.SemanticIndex = inDesc[i].semanticIndex;
		layout.Format = (DXGI_FORMAT)inDesc[i].format;
		layout.InputSlot = inDesc[i].inputSlot;
		layout.AlignedByteOffset = inDesc[i].alignedByteOffset;
		layout.InputSlotClass = (D3D11_INPUT_CLASSIFICATION)inDesc[i].inputSlotClass;
		layout.InstanceDataStepRate = inDesc[i].instanceDataStepRate;
		m_Descriptors.push_back(layout);
	}
}
