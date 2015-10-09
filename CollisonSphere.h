#pragma once
#include "CollisonBlob.h"

class CollisonSphere : public CollisonBlob
{
private:
	float mRadius;
protected:

public:
	CollisonSphere(XMFLOAT3 worldPosCenter, float radius);
	~CollisonSphere();

	XMFLOAT3 Intersect(CollisonBlob* other);

	float GetRadius() { return mRadius; }
};

CollisonSphere::CollisonSphere(XMFLOAT3 worldPosCenter, float radius) : CollisonBlob(worldPosCenter)
{
	id = 0;
	mRadius = radius;
}

CollisonSphere::~CollisonSphere()
{

}

XMFLOAT3 CollisonSphere::Intersect(CollisonBlob* otherBlob)
{
	//XMFLOAT3 thisToOther = Sub(otherBlob->GetWorldPosCenter(), GetWorldPosCenter());
	//if (otherBlob->GetID() == 0)
	//{
	//	CollisonSphere* other = (CollisonSphere*)otherBlob;
	//	if (this->mRadius + other->mRadius < Length(thisToOther))
	//	{
	//		return Normalize(thisToOther);
	//	}
	//}
	return XMFLOAT3(0.f, 0.f, 0.f);
}