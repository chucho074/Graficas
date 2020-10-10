#include "CInputLayout.h"

CInputLayout::CInputLayout() {
	m_InputLayout = nullptr;
}

CInputLayout::~CInputLayout() {
	SAFE_RELEASE(m_InputLayout);
}

void CInputLayout::init(const std::vector<InputLayoutDesc>& inDesc) {
	for (int i = 0; i < inDesc.size(); ++i) {
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
