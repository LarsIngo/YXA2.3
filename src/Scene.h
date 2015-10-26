#pragma once
#include "PointerList.h"
#include "Image.h"
#include "RenderEngine.h"
#include "PhysicsEngine.h"
#include "Object.h"
#include "Camera.h"
#include "Model.h"

class Scene
{
private:
	RenderEngine** mRenderEngine;
	PhysicsEngine** mPhysicsEngine;
	PointerList<Object> mObjectList = PointerList<Object>(1, 1);
	PointerList<Camera> mCameraList = PointerList<Camera>(1, 1);

protected:

public:
	Scene(RenderEngine** renderEngine, PhysicsEngine** physicsEngine);
	~Scene();

	Object* CreateObject(Model* model);
	Camera* CreateCamera(XMINT2 resolution);

	void RenderImage(Camera* camera, Image* image);
	void UpdatePhysics(float updateRate);
};

Scene::Scene(RenderEngine** renderEngine, PhysicsEngine** physicsEngine)
{
	mRenderEngine = renderEngine;
	mPhysicsEngine = physicsEngine;
}

Scene::~Scene()
{

}

Object* Scene::CreateObject(Model* model)
{
	return mObjectList.Add(new Object(model));
}

Camera* Scene::CreateCamera(XMINT2 resolution)
{
	return mCameraList.Add(new Camera(resolution));
}

void Scene::RenderImage(Camera* camera, Image* image)
{
	(*mRenderEngine)->Render(&mObjectList, camera, image);
}

void Scene::UpdatePhysics(float updateRate)
{
	(*mPhysicsEngine)->Update(updateRate, &mObjectList);
}