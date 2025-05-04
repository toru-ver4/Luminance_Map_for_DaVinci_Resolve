// Basic Color Library made by Toru Yoshihara
#ifndef TY_COLOR_LIB_H
#define TY_COLOR_LIB_H

#include "ampas_color_lib.h"

#define GAMUT_IDX_BT709  (0)
#define GAMUT_IDX_P3D65  (1)
#define GAMUT_IDX_BT2020 (2)

typedef struct {
    float3 row0;
    float3 row1;
    float3 row2;
} Matrix3x3;

__CONSTANT__ float rgb2y_coef_bt2020[] = {0.26270021f, 0.67799807f, 0.05930171f};

__CONSTANT__ Matrix3x3 bt2020_to_p3d65_mtx = {
    { 0.75383303, 0.19859737, 0.0475696 },
    { 0.04574385, 0.94177722, 0.01247893 },
    { -0.00121034, 0.01760172, 0.98360862 }
};

__CONSTANT__ Matrix3x3 p3d65_to_bt2020_mtx = {
    { 1.34357825, -0.28217967, -0.06139858 },
    { -0.06529745, 1.07578792, -0.01049046 },
    { 0.00282179, -0.01959849, 1.01677671 }
};

__CONSTANT__ Matrix3x3 bt2020_to_rec709_mtx = {
    { 1.660491, -0.58764114, -0.07284986 },
    { -0.12455047, 1.1328999, -0.00834942 },
    { -0.01815076, -0.1005789, 1.11872966 }
};

// Apply 3x3 matrix
__DEVICE__ float3 apply_matrix(float3 in, Matrix3x3 mtx)
{
    float3 out;
    out.x = in.x * mtx.row0.x + in.y * mtx.row0.y + in.z * mtx.row0.z;
    out.y = in.x * mtx.row1.x + in.y * mtx.row1.y + in.z * mtx.row1.z;
    out.z = in.x * mtx.row2.x + in.y * mtx.row2.y + in.z * mtx.row2.z;
    return out;
}

// Converts RGB to Y.
__DEVICE__ float rgb_2_y(float3 in)
{
    float y;
    y = rgb2y_coef_bt2020[0] * in.x +
        rgb2y_coef_bt2020[1] * in.y +
        rgb2y_coef_bt2020[2] * in.z;
    return y;
}


// Gamma EOTF
__DEVICE__ float eotf_gamma(float in, float gamma)
{
    float y = _powf(in, gamma);
    return y;
}


__DEVICE__ float oetf_gamma(float in, float gamma)
{
    float y = _powf(in, 1.0f/gamma);
    return y;
}


__DEVICE__ float3 eotf_gamma24_f3(float3 in)
{
    float3 out;
    out.x = eotf_gamma(in.x, 2.4f);
    out.y = eotf_gamma(in.y, 2.4f);
    out.z = eotf_gamma(in.z, 2.4f);
    return out;
}

__DEVICE__ float3 oetf_gamma24_f3(float3 in)
{
    float3 out;
    out.x = oetf_gamma(in.x, 2.4f);
    out.y = oetf_gamma(in.y, 2.4f);
    out.z = oetf_gamma(in.z, 2.4f);
    return out;
}


// sRGB EOTF
__DEVICE__ float eotf_srgb(float in)
{
    float y;
    if(in <= 0.04045){
        y = in / 12.92f;
    }
    else{
        y = _powf((in + 0.055) / 1.055, 2.4);
    }
    return y;
}

// sRGB OETF
__DEVICE__ float oetf_srgb(float in)
{
    float y;
    if(in <= 0.0031308f){
        y = in * 12.92f;
    }
    else{
        y = 1.055f * _powf(in, 1.0f / 2.4f) - 0.055f;
    }
    return y;
}

__DEVICE__ float3 eotf_srgb_f3(float3 in)
{
    float3 out;
    out.x = eotf_srgb(in.x);
    out.y = eotf_srgb(in.y);
    out.z = eotf_srgb(in.z);
    return out;
}

__DEVICE__ float3 oetf_srgb_f3(float3 in)
{
    float3 out;
    out.x = oetf_srgb(in.x);
    out.y = oetf_srgb(in.y);
    out.z = oetf_srgb(in.z);
    return out;
}


__DEVICE__ inline float3 oetf_st2084_f3(float3 in)
{
    return Linear_2_ST2084_f3(in);
}


__DEVICE__ inline float3 eotf_st2084_f3(float3 in)
{
    return ST2084_2_Linear_f3(in);
}

__DEVICE__ inline float oetf_st2084(float in)
{
    return Linear_2_ST2084(in);
}


__DEVICE__ inline float eotf_st2084(float in)
{
    return ST2084_2_Linear(in);
}


#endif
