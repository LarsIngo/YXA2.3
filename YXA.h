#pragma once
#include <d3d11.h>
#include <Windows.h>

#include "PointerList.h"
#include "DPointerList.h"

#include "Vertex.h"
#include "YXAMath.h"

#include "DDSTextureLoader.h"

#include "WindowHandler.h"
#include "RenderEngine.h"
#include "ImageShaders.h"
#include "PhysicsEngine.h"

#include "Model.h"
#include "Scene.h"

#pragma comment(lib, "d3d11.lib")


using namespace DirectX;

class YXA
{
private:
	//We store these here so they are easy to access.
	HWND mHWND;
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mDeviceContext;
	IDXGISwapChain* mSwapChain;

	//The main modules
	WindowHandler* mWindowHandler; //Handles the windows
	RenderEngine* mRenderEngine; //Draws our images
	ImageShaders* mImageShaders;
	PhysicsEngine* mPhysicsEngine;

	//A list that contains all our scenes.
	PointerList<Image> mImageList = PointerList<Image>(1, 1);
	PointerList<Scene> mSceneList = PointerList<Scene>(1, 1);
	PointerList<Model> mModelList = PointerList<Model>(1, 1);
	DPointerList<Mesh> mMeshList = DPointerList<Mesh>(1, 1);
	DPointerList<Material> mMaterialList = DPointerList<Material>(1, 1);

	Material* CreateMaterial(string material);
	Mesh* CreateMesh(string mesh);

	static LRESULT CALLBACK WindowProcedure(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	void CreateHWND(XMINT2 resolution);
	void InitialiseWindow(XMINT2 resolution);
	void CreateDeviceAndSwapChain(XMINT2 resolution);
	void CreateViewport(XMINT2 resolution);
	void InitialiseRenderEngine();
	void InitialiseImageShaders();
	void InitialisePhysicsEngine();

protected:

public:
	YXA(XMINT2 resolution);
	~YXA();

	Image* CreateImage(XMINT2 resolution);
	Scene* CreateScene();
	Model* CreateModel(string mesh, string material);

	//void GaussianBlur(Image* srcImage, Image* trgImage);
	void Present(Image* image);

	bool Running();
};

YXA::YXA(XMINT2 resolution)
{	
	CreateHWND(resolution);
	CreateDeviceAndSwapChain(resolution);
	CreateViewport(resolution);
	InitialiseWindow(resolution);
	InitialiseRenderEngine();
	InitialiseImageShaders();
	InitialisePhysicsEngine();
}

YXA::~YXA()
{
	delete mWindowHandler;
	delete mRenderEngine;
	delete mImageShaders;
	delete mPhysicsEngine;
	mDevice->Release();
	mDeviceContext->Release();
	mSwapChain->Release();
}


//PRIVATE FUNCTIONS

Material* YXA::CreateMaterial(string material)
{
	int pos = mMaterialList[material];
	if (pos == -1)
	{
		ID3D11ShaderResourceView* SRV = nullptr;
		wstring wStr = wstring(material.begin(), material.end());
		if (FAILED(CreateDDSTextureFromFile(mDevice, wStr.c_str(), nullptr, &SRV)))
		{
			material = "Default";
			CreateDDSTextureFromFile(mDevice, L"Default_Diffuse.dds", nullptr, &SRV);
		}
		return mMaterialList.Add(material, new Material(SRV));
	}
	return mMaterialList[pos];
}


Mesh* YXA::CreateMesh(string mesh)
{
	int pos = mMeshList[mesh];
	if (pos == -1)
	{
		return mMeshList.Add(mesh, new Mesh(&mDevice, mesh));
	}
	return mMeshList[pos];
}

LRESULT CALLBACK YXA::WindowProcedure(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	// If a message has not been handled, send it to the default window procedure for handling.
	return DefWindowProc(handle, message, wParam, lParam);
}

void YXA::CreateHWND(XMINT2 resolution)
{
	// Register the window class to create.
	HINSTANCE applicationHandle = GetModuleHandle(NULL);
	WNDCLASS windowClass;
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProcedure;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = applicationHandle;
	windowClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(0, IDC_ARROW);
	windowClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = L"WindowClass";

	RegisterClass(&windowClass);

	mHWND = CreateWindow(
		L"WindowClass",
		L"Window Title",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		resolution.x,
		resolution.y,
		NULL,
		NULL,
		applicationHandle,
		NULL
		);

	ShowWindow(mHWND, SW_SHOWDEFAULT);
	UpdateWindow(mHWND);
}

void YXA::CreateDeviceAndSwapChain(XMINT2 resolution)
{
	//We initiate the device, device context and swap chain.
	DXGI_SWAP_CHAIN_DESC scDesc;
	scDesc.BufferDesc.Width = resolution.x; 		// Using the window's size avoids weird effects. If 0 the window's client width is used.
	scDesc.BufferDesc.Height = resolution.y;		// Using the window's size avoids weird effects. If 0 the window's client height is used.
	scDesc.BufferDesc.RefreshRate.Numerator = 0;	// Screen refresh rate as RationalNumber. Zeroing it out makes DXGI calculate it.
	scDesc.BufferDesc.RefreshRate.Denominator = 0;	// Screen refresh rate as RationalNumber. Zeroing it out makes DXGI calculate it.
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;						// The most common format. Variations include [...]UNORM_SRGB.
	scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	// The order pixel rows are drawn to the back buffer doesn't matter.
	scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;					// Since the back buffer and window sizes matches, scaling doesn't matter.
	scDesc.SampleDesc.Count = 1;												// Disable multisampling.
	scDesc.SampleDesc.Quality = 0;												// Disable multisampling.
	scDesc.BufferUsage = DXGI_USAGE_UNORDERED_ACCESS;						// The back buffer will be rendered to.
	scDesc.BufferCount = 1;							// We only have one back buffer.
	scDesc.OutputWindow = mHWND;			// Must point to the handle for the window used for rendering.
	scDesc.Windowed = true;							// Run in windowed mode. Fullscreen is covered in a later sample.
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;	// This makes the display driver select the most efficient technique.
	scDesc.Flags = 0;								// No additional options.

	D3D11CreateDeviceAndSwapChain(
		nullptr,					// Use the default adapter.
		D3D_DRIVER_TYPE_HARDWARE,	// Use the graphics card for rendering. Other options include software emulation.
		NULL,						// NULL since we don't use software emulation.
		NULL,						// No creation flags.
		nullptr,					// Array of feature levels to try using. With null the following are used 11.0, 10.1, 10.0, 9.3, 9.2, 9.1.
		0,							// The array above has 0 elements.
		D3D11_SDK_VERSION,			// Always use this.
		&scDesc,					// Description of the swap chain.
		&mSwapChain,				// [out] The created swap chain.
		&mDevice,					// [out] The created device.
		nullptr,					// [out] The highest supported feature level (from array).
		&mDeviceContext					// [out] The created device context.
		);
}

void YXA::CreateViewport(XMINT2 resolution)
{
	D3D11_VIEWPORT vp;
	vp.Width = (float)resolution.x;
	vp.Height = (float)resolution.y;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	mDeviceContext->RSSetViewports(1, &vp);
}

void YXA::InitialiseWindow(XMINT2 resolution)
{
	mWindowHandler = new WindowHandler(&mHWND, &mDevice, &mDeviceContext, &mSwapChain, &mImageShaders, resolution);
}

void YXA::InitialiseRenderEngine()
{
	 mRenderEngine = new RenderEngine(&mDevice, &mDeviceContext);
}

void YXA::InitialiseImageShaders()
{
	mImageShaders = new ImageShaders(&mDevice, &mDeviceContext);
}

void YXA::InitialisePhysicsEngine()
{
	mPhysicsEngine = new PhysicsEngine();
}

//PUBLIC FUNCTIONS

Image* YXA::CreateImage(XMINT2 resolution)
{
	return mImageList.Add(new Image(&mDevice, &mDeviceContext, &mImageShaders, resolution));
}

Scene* YXA::CreateScene()
{
	return mSceneList.Add(new Scene(&mRenderEngine));
}

Model* YXA::CreateModel(string mesh, string material)
{
	return mModelList.Add(new Model(CreateMesh(mesh), CreateMaterial(material)));
}

//void YXA::GaussianBlur(Image* srcImage, Image* trgImage)
//{
//	mImageShaders->GaussianBlur(srcImage->GetSRV(), trgImage->GetUAV(), trgImage->GetResolution());
//}

void YXA::Present(Image* image)
{
	mWindowHandler->Present(image);
}

bool YXA::Running()
{
	MSG windowMsg = { 0 };

	while (windowMsg.message != WM_QUIT)
	{
		if (PeekMessage(&windowMsg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&windowMsg);
			DispatchMessage(&windowMsg);
		}
		else
		{
			// If there are no more messages to handle, run a frame 
			// Usually Update() + Render() but in this sample only the latter is needed.
			return true;
		}
	}
	return false;
}