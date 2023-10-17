Texture2D colorMap : register(t0);
SamplerState colorSampler : register(s0);

cbuffer cbWorldMatrix : register(b0)
{
    matrix worldMatrix;
}

struct VS_input
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

struct PS_input
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

PS_input VS_Main(VS_input vertex)
{
    PS_input psOut;
    
    psOut.pos = mul(vertex.pos, worldMatrix);
    psOut.normal = mul(vertex.normal, worldMatrix);
    psOut.uv = vertex.uv;
    
    return psOut;
}

float4 PS_Main(PS_input pixel) : SV_TARGET
{
    float4 textura = colorMap.Sample(colorSampler, pixel.uv);
    clip(textura.a - 0.9f);
    return textura;
}