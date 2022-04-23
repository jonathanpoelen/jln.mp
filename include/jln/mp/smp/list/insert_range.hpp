#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/insert_range.hpp>
#include <jln/mp/list/is_list.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class>
  struct smp_insert_range_select;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ index, class seq, class C = listify>
  using insert_range_c = typename detail::smp_insert_range_select<
    typename detail::_is_list<seq>::type
  >::template f<index, seq, C>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(insert_range, (Index), (seq), (C, smp::listify),
  smp::insert_range_c<Index::value, seq, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, int_ index, class seq, class C>
  struct _sfinae<sfinae, insert_range_c<index, seq, C>>
  {
    using type = smp::insert_range_c<index, seq, sfinae<C>>;
  };

  template<>
  struct smp_insert_range_select<false_>
  {
    template<int_ index, class seq, class C>
    using f = bad_contract;
  };

  template<>
  struct smp_insert_range_select<true_>
  {
    template<int_ index, class seq, class C>
    using f = contract<insert_range_c<index, seq, subcontract<C>>>;
  };
}
/// \endcond
