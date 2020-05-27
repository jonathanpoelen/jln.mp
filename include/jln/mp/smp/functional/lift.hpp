#pragma once

#include "../assume.hpp"
#include "identity.hpp"
#include "../../functional/lift.hpp"

namespace jln::mp::smp
{
  template<template<class...> class F, class C = identity>
  using lift = try_contract<mp::lift<F, assume_unary<C>>>;

  template<template<class...> class F, class C = identity>
  using lift_t = try_contract<mp::lift_t<F, assume_unary<C>>>;
}


#include <type_traits>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, template<class...> class F, class C>
  struct _sfinae<sfinae, lift_t<F, C>>
  {
    using type = smp::lift_t<F, sfinae<C>>;
  };

  template<template<class> class sfinae, template<class...> class F, class C>
  struct _sfinae<sfinae, lift<F, C>>
  {
    using type = smp::lift<F, sfinae<C>>;
  };


  JLN_MP_MAKE_EXPECTED_ARGUMENT(argument_category::binary, (class C), (lift<std::is_same, C>));
  JLN_MP_MAKE_EXPECTED_ARGUMENT(argument_category::binary, (class C), (lift_t<std::is_same, C>));
}
/// \endcond
