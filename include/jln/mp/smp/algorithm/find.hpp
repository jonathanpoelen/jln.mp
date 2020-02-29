#pragma once

#include "../concepts.hpp"
#include "../list/list.hpp"
#include "../utility/same_as.hpp"
#include "../functional/identity.hpp"
#include "../../list/front.hpp"
#include "../../algorithm/find.hpp"

namespace jln::mp::smp
{
  template<class Pred, class C = listify, class NC = C>
  using find_if = contract<mp::find_if<
    // TODO optimize for same_as and other safe predicate
    concepts::predicate<Pred, mp::identity, mp::always<true_>>,
    mp::if_<
      mp::front<concepts::predicate<Pred>>,
      subcontract<C>,
      violation
    >,
    subcontract<NC>>>;

  template<class T, class C = listify, class NC = C>
  using find = contract<
    mp::find<T, subcontract<C>, subcontract<NC>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C, class NC>
  struct _sfinae<sfinae, find_if<Pred, C, NC>>
  {
    using type = smp::find_if<sfinae<Pred>, sfinae<C>, sfinae<NC>>;
  };
}
