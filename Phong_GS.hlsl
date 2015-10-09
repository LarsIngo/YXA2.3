struct GSInput
{
	float4 position : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float4 worldPos : WORLDPOSITION;
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float4 worldPos : WORLDPOSITION;
};

[maxvertexcount(3)]
void GS_main(triangle GSInput input[3], inout TriangleStream<VSOutput> TriStream)
{
	VSOutput output;

	for (int i = 0; i < 3; i++)
	{
		output.position = input[i].position;
		output.uv = input[i].uv;
		output.normal = input[i].normal;
		output.worldPos = input[i].worldPos;
		TriStream.Append(output);
	}

	TriStream.RestartStrip();
}