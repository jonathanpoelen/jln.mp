#pragma once

#include "../list/list.hpp"
#include "../config/enumerate.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<int>
    struct _transpose;
  }

  template<class C = listify>
  struct transpose
  {
    template<class... xs>
    using f = typename detail::_transpose<
      sizeof...(xs) ? (sizeof...(xs) > 8 ? 2 : 1) : 0
    >::template f<C, xs...>;
  };

  template<>
  struct transpose<listify>
  {
    template<class... xs>
    using f = typename detail::_transpose<
      sizeof...(xs) ? (sizeof...(xs) > 8 ? 2 : 11) : 10
    >::template f<listify, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using transpose = eager<L, mp::transpose<C>>;
  }
}

#include "transform.hpp"
#include "group_n.hpp"
#include "../list/join.hpp"

namespace jln::mp::detail
{
  template<class...>
  struct _transpose_impl;

  template<class...>
  struct _transpose_impl_l;

#define JLN_MP_TRANSPOSE_IMPL(n, mp_xs, mp_rxs, mp_rep)      \
  template<mp_xs(class..., JLN_MP_NIL, JLN_MP_COMMA)>        \
  struct _transpose_impl<mp_xs(list<, ...>, JLN_MP_COMMA)>   \
  {                                                          \
    template<class C>                                        \
    using f = typename C::template f<list<                   \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)            \
    >...>;                                                   \
    using type = list<list<                                  \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)            \
    >...>;                                                   \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_TRANSPOSE_IMPL)
  JLN_MP_TRANSPOSE_IMPL(8, JLN_MP_XS_8, _, _)

#undef JLN_MP_TRANSPOSE_IMPL

  template<>
  struct _transpose<0>
  {
    template<class C>
    using f = typename C::template f<>;
  };

  template<>
  struct _transpose<1>
  {
    template<class C, class... xs>
    using f = typename _transpose_impl<xs...>::template f<C>;
  };

  template<>
  struct _transpose<10>
  {
    template<class>
    using f = list<>;
  };

  template<>
  struct _transpose<11>
  {
    template<class, class... xs>
    using f = typename _transpose_impl<xs...>::type;
  };

  template<>
  struct _transpose<2>
  {
    template<class C, class... xs>
    using f = typename _group_n<true>
      ::template f<
        transform<
          // TODO cfl<_transpose_impl, cfe<call>> + remove _transpose_impl::type ?
          unpack<cfl<_transpose_impl>>,
          transpose<transform<unpack<join<>>, C>>
        >,
        8, xs...>;
  };

}
