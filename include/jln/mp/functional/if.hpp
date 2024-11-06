// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// A conditional expression.
  /// \treturn \value
  /// \see select, reverse_select
  template<class Pred, class TC, class FC = always<false_>>
  struct if_
  {
    template<class... xs>
    using f = typename conditional_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, xs...)::value)
    >
      ::template f<JLN_MP_TRACE_F(FC), JLN_MP_TRACE_F(TC)>
      ::template f<xs...>;
  };

  namespace emp
  {
    template<class Pred, class TC, class FC, class... xs>
    using if_ = typename mp::if_<Pred, TC, FC>::template f<xs...>;
  }
}


#include <jln/mp/list/size.hpp>
#include <jln/mp/algorithm/same.hpp>

/// \cond
namespace jln::mp
{
  template<class TC, class FC>
  struct if_<size<>, TC, FC>
  {
    template<class... xs>
    using f = typename conditional_c<JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs))>
      ::template f<JLN_MP_TRACE_F(FC), JLN_MP_TRACE_F(TC)>
      ::template f<xs...>;
  };

  template<int_ i, class TC, class FC>
  struct if_<size<is<number<i>>>, TC, FC>
  {
    template<class... xs>
    using f = typename conditional_c<sizeof...(xs) == i>
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };

  template<class TC, class FC>
  struct if_<same<>, TC, FC>
  {
    template<class... xs>
    using f = typename conditional_c<emp::same_xs_v<xs...>>
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };

  template<class C, class TC, class FC>
  struct if_<same<C>, TC, FC>
  {
    template<class... xs>
    using f = typename conditional_c<
      JLN_MP_TRACE_F(C)::template f<number<emp::same_xs_v<xs...>>>::value
    >
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };
}
/// \endcond
