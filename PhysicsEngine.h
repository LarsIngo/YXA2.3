#pragma once

#include <vector>
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
	//Step 1: Move all objects
	for (int i = 0; i < mObjectList->Size(); i++)
	{
		Object* obj = (*mObjectList)[i];
		if (obj->GetPhysicsBlob() != nullptr)
		{
			//obj->SetWorldPos(Add(obj->GetWorldPos(), Mul(obj->GetPhysicsBlob()->GetGravity(), 1.f * updateRate)));
			PhysicsBlob* physBlob = obj->GetPhysicsBlob();
			obj->SetWorldPos(Add(obj->GetWorldPos(), Mul(obj->GetPhysicsBlob()->GetGravity(), updateRate)));
			XMFLOAT3 oldWorldPos = obj->GetWorldPos();
			XMFLOAT3 oldVelocity = physBlob->GetVelocity();
			XMFLOAT3 vt = Mul(physBlob->GetVelocity(), updateRate);
			XMFLOAT3 att = Mul(Mul(physBlob->GetGravity(), updateRate), updateRate);
			XMFLOAT3 newWorldPos = Add(oldWorldPos, Add(vt, Mul(att, 1.f/2.f)));
			XMFLOAT3 newVelocity = Add(oldVelocity, Mul(physBlob->GetGravity(), updateRate));
			obj->SetWorldPos(newWorldPos);
			physBlob->SetVelocity(newVelocity);
		}
	}

	//Step 2: Collison Detection
	struct CollidingObjects
	{
		Object* objX;
		Object* objY;
	};
	vector<CollidingObjects> CollidingList;
	for (int y = 0; y < mObjectList->Size(); y++)
	{
		for (int x = y + 1; x < mObjectList->Size(); x++)
		{
			Object* objX = (*mObjectList)[x];
			Object* objY = (*mObjectList)[y];
			if(objX != objY && objX->GetCollisonBlob() != nullptr && objY->GetCollisonBlob() != nullptr)
			{
				CollidingObjects collison;
				if(objX->GetCollisonBlob()->GetID() == 0 && objY->GetCollisonBlob()->GetID() == 0)
				{
					CollisonBox* colX = (CollisonBox*)objX->GetCollisonBlob();
					CollisonBox* colY = (CollisonBox*)objY->GetCollisonBlob();
					BoundingBox boxX;
					BoundingBox boxY;
					colX->GetBoundingBox()->Transform(boxX, objX->GetModelMat());
					colY->GetBoundingBox()->Transform(boxY, objY->GetModelMat());
					if (boxX.Intersects(boxY))
					{
						collison.objX = objX;
						collison.objY = objY;
						CollidingList.push_back(collison);
					}
				}
				else if (objX->GetCollisonBlob()->GetID() == 0 && objY->GetCollisonBlob()->GetID() == 1)
				{
					CollisonBox* colX = (CollisonBox*)objX->GetCollisonBlob();
					CollisonSphere* colY = (CollisonSphere*)objY->GetCollisonBlob();
					BoundingBox boxX;
					BoundingSphere sphereY;
					colX->GetBoundingBox()->Transform(boxX, objX->GetModelMat());
					colY->GetBoundingSphere()->Transform(sphereY, objY->GetModelMat());
					if (boxX.Intersects(sphereY))
					{
						collison.objX = objX;
						collison.objY = objY;
						CollidingList.push_back(collison);
					}
				}
				else if (objX->GetCollisonBlob()->GetID() == 1 && objY->GetCollisonBlob()->GetID() == 0)
				{
					CollisonSphere* colX = (CollisonSphere*)objX->GetCollisonBlob();
					CollisonBox* colY = (CollisonBox*)objY->GetCollisonBlob();
					BoundingSphere sphereX; 
					BoundingBox boxY;
					colX->GetBoundingSphere()->Transform(sphereX, objX->GetModelMat());
					colY->GetBoundingBox()->Transform(boxY, objX->GetModelMat());
					if (sphereX.Intersects(boxY))
					{
						collison.objX = objX;
						collison.objY = objY;
						CollidingList.push_back(collison);
					}
				}
				else if (objX->GetCollisonBlob()->GetID() == 1 && objY->GetCollisonBlob()->GetID() == 1)
				{
					CollisonSphere* colX = (CollisonSphere*)objX->GetCollisonBlob();
					CollisonSphere* colY = (CollisonSphere*)objY->GetCollisonBlob();
					BoundingSphere sphereX;
					BoundingSphere sphereY;
					colX->GetBoundingSphere()->Transform(sphereX, objX->GetModelMat());
					colY->GetBoundingSphere()->Transform(sphereY, objY->GetModelMat());
					if (sphereX.Intersects(sphereY))
					{
						collison.objX = objX;
						collison.objY = objY;
						CollidingList.push_back(collison);
					}
				}
			}
		}
	}

	//Step 3: Move all intersecting objects in list back one frame
	for (int i = 0; i < CollidingList.size(); i++)
	{
		Object* obj;
		obj = CollidingList.at(i).objX;
		if(obj->GetPhysicsBlob() != nullptr)
		{
			//obj->SetWorldPos(Add(obj->GetWorldPos(), Mul(obj->GetPhysicsBlob()->GetGravity(), -1.f * updateRate)));
			PhysicsBlob* physBlob = obj->GetPhysicsBlob();
			obj->SetWorldPos(Add(obj->GetWorldPos(), Mul(obj->GetPhysicsBlob()->GetGravity(), -1.f * updateRate)));
			XMFLOAT3 oldWorldPos = obj->GetWorldPos();
			XMFLOAT3 oldVelocity = physBlob->GetVelocity();
			XMFLOAT3 vt = Mul(physBlob->GetVelocity(), -1.f * updateRate);
			XMFLOAT3 att = Mul(Mul(physBlob->GetGravity(), -1.f * updateRate), -1.f * updateRate);
			XMFLOAT3 newWorldPos = Add(oldWorldPos, Add(vt, Mul(att, 1.f / 2.f)));
			XMFLOAT3 newVelocity = Add(oldVelocity, Mul(physBlob->GetGravity(), -1.f * updateRate));
			obj->SetWorldPos(newWorldPos);
			physBlob->SetVelocity(newVelocity);

			physBlob->SetVelocity(XMFLOAT3(0, 20, 0));
		}
		obj = CollidingList.at(i).objY;
		if (obj->GetPhysicsBlob() != nullptr)
		{
			//obj->SetWorldPos(Add(obj->GetWorldPos(), Mul(obj->GetPhysicsBlob()->GetGravity(), -1.f * updateRate)));
			PhysicsBlob* physBlob = obj->GetPhysicsBlob();
			obj->SetWorldPos(Add(obj->GetWorldPos(), Mul(obj->GetPhysicsBlob()->GetGravity(), -1.f * updateRate)));
			XMFLOAT3 oldWorldPos = obj->GetWorldPos();
			XMFLOAT3 oldVelocity = physBlob->GetVelocity();
			XMFLOAT3 vt = Mul(physBlob->GetVelocity(), -1.f * updateRate);
			XMFLOAT3 att = Mul(Mul(physBlob->GetGravity(), -1.f * updateRate), -1.f * updateRate);
			XMFLOAT3 newWorldPos = Add(oldWorldPos, Add(vt, Mul(att, 1.f / 2.f)));
			XMFLOAT3 newVelocity = Add(oldVelocity, Mul(physBlob->GetGravity(), -1.f * updateRate));
			obj->SetWorldPos(newWorldPos);
			physBlob->SetVelocity(newVelocity);

			physBlob->SetVelocity(XMFLOAT3(0, 20, 0));
		}
	}

	//Step 4: Calculate new speeds for objects in list 


	//TODO COMPUTESHADER
	//Step 1: Move all objects
	//Step 2: Collison detection and add to a intersection objects to a list
	//TODO: Step 3: Move all intersecting objects in list back one frame
	//TODO: Step 4: Calculate new speeds for objects in list 
}