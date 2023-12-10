// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/list/lookup.hpp>

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct smp_build_indexed;
}
/// \endcond

namespace jln::mp::smp
{
  template<class... xs>
  using build_indexed = typename detail::smp_build_indexed<sizeof...(xs) <= 16>
    ::template f<xs...>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, build_indexed<xs...>>
  {
    using type = smp::build_indexed<xs...>;
  };


  template<>
  struct smp_build_indexed<true>
  {
    template<class... xs>
    using f = try_contract<mp::build_indexed<xs...>>;
  };

  template<bool, unsigned long long n>
  struct check_build_indexed_index2
  {
    template<class i>
    using f = number<0 <= i::value && static_cast<unsigned long long>(i::value) < n>;
  };

  template<unsigned long long n>
  struct check_build_indexed_index2<false, n> : always<false_>
  {};

  template<unsigned long long n>
  struct check_build_indexed_index
  {
    template<class... i>
    using f = typename check_build_indexed_index2<sizeof...(i) == 1, n>
      ::template f<i...>;
  };

  template<>
  struct smp_build_indexed<false>
  {
    template<class... xs>
    using f = test_contract<check_build_indexed_index<sizeof...(xs)>, mp::build_indexed<xs...>>;
  };
}
/// \endcond
