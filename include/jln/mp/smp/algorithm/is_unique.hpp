#pragma once

#include <jln/mp/smp/algorithm/unique.hpp>
#include <jln/mp/smp/number/to_bool.hpp>
#include <jln/mp/smp/functional/tee.hpp>
#include <jln/mp/smp/algorithm/same.hpp>
#include <jln/mp/algorithm/is_unique.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using is_unique = contract<mp::is_unique<assume_number<C>>>;

  template<class Cmp = lift<std::is_same>, class C = identity>
  using is_unique_with = detail::sfinae<mp::is_unique_with<
    assume_binary_barrier<Cmp>, assume_number_barrier<C>>>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, _is_unique<C>>
  {
    using type = smp::is_unique<sfinae<C>>;
  };

  template<class C>
  struct mk_is_unique<subcontract_barrier<smp::lift<std::is_same>>, C>
  {
    using type = smp::is_unique<C>;
  };

  template<class C>
  struct mk_is_unique<subcontract_barrier<smp::lift_t<std::is_same>>, C>
  : mk_is_unique<subcontract_barrier<smp::lift<std::is_same>>, C>
  {};

  template<class C>
  struct mk_is_unique<subcontract_barrier<smp::same<>>, C>
  : mk_is_unique<subcontract_barrier<smp::lift<std::is_same>>, C>
  {};
}
/// \endcond
