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

	void Update(float updateRate, PointerList<Object>* objectList);
};

PhysicsEngine::PhysicsEngine()
{
	//mPhysicsCS = new ComputeShader(,);
}

PhysicsEngine::~PhysicsEngine()
{

}

void PhysicsEngine::Update(float updateRate, PointerList<Object>* objectList)
{
	//Step 0: Save old objects
	PointerList<Object> oldObjectList(objectList->Size(), 1);
	for (int i = 0; i < objectList->Size(); i++) 
	{
		oldObjectList.Add(new Object(*(*objectList)[i]));
	}

	//Step 1: Move all objects
	for (int i = 0; i < objectList->Size(); i++)
	{
		Object* obj = (*objectList)[i];
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
		//Object* objX;
		//Object* objY;
		//int xPos;
		//int yPos;
		int pos[2];
	};
	vector<CollidingObjects> CollidingList;
	for (int y = 0; y < objectList->Size(); y++)
	{
		for (int x = y + 1; x < objectList->Size(); x++)
		{
			Object* objX = (*objectList)[x];
			Object* objY = (*objectList)[y];
			if(objX != objY && objX->GetCollisonBlob() != nullptr && objY->GetCollisonBlob() != nullptr)
			{
				//CollidingObjects collison;
				if(objX->GetCollisonBlob()->GetID() == 0 && objY->GetCollisonBlob()->GetID() == 0)
				{
					CollisonBox* colX = (CollisonBox*)objX->GetCollisonBlob();
					CollisonBox* colY = (CollisonBox*)objY->GetCollisonBlob();
					BoundingBox boxX;
					BoundingBox boxY;
					//BoundingBox* bX = colX->GetBoundingBox();
					//BoundingBox* bY = colY->GetBoundingBox();
					colX->GetBoundingBox()->Transform(boxX, objX->GetModelMat());
					colY->GetBoundingBox()->Transform(boxY, objY->GetModelMat());
					if (boxX.Intersects(boxY))
					{
						//CollidingObjects collison;
						//collison.objX = objX;
						//collison.objY = objY;
						//CollidingList.push_back(collison);
						CollidingObjects collison;
						//collison.xPos = x;
						//collison.yPos = y;
						collison.pos[0] = x;
						collison.pos[1] = y;
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
						/*collison.objX = objX;
						collison.objY = objY;*/
						CollidingObjects collison;
						//collison.xPos = x;
						//collison.yPos = y;
						collison.pos[0] = x;
						collison.pos[1] = y;
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
						/*collison.objX = objX;
						collison.objY = objY;*/
						CollidingObjects collison;
						//collison.xPos = x;
						//collison.yPos = y;
						collison.pos[0] = x;
						collison.pos[1] = y;
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
						/*collison.objX = objX;
						collison.objY = objY;*/
						CollidingObjects collison;
						//collison.xPos = x;
						//collison.yPos = y;
						collison.pos[0] = x;
						collison.pos[1] = y;
						CollidingList.push_back(collison);
					}
				}
			}
		}
	}

	//Step 3: Move all intersecting objects in list back one frame by set it to old pos
	for (int i = 0; i < CollidingList.size(); i++)
	{
		for (int m = 0; m < 2; m++)
		{
			Object* obj = (*objectList)[CollidingList.at(i).pos[m]];
			if (obj->GetPhysicsBlob() != nullptr)
			{
				objectList->ReplaceAt(CollidingList.at(i).pos[m], oldObjectList[CollidingList.at(i).pos[m]]);
			}
		}

		//Object* obj;
		//obj = (*objectList)[CollidingList.at(i).xPos];
		//if(obj->GetPhysicsBlob() != nullptr)
		//{
		//	Object* newObj = obj;
		//	XMFLOAT3 newPos = newObj->GetWorldPos();
		//	Object* oldObj = oldObjectList[CollidingList.at(i).xPos];
		//	XMFLOAT3 oldPos = oldObj->GetWorldPos();
		//	newObj = oldObj;
		//	XMFLOAT3 newPos2 = newObj->GetWorldPos();
		//	objectList->ReplaceAt(CollidingList.at(i).xPos, oldObjectList[CollidingList.at(i).xPos]);
		//	//TODO *(*objectList)[CollidingList.at(i).xPos] = *oldObjectList[CollidingList.at(i).xPos];
		//	XMFLOAT3 newPos3 = (*objectList)[CollidingList.at(i).xPos]->GetWorldPos();
		//	int o = 5;
		//	//PhysicsBlob* physBlob = obj->GetPhysicsBlob();
		//	//obj->SetWorldPos(Add(obj->GetWorldPos(), Mul(obj->GetPhysicsBlob()->GetGravity(), -1.f * updateRate)));
		//	//XMFLOAT3 oldWorldPos = obj->GetWorldPos();
		//	//XMFLOAT3 oldVelocity = physBlob->GetVelocity();
		//	//XMFLOAT3 vt = Mul(physBlob->GetVelocity(), -1.f * updateRate);
		//	//XMFLOAT3 att = Mul(Mul(physBlob->GetGravity(), -1.f * updateRate), -1.f * updateRate);
		//	//XMFLOAT3 newWorldPos = Add(oldWorldPos, Add(vt, Mul(att, 1.f / 2.f)));
		//	//XMFLOAT3 newVelocity = Add(oldVelocity, Mul(physBlob->GetGravity(), -1.f * updateRate));
		//	//obj->SetWorldPos(newWorldPos);
		//	//physBlob->SetVelocity(newVelocity);

		//	//physBlob->SetVelocity(XMFLOAT3(0,20,0));
		//	//obj->SetWorldPos(oldObjectList.at(CollidingList.at(i).xPos).worldPos);
		//	//obj->SetRotation(oldObjectList.at(CollidingList.at(i).xPos).rotation);
		//	//delete obj->GetPhysicsBlob();
		//	//obj->SetPhysicsBlob(oldObjectList.at(CollidingList.at(i).xPos).physicsBlob);// = oldObjectList.at(CollidingList.at(i).xPos).physicsBlob;
		//}
		//obj = (*objectList)[CollidingList.at(i).yPos];
		//if (obj->GetPhysicsBlob() != nullptr)
		//{
		//	obj = oldObjectList[CollidingList.at(i).yPos];
		//	//PhysicsBlob* physBlob = obj->GetPhysicsBlob();
		//	//obj->SetWorldPos(Add(obj->GetWorldPos(), Mul(obj->GetPhysicsBlob()->GetGravity(), -1.f * updateRate)));
		//	//XMFLOAT3 oldWorldPos = obj->GetWorldPos();
		//	//XMFLOAT3 oldVelocity = physBlob->GetVelocity();
		//	//XMFLOAT3 vt = Mul(physBlob->GetVelocity(), -1.f * updateRate);
		//	//XMFLOAT3 att = Mul(Mul(physBlob->GetGravity(), -1.f * updateRate), -1.f * updateRate);
		//	//XMFLOAT3 newWorldPos = Add(oldWorldPos, Add(vt, Mul(att, 1.f / 2.f)));
		//	//XMFLOAT3 newVelocity = Add(oldVelocity, Mul(physBlob->GetGravity(), -1.f * updateRate));
		//	//obj->SetWorldPos(newWorldPos);
		//	//physBlob->SetVelocity(newVelocity);

		//	//physBlob->SetVelocity(XMFLOAT3(0, 20, 0));
		//}
	}

	//Step 4: Calculate new speeds for objects in list 
	for (int i = 0; i < CollidingList.size(); i++)
	{
		Object* objX = (*objectList)[CollidingList.at(i).pos[0]];
		Object* objY = (*objectList)[CollidingList.at(i).pos[1]];
		if (objX->GetPhysicsBlob() != nullptr)
		{
			PhysicsBlob* physBlob = objX->GetPhysicsBlob();
			physBlob->SetVelocity(XMFLOAT3(0,20,0));
		}
		if (objY->GetPhysicsBlob() != nullptr)
		{
			PhysicsBlob* physBlob = objY->GetPhysicsBlob();
			physBlob->SetVelocity(XMFLOAT3(0, 20, 0));
		}
	}

	//TODO COMPUTESHADER
	//Step 1: Move all objects
	//Step 2: Collison detection and add to a intersection objects to a list
	//TODO: Step 3: Move all intersecting objects in list back one frame
	//TODO: Step 4: Calculate new speeds for objects in list 

	//oldObjectList.clear();
	//oldObjectList.shrink_to_fit();
}