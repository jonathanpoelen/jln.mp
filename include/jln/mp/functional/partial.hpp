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
    template<class C, class... Fs>
    struct _partial;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions each taking the parameter corresponding to its position
  /// (or without parameter whether it does not exist)
  /// then calls \c C with the results and the rest of the parameters.
  /// \semantics
  ///   \code
  ///   partial<F,G,C>::f<a> == C::f<F::f<a>, G::f<>>
  ///   partial<F,G,C>::f<a,b,c,d> == C::f<F::f<a>, G::f<b>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see each, tee, partial
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, lift<detail::_partial>, Fs...>
  {};
#endif
}

#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/functional/each.hpp>
#include <jln/mp/functional/bind_front.hpp>

/// \cond
namespace jln::mp::detail
{
  constexpr int on_select(std::size_t nf, std::size_t nx)
  {
    return nf < nx ? 1 : nf > nx ? 2 : 0;
  }

  template<int, class C, class... Fs>
  struct _partial_select;

  // each (sizeof...(Fs) == sizeof...(xs))
  template<class C, class... Fs>
  struct _partial_select<0, C, Fs...>
  : _each<C, Fs...>
  {};

  template<class... Fs>
  struct partial_prefix
  {
    template<class C, class... xs>
    using f = bind_front<C, typename JLN_MP_TRACE_F(Fs)::template f<xs>...>;
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class... Fs>
  struct _partial_select<1, C, Fs...>
  {
    template<class... xs>
    using f = typename drop_front_impl<
      (sizeof...(xs) & 0) + sizeof...(Fs)
    >::template f<
      sizeof...(Fs),
      // take_front
      rotate_impl<(sizeof...(xs) & 0) + sizeof...(Fs)+1>
      ::template f<
        sizeof...(Fs)+1,
        drop_front_c<sizeof...(xs) - sizeof...(Fs), partial_prefix<Fs...>>,
        C, xs...>
      ::template f,
      xs...
    >;
  };

  template<class... Fs>
  struct partial_suffix
  {
    template<class C>
    using f = typename C::template f<typename JLN_MP_TRACE_F(Fs)::template f<>...>;
  };

  // sizeof...(Fs) > sizeof...(xs)
  template<class C, class... Fs>
  struct _partial_select<2, C, Fs...>
  {
    template<class... xs>
    using f = typename drop_front_c<sizeof...(xs), lift<partial_suffix>>
      ::template f<Fs...>
      ::template f<
        // take_front
        typename rotate_impl<sizeof...(xs)>
        ::template f<
          sizeof...(xs),
          drop_front_c<sizeof...(Fs) - sizeof...(xs), lift<partial_prefix>>,
          Fs...>
        ::template f<C, xs...>
      >;
  };

  template<class C, class... Fs>
  struct _partial
  {
    template<class... xs>
    using f = typename _partial_select<on_select(sizeof...(Fs), sizeof...(xs)), C, Fs...>
      ::template f<xs...>;
  };
} // namespace jln::mp
/// \endcond
