#pragma once
#include "PointerList.h"
#include "Image.h"
#include "RenderEngine.h"
#include "Object.h"
#include "Camera.h"
#include "Model.h"

class Scene
{
private:
	RenderEngine** mRenderEngine;
	PointerList<Object> mObjectList = PointerList<Object>(1, 1);
	PointerList<Camera> mCameraList = PointerList<Camera>(1, 1);

protected:

public:
	Scene(RenderEngine** renderEngine);
	~Scene();

	Object* CreateObject(Model* model);
	Camera* CreateCamera(XMINT2 resolution);

	void RenderImage(Camera* camera, Image* image);
};

Scene::Scene(RenderEngine** renderEngine)
{
	mRenderEngine = renderEngine;
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