// question A
#pragma once
#include <array>
#include <functional>

template<typename P, size_t W, size_t H>
class Image
{
    private:
        std::array<std::array<P, W>, H> _data;

    public:
        // question A.2: 
        Image() = default;
        Image(const P& pixel) 
        {
            // initialiser un array dont chaque ligne est un array de W pixels de type P
            for(auto& ligne: _data)
                ligne.fill(pixel);
        } 

        // question A.3: opérateurs; on échange i et j dans les accès, conformément à l'énoncé
        const P& operator()(const int& i, const int& j) const { return _data[j][i]; } // consultation
        P&       operator()(const int& i, const int& j)       { return _data[j][i]; } // affectation

        // question A.4: opérateur pour l'"addition" (utile à partir de la question D)
        Image<P, W, H> operator+(const Image<P, W, H>& other) const
        {
            auto result = Image<P, W, H> {};
            for (auto h = size_t { 0 }; h < H; ++h)
                for (auto w = size_t { 0 }; w < W; ++w)
                    result(w, h) = (*this)(w, h) + other(w, h);
    
            return result;
        }
    
        // question A.5: initialisation à l'aide d'un foncteur
        Image(const std::function<P(size_t i, size_t j)>& functor)
        {
            for (auto h = size_t { 0 }; h < H; ++h)
                for (auto w = size_t { 0 }; w < W; ++w)
                    (*this)(h, w) = functor(h, w);
        }
    
};
