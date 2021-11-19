#pragma once

#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/smp/number/to_bool.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/algorithm/disjunction.hpp>


namespace jln::mp::smp
{
  template<class C = identity>
  using disjunction = contract<mp::if_<
    mp::size<>,
    mp::drop_while<
      try_<mp::to_bool<mp::not_<>>, mp::identity, mp::always<false_>>,
      mp::if_<
        mp::if_<
          mp::size<>,
          mp::front<try_<mp::to_bool<>, mp::always<true_>, mp::always<false_>>>,
          mp::always<true_>
        >,
        mp::size<mp::to_bool<subcontract<C>>>,
        violation
      >
    >,
    always<false_, subcontract<C>>
  >>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, disjunction<C>>
  {
    using type = smp::disjunction<sfinae<C>>;
  };
}
/// \endcond
