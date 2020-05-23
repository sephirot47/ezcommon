#pragma once

#include "ez/Macros.h"
#include <array>
#include <cstdint>
#include <type_traits>
#include <vector>

namespace ez
{
template <typename T, bool IsConst>
struct GSpan final
{
public:
  using ValueType = T;
  using MaybeConstT = std::conditional_t<IsConst, const T, T>;
  using Iterator = const MaybeConstT*;
  using ConstIterator = const T*;

  GSpan(MaybeConstT* inData, const std::size_t inNumberOfElements)
      : mData(inData), mNumberOfElements(inNumberOfElements)
  {
  }

  Iterator begin() { return mData; }
  Iterator end() { return mData + mNumberOfElements; }
  ConstIterator begin() const { return mData; }
  ConstIterator end() const { return mData + mNumberOfElements; }
  ConstIterator cbegin() const { return begin(); }
  ConstIterator cend() const { return end(); }

  MaybeConstT& at(const std::size_t inIndex)
  {
    EXPECTS(inIndex < mNumberOfElements);
    return mData[inIndex];
  }
  const T& at(const std::size_t inIndex) const { return const_cast<GSpan&>(*this).at(inIndex); }
  MaybeConstT& operator[](const std::size_t inIndex) { return at(inIndex); }
  const T& operator[](const std::size_t inIndex) const { return const_cast<GSpan&>(*this).operator[](inIndex); }

  MaybeConstT* GetData() { return mData; }
  const T* GetData() const { return mData; }
  std::size_t GetNumberOfElements() const { return mNumberOfElements; }
  std::size_t GetSizeInBytes() const { return mNumberOfElements * sizeof(T); }

private:
  MaybeConstT* mData = nullptr;
  const std::size_t mNumberOfElements = 0;
};

template <typename T>
using Span = GSpan<T, true>;

template <typename T>
using MutableSpan = GSpan<T, false>;

template <typename T>
inline auto MakeSpan(const std::initializer_list<T>& inList)
{
  return Span<T>(&(*inList.begin()), std::distance(inList.begin(), inList.end()));
}
template <typename TArray>
inline auto MakeMutableSpan(TArray& inArray)
{
  return MutableSpan<typename TArray::value_type>(&(*inArray.begin()), std::distance(inArray.begin(), inArray.end()));
}
template <typename TArray>
inline auto MakeMutableSpan(TArray& inArray, const std::size_t inNumberOfElements)
{
  EXPECTS(inNumberOfElements <= inArray.size());
  return MutableSpan<typename TArray::value_type> { inArray.data(), inNumberOfElements };
}
template <typename TArray>
inline auto MakeSpan(const TArray& inArray)
{
  return Span<typename TArray::value_type>(&(*inArray.begin()), std::distance(inArray.begin(), inArray.end()));
}
template <typename TArray>
inline auto MakeSpan(const TArray& inArray, const std::size_t inNumberOfElements)
{
  EXPECTS(inNumberOfElements <= inArray.size());
  return Span<typename TArray::value_type> { inArray.data(), inNumberOfElements };
}
template <typename T>
inline auto MakeSpan(Span<T>& inMutableSpan)
{
  return Span<T>(inMutableSpan.GetData(), inMutableSpan.GetNumberOfElements());
}
}