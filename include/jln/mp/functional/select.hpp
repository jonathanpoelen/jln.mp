// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/front.hpp>
#include <jln/mp/list/at.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// A conditional selection expression.
  /// This is the equivalent of the ternary `Pred::f<a, b>::value ? a : b`.
  /// \pre `sizeof...(xs) >= 2`
  /// \treturn \value
  /// \see if_, reverse_select, select_flip, reverse_select_flip
  template<class Pred, class TC = identity, class FC = TC>
  struct select
  {
    template<class x, class y, class... xs>
    using f = typename conditional_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, y, xs...)::value)
    >
      ::template f<JLN_MP_TRACE_F(at1<FC>), JLN_MP_TRACE_F(front<TC>)>
      ::template f<x, y>;
  };

  /// A conditional selection expression.
  /// This is the equivalent of the ternary `Pred::f<a, b>::value ? b : a`.
  /// \pre `sizeof...(xs) >= 2`
  /// \treturn \value
  /// \see if_, select, select_flip, reverse_select_flip
  template<class Pred, class TC = identity, class FC = TC>
  struct reverse_select
  {
    template<class x, class y, class... xs>
    using f = typename conditional_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, y, xs...)::value)
    >
      ::template f<JLN_MP_TRACE_F(front<FC>), JLN_MP_TRACE_F(at1<TC>)>
      ::template f<x, y>;
  };

  /// A conditional selection expression with its two first arguments reversed.
  /// This is the equivalent of the ternary `Pred::f<b, a>::value ? a : b`.
  /// \pre `sizeof...(xs) >= 2`
  /// \treturn \value
  /// \see if_, select, reverse_select, reverse_select_flip
  template<class Pred, class TC = identity, class FC = TC>
  struct select_flip
  {
    template<class x, class y, class... xs>
    using f = typename conditional_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, y, x, xs...)::value)
    >
      ::template f<JLN_MP_TRACE_F(at1<FC>), JLN_MP_TRACE_F(front<TC>)>
      ::template f<x, y>;
  };

  /// A conditional selection expression with its two first arguments reversed.
  /// This is the equivalent of the ternary `Pred::f<b, a>::value ? b : a`.
  /// \pre `sizeof...(xs) >= 2`
  /// \treturn \value
  /// \see if_, select, reverse_select, select_flip
  template<class Pred, class TC = identity, class FC = TC>
  struct reverse_select_flip
  {
    template<class x, class y, class... xs>
    using f = typename conditional_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, y, x, xs...)::value)
    >
      ::template f<JLN_MP_TRACE_F(front<FC>), JLN_MP_TRACE_F(at1<TC>)>
      ::template f<x, y>;
  };

  namespace emp
  {
    template<class Pred, class a, class b>
    using select = typename mp::select<Pred>::template f<a, b>;

    template<class Pred, class a, class b>
    using reverse_select = typename mp::reverse_select<Pred>::template f<a, b>;

    template<class Pred, class a, class b>
    using select_flip = typename mp::select_flip<Pred>::template f<a, b>;

    template<class Pred, class a, class b>
    using reverse_select_flip = typename mp::reverse_select_flip<Pred>::template f<a, b>;

    template<class Pred, class a, class b>
    inline constexpr auto select_v = mp::select<Pred>::template f<a, b>::value;

    template<class Pred, class a, class b>
    inline constexpr auto reverse_select_v = mp::reverse_select<Pred>::template f<a, b>::value;

    template<class Pred, class a, class b>
    inline constexpr auto select_flip_v = mp::select_flip<Pred>::template f<a, b>::value;

    template<class Pred, class a, class b>
    inline constexpr auto reverse_select_flip_v = mp::reverse_select_flip<Pred>::template f<a, b>::value;
  }
}


/// \cond
namespace jln::mp
{
  template<class Pred, class C>
  struct select<Pred, C, C>
  {
    template<class x, class y, class... xs>
    using f = typename C::template f<
      typename conditional_c<
        JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, y, xs...)::value)
      >
        ::template f<y, x>
    >;
  };

  template<class Pred>
  struct select<Pred>
  {
    template<class x, class y, class... xs>
    using f = typename conditional_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, y, xs...)::value)
    >
      ::template f<y, x>;
  };


  template<class Pred, class C>
  struct reverse_select<Pred, C, C>
  {
    template<class x, class y, class... xs>
    using f = typename C::template f<
      typename conditional_c<
        JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, y, xs...)::value)
      >
        ::template f<x, y>
    >;
  };

  template<class Pred>
  struct reverse_select<Pred>
  {
    template<class x, class y, class... xs>
    using f = typename conditional_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, y, xs...)::value)
    >
      ::template f<x, y>;
  };


  template<class Pred, class C>
  struct select_flip<Pred, C, C>
  {
    template<class x, class y, class... xs>
    using f = typename C::template f<
      typename conditional_c<
        JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, y, x, xs...)::value)
      >
        ::template f<y, x>
    >;
  };

  template<class Pred>
  struct select_flip<Pred>
  {
    template<class x, class y, class... xs>
    using f = typename conditional_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, y, x, xs...)::value)
    >
      ::template f<y, x>;
  };


  template<class Pred, class C>
  struct reverse_select_flip<Pred, C, C>
  {
    template<class x, class y, class... xs>
    using f = typename C::template f<
      typename conditional_c<
        JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, y, x, xs...)::value)
      >
        ::template f<x, y>
    >;
  };

  template<class Pred>
  struct reverse_select_flip<Pred>
  {
    template<class x, class y, class... xs>
    using f = typename conditional_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, y, x, xs...)::value)
    >
      ::template f<x, y>;
  };
}
/// \endcond
