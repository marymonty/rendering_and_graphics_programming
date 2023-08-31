// MARY
// ColorSelected3DOptimized 
// implements the declarations in the header file of the same name

#include "ColorSelected3DOptimized.h"
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>

// Constructor
// creates the input layout and constant buffer
ColorSelected3DOptimized::ColorSelected3DOptimized(ID3D11Device* device)
	: ShaderBase(device, L"../Assets/Shaders/ColorSelected3DOptimized.hlsl")
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);  
	this->CreateInputLayout(layout, numElements);

	HRESULT hr;  

	// W*V*P matrix and Color buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_WVPColor);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWVPColor);
	assert(SUCCEEDED(hr));

}

// Destructor
// cleans up our COM objects
ColorSelected3DOptimized::~ColorSelected3DOptimized()
{
	ReleaseAndDeleteCOMobject(mpBuffWVPColor);
}

// SendWVPColor
// calls UpdateSubresource using the function parameters
// @params:
//		wvp : the matrix that is the World * View * Projection matrix
//		col : the Color vect selected
void ColorSelected3DOptimized::SendWVPColor(const Matrix& wvp, const Vect& col)
{
	Data_WVPColor wc;
	wc.WVP = wvp;
	wc.Color = col;

	this->GetContext()->UpdateSubresource(mpBuffWVPColor, 0, nullptr, &wc, 0, 0);
}

// SetToContext
// set this shader to context by calling the base class SetToContext and 
// SetToContext_VS_PS_InputLayout functions, then also setting the 
// Vertex Shader constant buffer with our ColorSelected3DOptimized constant buffer
// for the WVP and Color
void ColorSelected3DOptimized::SetToContext(ID3D11DeviceContext* devcon)
{
	ShaderBase::SetContext(devcon);
	ShaderBase::SetToContext_VS_PS_InputLayout();

	devcon->VSSetConstantBuffers(0, 1, &mpBuffWVPColor);
}


