#pragma once

#include "../list/join.hpp"
#include "../list/drop.hpp"
#include "../list/take.hpp"
#include "../functional/call.hpp"

#include <algorithm>

namespace jln::mp
{
  /// \ingroup list

  /// Removes all elements between two arbitrary indices of a sequence.
  /// \pre 0 \<= start \< sizeof...(xs)
  /// \pre 0 \<= start + size \< sizeof...(xs)
  /// \return \sequence
  template<class start, class size = number<1>, class C = listify>
  struct erase
  {
    template<class... xs>
    using f = call<
      join<C>,
      typename take<start>::template f<xs...>,
      call<drop_c<std::min<std::size_t>(
        sizeof...(xs),
        detail::validate_index<start::value, sizeof...(xs)>::value
        + std::size_t{size::value}
      )>, xs...>
    >;
  };

  template<int_ start, int_ size = 1, class C = listify>
  using erase_c = erase<number<start>, number<size>, C>;

  namespace emp
  {
    template<class L, class start, class size = mp::number<1>, class C = mp::listify>
    using erase = unpack<L, mp::erase<start, size, C>>;

    template<class L, int_ start, int_ size = 1, class C = mp::listify>
    using erase_c = erase<L, number<start>, number<size>, C>;
  }
}
