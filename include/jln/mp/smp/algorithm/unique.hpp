// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/algorithm/same.hpp>
#include <jln/mp/smp/algorithm/fold.hpp>
#include <jln/mp/smp/utility/unpack.hpp>
#include <jln/mp/smp/functional/lift.hpp>
#include <jln/mp/smp/list/push_front.hpp>
#include <jln/mp/smp/list/pop_front.hpp>
#include <jln/mp/algorithm/unique.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using unique = detail::sfinae<mp::unique<subcontract_barrier<C>>>;

  template<class Cmp = same<>, class C = listify>
  using unique_if = detail::sfinae<mp::unique_if<
    assume_binary_barrier<Cmp>, subcontract_barrier<C>>>;
}

#include <jln/mp/smp/algorithm/none_of.hpp>
#include <jln/mp/smp/utility/unpack.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class C>
  struct smp_unique_continuation
  {
    using type = C;
  };

  template<>
  struct smp_unique_continuation<try_<unpack<listify>>>
  {
    using type = mp::identity;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, push_front<list<>, fold<lift<emp::set_push_back>, C>>>
  {
    using type = contract<push_front<list<>, fold<
      lift<emp::set_push_back>, typename smp_unique_continuation<
        assume_unary<sfinae<C>>
      >::type
    >>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, push_front<list<>, fold<
    unpack<_set_cmp_push_back<JLN_MP_TRACE_F(smp::same<>)>>, C
  >>>
  {
    using type = contract<push_front<list<>, fold<
      lift<emp::set_push_back>, typename smp_unique_continuation<
        assume_unary<optimize_useless_unpack_t<sfinae<C>>>
      >::type
    >>>;
  };

  template<class Cmp>
  struct _smp_set_cmp_push_back
  {
    template<class x, class... xs>
    using f = JLN_MP_CONDITIONAL_P_C_T(
      (smp::none_of<contract<push_back<x, Cmp>>>
      ::template f<xs...>::value),
      (list<xs..., x>),
      (list<xs...>)
    );
  };

  template<class C>
  struct smp_unique_if_continuation
  {
    using type = C;
  };

  template<>
  struct smp_unique_if_continuation<try_<unpack<listify>>>
  {
    using type = contract<mp::identity>;
  };

  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, push_front<list<>, fold<
    unpack<_set_cmp_push_back<JLN_MP_TRACE_F(Cmp)>>, C
  >>>
  {
    using type = contract<push_front<list<>, smp::fold<
      contract<unpack<try_<_smp_set_cmp_push_back<
        JLN_MP_TRACE_F(assume_binary<sfinae<Cmp>>)
      >>>>,
      typename smp_unique_if_continuation<
        assume_unary<sfinae<C>>
      >::type
    >>>;
  };
}
/// \endcond
