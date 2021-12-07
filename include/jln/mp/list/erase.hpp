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
  template<unsigned start, unsigned size = 1, class C = listify>
  struct erase_c
  {
    template<class... xs>
    using f = typename join<C>::template f<
      typename take_front_c<start>::template f<xs...>,
      typename drop_front_c<detail::min(
        sizeof...(xs),
        start + size
      )>::template f<xs...>
    >;
  };

  template<class start, class size = number<1>, class C = listify>
  using erase = erase_c<start::value, size::value, C>;

  namespace emp
  {
    template<class L, class start, class size = mp::number<1>, class C = mp::listify>
    using erase = unpack<L, mp::erase<start, size, C>>;

    template<class L, unsigned start, unsigned size = 1, class C = mp::listify>
    using erase_c = unpack<L, mp::erase_c<start, size, C>>;
  }
}
