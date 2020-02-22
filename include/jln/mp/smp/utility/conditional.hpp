#pragma once

#include "../../utility/conditional.hpp"
#include "../../functional/contract.hpp"
#include "../../functional/sfinaefwd.hpp"

namespace jln::mp::smp
{
  template<bool b>
  using conditional_c = valid_contract<mp::try_invoke<mp::conditional_c<b>>>;
}

JLN_MP_MAKE_REGULAR_SMP1_P(conditional, (x), smp::conditional_c<bool(x::value)>)

namespace jln::mp::detail
{
  template<template<class> class sfinae, bool b>
  struct _sfinae<sfinae, conditional_c<b>>
  {
    using type = smp::conditional_c<b>;
  };
}
