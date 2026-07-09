//////////////
// TYPEDEFS //
//////////////
struct PixelInput_s
{
    float4 position : SV_POSITION;
};

float4 PGradientPixelShader(PixelInput_s input) : SV_TARGET
{   
    float2 screenPosition = input.position.xy;
    float2 resolution = float2(800.0f, 600.0f);
    float2 uv = screenPosition / resolution;
    
    return float4(uv.x, uv.y, 1.0f - uv.x, 1.0f);
}