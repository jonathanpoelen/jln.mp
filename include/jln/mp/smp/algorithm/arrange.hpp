#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/arrange.hpp>
#include <jln/mp/algorithm/none_of.hpp>
#include <jln/mp/functional/if.hpp>

namespace jln::mp::smp
{
  template<class Ints, class C = listify>
  using arrange = try_contract<
    mp::arrange<Ints, if_<none_of<is<detail::unindexed>>, subcontract<C>, violation>>
  >;

  template<unsigned... ints>
  using arrange_c = arrange<int_seq_v<ints...>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Ints, class C>
  struct _sfinae<sfinae, arrange<Ints, C>>
  {
    using type = smp::arrange<Ints, sfinae<C>>;
  };
}
/// \endcond
