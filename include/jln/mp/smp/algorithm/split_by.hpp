#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/split_by.hpp>
#include <jln/mp/functional/invoke_twice.hpp>
#include <jln/mp/functional/tee.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class SubC1, class SubC2, class C>
  struct _smp_split_by;
}
/// \endcond

namespace jln::mp::smp
{
  template<class GetIndex, class SubC1 = listify, class SubC2 = SubC1, class C = listify>
  using split_by = contract<mp::invoke_twice<mp::tee<
    subcontract<GetIndex>,
    detail::_smp_split_by<subcontract<SubC1>, subcontract<SubC2>, subcontract<C>>
  >>>;

  template<class GetIndex, class C = listify>
  using split_by2 = contract<mp::invoke_twice<mp::tee<
    subcontract<GetIndex>,
    detail::_smp_split_by<mp::listify, mp::listify, subcontract<C>>
  >>>;
}

/// \cond
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/functional/monadic.hpp>

namespace jln::mp::detail
{
  template<class SubC1, class SubC2, class C>
  struct _smp_split_by
  {
    template<class i, class = void>
    struct impl
    {
      template<class... xs>
      using f = na;
    };

    template<class i>
    struct impl<i, decltype(void(unsigned{i::value}))>
    {
      template<class... xs>
      using f = typename conditional_c<i::value <= sizeof...(xs)>
        ::template f<mp::lift<_split_by_i>, violation>
        ::template f<i, SubC1, SubC2, monadic_xs<C>, xs...>;
    };

    template<class i>
    using f = impl<i>;
  };


  template<template<class> class sfinae, class GetIndex, class SubC1, class SubC2, class C>
  struct _sfinae<sfinae, split_by<GetIndex, SubC1, SubC2, C>>
  {
    using type = smp::split_by<sfinae<GetIndex>, sfinae<SubC1>, sfinae<SubC2>, sfinae<C>>;
  };
}
/// \endcond
