#pragma once

#include <jln/mp/smp/algorithm/unique.hpp>
#include <jln/mp/smp/number/to_bool.hpp>
#include <jln/mp/smp/functional/tee.hpp>
#include <jln/mp/smp/algorithm/same.hpp>
#include <jln/mp/algorithm/is_unique.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct mk_smp_is_unique;
}

namespace jln::mp::smp
{
  template<class C = identity>
  using is_unique = contract<mp::is_unique<assume_number<C>>>;

  template<class Cmp = lift<std::is_same>, class C = identity>
  using is_unique_with = typename detail::mk_smp_is_unique<Cmp>
    ::template f<C>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_unique_impl<C>>
  {
    using type = smp::is_unique<sfinae<C>>;
  };

  template<class Cmp>
  struct mk_smp_is_unique
  {
    template<class C>
    using f = contract<tee<
      subcontract<smp::unique_if<Cmp>>,
      listify,
      monadic0<lift_t<std::is_same, to_bool<assume_number<C>>>>>>;
  };

  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, tee<
    push_front<list<>, fold_left<
      unpack<_set_cmp_push_back<JLN_MP_TRACE_F(Cmp)>>>>,
    listify,
    lift_t<std::is_same, to_bool<C>>
  >>
  {
    using type = typename mk_smp_is_unique<sfinae<Cmp>>::template f<sfinae<C>>;
  };

  template<>
  struct mk_smp_is_unique<smp::lift<std::is_same>>
  {
    template<class C>
    using f = smp::is_unique<C>;
  };

  template<>
  struct mk_smp_is_unique<smp::lift_t<std::is_same>>
  : mk_smp_is_unique<smp::lift<std::is_same>>
  {};

  template<>
  struct mk_smp_is_unique<smp::same<>>
  : mk_smp_is_unique<smp::lift<std::is_same>>
  {};
}
/// \endcond
