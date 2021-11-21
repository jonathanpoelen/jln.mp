#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/drop_back.hpp>
#include <jln/mp/algorithm/drop_while.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/algorithm/take_while.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/functional/invoke_twice.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using take_while = contract<mp::invoke_twice<
    mp::drop_while<
      concepts::predicate<assume_unary<Pred>>,
      mp::if_<
        mp::if_<
          mp::size<>,
          mp::front<concepts::predicate<assume_unary<Pred>, mp::always<true_>>>,
          mp::always<mp::true_>
        >,
        mp::size<
          mp::push_back<
            subcontract<C>,
            mp::lift<mp::drop_back>
          >
        >,
        mp::always<violation>
      >
    >
  >>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, take_while<Pred, C>>
  {
    using type = smp::take_while<sfinae<Pred>, sfinae<C>>;
  };
}
/// \endcond
