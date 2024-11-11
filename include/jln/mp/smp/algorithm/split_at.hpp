// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/split_at.hpp>
#include <type_traits> // std::void_t

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_smp_split_at;

  template<class>
  struct is_listify_parameter;

  template<class, class>
  struct assume_binary_list_or_not;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_t i, class SubC1 = listify, class SubC2 = SubC1, class C = listify>
  using split_at2_with_c = typename detail::mk_smp_split_at<i >= 0>
    ::template f<
      i,
      typename detail::assume_binary_list_or_not<
        typename detail::is_listify_parameter<SubC1>::type,
        typename detail::is_listify_parameter<SubC2>::type
      >::template f<C>,
      mp::split_at2_with_c,
      subcontract<SubC1>,
      subcontract<SubC2>
    >;

  template<int_t i, class F = listify, class C = listify>
  using split_at_with_c = typename detail::mk_smp_split_at<i >= 0>
    ::template f<
      i,
      typename detail::assume_binary_list_or_not<
        typename detail::is_listify_parameter<F>::type,
        true_
      >::template f<C>,
      mp::split_at_with_c,
      subcontract<F>
    >;

  template<int_t i, class C = listify>
  using split_at_c = typename detail::mk_smp_split_at<i >= 0>
    ::template f<i, assume_binary_list<C>, mp::split_at2_with_c, mp::listify, mp::listify>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(split_at2_with,
  (I), (SubC1, smp::listify), (SubC2, smp::listify), (C, smp::listify),
  smp::split_at2_with_c<I::value, SubC1, SubC2, C>)

namespace jln::mp::smp
{
  template<class I, class C = listify>
  using split_at = split_at2_with<I, listify, listify, C>;

  template<class I, class F = listify, class C = listify>
  using split_at_with = split_at2_with<I, F, F, C>;
}

#include <jln/mp/number/operators.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, unsigned i, class SubC1, class SubC2, class C>
  struct _sfinae<sfinae, split_at2_with_c<i, SubC1, SubC2, C>>
  {
    using type = smp::split_at2_with_c<i, sfinae<SubC1>, sfinae<SubC2>, sfinae<C>>;
  };

  template<template<class> class sfinae, unsigned i, class C>
  struct _sfinae<sfinae, split_at2_with_c<i, listify, listify, C>>
  {
    using type = smp::split_at_c<i, sfinae<C>>;
  };


  template<class>
  struct is_listify_parameter
  {
    using type = false_;
  };

  template<>
  struct is_listify_parameter<listify>
  {
    using type = true_;
  };

  template<>
  struct is_listify_parameter<smp::listify>
  {
    using type = true_;
  };


  template<class, class>
  struct assume_binary_list_or_not
  {
    template<class C> using f = subcontract<C>;
  };

  template<>
  struct assume_binary_list_or_not<true_, true_>
  {
    template<class C> using f = assume_binary_list<C>;
  };


  template<>
  struct mk_smp_split_at<true>
  {
    template<int_t i, class C, template<unsigned, class...> class Tpl, class... F>
    using f = test_contract<
      mp::size<mp::greater_equal_than_c<i>>,
      Tpl<i, F..., C>>;
  };

  template<>
  struct mk_smp_split_at<false>
  {
    template<int_t i, class C, template<unsigned, class...> class Tpl, class... F>
    using f = bad_contract;
  };
}
/// \endcond
