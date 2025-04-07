#include "../lib/image_lib.hpp"
#include "image.hpp"

#include <filesystem>
#include <iostream>
#include <string>

void usage()
{
    std::cout << "Usage:\n"
              << "./gray path/to/images/folder" << std::endl;
}

// On définit une nouvelle classe GrayScale qui boxe un uint8_t...
struct GrayScale
{
    uint8_t value;
};

// ... pour pouvoir redefinir l'opérateur + sur ce type
GrayScale operator+(GrayScale l, GrayScale r)
{
    // Rappelez vous que 0 représente le noir et 255 le blanc donc l'addition estompe les couleurs
    // Pour que l'addition superpose les motifs, on inverse les valeurs:
    int res = (255 - ((255 - l.value) + (255 - r.value)));
    if (res < 0)
        return { 0 };
    else
        return { static_cast<uint8_t>(res) };
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        usage();
        return -1;
    }

    const auto input_path = std::filesystem::path { argv[1] };

    {
        constexpr unsigned size = 128;

        auto img = Image<uint8_t, size, 2 * size> { 127 };
        std::cout << static_cast<int>(img(1, 1)) << std::endl;    // -> 127
        std::cout << static_cast<int>(img(56, 156)) << std::endl; // -> 127
        for (int i = -9; i < 10; ++i)
        {
            img(63 + i, 127) = 255u;
            img(63, 127 + i) = 255u;
        }
        std::cout << static_cast<int>(img(63, 127)) << std::endl; // -> 255
        image_lib::save(img, "images/gray-rectangle-with-white-cross.png");
    }

    {
        constexpr unsigned size = 100;
        auto               v    = image_lib::load<GrayScale, size, size>(input_path / "v.png");
        auto               m    = image_lib::load<GrayScale, size, size>(input_path / "m.png");
        auto               vm   = v + m;
        image_lib::save(vm, "images/vm.png");
    }

    {
        constexpr unsigned size  = 128;
        auto               shade = Image<uint8_t, 2 * size, size> { [](size_t x, size_t y) { return x; } };
        image_lib::save(shade, "images/left-to-right-shade.png");
    }

    return 0;
}