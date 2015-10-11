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
};

Object::Object(Model* model) : Entity()
{
	mModel = model;
}

Object::~Object()
{

}