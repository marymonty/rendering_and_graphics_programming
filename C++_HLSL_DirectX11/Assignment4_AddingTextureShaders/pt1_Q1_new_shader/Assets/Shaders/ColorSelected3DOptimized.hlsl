#pragma pack_matrix( row_major )
// MARY
// We are removing the CamData buffer, which held the View and Projection
// matrices. We are keeping the InstanceData buffer which will now hold
// the World*View*Projection matrix as well as the selected Color
cbuffer InstanceData : register(b0)
{
	float4x4 WVP;
	float4 SelectedColor;
};

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION )
{
    VS_OUTPUT output;
    // MARY
    // Now the output position is just pos * our WVP matrix
    output.Pos = mul(Pos, WVP);
    output.Color = SelectedColor;
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
    return input.Color;
}
