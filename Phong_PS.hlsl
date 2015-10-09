Texture2D txDiffuse : register(t0);

SamplerState sampAni;

cbuffer constBuffer
{
	float4 camPos;
	float4 depth;
};

struct PSInput
{
	float4 position : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float4 worldPos : WORLDPOSITION;
};

struct PSOutput
{
	float4 diffuse : SV_TARGET0;
};

PSOutput PS_main(PSInput input) : SV_TARGET
{
	PSOutput output;

	//float d = dot(float3(0, 0, -1), input.normal);
	//output.diffuse = txDiffuse.Sample(sampAni, input.uv) * d;//float4(d,d,d, 1.f);
	output.diffuse = txDiffuse.Sample(sampAni, input.uv);
	//output.diffuse = float4(input.normal, 1.f);
	//output.diffuse = float4(1.f, 1.f, 1.f, 1.f);
	return output;
}