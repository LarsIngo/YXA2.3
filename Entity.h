#pragma once
#include <DirectXMath.h>
#include "CollisonBlob.h"
using namespace DirectX;

class Entity
{
private:

protected:
	XMFLOAT3 mWorldPos;
	XMFLOAT3 mRotation;
	XMFLOAT3 mScale;
	XMFLOAT3 mFrontDirection;
	XMFLOAT3 mUpDirection;

	CollisonBlob* mCollisonBlob;

	XMMATRIX GetRotationMat(){ return XMMatrixRotationRollPitchYawFromVector(GetRotationVec()); }
public:
	Entity();
	virtual ~Entity();

	void Translate(XMFLOAT3 worldPos);
	void Rotate(XMFLOAT3 rotation);
	void Scale(XMFLOAT3 scale);

	void Translate(XMVECTOR worldPos);
	void Rotate(XMVECTOR rotation);
	void Scale(XMVECTOR scale);

	void LookAt(XMFLOAT3 worldPos); //TODO
	void LookTo(XMFLOAT3 direction); //TODO
	void LookAt(XMVECTOR worldPosVec); //TODO
	void LookTo(XMVECTOR directionVec); //TODO
	
	void MoveRight(float move);
	void MoveUp(float move);
	void MoveFront(float move);

	void Yaw(float rot);
	void Pitch(float rot);
	void Roll(float rot);

	XMMATRIX GetModelMat();

	
	//GET & SET
	XMFLOAT3 GetWorldPos() { return mWorldPos; }
	XMFLOAT3 GetRotation() { return mRotation; }
	XMFLOAT3 GetScale() { return mScale; }
	XMFLOAT3 GetFrontDirection() { return mFrontDirection; }
	XMFLOAT3 GetUpDirection() { return mUpDirection; }

	XMFLOAT4 GetWorldPosF4() { return XMFLOAT4(mWorldPos.x, mWorldPos.y, mWorldPos.z, 0); }
	XMFLOAT4 GetRotationF4() { return XMFLOAT4(mRotation.x, mRotation.y, mRotation.z, 0); }
	XMFLOAT4 GetScaleF4() { return XMFLOAT4(mScale.x, mScale.y, mScale.z, 0); }
	XMFLOAT4 GetFrontDirectionF4() { return XMFLOAT4(mFrontDirection.x, mFrontDirection.y, mFrontDirection.z, 0); }
	XMFLOAT4 GetUpDirectionF4() { return XMFLOAT4(mUpDirection.x, mUpDirection.y, mUpDirection.z, 0); }

	XMVECTOR GetWorldPosVec() { return XMLoadFloat3(&mWorldPos); }
	XMVECTOR GetRotationVec() { return XMLoadFloat3(&mRotation); }
	XMVECTOR GetScaleVec() { return XMLoadFloat3(&mScale); }
	XMVECTOR GetFrontDirectionVec() { return  XMLoadFloat3(&mFrontDirection); }
	XMVECTOR GetUpDirectionVec() { return  XMLoadFloat3(&mUpDirection); }

	void SetWorldPos(XMFLOAT3 worldPos) { mWorldPos = worldPos; }
	void SetRotation(XMFLOAT3 rotation) { mRotation = rotation; }
	void SetScale(XMFLOAT3 scale) { mScale = scale; }
	void SetFrontDirection(XMFLOAT3 frontDirection) { mFrontDirection = frontDirection; }
	void SetUpDirection(XMFLOAT3 upDirection) { mUpDirection = upDirection; }

	void SetWorldPos(XMVECTOR worldPos) { XMStoreFloat3(&mWorldPos, worldPos); }
	void SetRotation(XMVECTOR rotation) { XMStoreFloat3(&mRotation, rotation); }
	void SetScale(XMVECTOR scale) { XMStoreFloat3(&mScale, scale); }
	void SetFrontDirection(XMVECTOR frontDirection) { XMStoreFloat3(&mFrontDirection, frontDirection); }
	void SetUpDirection(XMVECTOR upDirection) { XMStoreFloat3(&mUpDirection, upDirection); }
};

Entity::Entity()
{
	mWorldPos = XMFLOAT3(0.f, 0.f, 0.f);
	mRotation = XMFLOAT3(0.f, 0.f, 0.f);
	mScale = XMFLOAT3(1.f, 1.f, 1.f);
	mFrontDirection = XMFLOAT3(0.f, 0.f, -1.f);
	mUpDirection = XMFLOAT3(0.f, 1.f, 0.f);
}

Entity::~Entity()
{

}

void Entity::Translate(XMFLOAT3 worldPos)
{
	mWorldPos.x += worldPos.x;
	mWorldPos.y += worldPos.y;
	mWorldPos.z += worldPos.z;
}

void Entity::Rotate(XMFLOAT3 rotation)
{
	mRotation.x += rotation.x;
	mRotation.y += rotation.y;
	mRotation.z += rotation.z;
}

void Entity::Scale(XMFLOAT3 scale)
{
	mScale.x += scale.x;
	mScale.y += scale.y;
	mScale.z += scale.z;
}

void Entity::Translate(XMVECTOR worldPosV)
{
	XMFLOAT3 worldPos;
	XMStoreFloat3(&worldPos, worldPosV);
	mWorldPos.x += worldPos.x;
	mWorldPos.y += worldPos.y;
	mWorldPos.z += worldPos.z;
}

void Entity::Rotate(XMVECTOR rotationV)
{
	XMFLOAT3 rotation;
	XMStoreFloat3(&rotation, rotationV);
	mRotation.x += rotation.x;
	mRotation.y += rotation.y;
	mRotation.z += rotation.z;
}

void Entity::Scale(XMVECTOR scaleV)
{
	XMFLOAT3 scale;
	XMStoreFloat3(&scale, scaleV);
	mScale.x += scale.x;
	mScale.y += scale.y;
	mScale.z += scale.z;
}

void Entity::LookAt(XMFLOAT3 worldPos)
{
	XMVECTOR thisToOtherV = XMVectorSet(worldPos.x - mWorldPos.x, worldPos.y - mWorldPos.y, worldPos.z - mWorldPos.z, 0.f);
	thisToOtherV = XMVector3Normalize(thisToOtherV);
	XMFLOAT3 thisToOther;
	XMStoreFloat3(&thisToOther, thisToOtherV);
	//float dot = thisToOther.x, 
}

void Entity::LookTo(XMFLOAT3 direction)
{

	//mRotation = direction; 
}

void Entity::LookAt(XMVECTOR worldPosVec)
{
	XMFLOAT3 worldPos;
	XMStoreFloat3(&worldPos, worldPosVec);
}

void Entity::LookTo(XMVECTOR directionVec)
{
	XMFLOAT3 direction;
	XMStoreFloat3(&direction, directionVec);
}

void Entity::MoveRight(float move)
{
	SetWorldPos(GetWorldPosVec() + XMVector4Transform(XMVectorSet(move, 0.f, 0.f, 0.f), GetRotationMat()));
}

void Entity::MoveUp(float move)
{
	SetWorldPos(GetWorldPosVec() + XMVector4Transform(XMVectorSet(0.f, move, 0.f, 0.f), GetRotationMat()));
}

void Entity::MoveFront(float move)
{
	SetWorldPos(GetWorldPosVec() + XMVector4Transform(XMVectorSet(0.f, 0.f, move, 0.f), GetRotationMat()));
}

void Entity::Yaw(float rot)
{
	//SetRotation(GetRotationVec() + XMVector4Transform(XMVectorSet(rot, 0.f, 0.f, 0.f), GetRotationMat()));
	mRotation.x += rot;
	if (mRotation.x > 6.28f)
	{
		SetRotation(XMFLOAT3(GetRotation().x - 6.28f, GetRotation().y, GetRotation().z));

	}
	else if (mRotation.x < -6.28f)
	{
		SetRotation(XMFLOAT3(GetRotation().x + 6.28f, GetRotation().y, GetRotation().z));
	}
}

void Entity::Pitch(float rot)
{
	//SetRotation(GetRotationVec() + XMVector4Transform(XMVectorSet(0.f, rot, 0.f, 0.f), GetRotationMat()));
	mRotation.y += rot;
	if (mRotation.y > 6.28f)
	{
		SetRotation(XMFLOAT3(GetRotation().x, GetRotation().y - 6.28f, GetRotation().z));
	}
	else if (mRotation.y < -6.28f)
	{
		SetRotation(XMFLOAT3(GetRotation().x, GetRotation().y + 6.28f, GetRotation().z));
	}
}

void Entity::Roll(float rot)
{
	//SetRotation(GetRotationVec() + XMVector4Transform(XMVectorSet(0.f, 0.f, rot, 0.f), GetRotationMat()));
	if (GetRotation().z > 6.28f)
	{
		SetRotation(XMFLOAT3(GetRotation().x, GetRotation().y, GetRotation().z - 6.28f));
	}
	else if (GetRotation().z < -6.28f)
	{
		SetRotation(XMFLOAT3(GetRotation().x, GetRotation().y, GetRotation().z + 6.28f));
	}
}


XMMATRIX Entity::GetModelMat()
{
	//TODO ROTATION & SCALE
	//XMMATRIX rotation = XMMatrixRotationRollPitchYawFromVector(GetRotationVec());
	XMMATRIX worldPosMat = XMMatrixTranslationFromVector(GetWorldPosVec());
	XMMATRIX scaleMat = XMMatrixScalingFromVector(GetScaleVec());
	return scaleMat * GetRotationMat() * worldPosMat;
}