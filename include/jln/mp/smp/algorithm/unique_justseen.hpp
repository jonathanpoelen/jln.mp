#pragma once

#include <jln/mp/smp/algorithm/same.hpp>
#include <jln/mp/smp/algorithm/group.hpp>
#include <jln/mp/algorithm/unique_justseen.hpp>

namespace jln::mp::smp
{
  template<class Cmp, class C = listify>
  using unique_justseen_by = group_by<Cmp, contract<
      mp::transform<mp::unpack<mp::front<>>, subcontract<C>>>>;

  template<class C = listify>
  using unique_justseen = unique_justseen_by<same<>, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, unique_justseen_by<Cmp, C>>
  {
    using type = smp::unique_justseen_by<sfinae<Cmp>, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unique_justseen_by<same<>, C>>
  {
    using type = smp::unique_justseen<sfinae<C>>;
  };
}
/// \endcond
