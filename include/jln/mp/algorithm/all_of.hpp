#pragma once

#include "../number/number.hpp"
#include "../algorithm/transform.hpp"
#include "../functional/identity.hpp"

namespace jln::mp
{
  // TODO all_of
  // template<class F, class C = identity>
  // using all_of = mp::transform<F, mp::and_<C>>;

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
} // namespace jln::mp
