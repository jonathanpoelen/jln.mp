// SPDX-FileCopyrightText: 2025 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/unique.hpp>
#include <jln/mp/algorithm/unique_by.hpp>
#include <jln/mp/smp/algorithm/none_of.hpp>

/// \cond
namespace jln::mp::detail
{
  struct is_not_unique_by_kv_entry;

  template<class KeyF, class C, class CC = unique_by_kv<C>>
  struct smp_unique_by;
}
/// \endcond

namespace jln::mp::smp
{
  template<class KeyF, class C = listify>
  using unique_by = try_contract<detail::smp_unique_by<assume_unary<KeyF>, subcontract<C>>>;

  template<class C = listify>
  using unique_by_kv = test_contract<
    mp::none_of<detail::is_not_unique_by_kv_entry>,
    mp::unique_by_kv<subcontract<C>>
  >;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class KeyF, class C>
  struct _sfinae<sfinae, unique_by<KeyF, C>>
  {
    using type = smp::unique_by<sfinae<KeyF>, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unique_by<smp::identity, C>>
  {
    using type = smp::unique<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unique_by<identity, C>>
  {
    using type = smp::unique<sfinae<C>>;
  };


  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unique_by_kv<C>>
  {
    using type = smp::unique_by_kv<sfinae<C>>;
  };


  struct is_not_unique_by_kv_entry
  {
    template<class>
    struct f : true_
    {};

    template<class k, class v>
    struct f<unique_by_kv_entry<k, v>> : false_
    {};
  };


#if JLN_MP_FEATURE_CONCEPTS
  template<not_same_as_na... k>
  struct smp_unique_by_impl
  {
    template<class C, class... v>
    using f = typename C::template f<unique_by_kv_entry<k, v>...>;
  };
#else
  template<class... k>
  struct smp_unique_by_impl
  {
    struct dispatch
    {
      template<class C, class... v>
      using f = typename C::template f<unique_by_kv_entry<k, v>...>;
    };

    using impl = JLN_MP_CONDITIONAL_C_T(JLN_MP_NONE_SAME_AS(na, k), dispatch, na);
  };
#endif

  template<class KeyF, class, class C>
  struct smp_unique_by
  {
    template<class... xs>
    using f = typename smp_unique_by_impl<JLN_MP_CALL_TRACE(KeyF, xs)...>
#if !JLN_MP_FEATURE_CONCEPTS
      ::impl
#endif
      ::template f<C, xs...>;
  };
}
/// \endcond
