#pragma once

#include "../list/list.hpp"
#include "../algorithm/fold_left.hpp"
#include "../utility/unpack.hpp"
#include "../functional/function.hpp"
#include "../list/push_front.hpp"
#include "../list/pop_front.hpp"
#include "../../algorithm/unique.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using unique = detail::sfinae<mp::unique<subcontract_barrier<C>>>;

  template<class Cmp = cfe<std::is_same>, class C = listify>
  using unique_if = detail::sfinae<mp::unique_if<
    assume_binary_barrier<Cmp>, subcontract_barrier<C>>>;
}

#include "../algorithm/same.hpp"
#include "../utility/unpack.hpp"

namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, cfl<_set_push_back>>
  {
    using type = contract<cfl<_set_push_back>>;
  };

  template<template<class> class sfinae, class Cmp>
  struct _sfinae<sfinae, _set_cmp_push_back<Cmp>>
  {
    using type = contract<try_invoke<_set_cmp_push_back<sfinae<Cmp>>>>;
  };

  template<class C>
  struct mk_unique<subcontract_barrier<smp::cfe<std::is_same>>, C>
  {
    using type = push_front<list<>, fold_left<
      contract_barrier<cfl<_set_push_back>>,
      optimize_useless_unpack_t<unpack<C>>
    >>;
  };

  template<class C>
  struct mk_unique<subcontract_barrier<smp::cfl<std::is_same>>, C>
  : mk_unique<subcontract_barrier<smp::cfe<std::is_same>>, C>
  {};

  template<class C>
  struct mk_unique<subcontract_barrier<smp::same<>>, C>
  : mk_unique<subcontract_barrier<smp::cfe<std::is_same>>, C>
  {};
}
