#pragma once
#include <cstddef>
#include <array>
#include <functional>

template<typename Pixeltype1, typename Pixeltype2>
using CombinedPixel = decltype(std::declval<Pixeltype1>() + std::declval<Pixeltype2>());

template<typename P, size_t W, size_t H>
class Image
{

public:
    Image() = default;

    Image(const P& pixel) {
        for (size_t i = 0; i < H; i++) {
            std::fill(_image.at(i), W, pixel);
        }
    }

    Image(const std::function<P(size_t i, size_t j)>& f) {
        for (size_t i = 0; i < H; i++) {
            for (size_t j = 0; j < W; j++) {
                _image[i][j] = f(i, j);
            }
        }
    }

    const P& operator()(size_t i, size_t j)const {
        return _image.at(j).at(i);
    }

    P& operator()(size_t i, size_t j) {
        return _image[j][i];
    }

    template <typename OtherP>
    Image<CombinedPixel<P, OtherP>, W, H> operator+(const Image<OtherP, W, H>& other) const {
        auto result = Image<CombinedPixel<P, OtherP>, W, H> {};
        for (auto h = size_t { 0 }; h < H; ++h) {
            for (auto w = size_t { 0 }; w < W; ++w) {
                result(w, h) = (*this)(w, h) + other(w, h);
            }
        }
        return result;
    }

private:
    std::array<std::array<P, W>, H> _image;
    // size_t _W;
    // size_t _H;
};

