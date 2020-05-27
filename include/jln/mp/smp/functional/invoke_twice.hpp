#pragma once

#include "../contract.hpp"
#include "../../functional/lift.hpp"
#include "../../functional/invoke_twice.hpp"

namespace jln::mp::smp
{
  template<class F>
  using invoke_twice = contract<mp::invoke_twice<mp::try_subcontract<
    F, mp::lift<try_subcontract>, mp::always<mp::violation>>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F>
  struct _sfinae<sfinae, invoke_twice<F>>
  {
    using type = smp::invoke_twice<sfinae<F>>;
  };
}
/// \endcond
