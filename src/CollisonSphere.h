#pragma once
#include "CollisonBlob.h"

class CollisonSphere : public CollisonBlob
{
private:
	float mRadius;
	BoundingSphere* mBoundingSphere;
protected:

public:
	CollisonSphere(XMFLOAT3 worldPosCenter, float radius);
	~CollisonSphere();

	//bool Intersect(CollisonBlob* otherCollisonBlob);

	BoundingSphere* GetBoundingSphere() { return mBoundingSphere; }
};

CollisonSphere::CollisonSphere(XMFLOAT3 worldPosCenter, float radius) : CollisonBlob(worldPosCenter)
{
	mId = 1;
	mRadius = radius;
	mBoundingSphere = new BoundingSphere(mWorldPosCenter, radius);
}

CollisonSphere::~CollisonSphere()
{
	delete mBoundingSphere;
}
//
//bool CollisonSphere::Intersect(CollisonBlob* otherCollisonBlob)
//{
//	if (otherCollisonBlob->GetID() == 0)
//	{
//		CollisonBox* otherCollisonBox = (CollisonBox*)otherCollisonBlob;
//		return mBoundingSphere->Intersects(*otherCollisonBox->GetBoundingBox());
//	}
//	else if (otherCollisonBlob->GetID() == 1)
//	{
//		CollisonSphere* otherCollisonSphere = (CollisonSphere*)otherCollisonBlob;
//		return mBoundingSphere->Intersects(*otherCollisonSphere->GetBoundingSphere());
//	}
//}