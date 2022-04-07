#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/algorithm/is_sorted.hpp>

namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = identity>
  using is_sorted = contract<
    mp::if_<
      mp::size<mp::less_than_c<2>>,
      always<mp::number<1>, assume_positive_number_barrier<C>>,
      mp::tee<
        mp::pop_front<>,
        mp::rotate_c<-1, mp::pop_front<>>,
        mp::zip_with<
          try_assume_binary<Cmp>,
          mp::try_<mp::or_<mp::not_<try_assume_positive_number<C>>>>
        >
      >
    >
  >;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, is_sorted<Cmp, C>>
  {
    using type = smp::is_sorted<sfinae<Cmp>, sfinae<C>>;
  };
}
/// \endcond
