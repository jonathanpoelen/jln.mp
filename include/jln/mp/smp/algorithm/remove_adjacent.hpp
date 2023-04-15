#pragma once

#include <jln/mp/smp/algorithm/same.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/algorithm/remove_adjacent.hpp>

namespace jln::mp::smp
{
  template<class BinaryPred, class C = listify>
  using remove_adjacent_if = try_contract<mp::remove_adjacent_if<
    assume_binary<BinaryPred>, subcontract<C>>>;

  template<class C = listify>
  using remove_adjacent = contract<mp::remove_adjacent<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class BinaryPred, class C>
  struct _sfinae<sfinae, remove_adjacent_if<BinaryPred, C>>
  {
    using type = smp::remove_adjacent_if<sfinae<BinaryPred>, sfinae<C>>;
  };
}
/// \endcond
