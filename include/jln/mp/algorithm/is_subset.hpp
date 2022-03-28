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
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::_is_subset<detail::min(3, sizeof...(seqs))>
      ::template f<JLN_MP_TRACE_F(Equal), seqs...>
    );
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


#include <jln/mp/list/is_empty.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Equal, class... xs>
  struct _is_subset_of
  {
    template<class x>
    using f = number<!is_drop_while_continue<
      typename _drop_until<sizeof...(xs)>::template f<0, push_back<x, Equal>, xs...>
    >::type::value>;
  };

  template<>
  struct _is_subset<0> : _is_disjoint<0>
  {};

  template<>
  struct _is_subset<1> : _is_disjoint<0>
  {};

  template<class Equal, class seq0>
  using to_is_subset_impl = is_disjoint_impl<
    typename _unpack<seq0>::template f<lift<_is_subset_of>, Equal>
  >;

  template<>
  struct _is_subset<2>
  {
    template<class Equal, class seq0, class seq1>
    using f = typename _unpack<seq1>
      ::template f<to_is_subset_impl<Equal, seq0>>;
  };

  template<>
  struct _is_subset<3>
  {
    template<class Equal, class seq0, class... seqs>
    using f = typename detail::is_drop_while_continue<
      typename _drop_while<sizeof...(seqs)>::template f<
        0,
        unpack<to_is_subset_impl<Equal, seq0>>,
        seqs...
    >>::type;
  };
}

#ifndef JLN_MP_DOXYGENATING
namespace jln::mp::emp
{
  template<class L1, class L2, class C = mp::identity>
  using is_subset = typename C::template f<
    typename detail::_is_subset<2>::f<mp::lift<std::is_same>, L1, L2>
  >;

  template<class L1, class L2, class Equal = lift<std::is_same>, class C = mp::identity>
  using is_subset_with = typename C::template f<
    typename detail::_is_subset<2>::f<Equal, L1, L2>
  >;
}
#endif
/// \endcond
