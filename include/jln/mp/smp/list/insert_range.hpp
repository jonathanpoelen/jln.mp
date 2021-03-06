#pragma once

#include <jln/mp/smp/list/join.hpp>
#include <jln/mp/smp/list/take_front.hpp>
#include <jln/mp/smp/list/drop_front.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/smp/functional/tee.hpp>
#include <jln/mp/list/insert_range.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class>
  struct _smp_insert_range_dispatch;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ i, class seq, class C = listify>
  using insert_range_c = typename detail::_smp_insert_range_dispatch<seq>
    ::template f<i, C>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(insert_range, (I), (seq), (C, smp::listify),
  smp::insert_range_c<I::value, seq, C>)

/// \cond
namespace jln::mp::detail
{
  template<class... xs>
  struct _smp_insert_range_dispatch<list<xs...>>
  {
    template<int_ i, class C>
    using f = test_contract<
      size<greater_equal_than_c<i>>,
      tee<take_front_c<i>, always<list<xs...>>, drop_front_c<i>, join<subcontract<C>>>
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
/// \endcond
