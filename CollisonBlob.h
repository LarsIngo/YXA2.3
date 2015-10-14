#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include "YXAMath.h"

using namespace DirectX;

class CollisonBlob
{
private:

protected:
	int mId;
	XMFLOAT3 mWorldPosCenter;
public:
	CollisonBlob(XMFLOAT3 worldPosCenter);
	virtual ~CollisonBlob();
	CollisonBlob(CollisonBlob& other);
	CollisonBlob& operator=(CollisonBlob& other);

	//virtual bool Intersect(CollisonBlob* otherCollisonBlob) = 0;

	int GetID() { return mId; }
	XMFLOAT3 GetWorldPosCenter() { return mWorldPosCenter; }
};

CollisonBlob::CollisonBlob(XMFLOAT3 worldPosCenter)
{
	mId = -1;
	mWorldPosCenter = worldPosCenter;
}

CollisonBlob::~CollisonBlob()
{

}

CollisonBlob::CollisonBlob(CollisonBlob& other)
{
	mId = other.GetID();
	mWorldPosCenter = other.GetWorldPosCenter();
}

CollisonBlob& CollisonBlob::operator=(CollisonBlob& other)
{
	if(this != &other)
	{
		mId = other.GetID();
		mWorldPosCenter = other.GetWorldPosCenter();
	}
	return *this;
}