#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class BoundingBlob
{
private:

protected:
	int id;
	XMFLOAT3 mWorldPosCenter;
public:
	BoundingBlob(XMFLOAT3 worldPosCenter);
	virtual ~BoundingBlob();

	virtual XMFLOAT3 Intersect(BoundingBlob* other) = 0;

	int GetID() { return id; }
	XMFLOAT3 GetWorldPosCenter() { return mWorldPosCenter; }
};

BoundingBlob::BoundingBlob(XMFLOAT3 worldPosCenter)
{
	mWorldPosCenter = worldPosCenter;
}

BoundingBlob::~BoundingBlob()
{

}