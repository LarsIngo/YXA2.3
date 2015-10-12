#pragma once
#include "CollisonBlob.h"

class CollisonBox : public CollisonBlob
{
private:
	XMFLOAT3 mExtends;
	BoundingBox* mBoundingBox;
protected:

public:
	CollisonBox(XMFLOAT3 worldPosCenter, XMFLOAT3 radius);
	~CollisonBox();

	//bool Intersect(CollisonBlob* otherCollisonBlob);

	BoundingBox* GetBoundingBox() { return mBoundingBox; }
};

CollisonBox::CollisonBox(XMFLOAT3 worldPosCenter, XMFLOAT3 extends) : CollisonBlob(worldPosCenter)
{
	id = 0;
	mExtends = extends;
	mBoundingBox = new BoundingBox(worldPosCenter, extends);
}

CollisonBox::~CollisonBox()
{
	delete mBoundingBox;
}

//bool CollisonBox::Intersect(CollisonBlob* otherCollisonBlob)
//{
//	if (otherCollisonBlob->GetID() == 0)
//	{
//		CollisonBox* otherCollisonBox = (CollisonBox*)otherCollisonBlob;
//		return mBoundingBox->Intersects(*otherCollisonBox->GetBoundingBox());
//	}
//	else if (otherCollisonBlob->GetID() == 1)
//	{
//		CollisonSphere* otherCollisonSphere = (CollisonSphere*)otherCollisonBlob;
//		return mBoundingBox->Intersects(*otherCollisonSphere->GetBoundingSphere());
//	}
//}