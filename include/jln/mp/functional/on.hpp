#pragma once

#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template <class C, class... Fs>
    struct _on;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions each taking the parameter corresponding to its position
  /// (or without parameter whether it does not exist)
  /// then calls \c C with the results and the rest of the parameters.
  /// \semantics
  ///   \code
  ///   on<F,G,C>::f<a> == C::f<F::f<a>, G::f<>>
  ///   on<F,G,C>::f<a,b,c,d> == C::f<F::f<a>, G::f<b>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see each, tee, partial
#ifdef JLN_MP_DOXYGENATING
  template <class... Fs, class C>
  struct on
  {
    template<class... xs>
    using f;
  };
#else
  template <class... Fs>
  struct on
  : rotate<number<-1>, lift<detail::_on>>
  ::template f<Fs...>
  {};
#endif
}

#include <jln/mp/list/join.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/functional/each.hpp>
#include <jln/mp/functional/tee.hpp>

/// \cond
namespace jln::mp::detail
{
  constexpr int on_select(std::size_t nf, std::size_t nx)
  {
    return (nf < nx) ? 1 : (nf > nx) ? 2 : 0;
  }

  template <int, class C, class... Fs>
  struct _on_select;

  // each
  template <class C, class... Fs>
  struct _on_select<0, C, Fs...>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_XS(xs, C, typename Fs::template f<xs>...);
  };

  // partial
  template <class C, class... Fs>
  struct _on_select<1, C, Fs...>
  {
    template<class... xs>
    using f = typename _join_select<2>::f<
      C,
      typename take_front_c<sizeof...(Fs), _each<listify, Fs...>>::template f<xs...>,
      typename drop_front_c<sizeof...(Fs)>::template f<xs...>
    >::type;
  };

  template <class C, class... Fs>
  struct _on_select<2, C, Fs...>
  {
    template<class... xs>
    using f = typename _join_select<2>::f<
      C,
      typename take_front_c<sizeof...(xs)+1, lift<_each>>
        ::template f<listify, Fs...>
        ::template f<xs...>,
      typename drop_front_c<sizeof...(xs), lift<tee>>
        ::template f<Fs..., listify>
        ::template f<>
    >::type;
  };

  template <class C, class... Fs>
  struct _on
  {
    template<class... xs>
    using f = typename _on_select<on_select(sizeof...(Fs), sizeof...(xs)), C, Fs...>
      ::template f<xs...>;
  };
} // namespace jln::mp
/// \endcond
