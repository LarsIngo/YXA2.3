#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>

#pragma comment(lib, "d3dcompiler.lib")

using namespace std;
using namespace DirectX;

class Shader
{
private:

protected:
	ID3D11Device** mDevice;
	ID3D11DeviceContext** mDeviceContext;

	ID3D11Buffer* mConstBuffer;
	ID3D11UnorderedAccessView* mStructBuffer;

	void CreateConstBuffer(unsigned int byteWidth);
	void CreateStructBuffer(unsigned int nrOfElements, unsigned int byteWidth);
public:
	Shader(ID3D11Device** device, ID3D11DeviceContext** deviceContext, unsigned int constBufferByteWidth, unsigned int structBufferNrOfElements, unsigned int structBufferByteWidth);
	virtual ~Shader();

	ID3D11Buffer** GetConstBuffer() { return &mConstBuffer; }
	ID3D11UnorderedAccessView** GetStructBuffer() { return &mStructBuffer; }

	virtual void Exec(ID3D11ShaderResourceView** sourceSRV, ID3D11UnorderedAccessView** targetUAV, XMINT2 resolution) = 0;
};

Shader::Shader(ID3D11Device** device, ID3D11DeviceContext** deviceContext, unsigned int constBufferByteWidth, unsigned int structBufferNrOfElements, unsigned int structBufferByteWidth)
{
	mDevice = device;
	mDeviceContext = deviceContext;
	CreateConstBuffer(constBufferByteWidth);
	CreateStructBuffer(structBufferNrOfElements, structBufferByteWidth);
}

Shader::~Shader()
{
	if (mConstBuffer != nullptr)
	{
		mConstBuffer->Release();
	}
	if (mStructBuffer != nullptr)
	{
		mStructBuffer->Release();
	}
}

void Shader::CreateConstBuffer(unsigned int byteWidth)
{
	if (byteWidth != 0)
	{
		unsigned int padBytes = 0;
		if(byteWidth % 16 != 0)
		{
			padBytes = 16 - byteWidth % 16;
		}
		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = byteWidth + padBytes;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		HRESULT hr = (*mDevice)->CreateBuffer(&bufferDesc, nullptr, &mConstBuffer);
	}
	else
	{
		mConstBuffer = nullptr;
	}
}

void Shader::CreateStructBuffer(unsigned int nrOfElements, unsigned int byteStride)
{
	unsigned int byteWidth = nrOfElements * byteStride;
	if (nrOfElements != 0 && byteWidth != 0)
	{
		int padBytes = 0;
		if (byteWidth % 16 != 0)
		{
			padBytes = 16 - byteWidth % 16;
		}
		//STRUCURED BUFFERS
		ID3D11Buffer* buffer;
		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		bufferDesc.ByteWidth = byteWidth + padBytes;
		bufferDesc.StructureByteStride = byteWidth / nrOfElements;
		HRESULT hr = (*mDevice)->CreateBuffer(&bufferDesc, NULL, &buffer);

		D3D11_UNORDERED_ACCESS_VIEW_DESC descUAV;
		descUAV.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		descUAV.Format = DXGI_FORMAT_UNKNOWN;
		descUAV.Buffer.FirstElement = 0;
		descUAV.Buffer.Flags = 0;
		descUAV.Buffer.NumElements = nrOfElements;

		hr = (*mDevice)->CreateUnorderedAccessView(buffer, &descUAV, &mStructBuffer);
		//buffer->Release();
	}
	else
	{
		mStructBuffer = nullptr;
	}
}