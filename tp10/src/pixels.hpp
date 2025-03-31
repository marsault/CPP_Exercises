#pragma once
#include "../lib/image_lib.hpp"

// question C: définition des struct
struct RGBA 
{
    uint8_t r, g, b, a;
};

struct RGB
{
    uint8_t r, g, b;
};

struct Luma
{
    uint8_t gray;
};


// question C: implémentation des conversions
// modèle de base
template <typename To, typename From>
To convert(const From& stuff);

// spécialisations
// type entrée == type sortie
template <>
RGBA convert<RGBA, RGBA>(const RGBA& x) { return x; }

template <>
RGB convert<RGB, RGB>(const RGB& x) {return x; }

template <>
Luma convert<Luma, Luma>(const Luma& x) { return x; }

// RGBA -> RGB
template <>
RGB convert<RGB, RGBA>(const RGBA& x) { return { x.r, x.g, x.b }; }

// RGB -> RGBA
template <>
RGBA convert<RGBA, RGB>(const RGB& x) { return { x.r, x.g, x.b, 255 }; }

// RGB -> Luma: on utilise image_lib::rgb_to_grayscale()
template <>
Luma convert<Luma, RGB>(const RGB& x) { return Luma{image_lib::rgb_to_grayscale(x.r, x.g, x.b)}; }

// Luma -> RGB: on utilise image_lib::grayscale_to_rgb()
template <>
RGB convert<RGB, Luma>(const Luma& x) 
{ 
    const auto data = image_lib::grayscale_to_rgb(x.gray); 
    return RGB {data[0], data[1], data[2]};
}

// RGBA -> Luma: on utilise convert<RGBA, RGB> et convert<RGB,Luma>
template <>
Luma convert<Luma, RGBA>(const RGBA& x) { return convert<Luma, RGB>(convert<RGB, RGBA>(x)); }

// Luma -> RGBA: on utilise convert<Luma, RGB> et convert<RGB,RGBA>
template <>
RGBA convert<RGBA, Luma>(const Luma& x) { return convert<RGBA, RGB>(convert<RGB, Luma>(x)); }

// question D.1
// RGBA + RGBA (cas de base)
RGBA operator+(const RGBA& lhs, const RGBA& rhs)
{
    const auto data = image_lib::mix_color(lhs.r, lhs.g, lhs.b, lhs.a, rhs.r, rhs.g, rhs.b, rhs.a);
    return {data[0], data[1], data[2], data[3]};
}

// question D.2
// RGB + RGBA -> RGB
RGB operator+(const RGB& lhs, const RGBA& rhs)
{
    const auto new_lhs = convert<RGBA, RGB>(lhs);
    return convert<RGB, RGBA>(new_lhs + rhs);
}

// Luma + RGBA -> RGB
RGB operator+(const Luma& lhs, const RGBA& rhs)
{
    const auto new_lhs = convert<RGBA, Luma>(lhs);
    return convert<RGB, RGBA>(new_lhs + rhs);
}

// RGBA + RGB -> RGBA
RGBA operator+(const RGBA& lhs, const RGB& rhs)
{
    const auto new_rhs = convert<RGBA, RGB>(rhs);
    return lhs + new_rhs;
}

// RGB + RGB -> RGB
RGB operator+(const RGB& lhs, const RGB& rhs)
{
    const auto new_lhs = convert<RGBA, RGB>(lhs);
    const auto new_rhs = convert<RGBA, RGB>(rhs);
    return convert<RGB, RGBA>(new_lhs + new_rhs);
}

// Luma + RGB -> RGB
RGB operator+(const Luma& lhs, const RGB& rhs)
{
    const auto new_lhs = convert<RGBA, Luma>(lhs);
    const auto new_rhs = convert<RGBA, RGB>(rhs);
    return convert<RGB, RGBA>(new_lhs + new_rhs);
}
