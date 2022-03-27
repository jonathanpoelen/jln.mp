#pragma once

#include <jln/mp/algorithm/drop_while.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct take_while_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Extract the first elements of a \sequence that satisfy a \predicate.
  /// When an element does not satisfy the predicate,
  /// call \c TC with it and those before it.
  /// Otherwise \c FC is called on the whole sequence.
  /// \treturn \sequence
  /// \see take_front, take_back, take_while_xs
  /// \see drop_while, drop_while_xs
  /// \see search, partial_search
  template<class Pred, class TC = listify, class FC = TC>
  struct take_while
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  template<class Pred, class TC = listify, class FC = TC>
  struct take_inclusive_while
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::to_drop_upto<
        typename detail::_drop_while<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type
    >::template f<TC, FC, xs...>;
  };

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_while = unpack<L, mp::take_while<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_inclusive_while = unpack<L, mp::take_inclusive_while<Pred, TC, FC>>;
  }
}


#include <jln/mp/list/take_front.hpp>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct take_while_impl<_drop_while_continue>
  {
    template<class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(FC, xs...);
  };

  template<std::size_t n>
  struct take_while_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, class... xs>
    using f = typename take_front_c<sizeof...(xs)-n-1, TC>::template f<xs...>;
  };
}
/// \encond
