RWTexture2D<float4> output : register(u0);

Texture2D<float4> input : register(t0);

cbuffer sFilter
{
	double filter[7][7];
	double pad;
};

SamplerState sampAni;

[numthreads(32, 24, 1)]
void CS_main(uint3 threadID : SV_DispatchThreadID, uint groupIndex : SV_GroupIndex, uint3 groupThreadID : SV_GroupThreadID, uint3 groupID : SV_GroupID)
{

	/*double sigma = 5.0, sum = 0.0;
	double f[7][7];

	for (int x = -3; x <= 3; x++)
	{
		for (int y = -3; y <= 3; y++)
		{
			f[x + 3][y + 3] = 1.0 / (2.0 * 3.14 * sigma * sigma) * exp(-(x*x + y*y) / (2.0 * sigma * sigma));

			sum += f[x + 3][y + 3];
		}
	}

	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			f[x][y] /= sum;
		}
	}

	float4 color = float4(0, 0, 0, 1);

	for (int x = -3; x < 3; x++) 
	{
		for (int y = -3; y < 3; y++) 
		{
			int a = threadID.x + x;
			int b = threadID.y + y;
			color += input[uint2(a, b)] * f[3 + x][3 + y];
		}
	}

	output[threadID.xy] = color;*/

	float3 color = float3(0, 0, 0);
	//double sum = 0.0;

	for (int x = -3; x < 3; x++) 
	{
		for (int y = -3; y < 3; y++) 
		{
			int a = threadID.x + x;
			int b = threadID.y + y;
			color += input[uint2(a, b)] * filter[3 + x][3 + y];
		}
	}

	output[threadID.xy] = float4(color, 1.f);

	//for (int x = 0; x < 7; x++)
	//{
	//	for (int y = 0; y < 7; y++)
	//	{
	//		sum += filter[x][y];
	//	}
	//}

	//if(threadID.x < 50)
	//{
	//	output[threadID.xy] = float4(sum, 0.f, 0.f, 1.f);
	//}
	//else
	//{ 
	//	output[threadID.xy] = color;
	//}

	//output[threadID.xy] = float4(1.f, 0.f, 0.f, 1.f);//color;
}

