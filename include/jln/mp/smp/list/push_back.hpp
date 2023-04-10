#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/push_back.hpp>

namespace jln::mp::smp
{
  template<class x, class C = listify>
  using push_back = contract<mp::push_back<x, assume_unary_or_more<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, push_back<x, C>>
  {
    using type = smp::push_back<x, sfinae<C>>;
  };
}
/// \endcond
