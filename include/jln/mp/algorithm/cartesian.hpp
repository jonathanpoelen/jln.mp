#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/detail/enumerate.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class, unsigned>
    struct _cartesian;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Computes the cartesian product of \lists.
  /// \pre `emp::is_list<seqs> && ...`
  /// \post `sizeof...(result) == (emp::size<seqs> * ...)` if `sizeof...(xs) != 0` else `0`
  /// \semantics
  ///   \code
  ///   cartesian<listify>::f<
  ///     list<_0, _1, _2>,
  ///     list<_3, _4>,
  ///     list<_5>
  ///   > = list<
  ///     list<_0, _3, _5>, list<_0, _4, _5>,
  ///     list<_1, _3, _5>, list<_1, _4, _5>,
  ///     list<_2, _3, _5>, list<_2, _4, _5>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class C = listify>
  struct cartesian
  {
    template<class... seqs>
    using f = typename detail::_cartesian<C, detail::min(2, sizeof...(seqs))>
      ::template f<seqs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using cartesian = unpack<L, cartesian<C>>;
  }
}


#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/algorithm/fold_left.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/functional/call.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class, class>
  struct _product;

  template<class... xs, class... ys>
  struct _product<list<xs...>, list<ys...>>
  {
    using type = list<list<xs..., ys>...>;
  };

  template<class... ys>
  struct _product<list<>, list<ys...>>
  {
    using type = list<>;
  };

  template<class>
  struct _product1;

  template<class... xs>
  struct _product1<list<xs...>>
  {
    using type = list<list<xs>...>;
  };

  template<class C>
  struct _cartesian<C, 0>
  {
    template<class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  template<>
  struct _cartesian<listify, 0>
  {
    template<class...>
    using f = list<>;
  };

  template<class C>
  struct _cartesian<C, 1>
  {
    template<class seq>
    using f = JLN_MP_CALL_TRACE(C, typename _product1<seq>::type);
  };

  template<>
  struct _cartesian<listify, 1>
  {
    template<class seq>
    using f = typename _product1<seq>::type;
  };

  template<class, class>
  struct _cartesian_impl;

  template<class... seqs, class seq>
  struct _cartesian_impl<list<seqs...>, seq>
  {
    using type = typename join<>
      ::f<typename _product<seqs, seq>::type...>;
  };

  template<class C, unsigned n>
  struct _cartesian
  {
    template<class seq, class... seqs>
    using f = typename fold_left<lift_t<detail::_cartesian_impl>, unpack<C>>
      ::template f<typename _product1<seq>::type, seqs...>;
  };

  template<unsigned n>
  struct _cartesian<listify, n>
  {
    template<class seq, class... seqs>
    using f = typename fold_left<lift_t<detail::_cartesian_impl>>
      ::template f<typename _product1<seq>::type, seqs...>;
  };
}
/// \endcond
