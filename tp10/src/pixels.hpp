#pragma once

#include "../lib/image_lib.hpp"

#include <cstdint>

struct RGBA
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct RGB
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct Luma
{
    uint8_t l;
};

template <typename To, typename From>
To convert(const From& stuff);

template <>
RGBA convert<RGBA, RGBA>(const RGBA& x)
{
    return x;
}

template <>
RGB convert<RGB, RGB>(const RGB& x)
{
    return x;
}

template <>
Luma convert<Luma, Luma>(const Luma& x)
{
    return x;
}

template <>
RGB convert<RGB, RGBA>(const RGBA& x)
{
    return { x.r, x.g, x.b };
}

template <>
RGBA convert<RGBA, RGB>(const RGB& x)
{
    return { x.r, x.g, x.b, 255 };
}

template <>
Luma convert<Luma, RGB>(const RGB& x)
{
    return { image_lib::rgb_to_grayscale(x.r, x.g, x.b) };
}

template <>
RGB convert<RGB, Luma>(const Luma& x)
{
    auto rgb = image_lib::grayscale_to_rgb(x.l);
    return { rgb[0], rgb[1], rgb[2] };
}

template <>
Luma convert<Luma, RGBA>(const RGBA& x)
{
    return convert<Luma, RGB>(convert<RGB, RGBA>(x));
}

template <>
RGBA convert<RGBA, Luma>(const Luma& x)
{
    return convert<RGBA, RGB>(convert<RGB, Luma>(x));
}

RGBA operator+(const RGBA& lhs, const RGBA& rhs)
{
    auto rgba = image_lib::mix_color(lhs.r, lhs.g, lhs.b, lhs.a, rhs.r, rhs.g, rhs.b, rhs.a);
    return { rgba[0], rgba[1], rgba[2], rgba[3] };
}

RGB operator+(const RGB& lhs, const RGBA& rhs)
{
    auto converted = convert<RGBA, RGB>(lhs);
    auto rgba =
        image_lib::mix_color(converted.r, converted.g, converted.b, converted.a, rhs.r, rhs.g, rhs.b, rhs.a);
    return convert<RGB, RGBA>({ rgba[0], rgba[1], rgba[2], rgba[3] });
}

RGB operator+(const Luma& lhs, const RGBA& rhs)
{
    auto converted = convert<RGBA, Luma>(lhs);
    auto rgba =
        image_lib::mix_color(converted.r, converted.g, converted.b, converted.a, rhs.r, rhs.g, rhs.b, rhs.a);
    return convert<RGB, RGBA>({ rgba[0], rgba[1], rgba[2], rgba[3] });
}

RGBA operator+(const RGBA& lhs, const RGB& rhs)
{
    auto converted = convert<RGBA, RGB>(rhs);
    auto rgba =
        image_lib::mix_color(lhs.r, lhs.g, lhs.b, lhs.a, converted.r, converted.g, converted.b, converted.a);
    return { rgba[0], rgba[1], rgba[2], rgba[3] };
}

RGB operator+(const RGB& lhs, const RGB& rhs)
{
    auto converted1 = convert<RGBA, RGB>(rhs);
    auto converted2 = convert<RGBA, RGB>(rhs);
    auto rgba = image_lib::mix_color(converted1.r, converted1.g, converted1.b, converted1.a, converted2.r,
                                     converted2.g, converted2.b, converted2.a);
    return convert<RGB, RGBA>({ rgba[0], rgba[1], rgba[2], rgba[3] });
}

RGB operator+(const Luma& lhs, const RGB& rhs)
{
    auto converted1 = convert<RGBA, Luma>(lhs);
    auto converted2 = convert<RGBA, RGB>(rhs);
    auto rgba = image_lib::mix_color(converted1.r, converted1.g, converted1.b, converted1.a, converted2.r,
                                     converted2.g, converted2.b, converted2.a);
    return convert<RGB, RGBA>({ rgba[0], rgba[1], rgba[2], rgba[3] });
}

// template <typename P>
// RGBA operator+(const P& lhs, const Luma& mask)
// {
//     auto    converted1 = convert<RGBA, P>(lhs);
//     auto    converted2 = convert<RGBA, Luma>(mask);
//     auto    rgba  = image_lib::mix_color(converted1.r, converted1.g, converted1.b, converted1.a,
//     converted2.r,
//                                          converted2.g, converted2.b, converted2.a);
//     uint8_t alpha = (converted1.a * mask.l / 255);
//     return { rgba[0], rgba[1], rgba[2], alpha };
// }

RGBA operator+(const RGBA& lhs, const Luma& rhs)
{
    auto v = lhs;
    v.a    = v.a * rhs.l / 255;
    return v;
}

RGBA operator+(const RGB& lhs, const Luma& rhs)
{
    return convert<RGBA, RGB>(lhs) + rhs;
}