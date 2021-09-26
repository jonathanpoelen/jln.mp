#pragma once

#include <jln/mp/functional/lift.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/detail/enumerate.hpp>
#include <jln/mp/functional/not_fn.hpp>

#include <type_traits>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct _is_disjoint;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether \value in `seqs[0]` are disjoint from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \number
  /// \see is_disjoint
  template<class Equal = lift<std::is_same>, class C = identity>
  struct is_disjoint_with
  {
    template<class... seqs>
    using f = typename C::template f<number<
      detail::_is_disjoint<detail::min(3, sizeof...(seqs))>
      ::template f<detail::to_not_fn_t<Equal>, seqs...>
      ::value
    >>;
  };

  /// Checks whether \value in `seqs[0]` are disjoint from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \number
  /// \see is_disjoint_with
  template<class C = identity>
  using is_disjoint = is_disjoint_with<lift<std::is_same>, C>;

  namespace emp
  {
#ifdef JLN_MP_DOXYGENATING
    template<class L1, class L2, class C = mp::identity>
    using is_disjoint = typename is_disjoint<C>::template f<L1, L2>;

    template<class L1, class L2, class Equal = lift<std::is_same>, class C = mp::identity>
    using is_disjoint_with = typename is_disjoint_with<Equal, C>::template f<L1, L2>;
#endif
  }
}


#include <jln/mp/algorithm/drop_while.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/utility/always.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Pred>
  struct is_disjoint_impl
  {
    template<class... xs>
    using f = std::is_same<_drop_while_continue, typename _drop_while<
      n_8_or_less_16_32_64_128_256(sizeof...(xs)), true
    >::template f<0, Pred, xs...>>;
  };

  template<class NotEqual, class... xs>
  struct _is_disjoint_of
  {
    template<class x>
    using f = std::is_same<_drop_while_continue, typename _drop_while<
      n_8_or_less_16_32_64_128_256(sizeof...(xs)), true
    >::template f<0, push_back<x, NotEqual>, xs...>>;
  };

  template<>
  struct _is_disjoint<0>
  {
    template<class NotEqual, class... xs>
    using f = true_;
  };

  template<>
  struct _is_disjoint<1> : _is_disjoint<0>
  {};

  template<class NotEqual, class seq0>
  using to_is_disjoint_impl = is_disjoint_impl<
    typename _unpack<seq0>::template f<lift<_is_disjoint_of>, NotEqual>
  >;

  template<>
  struct _is_disjoint<2>
  {
    template<class NotEqual, class seq0, class seq1>
    using f = typename _unpack<seq1>
      ::template f<to_is_disjoint_impl<NotEqual, seq0>>;
  };

  template<>
  struct _is_disjoint<3>
  {
    template<class NotEqual, class seq0, class... seqs>
    using f = std::is_same<_drop_while_continue, typename _drop_while<
      n_8_or_less_16_32_64_128_256(sizeof...(seqs)), true
    >::template f<
      0,
      unpack<to_is_disjoint_impl<NotEqual, seq0>>,
      seqs...
    >>;
  };
}

#ifndef JLN_MP_DOXYGENATING
namespace jln::mp::emp
{
  template<class L1, class L2, class C = mp::identity>
  using is_disjoint = typename C::template f<number<
    detail::_is_disjoint<2>::f<mp::lift<std::is_same, mp::not_<>>, L1, L2>::value
  >>;

  template<class L1, class L2, class Equal = lift<std::is_same>, class C = mp::identity>
  using is_disjoint_with = typename C::template f<number<
    detail::_is_disjoint<2>::f<detail::to_not_fn_t<Equal>, L1, L2>::value
  >>;
}
#endif
/// \endcond
