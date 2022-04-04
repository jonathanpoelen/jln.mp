#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/functional/random.hpp>

#ifdef __cpp_generic_lambdas
#if __cpp_generic_lambdas >= 201707L

namespace jln::mp::smp
{
  template<class C = identity>
  using random = contract<mp::random<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C, auto v>
  struct _sfinae<sfinae, random<C, v>>
  {
    using type = contract<mp::random<assume_unary<C>, v>>;
  };

  template<class C, auto v>
  struct expected_argument<random<C, v>>
  : number<argument_category::unary_or_more>
  {};
}
/// \endcond

#endif
#endif
