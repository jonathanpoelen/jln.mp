#pragma once

#include "../functional/identity.hpp"
#include "../../list/is_list.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using is_list = try_contract<mp::is_list<assume_number<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_list<C>>
  {
    using type = smp::is_list<sfinae<C>>;
  };

  template<class C>
  struct expected_argument<is_list<C>>
  : number<argument_category::unary>
  {};
}
