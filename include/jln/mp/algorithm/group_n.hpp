#pragma once

#include "../list/list.hpp"
#include "../utility/eager.hpp"
#include "../number/number.hpp"


namespace jln::mp
{
  namespace detail
  {
    template<bool>
    struct _group_n;
  }

  template<class n, class C = listify>
  struct group_n
  {
    template<class... xs>
    using f = typename detail::_group_n<sizeof...(xs) != 0 && (n::value > 0)>
      ::template f<C, n::value, xs...>;
  };

  template<int_ n, class C = listify>
  using group_n_c = group_n<number<n>, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using group_n = eager<L, mp::group_n<n, C>>;

    template<class L, int_ n, class C = mp::listify>
    using group_n_c = eager<L, mp::group_n_c<n, C>>;
  }
}


#include "split.hpp"
#include "make_int_sequence.hpp"
#include "../list/pop_front.hpp"

namespace jln::mp::detail
{
  template<int_... i>
  struct _group_n_impl
  {
    template<class C, unsigned long long n, class... xs>
    using f = call<
      fold_right<cfl<split_state>, unpack<pop_front<C>>>,
      list<list<>>,
      list<number<(i % n ? split_keep : split_before)>, xs>...
    >;
  };

  template<>
  struct _group_n<true>
  {
    template<class C, unsigned long long n, class... xs>
    using f = typename emp::make_int_sequence_v_c<
      sizeof...(xs), cfv_v<_group_n_impl>
    >::template f<C, n, xs...>;
  };

  template<>
  struct _group_n<false>
  {
    template<class C, unsigned long long, class...>
    using f = typename C::template f<>;
  };
}