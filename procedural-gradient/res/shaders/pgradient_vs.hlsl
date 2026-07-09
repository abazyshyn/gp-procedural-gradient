/////////////
// GLOBALS //
/////////////
cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

//////////////
// TYPEDEFS //
//////////////
struct VertexInput_s
{
    float3 position : POSITION;
};

struct PixelInput_s
{
    float4 position : SV_POSITION;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader                                                              //
////////////////////////////////////////////////////////////////////////////////
PixelInput_s PGradientVertexShader(VertexInput_s input)
{
    PixelInput_s output;
    
    float4 position = float4(input.position, 1.0f);
    output.position = mul(position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    return output;
}