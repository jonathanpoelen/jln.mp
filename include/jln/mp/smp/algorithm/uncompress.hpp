// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/algorithm/uncompress.hpp>
#include <jln/mp/number/operators.hpp>

namespace jln::mp::detail
{
  template<class Selectors, class = void>
  struct smp_uncompress_select;
}

namespace jln::mp::smp
{
  template<class FillT, bool... selectors>
  using uncompress_c = test_contract<
    size<greater_equal_than_c<(0 + ... + selectors)>>,
    uncompress_c_with<mp::listify, FillT, selectors...>
  >;

  template<class C, class FillT, bool... selectors>
  using uncompress_c_with = test_contract<
    size<greater_equal_than_c<(0 + ... + selectors)>>,
    uncompress_c_with<subcontract<C>, FillT, selectors...>
  >;

  template<class FillT, class Selectors, class C = listify>
  using uncompress = typename detail::smp_uncompress_select<Selectors>
    ::template f<FillT, C>;

  template<class FillT, class... Selectors>
  using uncompress_for = uncompress<FillT, mp::list<Selectors...>>;
}


#include <jln/mp/utility/always.hpp>
#include <type_traits>

/// \cond
namespace jln::mp::detail
{
  template<class Selectors, class>
  struct smp_uncompress_select : always<bad_contract>
  {};

  template<template<class...> class Tpl, class... Selectors>
  struct smp_uncompress_select<
    Tpl<Selectors...>,
#if JLN_MP_CUDA
    std::enable_if_t<((std::size_t{Selectors::value} <= 1) || ...) || !sizeof...(Selectors)>
#else
    std::void_t<decltype(JLN_MP_INTEGRAL_AS(bool, Selectors::value))...>
#endif
  >
  {
    template<class FillT, class C>
    using f = smp::uncompress_c_with<C, FillT, Selectors::value...>;
  };

  template<template<class> class sfinae, class C, class FillT, bool... selectors>
  struct _sfinae<sfinae, uncompress_c_with<C, FillT, selectors...>>
  {
    using type = smp::uncompress_c_with<sfinae<C>, FillT, selectors...>;
  };
}
/// \endcond
