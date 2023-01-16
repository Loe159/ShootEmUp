#include "Math.h"

const Vec2 Vec2_Up    = {  0.0f,  1.0f };
const Vec2 Vec2_Down  = {  0.0f, -1.0f };
const Vec2 Vec2_Left  = { -1.0f,  0.0f };
const Vec2 Vec2_Right = {  1.0f,  0.0f };
const Vec2 Vec2_Zero  = {  0.0f,  0.0f };
const Vec2 Vec2_One   = {  1.0f,  1.0f };

Vec2 Vec2_Set(float x, float y)
{
    Vec2 v = { .x = x, .y = y };
    return v;
}

Vec2 Vec2_Perp(Vec2 v)
{
    return Vec2_Set(v.y, -v.x);
}

Vec2 Vec2_Add(Vec2 v1, Vec2 v2)
{
    const Vec2 v3 = {v1.x+v2.x, v1.y+v2.y};
    return v3;
}

Vec2 Vec2_Sub(Vec2 v1, Vec2 v2)
{
    const Vec2 v3 = {v1.x-v2.x, v1.y-v2.y};
    return v3;
}

Vec2 Vec2_Scale(Vec2 v, float s)
{
    const Vec2 v2 = {v.x*s, v.y*s};
    return v2;
}

float Vec2_Length(Vec2 v)
{
    return sqrtf(powf(v.x, 2)+ powf(v.y, 2));
}

Vec2 Vec2_Normalize(Vec2 v)
{
    const Vec2 v2 = {v.x/ Vec2_Length(v), v.y/ Vec2_Length(v)};
    return v2;
}

float Vec2_Distance(Vec2 v1, Vec2 v2)
{
    return sqrtf(powf(v1.x-v2.x, 2)+ powf(v1.y-v2.y, 2));
}
