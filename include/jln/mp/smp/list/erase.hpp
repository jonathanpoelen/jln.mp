#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/erase.hpp>

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_smp_erase;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ start, int_ size = 1, class C = listify>
  using erase_c = typename detail::mk_smp_erase<start >= 0 && size >= 0>
    ::template f<start, size, C>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(erase, (start), (size, number<1>), (C, smp::listify),
  smp::erase_c<start::value, size::value, C>)


#include <jln/mp/number/operators.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, unsigned start, unsigned size, class C>
  struct _sfinae<sfinae, erase_c<start, size, C>>
  {
    using type = smp::erase_c<start, size, sfinae<C>>;
  };

  template<>
  struct mk_smp_erase<true>
  {
    template<int_ start, int_ size, class C>
    using f = test_contract<
      mp::size<mp::greater_equal_than_c<start>>,
      mp::erase_c<start, size, subcontract<C>>>;
  };

  template<>
  struct mk_smp_erase<false>
  {
    template<int_ i, int_ start, class C>
    using f = bad_contract;
  };
}
/// \endcond
