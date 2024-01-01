// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/compiler.hpp>
#include <jln/mp/utility/conditional.hpp>

namespace jln::mp
{
  /// Value that is not available.
  /// This type is used in `smp` for a contract that is not respected.
  struct na {};

#if !JLN_MP_MEMOIZED_ALIAS
  /// \cond
  namespace detail
  {
    template<class F, class... Params>
    struct memoizer_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Memoization version of \link call.
  template<class C, class... xs>
  using memoize_call = typename detail::memoizer_impl<C, xs...>::type;

  /// Memoize a call to \c C::f<xs...>.
  template<class C>
  struct memoize
  {
    template<class... xs>
    using f = typename detail::memoizer_impl<C, xs...>::type;
  };

# define JLN_MP_MEMOIZE(...) ::jln::mp::memoize<__VA_ARGS__>

#else
  template<class C, class... xs>
  using memoize_call = typename conditional_c<!sizeof...(xs)>
    ::template f<C, C>
    ::template f<xs...>;

  template<class C>
  struct memoize
  {
    template<class... xs>
    using f = typename conditional_c<!sizeof...(xs)>
      ::template f<C, C>
      ::template f<xs...>;
  };

# define JLN_MP_MEMOIZE(...) __VA_ARGS__
#endif
}

/// \cond
#if !JLN_MP_MEMOIZED_ALIAS
#include <jln/mp/list/list.hpp>

namespace jln::mp::detail
{
  struct uncallable_function
  {
    using try_type = na;
  };

  template<class T>
  struct memoize_result
  {
    using type = T;
    using try_type = T;
  };

  template<class F, class... Params>
  memoize_result<
    typename conditional_c<!sizeof...(Params)>
    ::template f<F, F>
    ::template f<Params...>
  > memoized_call(list<Params...>*);

  template<class F>
  uncallable_function memoized_call(void*);

  template<class C, class... Params>
  struct memoizer_impl : decltype(memoized_call<C>(static_cast<list<Params...>*>(nullptr)))
  {};
}
#endif
/// \endcond
