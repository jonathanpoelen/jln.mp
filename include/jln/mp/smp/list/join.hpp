#pragma once

#include "list.hpp"
#include "../algorithm/all_of.hpp"
#include "../../list/join.hpp"

namespace jln::mp::detail
{
  template<class> struct _is_join_param : false_ {};
}

namespace jln::mp::smp
{
  template<class C = listify>
  using join = contract<
    mp::all_of<mp::cfe<detail::_is_join_param>>,
    mp::join<subcontract<C>>>;
}


namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, join<C>>
  {
    using type = smp::join<sfinae<C>>;
  };

  template<template<class...> class Tpl, class... xs>
  struct _is_join_param<Tpl<xs...>>
  : true_
  {};
} // namespace jln::mp::detail
