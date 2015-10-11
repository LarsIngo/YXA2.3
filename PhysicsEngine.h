#pragma once

class PhysicsEngine
{
private:

protected:

public:
	PhysicsEngine();
	~PhysicsEngine();

	void Update(float updateRate, PointerList<Object>* mObjectList);
};

PhysicsEngine::PhysicsEngine()
{

}

PhysicsEngine::~PhysicsEngine()
{

}

void PhysicsEngine::Update(float updateRate, PointerList<Object>* mObjectList)
{
	//TODO COMPUTESHADER
	//Step 1: Move all objects
	//Step 2: Collison detection and add to a intersection objects to a list
	//Step 3: Move all intersecting objects in list back one frame
	//Step 4: Calculate new speeds for objects in list 
}