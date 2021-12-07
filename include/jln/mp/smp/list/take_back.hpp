#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/take_back.hpp>

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_take_back;

  template<bool>
  struct mk_take_back_max;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using take_back_c = typename detail::mk_take_back<n >= 0>
    ::template f<n, C>;

  template<int_ n, class C = listify>
  using take_back_max_c = typename detail::mk_take_back_max<n >= 0>
    ::template f<n, C>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(take_back, (N), (C, smp::listify), smp::take_back_c<N::value, C>)
JLN_MP_MAKE_REGULAR_SMP2_P(take_back_max, (N), (C, smp::listify), smp::take_back_max_c<N::value, C>)


#include <jln/mp/number/operators.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, take_back_c<N, C>>
  {
    using type = smp::take_back_c<N, sfinae<C>>;
  };

  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, take_back_max_c<N, C>>
  {
    using type = smp::take_back_max_c<N, sfinae<C>>;
  };

  template<>
  struct mk_take_back<true>
  {
    template<int_ n, class C>
    using f = test_contract<
      mp::size<mp::greater_equal_than_c<n>>,
      mp::take_back_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_take_back<false>
  {
    template<int_ i, int_ start, class C>
    using f = bad_contract;
  };

  template<>
  struct mk_take_back_max<true>
  {
    template<int_ n, class C>
    using f = contract<mp::take_back_max_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_take_back_max<false>
  {
    template<int_ i, int_ start, class C>
    using f = bad_contract;
  };
}
/// \endcond
