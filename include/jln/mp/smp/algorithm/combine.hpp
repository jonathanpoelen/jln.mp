#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/combine.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using combine = contract<mp::combine<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, combine<C>>
  {
    using type = smp::combine<sfinae<C>>;
  };
}
/// \endcond
