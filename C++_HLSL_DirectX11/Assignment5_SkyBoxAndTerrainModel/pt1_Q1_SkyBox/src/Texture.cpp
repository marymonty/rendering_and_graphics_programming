#include "Texture.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>

Texture::~Texture()
{
	ReleaseAndDeleteCOMobject(mpTextureRV);
	ReleaseAndDeleteCOMobject(mpSampler);
}

Texture::Texture(ID3D11Device* d3dDev, LPCWSTR filepath, D3D11_FILTER filter)
{
	DirectX::ScratchImage testTexture;
	HRESULT hr = LoadFromTGAFile(filepath, nullptr, testTexture);
	assert(SUCCEEDED(hr));

	CreateShaderResourceView(d3dDev, testTexture.GetImage(0, 0, 0), testTexture.GetImageCount(), testTexture.GetMetadata(), &mpTextureRV);

	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = filter;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = d3dDev->CreateSamplerState(&sampDesc, &mpSampler);
	assert(SUCCEEDED(hr));
}

void Texture::SetToContext(ID3D11DeviceContext* devcon, int texResSlot,  int sampSlot)
{
	devcon->PSSetShaderResources(texResSlot, 1, &mpTextureRV);
	devcon->PSSetSamplers(sampSlot, 1, &mpSampler);
}