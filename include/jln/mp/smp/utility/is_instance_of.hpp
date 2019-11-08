#pragma once

#include "../functional/identity.hpp"
#include "../../utility/is_instance_of.hpp"

namespace jln::mp::smp
{
  template<template<class...> class Tpl, class C = identity>
  using is_instance_of = try_contract<mp::is_instance_of<Tpl, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, template<class...> class Tpl, class C>
  struct _sfinae<sfinae, is_instance_of<Tpl, C>>
  {
    using type = smp::is_instance_of<Tpl, sfinae<C>>;
  };
}
