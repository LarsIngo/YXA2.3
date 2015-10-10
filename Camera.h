#pragma once
#include "Entity.h"

class Camera : public Entity
{
private:
	XMINT2 mResolution;
	float mNearZ;
	float mFarZ;
	float mFOV;
protected:

public:
	Camera(XMINT2 resolution);
	~Camera();

	XMINT2 GetResolution() { return mResolution; }
	float GetNearZ() { return mNearZ; }
	float GetFarZ() { return mFarZ; }
	float GetFOV() { return mFOV; }
	void SetResolution(XMINT2 resolution) { mResolution = resolution; }
	void SetNearZ(float nearZ) { mNearZ = nearZ; }
	void SetFarZ(float farZ) { mFarZ = farZ; }
	void SetFOV(float fov) { mFOV = fov; }

	XMMATRIX GetViewMat() { return XMMatrixLookToLH(GetWorldPosVec(), XMVector4Transform(GetFrontDirectionVec(), GetRotationMat()), XMVector4Transform(GetUpDirectionVec(), GetRotationMat())); }
	XMMATRIX GetProjMat() { return XMMatrixPerspectiveFovLH(mFOV, (float)mResolution.x / mResolution.y, mNearZ, mFarZ); }
};

Camera::Camera(XMINT2 resolution) : Entity()
{
	mWorldPos = XMFLOAT3(0.f, 0.f, -1.f);
	mFrontDirection = XMFLOAT3(0.f, 0.f, 1.f);
	mResolution = resolution;
	mNearZ = 0.001f;
	mFarZ = 200.f;
	mFOV =  3.14f / 180 * 70;
}

Camera::~Camera()
{

}