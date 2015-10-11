#pragma once
#include "CollisonBlob.h"

class CollisonBox : public CollisonBlob
{
private:
	XMFLOAT3 mRadius;
	BoundingBox* mBoundingBox;
protected:

public:
	CollisonBox(XMFLOAT3 worldPosCenter, XMFLOAT3 radius);
	~CollisonBox();

	XMFLOAT3 Intersect(CollisonBlob* other);

	XMFLOAT3 GetRadius() { return mRadius; }
};

CollisonBox::CollisonBox(XMFLOAT3 worldPosCenter, XMFLOAT3 radius) : CollisonBlob(worldPosCenter)
{
	id = 1;
	mRadius = radius;
}

CollisonBox::~CollisonBox()
{
	
}

XMFLOAT3 CollisonBox::Intersect(CollisonBlob* otherBlob)
{
	//XMFLOAT3 thisToOther = Sub(otherBlob->GetWorldPosCenter(), GetWorldPosCenter());
	//if (otherBlob->GetID() == 0)
	//{
	//	CollisonBox* other = (CollisonBox*)otherBlob;
	//	XMFLOAT3 otherRadius = other->GetRadius();
	//	if ((mRadius.x + otherRadius.x < Length(Project(thisToOther, XMFLOAT3(1.f, 0.f, 0.f))))  //TDOD ROTATE 
	//		&& (mRadius.y + otherRadius.y < Length(Project(thisToOther, XMFLOAT3(0.f, 1.f, 0.f))))
	//		&& (mRadius.z + otherRadius.z < Length(Project(thisToOther, XMFLOAT3(0.f, 0.f, 1.f)))))
	//	{
	//		return Normalize(thisToOther);
	//	}
	//}
	return XMFLOAT3(0.f, 0.f, 0.f);
}