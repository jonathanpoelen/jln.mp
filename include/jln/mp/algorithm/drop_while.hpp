#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/detail/enumerate.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool not_found>
    struct _drop_while;

    template<class>
    struct drop_while_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// \treturn \sequence
  /// \see drop_front, drop_back, take_while
  template<class Pred, class C = listify>
  struct drop_while
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::_drop_while<
        detail::n_8_or_less_16_32_64_128_256(sizeof...(xs)), true
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
  struct _drop_while<n, false>                                       \
  {                                                                  \
    template<std::size_t consumed, class Pred, class... xs>          \
    using f = _drop_while_result<consumed+sizeof...(xs)>;            \
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
      JLN_MP_XS_8(class, JLN_MP_NIL, JLN_MP_COMMA),
      class... xs>
    using f = typename _drop_while<7, Pred::template f<_1>::value>
      ::template f<
          consumed+sizeof...(xs), Pred,
          JLN_MP_XS_2_TO_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>;
  };

  template<>
  struct _drop_while<16, true>
  {
    template<
      std::size_t consumed,
      class Pred,
      JLN_MP_XS_8(class, JLN_MP_NIL, JLN_MP_COMMA),
      class... xs>
    using f = typename _drop_while<7, Pred::template f<_1>::value>
      ::template f<
          consumed+sizeof...(xs), Pred,
          JLN_MP_XS_2_TO_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>
      ::template f<
          _drop_while<n_8_or_less_16_32_64_128_256(sizeof...(xs)), true>,
          consumed, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)                                     \
  template<>                                                              \
  struct _drop_while<n, true>                                             \
  {                                                                       \
    template<                                                             \
      std::size_t consumed,                                               \
      class Pred,                                                         \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),                                \
      class... xs>                                                        \
    using f = typename _drop_while<m, true>                               \
      ::template f<                                                       \
          consumed+sizeof...(xs), Pred,                                   \
          xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>                       \
      ::template f<                                                       \
          _drop_while<n_8_or_less_16_32_64_128_256(sizeof...(xs)), true>, \
          consumed, Pred, xs...>;                                         \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond
