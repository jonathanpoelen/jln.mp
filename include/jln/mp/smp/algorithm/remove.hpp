#pragma once

#include "transform.hpp"
#include "../list/join.hpp"
#include "../utility/same_as.hpp"
#include "../../algorithm/remove.hpp"


namespace jln::mp::smp
{
  template<class Pred>
  using list_wrap_if = try_contract<
    mp::list_wrap_if<try_subcontract<Pred>>>;

  template<class Pred, class C = listify>
  using remove_if = valid_contract<mp::transform<
    subcontract<list_wrap_if<Pred>>,
    mp::monadic_xs<mp::join<subcontract<C>>>>>;

  template<class x, class C = listify>
  using remove = valid_contract<mp::remove<x, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred>
  struct _sfinae<sfinae, list_wrap_if<Pred>>
  {
    using type = smp::list_wrap_if<sfinae<Pred>>;
  };
}
