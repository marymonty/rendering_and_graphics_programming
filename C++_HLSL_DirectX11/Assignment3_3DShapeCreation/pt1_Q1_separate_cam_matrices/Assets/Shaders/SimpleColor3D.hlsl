//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

#pragma pack_matrix( row_major )

// MARY
// separate the constant buffers based on how often
// the data needs to be updated. have a constant buffer
// containing the camera data, and one containing particular
// instance data.

// CamData constant buffer is the 0th registered constant buffer in storage
// it contains the camera view matrix and camera projection matrix
// since these matrices do not change when rendering the separate cubes
cbuffer CamData : register (b0)
{
    float4x4 View;
    float4x4 Projection;
}

// InstanceData constant buffer is at the 1st (2nd) index of registered const buffers
// it contains the world matrix and the color of the cube
// since these params are both specific to each rendered object
cbuffer InstanceData : register( b1 )
{
	float4x4 World;
    float4 ColorInstance;
}

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION, float4 Color : COLOR )
{
    VS_OUTPUT output;
    output.Pos = mul( Pos, World);
    output.Pos = mul( output.Pos, View);
    output.Pos = mul( output.Pos, Projection);
    // MARY
    // making sure we are rendering the ColorInstance from the InstanceData
    // constant buffer, rather than just Color
    output.Color = ColorInstance;
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
    return input.Color;
}
