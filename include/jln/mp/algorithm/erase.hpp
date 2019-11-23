#pragma once

#include "../list/join.hpp"
#include "../list/drop.hpp"
#include "../list/take.hpp"
#include "../functional/call.hpp"

#include <algorithm>

namespace jln::mp
{
  template<class i, class count = number<1>, class C = listify>
  struct erase
  {
    template<class... xs>
    using f = call<
      join<C>,
      typename take<i>::template f<xs...>,
      call<drop_c<std::min<std::size_t>(
        sizeof...(xs),
        detail::validate_index<i::value, sizeof...(xs)>::value
        + std::size_t{count::value}
      )>, xs...>
    >;
  };

  template<int_ i, int_ count = 1, class C = listify>
  using erase_c = erase<number<i>, number<count>, C>;

  namespace emp
  {
    template<class L, class i, class count = mp::number<1>, class C = mp::listify>
    using erase = eager<L, mp::erase<i, count, C>>;

    template<class L, int_ i, int_ count = 1, class C = mp::listify>
    using erase_c = erase<L, number<i>, number<count>, C>;
  }
}
