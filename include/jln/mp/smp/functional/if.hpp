#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/smp/number/to_bool.hpp>
#include <jln/mp/functional/invoke_twice.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/number/as_number.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC, class FC = always<false_>>
  using if_ = contract<
    mp::invoke_twice<
      mp::try_<
        subcontract<Pred>,
        mp::try_<
          mp::to_bool<>,
          mp::if_<
            mp::identity,
            mp::always<subcontract<TC>>,
            mp::always<subcontract<FC>>
          >,
          mp::always<violation>
        >,
        mp::always<violation>
      >
    >
  >;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, if_<Pred, TC, FC>>
  {
    using type = smp::if_<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
