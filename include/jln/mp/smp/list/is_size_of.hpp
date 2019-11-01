#pragma once

#include "../functional/identity.hpp"
#include "../../list/is_size_of.hpp"

namespace jln::mp::smp
{
  template<class N, class C = identity>
  using is_size_of = valid_contract<mp::is_size_of<N, subcontract<C>>>;

  template<int_ n, class C = identity>
  using is_size_of_c = valid_contract<mp::is_size_of_c<n, subcontract<C>>>;

  template<class C = identity>
  using is_size_of_1 = valid_contract<mp::is_size_of_1<subcontract<C>>>;

  template<class C = identity>
  using is_size_of_2 = valid_contract<mp::is_size_of_2<subcontract<C>>>;

  template<class N, class C = identity>
  using is_size_larger_than = valid_contract<mp::is_size_larger_than<N, subcontract<C>>>;

  template<int_ n, class C = identity>
  using is_size_larger_than_c = valid_contract<mp::is_size_larger_than_c<n, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, is_size_of<N, C>>
  {
    using type = smp::is_size_of<N, sfinae<C>>;
  };
}
