#pragma once

#include "same.hpp"
#include "../list/list.hpp"
#include "../../functional/monadic.hpp"
#include "../../algorithm/remove_adjacent.hpp"

namespace jln::mp::smp
{
  template<class BinaryPred, class C = listify>
  using remove_adjacent_if = try_contract<mp::remove_adjacent_if<
    assume_binary<BinaryPred>, subcontract<C>>>;

  template<class C = listify>
  using remove_adjacent = contract<mp::remove_adjacent<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class BinaryPred, class C>
  struct _sfinae<sfinae, remove_adjacent_if<BinaryPred, C>>
  {
    using type = smp::remove_adjacent_if<sfinae<BinaryPred>, sfinae<C>>;
  };
}
