#pragma once

#include "../functional/identity.hpp"
#include "../../functional/monadic.hpp"
#include "../../algorithm/all_of.hpp"

namespace jln::mp
{
  namespace smp
  {
    template<class Pred, class C = identity>
    using all_of = valid_contract<
      monadic_xs<Pred, mp::all_of<identity, subcontract<C>>>>;
  }
} // namespace jln::mp


namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, all_of<Pred, C>>
  {
    using type = smp::all_of<sfinae<Pred>, sfinae<C>>;
  };
}
