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
	int id;
	XMFLOAT3 mWorldPosCenter;
public:
	CollisonBlob(XMFLOAT3 worldPosCenter);
	virtual ~CollisonBlob();

	virtual XMFLOAT3 Intersect(CollisonBlob* other) = 0;

	int GetID() { return id; }
	XMFLOAT3 GetWorldPosCenter() { return mWorldPosCenter; }
};

CollisonBlob::CollisonBlob(XMFLOAT3 worldPosCenter)
{
	id = -1;
	mWorldPosCenter = worldPosCenter;
}

CollisonBlob::~CollisonBlob()
{

}