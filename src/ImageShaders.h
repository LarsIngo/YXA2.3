#pragma once
#include <d3d11.h>
//#include <d3dcompiler.h>
#include <string>

#include "Shader.h"
#include "ComputeShader.h"

//#pragma comment(lib, "d3dcompiler.lib")

class Image;

using namespace std;

class ImageShaders
{
private:
	ID3D11Device** mDevice;
	ID3D11DeviceContext** mDeviceContext;

	//ID3D11ComputeShader* mCopy;
	Shader* mCopy;
	//ID3D11ComputeShader* mFXAA;
	//ID3D11ComputeShader* mMerge;
	//ID3D11ComputeShader* mGaussianBlur;
	Shader* mGaussianBlur;
	void CreateFilter();
	struct dataFilter
	{
		double filter[7][7];
		double pad;
	} sFilter;
	//dataFilter sFilter;

	//ID3D11Buffer* CreateConstBuffer(unsigned int byteWidth);

	//void CreateShader(string str, ID3D11ComputeShader** shader);
	//void ExecShader(ID3D11ComputeShader* shader, ID3D11ShaderResourceView* sourceSRV, ID3D11UnorderedAccessView* targetUAV);

public:
	ImageShaders(ID3D11Device** device, ID3D11DeviceContext** deviceContext);
	~ImageShaders();

	void Copy(ID3D11ShaderResourceView** sourceSRV, ID3D11UnorderedAccessView** targetUAV, XMINT2 resolution);
	//void FXAA(ID3D11ShaderResourceView* sourceSRV, ID3D11UnorderedAccessView* targetUAV);
	//void Merge(ID3D11ShaderResourceView* SRV0, ID3D11ShaderResourceView* SRV1, XMFLOAT2 offset1, ID3D11UnorderedAccessView* targetUAV);
	void GaussianBlur(ID3D11ShaderResourceView** sourceSRV, ID3D11UnorderedAccessView** targetUAV, XMINT2 resolution);

};

#include "Image.h"

ImageShaders::ImageShaders(ID3D11Device** device, ID3D11DeviceContext** deviceContext)
{
	mDevice = device;
	mDeviceContext = deviceContext;

	//CreateShader("Copy_CS.hlsl", &mCopy);
	mCopy = new ComputeShader(mDevice, mDeviceContext, NULL, NULL, NULL, "Copy_CS.hlsl");
	//CreateShader("FXAA_CS.hlsl", &mFXAA);
	//CreateShader("Merge_CS.hlsl", &mMerge);

	//TEST
	//CreateShader("GaussianBlur_CS.hlsl", &mGaussianBlur);
	//struct dataStruct { double filter[7][7]; } data;

	CreateFilter();
	mGaussianBlur = new ComputeShader(mDevice, mDeviceContext, sizeof(sFilter), NULL, NULL, "GaussianBlur_CS.hlsl");
}

ImageShaders::~ImageShaders()
{
	//mCopy->Release();
	delete mCopy;
	//mFXAA->Release();
	//mMerge->Release();
	//mGaussianBlur->Release();
	delete mGaussianBlur;
}

//void ImageShaders::CreateShader(string str, ID3D11ComputeShader** shader)
//{
//	ID3DBlob* errorBlob = nullptr;
//	ID3DBlob* pCS = nullptr;
//	wstring wStr = wstring(str.begin(), str.end());
//	HRESULT hr = D3DCompileFromFile(wStr.c_str(), nullptr, nullptr, "CS_main", "cs_5_0", 0, NULL, &pCS, &errorBlob);
//	if (FAILED(hr))
//	{
//		string errorMsg = (char*)errorBlob->GetBufferPointer();
//		OutputDebugStringA(errorMsg.c_str());
//	}
//
//	hr = (*mDevice)->CreateComputeShader(pCS->GetBufferPointer(), pCS->GetBufferSize(), nullptr, shader);
//	pCS->Release();
//}
//
//void ImageShaders::ExecShader(ID3D11ComputeShader* shader, ID3D11ShaderResourceView* sourceSRV, ID3D11UnorderedAccessView* targetUAV)
//{
//	(*mDeviceContext)->CSSetShader(shader, nullptr, NULL);
//	(*mDeviceContext)->CSSetUnorderedAccessViews(0, 1, &targetUAV, nullptr);
//	(*mDeviceContext)->CSSetShaderResources(0, 1, &sourceSRV);
//
//	(*mDeviceContext)->Dispatch(20, 20, 1);
//
//	(*mDeviceContext)->CSSetShader(nullptr, nullptr, NULL);
//	(*mDeviceContext)->CSSetUnorderedAccessViews(0, 0, nullptr, nullptr);
//	(*mDeviceContext)->CSSetShaderResources(0, 0, nullptr);
//}

void ImageShaders::Copy(ID3D11ShaderResourceView** sourceSRV, ID3D11UnorderedAccessView** targetUAV, XMINT2 resolution)
{
	//ExecShader(mCopy, sourceSRV, targetUAV);
	mCopy->Exec(sourceSRV, targetUAV, resolution);
}

//void ImageShaders::FXAA(ID3D11ShaderResourceView* sourceSRV, ID3D11UnorderedAccessView* targetUAV)
//{
//	ExecShader(mFXAA, sourceSRV, targetUAV);
//}

//void ImageShaders::Merge(ID3D11ShaderResourceView* SRV0, ID3D11ShaderResourceView* SRV1, XMFLOAT2 offset1, ID3D11UnorderedAccessView* targetUAV) 
//{
//
//	ID3D11ShaderResourceView* srvs[2] = { SRV0, SRV1 };
//
//	(*mDeviceContext)->CSSetShader(mMerge, nullptr, NULL);
//	(*mDeviceContext)->CSSetUnorderedAccessViews(0, 1, &targetUAV, nullptr);
//	(*mDeviceContext)->CSSetShaderResources(0, 2, srvs);
//
//	struct structDataCS
//	{
//
//		XMFLOAT4 pad;
//
//	};
//
//	ID3D11Buffer* constBuffer;
//	D3D11_BUFFER_DESC bufferDesc;
//	HRESULT hr;
//	structDataCS dataCS;
//
//	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
//	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
//	bufferDesc.ByteWidth = sizeof(structDataCS);
//	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	bufferDesc.CPUAccessFlags = 0;
//	bufferDesc.MiscFlags = 0;
//	bufferDesc.StructureByteStride = 0;
//	hr = (*mDevice)->CreateBuffer(&bufferDesc, nullptr, &constBuffer);
//
//	dataCS.pad = XMFLOAT4(offset1.x, offset1.y, 0, 1);
//	(*mDeviceContext)->UpdateSubresource(constBuffer, 0, nullptr, &dataCS, 0, 0);
//	(*mDeviceContext)->CSSetConstantBuffers(0, 1, &constBuffer);
//
//	(*mDeviceContext)->Dispatch(20, 20, 1);
//
//	(*mDeviceContext)->CSSetShader(nullptr, nullptr, NULL);
//	(*mDeviceContext)->CSSetUnorderedAccessViews(0, 0, nullptr, nullptr);
//	(*mDeviceContext)->CSSetShaderResources(0, 0, nullptr);
//	(*mDeviceContext)->CSGetConstantBuffers(0, 0, nullptr);
//}

void ImageShaders::GaussianBlur(ID3D11ShaderResourceView** sourceSRV, ID3D11UnorderedAccessView** targetUAV, XMINT2 resolution)
{
	//TODO so GB_Cs gets cbuffer
	//ExecShader(mGaussianBlur, sourceSRV, targetUAV);
	(*mDeviceContext)->UpdateSubresource(*mGaussianBlur->GetConstBuffer(), 0, nullptr, &sFilter, 0, 0);
	mGaussianBlur->Exec(sourceSRV, targetUAV, resolution);
}

void ImageShaders::CreateFilter()
{
	//GaussonFilter used in GaussinShader
	double sigma = 5.0, sum = 0.0;

	for (int x = -3; x <= 3; x++)
	{
		for (int y = -3; y <= 3; y++)
		{
			sFilter.filter[x + 3][y + 3] = 1.0 / (2.0 * 3.14 * sigma * sigma) * exp(-(x*x + y*y) / (2.0 * sigma * sigma));

			sum += sFilter.filter[x + 3][y + 3];
		}
	}

	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			sFilter.filter[x][y] /= sum;
		}
	}
}
