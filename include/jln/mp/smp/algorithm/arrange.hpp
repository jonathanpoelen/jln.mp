// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/contract.hpp>
#include <jln/mp/algorithm/arrange.hpp>
#include <jln/mp/detail/type_identity.hpp>
#include <initializer_list>

/// \cond
namespace jln::mp::detail
{
  template<int>
  struct smp_arrange_c;

  struct arrange_to_smp_arrange;

  constexpr int max_idx_arrange(std::initializer_list<int> l);
}
/// \endcond

namespace jln::mp::smp
{
  template<class Ints, class C = listify>
  using arrange = typename try_<
    detail::make_arrange<Ints>,
    detail::arrange_to_smp_arrange,
    mp::always<detail::type_identity<bad_contract>>
  >::template f<C>::type;

  template<int... ints>
  using arrange_c = typename detail::smp_arrange_c<detail::max_idx_arrange({ints...})>
    ::template make<listify, ints...>;

  template<class C, int... ints>
  using arrange_c_with = typename detail::smp_arrange_c<detail::max_idx_arrange({ints...})>
    ::template make<C, ints...>;
}

/// \cond
#include <jln/mp/list/clear.hpp>

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C, int_... ints>
  struct _sfinae<sfinae, apply_indexed_v<arrange_impl<C, ints...>>>
  {
    using type = smp::arrange_c_with<sfinae<C>, ints...>;
  };

  constexpr int max_idx_arrange(std::initializer_list<int> l)
  {
    if (l.size() == 0) {
      return -1; // no index
    }

    int r = 0;
    for (int n : l) {
      if (n < 0) {
        return -2; // negative index
      }
      if (n > r) {
        r = n;
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
      detail::apply_indexed_v<detail::arrange_impl<subcontract<C>, ns...>>
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

  struct arrange_to_smp_arrange
  {
    template<class>
    struct f
    {
      using type = bad_contract;
    };

    template<class C, int... ints>
    struct f<apply_indexed_v<arrange_impl<C, ints...>>>
    {
      using type = typename detail::smp_arrange_c<detail::max_idx_arrange({ints...})>
        ::template make<C, ints...>;
    };
  };
}
/// \endcond
