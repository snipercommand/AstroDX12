cbuffer cbPerObject : register(b0)
{
	float4x4 gWorld;
};

cbuffer cbPass : register(b1)
{
	float4x4 gView;
	float4x4 InvView;
	float4x4 gProj;
	float4x4 gInvProj;
	float4x4 gViewProj;
	float4x4 gInvViewProj;
	float3 gEyePosW;
	float gPerObjectPad1;	// Unused - padding
	float2 gRenderTargetSize;
	float2 gInvRenderTargetSize;
	float gNearZ;
	float gFarZ;
	float gTotalTime;
	float gDeltaTime;
};

struct VSInput
{
	float3 PosL  : POSITION;
	float4 Color : COLOR;
};

struct PSInput
{
	float4 PosH  : SV_POSITION;
	float4 Color : COLOR;
};

PSInput VS(VSInput i)
{
	PSInput o;

	// Transform to homogeneous clip space.
	float4 posW = mul(float4(i.PosL, 1.0f), gWorld);
	o.PosH = mul(posW, gViewProj);
	o.Color = i.Color;

	return o;
}

float4 PS(PSInput i) : SV_Target
{
	return i.Color;
}
