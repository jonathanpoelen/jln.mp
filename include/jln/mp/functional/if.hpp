#pragma once

#include "conditional.hpp"

namespace jln::mp
{
  template<class predicate, class true_continuation, class false_continuation>
  struct if_
  {
    template<class... xs>
    using f = typename mp::conditional_c<predicate::template f<xs...>::value>
      ::template f<true_continuation, false_continuation>
      ::template f<xs...>;
  };

  namespace eager
  {
    template<class predicate, class true_continuation, class false_continuation, class... xs>
    using if_ = typename mp::conditional_c<predicate::template f<xs...>::value>
      ::template f<true_continuation, false_continuation>
      ::template f<xs...>;
  }
} // namespace jln::mp
