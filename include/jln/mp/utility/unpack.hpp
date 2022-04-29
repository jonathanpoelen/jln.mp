#pragma once

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template <class C, class L, class... xs> struct _unpack {};
    template <class C, class L, class... xs> struct _unpack_append {};
  }
  /// \endcond

  /// \ingroup utility

  /// Turns a \typelist into a \sequence of those types.
  /// \semantics
  ///   \code
  ///   unpack<F>::f<typelist<xs...>, ys...> == F::f<ys..., xs...>
  ///   \endcode
  /// \treturn \sequence
  template<class C>
  struct unpack
  {
    template<class seq, class... xs>
    using f = typename detail::_unpack<C, seq, xs...>::type;
  };

  /// Turns a \typelist into a \sequence of those types.
  /// \semantics
  ///   \code
  ///   unpack_append<F>::f<typelist<xs...>, ys...> == F::f<xs..., ys...>
  ///   \endcode
  /// \treturn \sequence
  template<class C>
  struct unpack_append
  {
    template<class seq, class... xs>
    using f = typename detail::_unpack_append<C, seq, xs...>::type;
  };

  namespace emp
  {
    template<class L, class C, class... xs>
    using unpack = typename detail::_unpack<C, L, xs...>::type;

    template<class L, class C, class... xs>
    using unpack_append = typename detail::_unpack_append<C, L, xs...>::type;
  }
} // namespace jln::mp


#include <jln/mp/list/listify.hpp>
#include <jln/mp/functional/call.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class C, template<class...> class Seq, class... ys, class... xs>
  struct _unpack<C, Seq<ys...>, xs...>
  {
    using type = typename C::template f<xs..., ys...>;
  };

  template<class C, template<class...> class Seq, class... xs, class... ys>
  struct _unpack_append<C, Seq<xs...>, ys...>
  {
    using type = typename C::template f<xs..., ys...>;
  };

  template<class C>
  struct optimize_useless_unpack
  {
    using type = C;
  };

  template<>
  struct optimize_useless_unpack<unpack<listify>>
  {
    using type = identity;
  };

  template<>
  struct optimize_useless_unpack<unpack_append<listify>>
  {
    using type = identity;
  };

  template<class C>
  using optimize_useless_unpack_t = typename optimize_useless_unpack<C>::type;
}
/// \endcond
