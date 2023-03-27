#pragma once

#include <jln/mp/list/list.hpp>
#include <jln/mp/config/debug.hpp>
#include <jln/mp/utility/conditional.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    class uncallable_function
    {
      template<class... xs>
      using f = typename conditional_c<!sizeof...(xs)>
        ::template f<uncallable_function, uncallable_function>
        ::template g<xs...>;
    };

    template<class Function, class Params, class Error = uncallable_function>
    struct memoizer_impl
    {
      using type = typename Error::type;
    };

    template<class F, class... xs>
    using _memoizer = memoizer_impl<F, list<xs...>>;

    template<template<class...> class Function, class Params, class = void>
    struct _memoizerf_impl
    {};

    template<template<class...> class F, class... xs>
    using _memoizerf = _memoizerf_impl<F, list<xs...>>;
  }
  /// \endcond

  /// \ingroup functional

  /// Memoization version of \link call.
  template<class C, class... xs>
  using memoize_call = typename detail::memoizer_impl<C, list<xs...>>::type;

  /// Memoize a call to \c C::f<xs...>.
  template<class C>
  struct memoize
  {
    template<class... xs>
    using f = typename detail::memoizer_impl<C, list<xs...>>::type;
  };
}

/// \cond
namespace jln::mp::detail
{
  template<class x, class...>
  using _first = x;

  template<class Function, class... Params>
  struct memoizer_impl<Function, list<Params...>,
    _first<uncallable_function, typename Function::template f<Params...>>>
  {
    using type = typename Function::template f<Params...>;
  };

  template<template<class...> class Function, class... Params>
  struct _memoizerf_impl<Function, list<Params...>,
    _first<uncallable_function, Function<Params...>>>
  {
    using type = Function<Params...>;
  };
}
/// \endcond
