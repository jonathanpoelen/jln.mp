#pragma once

#include <jln/mp/smp/algorithm/same.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/group.hpp>

namespace jln::mp::smp
{
  template<class Cmp, class C = listify>
  using group_by = try_contract<mp::group_by<
    try_assume_binary<Cmp>, assume_lists<C>>>;

  template<class C = listify>
  using group = contract<mp::group<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, group_by<Cmp, C>>
  {
    using type = smp::group_by<sfinae<Cmp>, sfinae<C>>;
  };
}
/// \endcond
