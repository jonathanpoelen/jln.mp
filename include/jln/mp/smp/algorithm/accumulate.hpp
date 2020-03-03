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

namespace jln::mp::detail
{
  template<class F, class C>
  struct _smp_accumulate;
}

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using accumulate = test_contract<
    mp::if_<
      mp::size<>,
      mp::pop_front<mp::all_of<mp::is_list<>>>>,
    detail::_smp_accumulate<subcontract<F>, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, accumulate<F, C>>
  {
    using type = smp::accumulate<sfinae<F>, sfinae<C>>;
  };

  template<class F, class C>
  struct _smp_accumulate
  {
    template<class state, class... seqs>
    using f = call<join<push_front<state,
      mp::fold_left<mp::monadic0<F>, mp::monadic<C>>>>, seqs...>;
  };
}
