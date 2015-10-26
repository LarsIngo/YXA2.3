#pragma once
#include <d3d11.h>

class Material
{
private:

protected:
	ID3D11ShaderResourceView* mDiffuseSRV;

public:
	Material(ID3D11ShaderResourceView* mDiffuseSRV);
	~Material();

	ID3D11ShaderResourceView** GetDiffuse() { return &mDiffuseSRV; }
};

Material::Material(ID3D11ShaderResourceView* diffuseSRV)
{
	mDiffuseSRV = diffuseSRV;
}

Material::~Material()
{
	mDiffuseSRV->Release();
}