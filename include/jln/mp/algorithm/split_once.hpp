// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/clear.hpp>
#include <jln/mp/algorithm/index.hpp>
#include <jln/mp/algorithm/split_at.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class i>
    struct split_once_select;
  }
  /// \endcond
  /// \ingroup group

  /// Splits a \sequence at the first position that satisfy a predicate.
  /// \treturn \sequence of two or zero \sequence
  template<class Pred, class TC = listify, class FC = clear<>>
  struct split_once_if
  {
    template<class... xs>
    using f = typename detail::split_once_select<
      typename index_if<Pred, identity, always<number<-1>>>::template f<xs...>
    >
      ::template f<TC, FC>
      ::template f<xs...>;
  };

  template<class x, class TC = listify, class FC = clear<>>
  using split_once = split_once_if<is<x>, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = listify, class FC = clear<>>
    using split_once_if = typename detail::_unpack<mp::split_once_if<Pred, TC, FC>, L>::type;

    template<class L, class x, class TC = listify, class FC = clear<>>
    using split_once = typename detail::_unpack<mp::split_once_if<is<x>, TC, FC>, L>::type;
  }
}


#include <jln/mp/list/pop_front.hpp>

namespace jln::mp::detail
{
  template<int_ i>
  struct split_once_select<number<i>>
  {
    template<class TC, class FC>
    using f = split_at2_with_c<i, listify, pop_front<>, TC>;
  };

  template<>
  struct split_once_select<number<-1>>
  {
    template<class TC, class FC>
    using f = JLN_MP_TRACE_F(FC);
  };
}
