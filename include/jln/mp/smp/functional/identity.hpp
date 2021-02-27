#pragma once

#include <jln/mp/smp/functional//sfinaefwd.hpp>
#include <jln/mp/smp/assume.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/try.hpp>

namespace jln::mp::smp
{
  using identity = try_contract<mp::identity>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, identity>
  {
    using type = smp::identity;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT(argument_category::unary, (), (identity));
}
/// \endcond
