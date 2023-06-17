#pragma once

#include <jln/mp/detail/compiler.hpp>

#define JLN_MP_USE_STD_IS_SAME 1

#ifdef JLN_MP_NO_STL
# if JLN_MP_NO_STL
#   undef JLN_MP_USE_STD_IS_SAME
#   define JLN_MP_USE_STD_IS_SAME 0
# endif
#endif

#ifdef JLN_MP_NO_STL_TRAIT
# if JLN_MP_NO_STL_TRAIT
#   undef JLN_MP_USE_STD_IS_SAME
#   define JLN_MP_USE_STD_IS_SAME 0
# endif
#endif

#if JLN_MP_HAS_BUILTIN(__is_same)
# define JLN_MP_IS_SAME_V __is_same
namespace jln::mp::detail
{
  template<class T, class U> JLN_MP_CONSTEXPR_VAR bool is_same_v = __is_same(T, U);
}
#else

# if ! JLN_MP_GCC && JLN_MP_USE_STD_IS_SAME
#   include <type_traits>
namespace jln::mp::detail
{
  using std::is_same_v;
}
# else
namespace jln::mp::detail
{
  template<class T, class U> JLN_MP_CONSTEXPR_VAR bool is_same_v = false;
  template<class T> JLN_MP_CONSTEXPR_VAR is_same_v<T, T> = true;
}
# endif

# define JLN_MP_IS_SAME_V(...) ::jln::mp::detail::is_same<__VA_ARGS__>

#endif

#undef JLN_MP_USE_STD_IS_SAME
