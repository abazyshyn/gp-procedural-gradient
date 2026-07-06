//////////////
// TYPEDEFS //
//////////////
struct PixelInput_s
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

float4 PGradientPixelShader(PixelInput_s input) : SV_TARGET
{
    return input.color;
}