#pragma once

#include <jln/mp/algorithm/rotate.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct _adjacent_difference;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Computes the differences between adjacent_difference pair of elements.
  /// \semantics
  ///   \code
  ///   adjacent_difference_difference<C>::f<a, b, c> = C::f<a, sub::f<a, b>, sub::f<b, c>>
  ///   \endcode
  /// \treturn \sequence
  template<class C = listify>
  struct adjacent_difference
  {
    template<class... xs>
    using f = typename detail::_adjacent_difference<
      rotate_c<-1>::template f<xs...>
    >::template f<C, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using adjacent_difference = unpack<L, mp::adjacent_difference<C>>;
  }
}

#include <jln/mp/detail/compiler.hpp>

/// \cond
namespace jln::mp::detail
{
#if JLN_MP_MSVC
  template<class C, class x, int_... xs>
  using _adjacent_difference_msvc = JLN_MP_CALL_TRACE(C, x, number<xs>...);
#endif

  template<class y, class... ys>
  struct _adjacent_difference<list<y, ys...>>
  {
#if JLN_MP_MSVC
    template<class C, class x, class... xs>
    using f = _adjacent_difference_msvc<C, x, (xs::value - ys::value)...>;
#else
    template<class C, class x, class... xs>
    using f = JLN_MP_CALL_TRACE(C, x, number<xs::value - ys::value>...);
#endif
  };

  template<>
  struct _adjacent_difference<list<>>
  {
    template<class C, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };
}
/// \endcond
