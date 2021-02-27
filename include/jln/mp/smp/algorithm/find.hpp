#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/algorithm/find.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = listify, class NC = C>
  using find_if = contract<mp::find_if<
    concepts::predicate<assume_unary<Pred>, mp::identity, mp::always<true_>>,
    mp::if_<
      mp::front<concepts::predicate<assume_unary<Pred>>>,
      subcontract<C>,
      violation
    >,
    subcontract<NC>>>;

  template<class T, class C = listify, class NC = C>
  using find = contract<
    mp::find<T, subcontract<C>, subcontract<NC>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C, class NC>
  struct _sfinae<sfinae, find_if<Pred, C, NC>>
  {
    using type = smp::find_if<sfinae<Pred>, sfinae<C>, sfinae<NC>>;
  };
}
/// \endcond
