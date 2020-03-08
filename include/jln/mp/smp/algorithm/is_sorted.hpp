#pragma once

#include "../functional/identity.hpp"
#include "../utility/always.hpp"
#include "../number/operators.hpp"
#include "../../functional/fork.hpp"
#include "../../functional/if.hpp"
#include "../../list/size.hpp"
#include "../../algorithm/is_sorted.hpp"

namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = identity>
  using is_sorted = contract<
    mp::if_<
      mp::size<mp::less_than_c<2>>,
      always<mp::number<1>, C>,
      mp::fork<
        mp::pop_front<>,
        mp::rotate_c<-1, mp::pop_front<>>,
        mp::zip_with<
          try_assume_binary<Cmp>,
          mp::try_invoke<mp::or_<mp::not_<try_assume_unary<C>>>>
        >
      >
    >
  >;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, is_sorted<Cmp, C>>
  {
    using type = smp::is_sorted<sfinae<Cmp>, sfinae<C>>;
  };
}
