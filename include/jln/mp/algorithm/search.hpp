#pragma once

#include <jln/mp/algorithm/find.hpp>
#include <jln/mp/algorithm/index.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool found>
    struct _search;

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
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct search
  {
    template<class... xs>
    using f = typename detail::find_if_impl<
      typename detail::_search<
        detail::n_8_or_more_16_32_64_128_256(sizeof...(xs)), false
      >::template f<sizeof...(xs), Pred, xs...>
    >::template f<TC, FC, xs...>;
  };

  /// Search elements before sub-\sequence that satisfy a \predicate.
  /// Calls \c TC with the elements from the beginning to sub-\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct search_before
  {
    template<class... xs>
    using f = typename detail::search_before_impl<
      typename detail::_search<
        detail::n_8_or_more_16_32_64_128_256(sizeof...(xs)), false
      >::template f<sizeof...(xs), Pred, xs...>
    >::template f<TC, FC, xs...>;
  };

  /// Search elements before sub-\sequence that satisfy a \predicate.
  /// Calls \c TC with the elements from the beginning to sub-\sequence found + \c ExtendedByN.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  template<class Pred, class ExtendedByN, class TC = listify, class FC = clear<TC>>
  struct search_before_extended_by_n
  {
    template<class... xs>
    using f = typename detail::search_before_extended_by_n_impl<
      typename detail::_search<
        detail::n_8_or_more_16_32_64_128_256(sizeof...(xs)), false
      >::template f<sizeof...(xs), Pred, xs...>
    >::template f<TC, FC, ExtendedByN, xs...>;
  };

  /// Same \c search, but it stops when there is StopWhenAtLeast::value element or less.
  /// \treturn \sequence
  template<class StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  struct partial_search
  {
    template<class... xs>
    using f = typename detail::find_if_impl<
      typename detail::_search<
        detail::n_8_or_more_16_32_64_128_256(
          sizeof...(xs) > StopWhenAtLeast::value ? sizeof...(xs) - StopWhenAtLeast::value : 0
        ), false
      >::template f<size_t(sizeof...(xs) - StopWhenAtLeast::value), Pred, xs...>
    >::template f<TC, FC, xs...>;
  };

  template<int_ StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_c = partial_search<number<StopWhenAtLeast>, Pred, TC, FC>;

  /// Same \c search_before, but it stops when there is StopWhenAtLeast::value element or less.
  /// \treturn \sequence
  template<class StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  struct partial_search_before
  {
    template<class... xs>
    using f = typename detail::search_before_impl<
      typename detail::_search<
        detail::n_8_or_more_16_32_64_128_256(
          sizeof...(xs) > StopWhenAtLeast::value ? sizeof...(xs) - StopWhenAtLeast::value : 0
        ), false
      >::template f<size_t(sizeof...(xs) - StopWhenAtLeast::value), Pred, xs...>
    >::template f<TC, FC, xs...>;
  };

  template<int_ StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_before_c = partial_search_before<number<StopWhenAtLeast>, Pred, TC, FC>;

  /// Same \c search_before, but it stops when there is StopWhenAtLeast::value element or less.
  /// \treturn \sequence
  template<class StopWhenAtLeast, class Pred, class ExtendedByN,
           class TC = listify, class FC = clear<TC>>
  struct partial_search_before_extended_by_n
  {
    template<class... xs>
    using f = typename detail::search_before_extended_by_n_impl<
      typename detail::_search<
        detail::n_8_or_more_16_32_64_128_256(
          sizeof...(xs) > StopWhenAtLeast::value ? sizeof...(xs) - StopWhenAtLeast::value : 0
        ), false
      >::template f<size_t(sizeof...(xs) - StopWhenAtLeast::value), Pred, xs...>
    >::template f<TC, FC, ExtendedByN, xs...>;
  };

  template<int_ StopWhenAtLeast, class Pred, class ExtendedByN, class TC = listify, class FC = clear<TC>>
  using partial_search_before_extended_by_n_c
    = partial_search_before_extended_by_n<number<StopWhenAtLeast>, Pred, ExtendedByN, TC, FC>;

  /// Search the index of first sub-\sequence that satisfy a \predicate.
  /// \treturn \sequence
  template<class Pred, class TC = identity, class FC = size<>>
  struct search_index
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_search<
        detail::n_8_or_more_16_32_64_128_256(sizeof...(xs)), false
      >::template f<sizeof...(xs), Pred, xs...>
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
    using partial_search_c = unpack<L, mp::partial_search<Pred, number<StopWhenAtLeast>, TC, FC>>;

    template<class L, int_ StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before_c = unpack<L,
      mp::partial_search_before<Pred, number<StopWhenAtLeast>, TC, FC>>;

    template<class L, int_ StopWhenAtLeast, class Pred, class ExtendedByN,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before_extended_by_n_c = unpack<L,
      mp::partial_search_before_extended_by_n<Pred, mp::number<StopWhenAtLeast>, TC, FC>>;


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
  : partial_search<number<sizeof...(Ts)+1>,
      starts_with<list<T, U, Ts...>, C>, TC, FC>
  {};

  // optimize search_before with starts_with
  template<class T, class U, class... Ts, class C, class TC, class FC>
  struct search_before<starts_with<list<T, U, Ts...>, C>, TC, FC>
  : partial_search_before<number<sizeof...(Ts)+1>,
      starts_with<list<T, U, Ts...>, C>, TC, FC>
  {};

  // optimize search_before_extended_by_n with starts_with
  template<class T, class U, class... Ts, class C, class ExtendedByN, class TC, class FC>
  struct search_before_extended_by_n<starts_with<list<T, U, Ts...>, C>, ExtendedByN, TC, FC>
  : partial_search_before_extended_by_n<number<sizeof...(Ts)+1>,
      starts_with<list<T, U, Ts...>, C>, ExtendedByN, TC, FC>
  {};

  // optimize search_index with starts_with
  template<class T, class U, class... Ts, class C, class TC, class FC>
  struct search_index<starts_with<list<T, U, Ts...>, C>, TC, FC>
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_search<
        detail::n_8_or_more_16_32_64_128_256(
          sizeof...(xs) > sizeof...(Ts)+1 ? sizeof...(xs) - sizeof...(Ts) - 1 : 0
        ), false
      >::template f<sizeof...(xs) - sizeof...(Ts) - 1u, starts_with<list<T, U, Ts...>, C>, xs...>
    >::template f<TC, FC, xs...>;
  };

  // optimize search with ends_with
  template<class T, class U, class... Ts, class C, class TC, class FC>
  struct search<ends_with<list<T, U, Ts...>, C>, TC, FC>
  : partial_search<number<sizeof...(Ts)+1>,
      ends_with<list<T, U, Ts...>, C>, TC, FC>
  {};

  // optimize search_before with ends_with
  template<class T, class U, class... Ts, class C, class TC, class FC>
  struct search_before<ends_with<list<T, U, Ts...>, C>, TC, FC>
  : partial_search_before<number<sizeof...(Ts)+1>,
      ends_with<list<T, U, Ts...>, C>, TC, FC>
  {};

  // optimize search_before_extended_by_n with ends_with
  template<class T, class U, class... Ts, class C, class ExtendedByN, class TC, class FC>
  struct search_before_extended_by_n<ends_with<list<T, U, Ts...>, C>, ExtendedByN, TC, FC>
  : partial_search_before_extended_by_n<number<sizeof...(Ts)+1>,
      ends_with<list<T, U, Ts...>, C>, ExtendedByN, TC, FC>
  {};

  // optimize search_index with ends_with
  template<class T, class U, class... Ts, class C, class TC, class FC>
  struct search_index<ends_with<list<T, U, Ts...>, C>, TC, FC>
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_search<
        detail::n_8_or_more_16_32_64_128_256(
          sizeof...(xs) > sizeof...(Ts)+1 ? sizeof...(xs) - sizeof...(Ts) - 1 : 0
        ), false
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
    using f = typename FC::template f<xs...>;
  };

  template<std::size_t n>
  struct search_before_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, class... xs>
    using f = typename take_front<number<sizeof...(xs)-n-1>, TC>::template f<xs...>;
  };


  template<>
  struct search_before_extended_by_n_impl<_drop_while_continue>
  {
    template<class TC, class FC, class ExtendedByN, class... xs>
    using f = typename FC::template f<xs...>;
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
    using f = typename take_front<number<
      extended_by_n(sizeof...(xs), n+1, ExtendedByN::value)
    >, TC>::template f<xs...>;
  };


#define JLN_DROP_WHILE_IMPL(n, m)                                     \
  template<>                                                          \
  struct _search<n, false>                                            \
  {                                                                   \
    template<std::size_t remaining, class Pred, class x, class... xs> \
    using f = typename _search<m, Pred::template f<x, xs...>::value>  \
            ::template f<remaining-1, Pred, xs...>;                   \
  };                                                                  \
                                                                      \
  template<>                                                          \
  struct _search<n, true>                                             \
  {                                                                   \
    template<std::size_t remaining, class Pred, class... xs>          \
    using f = _drop_while_result<sizeof...(xs)>;                      \
  }

  JLN_DROP_WHILE_IMPL(7, 6);
  JLN_DROP_WHILE_IMPL(6, 5);
  JLN_DROP_WHILE_IMPL(5, 4);
  JLN_DROP_WHILE_IMPL(4, 3);
  JLN_DROP_WHILE_IMPL(3, 2);
  JLN_DROP_WHILE_IMPL(2, 1);
  JLN_DROP_WHILE_IMPL(1, 0);

#undef JLN_DROP_WHILE_IMPL

  template<>
  struct _search<0, false>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_continue;
  };

  template<>
  struct _search<0, true>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_result<sizeof...(xs)>;
  };

  template<>
  struct _search<8, false>
  {
    template<std::size_t remaining, class Pred, class x, class... xs>
    using f = typename _search<7, Pred::template f<x, xs...>::value>
      ::template f<remaining-8, Pred, xs...>;
  };

  template<>
  struct _search<16, false>
  {
    template<
      std::size_t remaining,
      class Pred,
      JLN_MP_XS_8(class, JLN_MP_NIL, JLN_MP_COMMA),
      class... xs>
    using f = typename _search<7, Pred::template f<
        JLN_MP_XS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), xs...
      >::value>
      ::template f<7, Pred,
                   JLN_MP_XS_2_TO_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
                   xs...>
      ::template f<_search<n_8_or_more_16_32_64_128_256(remaining-8), false>,
                   remaining-8, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)                                         \
  template<>                                                                  \
  struct _search<n, false>                                                    \
  {                                                                           \
    template<                                                                 \
      std::size_t remaining,                                                  \
      class Pred,                                                             \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),                                    \
      class... xs>                                                            \
    using f = typename _search<m, false>                                      \
      ::template f<m, Pred, xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), xs...>  \
      ::template f<_search<n_8_or_more_16_32_64_128_256(remaining-m), false>, \
                   remaining-m, Pred, xs...>;                                 \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond
