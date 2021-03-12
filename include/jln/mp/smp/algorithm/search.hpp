#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/size.hpp>
#include <jln/mp/smp/list/clear.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/algorithm/search.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/functional/invoke_twice.hpp>
#include <jln/mp/functional/compose.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using search = contract<mp::search<
    concepts::predicate<assume_unary_or_more<Pred>, mp::identity, mp::always<mp::true_>>,
    mp::if_<
      mp::if_<
        mp::size<>,
        concepts::predicate<assume_unary_or_more<Pred>>,
        mp::always<mp::true_>
      >,
      subcontract<TC>,
      violation
    >,
    subcontract<FC>
  >>;

  template<class Pred, class TC = identity, class FC = size<>>
  using search_index = contract<mp::invoke_twice<
    mp::search<
      concepts::predicate<assume_unary_or_more<Pred>, mp::identity, mp::always<mp::true_>>,
      mp::if_<
        concepts::predicate<assume_unary_or_more<Pred>, mp::always<mp::true_>>,
        mp::size<
          mp::push_back<
            sub<subcontract<TC>>,
            mp::compose_f<mp::push_back, mp::size>
          >
        >,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, search<Pred, TC, FC>>
  {
    using type = smp::search<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, search_index<Pred, TC, FC>>
  {
    using type = smp::search_index<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
