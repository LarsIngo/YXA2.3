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
	Object(Object& other);
	Object& operator=(Object& other);

	Model* GetModel() { return mModel; }
	PhysicsBlob* GetPhysicsBlob() { return mPhysicsBlob; }

	void SetPhysicsBlob(XMFLOAT3 gravity, XMFLOAT3 velocity, XMFLOAT3 angularVelocity, float frictionCoefficent)
	{
		if (mPhysicsBlob != nullptr)
		{
			delete mPhysicsBlob;
		}
		mPhysicsBlob = new PhysicsBlob(gravity, velocity, angularVelocity, frictionCoefficent);
	}
	void SetPhysicsBlob(PhysicsBlob* physicsBlob)
	{
		if (mPhysicsBlob != nullptr)
		{
			delete mPhysicsBlob;
		}
		mPhysicsBlob = new PhysicsBlob(*physicsBlob);
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

Object::Object(Object& other) : Entity(other)
{
	mModel = other.GetModel();
	if (other.GetPhysicsBlob() != nullptr)
	{
		mPhysicsBlob = new PhysicsBlob(*other.GetPhysicsBlob());
	}
	else
	{
		mPhysicsBlob = nullptr;
	}
}

Object& Object::operator=(Object& other)
{
	if(this != &other)
	{
		mModel = other.GetModel();
		if (mPhysicsBlob != nullptr)
		{
			delete mPhysicsBlob;
		}
		if (other.GetPhysicsBlob() != nullptr)
		{
			mPhysicsBlob = new PhysicsBlob(*other.GetPhysicsBlob());
		}
		else
		{
			mPhysicsBlob = nullptr;
		}
	}
	return *this;
}