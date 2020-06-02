#pragma once

#include "../functional/identity.hpp"
#include "../../functional/monadic.hpp"
#include "../../functional/if.hpp"
#include "../../list/size.hpp"
#include "../../utility/always.hpp"
#include "../../list/pop_front.hpp"
#include "../../algorithm/same.hpp"
#include "../../algorithm/fold_left.hpp"
#include "../../algorithm/transform.hpp"
#include "../../algorithm/accumulate.hpp"

/// \cond
namespace jln::mp::detail
{
  template<class F, class C>
  struct _smp_accumulate;
}
/// \endcond

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using accumulate = test_contract<
    mp::if_<
      mp::size<>,
      mp::pop_front<
        mp::if_<
          mp::size<>,
          mp::transform<
            try_<mp::unpack<mp::size<>>>,
            mp::monadic0<mp::same<>, mp::always<mp::false_>>
          >,
          mp::always<mp::true_>
        >
      >
    >,
    detail::_smp_accumulate<subcontract<F>, assume_unary<C>>>;
}

/// \cond
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
    using f = call<zip<push_front<state, fold_left<
      monadic0<flip<unpack<F>>>, monadic<C>
    >>>, seqs...>;
  };
}
/// \endcond
