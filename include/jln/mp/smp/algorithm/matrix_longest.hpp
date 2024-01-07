// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/matrix_longest.hpp>
#include <jln/mp/detail/smp_listify_or_monadic_xs.hpp>

namespace jln::mp::smp
{
  template<class FillValue, class F = listify, class C = listify>
  using left_matrix_longest_with = try_contract<mp::left_matrix_longest_with<
    FillValue, subcontract<F>,
    typename detail::smp_listify_or_monadic_xs<F>::template f<C>
  >>;

  template<class FillValue, class C = listify>
  using left_matrix_longest = try_contract<mp::left_matrix_longest_with<
    FillValue, mp::listify, assume_lists<C>>>;

  template<class FillValue, class F = listify, class C = listify>
  using right_matrix_longest_with = try_contract<mp::right_matrix_longest_with<
    FillValue, subcontract<F>,
    typename detail::smp_listify_or_monadic_xs<F>::template f<C>
  >>;

  template<class FillValue, class C = listify>
  using right_matrix_longest = try_contract<mp::right_matrix_longest_with<
    FillValue, mp::listify, assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class FillValue, class F, class C>
  struct _sfinae<sfinae, left_matrix_longest_with<FillValue, F, C>>
  {
    using type = smp::left_matrix_longest_with<FillValue, sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class FillValue, class F, class C>
  struct _sfinae<sfinae, right_matrix_longest_with<FillValue, F, C>>
  {
    using type = smp::right_matrix_longest_with<FillValue, sfinae<F>, sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT3(argument_category::lists, left_matrix_longest_with);
  JLN_MP_MAKE_EXPECTED_ARGUMENT3(argument_category::lists, right_matrix_longest_with);
}
/// \endcond
