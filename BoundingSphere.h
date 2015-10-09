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
};

BoundingSphere::BoundingSphere(XMFLOAT3 worldPosCenter, float radius) : BoundingBlob(worldPosCenter)
{
	mRadius = radius;
}

BoundingSphere::~BoundingSphere()
{

}

XMFLOAT3 BoundingSphere::Intersect(BoundingBlob* other)
{
	return XMFLOAT3(0.f, 0.f, 0.f);
}