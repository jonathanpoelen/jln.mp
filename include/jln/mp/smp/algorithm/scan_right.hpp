#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/algorithm/reverse.hpp>
#include <jln/mp/algorithm/scan_right.hpp>
#include <jln/mp/functional/monadic.hpp>

namespace jln::mp::smp
{
  template<class F, class C = listify>
  using scan_right = contract<mp::scan_right<
    monadic_xs<assume_binary<F>>,
    monadic_xs<subcontract<C>>
  >>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, scan_right<F, C>>
  {
    using type = smp::scan_right<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
