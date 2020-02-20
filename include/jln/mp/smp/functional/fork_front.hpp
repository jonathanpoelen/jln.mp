#pragma once

#include "../../functional/contract.hpp"
#include "../../functional/function.hpp"
#include "../../functional/fork_front.hpp"

namespace jln::mp::smp
{
  template<class F>
  using fork_front = valid_contract<mp::fork_front<mp::try_subcontract<
    F, mp::cfe<try_subcontract>, mp::always<mp::violation>>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F>
  struct _sfinae<sfinae, fork_front<F>>
  {
    using type = smp::fork_front<sfinae<F>>;
  };
}
