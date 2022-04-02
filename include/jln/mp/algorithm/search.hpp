#pragma once

#include <jln/mp/algorithm/drop_until_xs.hpp>
#include <jln/mp/algorithm/index.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct search_before_impl;

    template<class>
    struct search_before_extended_by_n_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Search the first sub-\sequence that satisfy a \predicate.
  /// Calls \c TC with all the elements from sub-\sequence found at the end.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search_before, partial_search, after, search_index
  /// \see search_before_extended_by_n
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct search
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  /// Search elements before sub-\sequence that satisfy a \predicate.
  /// Calls \c TC with the elements from the beginning to sub-\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, partial_search, after, search_index
  /// \see search_before_extended_by_n
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct search_before
  {
    template<class... xs>
    using f = typename detail::search_before_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  /// Search elements before sub-\sequence that satisfy a \predicate.
  /// Calls \c TC with the elements from the beginning to sub-\sequence found + \c ExtendedByN.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, search_before, partial_search, after, search_index
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class Pred, class ExtendedByN, class TC = listify, class FC = clear<TC>>
  struct search_before_extended_by_n
  {
    template<class... xs>
    using f = typename detail::search_before_extended_by_n_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, ExtendedByN, xs...>;
  };

  /// Same \c search, but it stops when there is StopWhenAtLeast::value element or less.
  /// \treturn \sequence
  /// \see search, search_before, after, search_index
  /// \see search_before_extended_by_n
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<int_ StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  struct partial_search_c
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::_drop_until_xs<
        StopWhenAtLeast < sizeof...(xs) ? sizeof...(xs) - StopWhenAtLeast : 0
      >::template f<size_t(sizeof...(xs) - StopWhenAtLeast), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  template<class StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search = partial_search_c<StopWhenAtLeast::value, Pred, TC, FC>;

  /// Same \c search_before, but it stops when there is StopWhenAtLeast::value element or less.
  /// \treturn \sequence
  /// \see search, search_before, partial_search, after, search_index
  /// \see search_before_extended_by_n, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<int_ StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  struct partial_search_before_c
  {
    template<class... xs>
    using f = typename detail::search_before_impl<
      typename detail::_drop_until_xs<
        StopWhenAtLeast < sizeof...(xs) ? sizeof...(xs) - StopWhenAtLeast : 0
      >::template f<size_t(sizeof...(xs) - StopWhenAtLeast), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  template<class StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_before = partial_search_before_c<StopWhenAtLeast::value, Pred, TC, FC>;

  /// Same \c search_before, but it stops when there is StopWhenAtLeast::value element or less.
  /// \treturn \sequence
  /// \see search, search_before, partial_search, after, search_index
  /// \see search_before_extended_by_n, partial_search_before
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<int_ StopWhenAtLeast, class Pred, class ExtendedByN,
           class TC = listify, class FC = clear<TC>>
  struct partial_search_before_extended_by_n_c
  {
    template<class... xs>
    using f = typename detail::search_before_extended_by_n_impl<
      typename detail::_drop_until_xs<
        StopWhenAtLeast < sizeof...(xs) ? sizeof...(xs) - StopWhenAtLeast : 0
      >::template f<size_t(sizeof...(xs) - StopWhenAtLeast), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, ExtendedByN, xs...>;
  };

  template<class StopWhenAtLeast, class Pred, class ExtendedByN, class TC = listify, class FC = clear<TC>>
  using partial_search_before_extended_by_n
    = partial_search_before_extended_by_n_c<StopWhenAtLeast::value, Pred, ExtendedByN, TC, FC>;

  /// Search the index of first sub-\sequence that satisfy a \predicate.
  /// \treturn \sequence
  /// \see search, search_before, after
  template<class Pred, class TC = identity, class FC = size<>>
  struct search_index
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using search = unpack<L, mp::search<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using search_before = unpack<L, mp::search_before<Pred, TC, FC>>;

    template<class L, class Pred, class ExtendedByN,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using search_before_extended_by_n = unpack<L,
      mp::search_before_extended_by_n<Pred, ExtendedByN, TC, FC>>;


    template<class L, class StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search = unpack<L, mp::partial_search<Pred, StopWhenAtLeast, TC, FC>>;

    template<class L, class StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before = unpack<L,
      mp::partial_search_before<Pred, StopWhenAtLeast, TC, FC>>;

    template<class L, class StopWhenAtLeast, class Pred, class ExtendedByN,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before_extended_by_n = unpack<L,
      mp::partial_search_before_extended_by_n<Pred, StopWhenAtLeast, TC, FC>>;


    template<class L, int_ StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_c = unpack<L, mp::partial_search_c<StopWhenAtLeast, Pred, TC, FC>>;

    template<class L, int_ StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before_c = unpack<L,
      mp::partial_search_before_c<StopWhenAtLeast, Pred, TC, FC>>;

    template<class L, int_ StopWhenAtLeast, class Pred, class ExtendedByN,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before_extended_by_n_c = unpack<L,
      mp::partial_search_before_extended_by_n_c<StopWhenAtLeast, Pred, TC, FC>>;


    template<class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    using search_index = unpack<L, mp::search<Pred, TC, FC>>;
  }
}

#include <jln/mp/algorithm/starts_with.hpp>
#include <jln/mp/algorithm/ends_with.hpp>

/// \cond
namespace jln::mp
{
  // optimize search with starts_with
  template<class T, class U, class... Ts, class C, class TC, class FC>
  struct search<starts_with<list<T, U, Ts...>, C>, TC, FC>
  : partial_search_c<sizeof...(Ts)+1,
      starts_with<list<T, U, Ts...>, C>, TC, FC>
  {};

  // optimize search_before with starts_with
  template<class T, class U, class... Ts, class C, class TC, class FC>
  struct search_before<starts_with<list<T, U, Ts...>, C>, TC, FC>
  : partial_search_before_c<sizeof...(Ts)+1,
      starts_with<list<T, U, Ts...>, C>, TC, FC>
  {};

  // optimize search_before_extended_by_n with starts_with
  template<class T, class U, class... Ts, class C, class ExtendedByN, class TC, class FC>
  struct search_before_extended_by_n<starts_with<list<T, U, Ts...>, C>, ExtendedByN, TC, FC>
  : partial_search_before_extended_by_n_c<sizeof...(Ts)+1,
      starts_with<list<T, U, Ts...>, C>, ExtendedByN, TC, FC>
  {};

  // optimize search_index with starts_with
  template<class T, class U, class... Ts, class C, class TC, class FC>
  struct search_index<starts_with<list<T, U, Ts...>, C>, TC, FC>
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_drop_until_xs<
        sizeof...(Ts)+1 < sizeof...(xs) ? sizeof...(xs) - sizeof...(Ts) - 1 : 0
      >::template f<sizeof...(xs) - sizeof...(Ts) - 1u, starts_with<list<T, U, Ts...>, C>, xs...>
    >::template f<TC, FC, xs...>;
  };

  // optimize search with ends_with
  template<class T, class U, class... Ts, class C, class TC, class FC>
  struct search<ends_with<list<T, U, Ts...>, C>, TC, FC>
  : partial_search_c<sizeof...(Ts)+1,
      ends_with<list<T, U, Ts...>, C>, TC, FC>
  {};

  // optimize search_before with ends_with
  template<class T, class U, class... Ts, class C, class TC, class FC>
  struct search_before<ends_with<list<T, U, Ts...>, C>, TC, FC>
  : partial_search_before_c<sizeof...(Ts)+1,
      ends_with<list<T, U, Ts...>, C>, TC, FC>
  {};

  // optimize search_before_extended_by_n with ends_with
  template<class T, class U, class... Ts, class C, class ExtendedByN, class TC, class FC>
  struct search_before_extended_by_n<ends_with<list<T, U, Ts...>, C>, ExtendedByN, TC, FC>
  : partial_search_before_extended_by_n_c<sizeof...(Ts)+1,
      ends_with<list<T, U, Ts...>, C>, ExtendedByN, TC, FC>
  {};

  // optimize search_index with ends_with
  template<class T, class U, class... Ts, class C, class TC, class FC>
  struct search_index<ends_with<list<T, U, Ts...>, C>, TC, FC>
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_drop_until_xs<
        sizeof...(Ts)+1 < sizeof...(xs)? sizeof...(xs) - sizeof...(Ts) - 1 : 0
      >::template f<sizeof...(xs) - sizeof...(Ts) - 1u, ends_with<list<T, U, Ts...>, C>, xs...>
    >::template f<TC, FC, xs...>;
  };
}
/// \endcond

#include <jln/mp/list/take_front.hpp>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct search_before_impl<_drop_while_continue>
  {
    template<class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(FC, xs...);
  };

  template<std::size_t n>
  struct search_before_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, class... xs>
    using f = typename take_front_c<sizeof...(xs)-n-1, TC>::template f<xs...>;
  };


  template<>
  struct search_before_extended_by_n_impl<_drop_while_continue>
  {
    template<class TC, class FC, class ExtendedByN, class... xs>
    using f = JLN_MP_CALL_TRACE(FC, xs...);
  };

  constexpr int_ extended_by_n(int_ seq_len, int_ n, int_ extended)
  {
    auto i = seq_len-n;
    auto take = i + extended;
    return (take < 0) ? 0
         : (take > seq_len) ? seq_len
         : take;
  }

  template<std::size_t n>
  struct search_before_extended_by_n_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, class ExtendedByN, class... xs>
    using f = typename take_front_c<
      extended_by_n(sizeof...(xs), n+1, ExtendedByN::value),
      TC
    >::template f<xs...>;
  };
}
/// \endcond
