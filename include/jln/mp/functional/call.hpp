#pragma once

#include <jln/mp/config/debug.hpp>
#include <jln/mp/config/config.hpp>
#include <jln/mp/detail/compiler.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/memoize.hpp>
#include <jln/mp/utility/conditional.hpp>

namespace jln::mp
{
  class to_many_argument_error {};

  /// \cond
  namespace detail
  {
    template<bool> struct dcall;
    template<bool> struct dcallf;
    template<bool> struct dcall_c;
    template<bool> struct dcallf_c;
  }
  /// \endcond

  /// \ingroup functional

#define JLN_MP_DCALL_XS(xs, ...) JLN_MP_DCALL(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT, __VA_ARGS__)
#define JLN_MP_DCALL_V_XS(xs, ...) JLN_MP_DCALL_V(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT, __VA_ARGS__)
#define JLN_MP_DCALLF_XS(xs, ...) JLN_MP_DCALLF(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT, __VA_ARGS__)
#define JLN_MP_DCALLF_C_XS(xs, ...) JLN_MP_DCALLF_C(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT, __VA_ARGS__)


#if JLN_MP_MSVC || JLN_MP_ENABLE_DEBUG || defined(JLN_MP_DOXYGENATING)

#ifdef JLN_MP_DOXYGENATING
  template<class C, class... xs>
  using call = C::f<xs...>;
  #define JLN_MP_DCALL(cond, ...) call<__VA_ARGS__>
  #define JLN_MP_DCALL_V(cond, ...) call<__VA_ARGS__>::value
  #define JLN_MP_DCALLF(cond, F, ...) F<__VA_ARGS__>
  #define JLN_MP_DCALL_C(cond, F, ...) F<__VA_ARGS__>
  #define JLN_MP_DCALLF_C(cond, F, ...) F<__VA_ARGS__>
#else
  template<class C, class... xs>
  using call = memoize_call<C, xs...>;
  #define JLN_MP_DCALL(cond, ...) typename detail::_memoizer<__VA_ARGS__>::type
  #define JLN_MP_DCALL_V(cond, ...) detail::_memoizer<__VA_ARGS__>::type::value
  #define JLN_MP_DCALLF(cond, ...) typename detail::dcallf<(cond)>::template f<__VA_ARGS__>
  #define JLN_MP_DCALL_C(cond, ...) typename detail::dcall_c<(cond)>::template f<__VA_ARGS__>
  #define JLN_MP_DCALLF_C(cond, ...) typename detail::dcallf_c<(cond)>::template f<__VA_ARGS__>
#endif

#if __cplusplus >= 201703L
  template<class C, auto... xs>
#else
  template<class C, int_... xs>
#endif
  using call_c = typename C::template f<xs...>;

  template<class C, class F, class... xs>
  using dispatch = call<C, call<F, xs>...>;

  template<class FC, class F, class... xs>
  using indirect_call = call<call<FC, xs...>, F, xs...>;

  template<class C, class F, class... xs>
  using unary_compose_call = call<C, call<F, xs...>>;

  template<class C, class F0, class F1, class... xs>
  using binary_compose_call = call<C, call<F0, xs...>, call<F1, xs...>>;

  template<class C, class F0, class F1, class F2, class... xs>
  using ternary_compose_call = call<C, call<F0, xs...>, call<F1, xs...>, call<F2, xs...>>;

#else
  /// \cond
  namespace detail
  {
    template<template<class...> class f, class FC, class F, class... xs>
    using _indirect_call = f<f<FC, xs...>, F, xs...>;

    template<template<class...> class f, class C, class F, class... xs>
    using _dispatch = f<C, f<F, xs>...>;

    template<template<class...> class f, class C, class F, class... xs>
    using _unary_compose_call = f<C, f<F, xs...>>;

    template<template<class...> class f, class C, class F0, class F1, class... xs>
    using _binary_compose_call = f<C, f<F0, xs...>, f<F1, xs...>>;

    template<template<class...> class f, class C, class F0, class F1, class F2, class... xs>
    using _ternary_compose_call = f<C, f<F0, xs...>, f<F1, xs...>, f<F2, xs...>>;
  }
  /// \endcond

# define JLN_MP_DCALL(cond, ...) typename detail::dcall<(cond)>::template f<__VA_ARGS__>
# define JLN_MP_DCALL_V(cond, ...) detail::dcall<(cond)>::template f<__VA_ARGS__>::value
# define JLN_MP_DCALLF(cond, ...) typename detail::dcallf<(cond)>::template f<__VA_ARGS__>
# define JLN_MP_DCALL_C(cond, ...) typename detail::dcall_c<(cond)>::template f<__VA_ARGS__>
# define JLN_MP_DCALLF_C(cond, ...) typename detail::dcallf_c<(cond)>::template f<__VA_ARGS__>

  template<class C, class... xs>
  using call = typename conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
    ::template f<C, to_many_argument_error>
    ::template f<xs...>;

#if __cplusplus >= 201703L
  template<class C, auto... xs>
#else
  template<class C, int_... xs>
#endif
  using call_c = typename detail::dcall_c<(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT)>
    ::template f<C, xs...>;

  template<class FC, class F, class... xs>
  using indirect_call = detail::_indirect_call<
    detail::dcall<(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT)>::template f,
    FC, F, xs...>;

  template<class C, class F, class... xs>
  using dispatch = detail::_dispatch<
    detail::dcall<(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT)>::template f,
    C, F, xs...>;

  template<class C, class F, class... xs>
  using unary_compose_call = detail::_unary_compose_call<
    detail::dcall<(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT)>::template f,
    C, F, xs...>;

  template<class C, class F0, class F1, class... xs>
  using binary_compose_call = detail::_binary_compose_call<
    detail::dcall<(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT)>::template f,
    C, F0, F1, xs...>;

  template<class C, class F0, class F1, class F2, class... xs>
  using ternary_compose_call = detail::_ternary_compose_call<
    detail::dcall<(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT)>::template f,
    C, F0, F1, F2, xs...>;
#endif

  template<class C, class... xs>
  using call_t = typename call<C, xs...>::type;

  template<class FC, class F, class... xs>
  using indirect_call_t = typename indirect_call<FC, F, xs...>::type;

  template<class C, class F, class... xs>
  using dispatch_t = typename dispatch<C, F, xs...>::type;

  template<class C, class F, class... xs>
  using unary_compose_call_t = typename unary_compose_call<C, F, xs...>::type;

  template<class C, class F0, class F1, class... xs>
  using binary_compose_call_t = typename binary_compose_call<C, F0, F1, xs...>::type;

  template<class C, class F0, class F1, class F2, class... xs>
  using ternary_compose_call_t = typename ternary_compose_call<C, F0, F1, F2, xs...>::type;
}

/// \cond
namespace jln::mp::detail
{
  template<>
  struct dcall<true>
  {
      template<class C, class... xs>
      using f = typename C::template f<xs...>;
  };

  template<>
  struct dcall_c<true>
  {
#if __cplusplus >= 201703L
      template<class C, auto...xs>
#else
      template<class C, int_...xs>
#endif
      using f = typename C::template f<xs...>;
  };

  template<>
  struct dcallf<true>
  {
    template<template<class...> class F, class... xs>
    using f = F<xs...>;
  };

  template<>
  struct dcallf_c<true>
  {
#if __cplusplus >= 201703L
      template<template<auto...> class F, auto...xs>
#else
      template<template<int_...> class F, int_...xs>
#endif
      using f = F<xs...>;
  };

  // useful to work around msvc bugs
  template<class F, class... xs>
  using raw_call = typename F::template f<xs...>;
}
/// \endcond
