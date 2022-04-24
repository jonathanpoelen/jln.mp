#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/insert_range.hpp>

/// \cond
namespace jln::mp::detail
{
  template<int_ index, class C>
  struct smp_insert_range_impl
  {
    template<class... xs>
    using f = contract<insert_range_c<index, list<xs...>, C>>;
  };
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ index, class seq, class C = listify>
  using insert_range_c = typename mp::try_<
    mp::unpack<detail::smp_insert_range_impl<index, subcontract<C>>>,
    mp::identity,
    mp::always<bad_contract>
  >::template f<seq>;
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
}
/// \endcond
