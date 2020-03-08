#pragma once

#include "../contract.hpp"
#include "../../functional/eval.hpp"

#ifdef __cpp_nontype_template_parameter_class
#if __cpp_nontype_template_parameter_class >= 201806L

namespace jln::mp::smp
{
  template <auto F, class C = identity>
  using eval = try_contract<mp::eval<F, assume_unary<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, auto F, class C>
  struct _sfinae<sfinae, eval<F, C>>
  {
    using type = smp::eval<F, sfinae<C>>;
  };
}
#endif
#endif
