#pragma once

#include "ez/Span.h"
#include <array>
#include <cstdlib>

namespace ez
{
// IsArray
template <typename T>
struct IsArray : std::false_type
{
};

template <typename T, std::size_t N>
struct IsArray<std::array<T, N>> : std::true_type
{
};

template <typename T>
static constexpr auto IsArray_v = IsArray<T>::value;

// IsSpan
template <typename T>
struct IsSpan : std::false_type
{
};

template <typename T>
struct IsSpan<Span<T>> : std::true_type
{
};

template <typename T>
static constexpr auto IsSpan_v = IsSpan<T>::value;
}