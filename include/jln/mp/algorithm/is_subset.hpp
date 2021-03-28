#pragma once

#include <jln/mp/algorithm/is_disjoint.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct _is_subset;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether \value in `seqs[0]` are subset from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \number
  /// \see is_subset
  template<class Equal = lift<std::is_same>, class C = identity>
  struct is_subset_with
  {
    template<class... seqs>
    using f = typename C::template f<number<
      detail::_is_subset<detail::min(3, sizeof...(seqs))>
      ::template f<detail::to_not_fn_t<Equal>, seqs...>
      ::value
    >>;
  };

  /// Checks whether \value in `seqs[0]` are subset from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \number
  /// \see is_subset_with
  template<class C = identity>
  using is_subset = is_subset_with<lift<std::is_same>, C>;

  namespace emp
  {
#ifdef JLN_MP_DOXYGENATING
    template<class L1, class L2, class C = mp::identity>
    using is_subset = typename is_subset<C>::template f<L1, L2>;

    template<class L1, class L2, class Equal = lift<std::is_same>, class C = mp::identity>
    using is_subset_with = typename is_subset_with<Equal, C>::template f<L1, L2>;
#endif
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class NotEqual, class... xs>
  struct _is_subset_of
  {
    template<class x>
    using f = number<!std::is_same<_drop_while_continue, typename _drop_while<
      n_8_or_more_16_32_64_128_256(sizeof...(xs)), true
    >::template f<0, push_back<x, NotEqual>, xs...>>::value>;
  };

  template<>
  struct _is_subset<0>
  {
    template<class NotEqual, class... xs>
    using f = true_;
  };

  template<>
  struct _is_subset<1> : _is_subset<0>
  {};

  template<class NotEqual, class seq0>
  using to_is_subset_impl = is_disjoint_impl<
    typename _unpack<seq0>::template f<
      if_<
        size<>,
        lift<_is_subset_of>,
        always<size<not_<>>>
      >,
      NotEqual
    >
  >;

  template<>
  struct _is_subset<2>
  {
    template<class NotEqual, class seq0, class seq1>
    using f = typename _unpack<seq1>
      ::template f<to_is_subset_impl<NotEqual, seq0>>;
  };

  template<>
  struct _is_subset<3>
  {
    template<class NotEqual, class seq0, class... seqs>
    using f = number<std::is_same<_drop_while_continue, typename _drop_while<
      n_8_or_more_16_32_64_128_256(sizeof...(seqs)), true
    >::template f<
      0,
      unpack<to_is_subset_impl<NotEqual, seq0>>,
      seqs...
    >>::value>;
  };
}

#ifndef JLN_MP_DOXYGENATING
namespace jln::mp::emp
{
  template<class L1, class L2, class C = mp::identity>
  using is_subset = typename C::template f<number<
    detail::_is_subset<2>::f<mp::lift<std::is_same, mp::not_<>>, L1, L2>::value
  >>;

  template<class L1, class L2, class Equal = lift<std::is_same>, class C = mp::identity>
  using is_subset_with = typename C::template f<number<
    detail::_is_subset<2>::f<detail::to_not_fn_t<Equal>, L1, L2>::value
  >>;
}
#endif
/// \endcond
