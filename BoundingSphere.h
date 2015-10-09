#pragma once
#include "BoundingBlob.h"

class BoundingSphere : public BoundingBlob
{
private:
	float mRadius;
protected:

public:
	BoundingSphere(XMFLOAT3 worldPosCenter, float radius);
	~BoundingSphere();

	XMFLOAT3 Intersect(BoundingBlob* other);

	float GetRadius() { return mRadius; }
};

BoundingSphere::BoundingSphere(XMFLOAT3 worldPosCenter, float radius) : BoundingBlob(worldPosCenter)
{
	id = 0;
	mRadius = radius;
}

BoundingSphere::~BoundingSphere()
{

}

XMFLOAT3 BoundingSphere::Intersect(BoundingBlob* otherBlob)
{
	XMFLOAT3 otherBlobWorldPos = otherBlob->GetWorldPosCenter();
	XMFLOAT3 thisWorldPos = GetWorldPosCenter();
	XMFLOAT3 thisToOther = XMFLOAT3(otherBlobWorldPos.x - thisWorldPos.x, otherBlobWorldPos.y - thisWorldPos.y, otherBlobWorldPos.z - thisWorldPos.z);
	float length = sqrt(thisToOther.x * thisToOther.x + thisToOther.y * thisToOther.y + thisToOther.z * thisToOther.z);
	if (otherBlob->GetID() == 0)
	{
		BoundingSphere* other = (BoundingSphere*)otherBlob;
		if (this->mRadius + other->mRadius < length)
		{
			return XMFLOAT3(thisToOther.x/length, thisToOther.y/length, thisToOther.z/length);
		}
	}
	return XMFLOAT3(0.f, 0.f, 0.f);
}