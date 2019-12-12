#pragma once

#include "../concepts.hpp"
#include "../list/list.hpp"
#include "../utility/same_as.hpp"
#include "../functional/identity.hpp"
#include "../../list/front.hpp"
#include "../../algorithm/lower_bound.hpp"

namespace jln::mp::smp
{
  template<class Pred, class C = listify, class NC = C>
  using lower_bound = valid_contract<
    mp::lower_bound<Pred, subcontract<C>, subcontract<NC>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C, class NC>
  struct _sfinae<sfinae, lower_bound<Pred, C, NC>>
  {
    using type = smp::lower_bound<sfinae<Pred>, sfinae<C>, sfinae<NC>>;
  };
}
