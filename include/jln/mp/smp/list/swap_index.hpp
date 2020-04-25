#pragma once

#include "../list/list.hpp"
#include "../../list/swap_index.hpp"

/// \cond
namespace jln::mp::detail
{
  template<class>
  struct _smp_swap_index;
}
/// \endcond

namespace jln::mp::smp
{
  template<unsigned i, unsigned j, class C = listify>
  using swap_index_c = typename detail::_smp_swap_index<
    mp::swap_index_c<i, j, C>>::type;
}

JLN_MP_MAKE_REGULAR_SMP3_P(swap_index, (i), (j), (C, smp::listify),
  smp::swap_index_c<i::value, j::value, C>)


#include "../../list/size.hpp"
#include "../../number/operators.hpp"

/// \cond
namespace jln::mp::detail
{
  template<unsigned i, class C>
  struct _smp_swap_index<if_valid_index<i, C>>
  {
    using type = test_contract<size<greater_than_c<i>>, subcontract<C>>;
  };

  template<unsigned i, unsigned j, class C>
  struct _smp_swap_index<swap_elem<i, j, C>>
  {
    using type = test_contract<size<greater_than_c<j>>, swap_elem<i, j, subcontract<C>>>;
  };

  template<template<class> class sfinae, unsigned i, class C>
  struct _sfinae<sfinae, if_valid_index<i, C>>
  : detail::_smp_swap_index<if_valid_index<i, sfinae<C>>>
  {};

  template<template<class> class sfinae, unsigned i, unsigned j, class C>
  struct _sfinae<sfinae, swap_elem<i, j, C>>
  : detail::_smp_swap_index<swap_elem<i, j, sfinae<C>>>
  {};
}
/// \endcond
