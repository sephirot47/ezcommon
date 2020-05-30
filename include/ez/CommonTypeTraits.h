#pragma once

#include "ez/Span.h"
#include <array>
#include <cstdlib>
#include <variant>

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

// VariantIndex
template <typename TVariantType, typename T, std::size_t TIndex>
constexpr std::size_t VariantIndex()
{
  if constexpr ((TIndex == std::variant_size_v<TVariantType>)
      || std::is_same_v<std::variant_alternative_t<TIndex, TVariantType>, T>)
  {
    return TIndex;
  }
  else
  {
    return VariantIndex<TVariantType, T, TIndex + 1>();
  }
}

template <typename TVariantType, typename T>
static constexpr auto VariantIndex_v = VariantIndex<TVariantType, T, 0>();
}