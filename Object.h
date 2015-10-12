#pragma once
#include "Entity.h"
#include "Model.h"
#include "PhysicsBlob.h"

class Object : public Entity
{
private:

protected:
	Model* mModel;
	PhysicsBlob* mPhysicsBlob;
public:
	Object(Model* model);
	~Object();

	Model* GetModel() { return mModel; }
	PhysicsBlob* GetPhysicsBlob() { return mPhysicsBlob; }

	void SetPhysicsBlob(XMFLOAT3 gravity, XMFLOAT3 velocity, XMFLOAT3 angularVelocity, float frictionCoefficent)
	{
		mPhysicsBlob = new PhysicsBlob(gravity, velocity, angularVelocity, frictionCoefficent);
	}
};

Object::Object(Model* model) : Entity()
{
	mModel = model;
	mPhysicsBlob = nullptr;
}

Object::~Object()
{
	if(mPhysicsBlob != nullptr)
	{
		delete mPhysicsBlob;
	}
}