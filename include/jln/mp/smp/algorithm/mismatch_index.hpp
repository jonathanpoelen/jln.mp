#pragma once

#include <jln/mp/smp/algorithm/mismatch.hpp>
#include <jln/mp/smp/list/at.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/smp/functional/lift.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/functional/invoke_twice.hpp>
#include <jln/mp/algorithm/mismatch_index.hpp>

namespace jln::mp::smp
{
  template<class Cmp = equal<>, class C = identity>
  using mismatch_index = mismatch<
    Cmp,
    mp::at0<assume_number<C>>,
    mp::if_<
      mp::at0<mp::is<number<-1>>>,
      mp::at1<assume_number<C>>,
      mp::at0<assume_number<C>>
    >
  >;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, mismatch<Cmp, at0<C>, if_<at0<is<number<-1>>>, at1<C>, at0<C>>>>
  {
    using type = smp::mismatch_index<sfinae<Cmp>, sfinae<C>>;
  };
}
