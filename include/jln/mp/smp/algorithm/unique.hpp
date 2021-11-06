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

  template<class Cmp = contract<mp::lift<std::is_same>>, class C = listify>
  using unique_if = detail::sfinae<mp::unique_if<
    assume_binary_barrier<Cmp>, subcontract_barrier<C>>>;
}

#include <jln/mp/smp/algorithm/same.hpp>
#include <jln/mp/smp/utility/unpack.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class C>
  struct smp_unique_continuation
  {
    using type = C;
  };

  template<>
  struct smp_unique_continuation<try_<unpack<lift<list>>>>
  {
    using type = mp::identity;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, push_front<list<>, fold_left<lift_t<_set_push_back>, C>>>
  {
    using type = contract<push_front<list<>, fold_left<
      lift_t<_set_push_back>, typename smp_unique_continuation<
        assume_unary<sfinae<C>>
      >::type
    >>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, push_front<list<>, fold_left<
    _set_cmp_push_back<contract_barrier<mp::lift<std::is_same>>>, C
  >>>
  {
    using type = contract<push_front<list<>, fold_left<
      lift_t<_set_push_back>, typename smp_unique_continuation<
        assume_unary<optimize_useless_unpack_t<sfinae<C>>>
      >::type
    >>>;
  };

  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, push_front<list<>, fold_left<
    _set_cmp_push_back<Cmp>, C
  >>>
  {
    using type = contract<push_front<list<>, smp::fold_left<
      contract<try_<_set_cmp_push_back<sfinae<Cmp>>>>, sfinae<C>
    >>>;
  };
}
/// \endcond
