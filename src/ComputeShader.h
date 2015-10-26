#pragma once
#include "Shader.h"

class ComputeShader : public Shader
{
private:
	ID3D11ComputeShader* mShader;

	void CreateShader(string hlsl);
protected:

public:
	ComputeShader(ID3D11Device** device, ID3D11DeviceContext** deviceContext, unsigned int constBufferByteWidth, unsigned int structBufferNrOfElements, unsigned int structBufferByteWidth, string hlsl);
	~ComputeShader();

	void Exec(ID3D11ShaderResourceView** sourceSRV, ID3D11UnorderedAccessView** targetUAV, XMINT2 resolution);
};

ComputeShader::ComputeShader(ID3D11Device** device, ID3D11DeviceContext** deviceContext, unsigned int constBufferByteWidth, unsigned int structBufferNrOfElements, unsigned int structBufferByteWidth, string hlsl) : Shader(device, deviceContext, constBufferByteWidth, structBufferNrOfElements, structBufferByteWidth)
{
	CreateShader(hlsl);
}

ComputeShader::~ComputeShader()
{
	mShader->Release();
}

void ComputeShader::Exec(ID3D11ShaderResourceView** sourceSRV, ID3D11UnorderedAccessView** targetUAV, XMINT2 resolution)
{
	(*mDeviceContext)->CSSetShader(mShader, nullptr, NULL);
	(*mDeviceContext)->CSSetUnorderedAccessViews(0, 1, targetUAV, nullptr);
	(*mDeviceContext)->CSSetShaderResources(0, 1, sourceSRV);

	if (mConstBuffer != nullptr)
	{
		(*mDeviceContext)->CSSetConstantBuffers(0, 1, &mConstBuffer);
	}
	if (mStructBuffer != nullptr)
	{
		//(*mDeviceContext)->CSSetUnorderedAccessViews(1, 2, &mStructBuffer, nullptr);
	}

	(*mDeviceContext)->Dispatch(resolution.x/32, resolution.y/24, 1);

	(*mDeviceContext)->CSSetConstantBuffers(0, 0, nullptr);
	(*mDeviceContext)->CSSetShader(nullptr, nullptr, NULL);
	(*mDeviceContext)->CSSetUnorderedAccessViews(0, 0, nullptr, nullptr);
	(*mDeviceContext)->CSSetShaderResources(0, 0, nullptr);
}

void ComputeShader::CreateShader(string hlsl)
{
	ID3DBlob* errorBlob = nullptr;
	ID3DBlob* shaderBlob = nullptr;
	wstring wStr = wstring(hlsl.begin(), hlsl.end());
	HRESULT hr = D3DCompileFromFile(wStr.c_str(), nullptr, nullptr, "CS_main", "cs_5_0", 0, NULL, &shaderBlob, &errorBlob);
	if (FAILED(hr))
	{
		string errorMsg = (char*)errorBlob->GetBufferPointer();
		OutputDebugStringA(errorMsg.c_str());
	}
	hr = (*mDevice)->CreateComputeShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &mShader);
	shaderBlob->Release();
}