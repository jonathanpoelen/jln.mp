#pragma once

#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/utility/unpack.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C = listify>
    struct _zip;
  }
  /// \endcond

  /// \ingroup group

  /// n-ary version of transform.
  /// \pre all parameters must be \lists
  /// \pre all lists must be the same size
  /// \semantics
  ///   \code
  ///   zip<listify>::f<
  ///     list<_1, _2, _3>,
  ///     list<_a, _b, _c>
  ///   > = list<
  ///     list<_1, _a>,
  ///     list<_2, _b>,
  ///     list<_3, _c>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  template<class C = listify>
  using zip = detail::_zip<detail::optimize_useless_transform_unpack_t<C>>;

  template<class F = listify, class C = listify>
  using zip_with = zip<transform<unpack<F>, C>>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using zip = unpack<L, mp::zip<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using zip_with = unpack<L, mp::zip_with<F, C>>;
  }
}

#include <jln/mp/detail/enumerate.hpp>
#include <jln/mp/list/join.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class...>
  struct _zip_impl;

#define JLN_MP_TRANSPOSE_IMPL(n, mp_xs, mp_rxs, mp_rep)        \
  template<class C, mp_xs(class..., JLN_MP_NIL, JLN_MP_COMMA)> \
  struct _zip_impl<C, mp_xs(list<, ...>, JLN_MP_COMMA)>        \
  {                                                            \
    using type = JLN_MP_CALL_TRACE(C, list<                  \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)              \
    >...);                                                     \
  };                                                           \
                                                               \
  template<class F, class C,                                   \
    mp_xs(class..., JLN_MP_NIL, JLN_MP_COMMA)>                 \
  struct _zip_impl<                                            \
    transform<unpack<F>, C>, mp_xs(list<, ...>, JLN_MP_COMMA)> \
  {                                                            \
    using type = JLN_MP_CALL_TRACE(C, JLN_MP_CALL_TRACE(F, \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)              \
    )...);                                                     \
  };

  JLN_MP_GEN_XS_1_TO_8_INCLUDED(JLN_MP_TRANSPOSE_IMPL)

#undef JLN_MP_TRANSPOSE_IMPL

  template<int>
  struct _zip_dispatch;

  template<class C>
  struct _zip
  {
    template<class... seqs>
    using f = typename _zip_dispatch<
      sizeof...(seqs) ? (sizeof...(seqs) > 8 ? 2 : 1) : 0
    >::template f<C, seqs...>;
  };

  template<>
  struct _zip_dispatch<0>
  {
    template<class C>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  template<>
  struct _zip_dispatch<1>
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
  struct _zip_dispatch<2>
  {
    template<class C, class... seqs>
    using f = typename _recursive_zip<
      (sizeof...(seqs) >= 8 ? 8 : sizeof...(seqs))
    >::template f<sizeof...(seqs)-8, C, seqs...>;
  };
}
/// \endcond
