#pragma once

#include "identity.hpp"
#include "../utility/always.hpp"
#include "../../functional/fork_front.hpp"
#include "../../functional/if.hpp"

namespace jln::mp::smp
{
  // TODO optimize if_<size_of<x>, size_of<y>, size_of<z>>
  template<class Pred, class TC, class FC = always<false_>>
  using if_ = valid_contract<
    mp::fork_front<
      mp::try_invoke<
        subcontract<Pred>,
        mp::try_invoke<
          mp::if_<
            mp::identity,
            mp::always<subcontract<TC>>,
            mp::always<subcontract<FC>>
          >,
          mp::identity,
          mp::always<violation>
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
