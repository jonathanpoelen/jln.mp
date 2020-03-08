#pragma once

#include "../list/join.hpp"
#include "../list/take.hpp"
#include "../list/drop.hpp"
#include "../utility/always.hpp"
#include "../functional/fork.hpp"
#include "../../list/insert_range.hpp"

namespace jln::mp::detail
{
  template<class>
  struct _smp_insert_range_dispatch;
}

namespace jln::mp::smp
{
  template<int_ i, class seq, class C = listify>
  using insert_range_c = typename detail::_smp_insert_range_dispatch<seq>
    ::template f<i, C>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(insert_range, (I), (seq), (C, smp::listify),
  smp::insert_range_c<I::value, seq, C>)

namespace jln::mp::detail
{
  template<class... xs>
  struct _smp_insert_range_dispatch<list<xs...>>
  {
    template<int_ i, class C>
    using f = test_contract<
      size<greater_equal_than_c<i>>, 
      fork<take_c<i>, always<list<xs...>>, drop_c<i>, join<subcontract<C>>>
    >;
  };
  
  template<>
  struct _smp_insert_range_dispatch<list<>>
  {
    template<int_ i, class C>
    using f = C;
  };
  
  template<class>
  struct _smp_insert_range_dispatch
  {
    template<int_ i, class C>
    using f = bad_contract;
  };
}
