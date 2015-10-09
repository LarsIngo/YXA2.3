#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class BoundingBlob
{
private:

protected:
	XMFLOAT3 mWorldPosCenter;
public:
	BoundingBlob(XMFLOAT3 worldPosCenter);
	virtual ~BoundingBlob();

	virtual XMFLOAT3 Intersect(BoundingBlob* other) = 0;
};

BoundingBlob::BoundingBlob(XMFLOAT3 worldPosCenter)
{
	mWorldPosCenter = worldPosCenter;
}

BoundingBlob::~BoundingBlob()
{

}