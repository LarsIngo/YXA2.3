RWTexture2D<float4> output : register(u0);

Texture2D<float4> input0 : register(t0);
Texture2D<float4> input1 : register(t1);

SamplerState sampAni;

cbuffer constBuffer
{
	float4 pad; //camWorldPos
};

[numthreads(32, 24, 1)]
void CS_main(uint3 threadID : SV_DispatchThreadID, uint groupIndex : SV_GroupIndex, uint3 groupThreadID : SV_GroupThreadID, uint3 groupID : SV_GroupID)
{
	output[threadID.xy] = input0[threadID.xy];

	if (threadID.x > pad.x && threadID.y > pad.y)
	{
		float2 test = float2(threadID.x - pad.x, threadID.y - pad.y);
		output[threadID.xy] = input1[test];
	}
	

}

