#pragma once

#include <vector>
#include <d3d12.h>

namespace AstroTools::Rendering::InputLayout
{
	const std::vector<D3D12_INPUT_ELEMENT_DESC> IL_Pos_Color
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
}