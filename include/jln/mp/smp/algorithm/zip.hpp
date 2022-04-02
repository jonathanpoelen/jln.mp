#pragma once

#include <jln/mp/smp/algorithm/transform.hpp>
#include <jln/mp/smp/utility/unpack.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/list/is_list.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/algorithm/same.hpp>
#include <jln/mp/algorithm/zip.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using zip = test_contract<
    mp::if_<
      mp::transform<mp::is_list<>, mp::and_<>>,
      mp::transform<mp::unpack<mp::size<>>, mp::same<>>
    >,
    mp::zip<assume_lists<C>>>;

  template<class F = listify, class C = listify>
  using zip_with = zip<transform<unpack<F>, C>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, _zip<C>>
  {
    using type = smp::zip<sfinae<C>>;
  };
}
/// \endcond
