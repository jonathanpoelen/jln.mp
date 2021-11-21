#pragma once

#include <jln/mp/list/join.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/take_front.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Removes all elements between two arbitrary indices of a sequence.
  /// \pre `0 <= start < sizeof...(xs)`
  /// \pre `0 <= start + size < sizeof...(xs)`
  /// \treturn \sequence
  template<class start, class size = number<1>, class C = listify>
  struct erase
  {
    template<class... xs>
    using f = typename join<C>::template f<
      typename take_front<start>::template f<xs...>,
      typename drop_front_c<detail::min(
        sizeof...(xs),
        start::value + size::value
      )>::template f<xs...>
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
