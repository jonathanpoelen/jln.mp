// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/join.hpp>
#include <jln/mp/list/wrap_in_list.hpp>
#include <jln/mp/number/number.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
#if JLN_MP_HAS_MEMOIZED_TYPE_PACK_ELEMENT
    template<class C, class>
    struct compress_impl;

    template<int>
    struct compress_indices;

    constexpr int compress_indices_select(std::size_t n);
#else
    template<template<class...> class C, class... Selectors>
    struct compress_impl;
#endif

    template<class L, class C>
    struct make_compress;
  }
  /// \endcond

  /// \ingroup filter

  /// Removes elements that have a corresponding element in \c selectors to 0.
  /// \pre `sizeof...(xs) == emp::size<Selectors>`
  /// \semantics
  ///   \code
  ///   compress_c<1,0,1,0,1,1>
  ///          ::f<a,b,c,d,e,f>
  ///      == list<a,  c,  e,f>
  ///   \endcode
  /// \treturn \sequence
  /// \see uncompress
  template<class C, bool... selectors>
  struct compress_c_with
#if JLN_MP_HAS_MEMOIZED_TYPE_PACK_ELEMENT
    : detail::compress_impl<
      C,
      typename detail::compress_indices<
        detail::compress_indices_select(sizeof...(selectors))
      >::template f<selectors...>::type
    >
#else
    : detail::compress_impl<C::template f, wrap_in_list_c<selectors>...>
#endif
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  template<bool... selectors>
  using compress_c = compress_c_with<listify, selectors...>;

  template<class... Selectors>
  using compress_for = compress_c_with<listify, Selectors::value...>;

  template<class Selectors, class C = listify>
  using compress = typename detail::make_compress<Selectors, C>::type;

  namespace emp
  {
    template<class L, class Selectors, class C = mp::listify>
    using compress = typename detail::_unpack<typename detail::make_compress<Selectors, C>::type, L>::type;

    template<class L, class... Selectors>
    using compress_for = typename detail::_unpack<mp::compress_c_with<listify, Selectors::value...>, L>::type;

    template<class L, bool... selectors>
    using compress_c = typename detail::_unpack<mp::compress_c_with<listify, selectors...>, L>::type;

    template<class L, class C, bool... selectors>
    using compress_c_with = typename detail::_unpack<mp::compress_c_with<C, selectors...>, L>::type;
  }
}

#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/detail/sequence.hpp>

/// \cond
#if JLN_MP_HAS_MEMOIZED_TYPE_PACK_ELEMENT
namespace jln::mp::detail
{
  template<int_t, class, class>
  struct concat_indices;

  template<int_t i, int_t... a, int_t... b>
  struct concat_indices<i, int_seq_c<a...>, int_seq_c<b...>>
  {
    using type = int_seq_c<a..., i+b...>;
  };


  template<>
  struct compress_indices<4>
  {
    template<bool b0 = 0, bool b1 = 0, bool b2 = 0, bool b3 = 0> struct f;
  };

  template<> struct compress_indices<4>::f<0,0,0,0> { using type = int_seq_c<>; };
  template<> struct compress_indices<4>::f<0,0,0,1> { using type = int_seq_c<3>; };
  template<> struct compress_indices<4>::f<0,0,1,0> { using type = int_seq_c<2>; };
  template<> struct compress_indices<4>::f<0,0,1,1> { using type = int_seq_c<2,3>; };
  template<> struct compress_indices<4>::f<0,1,0,0> { using type = int_seq_c<1>; };
  template<> struct compress_indices<4>::f<0,1,0,1> { using type = int_seq_c<1,3>; };
  template<> struct compress_indices<4>::f<0,1,1,0> { using type = int_seq_c<1,2>; };
  template<> struct compress_indices<4>::f<0,1,1,1> { using type = int_seq_c<1,2,3>; };
  template<> struct compress_indices<4>::f<1,0,0,0> { using type = int_seq_c<0>; };
  template<> struct compress_indices<4>::f<1,0,0,1> { using type = int_seq_c<0,3>; };
  template<> struct compress_indices<4>::f<1,0,1,0> { using type = int_seq_c<0,2>; };
  template<> struct compress_indices<4>::f<1,0,1,1> { using type = int_seq_c<0,2,3>; };
  template<> struct compress_indices<4>::f<1,1,0,0> { using type = int_seq_c<0,1>; };
  template<> struct compress_indices<4>::f<1,1,0,1> { using type = int_seq_c<0,1,3>; };
  template<> struct compress_indices<4>::f<1,1,1,0> { using type = int_seq_c<0,1,2>; };
  template<> struct compress_indices<4>::f<1,1,1,1> { using type = int_seq_c<0,1,2,3>; };

#define MP_MK_COMPRESS_INDICES(n, mp1, mp2)                                     \
  template<>                                                                    \
  struct compress_indices<n*2>                                                  \
  {                                                                             \
    template<mp1(bool, JLN_MP_NIL, JLN_MP_COMMA), mp2(bool, = 0, JLN_MP_COMMA)> \
    using f = concat_indices<                                                   \
      n,                                                                        \
      typename compress_indices<n>                                              \
        ::f<mp1(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>::type,                   \
      typename compress_indices<n>                                              \
        ::f<mp2(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>::type                    \
    >;                                                                          \
  };

  MP_MK_COMPRESS_INDICES(4, JLN_MP_XS_4, JLN_MP_XS_4_FROM_5)
  MP_MK_COMPRESS_INDICES(8, JLN_MP_XS_8, JLN_MP_XS_8_FROM_9)
  MP_MK_COMPRESS_INDICES(16, JLN_MP_XS_16, JLN_MP_XS_16_FROM_17)
  MP_MK_COMPRESS_INDICES(32, JLN_MP_XS_32, JLN_MP_XS_32_FROM_33)
  MP_MK_COMPRESS_INDICES(64, JLN_MP_XS_64, JLN_MP_XS_64_FROM_65)

#undef MP_MK_COMPRESS_INDICES

  constexpr int compress_indices_select(std::size_t n)
  {
    return n > 128 ? 256
         : n > 64 ? 128
         : n > 32 ? 64
         : n > 16 ? 32
         : n > 8 ? 16
         : n > 4 ? 8
         : 4;
  }

  template<int>
  struct compress_indices
  {
    template<JLN_MP_XS_128(bool, JLN_MP_NIL, JLN_MP_COMMA), bool... b>
    using f = concat_indices<
      128,
      typename compress_indices<128>
        ::f<JLN_MP_XS_128(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>::type,
      typename compress_indices<compress_indices_select(sizeof...(b))>
        ::template f<b...>::type
    >;
  };

  template<class C, class>
  struct compress_impl;

  template<class C, int_t... ints>
  struct compress_impl<C, int_seq_c<ints...>>
  {
     template<class... xs>
     using f = JLN_MP_DCALL_TRACE_XS(xs, C, __type_pack_element<ints, xs...>...);
  };
}
#else
namespace jln::mp
{
  template<bool... selectors>
  struct compress_c_with<listify, selectors...>
    : detail::compress_impl<list, wrap_in_list_c<selectors>...>
  {};
}

namespace jln::mp::detail
{
  template<template<class...> class C, class... Selectors>
  struct compress_impl
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(Selectors)>
      ::template f<C, typename Selectors::template f<xs>...>
      ::type
      ;
  };
}
#endif

namespace jln::mp::detail
{
  template<template<class...> class Tpl, class... selectors, class C>
  struct make_compress<Tpl<selectors...>, C>
  {
    using type = compress_c_with<C, selectors::value...>;
  };

  template<template<class T, T...> class Tpl, class T, T... selectors, class C>
  struct make_compress<Tpl<T, selectors...>, C>
  {
    using type = compress_c_with<C, selectors...>;
  };

  template<template<int_t...> class Tpl, int_t... selectors, class C>
  struct make_compress<Tpl<selectors...>, C>
  {
    using type = compress_c_with<C, selectors...>;
  };

  template<template<bool...> class Tpl, bool... selectors, class C>
  struct make_compress<Tpl<selectors...>, C>
  {
    using type = compress_c_with<C, selectors...>;
  };

#if JLN_MP_ENABLE_TPL_PARAM_AUTO
  template<template<auto...> class Tpl, auto... selectors, class C>
  struct make_compress<Tpl<selectors...>, C>
  {
    using type = compress_c_with<C, selectors...>;
  };
#endif
}
/// \endcond
