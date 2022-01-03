#pragma once

#include <Common.h>
#include <Rendering/Common/UploadBuffer.h>
#include <functional>

using Microsoft::WRL::ComPtr;

class IRenderable;
class IVertexData;
class Mesh;
struct FrameResource;

class IRenderer
{
public:
	virtual ~IRenderer() {};
	virtual void Init(HWND window, int width, int height) = 0;
	virtual void FinaliseInit() = 0;
	virtual void Render(
		float deltaTime,
		std::vector<std::shared_ptr<IRenderable>>& renderableObjects,
		FrameResource* currentFrameResources,
		std::function<void(int)> onNewFenceValue) = 0;
	virtual void AddNewFence(std::function<void(int)> onNewFenceValue) = 0;
	virtual void Shutdown() = 0;
	virtual void CreateRootSignature(ComPtr<ID3DBlob>& serializedRootSignature, ComPtr<ID3D12RootSignature>& outRootSignature) = 0;
	virtual void CreateMesh(std::weak_ptr<Mesh>& meshPtr, const void* vertexData, const UINT vertexDataCount, const UINT vertexDataByteSize, const std::vector<std::uint16_t>& indices) = 0;
protected:
	virtual ComPtr<ID3D12Device> GetDevice() const = 0;
public:
	virtual void CreateConstantBufferDescriptorHeaps(int16_t frameResourceCount, int32_t renderableObjectCount) = 0;

	template<typename T>
	std::unique_ptr<UploadBuffer<T>> CreateConstantBuffer(UINT elementCount)
	{
		return std::make_unique<UploadBuffer<T>>(GetDevice().Get(), elementCount, true);
	}

	virtual void CreateConstantBufferView(D3D12_GPU_VIRTUAL_ADDRESS cbvGpuAddress, UINT cbvByteSize, int32_t handleOffset) = 0;
	virtual void CreateGraphicsPipelineState(
		ComPtr<ID3D12PipelineState>& pso,
		ComPtr<ID3D12RootSignature>& rootSignature,
		std::vector<D3D12_INPUT_ELEMENT_DESC>& inputLayout,
		ComPtr<ID3DBlob>& vertexShaderByteCode,
		ComPtr<ID3DBlob>& pixelShaderByteCode) = 0;
	virtual void BuildFrameResources(std::vector<std::unique_ptr<FrameResource>>& outFrameResourcesList, int frameResourcesCount, int objectCount) = 0;
	virtual UINT64 GetLastCompletedFence() = 0;
	virtual void WaitForFence(UINT64 fenceValue) = 0;
	virtual void SetPassCBVOffset(int32_t offset) = 0;
};
