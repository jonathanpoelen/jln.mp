#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/clear.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/smp/functional/not_fn.hpp>
#include <jln/mp/algorithm/find.hpp>
#include <jln/mp/list/take_back.hpp>
#include <jln/mp/algorithm/drop_while.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/functional/invoke_twice.hpp>
#include <jln/mp/functional/if.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_if = contract<mp::invoke_twice<
    mp::drop_while<
      concepts::predicate<assume_unary<Pred>, mp::not_<>>,
      mp::if_<
        mp::size<>,
        mp::if_<
          mp::front<concepts::predicate<assume_unary<Pred>, mp::always<mp::true_>>>,
          mp::size<
            mp::push_back<
              subcontract<TC>,
              mp::lift<mp::take_back>
            >
          >,
          mp::always<violation>
        >,
        mp::always<subcontract<FC>>
      >
    >
  >>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_if_not = find_if<not_fn<Pred>, TC, FC>;

  template<class T, class TC = listify, class FC = clear<TC>>
  using find = contract<mp::find<T, subcontract<TC>, subcontract<FC>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, find_if<Pred, TC, FC>>
  {
    using type = smp::find_if<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
