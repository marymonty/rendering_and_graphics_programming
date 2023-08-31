#include "ShaderTextureMultiLight.h"
#include <d3d11.h>
#include "d3dUtil.h"
#include <d3dcompiler.h>
#include <string>
#include <assert.h>

// MAKE SURE WE ARE CALLING THE CORRECT HLSL FILE IN THIS CONSTRUCTOR
ShaderTextureMultiLight::ShaderTextureMultiLight(ID3D11Device* dev)
	: ShaderBase(dev, L"../Assets/Shaders/TextureMultiLight.hlsl")
{
	// we need to update the input layout to include position, tex coords, and normals
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
 		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	HRESULT hr = S_OK;

	// View Projection buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CamMatrices);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferCamMatrices);
	assert(SUCCEEDED(hr));

	// light param
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_LightParams);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferLightParams);
	assert(SUCCEEDED(hr));

	// Color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_WorldAndMaterial);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWordAndMaterial);
	assert(SUCCEEDED(hr));

	// Zeroing the light data
	ZeroMemory(&DirLightData, sizeof(DirLightData));
	ZeroMemory(&PointLightData, sizeof(PointLightData));
	ZeroMemory(&SpotLightData, sizeof(SpotLightData));
}

ShaderTextureMultiLight::~ShaderTextureMultiLight()
{
	ReleaseAndDeleteCOMobject(mpBuffWordAndMaterial);
	ReleaseAndDeleteCOMobject(mpBufferLightParams);
	ReleaseAndDeleteCOMobject(mpBufferCamMatrices);
}


// SetTextureResourceAndSampler
// takes a Texture as a parameter
void ShaderTextureMultiLight::SetTextureResourceAndSampler(Texture* tex)
{
	tex->SetToContext(this->GetContext());
}



void ShaderTextureMultiLight::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	CamMatrices	mCamMatrices;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpBufferCamMatrices, 0, nullptr, &mCamMatrices, 0, 0);
}

void ShaderTextureMultiLight::SetDirectionalLightParameters(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	DirLightData.Light.Ambient = amb;
	DirLightData.Light.Diffuse = dif;
	DirLightData.Light.Specular = sp;
	DirLightData.Direction = dir;
}

// MARY
// adding an index param to the Set Point Light Params so we can set one light at a time
void ShaderTextureMultiLight::SetPointLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	PointLightData[index].Light.Ambient = amb;
	PointLightData[index].Light.Diffuse = dif;
	PointLightData[index].Light.Specular = sp;
	PointLightData[index].Position = pos;
	PointLightData[index].Attenuation = att;
	PointLightData[index].Range = r;
}

// MARY
// adding an index param to the Set Spot Light Params so we can set one light at a time
void ShaderTextureMultiLight::SetSpotLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	SpotLightData[index].Light.Ambient = amb;
	SpotLightData[index].Light.Diffuse = dif;
	SpotLightData[index].Light.Specular = sp;
	SpotLightData[index].Position = pos;
	SpotLightData[index].Direction = dir;
	SpotLightData[index].Attenuation = att;
	SpotLightData[index].Range = r;
	SpotLightData[index].SpotExp = spotExp;
}

void ShaderTextureMultiLight::SendLightParameters( const Vect& eyepos)
{
	Data_LightParams dl;
	dl.DirLight = DirLightData;
	// MARY
	// have to account for each of the array lights
	dl.PntLight[0] = PointLightData[0];
	dl.PntLight[1] = PointLightData[1];
	dl.PntLight[2] = PointLightData[2];
	dl.SptLight[0] = SpotLightData[0];
	dl.SptLight[1] = SpotLightData[1];
	dl.SptLight[2] = SpotLightData[2];
	dl.EyePosWorld = eyepos;

	this->GetContext()->UpdateSubresource(mpBufferLightParams, 0, nullptr, &dl, 0, 0);
}

void ShaderTextureMultiLight::SendWorldAndMaterial(const Matrix& world, const Vect& amb, const Vect& dif, const Vect& sp)
{
	Data_WorldAndMaterial wm;
	wm.World = world;
	wm.WorlInv = world.getInv();
	wm.Mat.Ambient = amb;
	wm.Mat.Diffuse = dif;
	wm.Mat.Specular = sp;

	this->GetContext()->UpdateSubresource(mpBuffWordAndMaterial, 0, nullptr, &wm, 0, 0);
}

void ShaderTextureMultiLight::SetToContext(ID3D11DeviceContext* devcon)
{
	ShaderBase::SetContext(devcon);
	ShaderBase::SetToContext_VS_PS_InputLayout();

	devcon->VSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->VSSetConstantBuffers(1, 1, &mpBufferLightParams);
	devcon->VSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);

	devcon->PSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->PSSetConstantBuffers(1, 1, &mpBufferLightParams);
	devcon->PSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);
}