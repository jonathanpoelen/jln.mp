#pragma once

#include "../list/size.hpp"
#include "../list/list.hpp"
#include "../list/take.hpp"
#include "../utility/eager.hpp"
#include "../functional/each.hpp"
#include <algorithm>

namespace jln::mp
{
  namespace detail
  {
    struct _drop_back
    {
      template<int_ min, class n>
      using impl = typename conditional_c<min != n::value>
        ::template f<unpack<take_c<min>>, identity>;

      template<class C, class... ns>
      using f = _each<C, impl<std::min({int_(~0u), ns::value...}), ns>...>;
    };
  }

  template<class C = listify>
  struct matrix_shortest
  {
    template<class... seqs>
    using f = typename detail::_drop_back::f<C, unpack<size<>>::f<seqs>...>
      ::template f<seqs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using matrix_shortest = eager<L, mp::matrix_shortest<C>>;
  }
}
