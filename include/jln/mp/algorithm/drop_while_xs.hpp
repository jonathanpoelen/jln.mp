// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/drop_while.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool found = false>
    struct _drop_while_xs;

    constexpr int_t partial_drop_while_xs_size(int_t i, int_t size);

    template<int_t Size, class Pred, class... xs>
    using drop_while_xs_call = typename detail::_drop_while_xs<Size>
      ::template f<Size, Pred, xs...>;
  }
  /// \endcond

  /// \ingroup search

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// Same as \c drop_while, but the \predicate takes all the elements of
  /// the current position until the end of the list.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while, partial_drop_while_xs
  /// \see take_while, take_while_xs
  /// \see search
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_while_xs
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::_drop_while_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Same as \c drop_while_extended_by_n_c, but for \c drop_while_xs.
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_while_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::drop_while_extended_by_n_impl<
      typename detail::_drop_while_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_while_extended_by_n_xs = drop_while_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_while_xs = drop_while_extended_by_n_xs_c<1, Pred, TC, FC>;

  /// Same as \c drop_while_extended_by_n_xs_c, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while, drop_while_xs
  /// \see take_while, take_while_xs
  /// \see search, partial_search
  template<int_t OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC = listify, class FC = clear<TC>>
  struct partial_drop_while_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::drop_while_extended_by_n_impl<
      typename detail::drop_while_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
        JLN_MP_TRACE_F(Pred), xs...
      >
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_while_xs =
    partial_drop_while_extended_by_n_xs_c<OffsetEnd::value, 0, Pred, TC, FC>;

  template<int_t OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_while_xs_c =
    partial_drop_while_extended_by_n_xs_c<OffsetEnd, 0, Pred, TC, FC>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_while_extended_by_n_xs =
    partial_drop_while_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>;

  template<std::size_t OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_inclusive_while_xs_c =
    partial_drop_while_extended_by_n_xs_c<OffsetEnd, 1, Pred, TC, FC>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_inclusive_while_xs =
    partial_drop_while_extended_by_n_xs_c<OffsetEnd::value, 1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_while_xs = typename detail::_unpack<mp::drop_while_xs<Pred, TC, FC>, L>::type;

    template<class L, class ExtendedByN, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_while_extended_by_n_xs = typename detail::_unpack<
      mp::drop_while_extended_by_n_xs<ExtendedByN, Pred, TC, FC>, L>::type;

    template<class L, std::size_t ExtendedByN, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_while_extended_by_n_xs_c = typename detail::_unpack<
      mp::drop_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>, L>::type;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_while_xs = typename detail::_unpack<
      mp::partial_drop_while_xs<OffsetEnd, Pred, TC, FC>, L>::type;

    template<class L, int_t OffsetEnd, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_while_xs_c = typename detail::_unpack<
      mp::partial_drop_while_xs_c<OffsetEnd, Pred, TC, FC>, L>::type;

    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_inclusive_while_xs = typename detail::_unpack<
      mp::drop_inclusive_while_xs<Pred, TC, FC>, L>::type;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_inclusive_while_xs = typename detail::_unpack<
      mp::partial_drop_inclusive_while_xs<OffsetEnd, Pred, TC, FC>, L>::type;

    template<class L, int_t OffsetEnd, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_inclusive_while_xs_c = typename detail::_unpack<
      mp::partial_drop_inclusive_while_xs_c<OffsetEnd, Pred, TC, FC>, L>::type;

    template<class L, class OffsetEnd, class ExtendedByN, class Pred,
             class TC = listify, class FC = mp::clear<TC>>
    using partial_drop_while_extended_by_n_xs = typename detail::_unpack<
      mp::partial_drop_while_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, FC>, L>::type;

    template<class L, int_t OffsetEnd, std::size_t ExtendedByN, class Pred,
             class TC = listify, class FC = mp::clear<TC>>
    using partial_drop_while_extended_by_n_xs_c = typename detail::_unpack<
      mp::partial_drop_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>, L>::type;
  }

  /// \cond
  template<class Pred, class TC, class FC>
  struct drop_while_xs<Pred, drop_front_c<1, TC>, FC>
  : drop_while_extended_by_n_xs_c<1, Pred, TC, FC>
  {};
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  constexpr int_t partial_drop_while_xs_size(int_t i, int_t size)
  {
    return (i >= size) ? size
         : (i >= 0) ? i
         : (i >= -size) ? size + i + 1
         : 0
         ;
  }

  template<int n>
  struct _drop_while_xs<n, false> : _drop_while_xs<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256,
    false
  >
  {};

  struct drop_while_xs_impl_false
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_result<sizeof...(xs)>;
  };

#define JLN_DROP_WHILE_IMPL(n, m)                                       \
  template<>                                                            \
  struct _drop_while_xs<n, false>                                       \
  {                                                                     \
    template<std::size_t remaining, class Pred, class x, class... xs>   \
    using f = typename _drop_while_xs<                                  \
      m, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<x, xs...>::value) \
    >::template f<remaining-1, Pred, xs...>;                            \
  };                                                                    \
                                                                        \
  template<>                                                            \
  struct _drop_while_xs<n, true> : drop_while_xs_impl_false            \
  {}

  JLN_DROP_WHILE_IMPL(7, 6);
  JLN_DROP_WHILE_IMPL(6, 5);
  JLN_DROP_WHILE_IMPL(5, 4);
  JLN_DROP_WHILE_IMPL(4, 3);
  JLN_DROP_WHILE_IMPL(3, 2);
  JLN_DROP_WHILE_IMPL(2, 1);
  JLN_DROP_WHILE_IMPL(1, 0);

#undef JLN_DROP_WHILE_IMPL

  // _drop_while_xs<n, b> is a _search<n, !b>

  template<>
  struct _drop_while_xs<0, false>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_continue;
  };

  template<>
  struct _drop_while_xs<0, true>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_result<sizeof...(xs)>;
  };

  template<>
  struct _drop_while_xs<8, false>
  {
    template<std::size_t remaining, class Pred, class x, class... xs>
    using f = typename _drop_while_xs<
      7, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<x, xs...>::value)
    >::template f<remaining-8, Pred, xs...>;
  };

  template<>
  struct _drop_while_xs<16, false>
  {
    template<
      std::size_t remaining,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_while_xs<7, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<
        _1, _2, _3, _4, _5, _6, _7, _8, xs...
      >::value)>
      ::template f<7, Pred, _2, _3, _4, _5, _6, _7, _8, xs...>
      ::template f<_drop_while_xs<remaining-8>, remaining-8, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)                                        \
  template<>                                                                 \
  struct _drop_while_xs<n, false>                                            \
  {                                                                          \
    template<                                                                \
      std::size_t remaining,                                                 \
      class Pred,                                                            \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),                                   \
      class... xs>                                                           \
    using f = typename _drop_while_xs<m, false>                              \
      ::template f<m, Pred, xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), xs...> \
      ::template f<_drop_while_xs<remaining-m>, remaining-m, Pred, xs...>;   \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond
