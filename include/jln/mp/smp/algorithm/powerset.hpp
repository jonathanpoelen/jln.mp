#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/powerset.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using powerset = contract<mp::powerset<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, powerset<C>>
  {
    using type = smp::powerset<sfinae<C>>;
  };
}
/// \endcond
