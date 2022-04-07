#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/take_front.hpp>
#include <jln/mp/smp/list/drop_front.hpp>
#include <jln/mp/smp/functional/tee.hpp>
#include <jln/mp/algorithm/split_at.hpp>

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_smp_split_at;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ i, class F = listify, class C = listify>
  using split_at_with_c = typename detail::mk_smp_split_at<i >= 0>
    ::template f<i, C, mp::split_at_with_c, assume_binary<F>>;

  template<int_ i, class C = listify>
  using split_at_c = typename detail::mk_smp_split_at<i >= 0>
    ::template f<i, C, mp::split_at_c>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(split_at, (I), (C, smp::listify), smp::split_at_c<I::value, C>)
JLN_MP_MAKE_REGULAR_SMP3_P(split_at_with,
  (I), (F, smp::listify), (C, smp::listify), smp::split_at_with_c<I::value, F, C>)


#include <jln/mp/number/operators.hpp>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct mk_smp_split_at<true>
  {
    template<int_ i, class C, template<unsigned, class...> class Tpl, class... F>
    using f = test_contract<
      mp::size<mp::greater_equal_than_c<i>>,
      Tpl<i, F..., assume_binary_list<C>>>;
  };

  template<>
  struct mk_smp_split_at<false>
  {
    template<int_ i, class C, template<unsigned, class...> class Tpl, class... F>
    using f = bad_contract;
  };
}
/// \endcond
