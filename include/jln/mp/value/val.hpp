#pragma once

#include <jln/mp/config/debug.hpp>
#include <jln/mp/detail/compiler.hpp>

#include <type_traits>

namespace jln::mp
{
  /// \ingroup value

#if __cplusplus >= 201703L
# if !JLN_MP_ENABLE_DEBUG || JLN_MP_CLANG_LIKE
  template<auto v>
  struct val
  {
    static constexpr decltype(v) value = v;
  };

  template<class T, T v>
  using typed_val = val<v>;
# else
  template<class T, T v>
  struct typed_val
  {
    static constexpr T const value = v;
  };

  template<auto v>
  using val = typed_val<std::remove_const_t<decltype(v)>, v>;
# endif
#else
  template<class T, T v>
  struct typed_val
  {
    static constexpr T const value = v;
  };
#endif
}
