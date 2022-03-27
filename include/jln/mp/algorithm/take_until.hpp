#pragma once

#include <jln/mp/algorithm/take_while.hpp>
#include <jln/mp/algorithm/drop_until.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Extract the first elements of a \sequence that does not satisfy a \predicate.
  /// When an element satisfy the predicate,
  /// call \c TC with it and those before it.
  /// Otherwise \c FC is called on the whole sequence.
  /// \treturn \sequence
  /// \see take_front, take_back, take_until_xs
  /// \see drop_until, drop_until_xs
  /// \see search, partial_search
  template<class Pred, class TC = listify, class FC = TC>
  struct take_until
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  template<class Pred, class TC = listify, class FC = TC>
  struct take_inclusive_until
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::to_drop_upto<
        typename detail::_drop_until<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type
    >::template f<TC, FC, xs...>;
  };

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_until = unpack<L, mp::take_until<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_inclusive_until = unpack<L, mp::take_inclusive_until<Pred, TC, FC>>;
  }
}
