#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/algorithm/fold_left.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class, class>
    struct product_impl;

    template<class x, class y>
    using product_impl_t = typename product_impl<x, y>::type;

    template<class, class>
    struct _product;
  }
  /// \endcond

  /// \ingroup group

  /// Computes the cartesian product of \lists.
  /// \pre `emp::is_list<seqs> && ...`
  /// \post `sizeof...(result) == (emp::size<seqs> * ...)` if `sizeof...(xs) != 0` else `0`
  /// \semantics
  ///   \code
  ///   call<product<listify>,
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
  struct product
  {
    template<class seq = list<>, class... seqs>
    using f = typename detail::_unpack<
      typename detail::fold_left_impl<sizeof...(seqs)>
      ::template f<
        detail::product_impl_t,
        typename detail::_product<list<>, seq>::type,
        seqs...
      >
    >::template f<C>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using product = unpack<L, product<C>>;
  }

  /// \cond
  template<>
  struct product<listify>
  {
    template<class seq = list<>, class... seqs>
    using f = typename detail::fold_left_impl<sizeof...(seqs)>
      ::template f<
        detail::product_impl_t,
        typename detail::_product<list<>, seq>::type,
        seqs...
      >;
  };
  /// \endcond
}


#include <jln/mp/list/join.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class... xs, class... ys>
  struct _product<list<xs...>, list<ys...>>
  {
    using type = list<list<xs..., ys>...>;
  };

  template<class... seqs, class seq>
  struct product_impl<list<seqs...>, seq>
  : detail::_join_select<sizeof...(seqs)>
    ::template f<list, typename _product<seqs, seq>::type...>
  {};
}
/// \endcond
