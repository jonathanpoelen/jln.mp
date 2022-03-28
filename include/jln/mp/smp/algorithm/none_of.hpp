#pragma once

#include <jln/mp/smp/algorithm/drop_until.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/algorithm/none_of.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using none_of = drop_until<Pred, always<false_, C>, always<true_, C>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, none_of<Pred, C>>
  {
    using type = smp::none_of<sfinae<Pred>, sfinae<C>>;
  };
}
/// \endcond

