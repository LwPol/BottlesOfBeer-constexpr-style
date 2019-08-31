#pragma once
#include <array>
#include <utility>

template <std::size_t Remainder, std::size_t... Digits>
constexpr auto concatRemainder(std::index_sequence<Digits...>)
{
    return std::index_sequence<Digits..., Remainder>{};
}

template <std::size_t Remainder, std::size_t Rest>
struct explode
{
    constexpr static auto apply()
    {
        using RestSeq = typename explode<Rest % 10, Rest / 10>::type;
        return concatRemainder<Remainder>(RestSeq{});
    }
    using type = decltype(apply());
};

template <std::size_t Remainder>
struct explode<Remainder, 0>
{
    using type = std::index_sequence<Remainder>;
};

template <std::size_t N>
using digits_t = typename explode<N % 10, N / 10>::type;

template <std::size_t... Digits>
using numerical_string = std::array<char, std::index_sequence<Digits...>::size() + 1>;

template <std::size_t... Digits>
constexpr const numerical_string<Digits...> stringifyImpl(std::index_sequence<Digits...> digits)
{
    return {{('0' + Digits)..., '\0'}};
}

template <std::size_t N>
constexpr auto stringify()
{
    return stringifyImpl(digits_t<N>{});
}