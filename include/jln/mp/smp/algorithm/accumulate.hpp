#pragma once

#include "../functional/identity.hpp"
#include "../algorithm/fold_left.hpp"
#include "../../functional/monadic.hpp"
#include "../../functional/if.hpp"
#include "../../list/is_list.hpp"
#include "../../list/size.hpp"
#include "../../list/pop_front.hpp"
#include "../../algorithm/all_of.hpp"
#include "../../algorithm/accumulate.hpp"
#include "../../number/operators.hpp"

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using accumulate = test_contract<
    mp::if_<
      mp::size<>,
      mp::pop_front<mp::all_of<mp::is_list<>>>>,
    // TODO detail::_accumulate<smp::fold_left<F, C>>
    mp::accumulate<
      mp::monadic0<subcontract<F>>,
      mp::monadic<subcontract<C>>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, accumulate<F, C>>
  {
    using type = smp::accumulate<sfinae<F>, sfinae<C>>;
  };
}
