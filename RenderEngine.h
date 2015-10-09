#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>

#pragma comment(lib, "d3dcompiler.lib")

#include "Image.h"
#include "Camera.h"
#include "Object.h"

using namespace std;

class RenderEngine
{
private:
	ID3D11Device** mDevice;
	ID3D11DeviceContext** mDeviceContext;

	ID3D11VertexShader* mVertexShader;
	ID3D11GeometryShader* mGeometryShader;
	ID3D11PixelShader* mPixelShader;

	ID3D11InputLayout* mVertexLayout;

	ID3D11Buffer* mConstantBufferVS;
	struct structDataVS
	{
		XMMATRIX M;
		XMMATRIX MVP;
	};	

	ID3D11Buffer* mConstantBufferPS;
	struct structDataPS
	{
		XMFLOAT4 camPos;
		float depth;
		XMFLOAT3 pad;
	};

	void CreateShaders();
	void CreateConstantBuffers();

protected:

public:
	RenderEngine(ID3D11Device** mDevice, ID3D11DeviceContext** mDeviceContext);
	~RenderEngine();

	void Render(PointerList<Object>* objList, Camera* camera, Image* image);

};

RenderEngine::RenderEngine(ID3D11Device** device, ID3D11DeviceContext** deviceContext)
{
	mDevice = device;
	mDeviceContext = deviceContext;
	CreateShaders();
	CreateConstantBuffers();
}

RenderEngine::~RenderEngine()
{
	mVertexShader->Release();
	mGeometryShader->Release();
	mPixelShader->Release();
	mVertexLayout->Release();
	mConstantBufferVS->Release();
	mConstantBufferPS->Release();
}

void RenderEngine::Render(PointerList<Object>* objList, Camera* camera, Image* image)
{
	image->Clear();
	(*mDeviceContext)->OMSetRenderTargets(1, image->GetRTV(), *image->GetDSV());

	(*mDeviceContext)->VSSetShader(mVertexShader, nullptr, 0);
	(*mDeviceContext)->HSSetShader(nullptr, nullptr, 0);
	(*mDeviceContext)->DSSetShader(nullptr, nullptr, 0);
	(*mDeviceContext)->GSSetShader(mGeometryShader, nullptr, 0);
	(*mDeviceContext)->PSSetShader(mPixelShader, nullptr, 0);
	(*mDeviceContext)->CSSetShader(nullptr, nullptr, 0);

	(*mDeviceContext)->IASetInputLayout(mVertexLayout);
	(*mDeviceContext)->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//ConstantbuffersPS
	structDataPS dataPS;
	dataPS.camPos = camera->GetWorldPosF4();
	dataPS.depth = camera->GetFarZ()-camera->GetNearZ();
	(*mDeviceContext)->UpdateSubresource(mConstantBufferPS, 0, nullptr, &dataPS, 0, 0);
	(*mDeviceContext)->PSSetConstantBuffers(0, 1, &mConstantBufferPS);

	for (int i = 0; i < objList->Size(); i++)
	{
		ID3D11ShaderResourceView* diffuseSRV = *(*objList)[i]->GetModel()->GetMaterial()->GetDiffuse();
		ID3D11Buffer* vertexBuffer = *(*objList)[i]->GetModel()->GetMesh()->GetVertexBuffer();

		//ConstantbuffersVS
		structDataVS dataVS;
		XMMATRIX modelMat = (*objList)[i]->GetModelMat();
		XMMATRIX viewMat = camera->GetViewMat();
		XMMATRIX projMat = camera->GetProjMat();
		dataVS.M = XMMatrixTranspose(modelMat);
		dataVS.MVP = XMMatrixTranspose(modelMat * viewMat * projMat);
		(*mDeviceContext)->UpdateSubresource(mConstantBufferVS, 0, nullptr, &dataVS, 0, 0);
		(*mDeviceContext)->VSSetConstantBuffers(0, 1, &mConstantBufferVS);

		(*mDeviceContext)->PSSetShaderResources(0, 1, &diffuseSRV);

		UINT32 vertexSize = sizeof(Vertex);
		UINT32 offset = 0;
		(*mDeviceContext)->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexSize, &offset);

		(*mDeviceContext)->Draw((*objList)[i]->GetModel()->GetMesh()->GetNrOfVertices(), 0);
	}

	(*mDeviceContext)->OMSetRenderTargets(0, nullptr, nullptr);
	(*mDeviceContext)->VSSetShader(nullptr, nullptr, 0);
	(*mDeviceContext)->HSSetShader(nullptr, nullptr, 0);
	(*mDeviceContext)->DSSetShader(nullptr, nullptr, 0);
	(*mDeviceContext)->GSSetShader(nullptr, nullptr, 0);
	(*mDeviceContext)->PSSetShader(nullptr, nullptr, 0);
	(*mDeviceContext)->CSSetShader(nullptr, nullptr, 0);
	(*mDeviceContext)->PSSetShaderResources(0, 0, nullptr);
	(*mDeviceContext)->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
	(*mDeviceContext)->IASetInputLayout(nullptr);
	(*mDeviceContext)->VSSetConstantBuffers(0, 0, nullptr);
	(*mDeviceContext)->PSSetConstantBuffers(0, 0, nullptr);
}

void RenderEngine::CreateShaders()
{
	ID3DBlob* errorBlob = nullptr;
	ID3DBlob* pShader = nullptr;
	HRESULT hr = NULL;
	//VS
	hr = D3DCompileFromFile(L"Phong_VS.hlsl", nullptr, nullptr, "VS_main", "vs_5_0", 0, NULL, &pShader, &errorBlob);
	if (FAILED(hr))
	{
		string errorMsg = (char*)errorBlob->GetBufferPointer();
		OutputDebugStringA(errorMsg.c_str());
	}
	hr = (*mDevice)->CreateVertexShader(pShader->GetBufferPointer(), pShader->GetBufferSize(), nullptr, &mVertexShader);

	//Layout
	D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	hr = (*mDevice)->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), pShader->GetBufferPointer(), pShader->GetBufferSize(), &mVertexLayout);
	pShader->Release();

	//GS
	hr = D3DCompileFromFile(L"Phong_GS.hlsl", nullptr, nullptr, "GS_main", "gs_5_0", 0, NULL, &pShader, &errorBlob);
	if (FAILED(hr))
	{
		string errorMsg = (char*)errorBlob->GetBufferPointer();
		OutputDebugStringA(errorMsg.c_str());
	}
	hr = (*mDevice)->CreateGeometryShader(pShader->GetBufferPointer(), pShader->GetBufferSize(), nullptr, &mGeometryShader);
	pShader->Release();

	//PS
	hr = D3DCompileFromFile(L"Phong_PS.hlsl", nullptr, nullptr, "PS_main", "ps_5_0", 0, NULL, &pShader, &errorBlob);
	if (FAILED(hr))
	{
		string errorMsg = (char*)errorBlob->GetBufferPointer();
		OutputDebugStringA(errorMsg.c_str());
	}
	hr = (*mDevice)->CreatePixelShader(pShader->GetBufferPointer(), pShader->GetBufferSize(), nullptr, &mPixelShader);
	pShader->Release();
}

void RenderEngine::CreateConstantBuffers()
{
	D3D11_BUFFER_DESC bufferDesc;
	HRESULT hr;
	//VS
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(structDataVS);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	hr = (*mDevice)->CreateBuffer(&bufferDesc, nullptr, &mConstantBufferVS);

	//PS
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(structDataPS);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	hr = (*mDevice)->CreateBuffer(&bufferDesc, nullptr, &mConstantBufferPS);
}