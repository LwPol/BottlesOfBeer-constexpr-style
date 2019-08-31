#pragma once
#include <array>
#include <type_traits>

template <std::size_t N>
using size = std::integral_constant<std::size_t, N>;

template <std::size_t N>
constexpr size<N> length(const std::array<char, N>&)
{
    return {};
}
template <std::size_t N>
constexpr size<N> length(const char (&)[N])
{
    return {};
}

template <class T>
using length_t = decltype(length(std::declval<T>()));