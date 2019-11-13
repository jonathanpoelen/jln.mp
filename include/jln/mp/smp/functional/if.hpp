#pragma once

#include "identity.hpp"
#include "../utility/always.hpp"
#include "../../functional/fork_front.hpp"
#include "../../functional/if.hpp"
#include "../../functional/fork.hpp"
#include "../../number/as_number.hpp"

namespace jln::mp::smp
{
  template<class Pred, class TC, class FC = always<false_>>
  using if_ = valid_contract<
    mp::fork_front<
      mp::try_invoke<
        // TODO output_type<Pred> = number -> if_<subcontract<Pred>, ....>
        mp::fork<subcontract<Pred>, mp::as_number<>>,
        mp::if_<
          mp::identity,
          mp::always<subcontract<TC>>,
          mp::always<subcontract<FC>>
        >,
        mp::always<violation>
      >
    >
  >;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, if_<Pred, TC, FC>>
  {
    using type = smp::if_<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}