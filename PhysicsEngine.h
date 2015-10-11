#pragma once

#include "ComputeShader.h"
#include "YXAMath.h"

class PhysicsEngine
{
private:
	ComputeShader* mPhysicsCS;
protected:

public:
	PhysicsEngine();
	~PhysicsEngine();

	void Update(float updateRate, PointerList<Object>* mObjectList);
};

PhysicsEngine::PhysicsEngine()
{
	//mPhysicsCS = new ComputeShader(,);
}

PhysicsEngine::~PhysicsEngine()
{

}

void PhysicsEngine::Update(float updateRate, PointerList<Object>* mObjectList)
{
	for (int i = 0; i < mObjectList->Size(); i++)
	{
		(*mObjectList)[i]->SetWorldPos(Add((*mObjectList)[i]->GetWorldPos(), Mul(XMFLOAT3(0.f, -1.f, 0.f), updateRate)));
	}
	//TODO COMPUTESHADER
	//Step 1: Move all objects
	//Step 2: Collison detection and add to a intersection objects to a list
	//Step 3: Move all intersecting objects in list back one frame
	//Step 4: Calculate new speeds for objects in list 
}