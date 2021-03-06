#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool found>
    struct _drop_while;

    template<class>
    struct drop_while_impl;

    constexpr unsigned _drop_while_select(unsigned n);
  }
  /// \endcond

  /// \ingroup list

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// \treturn \sequence
  template<class Pred, class C = listify>
  struct drop_while
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::_drop_while<
        detail::_drop_while_select(sizeof...(xs)), true
      >::template f<0, Pred, xs...>
    >::template f<C, xs...>;
  };

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using drop_while = unpack<L, mp::drop_while<Pred, C>>;
  }
}


#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/detail/enumerate.hpp>

/// \cond
namespace jln::mp::detail
{
  template<std::size_t n>
  struct _drop_while_result
  {
    template<class C, std::size_t truncated, class Pred, class... xs>
    using f = _drop_while_result;
  };

  struct _drop_while_continue
  {
    template<class C, std::size_t truncated, class Pred, class... xs>
    using f = typename C::template f<truncated, Pred, xs...>;
  };

  template<>
  struct drop_while_impl<_drop_while_continue>
  {
    template<class C, class...>
    using f = typename C::template f<>;
  };

  template<std::size_t n>
  struct drop_while_impl<_drop_while_result<n>>
  {
    template<class C, class... xs>
    using f = typename drop_front<number<sizeof...(xs)-n-1>, C>::template f<xs...>;
  };

  constexpr unsigned _drop_while_select(unsigned n)
  {
    return n <= 8 ? n
         : n <= 16 ? 16
         : n <= 32 ? 32
         : n <= 64 ? 64
         : n <= 128 ? 128
         : 256;
  }

#define JLN_DROP_WHILE_IMPL(n, m)                                     \
  template<>                                                          \
  struct _drop_while<n, true>                                         \
  {                                                                   \
    template<std::size_t truncated, class Pred, class x, class... xs> \
    using f = typename _drop_while<m, Pred::template f<x>::value>     \
            ::template f<truncated, Pred, xs...>;                     \
  };                                                                  \
                                                                      \
  template<>                                                          \
  struct _drop_while<n, false>                                        \
  {                                                                   \
    template<std::size_t truncated, class Pred, class... xs>          \
    using f = _drop_while_result<truncated+sizeof...(xs)>;            \
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
  struct _drop_while<0, true>
  {
    template<std::size_t truncated, class Pred, class... xs>
    using f = _drop_while_continue;
  };

  template<>
  struct _drop_while<0, false>
  {
    template<std::size_t truncated, class Pred, class... xs>
    using f = _drop_while_result<truncated+sizeof...(xs)>;
  };

  template<>
  struct _drop_while<8, true>
  {
    template<
      std::size_t truncated,
      class Pred,
      JLN_MP_XS_8(class, JLN_MP_NIL, JLN_MP_COMMA),
      class... xs>
    using f = typename _drop_while<7, Pred::template f<_1>::value>
      ::template f<
          truncated+sizeof...(xs), Pred,
          JLN_MP_XS_2_TO_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>;
  };

  template<>
  struct _drop_while<16, true>
  {
    template<
      std::size_t truncated,
      class Pred,
      JLN_MP_XS_8(class, JLN_MP_NIL, JLN_MP_COMMA),
      class... xs>
    using f = typename _drop_while<7, Pred::template f<_1>::value>
      ::template f<
          truncated+sizeof...(xs), Pred,
          JLN_MP_XS_2_TO_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>
      ::template f<
          _drop_while<_drop_while_select(sizeof...(xs)), true>,
          truncated, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)                           \
  template<>                                                    \
  struct _drop_while<n, true>                                   \
  {                                                             \
    template<                                                   \
      std::size_t truncated,                                    \
      class Pred,                                               \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),                      \
      class... xs>                                              \
    using f = typename _drop_while<m, true>                     \
      ::template f<                                             \
          truncated+sizeof...(xs), Pred,                        \
          xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>             \
      ::template f<                                             \
          _drop_while<_drop_while_select(sizeof...(xs)), true>, \
          truncated, Pred, xs...>;                              \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond
