// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/same.hpp>
#include <jln/mp/algorithm/is_unique.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Cmp, class C>
  struct mk_smp_is_unique_if;
}

namespace jln::mp::smp
{
  template<class C = identity>
  using is_unique = contract<mp::is_unique<assume_positive_number<C>>>;

  template<class Cmp = same<>, class C = identity>
  using is_unique_if = typename detail::mk_smp_is_unique_if<
    assume_binary<Cmp>, assume_positive_number<C>>::type;
}


#include <jln/mp/smp/algorithm/none_of.hpp>
#include <jln/mp/smp/algorithm/fold.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct smp_is_unique_set_cmp_push_back_or_void
  {
    template<class x, class... xs>
    using f = JLN_MP_CONDITIONAL_P_C_T(
      (smp::none_of<contract<push_back<x, Cmp>>>::template f<xs...>::value),
      (list<xs..., x>),
      (void)
    );
  };

  template<class Cmp, class C>
  struct smp_is_unique_if_impl
    : push_front<
        list<>,
        smp::fold<
          contract<is_unique_unpack<try_<smp_is_unique_set_cmp_push_back_or_void<Cmp>>>>,
          contract<is_not<void, C>>
        >
      >
  {};

  template<class Cmp, class C>
  struct mk_smp_is_unique_if
  {
    using type = contract<smp_is_unique_if_impl<Cmp, C>>;
  };

  template<class C>
  struct mk_smp_is_unique_if<same<>, C>
  {
    using type = contract<mp::is_unique<C>>;
  };


  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, is_unique_if<Cmp, C>>
  {
    using type = smp::is_unique_if<sfinae<Cmp>, sfinae<C>>;
  };
}
/// \endcond
