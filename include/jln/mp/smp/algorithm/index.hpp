#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/size.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/algorithm/conjunction.hpp> // because conjunction is a index_if
#include <jln/mp/algorithm/drop_while.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/algorithm/index.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/functional/invoke_twice.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/functional/compose.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = identity, class FC = size<>>
  using index_if = contract<mp::invoke_twice<
    mp::drop_while<
      concepts::predicate<assume_unary<Pred>, mp::not_<>>,
      mp::if_<
        mp::front<concepts::predicate<assume_unary<Pred>, mp::always<true_>>>,
        mp::size<
          mp::push_back<
            sub<TC>,
            mp::compose_f<mp::push_back, mp::size>
          >
        >,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;

  template<class T, class TC = identity, class FC = size<>>
  using index_of = contract<mp::index_if<is<T>, subcontract<TC>, subcontract<FC>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, index_if<Pred, TC, FC>>
  {
    using type = smp::index_if<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
