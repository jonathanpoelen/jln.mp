#pragma once

#include "find.hpp"
#include "../list/size.hpp"
#include "../utility/always.hpp"
#include "../../algorithm/index.hpp"
#include "../../functional/fork.hpp"
#include "../../functional/fork_front.hpp"

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using index_for = try_contract<
    mp::index_for<subcontract<F>, subcontract<C>>>;

  template<class Pred, class C = identity, class NC = always<na>>
  using index_if = index_for<find_if<Pred, size<>, NC>, C>;

  template<class T, class C = identity, class NC = always<na>>
  using index_of = index_if<same_as<T>, C, NC>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, index_for<F, C>>
  {
    using type = smp::index_for<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class T, class C, class NC>
  struct _sfinae<sfinae, index_for<find_if<same_as<T>, size<>, NC>, C>>
  {
    using type = smp::index_of<T, sfinae<C>, sfinae<NC>>;
  };
}
