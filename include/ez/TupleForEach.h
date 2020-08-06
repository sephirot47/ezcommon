#pragma once

#include <cstdint>
#include <tuple>
#include <type_traits>

template <typename TTuple, typename TFunction, std::size_t... TIndices>
void _ForEach(TTuple&& ioTuple, const TFunction& inFunction, std::index_sequence<TIndices...>)
{
  using swallow = int[];
  (void)swallow { 1, (inFunction(std::get<TIndices>(std::forward<TTuple>(ioTuple))), void(), int {})... };
}

template <typename TTuple, typename TFunction>
void ForEach(TTuple&& ioTuple, const TFunction& inFunction)
{
  constexpr std::size_t N = std::tuple_size<std::remove_cvref_t<TTuple>>::value;
  _ForEach(std::forward<TTuple>(ioTuple), inFunction, std::make_index_sequence<N> {});
}