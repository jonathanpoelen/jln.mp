#pragma once

#include "../functional/identity.hpp"
#include "../../number/is_number.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using is_number = try_contract<
    // TODO when_C_or_identity
    // when<mp::size_of_1<>, C> -> C
    // when<mp::alway<true_>, identity> -> identity
    // identity -> identity
    mp::is_number<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_number<C>>
  {
    using type = smp::is_number<sfinae<C>>;
  };
}
