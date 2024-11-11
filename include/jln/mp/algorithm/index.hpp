// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/drop_until.hpp>
#include <jln/mp/algorithm/drop_until_xs.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/utility/is.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct index_if_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Finds the index of the first element of \sequence
  /// that satisfies the \predicate \c Pred.
  /// Calls \c TC with the index found or \c FC with the whole \sequence.
  /// \treturn \number
  template<class Pred, class TC = identity, class FC = size<>>
  struct index_if
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Finds the index of the first element of \sequence that is a type \c T.
  /// Calls \c TC with the index found or \c FC with the whole \sequence.
  /// \treturn \number
  template<class T, class TC = identity, class FC = size<>>
  using index_of = index_if<is<T>, TC, FC>;

  /// Search the index of first sub-\sequence that satisfy a \predicate.
  /// \treturn \sequence
  template<class Pred, class TC = identity, class FC = size<>>
  struct index_if_xs
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Same as \c index_if_xs, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  template<int_t OffsetEnd, class Pred, class TC = identity, class FC = size<>>
  struct partial_index_if_xs_c
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      detail::drop_until_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
        JLN_MP_TRACE_F(Pred), xs...
      >
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class OffsetEnd, class Pred, class TC = identity, class FC = size<>>
  using partial_index_if_xs = partial_index_if_xs_c<OffsetEnd::value, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    using index_if = unpack<L, mp::index_if<Pred, TC, FC>>;

    template<class L, class T, class TC = mp::identity, class FC = mp::size<>>
    using index_of = unpack<L, mp::index_of<T, TC, FC>>;

    template<class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    using index_if_xs = unpack<L, mp::index_if_xs<Pred, TC, FC>>;

    template<class OffsetEnd, class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    using partial_index_if_xs = unpack<L, mp::partial_index_if_xs<OffsetEnd, Pred, TC, FC>>;

    template<int_t OffsetEnd, class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    using partial_index_if_xs_c = unpack<L, mp::partial_index_if_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    inline constexpr bool index_if_v = unpack<L, mp::index_if<Pred, TC, FC>>::value;

    template<class L, class T, class TC = mp::identity, class FC = mp::size<>>
    inline constexpr bool index_of_v = unpack<L, mp::index_of<T, TC, FC>>::value;

    template<class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    inline constexpr bool index_if_xs_v = unpack<L, mp::index_if_xs<Pred, TC, FC>>::value;

    template<class OffsetEnd, class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    inline constexpr bool partial_index_if_xs_v = unpack<L, mp::partial_index_if_xs<OffsetEnd, Pred, TC, FC>>::value;

    template<int_t OffsetEnd, class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    inline constexpr bool partial_index_if_xs_c_v = unpack<L, mp::partial_index_if_xs_c<OffsetEnd, Pred, TC, FC>>::value;
  }
}


#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/always.hpp>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct index_if_impl<_drop_while_continue>
    : drop_while_impl<_drop_while_continue>
  {};

  template<std::size_t n>
  struct index_if_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, std::size_t m>
    using f = always<JLN_MP_CALL_TRACE(TC, number<m-n-1>)>;
  };
}
/// \endcond
