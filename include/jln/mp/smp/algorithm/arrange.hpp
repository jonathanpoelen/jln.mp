// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/contract.hpp>
#include <jln/mp/algorithm/arrange.hpp>
#include <jln/mp/detail/first.hpp>

/// \cond
namespace jln::mp::detail
{
  struct arrange_to_smp_arrange;

#if ! JLN_MP_HAS_MEMOIZED_PACK_AT
  template<int>
  struct smp_arrange_c;

  template<class... T>
  constexpr int max_idx_arrange(T... n);
#endif
}
/// \endcond

namespace jln::mp::smp
{
  template<class Ints, class C = listify>
  using arrange = typename mp::try_<
    detail::make_arrange<Ints>,
    detail::arrange_to_smp_arrange,
    mp::always<detail::first<bad_contract, 1>>
  >::template f<C>::type;

#if JLN_MP_HAS_MEMOIZED_PACK_AT
  template<int... ints>
  using arrange_c = try_contract<mp::arrange_c_with<mp::listify, ints...>>;

  template<class C, int... ints>
  using arrange_c_with = try_contract<mp::arrange_c_with<subcontract<C>, ints...>>;
#else
  template<int... ints>
  using arrange_c = typename detail::smp_arrange_c<detail::max_idx_arrange(ints...)>
    ::template make<listify, ints...>;

  template<class C, int... ints>
  using arrange_c_with = typename detail::smp_arrange_c<detail::max_idx_arrange(ints...)>
    ::template make<C, ints...>;
#endif
}


#include <jln/mp/list/clear.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C, int... ints>
  struct _sfinae<sfinae, arrange_c_with<C, ints...>>
  {
    using type = smp::arrange_c_with<sfinae<C>, ints...>;
  };

#if ! JLN_MP_HAS_MEMOIZED_PACK_AT
  template<class... T>
  constexpr int max_idx_arrange(T... n)
  {
    int r = -1; // empty list

    if constexpr (sizeof...(n) > 0) {
      r = 0;
      int a[]{n...};
      for (int n : a) {
        if (n < 0) {
          return -2; // negative index
        }
        if (n > r) {
          r = n;
        }
      }
    }

    return r; // r >= 0
  }

  template<int n>
  struct smp_arrange_c
  {
    template<class... xs>
    using f = number<n < sizeof...(xs)>;

    template<class C, int... ns>
    using make = test_contract<
      smp_arrange_c,
      arrange_c_with<subcontract<C>, ns...>
    >;
  };

  // no index
  template<>
  struct smp_arrange_c<-1>
  {
    template<class C, int...>
    using make = contract<mp::clear<subcontract<C>>>;
  };

  // index with negative value
  template<>
  struct smp_arrange_c<-2>
  {
    template<class C, int...>
    using make = bad_contract;
  };
#endif

  struct arrange_to_smp_arrange
  {
    template<class>
    struct f
    {
      using type = bad_contract;
    };

    template<class C, int... ints>
    struct f<arrange_c_with<C, ints...>>
    {
#if JLN_MP_HAS_MEMOIZED_PACK_AT
      using type = try_contract<arrange_c_with<subcontract<C>, ints...>>;
#else
      using type = typename detail::smp_arrange_c<detail::max_idx_arrange(ints...)>
        ::template make<C, ints...>;
#endif
    };
  };
}
/// \endcond
