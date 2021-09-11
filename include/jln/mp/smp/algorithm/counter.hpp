#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/counter.hpp>


namespace jln::mp::smp
{
  template<class C = listify>
  using counter = contract<mp::counter<assume_lists<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, counter<C>>
  {
    using type = smp::counter<sfinae<C>>;
  };
}
