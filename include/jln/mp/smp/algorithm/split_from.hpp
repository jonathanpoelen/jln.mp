#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/split_from.hpp>
#include <jln/mp/functional/invoke_twice.hpp>
#include <jln/mp/functional/tee.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class SubC1, class SubC2, class C>
  struct _smp_split_from;
}
/// \endcond

namespace jln::mp::smp
{
  template<class GetIndex, class SubC1 = listify, class SubC2 = SubC1, class C = listify>
  using split_from2 = contract<mp::invoke_twice<mp::tee<
    subcontract<GetIndex>,
    detail::_smp_split_from<subcontract<SubC1>, subcontract<SubC2>, subcontract<C>>
  >>>;

  template<class GetIndex, class C = listify>
  using split_from = contract<mp::invoke_twice<mp::tee<
    subcontract<GetIndex>,
    detail::_smp_split_from<mp::listify, mp::listify, subcontract<C>>
  >>>;
}

/// \cond
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/functional/monadic.hpp>

namespace jln::mp::detail
{
  struct smp_split_from_i
  {
    template<class position, class C1, class C2, class C, class... xs>
    using f = _split_from_i<position::value, C1, C2, C, xs...>;
  };

  template<class SubC1, class SubC2, class C>
  struct _smp_split_from
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
        ::template f<smp_split_from_i, violation>
        ::template f<i, SubC1, SubC2, monadic_xs<C>, xs...>;
    };

    template<class i>
    using f = impl<i>;
  };


  template<template<class> class sfinae, class GetIndex, class SubC1, class SubC2, class C>
  struct _sfinae<sfinae, split_from2<GetIndex, SubC1, SubC2, C>>
  {
    using type = smp::split_from2<sfinae<GetIndex>, sfinae<SubC1>, sfinae<SubC2>, sfinae<C>>;
  };
}
/// \endcond
