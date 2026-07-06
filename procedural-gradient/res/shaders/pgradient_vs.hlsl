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
    float4 position : POSITION;
    float4 color : COLOR;
};

struct PixelInput_s
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader                                                              //
////////////////////////////////////////////////////////////////////////////////
PixelInput_s PGradientVertexShader(VertexInput_s input)
{
    PixelInput_s output;
    
    input.position.w = 1.0f;
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    output.color = input.color;
    
    return output;
}