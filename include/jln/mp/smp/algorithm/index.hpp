#pragma once

#include "find.hpp"
#include "../utility/always.hpp"
#include "../../algorithm/index.hpp"
#include "../../functional/fork.hpp"
#include "../../functional/fork_front.hpp"

namespace jln::mp::smp
{
  template<class Pred, class C = identity, class NC = always<na>>
  using index_if = valid_contract<mp::fork_front<mp::fork<
    mp::always<Pred>,
    mp::size<mp::fork<
      mp::identity,
      mp::always<subcontract<C>>,
      mp::cfe<mp::offset, cfe<contract_barrier>>
    >>,
    mp::always<NC>,
    mp::cfe<find_if, mp::cfe<try_invoke>>
  >>>;

  template<class T, class C = identity, class NC = always<na>>
  using index_of = valid_contract<
    mp::index_of<T, subcontract<C>, subcontract<NC>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C, class NC>
  struct _sfinae<sfinae, index_if<Pred, C, NC>>
  {
    using type = smp::index_if<sfinae<Pred>, sfinae<C>, sfinae<NC>>;
  };

  template<template<class> class sfinae, class T, class C, class NC>
  struct _sfinae<sfinae, index_if<same_as<T>, C, NC>>
  {
    using type = smp::index_of<T, sfinae<C>, sfinae<NC>>;
  };
}
