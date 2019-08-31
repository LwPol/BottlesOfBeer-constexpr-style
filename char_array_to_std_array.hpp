#pragma once
#include <array>
#include "string_length.hpp"

template <std::size_t... I>
using converted_string = std::array<char, std::index_sequence<I...>::size()>;

template <std::size_t N, std::size_t... I>
constexpr converted_string<I...> charArrayToStdArrayImpl(const char (&array)[N],
                                                         std::index_sequence<I...>)
{
    return {{array[I]...}};
}

template <std::size_t N>
constexpr auto charArrayToStdArray(const char (&array)[N])
{
    using arrayLength = length_t<decltype(array)>;
    return charArrayToStdArrayImpl(array, std::make_index_sequence<arrayLength::value>{});
}