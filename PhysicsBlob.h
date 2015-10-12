#pragma once

class PhysicsBlob
{
private:
	XMFLOAT3 mGravity;
	XMFLOAT3 mVelocity;
	XMFLOAT3 mAngularVelocity;
	float mFrictionCoefficent;
protected:

public:
	PhysicsBlob(XMFLOAT3 gravity, XMFLOAT3 velocity, XMFLOAT3 angularVelocity, float frictionCoefficent);
	~PhysicsBlob();

	float GetFrictionCoefficent() { return mFrictionCoefficent; }

	XMFLOAT3 GetGravity() { return mGravity; }
	XMFLOAT3 GetVelocity() { return mVelocity; }
	XMFLOAT3 GetAngularVelocity() { return mAngularVelocity; }

	XMFLOAT4 GetGravityF4() { return XMFLOAT4(mGravity.x, mGravity.y, mGravity.z, 0.f); }
	XMFLOAT4 GetVelocityF4() { return XMFLOAT4(mVelocity.x, mVelocity.y, mVelocity.z, 0.f); }
	XMFLOAT4 GetAngularVelocityF4() { return XMFLOAT4(mAngularVelocity.x, mAngularVelocity.y, mAngularVelocity.z, 0.f); }

	XMVECTOR GetGravityVec() { return XMLoadFloat3(&mGravity); }
	XMVECTOR GetVelocityVec() { return XMLoadFloat3(&mVelocity); }
	XMVECTOR GetAngularVelocityVec() { return XMLoadFloat3(&mAngularVelocity); }

	void SetGravity(XMFLOAT3 gravity) { mGravity = gravity; }
	void SetVelocity(XMFLOAT3 velocity) { mVelocity = velocity; }
	void SetAngularVelocity(XMFLOAT3 angularVelocity) { mAngularVelocity = angularVelocity; }
	void SetFrictionCoefficent(float frictionCoefficent) { mFrictionCoefficent = frictionCoefficent; }
};

PhysicsBlob::PhysicsBlob(XMFLOAT3 gravity, XMFLOAT3 velocity, XMFLOAT3 angularVelocity, float frictionCoefficent)
{
	mGravity = gravity;
	mVelocity = velocity;
	mAngularVelocity = angularVelocity;
	mFrictionCoefficent = frictionCoefficent;
}

PhysicsBlob::~PhysicsBlob()
{

}