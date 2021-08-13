#pragma once

#include <jln/mp/list/front.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/smp/number/as_bool.hpp>
#include <jln/mp/algorithm/drop_while.hpp>
#include <jln/mp/algorithm/conjunction.hpp>
#include <jln/mp/smp/contract.hpp>


namespace jln::mp::smp
{
  template<class C = identity>
  using conjunction = contract<mp::drop_while<
    try_<mp::as_bool<>, mp::identity, mp::always<false_>>,
    mp::if_<
      mp::if_<
        mp::size<>,
        mp::front<try_<mp::as_bool<>, mp::always<true_>, mp::always<false_>>>,
        mp::always<true_>
      >,
      mp::is_empty<subcontract<C>>,
      violation
    >
  >>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, conjunction<C>>
  {
    using type = smp::conjunction<sfinae<C>>;
  };
}
/// \endcond
