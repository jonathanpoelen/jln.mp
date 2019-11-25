#pragma once

#include "../list/list.hpp"
#include "../../list/size.hpp"
#include "../../list/is_list.hpp"
#include "../../functional/if.hpp"
#include "../../number/operators.hpp"
#include "../../algorithm/same.hpp"
#include "../../algorithm/transform.hpp"
#include "../../algorithm/transpose.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using transpose = contract<
    mp::if_<
      mp::transform<mp::is_list<>, mp::and_<>>,
      mp::transform<mp::unpack<mp::size<>>, mp::same<>>
    >,
    mp::transpose<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, transpose<C>>
  {
    using type = smp::transpose<sfinae<C>>;
  };
}
