#pragma once

#include "../functional/identity.hpp"
#include "../algorithm/fold_left.hpp"
#include "../../functional/monadic.hpp"
#include "../../functional/if.hpp"
#include "../../list/is_list.hpp"
#include "../../list/size.hpp"
#include "../../list/pop_front.hpp"
#include "../../algorithm/transform.hpp"
#include "../../algorithm/accumulate.hpp"
#include "../../number/operators.hpp"

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using accumulate = contract<
    mp::if_<
      mp::size<>,
      mp::pop_front<mp::transform<mp::is_list<>, mp::and_<>>>>,
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