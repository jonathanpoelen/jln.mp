#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/list/back.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/algorithm/conjunction.hpp>

/// \cond
namespace jln::mp::detail
{
  template<
    template<class...> class drop, class pred_result, class default_result,
    class Pred, class C
  >
  using conjunction_disjunction_with = contract<drop<
    smp::concepts::predicate<assume_unary<Pred>, identity, always<pred_result>>,
    front<
      if_<
        smp::concepts::predicate<assume_unary<Pred>, always<true_>>,
        assume_unary<C>,
        violation
      >
    >,
    detail::optimize_tee_t<tee<
      if_<
        size<>,
        back<>,
        always<default_result>
      >,
      assume_unary<C>
    >>
  >>;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using conjunction_with = detail::conjunction_disjunction_with<
    mp::drop_while, false_, true_, Pred, C>;

  template<class C = identity>
  using conjunction = conjunction_with<identity, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, conjunction_with<Pred, C>>
  {
    using type = smp::conjunction_with<sfinae<Pred>, sfinae<C>>;
  };
}
/// \endcond
