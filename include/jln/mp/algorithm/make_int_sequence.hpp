// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/numbers.hpp>
#include <jln/mp/detail/compiler.hpp>

#ifdef JLN_MP_DISABLE_INTEGER_SEQUENCE_OPTIMIZATION
#  define JLN_MP_USE_INTEGER_PACK 0
#  define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#elif JLN_MP_HAS_BUILTIN(__make_integer_seq) || defined(_MSC_VER)
#  define JLN_MP_USE_INTEGER_PACK 0
#  define JLN_MP_USE_MAKE_INTEGER_SEQ 1
#elif JLN_MP_HAS_BUILTIN(__integer_pack) || JLN_MP_GCC >= 800
#  define JLN_MP_USE_INTEGER_PACK 1
#  define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#else
#  define JLN_MP_USE_INTEGER_PACK 0
#  define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#endif

#if JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
#  include <cstddef>
#elif defined(JLN_MP_FALLBACK_TO_STD_SEQUENCE)
#  include <utility>
#endif


namespace jln::mp
{
  /// \cond
  namespace detail
  {
#if JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
    template<class>
    struct make_int_sequence_impl;
#elif ! defined(JLN_MP_FALLBACK_TO_STD_SEQUENCE)
    template<unsigned n>
    struct mk_int_seq;

    template<class C, class Ints>
    struct make_int_sequence_impl;

    template<template<class T, T...> class C, class Int, class Ints>
    struct make_int_pack_impl;

    template<template<class T, T...> class C, class Int, unsigned n>
    using make_int_pack_t = typename make_int_pack_impl<C, Int, typename mk_int_seq<n>::type>::type;
#else
    template<class C, class Ints>
    struct make_int_sequence_impl;

    template<template<class T, T...> class C, class Ints>
    struct make_int_pack_impl;

    template<template<class T, T...> class C, class Int, Int n>
    using make_int_pack_t = typename make_int_pack_impl<C, std::make_integer_sequence<Int, n>>::type;
#endif
  }
  /// \endcond

  /// \ingroup number

  /// Generates an incremental sequence of \c n \c int_t.
  /// \treturn \sequence
  /// \see make_int_sequence, iota
  template<class C = numbers<>>
  struct make_int_sequence_v
  {
    template<class n>
#if JLN_MP_USE_MAKE_INTEGER_SEQ
    using f = typename __make_integer_seq<detail::make_int_sequence_impl<C>
      ::template f, int_t, n::value>::type;
#elif JLN_MP_USE_INTEGER_PACK
    using f = typename detail::make_int_sequence_impl<C>
      ::template f<int_t, __integer_pack(n::value)...>::type;
#elif ! defined(JLN_MP_FALLBACK_TO_STD_SEQUENCE)
    using f = typename detail::make_int_sequence_impl<
      C, typename detail::mk_int_seq<n::value>::type>::type;
#else
    using f = typename detail::make_int_sequence_impl<
      C, std::make_integer_sequence<int_t, n::value>>::type;
#endif
  };

  template<class C = mp::listify>
  using make_int_sequence = make_int_sequence_v<mp::numbers<C>>;

  namespace emp
  {
#if JLN_MP_USE_INTEGER_PACK
    template<unsigned n, class C = mp::numbers<>>
    using make_int_sequence_v_c = typename detail::make_int_sequence_impl<C>
      ::template f<int_t, __integer_pack(n)...>::type;

    template<unsigned n, class C = mp::listify>
    using make_int_sequence_c = typename detail::make_int_sequence_impl<mp::numbers<C>>
      ::template f<int_t, __integer_pack(n)...>::type;

    template<class n, class C = mp::numbers<>>
    using make_int_sequence_v = typename detail::make_int_sequence_impl<C>
      ::template f<int_t, __integer_pack(n::value)...>::type;

    template<class n, class C = mp::listify>
    using make_int_sequence = typename detail::make_int_sequence_impl<mp::numbers<C>>
      ::template f<int_t, __integer_pack(n::value)...>::type;
#elif JLN_MP_USE_MAKE_INTEGER_SEQ
    template<unsigned n, class C = mp::numbers<>>
    using make_int_sequence_v_c = typename __make_integer_seq<
      detail::make_int_sequence_impl<C>::template f, int_t, n>::type;

    template<unsigned n, class C = mp::listify>
    using make_int_sequence_c = typename __make_integer_seq<
      detail::make_int_sequence_impl<mp::numbers<C>>::template f, int_t, n>::type;

    template<class n, class C = mp::numbers<>>
    using make_int_sequence_v = typename __make_integer_seq<
      detail::make_int_sequence_impl<C>::template f, int_t, n::value>::type;

    template<class n, class C = mp::listify>
    using make_int_sequence = typename __make_integer_seq<
      detail::make_int_sequence_impl<mp::numbers<C>>::template f, int_t, n::value>::type;
#else
# if ! defined(JLN_MP_FALLBACK_TO_STD_SEQUENCE)
#   define JLN_MK_INT_SEQ(n) typename detail::mk_int_seq<n>::type
# else
#   define JLN_MK_INT_SEQ(n) std::make_integer_sequence<int_t, n>
# endif

    template<unsigned n, class C = mp::numbers<>>
    using make_int_sequence_v_c = typename detail::make_int_sequence_impl<
      C, JLN_MK_INT_SEQ(n)>::type;

    template<unsigned n, class C = mp::listify>
    using make_int_sequence_c = typename detail::make_int_sequence_impl<
      mp::numbers<C>, JLN_MK_INT_SEQ(n)>::type;

    template<class n, class C = mp::numbers<>>
    using make_int_sequence_v = typename detail::make_int_sequence_impl<
      C, JLN_MK_INT_SEQ(n::value)>::type;

    template<class n, class C = mp::listify>
    using make_int_sequence = typename detail::make_int_sequence_impl<
      mp::numbers<C>, JLN_MK_INT_SEQ(n::value)>::type;

# undef JLN_MK_INT_SEQ
#endif
  }

  /// Fast initialization of template of the shape `tpl_class<class T, T... ints>`.
  /// \pre `n` should be a template parameter.
  /// \code
  /// template<class, int...>
  /// struct ints { ... };
  ///
  /// template<class n>
  /// using make_ints = JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, n::value, ints);
  /// \endcode
  #if JLN_MP_USE_MAKE_INTEGER_SEQ
  #  define JLN_MP_MAKE_INTEGER_SEQUENCE_T(T, n, /*tpl_class*/...) \
    __make_integer_seq<__VA_ARGS__, T, n>
  #  define JLN_MP_MAKE_INTEGER_SEQUENCE_TYPENAME
  #elif JLN_MP_USE_INTEGER_PACK
  #  define JLN_MP_MAKE_INTEGER_SEQUENCE_T(T, n, /*tpl_class*/...) \
    __VA_ARGS__<T, __integer_pack(n)...>
  #  define JLN_MP_MAKE_INTEGER_SEQUENCE_TYPENAME typename
  #else
  #  define JLN_MP_MAKE_INTEGER_SEQUENCE_T(T, n, /*tpl_class*/...) \
      ::jln::mp::detail::make_int_pack_t<__VA_ARGS__, T, n>
  #  define JLN_MP_MAKE_INTEGER_SEQUENCE_TYPENAME typename
  #endif

  /// Fast initialization of template of the shape `tpl_class<class T, std::size_t... ints>`.
  /// \pre `n` should be a template parameter.
  #define JLN_MP_MAKE_INDEX_SEQUENCE(n, /*tpl_class*/...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_T(std::size_t, n, __VA_ARGS__)

  /// Fast initialization of template of the shape `tpl_class<class T, int_t... ints>`.
  /// \pre `n` should be a template parameter.
  #define JLN_MP_MAKE_INTEGER_SEQUENCE(n, /*tpl_class*/...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_T(::jln::mp::int_t, n, __VA_ARGS__)

  /// Fast initialization of template of the shape `tpl_class<class T, unsigned... ints>`.
  /// \pre `n` should be a template parameter.
  #define JLN_MP_MAKE_UNSIGNED_SEQUENCE(n, /*tpl_class*/...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_T(unsigned, n, __VA_ARGS__)

  /// Template-dependent version of \c JLN_MP_MAKE_INTEGER_SEQUENCE_T ; add typename when needed.


  /// \code
  /// // typename impl<...>::template f<T, 0, 1, 2> ->
  /// JLN_MP_D_MAKE_INTEGER_SEQUENCE_T(T, n, impl<...>::template f)
  /// \endcode
  #define JLN_MP_D_MAKE_INTEGER_SEQUENCE_T(T, n, /*tpl_class*/...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_TYPENAME JLN_MP_MAKE_INTEGER_SEQUENCE_T(T, n, __VA_ARGS__)

  /// Template-dependent version of \c JLN_MP_MAKE_INDEX_SEQUENCE ; add typename when needed.
  /// \code
  /// // typename impl<...>::template f<T, 0, 1, 2> ->
  /// JLN_MP_MAKE_INDEX_SEQUENCE(n, impl<...>::template f)
  /// \endcode
  #define JLN_MP_D_MAKE_INDEX_SEQUENCE(n, /*tpl_class*/...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_TYPENAME JLN_MP_MAKE_INDEX_SEQUENCE(n, __VA_ARGS__)

  /// Template-dependent version of \c JLN_MP_MAKE_INTEGER_SEQUENCE ; add typename when needed.
  /// \code
  /// // typename impl<...>::template f<T, 0, 1, 2> ->
  /// JLN_MP_D_MAKE_INTEGER_SEQUENCE(n, impl<...>::template f)
  /// \endcode
  #define JLN_MP_D_MAKE_INTEGER_SEQUENCE(n, /*tpl_class*/...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_TYPENAME JLN_MP_MAKE_INTEGER_SEQUENCE(n, __VA_ARGS__)

  /// Template-dependent version of \c JLN_MP_MAKE_UNSIGNED_SEQUENCE ; add typename when needed.
  /// \code
  /// // typename impl<...>::template f<T, 0, 1, 2> ->
  /// JLN_MP_D_MAKE_UNSIGNED_SEQUENCE(n, impl<...>::template f)
  /// \endcode
  #define JLN_MP_D_MAKE_UNSIGNED_SEQUENCE(n, /*tpl_class*/...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_TYPENAME JLN_MP_MAKE_UNSIGNED_SEQUENCE(n, __VA_ARGS__)

  /// single list of \c int_t.
  template<int_t... i>
  struct int_seq_c {};
} // namespace jln::mp


/// \cond
#if JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
namespace jln::mp::detail
{
  template<class C>
  struct make_int_sequence_impl
  {
    template<class, int_t... ns>
    struct f
    {
      using type = typename C::template f<ns...>;
    };
  };

  template<>
  struct make_int_sequence_impl<numbers<>>
  {
    template<class, int_t... ns>
    struct f
    {
      using type = list<number<ns>...>;
    };
  };

  template<class C>
  struct make_int_sequence_impl<numbers<C>>
  {
    template<class, int_t... ns>
    struct f
    {
      using type = typename C::template f<number<ns>...>;
    };
  };

  template<template<class...> class F>
  struct make_int_sequence_impl<numbers<cfe<F>>>
  {
    template<class, int_t... ns>
    struct f
    {
      using type = F<number<ns>...>;
    };
  };

  template<template<class...> class F, class C>
  struct make_int_sequence_impl<numbers<cfe<F, C>>>
  {
    template<class, int_t... ns>
    struct f
    {
      using type = typename C::template f<F<number<ns>...>>;
    };
  };

  template<template<class...> class F>
  struct make_int_sequence_impl<numbers<cfl<F>>>
  {
    template<class, int_t... ns>
    struct f
    {
      using type = typename F<number<ns>...>::type;
    };
  };

  template<template<class...> class F, class C>
  struct make_int_sequence_impl<numbers<cfl<F, C>>>
  {
    template<class, int_t... ns>
    struct f
    {
      using type = typename C::template f<F<number<ns>...>>::type;
    };
  };

  template<template<JLN_MP_TPL_PARAM_AUTO_OR_INT...> class F>
  struct make_int_sequence_impl<cfe_v_c<F>>
  {
    template<class, int_t... ns>
    struct f
    {
      using type = F<ns...>;
    };
  };

  template<template<JLN_MP_TPL_PARAM_AUTO_OR_INT...> class F, class C>
  struct make_int_sequence_impl<cfe_v_c<F, C>>
  {
    template<class, int_t... ns>
    struct f
    {
      using type = typename C::template f<F<ns...>>;
    };
  };

  template<template<JLN_MP_TPL_PARAM_AUTO_OR_INT...> class F>
  struct make_int_sequence_impl<cfl_v_c<F>>
  {
    template<class, int_t... ns>
    struct f
    {
      using type = typename F<ns...>::type;
    };
  };

  template<template<JLN_MP_TPL_PARAM_AUTO_OR_INT...> class F, class C>
  struct make_int_sequence_impl<cfl_v_c<F, C>>
  {
    template<class, int_t... ns>
    struct f
    {
      using type = typename C::template f<F<ns...>>::type;
    };
  };

  template<template<JLN_MP_TPL_PARAM_AUTO_OR_INT...> class F>
  struct make_int_sequence_impl<numbers<cfe_v<F>>> : make_int_sequence_impl<cfe_v_c<F>>
  {};

  template<template<JLN_MP_TPL_PARAM_AUTO_OR_INT...> class F, class C>
  struct make_int_sequence_impl<numbers<cfe_v<F, C>>> : make_int_sequence_impl<cfe_v_c<F, C>>
  {};

  template<template<JLN_MP_TPL_PARAM_AUTO_OR_INT...> class F>
  struct make_int_sequence_impl<numbers<cfl_v<F>>> : make_int_sequence_impl<cfl_v_c<F>>
  {};

  template<template<JLN_MP_TPL_PARAM_AUTO_OR_INT...> class F, class C>
  struct make_int_sequence_impl<numbers<cfl_v<F, C>>> : make_int_sequence_impl<cfl_v_c<F, C>>
  {};
}
#elif ! defined(JLN_MP_FALLBACK_TO_STD_SEQUENCE)
namespace jln::mp::detail
{
  template<bool, int_t n, class ns>
  struct int_seq_expand;

  template<int_t n, int_t... ns>
  struct int_seq_expand<false, n, int_seq_c<ns...>>
  {
    using type = int_seq_c<ns..., (n+ns)...>;
  };

  template<int_t n, int_t... ns>
  struct int_seq_expand<true, n, int_seq_c<ns...>>
  {
    using type = int_seq_c<ns..., (n+ns)..., n * 2>;
  };

  template<unsigned n>
  struct mk_int_seq
  : int_seq_expand<n & 1, n / 2, typename mk_int_seq<n / 2>::type>
  {};

  template<> struct mk_int_seq<0> { using type = int_seq_c<>; };
  template<> struct mk_int_seq<1> { using type = int_seq_c<0>; };

  template<int_t... ns>
  struct make_int_sequence_impl<numbers<>, int_seq_c<ns...>>
  {
    using type = list<number<ns>...>;
  };

  template<class C, int_t... ns>
  struct make_int_sequence_impl<C, int_seq_c<ns...>>
  {
    using type = typename C::template f<ns...>;
  };

  template<class C, int_t... ns>
  struct make_int_sequence_impl<numbers<C>, int_seq_c<ns...>>
  {
    using type = typename C::template f<number<ns>...>;
  };

  template<template<class T, T...> class C, class Int, int_t... ns>
  struct make_int_pack_impl<C, Int, int_seq_c<ns...>>
  {
    using type = C<Int, ns...>;
  };
}
#else
namespace jln::mp::detail
{
  template<class C, int_t... ns>
  struct make_int_sequence_impl<C, std::integer_sequence<int_t, ns...>>
  {
    using type = typename C::template f<ns...>;
  };

  template<class C, int_t... ns>
  struct make_int_sequence_impl<numbers<C>, std::integer_sequence<int_t, ns...>>
  {
    using type = typename C::template f<number<ns>...>;
  };

  template<template<class T, T...> class C, class Int, Int... ns>
  struct make_int_pack_impl<C, std::integer_sequence<Int, ns...>>
  {
    using type = C<Int, ns...>;
  };
}
#endif
/// \endcond
