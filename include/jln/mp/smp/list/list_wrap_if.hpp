#pragma once

#include "../../functional/try_invoke.hpp"
#include "../../list/list_wrap_if.hpp"

namespace jln::mp::smp
{
  template<class Pred>
  using list_wrap_if = try_contract<
    mp::list_wrap_if<try_subcontract<Pred>>>;

  template<class Pred>
  using list_wrap_if_not = try_contract<
    mp::list_wrap_if_not<try_subcontract<Pred>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred>
  struct _sfinae<sfinae, _list_wrap_if<Pred>>
  {
    using type = smp::list_wrap_if<sfinae<Pred>>;
  };

  template<template<class> class sfinae, class Pred>
  struct _sfinae<sfinae, _list_wrap_if_not<Pred>>
  {
    using type = smp::list_wrap_if_not<sfinae<Pred>>;
  };
}