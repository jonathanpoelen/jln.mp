#pragma once

#include "../number/number.hpp"
#include "../functional/identity.hpp"

namespace jln::mp
{
  template<class predicate, class continuation = identity>
  struct all_of
  {
    template<class... xs>
    using f = typename continuation::template f<number<(predicate::template f<xs>::value && ... && true)>>;
  };
} // namespace jln::mp
