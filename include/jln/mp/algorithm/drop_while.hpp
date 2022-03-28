#pragma once

#include <jln/mp/list/clear.hpp>
#include <jln/mp/list/listify.hpp>
#include <jln/mp/list/drop_front.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool not_found = true>
    struct _drop_while;

    template<class>
    struct to_drop_upto;

    template<class>
    struct drop_while_impl;
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
    >::template f<TC, FC, xs...>;
  };

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_while = drop_while<Pred, drop_front_c<1, TC>, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_while = unpack<L, mp::drop_while<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_inclusive_while = unpack<L, mp::drop_inclusive_while<Pred, TC, FC>>;
  }

  /// \cond
  template<class Pred, class TC, class FC>
  struct drop_while<Pred, drop_front_c<1, TC>, FC>
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::to_drop_upto<
        typename detail::_drop_while<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type
    >::template f<TC, FC, xs...>;
  };
  /// \endcond
}


#include <jln/mp/detail/enumerate.hpp>
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
    template<class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(FC, xs...);
  };

  template<std::size_t n>
  struct drop_while_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, class... xs>
    using f = typename drop_front_c<sizeof...(xs)-n-1, TC>::template f<xs...>;
  };


  template<>
  struct to_drop_upto<_drop_while_continue>
  {
    using type = _drop_while_continue;
  };

  template<std::size_t n>
  struct to_drop_upto<_drop_while_result<n>>
  {
    using type = _drop_while_result<n-1>;
  };


  // _drop_while<n, b> = _drop_until<n, !b>

  template<int n>
  struct _drop_while<n, true> : _drop_while<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256,
    true
  >
  {};

  struct drop_while_impl_false
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_result<consumed+sizeof...(xs)>;
  };

#define JLN_DROP_WHILE_IMPL(n, m)                                    \
  template<>                                                         \
  struct _drop_while<n, true>                                        \
  {                                                                  \
    template<std::size_t consumed, class Pred, class x, class... xs> \
    using f = typename _drop_while<m, Pred::template f<x>::value>    \
            ::template f<consumed, Pred, xs...>;                     \
  };                                                                 \
                                                                     \
  template<>                                                         \
  struct _drop_while<n, false> : drop_while_impl_false               \
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
  struct _drop_while<0, true>
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_continue;
  };

  template<>
  struct _drop_while<0, false>
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_result<consumed+sizeof...(xs)>;
  };

  template<>
  struct _drop_while<8, true>
  {
    template<
      std::size_t consumed,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_while<7, Pred::template f<_1>::value>
      ::template f<
          consumed+sizeof...(xs), Pred,
          _2, _3, _4, _5, _6, _7, _8>;
  };

  template<>
  struct _drop_while<16, true>
  {
    template<
      std::size_t consumed,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_while<7, Pred::template f<_1>::value>
      ::template f<
          consumed+sizeof...(xs), Pred,
          _2, _3, _4, _5, _6, _7, _8>
      ::template f<
          _drop_while<sizeof...(xs), true>,
          consumed, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)               \
  template<>                                        \
  struct _drop_while<n, true>                       \
  {                                                 \
    template<                                       \
      std::size_t consumed,                         \
      class Pred,                                   \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),          \
      class... xs>                                  \
    using f = typename _drop_while<m, true>         \
      ::template f<                                 \
          consumed+sizeof...(xs), Pred,             \
          xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)> \
      ::template f<                                 \
          _drop_while<sizeof...(xs), true>,         \
          consumed, Pred, xs...>;                   \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond
