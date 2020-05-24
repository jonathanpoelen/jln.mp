#pragma once

#include "unique.hpp"
#include "../number/to_bool.hpp"
#include "../functional/tee.hpp"
#include "../algorithm/same.hpp"
#include "../../algorithm/is_unique.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using is_unique = contract<mp::is_unique<assume_number<C>>>;

  template<class Cmp = lift<std::is_same>, class C = identity>
  using is_unique_if = detail::sfinae<mp::is_unique_if<
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
