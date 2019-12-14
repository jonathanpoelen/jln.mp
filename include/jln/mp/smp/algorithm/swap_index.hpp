#pragma once

#include "../list/list.hpp"
#include "../../algorithm/swap_index.hpp"

namespace jln::mp::detail
{
  template<class>
  struct _smp_swap_index;
}

namespace jln::mp::smp
{
  template<class I, class J, class C = listify>
  using swap_index = typename detail::_smp_swap_index<
    mp::swap_index<I, J, C>>::type;

  template<unsigned i, unsigned j, class C = listify>
  using swap_index_c = typename detail::_smp_swap_index<
    mp::swap_index_c<i, j, C>>::type;
}

namespace jln::mp::detail
{
  template<unsigned i, class C>
  struct _smp_swap_index<if_valid_index<i, C>>
  {
    using type = contract<size<greater_than_c<i>>, subcontract<C>>;
  };

  template<unsigned i, unsigned j, class C>
  struct _smp_swap_index<swap_elem<i, j, C>>
  {
    using type = contract<size<greater_than_c<j>>, swap_elem<i, j, subcontract<C>>>;
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
