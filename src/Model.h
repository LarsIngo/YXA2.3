#pragma once

#include "Mesh.h"
#include "Material.h"

class Model
{
private:
	Mesh* mMesh;
	Material* mMaterial;
public:
	Model(Mesh* mesh, Material* material);
	~Model();

	Mesh* GetMesh() { return mMesh; }
	Material* GetMaterial() { return mMaterial; }
};

Model::Model(Mesh* mesh, Material* material)
{
	mMesh = mesh;
	mMaterial = material;
}

Model::~Model()
{

}