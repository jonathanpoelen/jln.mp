#pragma once

#include <jln/mp/detail/compiler.hpp>

#ifndef JLN_MP_NO_STL_TRAIT
# define JLN_MP_NO_STL_TRAIT 0
#endif

#if JLN_MP_HAS_BUILTIN(__is_same)
#  define JLN_MP_IS_SAME_V __is_same
#else

#if JLN_MP_MSVC && ! JLN_MP_NO_STL_TRAIT
# include <type_traits>

namespace jln::mp::detail
{
  using std::is_same_v;
}
#else
namespace jln::mp::detail
{
  template<class T, class U> JLN_MP_CONSTEXPR_VAR bool is_same_v = false;
  template<class T> JLN_MP_CONSTEXPR_VAR is_same_v<T, T> = true;
}
#endif

#define JLN_MP_IS_SAME_V(...) ::jln::mp::detail::is_same<__VA_ARGS__>

#endif
