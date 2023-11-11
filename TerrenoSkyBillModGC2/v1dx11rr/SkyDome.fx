Texture2D textureDay : register(t0);
Texture2D textureAfternoon : register(t1);
Texture2D textureNight : register(t2);

SamplerState colorSampler : register(s0);

cbuffer MatrixBuffer : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projMatrix;
    float4 valores;
};

//CBUFFER PARA BLEND FACTOR
cbuffer BlendFactor : register(b0)
{
    float3 blendVector;
};

struct VS_Input
{
    float4 pos : POSITION;
    float2 tex0 : TEXCOORD0;
};

struct PS_Input
{
    float4 pos : SV_POSITION;
    float2 tex0 : TEXCOORD0;
};

PS_Input VS_Main(VS_Input vertex)
{
    PS_Input vsOut = (PS_Input) 0;
    vsOut.pos = mul(vertex.pos, worldMatrix);
    vsOut.pos = mul(vsOut.pos, viewMatrix);
    vsOut.pos = mul(vsOut.pos, projMatrix);

    vsOut.tex0 = vertex.tex0;

    return vsOut;
}

float4 PS_Main(PS_Input pix) : SV_TARGET
{
	// proceso de mezcla de texturas apartir del factor de blend
    float3 blendFactor = (float3) blendVector;
    //convierte textura a float4
    float4 texturaDia = textureDay.Sample(colorSampler, pix.tex0);
    float4 texturaTarde = textureAfternoon.Sample(colorSampler, pix.tex0);
    float4 texturaNoche = textureNight.Sample(colorSampler, pix.tex0);
	
    float4 finalColor = texturaDia * (blendFactor.x) + texturaTarde * (blendFactor.y) + texturaNoche * (blendFactor.z);
	
    return finalColor;
}