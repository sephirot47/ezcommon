#pragma once

#include "ez/Span.h"

namespace ez
{
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