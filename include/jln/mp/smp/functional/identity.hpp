#pragma once

#include "sfinaefwd.hpp"
#include "../assume.hpp"
#include "../../functional/identity.hpp"
#include "../../functional/try_invoke.hpp"

namespace jln::mp::smp
{
  using identity = try_contract<mp::identity>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, identity>
  {
    using type = smp::identity;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT(argument_category::unary, (), (identity));
}
