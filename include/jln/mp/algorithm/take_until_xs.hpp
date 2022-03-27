#pragma once

#include <jln/mp/algorithm/drop_until_xs.hpp>
#include <jln/mp/algorithm/take_until.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Extracts the first elements of a \sequence that does not satisfy a \predicate.
  /// \treturn \sequence
  /// \see take_front, take_back, take_until, partial_take_until_xs
  /// \see drop_until, drop_until_xs
  /// \see search
  template<class Pred, class TC = listify, class FC = TC>
  struct take_until_xs
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  /// Same as \c take_until_xs, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_until, drop_until_xs
  /// \see take_until, take_until_xs
  /// \see search, partial_search
  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  struct partial_take_until_xs_c
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::drop_until_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
        JLN_MP_TRACE_F(Pred), xs...
      >
    >::template f<TC, FC, xs...>;
  };

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_until_xs = partial_take_until_xs_c<OffsetEnd::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  struct take_inclusive_until_xs
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::to_drop_upto<
        typename detail::_drop_until_xs<sizeof...(xs)>
        ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
      >::type
    >::template f<TC, FC, xs...>;
  };

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  struct partial_take_inclusive_until_xs_c
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::to_drop_upto<
        typename detail::drop_until_xs_call<
            detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
            JLN_MP_TRACE_F(Pred), xs...
        >
      >::type
    >::template f<TC, FC, xs...>;
  };

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_inclusive_until_xs = partial_take_until_xs_c<
    OffsetEnd::value, Pred, take_front_c<1, TC>, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using take_until_xs = unpack<L, mp::take_until_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_take_until_xs = unpack<L,
      mp::partial_take_until_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_take_until_xs_c = unpack<L,
      mp::partial_take_until_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using take_inclusive_until_xs = unpack<L, mp::take_inclusive_until_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = TC>
    using partial_take_inclusive_until_xs = unpack<L,
      mp::partial_take_inclusive_until_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred,
             class TC = mp::listify, class FC = TC>
    using partial_take_inclusive_until_xs_c = unpack<L,
      mp::partial_take_inclusive_until_xs_c<OffsetEnd, Pred, TC, FC>>;
  }
}
