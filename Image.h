#pragma once
#include <d3d11.h>

class ImageShaders;

class Image
{
private:
	ID3D11Device** mDevice;
	ID3D11DeviceContext** mDeviceContext;
	ImageShaders** mImageShaders;
	
	ID3D11RenderTargetView* mRTV;
	ID3D11ShaderResourceView* mSRV;
	ID3D11UnorderedAccessView* mUAV;
	ID3D11DepthStencilView* mDSV;
	//ID3D11ShaderResourceView* mDepthSRV;
	XMINT2 mResolution;
	float mClearColor[4] = { 0.4f, 0.4f, 0.4f, 1.0f };

	void CreateImage();
	void CreateDSV();

protected:

public:
	Image(ID3D11Device** device, ID3D11DeviceContext** deviceContext, ImageShaders** imageShaders, XMINT2 resolution);
	~Image();

	ID3D11RenderTargetView** GetRTV() { return &mRTV; }
	ID3D11ShaderResourceView** GetSRV() { return &mSRV; }
	ID3D11UnorderedAccessView** GetUAV() { return &mUAV; }
	ID3D11DepthStencilView** GetDSV() { return &mDSV; }
	XMINT2 GetResolution() { return mResolution; }
	void SetClearColor(float clearColor[4]) { for (int i = 0; i < 4; i++) { mClearColor[i] = clearColor[i]; } }

	void CopyTo(Image* trgImage);
	void GaussianBlurTo(Image* trgImage);
	//Image* FXAA();
	//Image* Merge();
	void Clear();
};

#include "ImageShaders.h"

Image::Image(ID3D11Device** device, ID3D11DeviceContext** deviceContext, ImageShaders** imageShaders, XMINT2 resolution)
{
	mDevice = device;
	mDeviceContext = deviceContext;
	mImageShaders = imageShaders;
	mResolution = resolution;

	CreateImage();
	CreateDSV();
}

Image::~Image()
{
	mRTV->Release();
	mSRV->Release();
	mUAV->Release();
	mDSV->Release();
	//mDepthSRV->Release();
}

void Image::CreateImage()
{
	//RTV Texture Desc
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = mResolution.x;
	textureDesc.Height = mResolution.y;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_SNORM; //TODO CHECK FORMAT
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS; //TODO CHECK FLAGS
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	//RTV Texture
	ID3D11Texture2D* texture = nullptr;
	(*mDevice)->CreateTexture2D(&textureDesc, NULL, &texture);
	(*mDevice)->CreateShaderResourceView(texture, NULL, &mSRV);
	(*mDevice)->CreateUnorderedAccessView(texture, NULL, &mUAV);
	(*mDevice)->CreateRenderTargetView(texture, NULL, &mRTV);
	texture->Release();
}

void Image::CreateDSV()
{
	//DSV Texture Desc
	D3D11_TEXTURE2D_DESC depthTexDesc;
	ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
	depthTexDesc.Width = mResolution.x;
	depthTexDesc.Height = mResolution.y;
	depthTexDesc.MipLevels = 1;
	depthTexDesc.ArraySize = 1;
	depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; //DXGI_FORMAT_R24G8_TYPELESS
	depthTexDesc.SampleDesc.Count = 1;
	depthTexDesc.SampleDesc.Quality = 0;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; //BIND SRV NOT VALID
	depthTexDesc.CPUAccessFlags = 0;
	depthTexDesc.MiscFlags = 0;

	//D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	//dsvd.Format = DXGI_FORMAT_UNKNOWN; //DXGI_FORMAT_UNKNOWN //https://msdn.microsoft.com/en-us/library/windows/desktop/ff476112%28v=vs.85%29.aspx, http://stackoverflow.com/questions/27522251/shadow-mapping-in-directx-sampler-depth-texture-always-return-0
	//dsvd.Flags = 0;
	//dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//dsvd.Texture2D.MipSlice = 0;

	//D3D11_SHADER_RESOURCE_VIEW_DESC srcd;
	//srcd.

	//DSV Texture
	ID3D11Texture2D* depthTexture;
	HRESULT hr = (*mDevice)->CreateTexture2D(&depthTexDesc, NULL, &depthTexture);
	hr = (*mDevice)->CreateDepthStencilView(depthTexture, NULL, &mDSV);
	//hr = (*mDevice)->CreateShaderResourceView(depthTexture, NULL, &mDepthSRV);
	depthTexture->Release();
}

void Image::CopyTo(Image* trgImage)
{
	(*mImageShaders)->Copy(&mSRV, trgImage->GetUAV(), trgImage->GetResolution());
}

void Image::GaussianBlurTo(Image* trgImage)
{
	(*mImageShaders)->GaussianBlur(&mSRV, trgImage->GetUAV(), trgImage->GetResolution());
}

//Image* Image::FXAA()
//{
//
//	Image* newImg = new Image(mDevice, mDeviceContext, mImageShaders, mResolution);
//
//	(*mImageShaders)->FXAA(mSRV, *newImg->GetUAV());
//
//	return newImg;
//
//}
//
//Image* Image::Merge()
//{
//
//	Image* newImg = new Image(mDevice, mDeviceContext, mImageShaders, mResolution);
//
//	(*mImageShaders)->Merge(mSRV, mSRV, XMFLOAT2(200,200),*newImg->GetUAV());
//
//	return newImg;
//
//}


void Image::Clear()
{
	(*mDeviceContext)->ClearRenderTargetView(mRTV, mClearColor);
	(*mDeviceContext)->ClearDepthStencilView(mDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
}