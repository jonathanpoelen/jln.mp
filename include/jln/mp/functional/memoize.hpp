// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/compiler.hpp>
#include <jln/mp/utility/conditional.hpp>

namespace jln::mp
{
  /// Value that is not available.
  /// This type is used in `smp` for a contract that is not respected.
  struct na {};

#if !JLN_MP_HAS_MEMOIZED_ALIAS || JLN_MP_WORKAROUND(JLN_MP_MSVC, < 1942)

# if !JLN_MP_CUDA
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

# else // if JLN_MP_CUDA

  /// \cond
  namespace detail
  {
    template<class dummy, class F, class... Params>
    struct memoizer_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Memoization version of \link call.
  template<class C, class... xs>
  using memoize_call = typename detail::memoizer_impl<void, C, xs...>::type;

  /// Memoize a call to \c C::f<xs...>.
  template<class C>
  struct memoize
  {
    template<class... xs>
    using f = typename detail::memoizer_impl<void, C, xs...>::type;
  };

# endif

# define JLN_MP_MEMOIZE(...) ::jln::mp::memoize<__VA_ARGS__>

#else // if JLN_MP_HAS_MEMOIZED_ALIAS && !JLN_MP_WORKAROUND(JLN_MP_MSVC, < 1942)
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


// # if !JLN_MP_CUDA
#include <jln/mp/list/list.hpp>
#include <jln/mp/utility/void_t.hpp>
// # endif

/// \cond
namespace jln::mp::detail
{
#if JLN_MP_HAS_MEMOIZED_ALIAS
# define JLN_MP_SIMPLE_MEMOIZER(...) __VA_ARGS__
#else
  template<class F, class... xs>
  struct simple_memoizer_impl
  {
    using type = typename F::template f<xs...>;
  };

  template<class F>
  struct simple_memoizer
  {
    template<class... xs>
    using f = typename simple_memoizer_impl<F, xs...>::type;
  };
# define JLN_MP_SIMPLE_MEMOIZER(...) ::jln::mp::detail::simple_memoizer<__VA_ARGS__>
#endif
}

#if !JLN_MP_HAS_MEMOIZED_ALIAS || JLN_MP_WORKAROUND(JLN_MP_MSVC, < 1942)

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

# if !JLN_MP_CUDA
  template<class F, class... Params, class P>
  memoize_result<
#   if JLN_MP_FEATURE_TYPE_PACK_ELEMENT
    typename __type_pack_element<!sizeof(P), F, F>
#   else
    typename conditional_c<!sizeof(P)>
    ::template f<F, F>
#   endif
    ::template f<Params...>
  > memoized_call(P);

  template<class F, class...>
  uncallable_function memoized_call(char);

  template<class C, class... Params>
  struct memoizer_impl : decltype(memoized_call<C, Params...>(1))
  {};
#else // if JLN_MP_CUDA
  template<class dummy, class F, class... Params>
  struct memoizer_impl : uncallable_function
  {};

  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Wattributes")
  template<class F, class... Params>
  struct memoizer_impl<void_t<typename F::template f<Params...>>, F, Params...>
    : memoize_result<typename F::template f<Params...>>
  {};
  JLN_MP_DIAGNOSTIC_POP()
# endif
}
#else // if JLN_MP_HAS_MEMOIZED_ALIAS && !JLN_MP_WORKAROUND(JLN_MP_MSVC, < 1942)
namespace jln::mp::detail
{
  struct uncallable_function
  {};
}
#endif
/// \endcond
