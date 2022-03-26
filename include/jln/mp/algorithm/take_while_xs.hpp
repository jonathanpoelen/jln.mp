#pragma once

#include <jln/mp/algorithm/drop_while_xs.hpp>
#include <jln/mp/algorithm/take_while.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Extracts the first elements of a \sequence that satisfy a \predicate.
  /// \treturn \sequence
  /// \see take_front, take_back, take_while, partial_take_while_xs
  /// \see drop_while, drop_while_xs
  /// \see search
  template<class Pred, class C = listify>
  struct take_while_xs
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_while_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<C, xs...>;
  };

  /// Same as \c take_while_xs, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while, drop_while_xs
  /// \see take_while, take_while_xs
  /// \see search, partial_search
  template<int_ OffsetEnd, class Pred, class C = listify>
  struct partial_take_while_xs_c
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::drop_while_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
        JLN_MP_TRACE_F(Pred), xs...
      >
    >::template f<C, xs...>;
  };

  template<class OffsetEnd, class Pred, class C = listify>
  using partial_take_while_xs = partial_take_while_xs_c<OffsetEnd::value, Pred, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using take_while_xs = unpack<L, mp::take_while_xs<Pred, C>>;

    template<class L, class OffsetEnd, class state, class Pred, class C = mp::identity>
    using partial_take_while_xs = unpack<L,
      mp::partial_take_while_xs<OffsetEnd, Pred, C>>;

    template<class L, int_ OffsetEnd, class Pred, class C = mp::listify>
    using partial_take_while_xs_c = unpack<L,
      mp::partial_take_while_xs_c<OffsetEnd, Pred, C>>;
  }
}
