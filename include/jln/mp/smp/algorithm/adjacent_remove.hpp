#pragma once

#include "same.hpp"
#include "../list/listify.hpp"
#include "../../functional/monadic.hpp"
#include "../../algorithm/adjacent_remove.hpp"

namespace jln::mp::smp
{
  template<class BinaryPred, class C = listify>
  using adjacent_remove_if = try_contract<mp::adjacent_remove_if<
    assume_binary<BinaryPred>, subcontract<C>>>;

  template<class C = listify>
  using adjacent_remove = contract<mp::adjacent_remove<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class BinaryPred, class C>
  struct _sfinae<sfinae, adjacent_remove_if<BinaryPred, C>>
  {
    using type = smp::adjacent_remove_if<sfinae<BinaryPred>, sfinae<C>>;
  };
}
/// \endcond
