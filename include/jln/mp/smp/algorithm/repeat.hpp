#pragma once

#include "../list/list.hpp"
#include "../../algorithm/repeat.hpp"

namespace jln::mp::smp
{
  template<class N, class C = listify>
  using repeat = try_contract<mp::repeat<N, subcontract<C>>>;

  template<int_ n, class C = listify>
  using repeat_c = repeat<mp::number<n>, C>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, repeat<N, C>>
  {
    using type = smp::repeat<N, sfinae<C>>;
  };
}
