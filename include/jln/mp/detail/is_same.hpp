#pragma once

#include <jln/mp/detail/compiler.hpp>

#if JLN_MP_HAS_BUILTIN(__is_same)
#  define JLN_MP_IS_SAME_V __is_same
#else
// TODO with msvc: using std::is_same (except when no stl)
namespace jln::mp::detail
{
  template<class x, class y> JLN_MP_CONSTEXPR_VAR bool is_same_v = false;
  template<class x> JLN_MP_CONSTEXPR_VAR is_same_v<x, x> = true;

#define JLN_MP_IS_SAME_V(...) ::jln::mp::detail::is_same<__VA_ARGS__>
}
#endif
