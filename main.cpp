#include <iostream>
#include "char_array_to_std_array.hpp"
#include "number_to_string.hpp"
#include "string_concat.hpp"
#include "string_length.hpp"

template <std::size_t N>
struct BottlesForm
{
    constexpr static auto apply() { return concat(stringify<N>(), " bottles"); }
};

template <>
struct BottlesForm<1>
{
    constexpr static auto apply() { return charArrayToStdArray("1 bottle"); }
};

template <>
struct BottlesForm<0>
{
    constexpr static auto apply() { return charArrayToStdArray("no more bottles"); }
};

template <std::size_t N>
constexpr auto bottlesForm()
{
    return BottlesForm<N>::apply();
}

template <std::size_t N>
struct MiddlePart
{
    constexpr static auto apply()
    {
        return charArrayToStdArray("Take one down and pass it around - ");
    }
};

template <>
struct MiddlePart<1>
{
    constexpr static auto apply()
    {
        return charArrayToStdArray("Take it down and pass it around - ");
    }
};

template <std::size_t N>
constexpr auto middlePart()
{
    return MiddlePart<N>::apply();
}

template <std::size_t N>
constexpr auto verse()
{
    return concat(bottlesForm<N>(), " of beer on the wall, ", bottlesForm<N>(), " of beer. ",
                  middlePart<N>(), bottlesForm<N - 1>(), " of beer on the wall.\n");
}

template <std::size_t N>
struct SongComposition
{
    constexpr static auto apply() { return concat(verse<N>(), SongComposition<N - 1>::apply()); }
};

template <>
struct SongComposition<1>
{
    constexpr static auto apply() { return verse<1>(); }
};

template <std::size_t N>
constexpr auto composeSong()
{
    return SongComposition<N>::apply();
}

int main()
{
    // WARNING: make sure you have enough memory to compile it! GCC 7.4.0 needs about 2.5 GB of memory. Beware, you have been warned!
    constexpr auto song = composeSong<99>();
    std::cout << song.data() << '\n';
}
