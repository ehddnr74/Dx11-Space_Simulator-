#ifndef _DEBUGSHAPE
#define _DEBUGSHAPE

#include "value.fx"

// =================
// DebugShape Shader
// Topology : LineStrip
// RS_TYPE  : CULL_NONE
// DS_TYPE  : NO_TEST_NO_WRITE
// BS_TYPE  : Default

// Parameter
// g_vec4_0 : OutColor
// ==================
struct VS_DEBUG_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
    float3 vNormal : NORMAL;
};

struct VS_DEBUG_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    float3 vViewPos : POSITION;
    float3 vViewNormal : NORMAL;
};

VS_DEBUG_OUT VS_DebugShape(VS_DEBUG_IN _in)
{
    VS_DEBUG_OUT output = (VS_DEBUG_OUT) 0.f;    
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
    output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV));
    
    
    
    
    return output;    
}

float4 PS_DebugShape(VS_DEBUG_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    vOutColor = g_vec4_0;
    
    return vOutColor;
}


float4 PS_DebugShape_Sphere(VS_DEBUG_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
        
    float3 vEye = -normalize(_in.vViewPos);        
    float fOutLine = 1.f - saturate(abs(dot(vEye, _in.vViewNormal)));        
    fOutLine = pow(fOutLine, 2.5);
    
    vOutColor = g_vec4_0;
    vOutColor.a = fOutLine;    
    
    return vOutColor;
}

// 보호막 셰이더 
float4 PS_Sphere_Shiled(VS_DEBUG_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
        
    float3 vEye = -normalize(_in.vViewPos);
    float fOutLine = 1.f - saturate(abs(dot(vEye, _in.vViewNormal)));
    fOutLine = pow(fOutLine, 0.5);
    
    
   // vOutColor = g_vec4_0;
   // vOutColor = float4(1.f, 0.f, 1.f, fOutLine);
    //vOutColor.a = fOutLine;
    
    if (g_btex_0)
    {
        vOutColor = g_tex_0.Sample(g_sam_0, _in.vUV);
        vOutColor.a = fOutLine;
    }
    
    return vOutColor;
}


float4 PS_Boss_Shiled(VS_DEBUG_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
        
    float3 vEye = -normalize(_in.vViewPos);
    float fOutLine = 1.f - saturate(abs(dot(vEye, _in.vViewNormal)));
    fOutLine = pow(fOutLine, 0.3);
    
    
   // vOutColor = g_vec4_0;
   // vOutColor = float4(1.f, 0.f, 1.f, fOutLine);
    //vOutColor.a = fOutLine;
    
    if (g_btex_0)
    {
        vOutColor = g_tex_0.Sample(g_sam_0, _in.vUV);
        vOutColor.a = fOutLine;
    }
    
    return vOutColor;
}

float4 PS_Lerp_Shiled(VS_DEBUG_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    float4 vOutColor1 = (float4) 0.f;
    float4 vOutColor2 = (float4) 0.f;
        
    float3 vEye = -normalize(_in.vViewPos);
    float fOutLine = saturate(abs(dot(vEye, _in.vViewNormal)));
   // fOutLine = pow(fOutLine, 0.5);
    
    if (g_btex_0)
    {
        vOutColor1 = g_tex_0.Sample(g_sam_0, _in.vUV);
        vOutColor1.a = fOutLine;
    }
    if (g_btex_1)
    {
        vOutColor2 = g_tex_1.Sample(g_sam_0, _in.vUV);
        vOutColor2.a = fOutLine;
    }
    
    vOutColor = lerp(vOutColor1, vOutColor2, 0.6f); //1 - vOutColor1.a);
    vOutColor.a = 1.0f;
    
    return vOutColor;
}

float4 PS_MonsterTargetShape(VS_DEBUG_OUT _in) : SV_Target
{
    float4 vOutColor = float4(1.0f, 0.f, 0.f, 1.f);
        
    float3 vEye = -normalize(_in.vViewPos);
    float fOutLine = 1.f - saturate(abs(dot(vEye, _in.vViewNormal)));
    fOutLine = pow(fOutLine, 2.5);
    
    vOutColor.a = fOutLine;
    
    return vOutColor;
}

#endif
