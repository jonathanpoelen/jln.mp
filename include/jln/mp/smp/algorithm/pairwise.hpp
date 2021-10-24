#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/pairwise.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using pairwise = contract<pairwise<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, pairwise<C>>
  {
    using type = smp::pairwise<sfinae<C>>;
  };
}
/// \endcond
