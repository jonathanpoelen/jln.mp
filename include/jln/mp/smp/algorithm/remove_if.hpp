#pragma once

#include "transform.hpp"
#include "../list/join.hpp"
#include "../../algorithm/remove_if.hpp"

namespace jln::mp::smp
{
  template<class Pred>
  using list_wrap_if = try_contract<mp::list_wrap_if<subcontract<Pred>>>;

  template<class Pred, class C = listify>
  using remove_if = valid_contract<mp::transform<
    try_invoke<mp::list_wrap_if<subcontract<Pred>>>,
    mp::monadic_xs<mp::join<subcontract<C>>>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred>
  struct _sfinae<sfinae, list_wrap_if<Pred>>
  {
    using type = smp::list_wrap_if<sfinae<Pred>>;
  };
}
