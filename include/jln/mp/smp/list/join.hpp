#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/algorithm/all_of.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/list/is_list.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using join = test_contract<
    mp::all_of<mp::is_list<>>,
    mp::join<subcontract<C>>>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, join<C>>
  {
    using type = smp::join<sfinae<C>>;
  };
} // namespace jln::mp::detail

#include <jln/mp/smp/optimizer/optimizer.hpp>

namespace jln::mp::optimizer
{
  template<bool>
  struct optimized_for_join_wrap;

  template<>
  struct optimized_for_join_wrap<true>
  {
    template<class... xs>
    using f = wrap_optimize_with_params<types::basic_seq<xs...>>;
  };

  template<>
  struct optimized_for_join_wrap<false>
  {
    template<class... xs>
    using f = wrap_optimize_with_function<lift<join>, types::basic_seq<xs...>>;
  };

  struct optimized_for_join_impl
  {
    template<class... xs>
    using f = typename optimized_for_join_wrap<(... && is_real_type_v<xs>)>
      ::template f<xs...>;
  };

  template<class C, class params>
  struct optimizer_impl<join<C>, params>
  {
    using type = typename dispatch_join_list<params>
      ::template f<
        optimized_for_join_impl,
        add_uncallable_output<optimized_for_join_impl>,
        always<uncallable>>
      ::template f<C>;
  };
}
/// \endcond
