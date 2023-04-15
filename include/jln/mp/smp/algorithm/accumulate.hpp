#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/algorithm/same.hpp>
#include <jln/mp/algorithm/fold.hpp>
#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/algorithm/accumulate.hpp>

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
    detail::_smp_accumulate<assume_binary<F>, assume_unary<C>>>;
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
    using f = typename zip<push_front<state, fold<
      monadic0<flip<unpack<F>>>, monadic<C>
    >>>::template f<seqs...>;
  };
}
/// \endcond
