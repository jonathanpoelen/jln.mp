// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/clear.hpp>
#include <jln/mp/list/listify.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <cstddef>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool found = false>
    struct _drop_while;

    template<class>
    struct to_drop_upto;

    template<class>
    struct drop_while_impl;

    template<class>
    struct drop_while_extended_by_n_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// When an element does not satisfy the predicate,
  /// call \c TC with it and all those that follow it.
  /// Otherwise \c FC is called on the whole sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while_xs
  /// \see take_while, take_while_xs
  /// \see search, partial_search
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_while
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Remove the first minus at most \c ExtendedByN elements of a \sequence that satisfy a \predicate.
  /// When an element does not satisfy the predicate,
  /// call \c TC with it and all those that follow it plus at most \c ExtendedByN.
  /// Otherwise \c FC is called on the whole sequence.
  /// \semantics
  ///   \code
  ///   call<drop_while_extended_by_n_c<2, is_not<number<4>>>,
  ///     number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   //                         ^ 2        ^ 1       ^ found elem
  ///   ==
  ///   list<number<2>, number<3>, number<4>, number<5>>
  ///
  ///   call<drop_while_extended_by_n_c<2, is_not<number<1>>>,
  ///     number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   //   ^ 1       ^ found elem
  ///   ==
  ///   list<number<0>, number<1>>
  ///   \endcode
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_while_extended_by_n_c
  {
    template<class... xs>
    using f = typename detail::drop_while_extended_by_n_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_while_extended_by_n = drop_while_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_while = drop_while_extended_by_n_c<1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_while = typename detail::_unpack<mp::drop_while<Pred, TC, FC>, L>::type;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
    using drop_while_extended_by_n_c = typename detail::_unpack<
      mp::drop_while_extended_by_n_c<ExtendedByN, Pred, TC, FC>, L>::type;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
    using drop_while_extended_by_n = typename detail::_unpack<
      mp::drop_while_extended_by_n<ExtendedByN, Pred, TC, FC>, L>::type;

    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_inclusive_while = typename detail::_unpack<mp::drop_inclusive_while<Pred, TC, FC>, L>::type;
  }

  /// \cond
  template<class Pred, class TC, class FC>
  struct drop_while<Pred, drop_front_c<1, TC>, FC>
  : drop_while_extended_by_n_c<1, Pred, TC, FC>
  {};
  /// \endcond
}


#include <jln/mp/detail/sequence.hpp>
#include <jln/mp/number/number.hpp>

/// \cond
namespace jln::mp::detail
{
  template<std::size_t n>
  struct _drop_while_result
  {
    template<class C, std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_result;
  };

  struct _drop_while_continue
  {
    template<class C, std::size_t consumed, class Pred, class... xs>
    using f = typename C::template f<consumed, Pred, xs...>;
  };


  template<class>
  struct is_drop_while_continue
  {
    using type = false_;
  };

  template<>
  struct is_drop_while_continue<_drop_while_continue>
  {
    using type = true_;
  };


  template<>
  struct drop_while_impl<_drop_while_continue>
  {
    template<class TC, class FC, std::size_t m>
    using f = JLN_MP_TRACE_F(FC);
  };

  template<std::size_t n>
  struct drop_while_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, std::size_t m>
    using f = drop_front_c<m-n-1, TC>;
  };


  template<>
  struct drop_while_extended_by_n_impl<_drop_while_continue>
  {
    template<std::size_t ExtendedByN, class TC, class FC, std::size_t m>
    using f = JLN_MP_TRACE_F(FC);
  };

  template<std::size_t n>
  struct drop_while_extended_by_n_impl<_drop_while_result<n>>
  {
    template<std::size_t ExtendedByN, class TC, class FC, std::size_t m>
    using f = drop_front_c<
      m - (n >= ExtendedByN ? n - ExtendedByN + 1 : 0),
      TC
    >;
  };


  // _drop_while<n, b> = _drop_until<n, !b>

  template<int n>
  struct _drop_while<n, false> : _drop_while<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256,
    false
  >
  {};

  struct drop_while_impl_false
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_result<consumed+sizeof...(xs)>;
  };

#define JLN_DROP_WHILE_IMPL(n, m)                                    \
  template<>                                                         \
  struct _drop_while<n, false>                                       \
  {                                                                  \
    template<std::size_t consumed, class Pred, class x, class... xs> \
    using f = typename _drop_while<                                  \
      m, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<x>::value)     \
    >::template f<consumed, Pred, xs...>;                            \
  };                                                                 \
                                                                     \
  template<>                                                         \
  struct _drop_while<n, true> : drop_while_impl_false               \
  {}

  JLN_DROP_WHILE_IMPL(7, 6);
  JLN_DROP_WHILE_IMPL(6, 5);
  JLN_DROP_WHILE_IMPL(5, 4);
  JLN_DROP_WHILE_IMPL(4, 3);
  JLN_DROP_WHILE_IMPL(3, 2);
  JLN_DROP_WHILE_IMPL(2, 1);
  JLN_DROP_WHILE_IMPL(1, 0);

#undef JLN_DROP_WHILE_IMPL

  template<>
  struct _drop_while<0, false>
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_continue;
  };

  template<>
  struct _drop_while<0, true>
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_result<consumed+sizeof...(xs)>;
  };

  template<>
  struct _drop_while<8, false>
  {
    template<
      std::size_t consumed,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_while<7, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<_1>::value)>
      ::template f<
          consumed+sizeof...(xs), Pred,
          _2, _3, _4, _5, _6, _7, _8>;
  };

  template<>
  struct _drop_while<16, false>
  {
    template<
      std::size_t consumed,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_while<7, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<_1>::value)>
      ::template f<
          consumed+sizeof...(xs), Pred,
          _2, _3, _4, _5, _6, _7, _8>
      ::template f<
          _drop_while<sizeof...(xs), false>,
          consumed, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)               \
  template<>                                        \
  struct _drop_while<n, false>                      \
  {                                                 \
    template<                                       \
      std::size_t consumed,                         \
      class Pred,                                   \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),          \
      class... xs>                                  \
    using f = typename _drop_while<m, false>        \
      ::template f<                                 \
          consumed+sizeof...(xs), Pred,             \
          xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)> \
      ::template f<                                 \
          _drop_while<sizeof...(xs), false>,        \
          consumed, Pred, xs...>;                   \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond
