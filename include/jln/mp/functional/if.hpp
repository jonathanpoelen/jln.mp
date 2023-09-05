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
  template<class Pred, class TC, class FC = always<false_>>
  struct if_
  {
    template<class... xs>
    using f = typename mp::conditional_c<bool(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, xs...)::value)>
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };

  namespace emp
  {
    template<class Pred, class TC, class FC, class... xs>
    using if_ = typename mp::if_<Pred, TC, FC>::template f<xs...>;
  }
}

/// \cond
#include <jln/mp/list/size.hpp>

namespace jln::mp
{
  template<class TC, class FC>
  struct if_<size<>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<!sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(FC), JLN_MP_TRACE_F(TC)>
      ::template f<xs...>;
  };

  template<int_ i, class TC, class FC>
  struct if_<size<is<number<i>>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<sizeof...(xs) == i>
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };
}
/// \endcond
