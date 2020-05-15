#pragma once

#include <type_traits>

namespace ez
{

#define DECLARE_FLAGS(TFlagBits)                                                                                       \
  constexpr inline TFlagBits operator&(const TFlagBits inLHS, const TFlagBits inRHS)                                   \
  {                                                                                                                    \
    return static_cast<TFlagBits>(static_cast<std::underlying_type_t<TFlagBits>>(inLHS)                                \
        & static_cast<std::underlying_type_t<TFlagBits>>(inRHS));                                                      \
  }                                                                                                                    \
                                                                                                                       \
  constexpr inline TFlagBits operator|(const TFlagBits inLHS, const TFlagBits inRHS)                                   \
  {                                                                                                                    \
    return static_cast<TFlagBits>(static_cast<std::underlying_type_t<TFlagBits>>(inLHS)                                \
        | static_cast<std::underlying_type_t<TFlagBits>>(inRHS));                                                      \
  }                                                                                                                    \
                                                                                                                       \
  constexpr inline TFlagBits operator~(const TFlagBits inRHS)                                                          \
  {                                                                                                                    \
    return static_cast<TFlagBits>(~static_cast<std::underlying_type_t<TFlagBits>>(inRHS));                             \
  }                                                                                                                    \
                                                                                                                       \
  constexpr inline bool IsFlagOn(const TFlagBits inFlags, const TFlagBits inFlagToCheck)                               \
  {                                                                                                                    \
    return static_cast<int>(inFlags & inFlagToCheck) != 0;                                                             \
  }
}