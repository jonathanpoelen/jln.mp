#pragma once

#include <jln/mp/number/numbers.hpp>

#ifdef JLN_MP_DISABLE_INTEGER_SEQUENCE_OPTIMIZATION
#  define JLN_MP_USE_INTEGER_PACK 0
#  define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#elif defined(__has_builtin)
#  if __has_builtin(__make_integer_seq)
#    define JLN_MP_USE_INTEGER_PACK 0
#    define JLN_MP_USE_MAKE_INTEGER_SEQ 1
#  elif __has_builtin(__integer_pack)
#    define JLN_MP_USE_INTEGER_PACK 1
#    define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#  endif
#elif defined(_MSC_VER)
#  define JLN_MP_USE_INTEGER_PACK 0
#  define JLN_MP_USE_MAKE_INTEGER_SEQ 1
#elif defined(__GNUC__)
#  if __GNUC__ >= 8
#    define JLN_MP_USE_INTEGER_PACK 1
#    define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#  endif
#endif

#ifndef JLN_MP_USE_INTEGER_PACK
#  define JLN_MP_USE_INTEGER_PACK 0
#  define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#endif


#if JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
#  include <cstddef>
#else
#  include <utility>
#endif


namespace jln::mp
{
  /// \cond
  namespace detail
  {
#if JLN_MP_USE_MAKE_INTEGER_SEQ
    template<class>
    struct make_int_sequence_impl;
#elif JLN_MP_USE_INTEGER_PACK
    template<class C, int_... ns>
    using make_int_sequence_impl = typename C::template f<ns...>;
#else
    template<class C, class Ints>
    struct make_int_sequence_impl;

    template<template<class T, T...> class C, class Ints>
    struct make_int_pack_impl;

    template<template<class T, T...> class C, class Int, Int n>
    using make_int_pack_t = typename make_int_pack_impl<C, std::make_integer_sequence<Int, n>>::type;
#endif
  }
  /// \endcond


  /// \ingroup number

  /// Generates an incremental sequence of \c n \c int_.
  /// \treturn \sequence
  /// \see make_int_sequence, iota
  template<class C = numbers<>>
  struct make_int_sequence_v
  {
    template<class n>
#if JLN_MP_USE_MAKE_INTEGER_SEQ
    using f = __make_integer_seq<detail::make_int_sequence_impl<C>
      ::template f, int_, n::value>;
#elif JLN_MP_USE_INTEGER_PACK
    using f = detail::make_int_sequence_impl<C, __integer_pack(n::value)...>;
#else
    using f = typename detail::make_int_sequence_impl<
      C, std::make_integer_sequence<int_, n::value>>::type;
#endif
  };

  template<class C = mp::listify>
  using make_int_sequence = make_int_sequence_v<mp::numbers<C>>;

  /// Fast initialization of template of the shape `name<class T, T... ints>`.
  /// `n` should be a template parameter.
  /// \code
  /// template<class, int...>
  /// struct ints { ... };
  ///
  /// template<class n>
  /// using make_ints = JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, n::value, ints);
  /// \endcode
  #if JLN_MP_USE_MAKE_INTEGER_SEQ
  #  define JLN_MP_MAKE_INTEGER_SEQUENCE_T(T, n, ...) __make_integer_seq<__VA_ARGS__, T, n>
  #elif JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
  #  define JLN_MP_MAKE_INTEGER_SEQUENCE_T(T, n, ...) __VA_ARGS__<T, __integer_pack(n)...>
  #else
  #  define JLN_MP_MAKE_INTEGER_SEQUENCE_T(T, n, ...) \
      ::jln::mp::detail::make_int_pack_t<__VA_ARGS__, T, n>
  #endif

  /// Fast initialization of template of the shape `name<class T, std::size_t... ints>`.
  /// `n` should be a template parameter.
  #define JLN_MP_MAKE_INDEX_SEQUENCE(n, ...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_T(std::size_t, n, __VA_ARGS__)

  /// Fast initialization of template of the shape `name<class T, int_... ints>`.
  /// `n` should be a template parameter.
  #define JLN_MP_MAKE_INTEGER_SEQUENCE(n, ...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_T(::jln::mp::int_, n, __VA_ARGS__)


  namespace emp
  {
#if JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
    template<unsigned n, class C = mp::numbers<>>
    using make_int_sequence_v_c = typename mp::make_int_sequence_v<C>
      ::template f<number<n>>;

    template<unsigned n, class C = mp::listify>
    using make_int_sequence_c = typename mp::make_int_sequence_v<mp::numbers<C>>
      ::template f<number<n>>;

    template<class n, class C = mp::numbers<>>
    using make_int_sequence_v = typename mp::make_int_sequence_v<C>
      ::template f<n>;

    template<class n, class C = mp::listify>
    using make_int_sequence = typename mp::make_int_sequence_v<mp::numbers<C>>
      ::template f<n>;
#else
    template<unsigned n, class C = mp::numbers<>>
    using make_int_sequence_v_c = typename detail::make_int_sequence_impl<C,
      std::make_integer_sequence<int_, n>>::type;

    template<unsigned n, class C = mp::listify>
    using make_int_sequence_c = typename detail::make_int_sequence_impl<mp::numbers<C>,
      std::make_integer_sequence<int_, n>>::type;

    template<class n, class C = mp::numbers<>>
    using make_int_sequence_v = typename detail::make_int_sequence_impl<C,
      std::make_integer_sequence<int_, n::value>>::type;

    template<class n, class C = mp::listify>
    using make_int_sequence = typename detail::make_int_sequence_impl<mp::numbers<C>,
      std::make_integer_sequence<int_, n::value>>::type;
#endif
  }
} // namespace jln::mp


/// \cond
#if JLN_MP_USE_MAKE_INTEGER_SEQ
namespace jln::mp
{
  namespace detail
  {
    template<class, int_... ns>
    using make_numbers_sequence = list<number<ns>...>;

    template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
    struct make_numbers_sequence_fc
    {
      template<class, int_... ns>
      struct f
      {
        using type = F<ns...>;
      };
    };
  }

  template<>
  struct make_int_sequence_v<numbers<>>
  {
    template<class n>
    using f = __make_integer_seq<detail::make_numbers_sequence, int_, n::value>;
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C>
  struct make_int_sequence_v<lift_v<F, C>>
  {
    template<class n>
    using f = typename C::template f<typename __make_integer_seq<
      detail::make_numbers_sequence_fc<F>::template f, int_, n::value
    >::type>;
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C>
  struct make_int_sequence_v<lift_v_t<F, C>>
  {
    template<class n>
    using f = typename C::template f<typename __make_integer_seq<
      detail::make_numbers_sequence_fc<F>::template f, int_, n::value
    >::type::type>;
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct make_int_sequence_v<lift_v<F>>
  {
    template<class n>
    using f = typename __make_integer_seq<
      detail::make_numbers_sequence_fc<F>::template f, int_, n::value
    >::type;
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct make_int_sequence_v<lift_v_t<F>>
  {
    template<class n>
    using f = typename __make_integer_seq<
      detail::make_numbers_sequence_fc<F>::template f, int_, n::value
    >::type::type;
  };
}
#elif JLN_MP_USE_INTEGER_PACK
namespace jln::mp
{
  template<>
  struct make_int_sequence_v<numbers<>>
  {
    template<class n>
    using f = emp::numbers<__integer_pack(n::value)...>;
  };

  namespace detail
  {
    template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class n>
    struct make_numbers_sequence_fc_t
    {
      using type = F<__integer_pack(n::value)...>;
    };
  }

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C>
  struct make_int_sequence_v<lift_v<F, C>>
  {
    template<class n>
    using f = typename C::template f<
      typename detail::make_numbers_sequence_fc_t<F, n>::type
    >;
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C>
  struct make_int_sequence_v<lift_v_t<F, C>>
  {
    template<class n>
    using f = typename C::template f<
      typename detail::make_numbers_sequence_fc_t<F, n>::type::type
    >;
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct make_int_sequence_v<lift_v<F>>
  {
    template<class n>
    using f = typename detail::make_numbers_sequence_fc_t<F, n>::type;
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct make_int_sequence_v<lift_v_t<F>>
  {
    template<class n>
    using f = typename detail::make_numbers_sequence_fc_t<F, n>::type::type;
  };
}
#endif

namespace jln::mp::detail
{
#if JLN_MP_USE_MAKE_INTEGER_SEQ
  template<class C>
  struct make_int_sequence_impl
  {
    template<class, int_... ns>
    using f = typename conditional_c<!sizeof...(ns)>
      ::template f<C, C>
      ::template f<ns...>;
  };
#elif ! JLN_MP_USE_INTEGER_PACK
  template<class C, int_... ns>
  struct make_int_sequence_impl<C, std::integer_sequence<int_, ns...>>
  {
    using type = typename C::template f<ns...>;
  };

  template<template<class T, T...> class C, class Int, Int... ns>
  struct make_int_pack_impl<C, std::integer_sequence<Int, ns...>>
  {
    using type = C<Int, ns...>;
  };
#endif
}
/// \endcond

#undef JLN_MP_USE_INTEGER_PACK
#undef JLN_MP_USE_MAKE_INTEGER_SEQ
