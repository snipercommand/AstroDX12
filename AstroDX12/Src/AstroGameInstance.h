#pragma once

#include "Game.h"
#include "Common.h"
#include "Rendering/Common/UploadBuffer.h"
#include "Rendering/RenderData/Mesh.h"
#include "Maths/MathUtils.h"

using Microsoft::WRL::ComPtr;

struct RenderableObjectConstantData
{
    DirectX::XMFLOAT4X4 WorldViewProj = AstroTools::Maths::Identity4x4();
};

class AstroGameInstance final :
    public Game 
{
public:
    // Scene renderable objects building
    virtual void BuildConstantBuffers() override;
    virtual void BuildRootSignature() override;
    virtual void BuildShadersAndInputLayout() override;
    virtual void BuildSceneGeometry() override;
    virtual void BuildPipelineStateObject() override;

private:
    ComPtr<ID3D12RootSignature> m_rootSignature = nullptr;
    ComPtr<ID3D12DescriptorHeap> m_constantBufferViewHeap;
    std::unique_ptr<UploadBuffer<RenderableObjectConstantData>> m_renderableObjectConstantBuffer;
    std::unique_ptr<Mesh> m_testMesh = nullptr;

    ComPtr<ID3DBlob> m_vertexShaderByteCode = nullptr;
    ComPtr<ID3DBlob> m_pixelShaderByteCode = nullptr;

    std::vector<D3D12_INPUT_ELEMENT_DESC> m_inputLayout;
    ComPtr<ID3D12PipelineState> m_PipelineStateObject = nullptr;

    XMFLOAT4X4 m_worldMat = AstroTools::Maths::Identity4x4();
    XMFLOAT4X4 m_viewMat = AstroTools::Maths::Identity4x4();
    XMFLOAT4X4 m_projMat = AstroTools::Maths::Identity4x4();

    const float m_theta = 1.5f * XM_PI;
    const float m_phi = XM_PIDIV4;
    const float m_radius = 5.0f;
};

