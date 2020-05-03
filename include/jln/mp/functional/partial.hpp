#pragma once

#include "../algorithm/rotate.hpp"
#include "../number/number.hpp"
#include "function.hpp"
#include "call.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template <class, class...>
    struct _partial;
  }
  /// \endcond

  /// \ingroup functional

  /// Invoke multiple functions each taking the parameter corresponding to its position
  /// then calls `C` with the results and the rest of the parameters.
  /// \pre sizeof...(Fs) >= 1
  /// \pre sizeof...(xs) >= sizeof...(Fs) - 1
  /// \semantics
  ///   \code
  ///   partial\<F,G,C\>::f\<a,b,c,d\> == C::f\<F::f\<a\>, G::f\<b\>, c, d\>
  ///   \endcode
  /// \treturn \value
  /// \see each, fork, partial_eager
  template <class... Fs>
  struct partial
  : rotate<number<-1>, cfe<detail::_partial>>
  ::template f<Fs...>
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f = /* unspecified */;
#endif
  };

  /// \cond
  template <class C>
  struct partial<C>
  {
    template <class... xs>
    using f = call<C, xs...>;
  };

  template <class F, class C>
  struct partial<F, C>
  {
    template <class x, class... xs>
    using f = call<C, call<F, x>, xs...>;
  };

  template <class F0, class F1, class C>
  struct partial<F0, F1, C>
  {
    template <class x0, class x1, class... xs>
    using f = call<C, call<F0, x0>, call<F1, x1>, xs...>;
  };

  template <class F0, class F1, class F2, class C>
  struct partial<F0, F1, F2, C>
  {
    template <class x0, class x1, class x2, class... xs>
    using f = call<C, call<F0, x0>, call<F1, x1>, call<F2, x2>, xs...>;
  };
  /// \endcond
}

#include "each.hpp"
#include "../list/join.hpp"
#include "../algorithm/make_int_sequence.hpp"
#include "../algorithm/transform.hpp"
#include "../utility/always.hpp"

/// \cond
namespace jln::mp::detail
{
  template <class C, class... Fs>
  struct _partial
  {
    template<class... xs>
    using f = typename _join_select<2>::f<
      cfe<_each>,
      list<C, Fs...>,
      emp::make_int_sequence_c<sizeof...(xs) - sizeof...(Fs), transform<always<identity>>>
    >::type::template f<xs...>;
  };
} // namespace jln::mp
/// \endcond
