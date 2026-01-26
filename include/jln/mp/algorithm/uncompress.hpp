// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/join.hpp>
#include <jln/mp/list/wrap_in_list.hpp>
#include <jln/mp/algorithm/make_int_sequence.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, class FillT, class L>
    struct uncompress_impl;

    template<class FillT, class Selectors, class C>
    struct make_uncompress;

    template<bool...>
    struct uncompress_indices;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Create sequence by replacing false in \c selectors with \c FillT
  /// and true with a element in xs value, starting from the left.
  /// \semantics
  ///   \code
  ///   uncompress_c<T, 1,0,1,0,1,1>
  ///            ::f<   a,  c,  e,f>
  ///        == list<   a,T,c,T,e,f>
  ///   \endcode
  /// \treturn \sequence
  /// \see compress
  template<class C, class FillT, bool... selectors>
  struct uncompress_c_with
  : detail::uncompress_impl<
      C,
      FillT,
      typename detail::uncompress_indices<selectors...>::type
    >
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  template<class FillT, bool... selectors>
  using uncompress_c = uncompress_c_with<listify, FillT, selectors...>;

  template<class FillT, class... Selectors>
  using uncompress_for = uncompress_c_with<listify, FillT, Selectors::value...>;

  template<class FillT, class Selectors, class C = listify>
  using uncompress = typename detail::make_uncompress<FillT, Selectors, C>::type;

  namespace emp
  {
    template<class L, class FillT, class Selectors, class C = mp::listify>
    using uncompress = typename detail::_unpack<typename detail::make_uncompress<FillT, Selectors, C>::type, L>::type;

    template<class L, class FillT, class... Selectors>
    using uncompress_for = typename detail::_unpack<mp::uncompress_c_with<listify, FillT, Selectors::value...>, L>::type;

    template<class L, class FillT, bool... selectors>
    using uncompress_c = typename detail::_unpack<mp::uncompress_c_with<listify, FillT, selectors...>, L>::type;

    template<class L, class FillT, class C, bool... selectors>
    using uncompress_c_with = typename detail::_unpack<mp::uncompress_c_with<C, FillT, selectors...>, L>::type;
  }
}


#include <jln/mp/utility/enable_if.hpp>
#include <jln/mp/detail/sequence.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class FillT, template<class...> class Tpl, class... selectors, class C>
  struct make_uncompress<FillT, Tpl<selectors...>, C>
  {
    using type = uncompress_c_with<C, FillT, selectors::value...>;
  };

  template<class FillT, template<class T, T...> class Tpl, class T, T... selectors, class C>
  struct make_uncompress<FillT, Tpl<T, selectors...>, C>
  {
    using type = uncompress_c_with<C, FillT, selectors...>;
  };

  template<class FillT, template<int_t...> class Tpl, int_t... selectors, class C>
  struct make_uncompress<FillT, Tpl<selectors...>, C>
  {
    using type = uncompress_c_with<C, FillT, selectors...>;
  };

  template<class FillT, template<bool...> class Tpl, bool... selectors, class C>
  struct make_uncompress<FillT, Tpl<selectors...>, C>
  {
    using type = uncompress_c_with<C, FillT, selectors...>;
  };

#if JLN_MP_ENABLE_TPL_PARAM_AUTO
  template<template<auto...> class Tpl, class FillT, auto... selectors, class C>
  struct make_uncompress<FillT, Tpl<selectors...>, C>
  {
    using type = uncompress_c_with<C, FillT, selectors...>;
  };
#endif


  template<class, class>
  struct concat_uncompressed_indices;

  template<int_t i1, int_t... a, int_t i2, int_t... b>
  struct concat_uncompressed_indices<int_seq_c<i1, a...>, int_seq_c<i2, b...>>
  {
    using type = int_seq_c<i1+i2, a..., b == 0 ? 0 : i1+b...>;
  };


  template<> struct uncompress_indices<> { using type = int_seq_c<0>; };

  template<> struct uncompress_indices<0> { using type = int_seq_c<0,0>; };
  template<> struct uncompress_indices<1> { using type = int_seq_c<1,1>; };

  template<> struct uncompress_indices<0,0> { using type = int_seq_c<0,0,0>; };
  template<> struct uncompress_indices<0,1> { using type = int_seq_c<1,0,1>; };
  template<> struct uncompress_indices<1,0> { using type = int_seq_c<1,1,0>; };
  template<> struct uncompress_indices<1,1> { using type = int_seq_c<2,1,2>; };

  template<> struct uncompress_indices<0,0,0> { using type = int_seq_c<0,0,0,0>; };
  template<> struct uncompress_indices<0,0,1> { using type = int_seq_c<1,0,0,1>; };
  template<> struct uncompress_indices<0,1,0> { using type = int_seq_c<1,0,1,0>; };
  template<> struct uncompress_indices<0,1,1> { using type = int_seq_c<2,0,1,2>; };
  template<> struct uncompress_indices<1,0,0> { using type = int_seq_c<1,1,0,0>; };
  template<> struct uncompress_indices<1,0,1> { using type = int_seq_c<2,1,0,2>; };
  template<> struct uncompress_indices<1,1,0> { using type = int_seq_c<2,1,2,0>; };
  template<> struct uncompress_indices<1,1,1> { using type = int_seq_c<3,1,2,3>; };

  template<> struct uncompress_indices<0,0,0,0> { using type = int_seq_c<0,0,0,0,0>; };
  template<> struct uncompress_indices<0,0,0,1> { using type = int_seq_c<1,0,0,0,1>; };
  template<> struct uncompress_indices<0,0,1,0> { using type = int_seq_c<1,0,0,1,0>; };
  template<> struct uncompress_indices<0,0,1,1> { using type = int_seq_c<2,0,0,1,2>; };
  template<> struct uncompress_indices<0,1,0,0> { using type = int_seq_c<1,0,1,0,0>; };
  template<> struct uncompress_indices<0,1,0,1> { using type = int_seq_c<2,0,1,0,2>; };
  template<> struct uncompress_indices<0,1,1,0> { using type = int_seq_c<2,0,1,2,0>; };
  template<> struct uncompress_indices<0,1,1,1> { using type = int_seq_c<3,0,1,2,3>; };
  template<> struct uncompress_indices<1,0,0,0> { using type = int_seq_c<1,1,0,0,0>; };
  template<> struct uncompress_indices<1,0,0,1> { using type = int_seq_c<2,1,0,0,2>; };
  template<> struct uncompress_indices<1,0,1,0> { using type = int_seq_c<2,1,0,2,0>; };
  template<> struct uncompress_indices<1,0,1,1> { using type = int_seq_c<3,1,0,2,3>; };
  template<> struct uncompress_indices<1,1,0,0> { using type = int_seq_c<2,1,2,0,0>; };
  template<> struct uncompress_indices<1,1,0,1> { using type = int_seq_c<3,1,2,0,3>; };
  template<> struct uncompress_indices<1,1,1,0> { using type = int_seq_c<3,1,2,3,0>; };
  template<> struct uncompress_indices<1,1,1,1> { using type = int_seq_c<4,1,2,3,4>; };

#define MP_MK_UNCOMPRESS_INDICES(seq)                                               \
  template<seq(bool, JLN_MP_NIL, JLN_MP_COMMA), bool b, bool... bs>                 \
  struct uncompress_indices<seq(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), b, bs...>    \
  : concat_uncompressed_indices<                                                    \
      typename uncompress_indices<seq(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>::type, \
      typename uncompress_indices<b, bs...>::type                                   \
    >                                                                               \
  {};

  MP_MK_UNCOMPRESS_INDICES(JLN_MP_XS_4)
  MP_MK_UNCOMPRESS_INDICES(JLN_MP_XS_8)
  MP_MK_UNCOMPRESS_INDICES(JLN_MP_XS_16)
  MP_MK_UNCOMPRESS_INDICES(JLN_MP_XS_32)
  MP_MK_UNCOMPRESS_INDICES(JLN_MP_XS_64)
  MP_MK_UNCOMPRESS_INDICES(JLN_MP_XS_128)

#undef MP_MK_UNCOMPRESS_INDICES


  template<class C, class FillT, int_t d, int_t... i>
  struct uncompress_impl<C, FillT, int_seq_c<d, i...>>
  {
  private:
    template<class Lookup>
    using impl = typename enable_if_t<0 <= sizeof(Lookup), JLN_MP_TRACE_F(C)>
      ::template f<typename Lookup::template f<i>...>;

  public:
    template<class... xs>
    using f = impl<build_indexed_v<FillT, xs...>>;
  };
}
/// \endcond
