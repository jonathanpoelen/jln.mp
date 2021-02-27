#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/number/numbers.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using numbers = contract<mp::numbers<assume_numbers<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, numbers<C>>
  {
    using type = smp::numbers<sfinae<C>>;
  };
}
/// \endcond
