//--------------------------------------------------------------------------------------
// SimpleColorPlus
//--------------------------------------------------------------------------------------

// MARY 
// We need to update this whole file

// We update the VertexData and PixelData structs to match our input layout
// defined in D3D11_INPUT_ELEMENT_DESC layout[]
// meaning, we need a float4 position with semantics matching that of the first param in layout[] "POSITION"
// and a int ColorNum with semantics matching first layout[] param "COLORNUM"
struct VertexData
{
	float4 Pos : POSITION;
	int ColorNum : COLORNUM;
};

struct PixelData
{
	float4 Pos : SV_POSITION;
	int ColorNum : COLORNUM;
};


// We need to set up the shader constants for the constant buffer
//--------------------------------------------------------------------------------------
// Constant Buffer Shader Constants
//--------------------------------------------------------------------------------------
// we should register new buffers, this b0 indicates it is the 0th constant buffer
cbuffer bufColor : register(b0)
{
	// float4 is shorthand for a Vect of four floats
	// this needs to match our CBColor struct
	float4 ActiveCol[2];
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
// I did not change the vertex shader since I am changing the color through the Pixel Shader
PixelData VS(VertexData inVert)
{
	return inVert;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
// we now have two inputs for a Pixel Shader - the position AND the ColorNum int
float4 PS(float4 pix : SV_POSITION, int ColorNum : COLORNUM) : SV_Target
{
	// we return the correct Color using the ColorNum param and the Color array (ActiveCol)
	return ActiveCol[ColorNum];
}
