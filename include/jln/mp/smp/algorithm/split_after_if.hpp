#pragma once

#include "../list/list.hpp"
#include "../algorithm/transform.hpp"
#include "../utility/always.hpp"
#include "../../functional/monadic.hpp"
#include "../../algorithm/split_after_if.hpp"

namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using split_after_if = contract<
    mp::transform<
      try_invoke<Pred, same_as<na>, mp::always<false_>>,
      or_<not_<>>>,
    mp::split_after_if<subcontract<Pred>, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, split_after_if<F, C>>
  {
    using type = smp::split_after_if<sfinae<F>, sfinae<C>>;
  };
}
