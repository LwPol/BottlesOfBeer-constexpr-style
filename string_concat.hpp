#pragma once
#include <array>
#include <utility>
#include "string_length.hpp"

constexpr std::size_t string_size()
{
    return 0;
}
template <class... Args>
constexpr std::size_t string_size(std::size_t size, Args... args)
{
    return (size == 0 ? 0 : size - 1) + string_size(args...);
}
template <class... Args>
using string_length = size<string_size(length_t<Args>{}...)>;

template <class... Args>
using combined_string = std::array<char, string_length<Args...>::value + 1>;

template <class Lhs, class Rhs, std::size_t... I1, std::size_t... I2>
constexpr const combined_string<Lhs, Rhs> concatImpl(const Lhs& lhs, const Rhs& rhs,
                                                     std::index_sequence<I1...>,
                                                     std::index_sequence<I2...>)
{
    return {{lhs[I1]..., rhs[I2]..., '\0'}};
}

template <class Lhs, class Rhs>
constexpr const combined_string<Lhs, Rhs> concat(const Lhs& lhs, const Rhs& rhs)
{
    return concatImpl(lhs, rhs, std::make_index_sequence<string_length<Lhs>::value>{},
                      std::make_index_sequence<string_length<Rhs>::value>{});
}

template <class T0, class T1, class... Ts>
constexpr const combined_string<T0, T1, Ts...> concat(const T0& t0, const T1& t1, const Ts&... ts)
{
    return concat(t0, concat(t1, ts...));
}

template <class T>
constexpr const combined_string<T> concat(const T& t)
{
    return concat(t, "");
}

constexpr const combined_string<> concat()
{
    return concat("");
}