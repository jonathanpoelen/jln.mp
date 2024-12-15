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
      ::template f<at1<FC>, front<TC>>
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
      ::template f<front<FC>, at1<TC>>
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
      ::template f<at1<FC>, front<TC>>
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
      ::template f<front<FC>, at1<TC>>
      ::template f<x, y>;
  };

  namespace emp
  {
    template<class Pred, class x, class y>
    using select = JLN_MP_CONDITIONAL_C_T(
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_TRACE_F(Pred)::template f<x, y>::value),
      y, x
    );

    template<class Pred, class x, class y>
    using reverse_select = JLN_MP_CONDITIONAL_C_T(
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_TRACE_F(Pred)::template f<x, y>::value),
      x, y
    );

    template<class Pred, class x, class y>
    using select_flip = JLN_MP_CONDITIONAL_C_T(
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_TRACE_F(Pred)::template f<y, x>::value),
      y, x
    );

    template<class Pred, class x, class y>
    using reverse_select_flip = JLN_MP_CONDITIONAL_C_T(
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_TRACE_F(Pred)::template f<y, x>::value),
      x, y
    );

    template<class Pred, class x, class y>
    inline constexpr auto select_v = select<Pred, x, y>::value;

    template<class Pred, class x, class y>
    inline constexpr auto reverse_select_v = reverse_select<Pred, x, y>::value;

    template<class Pred, class x, class y>
    inline constexpr auto select_flip_v = select_flip<Pred, x, y>::value;

    template<class Pred, class x, class y>
    inline constexpr auto reverse_select_flip_v = reverse_select_flip<Pred, x, y>::value;
  }
}


/// \cond
namespace jln::mp
{
  template<class Pred, class C>
  struct select<Pred, C, C>
  {
    template<class x, class y, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      JLN_MP_CONDITIONAL_C_T(
        JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, y, xs...)::value),
        y, x
      )
    );
  };

  template<class Pred>
  struct select<Pred>
  {
    template<class x, class y, class... xs>
    using f = JLN_MP_CONDITIONAL_C_T(
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, y, xs...)::value),
      y, x
    );
  };


  template<class Pred, class C>
  struct reverse_select<Pred, C, C>
  {
    template<class x, class y, class... xs>
    using f = typename C::template f<
      JLN_MP_CONDITIONAL_C_T(
        JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, y, xs...)::value),
        x, y
      )
    >;
  };

  template<class Pred>
  struct reverse_select<Pred>
  {
    template<class x, class y, class... xs>
    using f = JLN_MP_CONDITIONAL_C_T(
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, y, xs...)::value),
      x, y
    );
  };


  template<class Pred, class C>
  struct select_flip<Pred, C, C>
  {
    template<class x, class y, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      JLN_MP_CONDITIONAL_C_T(
        JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, y, x, xs...)::value),
        y, x
      )
    );
  };

  template<class Pred>
  struct select_flip<Pred>
  {
    template<class x, class y, class... xs>
    using f = JLN_MP_CONDITIONAL_C_T(
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, y, x, xs...)::value),
      y, x
    );
  };


  template<class Pred, class C>
  struct reverse_select_flip<Pred, C, C>
  {
    template<class x, class y, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      JLN_MP_CONDITIONAL_C_T(
        JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, y, x, xs...)::value),
        x, y
      )
    );
  };

  template<class Pred>
  struct reverse_select_flip<Pred>
  {
    template<class x, class y, class... xs>
    using f = JLN_MP_CONDITIONAL_C_T(
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, y, x, xs...)::value),
      x, y
    );
  };
}
/// \endcond
