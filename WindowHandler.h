#pragma once
#include <d3d11.h>
#include <Windows.h>

#include "Image.h"
#include "ImageShaders.h"

using namespace DirectX;

class WindowHandler
{
private:

	HWND* mHWND;
	ID3D11Device** mDevice;
	ID3D11DeviceContext** mDeviceContext;
	IDXGISwapChain** mSwapChain;

	ImageShaders** mImageShaders;

	
	//The dimension of the window
	XMINT2 mResolution;
	ID3D11UnorderedAccessView* mBackBufferUAV;

	void InitialiseBackBuffer();
	
public:
	WindowHandler(HWND* hwnd, ID3D11Device** device, ID3D11DeviceContext** deviceContext, IDXGISwapChain** swapChain, ImageShaders** imageShaders, XMINT2 resolution);
	~WindowHandler();

	XMINT2 GetResolution() { return mResolution; }

	void Present(Image* image);
};

WindowHandler::WindowHandler(HWND* hwnd, ID3D11Device** device, ID3D11DeviceContext** deviceContext, IDXGISwapChain** swapChain, ImageShaders** imageShaders, XMINT2 resolution)
{
	mHWND = hwnd;
	mDevice = device;
	mDeviceContext = deviceContext;
	mSwapChain = swapChain;
	mImageShaders = imageShaders;
	mResolution = resolution;
	InitialiseBackBuffer();
}

WindowHandler::~WindowHandler()
{
	mBackBufferUAV->Release();
}

void WindowHandler::InitialiseBackBuffer()
{
	ID3D11Texture2D* backBuffer;
	(*mSwapChain)->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	(*mDevice)->CreateUnorderedAccessView(backBuffer, nullptr, &mBackBufferUAV);
	backBuffer->Release();
}

void WindowHandler::Present(Image* image)
{
	FLOAT bgColor[] = { 0.2f, 1.0f, 0.2f, 1.0f };		// Back buffer clear colour as an array of floats (rgba).
	(*mDeviceContext)->ClearUnorderedAccessViewFloat(mBackBufferUAV, bgColor);		// Clear the render target view using the specified colour.

	(*mImageShaders)->Copy(image->GetSRV(), &mBackBufferUAV, image->GetResolution());
	//image->Copy(mBackBufferUAV);

	// When everything has been drawn, present the final result on the screen by swapping the back and front buffers.
	(*mSwapChain)->Present(0, 0);
}