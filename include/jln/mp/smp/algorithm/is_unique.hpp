#pragma once

#include "unique.hpp"
#include "../functional/fork.hpp"
#include "../../algorithm/is_unique.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using is_unique = contract<mp::is_unique<assume_unary<C>>>;

  template<class Cmp = cfe<std::is_same>, class C = identity>
  using is_unique_if = detail::sfinae<mp::is_unique_if<
    contract_barrier<assume_binary<Cmp>>, contract_barrier<assume_unary<C>>>>;
}

#include "../algorithm/same.hpp"
#include "../utility/unpack.hpp"
#include "../number/to_bool.hpp"

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, _is_unique<C>>
  {
    using type = smp::is_unique<sfinae<C>>;
  };

  template<class C>
  struct mk_is_unique<subcontract_barrier<smp::cfe<std::is_same>>, C>
  {
    using type = smp::is_unique<C>;
  };

  template<class C>
  struct mk_is_unique<subcontract_barrier<smp::cfl<std::is_same>>, C>
  : mk_is_unique<subcontract_barrier<smp::cfe<std::is_same>>, C>
  {};

  template<class C>
  struct mk_is_unique<subcontract_barrier<smp::same<>>, C>
  : mk_is_unique<subcontract_barrier<smp::cfe<std::is_same>>, C>
  {};
}
