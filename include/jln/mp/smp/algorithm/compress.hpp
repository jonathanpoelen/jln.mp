// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/algorithm/compress.hpp>

namespace jln::mp::detail
{
  template<class Selectors, class = void>
  struct smp_compress_select;
}

namespace jln::mp::smp
{
  template<bool... selectors>
  using compress_c = test_contract<
    size<is<number<sizeof...(selectors)>>>,
    compress_c_with<listify, selectors...>
  >;

  template<class C, bool... selectors>
  using compress_c_with = test_contract<
    size<is<number<sizeof...(selectors)>>>,
    compress_c_with<subcontract<C>, selectors...>
  >;

  template<class Selectors, class C = listify>
  using compress = typename detail::smp_compress_select<Selectors>
    ::template f<C>;

  template<class... Selectors>
  using compress_for = compress<mp::list<Selectors...>>;
}


#include <jln/mp/utility/always.hpp>
#include <type_traits>

/// \cond
namespace jln::mp::detail
{
  template<class Selectors, class>
  struct smp_compress_select : always<bad_contract>
  {};

  template<template<class...> class Tpl, class... Selectors>
  struct smp_compress_select<
    Tpl<Selectors...>,
#if JLN_MP_CUDA
    std::enable_if_t<((std::size_t{Selectors::value} <= 1) || ...) || !sizeof...(Selectors)>
#else
    std::void_t<decltype(JLN_MP_INTEGRAL_AS(bool, Selectors::value))...>
#endif
  >
  {
    template<class C>
    using f = smp::compress_c_with<C, Selectors::value...>;
  };

  template<template<class> class sfinae, class C, bool... selectors>
  struct _sfinae<sfinae, compress_c_with<C, selectors...>>
  {
    using type = smp::compress_c_with<sfinae<C>, selectors...>;
  };
}
/// \endcond
