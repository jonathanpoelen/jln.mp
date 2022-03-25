#pragma once

#include <jln/mp/algorithm/same.hpp>
#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/functional/try.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct _group;
  }
  /// \endcond

  /// \ingroup group

  /// Groups adjacent elements that respect a predicate.
  /// \semantics
  ///   \code
  ///   group_by<same<>>::f<void, void, int, void>
  ///   == list<
  ///     list<void, void>,
  ///     list<int>,
  ///     list<void>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  template<class Cmp, class C = listify>
  struct group_by
  {
    template<class... xs>
    using f = typename detail::_group<sizeof...(xs) != 0>
      ::template f<C, Cmp, xs...>;
  };

  template<class C = listify>
  using group = group_by<same<>, C>;

  namespace emp
  {
    template<class L, class Cmp, class C = mp::listify>
    using group_by = unpack<L, mp::group_by<Cmp, C>>;

    template<class L, class C = mp::listify>
    using group = unpack<L, mp::group<C>>;
  }
}


#include <jln/mp/algorithm/split.hpp>
#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/push_front.hpp>
#include <jln/mp/functional/lift.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class x, class C>
  struct _group_insert_x
  {
    template<class seq, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(
      xs, C,
      typename detail::_unpack<seq>::template f<push_front<x>>,
      xs...
    );
  };

  template<class x, class F, class C>
  struct _group_insert_x<x, transform<unpack<F>, C>>
  {
    template<class seq, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(
      xs, C,
      typename detail::_unpack<seq>::template f<push_front<x, F>>,
      typename detail::_unpack<xs>::template f<F>...
    );
  };

  template<class...>
  struct _group_impl;

  template<class C, class Cmp, class x, class... xs, class... ys>
  struct _group_impl<C, Cmp, x, list<ys...>, xs...>
  {
    using type = typename fold_right<lift_t<split_state>, unpack<_group_insert_x<x, C>>>
      ::template f<list<list<>>,
                   list<number<Cmp::template f<ys, xs>::value
                     ? split_keep : split_before>, xs>...
      >;
  };

  template<class... ys>
  struct _smp_group_impl
  {
    template<class C, class Cmp, class x, class... xs>
    using f = typename fold_right<lift_t<split_state>, unpack<_group_insert_x<x, C>>>
      ::template f<list<list<>>,
                   list<number<Cmp::template f<ys, xs>::value
                     ? split_keep : split_before>, xs>...
      >;
  };

  template<class C, class Cmp, class TC, class FC, class x, class... xs, class... ys>
  struct _group_impl<C, try_<Cmp, TC, FC>, x, list<ys...>, xs...>
  {
    using type = typename try_<_smp_group_impl<ys...>>
      ::template f<C, try_<Cmp, TC, FC>, x, xs...>;
  };

  template<>
  struct _group<true>
  {
    template<class C, class Cmp, class x, class... xs>
    using f = typename _group_impl<
      C, Cmp, x,
      typename take_front_c<sizeof...(xs)>::template f<x, xs...>,
      xs...
    >::type;
  };

  template<>
  struct _group<false>
  {
    template<class C, class>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };
}
/// \endcond
