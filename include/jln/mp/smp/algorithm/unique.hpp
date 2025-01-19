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
  using unique = contract<mp::unique_if<mp::same<>, subcontract<C>>>;

  template<class Cmp = same<>, class C = listify>
  using unique_if = detail::sfinae<mp::unique_if<
    assume_binary_barrier<Cmp>, subcontract_barrier<C>>>;
}

#include <jln/mp/smp/algorithm/none_of.hpp>
#include <jln/mp/smp/utility/unpack.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unique_if<same<>, C>>
  {
    using type = smp::unique<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unique_if<smp::same<>, C>>
  {
    using type = smp::unique<sfinae<C>>;
  };

  template<class Cmp>
  struct smp_set_cmp_push_back
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
    using type = unpack<C>;
  };

  template<>
  struct smp_unique_if_continuation<listify>
  {
    using type = contract<mp::identity>;
  };

  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, unique_if<Cmp, C>>
  {
    using type = contract<
      unique_if_impl<
        list<>,
        smp::fold<
          contract<unpack<try_<smp_set_cmp_push_back<
            JLN_MP_TRACE_F(assume_binary<sfinae<Cmp>>)
          >>>>,
          typename smp_unique_if_continuation<
            sfinae<C>
          >::type
        >
      >
    >;
  };
}
/// \endcond
