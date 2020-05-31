#pragma once

#include "../contract.hpp"
#include "../list/listify.hpp"
#include "../../algorithm/flatten.hpp"

namespace jln::mp::smp
{
  template<class S = mp::lift<list>, class C = listify>
  using flatten = try_contract<mp::flatten<S, subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class S, class C>
  struct _sfinae<sfinae, flatten<S, C>>
  {
    using type = smp::flatten<S, sfinae<C>>;
  };
}
/// \endcond
