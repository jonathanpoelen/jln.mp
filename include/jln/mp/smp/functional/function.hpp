#pragma once

#include "identity.hpp"
#include "../../functional/function.hpp"

namespace jln::mp::smp
{
  template<template<class...> class F, class C = identity>
  using cfe = try_contract<mp::cfe<F, assume_unary<C>>>;

  template<template<class...> class F, class C = identity>
  using cfl = try_contract<mp::cfl<F, assume_unary<C>>>;
}


#include <type_traits>

namespace jln::mp::detail
{
  template<template<class> class sfinae, template<class...> class F, class C>
  struct _sfinae<sfinae, cfl<F, C>>
  {
    using type = smp::cfl<F, sfinae<C>>;
  };

  template<template<class> class sfinae, template<class...> class F, class C>
  struct _sfinae<sfinae, cfe<F, C>>
  {
    using type = smp::cfe<F, sfinae<C>>;
  };
  
  
  template<class C>
  struct expected_argument<cfe<std::is_same, C>>
  : number<argument_category::binary>
  {};
  
  template<class C>
  struct expected_argument<cfl<std::is_same, C>>
  : number<argument_category::binary>
  {};
}
