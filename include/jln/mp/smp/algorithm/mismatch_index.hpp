#pragma once

#include "mismatch.hpp"
#include "../list/at.hpp"
#include "../utility/always.hpp"
#include "../utility/same_as.hpp"
#include "../functional/lift.hpp"
#include "../functional/identity.hpp"
#include "../functional/invoke_twice.hpp"
#include "../../algorithm/mismatch_index.hpp"

namespace jln::mp::smp
{
  template<class Cmp = equal<>, class C = identity>
  using mismatch_index = mismatch<
    Cmp,
    mp::at0<assume_number<C>>,
    mp::if_<
      mp::at0<mp::same_as<number<-1>>>,
      mp::at1<assume_number<C>>,
      mp::at0<assume_number<C>>
    >
  >;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, mismatch<Cmp, at0<C>, if_<at0<same_as<number<-1>>>, at1<C>, at0<C>>>>
  {
    using type = smp::mismatch_index<sfinae<Cmp>, sfinae<C>>;
  };
}
