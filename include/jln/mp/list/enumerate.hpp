// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/list/listify.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct enumerate_impl;

    template<class, int_t...>
    struct enumerate_v_impl;
  }
  /// \endcond


  /// \ingroup list

  /// Returns pairs containing a numeric index of type \c int_t and a value.
  /// \semantics
  ///   \code
  ///   C::f<F::f<0, xs[0]>, ..., F::f<n, xs[n]>>
  ///   \endcode
  /// \treturn \sequence
  template<class F, class C = listify>
  struct enumerate_v_with
  {
    template<class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), detail::enumerate_v_impl)
      ::template f<F, JLN_MP_TRACE_F(C), xs...>;
  };

  /// Returns pairs containing an index and a value.
  /// \semantics
  ///   \code
  ///   C::f<F::f<number<0>, xs[0]>, ..., F::f<number<n>, xs[n]>>
  ///   \endcode
  /// \treturn \sequence
  template<class F = listify, class C = listify>
  struct enumerate_with
  {
    template<class... xs>
    using f = typename detail::enumerate_impl<emp::make_int_sequence_c<sizeof...(xs)>>
      ::template f<JLN_MP_TRACE_F(F)::template f, JLN_MP_TRACE_F(C), xs...>;
  };

  template<class C = listify>
  using enumerate = enumerate_with<listify, C>;

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using enumerate_v_with = unpack<L, mp::enumerate_v_with<F, C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using enumerate_with = unpack<L, mp::enumerate_with<F, C>>;

    template<class L, class C = mp::listify>
    using enumerate = unpack<L, mp::enumerate_with<mp::listify, C>>;
  }
} // namespace jln::mp


/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS
namespace jln::mp
{
  template<template<class...> class F, class C>
  struct enumerate_with<lift<F>, C>
  {
    template<class... xs>
    using f = typename detail::enumerate_impl<emp::make_int_sequence_c<sizeof...(xs)>>
      ::template f<F, JLN_MP_TRACE_F(C), xs...>;
  };
}
#endif

namespace jln::mp::detail
{
  template<class... ns>
  struct enumerate_impl<list<ns...>>
  {
    template<template<class...> class F, class C, class... xs>
    using f = typename C::template f<F<ns, xs>...>;
  };

  template<class, int_t... i>
  struct enumerate_v_impl
  {
    template<class F, class C, class... xs>
    using f = typename C::template f<typename F::template f<i, xs>...>;
  };
}
/// \endcond
