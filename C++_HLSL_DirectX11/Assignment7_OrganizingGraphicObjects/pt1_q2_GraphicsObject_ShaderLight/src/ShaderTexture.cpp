#include "ShaderTexture.h"

#include <d3d11.h>
#include "d3dUtil.h"
#include <d3dcompiler.h>
#include <string>
#include <assert.h>

// ShaderTexture constructor
// set the shader to be the Texture.hlsl file
// then initialize the input layout and constant buffers
ShaderTexture::ShaderTexture(ID3D11Device* device)
	: ShaderBase(device, L"../Assets/Shaders/Texture.hlsl")
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	HRESULT hr;

	// View Projection buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CamMatrices);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpCamBuff);
	assert(SUCCEEDED(hr));

	// World Matrix buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WorldData);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpWorldBuff);
	assert(SUCCEEDED(hr));

}

// Destructor
// releases and deletes all our COM objects
ShaderTexture::~ShaderTexture()
{
	ReleaseAndDeleteCOMobject(mpCamBuff);
	ReleaseAndDeleteCOMobject(mpWorldBuff);

}

// SetToContext
// call the shaderBase class functions to set the VS,
// PS and input layout, then set the shader texture constant buffers
void ShaderTexture::SetToContext(ID3D11DeviceContext* devcon)
{
	ShaderBase::SetContext(devcon);
	ShaderBase::SetToContext_VS_PS_InputLayout();

	devcon->VSSetConstantBuffers(0, 1, &mpCamBuff);
	devcon->VSSetConstantBuffers(1, 1, &mpWorldBuff);
}

// SetTextureResourceAndSampler
// takes a Texture as a parameter
void ShaderTexture::SetTextureResourceAndSampler(Texture* tex)
{
	tex->SetToContext(this->GetContext());
}

// SendCamMatrices
// takes a View and Projection matrix as parameters
// creates a CamMatrices constant buffer to fill with our params
// then updates the mpCamBuff handler with our new constant buffer
void ShaderTexture::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	CamMatrices	mCamMatrices;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpCamBuff, 0, nullptr, &mCamMatrices, 0, 0);
}

// SendWorld
// takes a World Matrix parameter
// creates a WorldData constant buffer, sets the World matrix 
// in the constant buffer to be the World matrix passed in the param
// then Updates the handler (mpWorldBuff) SubResource with this new world matrix
void ShaderTexture::SendWorld(const Matrix& world)
{
	WorldData wd;
	wd.World = world;

	this->GetContext()->UpdateSubresource(mpWorldBuff, 0, nullptr, &wd, 0, 0);
}

