#pragma once

#include "transform.hpp"
#include "../list/list.hpp"
#include "../utility/eager.hpp"


namespace jln::mp
{
  namespace detail
  {
    template<int>
    struct _zip;

    struct _drop_back;
  }

  template<class C = listify>
  struct zip
  {
    template<class... seqs>
    using f = typename detail::_zip<
      sizeof...(seqs) ? (sizeof...(seqs) > 8 ? 2 : 1) : 0
    >::template f<C, seqs...>;
  };

  template<class C>
  struct zip<transform<unpack<listify>, C>>
  : zip<C>
  {};

  template<class F = listify, class C = listify>
  using zip_with = zip<transform<unpack<F>, C>>;

  template<class C = listify>
  struct zip_shortest
  {
    template<class... xs>
    using f = typename transform<
      call<transform<unpack<size<>>, detail::_drop_back>, xs...>,
      zip<C>
    >::template f<xs...>;
  };

  template<class C>
  struct zip_shortest<transform<unpack<listify>, C>>
  : zip_shortest<C>
  {};

  template<class F = listify, class C = listify>
  using zip_shortest_with = zip_shortest<transform<unpack<F>, C>>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using zip = eager<L, mp::zip<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using zip_with = eager<L, mp::zip_with<F, C>>;

    template<class L, class C = mp::listify>
    using zip_shortest = eager<L, mp::zip_shortest<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using zip_shortest_with = eager<L, mp::zip_shortest_with<F, C>>;
  }
}

#include "../config/enumerate.hpp"
#include "../utility/same_as.hpp"
#include "../list/join.hpp"
#include "../list/take.hpp"
#include <algorithm>

namespace jln::mp::detail
{
  template<class...>
  struct _zip_impl;

#define JLN_MP_TRANSPOSE_IMPL(n, mp_xs, mp_rxs, mp_rep)         \
  template<class C, mp_xs(class..., JLN_MP_NIL, JLN_MP_COMMA)>  \
  struct _zip_impl<C, mp_xs(list<, ...>, JLN_MP_COMMA)>         \
  {                                                             \
    using type = typename C::template f<list<                   \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)               \
    >...>;                                                      \
  };                                                            \
                                                                \
  template<class F, class C,                                    \
    mp_xs(class..., JLN_MP_NIL, JLN_MP_COMMA)>                  \
  struct _zip_impl<                                             \
    transform<unpack<F>, C>, mp_xs(list<, ...>, JLN_MP_COMMA)>  \
  {                                                             \
    using type = typename C::template f<typename F::template f< \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)               \
    >...>;                                                      \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_TRANSPOSE_IMPL)
  JLN_MP_TRANSPOSE_IMPL(8, JLN_MP_XS_8, _, _)

#undef JLN_MP_TRANSPOSE_IMPL

  template<>
  struct _zip<0>
  {
    template<class C>
    using f = typename C::template f<>;
  };

  template<>
  struct _zip<1>
  {
    template<class C, class... seqs>
    using f = typename _zip_impl<C, seqs...>::type;
  };

  template<int>
  struct _recursive_zip
  {
    template<int n, class C,
      class _0, class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class... seqs>
    using f = typename _recursive_zip<(n >= 8 ? 8 : n)>
      ::template f<
        n-8, C, seqs..., typename _zip_impl<listify,
          _0, _1, _2, _3, _4, _5, _6, _7>::type
      >;
  };

  template<>
  struct _recursive_zip<0>
  {
    template<int, class C, class... seqs>
    using f = typename zip<transform<unpack<join<>>, C>>
      ::template f<seqs...>;
  };

#define JLN_MP_TRANSPOSE_IMPL(n, mp_xs, mp_rxs, mp_rep)      \
  template<>                                                 \
  struct _recursive_zip<n>                                   \
  {                                                          \
    template<int, class C                                    \
      mp_xs(JLN_MP_COMMA class, JLN_MP_NIL, JLN_MP_NIL),     \
      class... seqs>                                         \
    using f = typename zip<transform<unpack<join<>>, C>>     \
      ::template f<seqs..., typename _zip_impl<listify,      \
        mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>::type>; \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_TRANSPOSE_IMPL)

#undef JLN_MP_TRANSPOSE_IMPL

  template<>
  struct _zip<2>
  {
    template<class C, class... seqs>
    using f = typename _recursive_zip<
      (sizeof...(seqs) >= 8 ? 8 : sizeof...(seqs))
    >::template f<sizeof...(seqs)-8, C, seqs...>;
  };

  struct _drop_back
  {
    template<class n>
    using impl = unpack<if_<size<same_as<n>>, listify, take<n>>>;

    template<class... ns>
    using f = impl<number<std::min({int_(~0u), ns::value...})>>;
  };
}
