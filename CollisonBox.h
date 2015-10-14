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
	CollisonBox(CollisonBox& other);
	CollisonBox& operator=(CollisonBox& other);

	BoundingBox* GetBoundingBox() { return mBoundingBox; }
};

CollisonBox::CollisonBox(XMFLOAT3 worldPosCenter, XMFLOAT3 extends) : CollisonBlob(worldPosCenter)
{
	mId = 0;
	mExtends = extends;
	mBoundingBox = new BoundingBox(worldPosCenter, extends);
}

CollisonBox::~CollisonBox()
{
	delete mBoundingBox;
}

CollisonBox::CollisonBox(CollisonBox& other) : CollisonBlob(other)
{
	mExtends = other.mExtends;
	if(other.GetBoundingBox() != nullptr)
	{
		mBoundingBox = new BoundingBox(*other.GetBoundingBox());
	}
	else
	{
		mBoundingBox = nullptr;
	}
}

CollisonBox& CollisonBox::operator=(CollisonBox& other)
{
	if (this != &other)
	{
		mExtends = other.mExtends;
		if (mBoundingBox != nullptr)
		{
			delete mBoundingBox;
		}
		if (other.GetBoundingBox() != nullptr)
		{
			mBoundingBox = new BoundingBox(*other.GetBoundingBox());
		}
		else
		{
			mBoundingBox = nullptr;
		}
	}
	return *this;
}