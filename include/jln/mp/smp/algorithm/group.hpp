#pragma once

#include "same.hpp"
#include "../list/list.hpp"
#include "../../functional/monadic.hpp"
#include "../../algorithm/group.hpp"

namespace jln::mp::smp
{
  template<class Cmp, class C = listify>
  using group_if = try_contract<mp::group_if<
    subcontract<Cmp>, subcontract<C>>>;

  template<class C = listify>
  using group = valid_contract<mp::group<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, group_if<Cmp, C>>
  {
    using type = smp::group_if<sfinae<Cmp>, sfinae<C>>;
  };
}