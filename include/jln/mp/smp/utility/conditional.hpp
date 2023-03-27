#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/functional/sfinaefwd.hpp>
#include <jln/mp/utility/conditional.hpp>

namespace jln::mp::smp
{
  template<bool b>
  using conditional_c = try_contract<mp::conditional_c<b>>;
}

JLN_MP_MAKE_REGULAR_SMP1_P(conditional, (x), smp::conditional_c<bool(x::value)>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, bool b>
  struct _sfinae<sfinae, conditional_c<b>>
  {
    using type = smp::conditional_c<b>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT(argument_category::binary, (bool b), (conditional_c<b>));
}

#include <jln/mp/smp/optimizer/optimizer.hpp>

namespace jln::mp::optimizer
{
  template<bool b>
  struct optimized_for_conditional
  {
    template<class... xs>
    using f = optimized_result<union_<xs...>, conditional_c<b>>;
  };

  template<bool b, class params>
  struct optimizer_impl<conditional_c<b>, params>
  {
    using type = typename count_param_always_maybe_never_selector<params, 2>
      ::template f<dispatch_param_at_c<params, b ? 0 : 1>>
      ::template f<optimized_for_conditional<b>>;
  };
}
/// \endcond
