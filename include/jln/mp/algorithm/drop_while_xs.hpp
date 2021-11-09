#pragma once

#include <jln/mp/algorithm/drop_while.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool not_found>
    struct _drop_while_xs;

    constexpr int_ partial_drop_while_xs_size(int_ i, int_ size)
    {
      return (i >= size) ? size
        : (i >= 0) ? i
        : (i >= -size) ? size + i + 1
        : 0
        ;
    }

    template<int_ Size, class Pred, class... xs>
    using drop_while_xs_call = typename detail::_drop_while_xs<
      detail::n_8_or_less_16_32_64_128_256(Size),
      true
    >::template f<Size, Pred, xs...>;
  }
  /// \endcond

  /// \ingroup search

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// The \predicate takes all the elements of the current position until
  /// the end of the list.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while, partial_drop_while_xs, take_while, take_while_xs
  template<class Pred, class C = listify>
  struct drop_while_xs
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::_drop_while_xs<
        detail::n_8_or_less_16_32_64_128_256(sizeof...(xs)),
        true
      >::template f<sizeof...(xs), Pred, xs...>
    >::template f<C, xs...>;
  };

  /// Same as \c drop_while_xs, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while, drop_while_xs, take_while, take_while_xs
  template<class OffsetEnd, class Pred, class C = listify>
  struct partial_drop_while_xs
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::drop_while_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd::value, sizeof...(xs)),
        Pred, xs...
      >
    >::template f<C, xs...>;
  };

  template<int_ OffsetEnd, class Pred, class C = listify>
  using partial_drop_while_xs_c = partial_drop_while_xs<number<OffsetEnd>, Pred, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using drop_while_xs = unpack<L, mp::drop_while_xs<Pred, C>>;

    template<class L, class OffsetEnd, class state, class Pred, class C = mp::identity>
    using partial_drop_while_xs = unpack<L,
      mp::partial_drop_while_xs<OffsetEnd, Pred, C>>;

    template<class L, int_ OffsetEnd, class Pred, class C = mp::listify>
    using partial_drop_while_xs_c = unpack<L,
      mp::partial_drop_while_xs<number<OffsetEnd>, Pred, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
#define JLN_DROP_WHILE_IMPL(n, m)                                           \
  template<>                                                                \
  struct _drop_while_xs<n, true>                                            \
  {                                                                         \
    template<std::size_t remaining, class Pred, class x, class... xs>       \
    using f = typename _drop_while_xs<m, Pred::template f<x, xs...>::value> \
            ::template f<remaining-1, Pred, xs...>;                         \
  };                                                                        \
                                                                            \
  template<>                                                                \
  struct _drop_while_xs<n, false>                                           \
  {                                                                         \
    template<std::size_t remaining, class Pred, class... xs>                \
    using f = _drop_while_result<sizeof...(xs)>;                            \
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
  struct _drop_while_xs<0, true>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_continue;
  };

  template<>
  struct _drop_while_xs<0, false>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_result<sizeof...(xs)>;
  };

  template<>
  struct _drop_while_xs<8, true>
  {
    template<std::size_t remaining, class Pred, class x, class... xs>
    using f = typename _drop_while_xs<7, Pred::template f<x, xs...>::value>
      ::template f<remaining-8, Pred, xs...>;
  };

  template<>
  struct _drop_while_xs<16, true>
  {
    template<
      std::size_t remaining,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_while_xs<7, Pred::template f<
        _1, _2, _3, _4, _5, _6, _7, _8, xs...
      >::value>
      ::template f<7, Pred, _2, _3, _4, _5, _6, _7, _8, xs...>
      ::template f<_drop_while_xs<n_8_or_less_16_32_64_128_256(remaining-8), true>,
                   remaining-8, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)                                               \
  template<>                                                                        \
  struct _drop_while_xs<n, true>                                                    \
  {                                                                                 \
    template<                                                                       \
      std::size_t remaining,                                                        \
      class Pred,                                                                   \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),                                          \
      class... xs>                                                                  \
    using f = typename _drop_while_xs<m, true>                                      \
      ::template f<m, Pred, xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), xs...>        \
      ::template f<_drop_while_xs<n_8_or_less_16_32_64_128_256(remaining-m), true>, \
                   remaining-m, Pred, xs...>;                                       \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond