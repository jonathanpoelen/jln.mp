#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/algorithm/same.hpp>
#include <jln/mp/smp/utility/is_not.hpp>
#include <jln/mp/smp/functional/tee.hpp>
#include <jln/mp/smp/functional/lift.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/functional/try.hpp>
#include <jln/mp/list/wrap_in_list.hpp>

namespace jln::mp::smp
{
  template<class Pred>
  using wrap_in_list_if = try_contract<mp::wrap_in_list_if<
    concepts::strong_predicate_or<assume_unary_or_more<Pred>, mp::violation>>>;

  template<class Pred>
  using wrap_in_list_if_not = try_contract<mp::wrap_in_list_if_not<
    concepts::strong_predicate_or<assume_unary_or_more<Pred>, mp::violation>>>;

  template<bool b>
  using wrap_in_list_c = contract<mp::wrap_in_list_c<b>>;
}

JLN_MP_MAKE_REGULAR_SMP1_P(wrap_in_list, (N), smp::wrap_in_list_c<N::value>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred>
  struct _sfinae<sfinae, _wrap_in_list_if<Pred>>
  {
    using type = smp::wrap_in_list_if<sfinae<Pred>>;
  };

  template<template<class> class sfinae, class Pred>
  struct _sfinae<sfinae, _wrap_in_list_if_not<Pred>>
  {
    using type = smp::wrap_in_list_if_not<sfinae<Pred>>;
  };

  template<template<class> class sfinae, bool b>
  struct _sfinae<sfinae, wrap_in_list_c<b>>
  {
    using type = smp::wrap_in_list_c<b>;
  };
}

#include <jln/mp/smp/optimizer/optimizer.hpp>

namespace jln::mp::optimizer
{
  struct optimized_for_wrap_in_list_if
  {
    template<class R, class Pred, class x>
    using f = optimized_result<
      typename select_cond<R>::template f<list_t<x>, list<>>,
      detail::_wrap_in_list_if<Pred>
    >;
  };

  template<class Pred, class params>
  struct optimizer_impl<detail::_wrap_in_list_if<Pred>, params>
  {
    using type = typename dispatch_optimizer<optimized_for_wrap_in_list_if>
      ::template f<Pred, params, param_at_c<params, 0>>;
  };


  struct optimized_for_wrap_in_list_if_not
  {
    template<class R, class Pred, class x>
    using f = optimized_result<
      typename select_cond<R>::template f<list<>, list_t<x>>,
      detail::_wrap_in_list_if_not<Pred>
    >;
  };

  template<class Pred, class params>
  struct optimizer_impl<detail::_wrap_in_list_if_not<Pred>, params>
  {
    using type = typename dispatch_optimizer<optimized_for_wrap_in_list_if_not>
      ::template f<Pred, params, param_at_c<params, 0>>;
  };


  template<class params>
  struct optimizer_impl<wrap_in_list_c<true>, params>
  {
    using type = optimized_result<list_t<params>, wrap_in_list_c<true>>;
  };

  template<class params>
  struct optimizer_impl<wrap_in_list_c<false>, params>
  {
    using type = optimized_result_t<list<>, always<list<>>>;
  };
}
/// \endcond
