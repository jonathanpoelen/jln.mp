// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/circulant_matrix.hpp>
#include <jln/mp/smp/algorithm/transform.hpp>
#include <jln/mp/smp/utility/unpack.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/list/is_list.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/algorithm/all_of.hpp>
#include <jln/mp/algorithm/same.hpp>
#include <jln/mp/algorithm/zip.hpp>

namespace jln::mp::smp
{
  template<class F = listify, class C = listify>
  using zip_with = test_contract<
    mp::all_of<mp::is_list<>>,
    mp::if_<
      mp::transform<mp::unpack<mp::size<>>, mp::same<>>,
      mp::zip_with<assume_unary_or_more<F>, detail::smp_listify_or_monadic_xs<F, C>>,
      violation
    >
  >;

  template<class C = listify>
  using zip = zip_with<listify, C>;

}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, zip_with<F, C>>
  {
    using type = smp::zip_with<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
