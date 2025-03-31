// question A
#pragma once
#include <array>
#include <functional>

// question D.4: définition d'un alias-templaté
template<typename Pixeltype1, typename Pixeltype2>
using CombinedPixel = decltype(std::declval<Pixeltype1>() + std::declval<Pixeltype2>());

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
        // le modèle suivant convient pour additionner des pixels de même type, mais à partir de la
        // question D.4, on commence à les mélanger
        //
        // Image<P, W, H> operator+(const Image<P, W, H>& other) const
        //
        // on doit donc le modifier comme suit:
        template <typename OtherP>
        Image<CombinedPixel<P, OtherP>, W, H> operator+(const Image<OtherP, W, H>& other) const
        {
            // auto result = Image<P, W, H> {}; // question A.4
            // question D.4: il faut maintenant renvoyer une Image de CombinedPixel;
            // le reste de la fonction ne change pas
            auto result = Image<CombinedPixel<P, OtherP>, W, H> {};
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
