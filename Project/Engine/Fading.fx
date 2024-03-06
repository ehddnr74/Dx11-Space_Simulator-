#ifndef _FADING
#define _FADING

#include "value.fx"
#include "func.fx"

struct VS_IN
{
    float3 vLocalPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};


VS_OUT VS_Fading(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = float4(_in.vLocalPos * 2.f, 1.f);
    output.vUV = _in.vUV;
        
    return output;
}

// 레스터라이저 스테이트

#define ratio g_float_3;

float4 PS_Fading(VS_OUT _in) : SV_Target
{
    float2 vScreenUV = _in.vPosition.xy / g_Resolution;
    
    float4 vColor = g_tex_0.Sample(g_sam_0, vScreenUV);
    
    float a = ratio;
    
    vColor = float4(0.f, 0.f, 0.f, a);
    
    return vColor;
}
#endif