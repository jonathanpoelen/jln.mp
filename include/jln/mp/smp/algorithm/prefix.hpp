#pragma once

#include <jln/mp/algorithm/prefix.hpp>
#include <jln/mp/smp/list/listify.hpp>

namespace jln::mp::smp
{
  template<class x, class C = listify>
  using prefix = contract<mp::prefix<x, subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, prefix<x, C>>
  {
    using type = smp::prefix<x, sfinae<C>>;
  };
}
/// \endcond
