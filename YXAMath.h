#pragma once

#include <DirectXMath.h>

using namespace DirectX;

XMFLOAT3 Normalize(XMFLOAT3 vec);
float Length(XMFLOAT3 vec);
XMFLOAT3 Project(XMFLOAT3 vec1, XMFLOAT3 vec2);
float Dot(XMFLOAT3 vec1, XMFLOAT3 vec2);
XMFLOAT3 Add(XMFLOAT3 vec1, XMFLOAT3 vec2);
XMFLOAT3 Sub(XMFLOAT3 vec1, XMFLOAT3 vec2);
XMFLOAT3 Mul(XMFLOAT3 vec1, XMFLOAT3 vec2);
XMFLOAT3 Mul(float f, XMFLOAT3 vec);
XMFLOAT3 Div(XMFLOAT3 vec1, XMFLOAT3 vec2);

XMFLOAT3 Normalize(XMFLOAT3 vec)
{
	float length = Length(vec);
	return XMFLOAT3(vec.x / length, vec.y / length, vec.z / length);
}

float Length(XMFLOAT3 vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

XMFLOAT3 Project(XMFLOAT3 vec1, XMFLOAT3 vec2)
{
	float length = Length(vec2);
	return Mul(Dot(vec1, vec2) / (length * length), vec2);
}

float Dot(XMFLOAT3 vec1, XMFLOAT3 vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

XMFLOAT3 Add(XMFLOAT3 vec1, XMFLOAT3 vec2)
{
	return XMFLOAT3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

XMFLOAT3 Sub(XMFLOAT3 vec1, XMFLOAT3 vec2)
{
	return XMFLOAT3(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

XMFLOAT3 Mul(XMFLOAT3 vec1, XMFLOAT3 vec2)
{
	return XMFLOAT3(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
}

XMFLOAT3 Mul(float f, XMFLOAT3 vec)
{
	return XMFLOAT3(f * vec.x, f * vec.y, f * vec.z);
}

XMFLOAT3 Div(XMFLOAT3 vec1, XMFLOAT3 vec2)
{
	return XMFLOAT3(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
}
