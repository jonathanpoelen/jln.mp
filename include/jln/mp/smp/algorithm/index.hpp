#pragma once

#include "find.hpp"
#include "../number/operators.hpp"
#include "../utility/always.hpp"
#include "../utility/same_as.hpp"
#include "../../algorithm/index.hpp"

namespace jln::mp::detail
{
  template<class Pred, class C, class NC>
  struct _smp_index_if;
}

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using index_for = try_contract<
    mp::index_for<subcontract<F>, subcontract<C>>>;

  template<class Pred, class C = identity, class NC = always<na>>
  using index_if = contract<detail::_smp_index_if<
    subcontract<Pred>, subcontract<C>, subcontract<NC>>>;

  template<class T, class C = identity, class NC = always<na>>
  using index_of = index_if<same_as<T>, C, NC>;
}

namespace jln::mp::detail
{
  template<class Pred, class C, class NC>
  struct _smp_index_if
  {
    template<class... xs>
    using f = typename subcontract<smp::find_if<
      contract_barrier<Pred>,
      contract_barrier<size<push_front<
        number<sizeof...(xs)>,
        subcontract<smp::sub<contract_barrier<C>>>
      >>>,
      contract_barrier<NC>
    >>::template f<xs...>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, index_for<F, C>>
  {
    using type = smp::index_for<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C, class NC>
  struct _sfinae<sfinae, index_if<F, C, NC>>
  {
    using type = smp::index_if<sfinae<F>, sfinae<C>, sfinae<NC>>;
  };
}
