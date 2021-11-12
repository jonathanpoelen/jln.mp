#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/group_by_type.hpp>


namespace jln::mp::smp
{
  template<class C = listify>
  using group_by_type = contract<mp::group_by_type<assume_lists<C>>>;

  template<class F = listify, class C = listify>
  using group_by_type_with = try_contract<mp::group_by_type_with<F, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, group_by_type<C>>
  {
    using type = smp::group_by_type<sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, group_by_type_with<F, C>>
  {
    using type = smp::group_by_type_with<sfinae<F>, sfinae<C>>;
  };
}
