#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/list/listify.hpp>

namespace jln::mp::smp
{
  using listify = contract<mp::listify>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, listify>
  {
    using type = smp::listify;
  };
}

#include <jln/mp/smp/optimizer/optimizer.hpp>

namespace jln::mp::optimizer
{
  template<class params>
  struct optimizer_impl<listify, params>
  {
    using type = optimized_result<list_t<params>, listify>;
  };
}
/// \endcond
