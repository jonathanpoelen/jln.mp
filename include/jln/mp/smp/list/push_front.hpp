#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/push_front.hpp>

namespace jln::mp::smp
{
  template<class x, class C = listify>
  using push_front = contract<mp::push_front<x, assume_unary_or_more<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, push_front<x, C>>
  {
    using type = smp::push_front<x, sfinae<C>>;
  };
}
/// \endcond
