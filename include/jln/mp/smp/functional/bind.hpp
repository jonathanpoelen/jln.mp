#pragma once

#include "identity.hpp"
#include "../../functional/bind.hpp"
#include "../../utility/same_as.hpp"
#include "../../list/front.hpp"

namespace jln::mp::smp
{
  template<class F, class C>
  using bind1st = try_contract<mp::bind1st<
    try_subcontract<F>,
    mp::if_<mp::front<mp::same_as<na>>, violation, subcontract<C>>
  >>;

  // flip<bind1st, flip<C>>
  template<class F, class C>
  using bind2nd = try_contract<mp::bind2nd<
    try_subcontract<F>,
    mp::if_<mp::front<mp::same_as<na>>, violation, subcontract<C>>
  >>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, bind1st<F, C>>
  {
    using type = smp::bind1st<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, bind2nd<F, C>>
  {
    using type = smp::bind2nd<sfinae<F>, sfinae<C>>;
  };
}
