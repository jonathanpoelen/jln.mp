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
  template<class Selectors, class C = listify>
  using compress = typename detail::smp_compress_select<Selectors>
    ::template f<C>;

  template<bool... selectors>
  using compress_with_c = test_contract<
    mp::size<mp::is<mp::number<sizeof...(selectors)>>>,
    mp::compress<mp::list<mp::number<selectors>...>>
  >;
}

/// \cond
#include <type_traits>

namespace jln::mp::detail
{
  template<class Selectors, class>
  struct smp_compress_select
  {
    template<class C>
    using f = bad_contract;
  };

  template<class... Selectors>
  struct smp_compress_select<
    list<Selectors...>,
    std::void_t<decltype(bool{Selectors::value})...>
  >
  {
    template<class C>
    using f = test_contract<
      size<is<number<sizeof...(Selectors)>>>,
      compress<list<Selectors...>, subcontract<C>>
    >;
  };

  template<template<class> class sfinae, class Selectors, class C>
  struct _sfinae<sfinae, compress<Selectors, C>>
  {
    using type = smp::compress<Selectors, sfinae<C>>;
  };
}
/// \endcond
