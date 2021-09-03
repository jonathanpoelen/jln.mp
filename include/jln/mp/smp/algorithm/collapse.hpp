#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/assume.hpp>
#include <jln/mp/algorithm/collapse.hpp>

namespace jln::mp::smp
{
  template<class Keys, class C = listify>
  using collapse = try_contract<collapse<Keys, assume_lists<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Keys, class C>
  struct _sfinae<sfinae, collapse<Keys, C>>
  {
    using type = smp::collapse<Keys, sfinae<C>>;
  };
}
/// \endcond
