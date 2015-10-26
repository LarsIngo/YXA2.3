RWTexture2D<float4> output : register(u0);

Texture2D<float4> input : register(t0);

SamplerState sampAni;

[numthreads(32, 24, 1)]
void CS_main(uint3 threadID : SV_DispatchThreadID, uint groupIndex : SV_GroupIndex, uint3 groupThreadID : SV_GroupThreadID, uint3 groupID : SV_GroupID)
{
	output[threadID.xy] = float4(0.0f, 0.0f, 1.0f, 1.0f);//input[threadID.xy];
}

