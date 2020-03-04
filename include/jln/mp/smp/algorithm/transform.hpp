#pragma once

#include "../list/list.hpp"
#include "../../functional/monadic.hpp"
#include "../../algorithm/transform.hpp"

namespace jln::mp::smp
{
  template<class F, class C = listify>
  using transform = contract<mp::transform<
    assume_unary<F>, mp::monadic_xs<subcontract<C>>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, transform<F, C>>
  {
    using type = smp::transform<sfinae<F>, sfinae<C>>;
  };

  template<>
  struct optimize_useless_transform_unpack_impl<contract<identity>>
  {
    template<class C>
    using f = optimize_useless_transform_unpack_t<contract<C>>;
  };

  template<class F, class C>
  struct optimize_useless_transform_unpack<contract<transform<F, C>>>
  {
    using type = typename optimize_useless_transform_unpack_impl<optimize_useless_unpack_t<F>>
      ::template f<C>;
  };

  template<class F, class C>
  struct optimize_useless_transform_unpack<contract<transform<F, mp::monadic_xs<C>>>>
  {
    using type =
      typename optimize_useless_transform_unpack_impl<optimize_useless_unpack_t<F>>
      ::template f<
        typename conditional_c<std::is_same_v<
          optimize_useless_transform_unpack_t<transform<F>>,
          transform<F>
        >>
        ::template f<mp::monadic_xs<C>, C>
      >;
  };
}
