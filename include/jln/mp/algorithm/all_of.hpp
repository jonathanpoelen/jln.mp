#pragma once

#include "../number/number.hpp"
#include "../functional/identity.hpp"

namespace jln::mp
{
  template<class predicate, class continuation = identity>
  struct all_of
  {
    template<class... xs>
    using f = typename continuation::template f<number<
      (predicate::template f<xs>::value && ... && true)>>;
  };

  namespace emp
  {
    template<class predicate, class... xs>
    using all_of = number<(predicate::template f<xs>::value && ... && true)>;

    template<class predicate, class... xs>
    constexpr inline bool all_of_v = (predicate::template f<xs>::value && ... && true);
  }

  namespace smp
  {
    template<class predicate, class continuation>
    using all_of = when<is_invocable_predicate<predicate>,
      mp::all_of<predicate, when_continuation<continuation>>>;
  }
} // namespace jln::mp


namespace jln::mp::detail
{
  template<template<class> class sfinae, class predicate, class continuation>
  struct _sfinae<sfinae, all_of<predicate, continuation>>
  {
    using type = smp::all_of<sfinae<predicate>, sfinae<continuation>>;
  };
}
