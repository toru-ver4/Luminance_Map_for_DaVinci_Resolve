#ifndef TY_DRAW_LIB
#define TY_DRAW_LIB

#define FONT_COLOR_IDX_RED (0)
#define FONT_COLOR_IDX_GREEN (1)
#define FONT_COLOR_IDX_BLUE (2)
#define FONT_COLOR_IDX_CYAN (3)
#define FONT_COLOR_IDX_MAGENTA (4)
#define FONT_COLOR_IDX_YELLOW (5)

#define CROSS_HAIR_COLOR_IDX_RED (0)
#define CROSS_HAIR_COLOR_IDX_GREEN (1)
#define CROSS_HAIR_COLOR_IDX_BLUE (2)
#define CROSS_HAIR_COLOR_IDX_CYAN (3)
#define CROSS_HAIR_COLOR_IDX_MAGENTA (4)
#define CROSS_HAIR_COLOR_IDX_YELLOW (5)


typedef struct{
    int x;
    int y;
} int2;


typedef struct {
    float2 st_pos;
    float3 rgb;
} DigitResult;

__CONSTANT__ float3 rgbmyc_color[] = {
    {0.5, 0.0, 0.0},
    {0.0, 0.5, 0.0},
    {0.0, 0.0, 0.5},
    {0.0, 0.5, 0.5},
    {0.5, 0.0, 0.5},
    {0.5, 0.5, 0.0},
};

__CONSTANT__ float3 cross_hair_color = {0.5, 0.0, 0.5};
__CONSTANT__ float3 seven_seg_color = {0.5, 0.5, 0.5};
__CONSTANT__ float3 cross_hair_edge_color = {0.0, 0.0, 0.0};
__CONSTANT__ float3 black_color = {0.0, 0.0, 0.0};
__CONSTANT__ float3 grey_color = {0.6, 0.6, 0.6};
__CONSTANT__ int digit_to_mask[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
#define TEXT_PERIOD_MASK (0x80)
#define TEXT_NEGATIVE_MASK (0x40)
#define TEXT_EFFECTIVE_DIGIT (6)


__DEVICE__ float3 draw_rectangle_int(int p_Width, int p_Height, int p_X, int p_Y, float3 rgb_in, int2 st_pos, int2 ed_pos, float3 line_color)
{
    float3 rgb_out = rgb_in;
    if((st_pos.x <= p_X) && (p_X < ed_pos.x)){
        if((st_pos.y <= p_Y) && (p_Y < ed_pos.y)){
            rgb_out.x = line_color.x;
            rgb_out.y = line_color.y;
            rgb_out.z = line_color.z;
        }
    }

    return rgb_out;
}


__DEVICE__ float3 draw_rectangle(int p_Width, int p_Height, int p_X, int p_Y, float3 rgb_in, float2 st_pos, float2 ed_pos, float3 line_color)
{
    float3 rgb_out = rgb_in;
    if((st_pos.x <= p_X) && (p_X < ed_pos.x)){
        if((st_pos.y <= p_Y) && (p_Y < ed_pos.y)){
            rgb_out.x = line_color.x;
            rgb_out.y = line_color.y;
            rgb_out.z = line_color.z;
        }
    }

    return rgb_out;
}


__DEVICE__ float2 calc_cross_hair_pos(int p_Width, int p_Height, int p_X, int p_Y, float h_center_pos_rate, float v_center_pos_rate)
{
    float2 pos;
    pos.x = h_center_pos_rate * p_Width + 0.5;
    pos.y = v_center_pos_rate * p_Height + 0.5;

    return pos;
}

__DEVICE__ float3 draw_single_digit(int p_Width, int p_Height, int p_X, int p_Y, float3 rgb_in, float2 g_st_pos, int r_height, int r_width, int d_mask, float3 line_color)
{
    float3 rgb_out = rgb_in;
    float2 st_pos;
    float2 ed_pos;

    // A
    if((d_mask & 0x01) == 0x01){
        st_pos = make_float2(g_st_pos.x + r_height, g_st_pos.y);
        ed_pos = make_float2(st_pos.x + r_width, st_pos.y + r_height);
        rgb_out = draw_rectangle(p_Width, p_Height, p_X, p_Y, rgb_out, st_pos, ed_pos, line_color);
    }

    // B
    if((d_mask & 0x02) == 0x02){
        st_pos = make_float2(g_st_pos.x + r_height + r_width, g_st_pos.y + r_height);
        ed_pos = make_float2(st_pos.x + r_height, st_pos.y + r_width);
        rgb_out = draw_rectangle(p_Width, p_Height, p_X, p_Y, rgb_out, st_pos, ed_pos, line_color);
    }

    // C
    if((d_mask & 0x04) == 0x04){
        st_pos = make_float2(g_st_pos.x + r_height + r_width, g_st_pos.y + r_height * 2 + r_width);
        ed_pos = make_float2(st_pos.x + r_height, st_pos.y + r_width);
        rgb_out = draw_rectangle(p_Width, p_Height, p_X, p_Y, rgb_out, st_pos, ed_pos, line_color);
    }

    // D
    if((d_mask & 0x08) == 0x08){
        st_pos = make_float2(g_st_pos.x + r_height, g_st_pos.y + (r_height + r_width) * 2);
        ed_pos = make_float2(st_pos.x + r_width, st_pos.y + r_height);
        rgb_out = draw_rectangle(p_Width, p_Height, p_X, p_Y, rgb_out, st_pos, ed_pos, line_color);
    }

    // E
    if((d_mask & 0x10) == 0x10){
        st_pos = make_float2(g_st_pos.x, g_st_pos.y + r_height * 2 + r_width);
        ed_pos = make_float2(st_pos.x + r_height, st_pos.y + r_width);
        rgb_out = draw_rectangle(p_Width, p_Height, p_X, p_Y, rgb_out, st_pos, ed_pos, line_color);
    }

    // F
    if((d_mask & 0x20) == 0x20){
        st_pos = make_float2(g_st_pos.x, g_st_pos.y + r_height);
        ed_pos = make_float2(st_pos.x + r_height, st_pos.y + r_width);
        rgb_out = draw_rectangle(p_Width, p_Height, p_X, p_Y, rgb_out, st_pos, ed_pos, line_color);
    }

    // G
    if((d_mask & 0x40) == 0x40){
        st_pos = make_float2(g_st_pos.x + r_height, g_st_pos.y + r_height + r_width);
        ed_pos = make_float2(st_pos.x + r_width, st_pos.y + r_height);
        rgb_out = draw_rectangle(p_Width, p_Height, p_X, p_Y, rgb_out, st_pos, ed_pos, line_color);
    }

    // H
    if((d_mask & 0x80) == 0x80){
        st_pos = make_float2(g_st_pos.x, g_st_pos.y + (r_height + r_width) * 2);
        ed_pos = make_float2(st_pos.x + r_height, st_pos.y + r_height);
        rgb_out = draw_rectangle(p_Width, p_Height, p_X, p_Y, rgb_out, st_pos, ed_pos, line_color);
    }

    return rgb_out;
}


__DEVICE__ int calc_integer_digits(float drawing_value)
{
    int integer_digits = 1;
    int max_digits = TEXT_EFFECTIVE_DIGIT;
    int ii;

    for(ii=max_digits; ii > 0; ii--){
        if(drawing_value >= _powf(10, ii - 1)){
            integer_digits = ii;
            break;
        }
    }
    return integer_digits;
}


__DEVICE__ float2 calc_text_width(int r_width, int r_height)
{
    float2 out;
    out.x = r_width + r_height * 4;  // text width for digits
    out.y = r_height * 4;            // text width for period

    return out;
}

__DEVICE__ DigitResult draw_digits_int(int p_Width, int p_Height, int p_X, int p_Y, float3 rgb_in, float drawing_value, int2 g_st_pos, int r_height, int r_width, float3 font_color)
{
    int ii;
    float3 rgb_out = rgb_in;
    float2 text_width_float = calc_text_width(r_width, r_height);
    int text_width = int(text_width_float.x);
    int text_width_period = int(text_width_float.y);
    float magnitude_value;
    int digit;
    int integer_digits = calc_integer_digits(drawing_value);
    int decimal_digits;
    int drawing_value_int;
    int is_negative = 0;
    float2 st_pos;
    st_pos.x = g_st_pos.x;
    st_pos.y = g_st_pos.y;

    // draw background
    int text_height = (r_height + r_width) * 2;
    int text_height_margin = r_height * 2;

    // draw background (dark)
    if((p_Y >= (g_st_pos.y - text_height_margin)) && (p_Y < (g_st_pos.y + text_height + text_height_margin))){
        if((p_X >= (g_st_pos.x - r_height * 2)) && (p_X < (g_st_pos.x + (text_width * integer_digits + text_width) - text_width))){
            rgb_out.x = rgb_in.x / 3.0;
            rgb_out.y = rgb_in.y / 3.0;
            rgb_out.z = rgb_in.z / 3.0;
        }
    }

    if(drawing_value < 0){
        is_negative = 1;
    }
    drawing_value = _fabs(drawing_value);
    // integer_digits = calc_integer_digits(drawing_value);
    decimal_digits = TEXT_EFFECTIVE_DIGIT - integer_digits;
    if(is_negative){
        decimal_digits -= 1;  // Using one digit to render the "-" character.
    }

    // convert float to int for round-up.
    drawing_value_int = int(_round(drawing_value * _powf(10, decimal_digits)));

    // for negative value
    if(is_negative){
        rgb_out = draw_single_digit(p_Width, p_Height, p_X, p_Y, rgb_out, st_pos, r_height, r_width, TEXT_NEGATIVE_MASK, font_color);
        st_pos.x += text_width;
    }

    // draw integer value
    st_pos.x -= text_width;  // To neutralize the effect of the initial offset calculation in the for loop.
    for(ii=0; ii<integer_digits; ii++){
        magnitude_value = _powf(10, (integer_digits + decimal_digits - ii - 1));
        digit = int(_fmod((_floorf(drawing_value_int / magnitude_value)), 10));
        st_pos.x += text_width;
        rgb_out = draw_single_digit(p_Width, p_Height, p_X, p_Y, rgb_out, st_pos, r_height, r_width, digit_to_mask[digit], font_color);
    }

    DigitResult result;
    result.st_pos = st_pos;
    result.rgb = rgb_out;
    return result;
}

#endif
