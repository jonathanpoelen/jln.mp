#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/algorithm/fold_left.hpp>
#include <jln/mp/smp/utility/unpack.hpp>
#include <jln/mp/smp/functional/lift.hpp>
#include <jln/mp/smp/list/push_front.hpp>
#include <jln/mp/smp/list/pop_front.hpp>
#include <jln/mp/algorithm/unique.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using unique = detail::sfinae<mp::unique<subcontract_barrier<C>>>;

  template<class Cmp = lift<std::is_same>, class C = listify>
  using unique_if = detail::sfinae<mp::unique_if<
    assume_binary_barrier<Cmp>, subcontract_barrier<C>>>;
}

#include <jln/mp/smp/algorithm/same.hpp>
#include <jln/mp/smp/utility/unpack.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, lift_t<_set_push_back>>
  {
    using type = contract<lift_t<_set_push_back>>;
  };

  template<template<class> class sfinae, class Cmp>
  struct _sfinae<sfinae, _set_cmp_push_back<Cmp>>
  {
    using type = contract<try_<_set_cmp_push_back<sfinae<Cmp>>>>;
  };

  template<class C>
  struct mk_unique<subcontract_barrier<smp::lift<std::is_same>>, C>
  {
    using type = push_front<list<>, fold_left<
      contract_barrier<lift_t<_set_push_back>>,
      optimize_useless_unpack_t<unpack<C>>
    >>;
  };

  template<class C>
  struct mk_unique<subcontract_barrier<smp::lift_t<std::is_same>>, C>
  : mk_unique<subcontract_barrier<smp::lift<std::is_same>>, C>
  {};

  template<class C>
  struct mk_unique<subcontract_barrier<smp::same<>>, C>
  : mk_unique<subcontract_barrier<smp::lift<std::is_same>>, C>
  {};
}
/// \endcond
