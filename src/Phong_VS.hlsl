cbuffer constBuffer
{
	float4x4 M;
	float4x4 MVP;
};

struct VSInput
{
	float3 position : POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float4 worldPos : WORLDPOSITION;
};

VSOutput VS_main(VSInput input)
{
	VSOutput output;

	output.position = mul(float4(input.position, 1.f), MVP);
	output.uv = input.uv;
	output.normal = normalize(mul(input.normal, M));
	output.worldPos = mul(float4(input.position, 1.f), M);

	return output;
}