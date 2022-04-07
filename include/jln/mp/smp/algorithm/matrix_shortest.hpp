#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/contract.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/algorithm/matrix_shortest.hpp>

namespace jln::mp::smp
{
  template<class F = listify, class C = listify>
  using left_matrix_shortest_with = try_contract<
    mp::left_matrix_shortest_with<subcontract<F>, monadic_xs<subcontract<C>>>>;

  template<class C = listify>
  using left_matrix_shortest = left_matrix_shortest_with<listify, assume_lists_barrier<C>>;

  template<class F = listify, class C = listify>
  using right_matrix_shortest_with = try_contract<
    mp::right_matrix_shortest_with<subcontract<F>, monadic_xs<subcontract<C>>>>;

  template<class C = listify>
  using right_matrix_shortest = right_matrix_shortest_with<listify, assume_lists_barrier<C>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, left_matrix_shortest_with<F, C>>
  {
    using type = smp::left_matrix_shortest_with<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, right_matrix_shortest_with<F, C>>
  {
    using type = smp::right_matrix_shortest_with<sfinae<F>, sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT2(argument_category::lists, left_matrix_shortest_with);
  JLN_MP_MAKE_EXPECTED_ARGUMENT2(argument_category::lists, right_matrix_shortest_with);
}
/// \endcond
