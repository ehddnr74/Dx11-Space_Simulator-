#ifndef _POSTPROCESS
#define _POSTPROCESS

#include "value.fx"

struct VS_IN
{
    float3 vLocalPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position; // System Value
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};


// ============================
// GrayShader
// mesh : RectMesh
// Domain : DOMAIN_POSTPROCESS
// g_tex_0 : RederTarget Copy Texture

// Parameter
// g_int_0 : Check Index
// ============================
VS_OUT VS_GrayShader(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    output.vPosition = float4(_in.vLocalPos * 2.f, 1.f);
    
    output.vUV = _in.vUV;

    return output;
}

#define hitratio g_float_2;

float4 PS_GrayShader(VS_OUT _in) : SV_Target
{
	// �ȼ� ��ǥ
    // _in.vPosition.xy;
    float2 vScreenUV = _in.vPosition.xy / g_Resolution;
    
    //float4 vColor = g_tex_0.Sample(g_sam_0, _in.vUV);	
    float4 vColor = g_tex_0.Sample(g_sam_0, vScreenUV);
	
    //float vAver = (vColor.r + vColor.g + vColor.b) / 3.f;

    float a = hitratio;

    vColor = float4(1.0f, 0.f, 0.f, a);
	
    //vColor = float4(1.f, 0.f, 0.f, 0.5f);
  
    return vColor;
}



float4 PS_FlashShader(VS_OUT _in) : SV_Target
{
	//// �ȼ� ��ǥ
 //   // _in.vPosition.xy;
 //   float2 vUV = _in.vPosition.xy / g_Resolution;
    
 //   float4 vOutColor = (float4) 0.f;
   
 //   if (g_btex_0)
 //   {
 //       vOutColor = g_tex_0.Sample(g_sam_0, _in.vUV);
 //   }
    
 //   if(vOutColor.a == 0.f)
 //       discard;
      
    
 //   vOutColor = (1.0f, 0.f, 0.f, 1.0f);
    
 //   return vOutColor;
    
    float4 vOutColor = (float4) 0.f;
        
    if (g_btex_0)
    {
        vOutColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    } 
    
    if(vOutColor.a != 1)
        discard;
    
    return vOutColor;
}



// ============================
// Distortion Shader
// mesh : RectMesh
// Domain : DOMAIN_POSTPROCESS
// g_tex_0 : RederTarget Copy Texture
// g_tex_1 : Noise Texture
// ============================
VS_OUT VS_Distortion(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

   // output.vPosition = mul(float4(_in.vLocalPos, 1.f), g_matWVP);
    output.vPosition = float4(_in.vLocalPos * 2.f, 1.f);
    output.vUV = _in.vUV;

    return output;
}

float4 PS_Distortion(VS_OUT _in) : SV_Target
{
    float2 vUV = _in.vPosition.xy / g_Resolution;
		
	
    float fChange = cos(((vUV.x - g_AccTime * 0.05f) / 0.15f) * 2 * 3.1415926535f) * 0.01f;

    vUV.y += fChange;

    float4 vColor = g_tex_0.Sample(g_sam_0, vUV);
    //vColor.r *= 2.f;

    return vColor;
}

//float4 PS_Distortion(VS_OUT _in) : SV_Target
//{
//    float2 vUV = _in.vPosition.xy / g_Resolution;
	
//	// Noise Texture �� ������ �Ǿ� �ִٸ�
//    if (g_btex_1)
//    {
//        float2 vNoiseUV = float2(_in.vUV.x - (g_AccTime * 0.2f), _in.vUV.y);
//        float4 vNoise = g_tex_1.Sample(g_sam_0, vNoiseUV);

//        vNoise = (vNoise - 0.5f) * 0.02f;

//        vUV += vNoise.r;
//    }

//    float4 vColor = g_tex_0.Sample(g_sam_0, vUV);

//    //vColor.r *= 2.f;
	
//    return vColor;
//}








#endif