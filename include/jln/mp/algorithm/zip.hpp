#pragma once

#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/utility/unpack.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _zip_dispatch;
  }
  /// \endcond

  /// \ingroup group

  /// Turns rows into columns, and columns into rows.
  /// This is similar to transposing a matrix.
  /// \pre all parameters must be \lists
  /// \pre all lists must be the same size
  /// \semantics
  ///   \code
  ///   zip<>::f<
  ///     list<_1, _2, _3>,
  ///     list<_a, _b, _c>
  ///   > = list<
  ///     list<_1, _a>,
  ///     list<_2, _b>,
  ///     list<_3, _c>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see zip_longest
  template<class F = listify, class C = listify>
  struct zip_with
  {
    template<class... seqs>
    using f = typename detail::_zip_dispatch<
      sizeof...(seqs) ? sizeof...(seqs) <= 8 ? 1 : 2 : 0
    >::template f<
      JLN_MP_TRACE_F(C)::template f,
      JLN_MP_TRACE_F(F)::template f,
      seqs...
    >;
  };

  template<class C = listify>
  using zip = zip_with<listify, C>;

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

#define JLN_MP_TRANSPOSE_IMPL(n, mp_xs, mp_rxs, mp_rep)              \
  template<mp_xs(class..., JLN_MP_NIL, JLN_MP_COMMA)>                \
  struct _zip_impl<mp_xs(list<, ...>, JLN_MP_COMMA)>                 \
  {                                                                  \
    template<template<class...> class C, template<class...> class F> \
    using f = C<F<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>...>;  \
  };

  JLN_MP_GEN_XS_1_TO_8_INCLUDED(JLN_MP_TRANSPOSE_IMPL)

#undef JLN_MP_TRANSPOSE_IMPL

  template<>
  struct _zip_dispatch<0>
  {
    template<template<class...> class C, template<class...> class F>
    // using f = JLN_MP_CALL_TRACE_0_ARG(C);
    using f = C<>;
  };

  template<>
  struct _zip_dispatch<1>
  {
    template<template<class...> class C, template<class...> class F, class... seqs>
    using f = typename _zip_impl<seqs...>::template f<C, F>;
  };

  template<int>
  struct _recursive_zip;

  template<>
  struct _recursive_zip<0>
  {
    template<int n, template<class...> class C, template<class...> class F, class... seqs>
    using f = typename detail::_zip_dispatch<
      sizeof...(seqs) <= 8 ? 1 : 2
    >::template f<C, F, seqs...>;
  };

#define JLN_MP_TRANSPOSE_IMPL(n, mp_xs, mp_rxs, mp_rep)                  \
  template<>                                                             \
  struct _recursive_zip<n>                                               \
  {                                                                      \
    template<int, template<class...> class C, template<class...> class F \
      mp_xs(JLN_MP_COMMA class, JLN_MP_NIL, JLN_MP_NIL),                 \
      class... seqs>                                                     \
    using f = typename detail::_zip_dispatch<                            \
      sizeof...(seqs) < 8 ? 1 : 2                                        \
    >::template f<C, join<lift<F>>::template f, seqs...,                 \
        typename _zip_impl<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>  \
        ::template f<list, list>                                         \
      >;                                                                 \
  };

  template<>
  struct _recursive_zip<8>
  {
    template<int n, template<class...> class C, template<class...> class F,
      class _0, class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class... seqs>
    using f = typename _recursive_zip<n < 8 ? n : 8>
      ::template f<
        n-8, C, F, seqs..., typename _zip_impl<
          _0, _1, _2, _3, _4, _5, _6, _7
        >::template f<list, list>
      >;
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_TRANSPOSE_IMPL)

#undef JLN_MP_TRANSPOSE_IMPL

  template<>
  struct _zip_dispatch<2>
  {
    template<template<class...> class C, template<class...> class F, class... seqs>
    using f = typename _recursive_zip<!sizeof...(seqs) + 8>
      ::template f<sizeof...(seqs)-8, C, F, seqs...>;
  };
}
/// \endcond
