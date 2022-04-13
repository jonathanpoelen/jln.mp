// amalgamated version of https://github.com/jonathanpoelen/jln.mp

#pragma once

#ifndef JLN_MP_HPP
#define JLN_MP_HPP

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <limits>
#include <type_traits>
#include <utility>

namespace jln::mp
{
  /// \ingroup functional

  /// \treturn \value
  struct identity
  {
    template<class x>
    using f = x;
  };

  namespace emp
  {
    template<class x>
    using identity = x;
  }
} // namespace jln::mp
/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x>
  struct _sfinae;

  template<class x> struct _recursive_sfinae_impl;
  template<class x> struct _sfinae_once_impl;

  template<class x>
  using _recursive_sfinae = typename _recursive_sfinae_impl<x>::type;

  template<class x>
  using _sfinae_once = typename _sfinae_once_impl<x>::type;

  template<class x>
  using sfinae = typename detail::_sfinae<detail::_recursive_sfinae, x>::type;

  template<class x>
  using sfinae_once = typename detail::_sfinae<detail::_sfinae_once, x>::type;
}
/// \endcond


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x>
  struct _sfinae
  {
    static constexpr bool missing_specialization = static_cast<x*>(nullptr);
    static_assert(missing_specialization);
  };

  template<class x>
  struct _recursive_sfinae_impl
  {
    using type = typename _sfinae<_recursive_sfinae, x>::type;
  };

  template<class x>
  struct _sfinae_once_impl
  {
    using type = typename _sfinae<emp::identity, x>::type;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup list

  template<class... xs>
  class list {};
} // namespace jln::mp
namespace jln::mp
{
  /// \ingroup number

  using int_ = std::intmax_t;
  using uint_ = std::intmax_t;

  template<int_ v>
  struct number { static const int_ value = v; };

  using true_ = number<1>;
  using false_ = number<0>;

#if defined( __cpp_nontype_template_parameter_auto)
# if  __cpp_nontype_template_parameter_auto >= 201606L
#  define JLN_MP_ENABLE_TPL_AUTO 1
#  define JLN_MP_TPL_AUTO_OR_INT auto
# endif
#endif

#ifndef JLN_MP_TPL_AUTO_OR_INT
# define JLN_MP_TPL_AUTO_OR_INT ::jln::mp::int_
# define JLN_MP_ENABLE_TPL_AUTO 0
#endif
}
// Compiler type
//@{
#if defined(_MSC_VER) && defined(__clang__)
#  define JLN_MP_CLANG_LIKE 1
#  define JLN_MP_MSVC_LIKE 1
#  define JLN_MP_CLANG_CL 1
#  define JLN_MP_CLANG 0
#  define JLN_MP_MSVC 0
#  define JLN_MP_GCC 0
#elif defined(__clang__)
#  define JLN_MP_CLANG_LIKE 1
#  define JLN_MP_MSVC_LIKE 0
#  define JLN_MP_CLANG_CL 0
#  define JLN_MP_CLANG 1
#  define JLN_MP_MSVC 0
#  define JLN_MP_GCC 0
#elif defined(_MSC_VER)
#  define JLN_MP_CLANG_LIKE 0
#  define JLN_MP_MSVC_LIKE 1
#  define JLN_MP_CLANG_CL 0
#  define JLN_MP_CLANG 0
#  define JLN_MP_MSVC 1
#  define JLN_MP_GCC 0
#elif defined(__GNUC__)
#  define JLN_MP_CLANG_LIKE 0
#  define JLN_MP_MSVC_LIKE 0
#  define JLN_MP_CLANG_CL 0
#  define JLN_MP_CLANG 0
#  define JLN_MP_MSVC 0
#  define JLN_MP_GCC 1
#else
#  define JLN_MP_CLANG_LIKE 0
#  define JLN_MP_MSVC_LIKE 0
#  define JLN_MP_CLANG_CL 0
#  define JLN_MP_CLANG 0
#  define JLN_MP_MSVC 0
#  define JLN_MP_GCC 0
#endif
//@}

#define JLN_MP_PRAGMA(x) JLN_MP_PRAGMA_I(x)

#ifdef _MSC_VER
#  define JLN_MP_PRAGMA_I(x) __pragma(x)
#else
#  define JLN_MP_PRAGMA_I(x) _Pragma(#x)
#endif

// Features
//@{
#ifndef JLN_MP_FEATURE_CONCEPTS
#  ifdef __cpp_concepts
#    if __cpp_concepts >= 201907L
#      define JLN_MP_FEATURE_CONCEPTS 1
#    endif
#  endif
#  ifndef JLN_MP_FEATURE_CONCEPTS
#      define JLN_MP_FEATURE_CONCEPTS 0
#  endif
#endif
//@}

// Diagnostic
//@{
#if JLN_MP_CLANG || JLN_MP_GCC

#  define JLN_MP_DIAGNOSTIC_PUSH() _Pragma("GCC diagnostic push")
#  define JLN_MP_DIAGNOSTIC_POP() _Pragma("GCC diagnostic pop")

#  define JLN_MP_DIAGNOSTIC_MSVC_IGNORE(X)
#  define JLN_MP_DIAGNOSTIC_GCC_IGNORE(X) JLN_MP_PRAGMA_I(GCC diagnostic ignored X)
#  define JLN_MP_DIAGNOSTIC_MSVC_WARNING(X)
#  define JLN_MP_DIAGNOSTIC_GCC_WARNING(X) JLN_MP_PRAGMA_I(GCC diagnostic warning X)
#  define JLN_MP_DIAGNOSTIC_MSVC_ERROR(X)
#  define JLN_MP_DIAGNOSTIC_GCC_ERROR(X) JLN_MP_PRAGMA_I(GCC diagnostic error X)
#  ifdef __clang__
#    define JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE(X)
#    define JLN_MP_DIAGNOSTIC_CLANG_IGNORE JLN_MP_DIAGNOSTIC_GCC_IGNORE
#    define JLN_MP_DIAGNOSTIC_GCC_ONLY_WARNING(X)
#    define JLN_MP_DIAGNOSTIC_CLANG_WARNING JLN_MP_DIAGNOSTIC_GCC_WARNING
#    define JLN_MP_DIAGNOSTIC_GCC_ONLY_ERROR(X)
#    define JLN_MP_DIAGNOSTIC_CLANG_ERROR JLN_MP_DIAGNOSTIC_GCC_ERROR
#  else
#    define JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE JLN_MP_DIAGNOSTIC_GCC_IGNORE
#    define JLN_MP_DIAGNOSTIC_CLANG_IGNORE(X)
#    define JLN_MP_DIAGNOSTIC_GCC_ONLY_WARNING JLN_MP_DIAGNOSTIC_GCC_WARNING
#    define JLN_MP_DIAGNOSTIC_CLANG_WARNING(X)
#    define JLN_MP_DIAGNOSTIC_GCC_ONLY_ERROR JLN_MP_DIAGNOSTIC_GCC_ERROR
#    define JLN_MP_DIAGNOSTIC_CLANG_ERROR(X)
#  endif

#elif JLN_MP_MSVC

#  define JLN_MP_DIAGNOSTIC_PUSH() __pragma(warning(push))
#  define JLN_MP_DIAGNOSTIC_POP() __pragma(warning(pop))

#  define JLN_MP_DIAGNOSTIC_MSVC_IGNORE(X) JLN_MP_PRAGMA_I(warning(disable:X))
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE(X)
#  define JLN_MP_DIAGNOSTIC_GCC_IGNORE(X)

#  define JLN_MP_DIAGNOSTIC_MSVC_WARNING(X) JLN_MP_PRAGMA_I(warning(4:X))
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_WARNING(X)
#  define JLN_MP_DIAGNOSTIC_GCC_WARNING(X)

#  define JLN_MP_DIAGNOSTIC_MSVC_ERROR(X) JLN_MP_PRAGMA_I(error(X))
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_ERROR(X)
#  define JLN_MP_DIAGNOSTIC_GCC_ERROR(X)

#  if JLN_MP_CLANG_LIKE
#    define JLN_MP_DIAGNOSTIC_CLANG_IGNORE(X) JLN_MP_PRAGMA_I(GCC diagnostic ignored X)
#    define JLN_MP_DIAGNOSTIC_CLANG_WARNING(X) JLN_MP_PRAGMA_I(GCC diagnostic warning X)
#    define JLN_MP_DIAGNOSTIC_CLANG_ERROR(X) JLN_MP_PRAGMA_I(GCC diagnostic error X)
#  else
#    define JLN_MP_DIAGNOSTIC_CLANG_IGNORE(X)
#    define JLN_MP_DIAGNOSTIC_CLANG_WARNING(X)
#    define JLN_MP_DIAGNOSTIC_CLANG_ERROR(X)
#  endif

#else

#  define JLN_MP_DIAGNOSTIC_PUSH()
#  define JLN_MP_DIAGNOSTIC_POP()

#  define JLN_MP_DIAGNOSTIC_MSVC_IGNORE(X)
#  define JLN_MP_DIAGNOSTIC_GCC_IGNORE(X)
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE(X)
#  define JLN_MP_DIAGNOSTIC_CLANG_IGNORE(X)

#  define JLN_MP_DIAGNOSTIC_MSVC_WARNING(X)
#  define JLN_MP_DIAGNOSTIC_GCC_WARNING(X)
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_WARNING(X)
#  define JLN_MP_DIAGNOSTIC_CLANG_WARNING(X)

#  define JLN_MP_DIAGNOSTIC_MSVC_ERROR(X)
#  define JLN_MP_DIAGNOSTIC_GCC_ERROR(X)
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_ERROR(X)
#  define JLN_MP_DIAGNOSTIC_CLANG_ERROR(X)

#endif
//@}
#ifndef JLN_MP_ENABLE_DEBUG
#  define JLN_MP_ENABLE_DEBUG 0
#endif

// useless with gcc and msvc since it displays all the transformations
#if (JLN_MP_GCC || JLN_MP_MSVC) && !defined(JLN_MP_FORCE_DEBUG)
#  undef JLN_MP_ENABLE_DEBUG
#  define JLN_MP_ENABLE_DEBUG 0
#endif
#ifndef JLN_MP_MAX_CALL_ELEMENT
# define JLN_MP_MAX_CALL_ELEMENT 10000
#endif

/// \defgroup list List
/// \defgroup algorithm Algorithm
/// \defgroup number Number
/// \defgroup value Value
/// \defgroup functional Functional
/// \defgroup utility Utility
/// \defgroup trait Trait
/// \defgroup search Search
/// \defgroup group Group
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    class uncallable_function {};

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

  /// Memoize a call to C::f<xs...>.
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
namespace jln::mp
{
  /// \ingroup utility

  template<bool>
  struct conditional_c;

  template<>
  struct conditional_c<true>
  {
    template<class x, class y>
    using f = x;
  };

  template<>
  struct conditional_c<false>
  {
    template<class x, class y>
    using f = y;
  };

  template<class v>
  using conditional = conditional_c<bool(v::value)>;

  namespace emp
  {
    template<class v, class x, class y>
    using conditional = typename mp::conditional_c<bool(v::value)>
      ::template f<x, y>;

    template<bool cond, class x, class y>
    using conditional_c = typename mp::conditional_c<cond>
      ::template f<x, y>;
  }
} // namespace jln::mp
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool> struct dcallf;
    template<bool> struct dcall_c;
    template<bool> struct dcallf_c;

    class too_many_arguments_error {};
  }
  /// \endcond

  /// \ingroup functional


#define JLN_MP_IDENT(...) __VA_ARGS__

#if ! JLN_MP_ENABLE_DEBUG
  #define JLN_MP_TRACE_F(...) __VA_ARGS__
  #define JLN_MP_TRACE_TYPENAME

  #define JLN_MP_CALL_TRACE(C, ...) typename C ::template f<__VA_ARGS__>
  #define JLN_MP_CALL_TRACE_T(C, ...) typename C ::template f<__VA_ARGS__>
  #define JLN_MP_CALL_TRACE_0_ARG(...) typename __VA_ARGS__::template f<>
#else
  // does not compile with msvc...
  #define JLN_MP_TRACE_F(...) memoize<__VA_ARGS__>
  #define JLN_MP_TRACE_TYPENAME typename

  #define JLN_MP_CALL_TRACE(C, ...)            \
    typename ::jln::mp::detail::memoizer_impl< \
      C, ::jln::mp::list<__VA_ARGS__>          \
    >::type
  #define JLN_MP_CALL_TRACE_T(C, ...)          \
    typename ::jln::mp::detail::memoizer_impl< \
      typename C, ::jln::mp::list<__VA_ARGS__> \
    >::type
  #define JLN_MP_CALL_TRACE_0_ARG(...)         \
    typename ::jln::mp::detail::memoizer_impl< \
      __VA_ARGS__, ::jln::mp::list<>           \
    >::type
#endif


#ifdef JLN_MP_DOXYGENATING

template<class C, class... xs>
using call = C::f<xs...>;

#define JLN_MP_DCALL_TRACE_XS(xs, C, ...) call<C, __VA_ARGS__>
#define JLN_MP_DCALL_TRACE_XS_0(xs, C) call<__VA_ARGS__>
#define JLN_MP_DCALL_V_TRACE_XS(xs, C, ...) call<C, __VA_ARGS__>::value
#define JLN_MP_DCALLF_XS(xs, F, ...) F<__VA_ARGS__>
#define JLN_MP_DCALLF_C_XS(xs, F, ...) F<__VA_ARGS__>

#else

#define JLN_MP_DCALLF_XS(xs, C, ...)                               \
  typename detail::dcallf<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT> \
    ::template f<C, __VA_ARGS__>

#define JLN_MP_DCALLF_C_XS(xs, C, ...)                               \
  typename detail::dcallf_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT> \
    ::template f<C, __VA_ARGS__>

# if JLN_MP_MSVC

template<class C, class... xs>
using call = typename detail::memoizer_impl<C, list<xs...>>::type;

#  define JLN_MP_DCALL_TRACE_XS(xs, C, ...) \
    typename ::jln::mp::detail::memoizer_impl<C, ::jln::mp::list<__VA_ARGS__>>::type

#  define JLN_MP_DCALL_TRACE_XS_0(xs, C) \
    typename ::jln::mp::detail::memoizer_impl<C, ::jln::mp::list<>>::type

#  define JLN_MP_DCALL_V_TRACE_XS(xs, C, ...) \
    ::jln::mp::detail::memoizer_impl<C, ::jln::mp::list<__VA_ARGS__>>::type::value

# else

template<class C, class... xs>
using call = typename conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
  ::template f<C, detail::too_many_arguments_error>
  ::template f<xs...>;

#  define JLN_MP_DCALL_TRACE_XS(xs, C, ...)                                        \
    typename ::jln::mp::conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>     \
      ::template f<JLN_MP_TRACE_F(C), ::jln::mp::detail::too_many_arguments_error> \
      ::template f<__VA_ARGS__>

#  define JLN_MP_DCALL_TRACE_XS_0(xs, C)                                           \
    typename ::jln::mp::conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>     \
      ::template f<JLN_MP_TRACE_F(C), ::jln::mp::detail::too_many_arguments_error> \
      ::template f<>

#  define JLN_MP_DCALL_V_TRACE_XS(xs, C, ...)                                      \
    ::jln::mp::conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>              \
      ::template f<JLN_MP_TRACE_F(C), ::jln::mp::detail::too_many_arguments_error> \
      ::template f<__VA_ARGS__>                                                    \
      ::value

# endif
#endif


#if JLN_MP_MSVC
# define JLN_MP_MSVC_FIX_CALL(C, ...) \
  ::jln::mp::detail::raw_call<typename JLN_MP_IDENT C, __VA_ARGS__>

# define JLN_MP_MSVC_FIX_CALL_T(C, ...) \
  ::jln::mp::detail::raw_call<JLN_MP_IDENT C, __VA_ARGS__>
#else
# define JLN_MP_MSVC_FIX_CALL(C, ...) typename JLN_MP_IDENT C::template f<__VA_ARGS__>
# define JLN_MP_MSVC_FIX_CALL_T(C, ...) typename JLN_MP_IDENT C::template f<__VA_ARGS__>
#endif


template<class C, JLN_MP_TPL_AUTO_OR_INT... xs>
using call_c = typename detail::dcall_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
  ::template f<C, xs...>;

template<class C, class... xs>
using call_t = typename call<C, xs...>::type;

}

/// \cond
namespace jln::mp::detail
{
  template<>
  struct dcall_c<true>
  {
      template<class C, JLN_MP_TPL_AUTO_OR_INT...xs>
      using f = typename C::template f<xs...>;
  };

  template<>
  struct dcallf<true>
  {
    template<template<class...> class F, class... xs>
    using f = F<xs...>;
  };

  template<>
  struct dcallf_c<true>
  {
      template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, JLN_MP_TPL_AUTO_OR_INT...xs>
      using f = F<xs...>;
  };

  // useful to work around msvc bugs
  template<class F, class... xs>
  using raw_call = typename F::template f<xs...>;
}
/// \endcond
namespace jln::mp
{
  /// \ingroup utility

  /// Always evaluate at an arbitrary value.
  /// \post result = x
  /// \treturn value
  template<class x, class C = identity>
  struct always
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, x);
  };

  template<class x>
  struct always<x, identity>
  {
    template<class... xs>
    using f = x;
  };
}
namespace jln::mp
{
  /// \ingroup utility

  /// \treturn \bool
  template <class T, class C = identity>
  struct is
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<std::is_same<T, x>::value>);
  };

  /// \cond
  template<class T>
  struct is<T, identity>
  {
    template<class x>
    using f = number<std::is_same<T, x>::value>;
  };
  /// \endcond
} // namespace jln::mp
namespace jln::mp
{
  struct na {};

  using is_na = is<na>;
  using violation = always<na>;

  /// \cond
  namespace detail
  {
    template<class, class, class = void>
    struct _try_impl;

    template<class x>
    struct _try_dispatch;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes \c TC::f<result> whetehr \c F::f<xs...> is a valid expression
  /// other than \c na, otherwhise invokes \c FC::f<xs...>.
  /// \pre \c F::f<xs...> must be a SFINAE compatible expression
  /// \treturn \value
  template<class F, class TC = identity, class FC = violation>
  struct try_;

  template<class F, class FC>
  using try_or = try_<F, identity, FC>;

  template<class F, class TC, class FC>
  struct try_
  {
    template<class... xs>
    using f = typename detail::_try_dispatch<
      typename detail::_try_impl<F, list<xs...>>::type
    >::template f<TC, FC, xs...>;
  };

  namespace emp
  {
    template<class F, class TC, class FC, class... xs>
    using try_ = typename try_<F, TC, FC>::template f<xs...>;

    template<class F, class FC, class... xs>
    using try_or = typename try_<F, mp::identity, FC>::template f<xs...>;
  }
}


namespace jln::mp
{
  /// \cond
  template<class F>
  struct try_<F, always<true_>, always<false_>>
  {
    template<class... xs>
    using f = number<!std::is_same<na,
      typename detail::_try_impl<F, list<xs...>>::type
    >::value>;
  };

  template<class F>
  struct try_<F, identity, violation>
  {
    template<class... xs>
    using f = typename detail::_try_impl<F, list<xs...>>::type;
  };
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  template<class, class, class>
  struct _try_impl
  {
    using type = na;
  };

  template<class F, class... xs>
  struct _try_impl<F, list<xs...>, std::void_t<typename F::template f<xs...>>>
  {
    using type = JLN_MP_CALL_TRACE(F, xs...);
  };

  template<class x>
  struct _try_dispatch
  {
    template<class TC, class FC, class...>
    using f = JLN_MP_CALL_TRACE(TC, x);
  };

  template<>
  struct _try_dispatch<na>
  {
    template<class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(FC, xs...);
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup functional

  /// Makes a \function from a \lazymetafunction.
  /// \treturn \value
  /// \see lift
  template<template<class...> class F, class C = identity>
  struct lift_t
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_XS(xs, F, xs...)::type);
  };

  /// \cond
  template<template<class...> class F>
  struct lift_t<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_XS(xs, F, xs...)::type;
  };
  /// \endcond

  /// Makes a \function from a \metafunction.
  /// \treturn \value
  /// \see lift_t
  template<template<class...> class F, class C = identity>
  struct lift
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_XS(xs, F, xs...));
  };

  /// \cond
  template<template<class...> class F>
  struct lift<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_XS(xs, F, xs...);
  };
  /// \endcond

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct lift_c
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs...));
  };

  /// \cond
  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct lift_c<F, identity>
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs...);
  };
  /// \endcond

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct lift_v
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs::value...));
  };

  /// \cond
  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct lift_v<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs::value...);
  };
  /// \endcond
} // namespace jln::mp
namespace jln::mp
{
  /// \ingroup functional

  /// A conditional expression.
  /// \treturn \value
  template<class Pred, class TC, class FC = always<false_>>
  struct if_
  {
    template<class... xs>
    using f = typename mp::conditional_c<bool(call<JLN_MP_TRACE_F(Pred), xs...>::value)>
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };

  namespace emp
  {
    template<class Pred, class TC, class FC, class... xs>
    using if_ = typename mp::if_<Pred, TC, FC>::template f<xs...>;
  }
}

/// \cond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template <class L> struct _unpack {};
    template <class L> struct _unpack_append {};
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
    using f = typename detail::_unpack<seq>::template f<C, xs...>;
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
    using f = typename detail::_unpack_append<seq>::template f<C, xs...>;
  };

  namespace emp
  {
    template<class L, class C, class... xs>
    using unpack = typename detail::_unpack<L>::template f<C, xs...>;

    template<class L, class C, class... xs>
    using unpack_append = typename detail::_unpack_append<L>::template f<C, xs...>;
  }
} // namespace jln::mp


namespace jln::mp
{
  /// \ingroup list

  /// \treturn \link list
  using listify = lift<list>;

  /// \cond
  template<>
  struct lift<list, identity>
  {
    template<class... xs>
    using f = list<xs...>;
  };
  /// \endcond
} // namespace jln::mp
/// \cond
namespace jln::mp::detail
{
  template<template<class...> class Seq, class... ys>
  struct _unpack<Seq<ys...>>
  {
    template<class C, class... xs>
    using f = JLN_MP_CALL_TRACE(C, xs..., ys...);
  };

  template<template<class...> class Seq, class... xs>
  struct _unpack_append<Seq<xs...>>
  {
    template<class C, class... ys>
    using f = JLN_MP_CALL_TRACE(C, xs..., ys...);
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
namespace jln::mp
{
  /// \ingroup list

  /// Returns the number of elements in a \c xs.
  /// \treturn \number
  template<class C = identity>
  struct size
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<sizeof...(xs)>);
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using size = unpack<L, mp::size<C>>;
  }

  /// \cond
  template<>
  struct size<identity>
  {
    template<class... xs>
    using f = number<sizeof...(xs)>;
  };
  /// \endcond
}
namespace jln::mp
{
  template<class TC, class FC>
  struct if_<size<>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<!sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(FC), JLN_MP_TRACE_F(TC)>
      ::template f<xs...>;
  };
}
/// \endcond
namespace jln::mp
{
  namespace detail
  {
    template<class C> struct _subcontract;
    template<class x> struct _try_subcontract;
  }

  template<class C>
  struct contract
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };

  template<class test, class TC, class FC = violation>
  using contract_if = typename conditional_c<test::value>::template f<TC, FC>;

  template<bool test, class TC, class FC = violation>
  using contract_if_c = typename conditional_c<test>::template f<TC, FC>;

  template<class Pred, class TC = identity, class FC = violation>
  using test_contract = contract<if_<Pred, TC, FC>>;

  template<class F, class TC = identity, class FC = violation>
  using try_contract = contract<try_<F, TC, FC>>;

  using bad_contract = contract<violation>;


  template<class C>
  using subcontract = typename detail::_subcontract<C>::type;

  template<class F, class TC = identity, class FC = violation>
  using try_subcontract = typename detail::_try_subcontract<F>::template f<TC, FC>;

  template<class F>
  using subcontract_barrier = contract<subcontract<F>>;
}


namespace jln::mp
{
  /// \cond
  template<class C, class TC, class FC>
  struct try_<contract<C>, TC, FC>
  {
    template<class... xs>
    using f = typename detail::_try_dispatch<JLN_MP_DCALL_TRACE_XS(xs, C, xs...)>
      ::template f<TC, FC, xs...>;
  };

  template<class C>
  struct try_<contract<C>, always<true_>, always<false_>>
  {
    template<class... xs>
    using f = number<!std::is_same<na, JLN_MP_DCALL_TRACE_XS(xs, C, xs...)>::value>;
  };

  template<class C>
  struct try_<contract<C>, identity, violation>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct _subcontract
  {
    using type = try_<F>;
  };

  template<class C>
  struct _subcontract<contract<C>>
  {
    using type = C;
  };

  template<class F, class TC, class FC>
  struct _subcontract<try_<F, TC, FC>>
  {
    using type = try_<F, TC, FC>;
  };

  template<class F>
  struct optimize_try
  {
    using type = F;
  };

  template<class F>
  struct _try_subcontract
  {
    template<class TC, class FC>
    using f = try_<F, TC, FC>;
  };

  template<class TC, class FC>
  struct _try_subcontract_contract
  {
    template<class F>
    using f = typename optimize_try<try_<F, TC, FC>>::type;
  };

  template<>
  struct _try_subcontract_contract<identity, violation>
  {
    template<class F>
    using f = F;
  };

  template<class F>
  struct _try_subcontract<contract<F>>
  {
    template<class TC, class FC>
    using f = typename _try_subcontract_contract<TC, FC>::template f<F>;
  };

  template<class F, class TC1, class FC1>
  struct _try_subcontract<try_<F, TC1, FC1>>
  {
    template<class TC, class FC>
    using f = typename optimize_try<try_<try_<F, TC1, FC1>, TC, FC>>::type;
  };

  template<class F, class TC, class FC, class FC2>
  struct optimize_try<try_<try_<F, TC, FC>, identity, FC2>>
  : optimize_try<try_<F, TC, FC>>
  {};


  template<class F>
  typename F::type lazy_build(int);

  template<class F>
  bad_contract lazy_build(...);

#define JLN_MP_PARAM_NAME_2(name, init) name
#define JLN_MP_PARAM_NAME_1(name) name

#define JLN_MP_PARAM_DECL_2(name, init) name = init
#define JLN_MP_PARAM_DECL_1(name) name

#define JLN_MP_PARAM_COUNT_I(a, b, c, ...) c
#define JLN_MP_PARAM_COUNT_P(...) (__VA_ARGS__, _2, _1, _0)
#define JLN_MP_PARAM_COUNT(arg) JLN_MP_IDENT(JLN_MP_PARAM_COUNT_I JLN_MP_PARAM_COUNT_P arg)

#define JLN_MP_PP_CAT_II(a, b) a##b
#define JLN_MP_PP_CAT_I(a, b) JLN_MP_PP_CAT_II(a,b)
#define JLN_MP_PP_CAT(a, b) JLN_MP_PP_CAT_I(a, b)

#define JLN_MP_PARAM_DECL(arg) JLN_MP_PP_CAT(JLN_MP_PARAM_DECL, JLN_MP_PARAM_COUNT(arg)) arg
#define JLN_MP_PARAM_NAME(arg) JLN_MP_PP_CAT(JLN_MP_PARAM_NAME, JLN_MP_PARAM_COUNT(arg)) arg

#define JLN_MP_MAKE_REGULAR_SMP1_II(                     \
  ns_smp, ns_detail, smp_name, name, na, da, ...)        \
  namespace ns_detail {                                  \
    template<class na, class = void>                     \
    struct smp_name {};                                  \
    template<class na>                                   \
    struct smp_name<na, std::void_t<__VA_ARGS__>>        \
    { using type = __VA_ARGS__; };                       \
  }                                                      \
  namespace ns_smp {                                     \
    template<class da>                                   \
    using name = decltype(::jln::mp::detail::lazy_build< \
      ::ns_detail::smp_name<na>>(1));                    \
  }

#define JLN_MP_MAKE_REGULAR_SMP1_I(ns_smp, ns_detail, smp_name, name, na, da, ...) \
  JLN_MP_MAKE_REGULAR_SMP1_II(ns_smp, ns_detail, smp_name, name, na, da, __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP1(ns_smp, ns_detail, smp_name, name, a, ...) \
  JLN_MP_MAKE_REGULAR_SMP1_I(ns_smp, ns_detail, smp_name, name,             \
    JLN_MP_PARAM_NAME(a), JLN_MP_PARAM_DECL(a), __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP1_P(name, a, ...) JLN_MP_MAKE_REGULAR_SMP1( \
  jln::mp::smp, jln::mp::detail, smp_##name, name, a, __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP2_II(                      \
  ns_smp, ns_detail, smp_name, name, na, nb, da, db, ...) \
  namespace ns_detail {                                   \
    template<class na, class nb, class = void>            \
    struct smp_name {};                                   \
    template<class na, class nb>                          \
    struct smp_name<na, nb, std::void_t<__VA_ARGS__>>     \
    { using type = __VA_ARGS__; };                        \
  }                                                       \
  namespace ns_smp {                                      \
    template<class da, class db>                          \
    using name = decltype(::jln::mp::detail::lazy_build<  \
      ::ns_detail::smp_name<na, nb>>(1));                 \
  }

#define JLN_MP_MAKE_REGULAR_SMP2_I(ns_smp, ns_detail, smp_name, name, na, nb, da, db, ...) \
  JLN_MP_MAKE_REGULAR_SMP2_II(ns_smp, ns_detail, smp_name, name, na, nb, da, db, __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP2(ns_smp, ns_detail, smp_name, name, a, b, ...) \
  JLN_MP_MAKE_REGULAR_SMP2_I(ns_smp, ns_detail, smp_name, name,                \
    JLN_MP_PARAM_NAME(a), JLN_MP_PARAM_NAME(b),                                \
    JLN_MP_PARAM_DECL(a), JLN_MP_PARAM_DECL(b), __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP2_P(name, a, b, ...) JLN_MP_MAKE_REGULAR_SMP2( \
  jln::mp::smp, jln::mp::detail, smp_##name, name, a, b, __VA_ARGS__)


#define JLN_MP_MAKE_REGULAR_SMP3_II(                              \
  ns_smp, ns_detail, smp_name, name, na, nb, nc, da, db, dc, ...) \
  namespace ns_detail {                                           \
    template<class na, class nb, class nc, class = void>          \
    struct smp_name {};                                           \
    template<class na, class nb, class nc>                        \
    struct smp_name<na, nb, nc, std::void_t<__VA_ARGS__>>         \
    { using type = __VA_ARGS__; };                                \
  }                                                               \
  namespace ns_smp {                                              \
    template<class da, class db, class dc>                        \
    using name = decltype(::jln::mp::detail::lazy_build<          \
      ::ns_detail::smp_name<na, nb, nc>>(1));                     \
  }

#define JLN_MP_MAKE_REGULAR_SMP3_I(                               \
  ns_smp, ns_detail, smp_name, name, na, nb, nc, da, db, dc, ...) \
  JLN_MP_MAKE_REGULAR_SMP3_II(                                    \
    ns_smp, ns_detail, smp_name, name, na, nb, nc, da, db, dc, __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP3(ns_smp, ns_detail, smp_name, name, a, b, c, ...) \
  JLN_MP_MAKE_REGULAR_SMP3_I(ns_smp, ns_detail, smp_name, name,                   \
    JLN_MP_PARAM_NAME(a), JLN_MP_PARAM_NAME(b), JLN_MP_PARAM_NAME(c),             \
    JLN_MP_PARAM_DECL(a), JLN_MP_PARAM_DECL(b), JLN_MP_PARAM_DECL(c), __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP3_P(name, a, b, c, ...) JLN_MP_MAKE_REGULAR_SMP3( \
  jln::mp::smp, jln::mp::detail, smp_##name, name, a, b, c, __VA_ARGS__)


#define JLN_MP_MAKE_REGULAR_SMP4_II(                                      \
  ns_smp, ns_detail, smp_name, name, na, nb, nc, nd, da, db, dc, dd, ...) \
  namespace ns_detail {                                                   \
    template<class na, class nb, class nc, class nd, class = void>        \
    struct smp_name {};                                                   \
    template<class na, class nb, class nc, class nd>                      \
    struct smp_name<na, nb, nc, nd, std::void_t<__VA_ARGS__>>             \
    { using type = __VA_ARGS__; };                                        \
  }                                                                       \
  namespace ns_smp {                                                      \
    template<class da, class db, class dc, class dd>                      \
    using name = decltype(::jln::mp::detail::lazy_build<                  \
      ::ns_detail::smp_name<na, nb, nc, nd>>(1));                         \
  }

#define JLN_MP_MAKE_REGULAR_SMP4_I(                                       \
  ns_smp, ns_detail, smp_name, name, na, nb, nc, nd, da, db, dc, dd, ...) \
  JLN_MP_MAKE_REGULAR_SMP4_II(                                            \
    ns_smp, ns_detail, smp_name, name, na, nb, nc, nd, da, db, dc, dd, __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP4(ns_smp, ns_detail, smp_name, name, a, b, c, d, ...) \
  JLN_MP_MAKE_REGULAR_SMP4_I(ns_smp, ns_detail, smp_name, name,                      \
    JLN_MP_PARAM_NAME(a), JLN_MP_PARAM_NAME(b),                                      \
    JLN_MP_PARAM_NAME(c), JLN_MP_PARAM_NAME(d),                                      \
    JLN_MP_PARAM_DECL(a), JLN_MP_PARAM_DECL(b),                                      \
    JLN_MP_PARAM_DECL(c), JLN_MP_PARAM_DECL(d), __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP4_P(name, a, b, c, d, ...) JLN_MP_MAKE_REGULAR_SMP4( \
  jln::mp::smp, jln::mp::detail, smp_##name, name, a, b, c, d, __VA_ARGS__)


#define JLN_MP_MAKE_REGULAR_SMP5_II(                                              \
  ns_smp, ns_detail, smp_name, name, na, nb, nc, nd, ne, da, db, dc, dd, de, ...) \
  namespace ns_detail {                                                           \
    template<class na, class nb, class nc, class nd, class ne, class = void>      \
    struct smp_name {};                                                           \
    template<class na, class nb, class nc, class nd, class ne>                    \
    struct smp_name<na, nb, nc, nd, ne, std::void_t<__VA_ARGS__>>                 \
    { using type = __VA_ARGS__; };                                                \
  }                                                                               \
  namespace ns_smp {                                                              \
    template<class da, class db, class dc, class dd, class de>                    \
    using name = decltype(::jln::mp::detail::lazy_build<                          \
      ::ns_detail::smp_name<na, nb, nc, nd, ne>>(1));                             \
  }

#define JLN_MP_MAKE_REGULAR_SMP5_I(                                               \
  ns_smp, ns_detail, smp_name, name, na, nb, nc, nd, ne, da, db, dc, dd, de, ...) \
  JLN_MP_MAKE_REGULAR_SMP5_II(                                                    \
    ns_smp, ns_detail, smp_name, name, na, nb, nc, nd, ne, da, db, dc, dd, de, __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP5(ns_smp, ns_detail, smp_name, name, a, b, c, d, e, ...) \
  JLN_MP_MAKE_REGULAR_SMP5_I(ns_smp, ns_detail, smp_name, name,                         \
    JLN_MP_PARAM_NAME(a), JLN_MP_PARAM_NAME(b),                                         \
    JLN_MP_PARAM_NAME(c), JLN_MP_PARAM_NAME(d),                                         \
    JLN_MP_PARAM_NAME(e),                                                               \
    JLN_MP_PARAM_DECL(a), JLN_MP_PARAM_DECL(b),                                         \
    JLN_MP_PARAM_DECL(c), JLN_MP_PARAM_DECL(d),                                         \
    JLN_MP_PARAM_DECL(e), __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP5_P(name, a, b, c, d, e, ...) JLN_MP_MAKE_REGULAR_SMP5( \
  jln::mp::smp, jln::mp::detail, smp_##name, name, a, b, c, d, e, __VA_ARGS__)


  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, contract<C>>
  {
    using type = contract<C>;
  };

  template<template<class> class sfinae, class F, class TC, class FC>
  struct _sfinae<sfinae, try_<F, TC, FC>>
  {
    using type = contract<try_<F, TC, FC>>;
  };
}
/// \endcond
namespace jln::mp
{
  namespace detail
  {
#define JLN_MP_MK_ASSUME(name)                         \
    template<class F> struct name { using type = F; }; \
    template<class F> struct name<memoize<F>>          \
    {                                                  \
      using type = memoize<typename name<F>::type>;    \
    }

    JLN_MP_MK_ASSUME(_assume_number);
    JLN_MP_MK_ASSUME(_assume_positive_number);
    JLN_MP_MK_ASSUME(_assume_numbers);
    JLN_MP_MK_ASSUME(_assume_unary);
    JLN_MP_MK_ASSUME(_assume_unary_or_more);
    JLN_MP_MK_ASSUME(_assume_binary);
    JLN_MP_MK_ASSUME(_assume_binary_list);
    JLN_MP_MK_ASSUME(_assume_binary_or_more);
    JLN_MP_MK_ASSUME(_assume_lists);
#undef JLN_MP_MK_ASSUME
  }

  template<class C>
  using assume_number = typename detail::_assume_number<subcontract<C>>::type;

  template<class C>
  using assume_positive_number = typename detail::_assume_positive_number<subcontract<C>>::type;

  template<class C>
  using assume_numbers = typename detail::_assume_numbers<subcontract<C>>::type;

  template<class C>
  using assume_unary = typename detail::_assume_unary<subcontract<C>>::type;

  template<class C>
  using assume_binary = typename detail::_assume_binary<subcontract<C>>::type;

  template<class C>
  using assume_binary_list = typename detail::_assume_binary_list<subcontract<C>>::type;

  template<class C>
  using assume_lists = typename detail::_assume_lists<subcontract<C>>::type;

  template<class C>
  using assume_binary_or_more = typename detail::_assume_binary_or_more<subcontract<C>>::type;

  template<class C>
  using assume_unary_or_more = typename detail::_assume_unary_or_more<subcontract<C>>::type;


  template<class F>
  using assume_lists_barrier = contract<assume_lists<F>>;

  template<class F>
  using assume_unary_barrier = contract<assume_unary<F>>;

  template<class F>
  using assume_binary_barrier = contract<assume_binary<F>>;

  template<class F>
  using assume_number_barrier = contract<assume_number<F>>;

  template<class F>
  using assume_positive_number_barrier = contract<assume_positive_number<F>>;

  template<class F>
  using assume_binary_list_barrier = contract<assume_binary_list<F>>;
}


/// \cond
#define JLN_MP_UNPACK(...) __VA_ARGS__
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class x>
    struct _is_list;
  }
  /// \endcond

  /// \ingroup list

  /// Checks whether \c x is a \list.
  /// \treturn \number
  template<class C = identity>
  struct is_list
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_is_list<x>::type);
  };

  namespace emp
  {
    template<class x, class C = mp::identity>
    using is_list = JLN_MP_CALL_TRACE(C, typename detail::_is_list<x>::type);
  }
} // namespace jln::mp


/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct _is_list
  {
    using type = false_;
  };

  template<class... xs>
  struct _is_list<list<xs...>>
  {
    using type = true_;
  };
} // namespace jln::mp::detail
/// \endcond
namespace jln::mp
{
  /// \ingroup list

  /// Removes all elements from the \sequence.
  /// \treturn \value
  template<class C = listify>
  struct clear
  {
    template<class... xs>
    using f = typename C::template f<>;
  };

  /// \cond
  template<>
  struct clear<listify>
  {
    template<class... xs>
    using f = list<>;
  };
  /// \endcond
}
namespace jln::mp::detail
{
  constexpr unsigned min(unsigned a, unsigned b)
  {
    return a < b ? a : b;
  }

  constexpr unsigned max(unsigned a, unsigned b)
  {
    return a < b ? b : a;
  }
}

#define JLN_MP_NIL
#define JLN_MP_COMMA ,
#define JLN_MP_PAREN_OPEN (
#define JLN_MP_PAREN_CLOSE )

#define JLN_MP_GEN_XS_8_16_32_64_128(func)                   \
  func(8,   JLN_MP_XS_8,   JLN_MP_RXS_8,   JLN_MP_REPEAT_8)  \
  func(16,  JLN_MP_XS_16,  JLN_MP_RXS_16,  JLN_MP_REPEAT_16) \
  func(32,  JLN_MP_XS_32,  JLN_MP_RXS_32,  JLN_MP_REPEAT_32) \
  func(64,  JLN_MP_XS_64,  JLN_MP_RXS_64,  JLN_MP_REPEAT_64) \
  func(128, JLN_MP_XS_128, JLN_MP_RXS_128, JLN_MP_REPEAT_128)

#define JLN_MP_GEN_XS_16_64_256(func)                        \
  func(16,  JLN_MP_XS_16,  JLN_MP_RXS_16,  JLN_MP_REPEAT_16) \
  func(64,  JLN_MP_XS_64,  JLN_MP_RXS_64,  JLN_MP_REPEAT_64) \
  func(256, JLN_MP_XS_256, JLN_MP_RXS_256, JLN_MP_REPEAT_256)

#define JLN_MP_GEN_XS_8_16_64_256(func)                      \
  func(8,   JLN_MP_XS_8,   JLN_MP_RXS_8,   JLN_MP_REPEAT_8)  \
  func(16,  JLN_MP_XS_16,  JLN_MP_RXS_16,  JLN_MP_REPEAT_16) \
  func(64,  JLN_MP_XS_64,  JLN_MP_RXS_64,  JLN_MP_REPEAT_64) \
  func(256, JLN_MP_XS_256, JLN_MP_RXS_256, JLN_MP_REPEAT_256)

#define JLN_MP_GEN_XS_4_8_16_64_256(func)                    \
  func(4,   JLN_MP_XS_4,   JLN_MP_RXS_4,   JLN_MP_REPEAT_4)  \
  func(8,   JLN_MP_XS_8,   JLN_MP_RXS_8,   JLN_MP_REPEAT_8)  \
  func(16,  JLN_MP_XS_16,  JLN_MP_RXS_16,  JLN_MP_REPEAT_16) \
  func(64,  JLN_MP_XS_64,  JLN_MP_RXS_64,  JLN_MP_REPEAT_64) \
  func(256, JLN_MP_XS_256, JLN_MP_RXS_256, JLN_MP_REPEAT_256)

#define JLN_MP_GEN_XS_2_4_8_16_32_64_128_256(func)            \
  func(2,   JLN_MP_XS_2,   JLN_MP_RXS_2,   JLN_MP_REPEAT_2)   \
  func(4,   JLN_MP_XS_4,   JLN_MP_RXS_4,   JLN_MP_REPEAT_4)   \
  func(8,   JLN_MP_XS_8,   JLN_MP_RXS_8,   JLN_MP_REPEAT_8)   \
  func(16,  JLN_MP_XS_16,  JLN_MP_RXS_16,  JLN_MP_REPEAT_16)  \
  func(32,  JLN_MP_XS_32,  JLN_MP_RXS_32,  JLN_MP_REPEAT_32)  \
  func(64,  JLN_MP_XS_64,  JLN_MP_RXS_64,  JLN_MP_REPEAT_64)  \
  func(128, JLN_MP_XS_128, JLN_MP_RXS_128, JLN_MP_REPEAT_128) \
  func(256, JLN_MP_XS_256, JLN_MP_RXS_256, JLN_MP_REPEAT_256)

#define JLN_MP_GEN_XS_0_TO_8(func)                    \
  func(0, JLN_MP_XS_0, JLN_MP_RXS_0, JLN_MP_REPEAT_0) \
  func(1, JLN_MP_XS_1, JLN_MP_RXS_1, JLN_MP_REPEAT_1) \
  func(2, JLN_MP_XS_2, JLN_MP_RXS_2, JLN_MP_REPEAT_2) \
  func(3, JLN_MP_XS_3, JLN_MP_RXS_3, JLN_MP_REPEAT_3) \
  func(4, JLN_MP_XS_4, JLN_MP_RXS_4, JLN_MP_REPEAT_4) \
  func(5, JLN_MP_XS_5, JLN_MP_RXS_5, JLN_MP_REPEAT_5) \
  func(6, JLN_MP_XS_6, JLN_MP_RXS_6, JLN_MP_REPEAT_6) \
  func(7, JLN_MP_XS_7, JLN_MP_RXS_7, JLN_MP_REPEAT_7)

#define JLN_MP_GEN_XS_1_TO_8_INCLUDED(func) \
  JLN_MP_GEN_XS_1_TO_8(func)                \
  func(8, JLN_MP_XS_8, JLN_MP_RXS_8, JLN_MP_REPEAT_8)

#define JLN_MP_GEN_XS_1_TO_8(func)                    \
  func(1, JLN_MP_XS_1, JLN_MP_RXS_1, JLN_MP_REPEAT_1) \
  func(2, JLN_MP_XS_2, JLN_MP_RXS_2, JLN_MP_REPEAT_2) \
  func(3, JLN_MP_XS_3, JLN_MP_RXS_3, JLN_MP_REPEAT_3) \
  func(4, JLN_MP_XS_4, JLN_MP_RXS_4, JLN_MP_REPEAT_4) \
  func(5, JLN_MP_XS_5, JLN_MP_RXS_5, JLN_MP_REPEAT_5) \
  func(6, JLN_MP_XS_6, JLN_MP_RXS_6, JLN_MP_REPEAT_6) \
  func(7, JLN_MP_XS_7, JLN_MP_RXS_7, JLN_MP_REPEAT_7)

#define JLN_MP_GEN_XS_1_TO_4(func)                    \
  func(1, JLN_MP_XS_1, JLN_MP_RXS_1, JLN_MP_REPEAT_1) \
  func(2, JLN_MP_XS_2, JLN_MP_RXS_2, JLN_MP_REPEAT_2) \
  func(3, JLN_MP_XS_3, JLN_MP_RXS_3, JLN_MP_REPEAT_3)


#define JLN_MP_REPEAT_0(x, sep)
#define JLN_MP_REPEAT_1(x, B) x
#define JLN_MP_REPEAT_2(x, B) x B x
#define JLN_MP_REPEAT_3(x, B) x B x B x
#define JLN_MP_REPEAT_4(x, B) x B x B x B x
#define JLN_MP_REPEAT_5(x, B) x B x B x B x B x
#define JLN_MP_REPEAT_6(x, B) x B x B x B x B x B x
#define JLN_MP_REPEAT_7(x, B) x B x B x B x B x B x B x
#define JLN_MP_REPEAT_8(x, B) x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_16(x, B) \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_32(x, B)                                    \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_64(x, B)                                    \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_128(x, B)                                   \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_256(x, B)                                   \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x


#define JLN_MP_XS_0(before, after, sep)

#define JLN_MP_XS_1(before, after, sep) \
  before _1 after

#define JLN_MP_XS_2(before, after, sep) \
  before _1 after sep before _2 after

#define JLN_MP_XS_3(before, after, sep) \
  before _1 after sep before _2 after sep before _3 after

#define JLN_MP_XS_4(before, after, sep) \
  before _1 after sep before _2 after sep before _3 after sep before _4 after

#define JLN_MP_XS_5(before, after, sep)                                           \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep \
  before _5 after

#define JLN_MP_XS_6(before, after, sep)                                           \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep \
  before _5 after sep before _6 after

#define JLN_MP_XS_7(before, after, sep)                                           \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep \
  before _5 after sep before _6 after sep before _7 after

#define JLN_MP_XS_8(before, after, sep)                                           \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep \
  before _5 after sep before _6 after sep before _7 after sep before _8 after

#define JLN_MP_XS_2_TO_8(before, after, sep)                                      \
                      before _2 after sep before _3 after sep before _4 after sep \
  before _5 after sep before _6 after sep before _7 after sep before _8 after

#define JLN_MP_XS_16(before, after, sep)                                             \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep    \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep    \
  before _9 after sep before _10 after sep before _11 after sep before _12 after sep \
  before _13 after sep before _14 after sep before _15 after sep before _16 after

#define JLN_MP_XS_32(before, after, sep)                                              \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep     \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep     \
  before _9 after sep before _10 after sep before _11 after sep before _12 after sep  \
  before _13 after sep before _14 after sep before _15 after sep before _16 after sep \
  before _17 after sep before _18 after sep before _19 after sep before _20 after sep \
  before _21 after sep before _22 after sep before _23 after sep before _24 after sep \
  before _25 after sep before _26 after sep before _27 after sep before _28 after sep \
  before _29 after sep before _30 after sep before _31 after sep before _32 after

#define JLN_MP_XS_64(before, after, sep)                                              \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep     \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep     \
  before _9 after sep before _10 after sep before _11 after sep before _12 after sep  \
  before _13 after sep before _14 after sep before _15 after sep before _16 after sep \
  before _17 after sep before _18 after sep before _19 after sep before _20 after sep \
  before _21 after sep before _22 after sep before _23 after sep before _24 after sep \
  before _25 after sep before _26 after sep before _27 after sep before _28 after sep \
  before _29 after sep before _30 after sep before _31 after sep before _32 after sep \
  before _33 after sep before _34 after sep before _35 after sep before _36 after sep \
  before _37 after sep before _38 after sep before _39 after sep before _40 after sep \
  before _41 after sep before _42 after sep before _43 after sep before _44 after sep \
  before _45 after sep before _46 after sep before _47 after sep before _48 after sep \
  before _49 after sep before _50 after sep before _51 after sep before _52 after sep \
  before _53 after sep before _54 after sep before _55 after sep before _56 after sep \
  before _57 after sep before _58 after sep before _59 after sep before _60 after sep \
  before _61 after sep before _62 after sep before _63 after sep before _64 after

#define JLN_MP_XS_128(before, after, sep)                                                 \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep         \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep         \
  before _9 after sep before _10 after sep before _11 after sep before _12 after sep      \
  before _13 after sep before _14 after sep before _15 after sep before _16 after sep     \
  before _17 after sep before _18 after sep before _19 after sep before _20 after sep     \
  before _21 after sep before _22 after sep before _23 after sep before _24 after sep     \
  before _25 after sep before _26 after sep before _27 after sep before _28 after sep     \
  before _29 after sep before _30 after sep before _31 after sep before _32 after sep     \
  before _33 after sep before _34 after sep before _35 after sep before _36 after sep     \
  before _37 after sep before _38 after sep before _39 after sep before _40 after sep     \
  before _41 after sep before _42 after sep before _43 after sep before _44 after sep     \
  before _45 after sep before _46 after sep before _47 after sep before _48 after sep     \
  before _49 after sep before _50 after sep before _51 after sep before _52 after sep     \
  before _53 after sep before _54 after sep before _55 after sep before _56 after sep     \
  before _57 after sep before _58 after sep before _59 after sep before _60 after sep     \
  before _61 after sep before _62 after sep before _63 after sep before _64 after sep     \
  before _65 after sep before _66 after sep before _67 after sep before _68 after sep     \
  before _69 after sep before _70 after sep before _71 after sep before _72 after sep     \
  before _73 after sep before _74 after sep before _75 after sep before _76 after sep     \
  before _77 after sep before _78 after sep before _79 after sep before _80 after sep     \
  before _81 after sep before _82 after sep before _83 after sep before _84 after sep     \
  before _85 after sep before _86 after sep before _87 after sep before _88 after sep     \
  before _89 after sep before _90 after sep before _91 after sep before _92 after sep     \
  before _93 after sep before _94 after sep before _95 after sep before _96 after sep     \
  before _97 after sep before _98 after sep before _99 after sep before _100 after sep    \
  before _101 after sep before _102 after sep before _103 after sep before _104 after sep \
  before _105 after sep before _106 after sep before _107 after sep before _108 after sep \
  before _109 after sep before _110 after sep before _111 after sep before _112 after sep \
  before _113 after sep before _114 after sep before _115 after sep before _116 after sep \
  before _117 after sep before _118 after sep before _119 after sep before _120 after sep \
  before _121 after sep before _122 after sep before _123 after sep before _124 after sep \
  before _125 after sep before _126 after sep before _127 after sep before _128 after

#define JLN_MP_XS_256(before, after, sep)                                                 \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep         \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep         \
  before _9 after sep before _10 after sep before _11 after sep before _12 after sep      \
  before _13 after sep before _14 after sep before _15 after sep before _16 after sep     \
  before _17 after sep before _18 after sep before _19 after sep before _20 after sep     \
  before _21 after sep before _22 after sep before _23 after sep before _24 after sep     \
  before _25 after sep before _26 after sep before _27 after sep before _28 after sep     \
  before _29 after sep before _30 after sep before _31 after sep before _32 after sep     \
  before _33 after sep before _34 after sep before _35 after sep before _36 after sep     \
  before _37 after sep before _38 after sep before _39 after sep before _40 after sep     \
  before _41 after sep before _42 after sep before _43 after sep before _44 after sep     \
  before _45 after sep before _46 after sep before _47 after sep before _48 after sep     \
  before _49 after sep before _50 after sep before _51 after sep before _52 after sep     \
  before _53 after sep before _54 after sep before _55 after sep before _56 after sep     \
  before _57 after sep before _58 after sep before _59 after sep before _60 after sep     \
  before _61 after sep before _62 after sep before _63 after sep before _64 after sep     \
  before _65 after sep before _66 after sep before _67 after sep before _68 after sep     \
  before _69 after sep before _70 after sep before _71 after sep before _72 after sep     \
  before _73 after sep before _74 after sep before _75 after sep before _76 after sep     \
  before _77 after sep before _78 after sep before _79 after sep before _80 after sep     \
  before _81 after sep before _82 after sep before _83 after sep before _84 after sep     \
  before _85 after sep before _86 after sep before _87 after sep before _88 after sep     \
  before _89 after sep before _90 after sep before _91 after sep before _92 after sep     \
  before _93 after sep before _94 after sep before _95 after sep before _96 after sep     \
  before _97 after sep before _98 after sep before _99 after sep before _100 after sep    \
  before _101 after sep before _102 after sep before _103 after sep before _104 after sep \
  before _105 after sep before _106 after sep before _107 after sep before _108 after sep \
  before _109 after sep before _110 after sep before _111 after sep before _112 after sep \
  before _113 after sep before _114 after sep before _115 after sep before _116 after sep \
  before _117 after sep before _118 after sep before _119 after sep before _120 after sep \
  before _121 after sep before _122 after sep before _123 after sep before _124 after sep \
  before _125 after sep before _126 after sep before _127 after sep before _128 after sep \
  before _129 after sep before _130 after sep before _131 after sep before _132 after sep \
  before _133 after sep before _134 after sep before _135 after sep before _136 after sep \
  before _137 after sep before _138 after sep before _139 after sep before _140 after sep \
  before _141 after sep before _142 after sep before _143 after sep before _144 after sep \
  before _145 after sep before _146 after sep before _147 after sep before _148 after sep \
  before _149 after sep before _150 after sep before _151 after sep before _152 after sep \
  before _153 after sep before _154 after sep before _155 after sep before _156 after sep \
  before _157 after sep before _158 after sep before _159 after sep before _160 after sep \
  before _161 after sep before _162 after sep before _163 after sep before _164 after sep \
  before _165 after sep before _166 after sep before _167 after sep before _168 after sep \
  before _169 after sep before _170 after sep before _171 after sep before _172 after sep \
  before _173 after sep before _174 after sep before _175 after sep before _176 after sep \
  before _177 after sep before _178 after sep before _179 after sep before _180 after sep \
  before _181 after sep before _182 after sep before _183 after sep before _184 after sep \
  before _185 after sep before _186 after sep before _187 after sep before _188 after sep \
  before _189 after sep before _190 after sep before _191 after sep before _192 after sep \
  before _193 after sep before _194 after sep before _195 after sep before _196 after sep \
  before _197 after sep before _198 after sep before _199 after sep before _200 after sep \
  before _201 after sep before _202 after sep before _203 after sep before _204 after sep \
  before _205 after sep before _206 after sep before _207 after sep before _208 after sep \
  before _209 after sep before _210 after sep before _211 after sep before _212 after sep \
  before _213 after sep before _214 after sep before _215 after sep before _216 after sep \
  before _217 after sep before _218 after sep before _219 after sep before _220 after sep \
  before _221 after sep before _222 after sep before _223 after sep before _224 after sep \
  before _225 after sep before _226 after sep before _227 after sep before _228 after sep \
  before _229 after sep before _230 after sep before _231 after sep before _232 after sep \
  before _233 after sep before _234 after sep before _235 after sep before _236 after sep \
  before _237 after sep before _238 after sep before _239 after sep before _240 after sep \
  before _241 after sep before _242 after sep before _243 after sep before _244 after sep \
  before _245 after sep before _246 after sep before _247 after sep before _248 after sep \
  before _249 after sep before _250 after sep before _251 after sep before _252 after sep \
  before _253 after sep before _254 after sep before _255 after sep before _256 after

#define JLN_MP_XS_512(before, after, sep)                                                 \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep         \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep         \
  before _9 after sep before _10 after sep before _11 after sep before _12 after sep      \
  before _13 after sep before _14 after sep before _15 after sep before _16 after sep     \
  before _17 after sep before _18 after sep before _19 after sep before _20 after sep     \
  before _21 after sep before _22 after sep before _23 after sep before _24 after sep     \
  before _25 after sep before _26 after sep before _27 after sep before _28 after sep     \
  before _29 after sep before _30 after sep before _31 after sep before _32 after sep     \
  before _33 after sep before _34 after sep before _35 after sep before _36 after sep     \
  before _37 after sep before _38 after sep before _39 after sep before _40 after sep     \
  before _41 after sep before _42 after sep before _43 after sep before _44 after sep     \
  before _45 after sep before _46 after sep before _47 after sep before _48 after sep     \
  before _49 after sep before _50 after sep before _51 after sep before _52 after sep     \
  before _53 after sep before _54 after sep before _55 after sep before _56 after sep     \
  before _57 after sep before _58 after sep before _59 after sep before _60 after sep     \
  before _61 after sep before _62 after sep before _63 after sep before _64 after sep     \
  before _65 after sep before _66 after sep before _67 after sep before _68 after sep     \
  before _69 after sep before _70 after sep before _71 after sep before _72 after sep     \
  before _73 after sep before _74 after sep before _75 after sep before _76 after sep     \
  before _77 after sep before _78 after sep before _79 after sep before _80 after sep     \
  before _81 after sep before _82 after sep before _83 after sep before _84 after sep     \
  before _85 after sep before _86 after sep before _87 after sep before _88 after sep     \
  before _89 after sep before _90 after sep before _91 after sep before _92 after sep     \
  before _93 after sep before _94 after sep before _95 after sep before _96 after sep     \
  before _97 after sep before _98 after sep before _99 after sep before _100 after sep    \
  before _101 after sep before _102 after sep before _103 after sep before _104 after sep \
  before _105 after sep before _106 after sep before _107 after sep before _108 after sep \
  before _109 after sep before _110 after sep before _111 after sep before _112 after sep \
  before _113 after sep before _114 after sep before _115 after sep before _116 after sep \
  before _117 after sep before _118 after sep before _119 after sep before _120 after sep \
  before _121 after sep before _122 after sep before _123 after sep before _124 after sep \
  before _125 after sep before _126 after sep before _127 after sep before _128 after sep \
  before _129 after sep before _130 after sep before _131 after sep before _132 after sep \
  before _133 after sep before _134 after sep before _135 after sep before _136 after sep \
  before _137 after sep before _138 after sep before _139 after sep before _140 after sep \
  before _141 after sep before _142 after sep before _143 after sep before _144 after sep \
  before _145 after sep before _146 after sep before _147 after sep before _148 after sep \
  before _149 after sep before _150 after sep before _151 after sep before _152 after sep \
  before _153 after sep before _154 after sep before _155 after sep before _156 after sep \
  before _157 after sep before _158 after sep before _159 after sep before _160 after sep \
  before _161 after sep before _162 after sep before _163 after sep before _164 after sep \
  before _165 after sep before _166 after sep before _167 after sep before _168 after sep \
  before _169 after sep before _170 after sep before _171 after sep before _172 after sep \
  before _173 after sep before _174 after sep before _175 after sep before _176 after sep \
  before _177 after sep before _178 after sep before _179 after sep before _180 after sep \
  before _181 after sep before _182 after sep before _183 after sep before _184 after sep \
  before _185 after sep before _186 after sep before _187 after sep before _188 after sep \
  before _189 after sep before _190 after sep before _191 after sep before _192 after sep \
  before _193 after sep before _194 after sep before _195 after sep before _196 after sep \
  before _197 after sep before _198 after sep before _199 after sep before _200 after sep \
  before _201 after sep before _202 after sep before _203 after sep before _204 after sep \
  before _205 after sep before _206 after sep before _207 after sep before _208 after sep \
  before _209 after sep before _210 after sep before _211 after sep before _212 after sep \
  before _213 after sep before _214 after sep before _215 after sep before _216 after sep \
  before _217 after sep before _218 after sep before _219 after sep before _220 after sep \
  before _221 after sep before _222 after sep before _223 after sep before _224 after sep \
  before _225 after sep before _226 after sep before _227 after sep before _228 after sep \
  before _229 after sep before _230 after sep before _231 after sep before _232 after sep \
  before _233 after sep before _234 after sep before _235 after sep before _236 after sep \
  before _237 after sep before _238 after sep before _239 after sep before _240 after sep \
  before _241 after sep before _242 after sep before _243 after sep before _244 after sep \
  before _245 after sep before _246 after sep before _247 after sep before _248 after sep \
  before _249 after sep before _250 after sep before _251 after sep before _252 after sep \
  before _253 after sep before _254 after sep before _255 after sep before _256 after sep \
  before _257 after sep before _258 after sep before _259 after sep before _260 after sep \
  before _261 after sep before _262 after sep before _263 after sep before _264 after sep \
  before _265 after sep before _266 after sep before _267 after sep before _268 after sep \
  before _269 after sep before _270 after sep before _271 after sep before _272 after sep \
  before _273 after sep before _274 after sep before _275 after sep before _276 after sep \
  before _277 after sep before _278 after sep before _279 after sep before _280 after sep \
  before _281 after sep before _282 after sep before _283 after sep before _284 after sep \
  before _285 after sep before _286 after sep before _287 after sep before _288 after sep \
  before _289 after sep before _290 after sep before _291 after sep before _292 after sep \
  before _293 after sep before _294 after sep before _295 after sep before _296 after sep \
  before _297 after sep before _298 after sep before _299 after sep before _300 after sep \
  before _301 after sep before _302 after sep before _303 after sep before _304 after sep \
  before _305 after sep before _306 after sep before _307 after sep before _308 after sep \
  before _309 after sep before _310 after sep before _311 after sep before _312 after sep \
  before _313 after sep before _314 after sep before _315 after sep before _316 after sep \
  before _317 after sep before _318 after sep before _319 after sep before _320 after sep \
  before _321 after sep before _322 after sep before _323 after sep before _324 after sep \
  before _325 after sep before _326 after sep before _327 after sep before _328 after sep \
  before _329 after sep before _330 after sep before _331 after sep before _332 after sep \
  before _333 after sep before _334 after sep before _335 after sep before _336 after sep \
  before _337 after sep before _338 after sep before _339 after sep before _340 after sep \
  before _341 after sep before _342 after sep before _343 after sep before _344 after sep \
  before _345 after sep before _346 after sep before _347 after sep before _348 after sep \
  before _349 after sep before _350 after sep before _351 after sep before _352 after sep \
  before _353 after sep before _354 after sep before _355 after sep before _356 after sep \
  before _357 after sep before _358 after sep before _359 after sep before _360 after sep \
  before _361 after sep before _362 after sep before _363 after sep before _364 after sep \
  before _365 after sep before _366 after sep before _367 after sep before _368 after sep \
  before _369 after sep before _370 after sep before _371 after sep before _372 after sep \
  before _373 after sep before _374 after sep before _375 after sep before _376 after sep \
  before _377 after sep before _378 after sep before _379 after sep before _380 after sep \
  before _381 after sep before _382 after sep before _383 after sep before _384 after sep \
  before _385 after sep before _386 after sep before _387 after sep before _388 after sep \
  before _389 after sep before _390 after sep before _391 after sep before _392 after sep \
  before _393 after sep before _394 after sep before _395 after sep before _396 after sep \
  before _397 after sep before _398 after sep before _399 after sep before _400 after sep \
  before _401 after sep before _402 after sep before _403 after sep before _404 after sep \
  before _405 after sep before _406 after sep before _407 after sep before _408 after sep \
  before _409 after sep before _410 after sep before _411 after sep before _412 after sep \
  before _413 after sep before _414 after sep before _415 after sep before _416 after sep \
  before _417 after sep before _418 after sep before _419 after sep before _420 after sep \
  before _421 after sep before _422 after sep before _423 after sep before _424 after sep \
  before _425 after sep before _426 after sep before _427 after sep before _428 after sep \
  before _429 after sep before _430 after sep before _431 after sep before _432 after sep \
  before _433 after sep before _434 after sep before _435 after sep before _436 after sep \
  before _437 after sep before _438 after sep before _439 after sep before _440 after sep \
  before _441 after sep before _442 after sep before _443 after sep before _444 after sep \
  before _445 after sep before _446 after sep before _447 after sep before _448 after sep \
  before _449 after sep before _450 after sep before _451 after sep before _452 after sep \
  before _453 after sep before _454 after sep before _455 after sep before _456 after sep \
  before _457 after sep before _458 after sep before _459 after sep before _460 after sep \
  before _461 after sep before _462 after sep before _463 after sep before _464 after sep \
  before _465 after sep before _466 after sep before _467 after sep before _468 after sep \
  before _469 after sep before _470 after sep before _471 after sep before _472 after sep \
  before _473 after sep before _474 after sep before _475 after sep before _476 after sep \
  before _477 after sep before _478 after sep before _479 after sep before _480 after sep \
  before _481 after sep before _482 after sep before _483 after sep before _484 after sep \
  before _485 after sep before _486 after sep before _487 after sep before _488 after sep \
  before _489 after sep before _490 after sep before _491 after sep before _492 after sep \
  before _493 after sep before _494 after sep before _495 after sep before _496 after sep \
  before _497 after sep before _498 after sep before _499 after sep before _500 after sep \
  before _501 after sep before _502 after sep before _503 after sep before _504 after sep \
  before _505 after sep before _506 after sep before _507 after sep before _508 after sep \
  before _509 after sep before _510 after sep before _511 after sep before _512 after

#define JLN_MP_RXS_0(before, after, sep)

#define JLN_MP_RXS_1(before, after, sep) \
  before _1 after

#define JLN_MP_RXS_2(before, after, sep) \
  before _2 after sep before _1 after

#define JLN_MP_RXS_3(before, after, sep) \
  before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_4(before, after, sep) \
  before _4 after sep before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_5(before, after, sep) \
  before _5 after sep before _4 after sep before _3 after sep before _2 after sep \
  before _1 after

#define JLN_MP_RXS_6(before, after, sep)                                          \
  before _6 after sep before _5 after sep before _4 after sep before _3 after sep \
  before _2 after sep before _1 after

#define JLN_MP_RXS_7(before, after, sep)                                          \
  before _7 after sep before _6 after sep before _5 after sep before _4 after sep \
  before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_8(before, after, sep)                                          \
  before _8 after sep before _7 after sep before _6 after sep before _5 after sep \
  before _4 after sep before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_16(before, after, sep)                                             \
  before _16 after sep before _15 after sep before _14 after sep before _13 after sep \
  before _12 after sep before _11 after sep before _10 after sep before _9 after sep  \
  before _8 after sep before _7 after sep before _6 after sep before _5 after sep     \
  before _4 after sep before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_32(before, after, sep)                                             \
  before _32 after sep before _31 after sep before _30 after sep before _29 after sep \
  before _28 after sep before _27 after sep before _26 after sep before _25 after sep \
  before _24 after sep before _23 after sep before _22 after sep before _21 after sep \
  before _20 after sep before _19 after sep before _18 after sep before _17 after sep \
  before _16 after sep before _15 after sep before _14 after sep before _13 after sep \
  before _12 after sep before _11 after sep before _10 after sep before _9 after sep  \
  before _8 after sep before _7 after sep before _6 after sep before _5 after sep     \
  before _4 after sep before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_64(before, after, sep)                                             \
  before _64 after sep before _63 after sep before _62 after sep before _61 after sep \
  before _60 after sep before _59 after sep before _58 after sep before _57 after sep \
  before _56 after sep before _55 after sep before _54 after sep before _53 after sep \
  before _52 after sep before _51 after sep before _50 after sep before _49 after sep \
  before _48 after sep before _47 after sep before _46 after sep before _45 after sep \
  before _44 after sep before _43 after sep before _42 after sep before _41 after sep \
  before _40 after sep before _39 after sep before _38 after sep before _37 after sep \
  before _36 after sep before _35 after sep before _34 after sep before _33 after sep \
  before _32 after sep before _31 after sep before _30 after sep before _29 after sep \
  before _28 after sep before _27 after sep before _26 after sep before _25 after sep \
  before _24 after sep before _23 after sep before _22 after sep before _21 after sep \
  before _20 after sep before _19 after sep before _18 after sep before _17 after sep \
  before _16 after sep before _15 after sep before _14 after sep before _13 after sep \
  before _12 after sep before _11 after sep before _10 after sep before _9 after sep  \
  before _8 after sep before _7 after sep before _6 after sep before _5 after sep     \
  before _4 after sep before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_128(before, after, sep)                                                \
  before _128 after sep before _127 after sep before _126 after sep before _125 after sep \
  before _124 after sep before _123 after sep before _122 after sep before _121 after sep \
  before _120 after sep before _119 after sep before _118 after sep before _117 after sep \
  before _116 after sep before _115 after sep before _114 after sep before _113 after sep \
  before _112 after sep before _111 after sep before _110 after sep before _109 after sep \
  before _108 after sep before _107 after sep before _106 after sep before _105 after sep \
  before _104 after sep before _103 after sep before _102 after sep before _101 after sep \
  before _100 after sep before _99 after sep before _98 after sep before _97 after sep    \
  before _96 after sep before _95 after sep before _94 after sep before _93 after sep     \
  before _92 after sep before _91 after sep before _90 after sep before _89 after sep     \
  before _88 after sep before _87 after sep before _86 after sep before _85 after sep     \
  before _84 after sep before _83 after sep before _82 after sep before _81 after sep     \
  before _80 after sep before _79 after sep before _78 after sep before _77 after sep     \
  before _76 after sep before _75 after sep before _74 after sep before _73 after sep     \
  before _72 after sep before _71 after sep before _70 after sep before _69 after sep     \
  before _68 after sep before _67 after sep before _66 after sep before _65 after sep     \
  before _64 after sep before _63 after sep before _62 after sep before _61 after sep     \
  before _60 after sep before _59 after sep before _58 after sep before _57 after sep     \
  before _56 after sep before _55 after sep before _54 after sep before _53 after sep     \
  before _52 after sep before _51 after sep before _50 after sep before _49 after sep     \
  before _48 after sep before _47 after sep before _46 after sep before _45 after sep     \
  before _44 after sep before _43 after sep before _42 after sep before _41 after sep     \
  before _40 after sep before _39 after sep before _38 after sep before _37 after sep     \
  before _36 after sep before _35 after sep before _34 after sep before _33 after sep     \
  before _32 after sep before _31 after sep before _30 after sep before _29 after sep     \
  before _28 after sep before _27 after sep before _26 after sep before _25 after sep     \
  before _24 after sep before _23 after sep before _22 after sep before _21 after sep     \
  before _20 after sep before _19 after sep before _18 after sep before _17 after sep     \
  before _16 after sep before _15 after sep before _14 after sep before _13 after sep     \
  before _12 after sep before _11 after sep before _10 after sep before _9 after sep      \
  before _8 after sep before _7 after sep before _6 after sep before _5 after sep         \
  before _4 after sep before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_256(before, after, sep)                                                \
  before _256 after sep before _255 after sep before _254 after sep before _253 after sep \
  before _252 after sep before _251 after sep before _250 after sep before _249 after sep \
  before _248 after sep before _247 after sep before _246 after sep before _245 after sep \
  before _244 after sep before _243 after sep before _242 after sep before _241 after sep \
  before _240 after sep before _239 after sep before _238 after sep before _237 after sep \
  before _236 after sep before _235 after sep before _234 after sep before _233 after sep \
  before _232 after sep before _231 after sep before _230 after sep before _229 after sep \
  before _228 after sep before _227 after sep before _226 after sep before _225 after sep \
  before _224 after sep before _223 after sep before _222 after sep before _221 after sep \
  before _220 after sep before _219 after sep before _218 after sep before _217 after sep \
  before _216 after sep before _215 after sep before _214 after sep before _213 after sep \
  before _212 after sep before _211 after sep before _210 after sep before _209 after sep \
  before _208 after sep before _207 after sep before _206 after sep before _205 after sep \
  before _204 after sep before _203 after sep before _202 after sep before _201 after sep \
  before _200 after sep before _199 after sep before _198 after sep before _197 after sep \
  before _196 after sep before _195 after sep before _194 after sep before _193 after sep \
  before _192 after sep before _191 after sep before _190 after sep before _189 after sep \
  before _188 after sep before _187 after sep before _186 after sep before _185 after sep \
  before _184 after sep before _183 after sep before _182 after sep before _181 after sep \
  before _180 after sep before _179 after sep before _178 after sep before _177 after sep \
  before _176 after sep before _175 after sep before _174 after sep before _173 after sep \
  before _172 after sep before _171 after sep before _170 after sep before _169 after sep \
  before _168 after sep before _167 after sep before _166 after sep before _165 after sep \
  before _164 after sep before _163 after sep before _162 after sep before _161 after sep \
  before _160 after sep before _159 after sep before _158 after sep before _157 after sep \
  before _156 after sep before _155 after sep before _154 after sep before _153 after sep \
  before _152 after sep before _151 after sep before _150 after sep before _149 after sep \
  before _148 after sep before _147 after sep before _146 after sep before _145 after sep \
  before _144 after sep before _143 after sep before _142 after sep before _141 after sep \
  before _140 after sep before _139 after sep before _138 after sep before _137 after sep \
  before _136 after sep before _135 after sep before _134 after sep before _133 after sep \
  before _132 after sep before _131 after sep before _130 after sep before _129 after sep \
  before _128 after sep before _127 after sep before _126 after sep before _125 after sep \
  before _124 after sep before _123 after sep before _122 after sep before _121 after sep \
  before _120 after sep before _119 after sep before _118 after sep before _117 after sep \
  before _116 after sep before _115 after sep before _114 after sep before _113 after sep \
  before _112 after sep before _111 after sep before _110 after sep before _109 after sep \
  before _108 after sep before _107 after sep before _106 after sep before _105 after sep \
  before _104 after sep before _103 after sep before _102 after sep before _101 after sep \
  before _100 after sep before _99 after sep before _98 after sep before _97 after sep    \
  before _96 after sep before _95 after sep before _94 after sep before _93 after sep     \
  before _92 after sep before _91 after sep before _90 after sep before _89 after sep     \
  before _88 after sep before _87 after sep before _86 after sep before _85 after sep     \
  before _84 after sep before _83 after sep before _82 after sep before _81 after sep     \
  before _80 after sep before _79 after sep before _78 after sep before _77 after sep     \
  before _76 after sep before _75 after sep before _74 after sep before _73 after sep     \
  before _72 after sep before _71 after sep before _70 after sep before _69 after sep     \
  before _68 after sep before _67 after sep before _66 after sep before _65 after sep     \
  before _64 after sep before _63 after sep before _62 after sep before _61 after sep     \
  before _60 after sep before _59 after sep before _58 after sep before _57 after sep     \
  before _56 after sep before _55 after sep before _54 after sep before _53 after sep     \
  before _52 after sep before _51 after sep before _50 after sep before _49 after sep     \
  before _48 after sep before _47 after sep before _46 after sep before _45 after sep     \
  before _44 after sep before _43 after sep before _42 after sep before _41 after sep     \
  before _40 after sep before _39 after sep before _38 after sep before _37 after sep     \
  before _36 after sep before _35 after sep before _34 after sep before _33 after sep     \
  before _32 after sep before _31 after sep before _30 after sep before _29 after sep     \
  before _28 after sep before _27 after sep before _26 after sep before _25 after sep     \
  before _24 after sep before _23 after sep before _22 after sep before _21 after sep     \
  before _20 after sep before _19 after sep before _18 after sep before _17 after sep     \
  before _16 after sep before _15 after sep before _14 after sep before _13 after sep     \
  before _12 after sep before _11 after sep before _10 after sep before _9 after sep      \
  before _8 after sep before _7 after sep before _6 after sep before _5 after sep         \
  before _4 after sep before _3 after sep before _2 after sep before _1 after
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned>
    struct drop_front_impl;
  }
  /// \endcond

  /// \ingroup list

  /// Removes \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see drop_front_max, drop_back, take_front, take_back, drop_while
  template<unsigned N, class C = listify>
  struct drop_front_c
  {
    template<class... xs>
    using f = typename detail::drop_front_impl<
      (sizeof...(xs) & 0) + N
    >::template f<N, C, xs...>;
  };

  /// Removes at most \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while
  template<unsigned N, class C = listify>
  struct drop_front_max_c
  {
    template<class... xs>
    using f = typename detail::drop_front_impl<
      detail::min(N, sizeof...(xs))
    >::template f<detail::min(N, sizeof...(xs)), C, xs...>;
  };

  template<class N, class C = listify>
  using drop_front = drop_front_c<N::value, C>;

  template<class N, class C = listify>
  using drop_front_max = drop_front_max_c<N::value, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using drop_front = unpack<L, mp::drop_front<N, C>>;

    template<class L, unsigned n, class C = mp::listify>
    using drop_front_c = unpack<L, mp::drop_front_c<n, C>>;

    template<class L, class N, class C = mp::listify>
    using drop_front_max = unpack<L, mp::drop_front_max<N, C>>;

    template<class L, unsigned n, class C = mp::listify>
    using drop_front_max_c = unpack<L, mp::drop_front_max_c<n, C>>;
  }

  /// \cond
  template<class C>
  struct drop_front_c<0, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };


  template<class C>
  struct drop_front_max_c<0, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<unsigned n>
  struct drop_front_impl : drop_front_impl<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_DROP_IMPL(n, _, mp_rxs, mp_rep) \
  template<>                                   \
  struct drop_front_impl<n>                    \
  {                                            \
    template<unsigned size, class C,           \
      mp_rep(class JLN_MP_COMMA, JLN_MP_NIL)   \
      class... xs>                             \
    using f = JLN_MP_CALL_TRACE(C, xs...);     \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_MP_DROP_IMPL)

#undef JLN_MP_DROP_IMPL

#define JLN_MP_DROP_IMPL(n, _, mp_rxs, mp_rep) \
  template<>                                   \
  struct drop_front_impl<n>                    \
  {                                            \
    template<unsigned size, class C,           \
      mp_rep(class JLN_MP_COMMA, JLN_MP_NIL)   \
      class... xs>                             \
    using f = typename drop_front_impl<size-n> \
      ::template f<size-n, C, xs...>;          \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_DROP_IMPL)

#undef JLN_MP_DROP_IMPL
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool not_found = true>
    struct _drop_while;

    template<class>
    struct to_drop_upto;

    template<class>
    struct drop_while_impl;

    template<class>
    struct drop_while_extended_by_n_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// \pre \c Pred::f<x> must return a boolean, 1 or 0
  /// When an element does not satisfy the predicate,
  /// call \c TC with it and all those that follow it.
  /// Otherwise \c FC is called on the whole sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while_xs
  /// \see take_while, take_while_xs
  /// \see search, partial_search
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_while
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_while_extended_by_n_c
  {
    template<class... xs>
    using f = typename detail::drop_while_extended_by_n_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_while_extended_by_n = drop_while_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_while = drop_while_extended_by_n_c<1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_while = unpack<L, mp::drop_while<Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
    using drop_while_extended_by_n_c = unpack<L,
      mp::drop_while_extended_by_n_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
    using drop_while_extended_by_n = unpack<L,
      mp::drop_while_extended_by_n<ExtendedByN, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_inclusive_while = unpack<L, mp::drop_inclusive_while<Pred, TC, FC>>;
  }

  /// \cond
  template<class Pred, class TC, class FC>
  struct drop_while<Pred, drop_front_c<1, TC>, FC>
  : drop_while_extended_by_n_c<1, Pred, TC, FC>
  {};
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  template<std::size_t n>
  struct _drop_while_result
  {
    template<class C, std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_result;
  };

  struct _drop_while_continue
  {
    template<class C, std::size_t consumed, class Pred, class... xs>
    using f = typename C::template f<consumed, Pred, xs...>;
  };


  template<class>
  struct is_drop_while_continue
  {
    using type = false_;
  };

  template<>
  struct is_drop_while_continue<_drop_while_continue>
  {
    using type = true_;
  };


  template<>
  struct drop_while_impl<_drop_while_continue>
  {
    template<class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(FC, xs...);
  };

  template<std::size_t n>
  struct drop_while_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, class... xs>
    using f = typename drop_front_c<sizeof...(xs)-n-1, TC>::template f<xs...>;
  };


  template<>
  struct drop_while_extended_by_n_impl<_drop_while_continue>
  {
    template<std::size_t ExtendedByN, class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(FC, xs...);
  };

  template<std::size_t n>
  struct drop_while_extended_by_n_impl<_drop_while_result<n>>
  {
    template<std::size_t ExtendedByN, class TC, class FC, class... xs>
    using f = typename drop_front_c<
      sizeof...(xs) - (n >= ExtendedByN ? n - ExtendedByN + 1 : 0),
      TC
    >::template f<xs...>;
  };


  // _drop_while<n, b> = _drop_until<n, !b>

  template<int n>
  struct _drop_while<n, true> : _drop_while<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256,
    true
  >
  {};

  struct drop_while_impl_false
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_result<consumed+sizeof...(xs)>;
  };

#define JLN_DROP_WHILE_IMPL(n, m)                                    \
  template<>                                                         \
  struct _drop_while<n, true>                                        \
  {                                                                  \
    template<std::size_t consumed, class Pred, class x, class... xs> \
    using f = typename _drop_while<m, Pred::template f<x>::value>    \
            ::template f<consumed, Pred, xs...>;                     \
  };                                                                 \
                                                                     \
  template<>                                                         \
  struct _drop_while<n, false> : drop_while_impl_false               \
  {}

  JLN_DROP_WHILE_IMPL(7, 6);
  JLN_DROP_WHILE_IMPL(6, 5);
  JLN_DROP_WHILE_IMPL(5, 4);
  JLN_DROP_WHILE_IMPL(4, 3);
  JLN_DROP_WHILE_IMPL(3, 2);
  JLN_DROP_WHILE_IMPL(2, 1);
  JLN_DROP_WHILE_IMPL(1, 0);

#undef JLN_DROP_WHILE_IMPL

  template<>
  struct _drop_while<0, true>
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_continue;
  };

  template<>
  struct _drop_while<0, false>
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_result<consumed+sizeof...(xs)>;
  };

  template<>
  struct _drop_while<8, true>
  {
    template<
      std::size_t consumed,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_while<7, Pred::template f<_1>::value>
      ::template f<
          consumed+sizeof...(xs), Pred,
          _2, _3, _4, _5, _6, _7, _8>;
  };

  template<>
  struct _drop_while<16, true>
  {
    template<
      std::size_t consumed,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_while<7, Pred::template f<_1>::value>
      ::template f<
          consumed+sizeof...(xs), Pred,
          _2, _3, _4, _5, _6, _7, _8>
      ::template f<
          _drop_while<sizeof...(xs), true>,
          consumed, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)               \
  template<>                                        \
  struct _drop_while<n, true>                       \
  {                                                 \
    template<                                       \
      std::size_t consumed,                         \
      class Pred,                                   \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),          \
      class... xs>                                  \
    using f = typename _drop_while<m, true>         \
      ::template f<                                 \
          consumed+sizeof...(xs), Pred,             \
          xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)> \
      ::template f<                                 \
          _drop_while<sizeof...(xs), true>,         \
          consumed, Pred, xs...>;                   \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond
namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a predicate holds for all elements of a \sequence.
  /// \treturn \bool
  /// \see any_of, none_of
  template<class Pred, class C = identity>
  struct all_of
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(
      C,
      typename detail::is_drop_while_continue<
        typename detail::_drop_while<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type
    );
  };

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using all_of = unpack<L, mp::all_of<Pred, C>>;
  }
} // namespace jln::mp

namespace jln::mp
{
  /// \ingroup list

  /// Appends \c x to the end of the sequence.
  /// \treturn \sequence
  template<class x, class C = listify>
  struct push_back
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs..., x);
  };

  namespace emp
  {
    template<class L, class T, class C = mp::listify>
    using push_back = unpack<L, mp::push_back<T, C>>;
  }
}
namespace jln::mp
{
  /// \ingroup list

  /// Appends \c x to the beginning of the sequence.
  /// \treturn \sequence
  template<class x, class C = listify>
  struct push_front
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, x, xs...);
  };

  namespace emp
  {
    template<class L, class T, class C = mp::listify>
    using push_front = unpack<L, mp::push_front<T, C>>;
  }
}

JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wlogical-op")

namespace jln::mp
{
  /// \ingroup number

  template<class C = identity>
  struct or_
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value || ... || false)>);
  };

  template<class C = identity>
  struct left_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(false || ... || xs::value)>);
  };


  template<class C = identity>
  struct and_
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value && ... && true)>);
  };

  template<class C = identity>
  struct left_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(true && ... && xs::value)>);
  };


  template<class C = identity>
  struct add
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value + ...)>);
  };

  template<class C = identity>
  using add0 = if_<size<>, add<C>, always<number<0>, C>>;

  template<class C = identity>
  struct left_add
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... + xs::value)>);
  };

  template<class C = identity>
  using left_add0 = if_<size<>, left_add<C>, always<number<0>, C>>;


  template<class C = identity>
  struct sub
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... - xs::value)>);
  };

  template<class C = identity>
  using sub0 = if_<size<>, sub<C>, always<number<0>, C>>;

  template<class C = identity>
  struct lshift
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... << xs::value)>);
  };

  template<class C = identity>
  using lshift0 = if_<size<>, lshift<C>, always<number<0>, C>>;

  template<class C = identity>
  struct rshift
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... >> xs::value)>);
  };

  template<class C = identity>
  using rshift0 = if_<size<>, rshift<C>, always<number<0>, C>>;


  template<class C = identity>
  struct mul
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value * ...)>);
  };

  template<class C = identity>
  using mul0 = if_<size<>, mul<C>, always<number<0>, C>>;

  template<class C = identity>
  using mul1 = if_<size<>, mul<C>, always<number<1>, C>>;

  template<class C = identity>
  struct left_mul
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... * xs::value)>);
  };

  template<class C = identity>
  using left_mul0 = if_<size<>, left_mul<C>, always<number<0>, C>>;

  template<class C = identity>
  using left_mul1 = if_<size<>, left_mul<C>, always<number<1>, C>>;


  template<class C = identity>
  struct div
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... / xs::value)>);
  };

  template<class C = identity>
  using div0 = if_<size<>, div<C>, always<number<0>, C>>;

  template<class C = identity>
  using div1 = if_<size<>, div<C>, always<number<1>, C>>;

  template<class C = identity>
  struct mod
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... % xs::value)>);
  };

  template<class C = identity>
  using mod0 = if_<size<>, mod<C>, always<number<0>, C>>;

  template<class C = identity>
  using mod1 = if_<size<>, mod<C>, always<number<1>, C>>;


  template<class C = identity>
  struct xor_
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value ^ ...)>);
  };

  template<class C = identity>
  using xor0 = if_<size<>, xor_<C>, always<number<0>, C>>;

  template<class C = identity>
  struct left_xor
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... ^ xs::value)>);
  };

  template<class C = identity>
  using left_xor0 = if_<size<>, left_xor<C>, always<number<0>, C>>;


  template<class C = identity>
  struct bit_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value & ...)>);
  };

  template<class C = identity>
  using bit_and0 = if_<size<>, bit_and<C>, always<number<0>, C>>;

  template<class C = identity>
  struct left_bit_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... & xs::value)>);
  };

  template<class C = identity>
  using left_bit_and0 = if_<size<>, left_bit_and<C>, always<number<0>, C>>;


  template<class C = identity>
  struct bit_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value | ...)>);
  };

  template<class C = identity>
  using bit_or0 = if_<size<>, bit_or<C>, always<number<0>, C>>;

  template<class C = identity>
  struct left_bit_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... | xs::value)>);
  };

  template<class C = identity>
  using left_bit_or0 = if_<size<>, left_bit_or<C>, always<number<0>, C>>;


  template<class C = identity>
  struct neg
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(-x::value)>);
  };

  template<class C = identity>
  struct unary_plus
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(+x::value)>);
  };

  template<class C = identity>
  struct not_
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(!x::value)>);
  };

  template<class C>
  struct not_<not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(!int_{!x::value})>);
  };

  template<class C = identity>
  struct bit_not
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(~x::value)>);
  };

  template<class C = identity>
  struct inc
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value+1)>);
  };

  template<class C = identity>
  struct dec
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value-1)>);
  };

  template<class C = identity>
  struct equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value == y::value)>);
  };

  template<class C = identity>
  struct not_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value != y::value)>);
  };

  template<class C = identity>
  struct less
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value < y::value)>);
  };

  template<class C = identity>
  struct less_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value <= y::value)>);
  };

  template<class C = identity>
  struct greater
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value > y::value)>);
  };

  template<class C = identity>
  struct greater_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value >= y::value)>);
  };


  template<class N, class C = identity>
  using equal_to = push_front<N, equal<C>>;

  template<class N, class C = identity>
  using not_equal_to = push_front<N, not_equal<C>>;

  template<class N, class C = identity>
  using less_than = push_back<N, less<C>>;

  template<class N, class C = identity>
  using less_equal_than = push_back<N, less_equal<C>>;

  template<class N, class C = identity>
  using greater_than = push_back<N, greater<C>>;

  template<class N, class C = identity>
  using greater_equal_than = push_back<N, greater_equal<C>>;


  template<int_ n, class C = identity>
  using equal_to_c = equal_to<number<n>, C>;

  template<int_ n, class C = identity>
  using not_equal_to_c = not_equal_to<number<n>, C>;

  template<int_ n, class C = identity>
  using less_than_c = less_than<number<n>, C>;

  template<int_ n, class C = identity>
  using less_equal_than_c = less_equal_than<number<n>, C>;

  template<int_ n, class C = identity>
  using greater_than_c = greater_than<number<n>, C>;

  template<int_ n, class C = identity>
  using greater_equal_than_c = greater_equal_than<number<n>, C>;
}

namespace jln::mp::emp
{
  template<class L, class C = mp::identity>
  using or_seq = unpack<L, mp::or_<C>>;

  template<class L, class C = mp::identity>
  using and_seq = unpack<L, mp::and_<C>>;

  template<class L, class C = mp::identity>
  using or_left_seq = unpack<L, mp::left_or<C>>;

  template<class L, class C = mp::identity>
  using and_left_seq = unpack<L, mp::left_and<C>>;

  template<class L, class C = mp::identity>
  using add_seq = unpack<L, mp::add<C>>;

  template<class L, class C = mp::identity>
  using add0_seq = unpack<L, mp::add0<C>>;

  template<class L, class C = mp::identity>
  using left_add_seq = unpack<L, mp::left_add<C>>;

  template<class L, class C = mp::identity>
  using left_add0_seq = unpack<L, mp::left_add0<C>>;

  template<class L, class C = mp::identity>
  using sub_seq = unpack<L, mp::sub<C>>;

  template<class L, class C = mp::identity>
  using sub0_seq = unpack<L, mp::sub0<C>>;

  template<class L, class C = mp::identity>
  using lshift_seq = unpack<L, mp::lshift<C>>;

  template<class L, class C = mp::identity>
  using lshift0_seq = unpack<L, mp::lshift0<C>>;

  template<class L, class C = mp::identity>
  using rshift_seq = unpack<L, mp::rshift<C>>;

  template<class L, class C = mp::identity>
  using rshift0_seq = unpack<L, mp::rshift0<C>>;

  template<class L, class C = mp::identity>
  using mul_seq = unpack<L, mp::mul<C>>;

  template<class L, class C = mp::identity>
  using mul0_seq = unpack<L, mp::mul0<C>>;

  template<class L, class C = mp::identity>
  using mul1_seq = unpack<L, mp::mul1<C>>;

  template<class L, class C = mp::identity>
  using left_mul_seq = unpack<L, mp::left_mul<C>>;

  template<class L, class C = mp::identity>
  using left_mul0_seq = unpack<L, mp::left_mul0<C>>;

  template<class L, class C = mp::identity>
  using left_mul1_seq = unpack<L, mp::left_mul1<C>>;

  template<class L, class C = mp::identity>
  using div_seq = unpack<L, mp::div<C>>;

  template<class L, class C = mp::identity>
  using div0_seq = unpack<L, mp::div0<C>>;

  template<class L, class C = mp::identity>
  using div1_seq = unpack<L, mp::div1<C>>;

  template<class L, class C = mp::identity>
  using mod_seq = unpack<L, mp::mod<C>>;

  template<class L, class C = mp::identity>
  using mod0_seq = unpack<L, mp::mod0<C>>;

  template<class L, class C = mp::identity>
  using mod1_seq = unpack<L, mp::mod1<C>>;

  template<class L, class C = mp::identity>
  using xor_seq = unpack<L, mp::xor_<C>>;

  template<class L, class C = mp::identity>
  using xor0_seq = unpack<L, mp::xor0<C>>;

  template<class L, class C = mp::identity>
  using left_xor_seq = unpack<L, mp::left_xor<C>>;

  template<class L, class C = mp::identity>
  using left_xor0_seq = unpack<L, mp::left_xor0<C>>;

  template<class L, class C = mp::identity>
  using bit_and_seq = unpack<L, mp::bit_and<C>>;

  template<class L, class C = mp::identity>
  using bit_and0_seq = unpack<L, mp::bit_and0<C>>;

  template<class L, class C = mp::identity>
  using left_bit_and_seq = unpack<L, mp::left_bit_and<C>>;

  template<class L, class C = mp::identity>
  using left_bit_and0_seq = unpack<L, mp::left_bit_and0<C>>;

  template<class L, class C = mp::identity>
  using bit_or_seq = unpack<L, mp::bit_or<C>>;

  template<class L, class C = mp::identity>
  using bit_or0_seq = unpack<L, mp::bit_or0<C>>;

  template<class L, class C = mp::identity>
  using left_bit_or_seq = unpack<L, mp::left_bit_or<C>>;

  template<class L, class C = mp::identity>
  using left_bit_or0_seq = unpack<L, mp::left_bit_or0<C>>;


  template<int_... xs>
  using or_c = number<(xs || ... || false)>;

  template<int_... xs>
  using left_or_c = number<(false || ... || xs)>;

  template<int_... xs>
  using and_c = number<(xs && ... && true)>;

  template<int_... xs>
  using left_and_c = number<(true && ... && xs)>;

  template<int_... xs>
  using add_c = number<(xs + ...)>;

  template<int_... xs>
  using add0_c = add_c<xs..., 0>;

  template<int_... xs>
  using left_add_c = number<(... + xs)>;

  template<int_... xs>
  using left_add0_c = left_add_c<xs..., 0>;

  template<int_... xs>
  using sub_c = number<(... - xs)>;

  template<int_... xs>
  using sub0_c = sub_c<xs..., 0>;

  template<int_... xs>
  using lshift_c = number<(... << xs)>;

  template<int_... xs>
  using lshift0_c = lshift_c<xs..., 0>;

  template<int_... xs>
  using rshift_c = number<(... >> xs)>;

  template<int_... xs>
  using rshift0_c = rshift_c<xs..., 0>;

  template<int_... xs>
  using mul_c = number<(xs * ...)>;

  template<int_... xs>
  using mul0_c = mul_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<int_... xs>
  using mul1_c = mul_c<xs..., 1>;

  template<int_... xs>
  using left_mul_c = number<(... * xs)>;

  template<int_... xs>
  using left_mul0_c = left_mul_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<int_... xs>
  using left_mul1_c = left_mul_c<xs..., 1>;

  template<int_... xs>
  using div_c = number<(... / xs)>;

  template<int_... xs>
  using div0_c = div_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<int_... xs>
  using div1_c = div_c<xs..., 1>;

  template<int_... xs>
  using mod_c = number<(... % xs)>;

  template<int_... xs>
  using mod0_c = mod_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::min() : 0)>;

  template<int_... xs>
  using mod1_c = mod_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::min() : 1)>;

  template<int_... xs>
  using xor_c = number<(xs ^ ...)>;

  template<int_... xs>
  using xor0_c = xor_c<xs..., 0, 0>;

  template<int_... xs>
  using left_xor_c = number<(... ^ xs)>;

  template<int_... xs>
  using left_xor0_c = left_xor_c<xs..., 0, 0>;

  template<int_... xs>
  using bit_and_c = number<(xs & ...)>;

  template<int_... xs>
  using bit_and0_c = bit_and_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;

  template<int_... xs>
  using left_bit_and_c = number<(... & xs)>;

  template<int_... xs>
  using left_bit_and0_c = left_bit_and_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;

  template<int_... xs>
  using bit_or_c = number<(xs | ...)>;

  template<int_... xs>
  using bit_or0_c = bit_or_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;

  template<int_... xs>
  using left_bit_or_c = number<(... | xs)>;

  template<int_... xs>
  using left_bit_or0_c = left_bit_or_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;


  template<class... xs>
  using or_ = number<(xs::value || ... || false)>;

  template<class... xs>
  using and_ = number<(xs::value && ... && true)>;

  template<class... xs>
  using left_or = number<(false || ... || xs::value)>;

  template<class... xs>
  using left_and = number<(true && ... && xs::value)>;

  template<class... xs>
  using add = number<(xs::value + ...)>;

  template<class... xs>
  using add0 = typename mp::add0<>::template f<xs...>;

  template<class... xs>
  using left_add = number<(... + xs::value)>;

  template<class... xs>
  using left_add0 = typename mp::add0<>::template f<xs...>;

  template<class... xs>
  using sub = number<(... - xs::value)>;

  template<class... xs>
  using sub0 = typename mp::sub0<>::template f<xs...>;

  template<class... xs>
  using lshift = number<(... << xs::value)>;

  template<class... xs>
  using lshift0 = typename mp::lshift0<>::template f<xs...>;

  template<class... xs>
  using rshift = number<(... >> xs::value)>;

  template<class... xs>
  using rshift0 = typename mp::rshift0<>::template f<xs...>;

  template<class... xs>
  using mul = number<(xs::value * ...)>;

  template<class... xs>
  using mul0 = typename mp::mul0<>::template f<xs...>;

  template<class... xs>
  using mul1 = typename mp::mul1<>::template f<xs...>;

  template<class... xs>
  using left_mul = number<(... * xs::value)>;

  template<class... xs>
  using left_mul0 = typename mp::left_mul0<>::template f<xs...>;

  template<class... xs>
  using left_mul1 = typename mp::left_mul1<>::template f<xs...>;

  template<class... xs>
  using div = number<(... / xs::value)>;

  template<class... xs>
  using div0 = typename mp::div0<>::template f<xs...>;

  template<class... xs>
  using div1 = typename mp::div1<>::template f<xs...>;

  template<class... xs>
  using mod = number<(... % xs::value)>;

  template<class... xs>
  using mod0 = typename mp::mod0<>::template f<xs...>;

  template<class... xs>
  using mod1 = typename mp::mod1<>::template f<xs...>;

  template<class... xs>
  using xor_ = number<(xs::value ^ ...)>;

  template<class... xs>
  using xor0 = typename mp::xor0<>::template f<xs...>;

  template<class... xs>
  using left_xor = number<(... ^ xs::value)>;

  template<class... xs>
  using left_xor0 = typename mp::left_xor0<>::template f<xs...>;

  template<class... xs>
  using bit_and = number<(xs::value & ...)>;

  template<class... xs>
  using bit_and0 = typename mp::bit_and0<>::template f<xs...>;

  template<class... xs>
  using left_bit_and = number<(... & xs::value)>;

  template<class... xs>
  using left_bit_and0 = typename mp::left_bit_and0<>::template f<xs...>;

  template<class... xs>
  using bit_or = number<(xs::value | ...)>;

  template<class... xs>
  using bit_or0 = typename mp::bit_or0<>::template f<xs...>;

  template<class... xs>
  using left_bit_or = number<(... | xs::value)>;

  template<class... xs>
  using left_bit_or0 = typename mp::left_bit_or0<>::template f<xs...>;


  template<class x, class C = mp::identity>
  using neg = typename mp::neg<C>::template f<x>;

  template<class x, class C = mp::identity>
  using unary_plus = typename mp::unary_plus<C>::template f<x>;

  template<class x, class C = mp::identity>
  using not_ = typename mp::not_<C>::template f<x>;

  template<class x, class C = mp::identity>
  using bit_not = typename mp::bit_not<C>::template f<x>;

  template<class x, class C = mp::identity>
  using inc = typename mp::inc<C>::template f<x>;

  template<class x, class C = mp::identity>
  using dec = typename mp::dec<C>::template f<x>;

  template<class x, class y, class C = mp::identity>
  using equal = typename mp::equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using not_equal = typename mp::not_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using less = typename mp::less<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using less_equal = typename mp::less_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using greater = typename mp::greater<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using greater_equal = typename mp::greater_equal<C>::template f<x, y>;
}

JLN_MP_DIAGNOSTIC_POP()

/// \cond
namespace jln::mp
{
  /// \ingroup number

  /// Narrowing convertion from \value to \bool.
  /// \treturn \bool
  template<class C = identity>
  struct as_bool
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<bool{x::value}>);
  };

  namespace emp
  {
    template<class x>
    using as_bool = number<bool{x::value}>;
  }


  /// \cond
  template<>
  struct as_bool<identity>
  {
    template<class x>
    using f = number<bool{x::value}>;
  };
  /// \endcond
}
namespace jln::mp
{
  /// \ingroup number

  /// Converts a \value to a \bool.
  /// \treturn \bool
  template<class C = identity>
  struct to_bool
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<bool(x::value)>);
  };

  namespace emp
  {
    template<class x>
    using to_bool = number<bool(x::value)>;
  }


  /// \cond
  template<>
  struct to_bool<identity>
  {
    template<class x>
    using f = number<bool(x::value)>;
  };
  /// \endcond
}
namespace jln::mp
{
  template<>
  struct or_<identity>
  {
    template<class... xs>
    using f = number<(xs::value || ... || false)>;
  };

  template<>
  struct left_or<identity>
  {
    template<class... xs>
    using f = number<(false || ... || xs::value)>;
  };


  template<>
  struct and_<identity>
  {
    template<class... xs>
    using f = number<(xs::value && ... && true)>;
  };

  template<>
  struct left_and<identity>
  {
    template<class... xs>
    using f = number<(true && ... && xs::value)>;
  };


  template<>
  struct add<identity>
  {
    template<class... xs>
    using f = number<(xs::value + ...)>;
  };

  template<>
  struct left_add<identity>
  {
    template<class... xs>
    using f = number<(... + xs::value)>;
  };


  template<>
  struct not_<identity>
  {
    template<class x>
    using f = number<(!x::value)>;
  };


  template<>
  struct equal<identity>
  {
    template<class x, class y>
    using f = number<(x::value == y::value)>;
  };

  template<>
  struct not_equal<identity>
  {
    template<class x, class y>
    using f = number<(x::value != y::value)>;
  };

  template<>
  struct less<identity>
  {
    template<class x, class y>
    using f = number<(x::value < y::value)>;
  };

  template<>
  struct less_equal<identity>
  {
    template<class x, class y>
    using f = number<(x::value <= y::value)>;
  };

  template<>
  struct greater<identity>
  {
    template<class x, class y>
    using f = number<(x::value > y::value)>;
  };

  template<>
  struct greater_equal<identity>
  {
    template<class x, class y>
    using f = number<(x::value >= y::value)>;
  };


  template<>
  struct as_bool<not_<>>
  {
    template<class x>
    using f = number<!bool{x::value}>;
  };

  template<class C>
  struct as_bool<not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<!bool{x::value}>);
  };

  template<>
  struct to_bool<not_<>>
  {
    template<class x>
    using f = number<!bool(x::value)>;
  };

  template<class C>
  struct to_bool<not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<!bool(x::value)>);
  };

  template<class TC, class FC>
  struct if_<size<not_<>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<!sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };
}

/// \endcond
/// \cond
namespace jln::mp
{
  template<class Pred>
  struct all_of<Pred>
  {
    template<class... xs>
    using f = typename detail::is_drop_while_continue<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::type;
  };

  template<class Pred>
  struct all_of<Pred, not_<>>
  {
    template<class... xs>
    using f = number<!detail::is_drop_while_continue<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::type::value>;
  };

  template<class Pred, class C>
  struct all_of<Pred, not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(
      C,
      number<!detail::is_drop_while_continue<
        typename detail::_drop_while<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value>
    );
  };

  template<class Pred, class TC, class FC>
  struct if_<all_of<Pred>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      detail::is_drop_while_continue<
        typename detail::_drop_while<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };

  template<class Pred, class TC, class FC>
  struct if_<all_of<Pred, not_<>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      !detail::is_drop_while_continue<
        typename detail::_drop_while<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };
} // namespace jln::mp
/// \endcond
namespace jln::mp::detail
{
  template<class F>
  struct expected_argument : number<0>
  {};

  template<class F>
  struct expected_argument<memoize<F>> : expected_argument<F>
  {};

#define JLN_MP_MAKE_EXPECTED_ARGUMENT(expected, tpl, spe) \
  template<JLN_MP_UNPACK tpl>                             \
  struct expected_argument<JLN_MP_UNPACK spe>             \
  : number<expected>                                      \
  {}

#define JLN_MP_MAKE_EXPECTED_ARGUMENT1(expected, name) \
  template<class C>                                    \
  struct expected_argument<name<C>>                    \
  : number<expected>                                   \
  {}

#define JLN_MP_MAKE_EXPECTED_ARGUMENT2(expected, name) \
  template<class F, class C>                           \
  struct expected_argument<name<F, C>>                 \
  : number<expected>                                   \
  {}

#define JLN_MP_MAKE_EXPECTED_ARGUMENT3(expected, name) \
  template<class G, class F, class C>                  \
  struct expected_argument<name<G, F, C>>              \
  : number<expected>                                   \
  {}

  struct argument_category
  {
    enum tag
    {
      lists             = 1 << 0,
      number            = 1 << 1,
      positive_number   = 1 << 2,
      unary             = 1 << 3,
      binary            = 1 << 4,
      unary_or_more     = 1 << 5,
      binary_or_more    = 1 << 6,
      binary_list       = 1 << 7,
      numbers           = 1 << 8,
    };
  };

  struct _expected_argument_category : argument_category
  {
    enum tag
    {
      _lists            = lists,
      _numbers          = numbers,
      _number           = number | numbers | unary | unary_or_more,
      _positive_number  = positive_number | number | numbers | unary | unary_or_more,
      _unary            = unary | unary_or_more,
      _binary           = binary | unary_or_more | binary_or_more,
      _binary_list      = binary_list | lists | binary | unary_or_more | binary_or_more,
      _unary_or_more    = unary_or_more,
      _binary_or_more   = binary_or_more | unary_or_more,
    };
  };

#define JLN_MP_MK_ASSUME(cat)                        \
  template<class F>                                  \
  struct _assume_##cat<try_<F, identity, violation>> \
  {                                                  \
    using type = typename conditional_c<bool(        \
      expected_argument<F>::value                    \
      & _expected_argument_category::_##cat          \
    )>::template f<F, try_<F, identity, violation>>; \
  }

  JLN_MP_MK_ASSUME(lists);
  JLN_MP_MK_ASSUME(numbers);
  JLN_MP_MK_ASSUME(number);
  JLN_MP_MK_ASSUME(positive_number);
  JLN_MP_MK_ASSUME(unary);
  JLN_MP_MK_ASSUME(binary);
  JLN_MP_MK_ASSUME(binary_list);
  JLN_MP_MK_ASSUME(unary_or_more);
  JLN_MP_MK_ASSUME(binary_or_more);

#undef JLN_MP_MK_ASSUME

  template<class TC>
  struct _assume_lists<if_<mp::all_of<mp::is_list<>>, TC, violation>>
  {
    using type = TC;
  };

  template<class TC>
  struct _assume_unary_or_more<if_<mp::size<>, TC, violation>>
  {
    using type = TC;
  };

  template<class TC>
  struct _assume_unary<if_<mp::size<mp::is<number<1>>>, TC, violation>>
  {
    using type = TC;
  };

  template<class TC>
  struct _assume_binary<if_<mp::size<mp::is<number<2>>>, TC, violation>>
  {
    using type = TC;
  };

  template<class TC>
  struct _assume_binary_or_more<if_<mp::size<mp::is<number<2>>>, TC, violation>>
  {
    using type = TC;
  };
}
/// \endcond
namespace jln::mp::smp
{
  using identity = try_contract<mp::identity>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, identity>
  {
    using type = smp::identity;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT(argument_category::unary, (), (identity));
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool found = false>
    struct _drop_until;
  }
  /// \endcond

  /// \ingroup search

  /// Remove the first elements of a \sequence that does not satisfy a \predicate.
  /// \pre \c Pred::f<x> must return a boolean, 1 or 0
  /// When an element satisfy the predicate,
  /// call \c TC with it and those that follow it..
  /// Otherwise \c FC is called on the whole sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_until_xs
  /// \see take_until, take_until_xs
  /// \see search, partial_search
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_until
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_until_extended_by_n_c
  {
    template<class... xs>
    using f = typename detail::drop_while_extended_by_n_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_until_extended_by_n = drop_until_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_until = drop_until_extended_by_n_c<1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using drop_until = unpack<L, mp::drop_until<Pred, C>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
    using drop_until_extended_by_n_c = unpack<L,
      mp::drop_until_extended_by_n_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
    using drop_until_extended_by_n = unpack<L,
      mp::drop_until_extended_by_n<ExtendedByN, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_inclusive_until = unpack<L, mp::drop_inclusive_until<Pred, TC, FC>>;
  }

  /// \cond
  template<class Pred, class TC, class FC>
  struct drop_until<Pred, drop_front_c<1, TC>, FC>
  : drop_until_extended_by_n_c<1, Pred, TC, FC>
  {};
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  // _drop_until<n, b> = _drop_while<n, !b>

  template<int n>
  struct _drop_until<n, false> : _drop_until<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256,
    false
  >
  {};

  struct drop_until_impl_true
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_result<consumed+sizeof...(xs)>;
  };

#define JLN_DROP_WHILE_IMPL(n, m)                                    \
  template<>                                                         \
  struct _drop_until<n, false>                                       \
  {                                                                  \
    template<std::size_t consumed, class Pred, class x, class... xs> \
    using f = typename _drop_until<m, Pred::template f<x>::value>    \
            ::template f<consumed, Pred, xs...>;                     \
  };                                                                 \
                                                                     \
  template<>                                                         \
  struct _drop_until<n, true> : drop_until_impl_true                 \
  {}

  JLN_DROP_WHILE_IMPL(7, 6);
  JLN_DROP_WHILE_IMPL(6, 5);
  JLN_DROP_WHILE_IMPL(5, 4);
  JLN_DROP_WHILE_IMPL(4, 3);
  JLN_DROP_WHILE_IMPL(3, 2);
  JLN_DROP_WHILE_IMPL(2, 1);
  JLN_DROP_WHILE_IMPL(1, 0);

#undef JLN_DROP_WHILE_IMPL

  template<>
  struct _drop_until<0, false>
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_continue;
  };

  template<>
  struct _drop_until<0, true>
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_result<consumed+sizeof...(xs)>;
  };

  template<>
  struct _drop_until<8, false>
  {
    template<
      std::size_t consumed,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_until<7, Pred::template f<_1>::value>
      ::template f<
          consumed+sizeof...(xs), Pred,
          _2, _3, _4, _5, _6, _7, _8>;
  };

  template<>
  struct _drop_until<16, false>
  {
    template<
      std::size_t consumed,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_until<7, Pred::template f<_1>::value>
      ::template f<
          consumed+sizeof...(xs), Pred,
          _2, _3, _4, _5, _6, _7, _8>
      ::template f<
          _drop_until<sizeof...(xs), false>,
          consumed, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)               \
  template<>                                        \
  struct _drop_until<n, false>                      \
  {                                                 \
    template<                                       \
      std::size_t consumed,                         \
      class Pred,                                   \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),          \
      class... xs>                                  \
    using f = typename _drop_until<m, false>        \
      ::template f<                                 \
          consumed+sizeof...(xs), Pred,             \
          xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)> \
      ::template f<                                 \
          _drop_until<sizeof...(xs), false>,        \
          consumed, Pred, xs...>;                   \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond
namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a predicate does not hold for any element of a \sequence.
  /// \treturn \bool
  /// \see all_of, any_of
  template<class Pred, class C = identity>
  struct none_of
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(
      C,
      typename detail::is_drop_while_continue<
        typename detail::_drop_until<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type
    );
  };

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using none_of = unpack<L, mp::none_of<Pred, C>>;
  }
} // namespace jln::mp

/// \cond
namespace jln::mp
{
  template<class Pred>
  struct none_of<Pred>
  {
    template<class... xs>
    using f = typename detail::is_drop_while_continue<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::type;
  };

  template<class Pred>
  struct none_of<Pred, not_<>>
  {
    template<class... xs>
    using f = number<!detail::is_drop_while_continue<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::type::value>;
  };

  template<class Pred, class C>
  struct none_of<Pred, not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(
      C,
      number<!detail::is_drop_while_continue<
        typename detail::_drop_until<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value>
    );
  };

  template<class Pred, class TC, class FC>
  struct if_<none_of<Pred>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      detail::is_drop_while_continue<
        typename detail::_drop_until<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };

  template<class Pred, class TC, class FC>
  struct if_<none_of<Pred, not_<>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      !detail::is_drop_while_continue<
        typename detail::_drop_until<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };
} // namespace jln::mp
/// \endcond
namespace jln::mp
{
  /// \ingroup list

  /// Retrieves the first element of a sequence.
  /// \treturn \value
  template<class C = identity>
  struct front
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(C, x);
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using front = unpack<L, front<C>>;
  }
}

namespace jln::mp
{
  /// \cond
  template<>
  struct front<identity>
  {
    template<class x, class...>
    using f = x;
  };
  /// \endcond
}
namespace jln::mp
{
  /// \ingroup functional

  /// Invokes \c FC whether `na`, otherwise \c C.
  /// \treturn \value
  template<class C, class FC = violation>
  using monadic = if_<is<na>, FC, C>;

  /// Invokes \c FC whether first value is `na`, otherwise \c C.
  /// \treturn \value
  template<class C, class FC = violation>
  using monadic0 = if_<front<is<na>>, FC, C>;

  /// Invokes \c FC whether any value is `na`, otherwise \c C.
  /// \treturn \value
  template<class C, class FC = violation>
  using monadic_xs = if_<none_of<is<na>>, C, FC>;

  /// Monadify only if \c x is \c na.
  /// \treturn \value
  template<class x, template<class...> class M, class C, class FC = violation>
  using monadic_if_na = typename conditional_c<std::is_same<na, x>::value>
    ::template f<M<C, FC>, C>;
}
namespace jln::mp
{
  /// \ingroup list

  /// Remove the first element of sequence
  /// \pre `sizeof...(xs) > 0`
  /// \treturn \sequence
  template<class C = listify>
  using pop_front = drop_front_c<1, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using pop_front = drop_front_c<L, 1, C>;
  }
}
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _same;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether all \values are identical.
  /// \treturn \bool
  template<class C = identity>
  struct same
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::_same<detail::min(sizeof...(xs), 3)>::template f<xs...>);
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using same = unpack<L, mp::same<C>>;
  }
}


/// \cond
namespace jln::mp
{
  template<>
  struct same<identity>
  {
    template<class... xs>
    using f = typename detail::_same<detail::min(sizeof...(xs), 3)>::template f<xs...>;
  };
}

namespace jln::mp::detail
{
  template<>
  struct _same<0>
  {
    template<class...>
    using f = mp::true_;
  };

  template<>
  struct _same<1>
  {
    template<class>
    using f = mp::true_;
  };

  template<>
  struct _same<2>
  {
    template<class x, class y>
    using f = mp::number<std::is_same<x, y>::value>;
  };

  template<>
  struct _same<3>
  {
    template<class x, class... xs>
    using f = mp::number<std::is_same<list<x, xs...>, list<xs..., x>>::value>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct fold_left_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Folds left over a list using a binary predicate.
  /// fold_left consideres the first element in the input pack as the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<... F::f<xs[0], xs[1]>, xs[2]>, ..., xs[n-1]>, ...>
  ///   \endcode
  /// \treturn \value
  /// \see fold_right, fold_tree, reverse_fold, fold_balanced_tree
  template<class F, class C = identity>
  struct fold_left
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::fold_left_impl<
        int(sizeof...(xs)) - 1
      >::template f<JLN_MP_TRACE_F(F)::template f, xs...>
    );
  };

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using fold_left = unpack<L,
      mp::push_front<state, mp::fold_left<F, C>>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<int n>
  struct fold_left_impl : fold_left_impl<
      n < 8 ? 4
    : n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_FOLD_LEFT_SELECT(n, mp_xs, _, mp_dup)  \
  template<>                                          \
  struct fold_left_impl<n>                            \
  {                                                   \
    template<template<class...> class F, class state, \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),         \
      class... xs>                                    \
    using f = typename fold_left_impl<                \
      sizeof...(xs)                                   \
    >::template f<F,                                  \
      mp_dup(F<, JLN_MP_NIL) state,                   \
      mp_xs(JLN_MP_NIL, >, JLN_MP_COMMA), xs...       \
    >;                                                \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_FOLD_LEFT_SELECT)

#undef JLN_MP_FOLD_LEFT_SELECT

#define JLN_MP_FOLD_LEFT_SELECT(n, mp_xs, _, mp_dup)  \
  template<>                                          \
  struct fold_left_impl<n>                            \
  {                                                   \
    template<template<class...> class F, class state, \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA)>         \
    using f = mp_dup(F<, JLN_MP_NIL) state,           \
      mp_xs(JLN_MP_NIL, >, JLN_MP_COMMA);             \
  };

  JLN_MP_GEN_XS_1_TO_4(JLN_MP_FOLD_LEFT_SELECT)

#undef JLN_MP_FOLD_LEFT_SELECT

  template<>
  struct fold_left_impl<0>
  {
    template<template<class...> class, class state>
    using f = state;
  };

  template<>
  struct fold_left_impl<-1>
  {};
}
/// \endcond
namespace jln::mp
{
  /// \ingroup algorithm

  /// Executes \c F on every element of a \sequence.
  /// \treturn \sequence
#if defined(JLN_MP_DOXYGENATING) || JLN_MP_MSVC
  template<class F, class C = listify>
  struct transform
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, JLN_MP_DCALL_TRACE_XS(xs, F, xs)...);
  };
#else
  /// \cond
  namespace detail
  {
    template<class C, class F, class...xs>
    using transform_impl = JLN_MP_DCALL_TRACE_XS(xs, C, typename F::template f<xs>...);
  }
  /// \endcond

  template<class F, class C = listify>
  struct transform
  {
    template<class... xs>
    using f = detail::transform_impl<C,
      typename conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<JLN_MP_TRACE_F(F), detail::too_many_arguments_error>,
      xs...
    >;
  };
#endif

  namespace emp
  {
    template<class L, class C = mp::listify>
    using transform = unpack<L, mp::transform<C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class T>
  struct optimize_useless_transform_unpack
  {
    using type = T;
  };

  template<class T>
  using optimize_useless_transform_unpack_t
    = typename optimize_useless_transform_unpack<T>::type;

  template<class F>
  struct optimize_useless_transform_unpack_impl
  {
    template<class C>
    using f = transform<F, C>;
  };

  template<>
  struct optimize_useless_transform_unpack_impl<identity>
  {
    template<class C>
    using f = optimize_useless_transform_unpack_t<C>;
  };

  template<class F, class C>
  struct optimize_useless_transform_unpack<transform<F, C>>
  {
    using type = typename optimize_useless_transform_unpack_impl<optimize_useless_unpack_t<F>>
      ::template f<C>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _zip_dispatch;
  }
  /// \endcond

  /// \ingroup group

  /// Turns rows into columns, and columns into rows.
  /// This is similar to transposing a matrix.
  /// \pre all parameters must be \lists
  /// \pre all lists must be the same size
  /// \semantics
  ///   \code
  ///   zip<>::f<
  ///     list<_1, _2, _3>,
  ///     list<_a, _b, _c>
  ///   > = list<
  ///     list<_1, _a>,
  ///     list<_2, _b>,
  ///     list<_3, _c>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see zip_longest
  template<class F = listify, class C = listify>
  struct zip_with
  {
    template<class... seqs>
    using f = typename detail::_zip_dispatch<
      sizeof...(seqs) ? sizeof...(seqs) <= 8 ? 1 : 2 : 0
    >::template f<C, F, seqs...>;
  };

  template<class C = listify>
  using zip = zip_with<listify, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using zip = unpack<L, mp::zip<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using zip_with = unpack<L, mp::zip_with<F, C>>;
  }
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<std::size_t n>
    struct _join_select;
  }
  /// \endcond

  /// \ingroup list

  /// Concatenates \lists.
  /// \pre \c seqs must be a \sequence of \list
  /// \treturn \sequence
  template<class C = listify>
  struct join
  {
    template<class... seqs>
    using f = typename detail::_join_select<sizeof...(seqs)>
      ::template f<JLN_MP_TRACE_F(C), seqs...>::type;
  };

  namespace emp
  {
    template<class... seqs>
    using join = typename mp::join<>::template f<seqs...>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<std::size_t n>
  struct _join_select : _join_select<
      n <= 16 ? 16
    : n <= 64 ? 64
    : n <= 256 ? 256
    : 512
  >
  {};

  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_MSVC_IGNORE(4348)

#define JLN_MP_JOIN_SELECT(n, mp_xs, mp_rxs, _)   \
  template<>                                      \
  struct _join_select<n>                          \
  {                                               \
    template<class F,                             \
      mp_xs(class, = list<>, JLN_MP_COMMA)>       \
    struct f;                                     \
                                                  \
    template<class F,                             \
      mp_xs(class..., JLN_MP_NIL, JLN_MP_COMMA)>  \
    struct f<F, mp_xs(list<, ...>, JLN_MP_COMMA)> \
    {                                             \
      using type = JLN_MP_CALL_TRACE(F,           \
        mp_xs(JLN_MP_NIL, ..., JLN_MP_COMMA));    \
    };                                            \
  };

  JLN_MP_GEN_XS_16_64_256(JLN_MP_JOIN_SELECT)

#undef JLN_MP_JOIN_SELECT

  template<>
  struct _join_select<512>
  {
    template<class F,
      JLN_MP_XS_512(class, = list<>, JLN_MP_COMMA),
      class... tail>
    struct f;

    template<class F,
      JLN_MP_XS_512(class..., JLN_MP_NIL, JLN_MP_COMMA),
      class... tail>
    struct f<F, JLN_MP_XS_512(list<, ...>, JLN_MP_COMMA), tail...>
    : _join_select<sizeof...(tail)+1>
    ::template f<F, list<JLN_MP_XS_512(JLN_MP_NIL, ..., JLN_MP_COMMA)>, tail...>
    {};
  };

  JLN_MP_DIAGNOSTIC_POP()

} // namespace jln::mp::detail
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<class...>
  struct _zip_impl;

#define JLN_MP_TRANSPOSE_IMPL(n, mp_xs, mp_rxs, mp_rep) \
  template<mp_xs(class..., JLN_MP_NIL, JLN_MP_COMMA)>   \
  struct _zip_impl<mp_xs(list<, ...>, JLN_MP_COMMA)>    \
  {                                                     \
    template<class C, class F>                          \
    using f = typename C::template f<                   \
      typename F::template f<                           \
        mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)     \
      >...                                              \
    >;                                                  \
  };

  JLN_MP_GEN_XS_1_TO_8_INCLUDED(JLN_MP_TRANSPOSE_IMPL)

#undef JLN_MP_TRANSPOSE_IMPL

  template<>
  struct _zip_dispatch<0>
  {
    template<class C, class F>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  template<>
  struct _zip_dispatch<1>
  {
    template<class C, class F, class... seqs>
    using f = typename _zip_impl<seqs...>::template f<C, F>;
  };

  template<int>
  struct _recursive_zip;

  template<>
  struct _recursive_zip<0>
  {
    template<int n, class C, class F, class... seqs>
    using f = typename detail::_zip_dispatch<
      sizeof...(seqs) <= 8 ? 1 : 2
    >::template f<C, F, seqs...>;
  };

#define JLN_MP_TRANSPOSE_IMPL(n, mp_xs, mp_rxs, mp_rep)                 \
  template<>                                                            \
  struct _recursive_zip<n>                                              \
  {                                                                     \
    template<int, class C, class F                                      \
      mp_xs(JLN_MP_COMMA class, JLN_MP_NIL, JLN_MP_NIL),                \
      class... seqs>                                                    \
    using f = typename detail::_zip_dispatch<                           \
      sizeof...(seqs) < 8 ? 1 : 2                                       \
    >::template f<C, join<F>, seqs...,                                  \
        typename _zip_impl<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)> \
        ::template f<listify, listify>                                  \
      >;                                                                \
  };

  template<>
  struct _recursive_zip<8>
  {
    template<int n, class C, class F,
      class _0, class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class... seqs>
    using f = typename _recursive_zip<n < 8 ? n : 8>
      ::template f<
        n-8, C, F, seqs..., typename _zip_impl<
          _0, _1, _2, _3, _4, _5, _6, _7
        >::template f<listify, listify>
      >;
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_TRANSPOSE_IMPL)

#undef JLN_MP_TRANSPOSE_IMPL

  template<>
  struct _zip_dispatch<2>
  {
    template<class C, class F, class... seqs>
    using f = typename _recursive_zip<!sizeof...(seqs) + 8>
      ::template f<sizeof...(seqs)-8, C, F, seqs...>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup functional

  /// Invokes a \function with its two first arguments reversed.
  /// \treturn \sequence
  template<class C = listify>
  struct flip
  {
    template<class x0, class x1, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, x1, x0, xs...);
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using flip = unpack<L, mp::flip<C>>;
  }
}
namespace jln::mp
{
  /// \ingroup algorithm

  /// Computes the recursive invocation of \c F with the result of the previous
  /// invocation and each element of one or more \lists traversed in parallel
  /// from the beginning to the end.
  /// \pre all \c seqs must be the same size
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   C::f<fold_left<F>::f<
  ///     ...
  ///     fold_left<F>::f<fold_left<F>::f<state, ...seqs[:][0]>, ...seqs[:][1]>
  ///     ...,
  ///     ...seqs[:][n-1]>
  ///   >>
  ///   \endcode
  /// \treturn \value
  template<class F, class C = identity>
  struct accumulate
  {
    template<class state, class... seqs>
    using f = typename zip<push_front<state, fold_left<flip<unpack<F>>, C>>>
      ::template f<seqs...>;
  };

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using accumulate = unpack<L,
      mp::zip<mp::push_front<state, mp::fold_left<mp::flip<mp::unpack<F>>, C>>>>;
  }
}
/// \cond
namespace jln::mp::detail
{
  template<class F, class C>
  struct _smp_accumulate;
}
/// \endcond

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using accumulate = test_contract<
    mp::if_<
      mp::size<>,
      mp::pop_front<
        mp::if_<
          mp::size<>,
          mp::transform<
            try_<mp::unpack<mp::size<>>>,
            mp::monadic0<mp::same<>, mp::always<mp::false_>>
          >,
          mp::always<mp::true_>
        >
      >
    >,
    detail::_smp_accumulate<assume_binary<F>, assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, accumulate<F, C>>
  {
    using type = smp::accumulate<sfinae<F>, sfinae<C>>;
  };

  template<class F, class C>
  struct _smp_accumulate
  {
    template<class state, class... seqs>
    using f = typename zip<push_front<state, fold_left<
      monadic0<flip<unpack<F>>>, monadic<C>
    >>>::template f<seqs...>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  using listify = contract<mp::listify>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, listify>
  {
    using type = smp::listify;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template <unsigned n>
    struct rotate_impl;

    constexpr unsigned rotate_size(int_ n, unsigned size);
  }
  /// \endcond

  /// \ingroup algorithm

  /// Rotates the elements of a \sequence around a pivot.
  /// \tparam N  a negative value start to end of sequence. The final offset is a modulo of `sizeof...(xs)`.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///     n = 0
  ///     len = sizeof...(xs)
  ///     if (len) {
  ///       n = N::value
  ///       if (n < 0) n = len + (n % len)
  ///       n = n % len
  ///     }
  ///     C::f<...xs[n:], ...xs[:n]>
  ///   \endcode
  /// \treturn \sequence
  template <int_ N, class C = listify>
  struct rotate_c
  {
    template<class... xs>
    using f = typename detail::rotate_impl<
      detail::rotate_size(N, sizeof...(xs))
    >
    ::template f<
      detail::rotate_size(N, sizeof...(xs)),
      C, xs...
    >;
  };

  template <class N, class C = listify>
  using rotate = rotate_c<N::value, C>;

  namespace emp
  {
    template <class L, class n, class C = mp::listify>
    using rotate = unpack<L, mp::rotate<n, C>>;

    template <class L, int_ n, class C = mp::listify>
    using rotate_c = unpack<L, mp::rotate_c<n, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  constexpr unsigned rotate_size(int_ n, unsigned size)
  {
    return n >= size
      ? (size ? n % size : 0)
      : (n < 0 ? (size && n % size ? size + n % size : 0) : n);
  }

  template <unsigned n>
  struct rotate_impl : rotate_impl<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_ROTATE_IMPL(n, mp_xs, mp_rxs, _)           \
  template<>                                              \
  struct rotate_impl<n>                                   \
  {                                                       \
    template<unsigned size, class C,                      \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)              \
      class... xs>                                        \
    using f = JLN_MP_CALL_TRACE(C,                        \
      xs... mp_xs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL)); \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_MP_ROTATE_IMPL)

#undef JLN_MP_ROTATE_IMPL

#define JLN_MP_ROTATE_IMPL(n, mp_xs, mp_rxs, _)           \
  template<>                                              \
  struct rotate_impl<n>                                   \
  {                                                       \
    template<unsigned size, class C,                      \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)              \
      class... xs>                                        \
    using f = typename rotate_impl<size-n>                \
      ::template f<size-n, C,                             \
        xs... mp_xs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL) \
      >;                                                  \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_ROTATE_IMPL)

#undef JLN_MP_ROTATE_IMPL
} // namespace jln::mp
/// \endcond
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
namespace jln::mp::smp
{
  template<class C = listify>
  using adjacent_difference = try_contract<mp::adjacent_difference<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, adjacent_difference<C>>
  {
    using type = smp::adjacent_difference<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, adjacent_difference);
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = identity>
  using same = contract<mp::same<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, same<C>>
  {
    using type = smp::same<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct adjacent_remove_impl;
  }
  /// \endcond

  /// \ingroup filter

  /// Removes each element in a \sequence which respect a predicate with privious element.
  /// \treturn \sequence
  template<class BinaryPred, class C = listify>
  struct adjacent_remove_if
  {
    template<class... xs>
    using f = typename detail::adjacent_remove_impl<rotate_c<-1>::f<xs...>>
      ::template f<C, BinaryPred, xs...>
      ;
  };

  /// Removes each element in a \sequence which is the same type as the privious element.
  /// \treturn \sequence
  template<class C = listify>
  using adjacent_remove = adjacent_remove_if<same<>, C>;

  namespace emp
  {
    template<class L, class BinaryPred, class C = mp::listify>
    using adjacent_remove_if = unpack<L, mp::adjacent_remove_if<BinaryPred, C>>;

    template<class L, class C = mp::listify>
    using adjacent_remove = unpack<L, mp::adjacent_remove<C>>;
  }
}


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, class... Fs>
    struct _tee;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions passing all parameters to each.
  /// \treturn \value
  /// \see each, partial
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct tee
  {
    template<class... xs>
    using f = C::f<Fs::f<xs...>...>;
  };
#else
  template<class... Fs>
  struct tee
  : rotate_c<-1, lift<detail::_tee>>
  ::template f<Fs...>
  {};
#endif

  /// \cond
  template<class F, class C>
  struct tee<F, C>
  {
    template<class... xs>
    using f = typename JLN_MP_TRACE_F(C)::template f<
      JLN_MP_DCALL_TRACE_XS(xs, F, xs...)
    >;
  };

  template<class F0, class F1, class C>
  struct tee<F0, F1, C>
  {
    template<class... xs>
    using f = typename JLN_MP_TRACE_F(C)::template f<
      JLN_MP_DCALL_TRACE_XS(xs, F0, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F1, xs...)
    >;
  };

  template<class F0, class F1, class F2, class C>
  struct tee<F0, F1, F2, C>
  {
    template<class... xs>
    using f = typename JLN_MP_TRACE_F(C)::template f<
      JLN_MP_DCALL_TRACE_XS(xs, F0, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F1, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F2, xs...)
    >;
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<class C, class... Fs>
  struct _tee
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, JLN_MP_DCALL_TRACE_XS(xs, Fs, xs...)...);
  };
} // namespace jln::mp
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class F, class C>
    struct not_fn_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Returns the negation of \c F.
  /// \treturn \bool
  template<class F, class C = identity>
  using not_fn = typename detail::not_fn_impl<F, C>::type;

  namespace emp
  {
    template<class F, class... xs>
    using not_of = mp::number<!JLN_MP_DCALL_V_TRACE_XS(xs, F, xs...)>;

    template<class L, class F, class C = mp::identity>
    using not_fn = unpack<L, mp::not_fn<F, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct to_not_fn;

  template<class F>
  using to_not_fn_t = typename to_not_fn<F>::type;

  template<class Pred>
  struct to_not_fn
  {
    using type = tee<Pred, not_<>>;
  };

  template<>
  struct to_not_fn<not_<>>
  {
    using type = not_<not_<>>;
  };

  template<>
  struct to_not_fn<not_<not_<>>>
  {
    using type = not_<>;
  };

  template<class C>
  struct to_not_fn<not_<to_bool<C>>>
  : to_not_fn<not_<C>>
  {};

  template<class C>
  struct to_not_fn<not_<not_<not_<C>>>>
  : to_not_fn<not_<C>>
  {};

  template<>
  struct to_not_fn<identity>
  {
    using type = not_<>;
  };

  template<class PredNot>
  struct optimise_not_not;

  template<class PredNot>
  struct optimise_not_not<not_<not_<PredNot>>>
  {
    using type = PredNot;
  };

  template<class PredNot>
  struct optimise_not_not
  {
    using type = PredNot;
  };

  template<class C>
  struct to_not_fn<to_bool<C>>
  {
    using type = to_bool<typename optimise_not_not<to_not_fn_t<C>>::type>;
  };

  template<class x, class C>
  struct to_not_fn<is<x, C>>
  {
    using type = is<x, typename optimise_not_not<to_not_fn_t<C>>::type>;
  };

  template<class C>
  struct to_not_fn<same<C>>
  {
    using type = same<typename optimise_not_not<to_not_fn_t<C>>::type>;
  };

  template<class PredNot>
  struct to_not_fn_lift;

  template<template<class...> class F, class C, class Not>
  struct to_not_fn_lift<lift<F, tee<C, Not>>>
  {
    using type = tee<lift<F, C>, Not>;
  };

  template<class PredNot>
  struct to_not_fn_lift
  {
    using type = PredNot;
  };

  template<template<class...> class F, class C>
  struct to_not_fn<lift<F, C>>
  : to_not_fn_lift<lift<F, to_not_fn_t<C>>>
  {};

  template<class x, class C>
  struct to_not_fn<push_front<x, C>>
  {
    using type = push_front<x, to_not_fn_t<C>>;
  };

  template<class x, class C>
  struct to_not_fn<push_back<x, C>>
  {
    using type = push_back<x, to_not_fn_t<C>>;
  };

  template<class Pred>
  struct to_not_fn_tee;

  template<class Pred>
  struct to_not_fn_tee<tee<Pred, not_<>>>
  {
    using type = tee<Pred, not_<not_<>>>;
  };

  template<class Pred>
  struct to_not_fn_tee
  : to_not_fn<Pred>
  {};

  template<class Pred>
  struct to_not_fn<tee<Pred, not_<>>>
  : to_not_fn_tee<to_not_fn_t<Pred>>
  {};

  template<class PredNot>
  struct to_not_fn_tee2;

  template<class PredNot>
  struct to_not_fn_tee2<tee<PredNot, not_<>>>
  : to_not_fn<PredNot>
  {};

  template<class PredNot>
  struct to_not_fn_tee2<tee<PredNot, not_<not_<>>>>
  : to_not_fn<PredNot>
  {};

  template<class PredNot>
  struct to_not_fn_tee2
  {
    using type = PredNot;
  };

  template<class Pred, class C>
  struct to_not_fn<tee<Pred, C>>
  : to_not_fn_tee2<tee<Pred, to_not_fn_t<C>>>
  {};

  template<class F, class C>
  struct not_fn_impl
  : to_not_fn<tee<F, C>>
  {};

  template<class F>
  struct not_fn_impl<F, identity>
  : to_not_fn<F>
  {};
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class Pred>
    struct mk_wrap_in_list_if;

    template<class Pred>
    struct mk_wrap_in_list_if_not;
  }
  /// \endcond

  /// \ingroup list

  /// Returns a \list with the first element if the predicate is checked, otherwise returns a empty list.
  /// \pre \c Pred<xs...>::value must be narrowing convertible to bool
  /// \treturn \list
  template<class Pred>
  using wrap_in_list_if = typename detail::mk_wrap_in_list_if_not<
    detail::to_not_fn_t<Pred>
  >::type;

  /// Returns a \list with the first element if the predicate is not checked, otherwise returns a empty list.
  /// \pre \c Pred<xs...>::value must be narrowing convertible to bool
  /// \treturn \list
  template<class Pred>
  using wrap_in_list_if_not = typename detail::mk_wrap_in_list_if<
    detail::to_not_fn_t<Pred>
  >::type;

  template<bool b>
  struct wrap_in_list_c;

  template<>
  struct wrap_in_list_c<true>
  {
    template<class... xs>
    using f = list<xs...>;
  };

  template<>
  struct wrap_in_list_c<false>
  {
    template<class>
    using f = list<>;
  };

  template<class b>
  using wrap_in_list = wrap_in_list_c<b::value>;

  namespace emp
  {
    template<class Pred, class... xs>
    using wrap_in_list_if = typename mp::wrap_in_list_if<Pred>::template f<xs...>;

    template<class Pred, class... xs>
    using wrap_in_list_if_not = typename mp::wrap_in_list_if_not<Pred>::template f<xs...>;

    template<class b, class... xs>
    using wrap_in_list = typename mp::wrap_in_list_c<b::value>::template f<xs...>;

    template<bool b, class... xs>
    using wrap_in_list_c = typename mp::wrap_in_list_c<b>::template f<xs...>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<class Pred>
  struct _wrap_in_list_if
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(wrap_in_list_c<
      JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, xs...)
    >, x);
  };

  template<class Pred>
  struct _wrap_in_list_if_not
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(wrap_in_list_c<
      !JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, xs...)
    >, x);
  };

  template<class Pred>
  struct mk_wrap_in_list_if
  {
    using type = _wrap_in_list_if<Pred>;
  };

  template<class Pred>
  struct mk_wrap_in_list_if_not
  {
    using type = _wrap_in_list_if_not<Pred>;
  };


  template<class x>
  struct mk_wrap_in_list_if<is<x, not_<>>>
  {
    using type = _wrap_in_list_if_not<is<x>>;
  };

  template<>
  struct mk_wrap_in_list_if<same<not_<>>>
  {
    using type = _wrap_in_list_if_not<same<>>;
  };

  template<template<class...> class F>
  struct mk_wrap_in_list_if<lift<F, not_<>>>
  {
    using type = _wrap_in_list_if_not<lift<F>>;
  };

  template<class Pred>
  struct mk_wrap_in_list_if<tee<Pred, not_<>>>
  {
    using type = _wrap_in_list_if_not<Pred>;
  };


  template<class x>
  struct mk_wrap_in_list_if_not<is<x, not_<>>>
  {
    using type = _wrap_in_list_if<is<x>>;
  };

  template<>
  struct mk_wrap_in_list_if_not<same<not_<>>>
  {
    using type = _wrap_in_list_if<same<>>;
  };

  template<template<class...> class F>
  struct mk_wrap_in_list_if_not<lift<F, not_<>>>
  {
    using type = _wrap_in_list_if<lift<F>>;
  };

  template<class Pred>
  struct mk_wrap_in_list_if_not<tee<Pred, not_<>>>
  {
    using type = _wrap_in_list_if<Pred>;
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<class BinaryPred, class x, class y>
  using adjacent_remove_transform = typename wrap_in_list_c<
    !JLN_MP_TRACE_F(BinaryPred)::template f<x, y>::value
  >::template f<x>;

  template<class y, class... ys>
  struct adjacent_remove_impl<list<y, ys...>>
  {
    template<class C, class BinaryPred, class x, class... xs>
    using f = typename detail::_join_select<sizeof...(ys)+1>::template f<
      JLN_MP_TRACE_F(C),
      list<x>,
#if JLN_MP_GCC
      adjacent_remove_transform<BinaryPred, xs, ys>...
#else
      typename wrap_in_list_c<!JLN_MP_TRACE_F(BinaryPred)::template f<xs, ys>::value>
        ::template f<xs>...
#endif
    >::type;
  };

  template<class x>
  struct adjacent_remove_impl<list<x>>
  {
    template<class C, class F, class y>
    using f = typename JLN_MP_TRACE_F(C)::template f<y>;
  };

  template<>
  struct adjacent_remove_impl<list<>>
  {
    template<class C, class F, class... ys>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class BinaryPred, class C = listify>
  using adjacent_remove_if = try_contract<mp::adjacent_remove_if<
    assume_binary<BinaryPred>, subcontract<C>>>;

  template<class C = listify>
  using adjacent_remove = contract<mp::adjacent_remove<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class BinaryPred, class C>
  struct _sfinae<sfinae, adjacent_remove_if<BinaryPred, C>>
  {
    using type = smp::adjacent_remove_if<sfinae<BinaryPred>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = listify>
  using clear = contract<mp::clear<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, clear<C>>
  {
    using type = smp::clear<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool not_found = true>
    struct _drop_while_xs;

    constexpr int_ partial_drop_while_xs_size(int_ i, int_ size);

    template<int_ Size, class Pred, class... xs>
    using drop_while_xs_call = typename detail::_drop_while_xs<Size>
      ::template f<Size, Pred, xs...>;
  }
  /// \endcond

  /// \ingroup search

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// Same as \c drop_while, but the \predicate takes all the elements of
  /// the current position until the end of the list.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while, partial_drop_while_xs
  /// \see take_while, take_while_xs
  /// \see search
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_while_xs
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::_drop_while_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_while_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::drop_while_extended_by_n_impl<
      typename detail::_drop_while_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_while_extended_by_n_xs = drop_while_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_while_xs = drop_while_extended_by_n_xs_c<1, Pred, TC, FC>;

  /// Same as \c drop_while_extended_by_n_xs_c, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while, drop_while_xs
  /// \see take_while, take_while_xs
  /// \see search, partial_search
  template<int_ OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC = listify, class FC = clear<TC>>
  struct partial_drop_while_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::drop_while_extended_by_n_impl<
      typename detail::drop_while_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
        JLN_MP_TRACE_F(Pred), xs...
      >
    >::template f<ExtendedByN, TC, FC, xs...>;
  };

  template<class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_while_xs =
    partial_drop_while_extended_by_n_xs_c<OffsetEnd::value, 0, Pred, TC, FC>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_while_xs_c =
    partial_drop_while_extended_by_n_xs_c<OffsetEnd, 0, Pred, TC, FC>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_while_extended_by_n_xs =
    partial_drop_while_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>;

  template<std::size_t OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_inclusive_while_xs_c =
    partial_drop_while_extended_by_n_xs_c<OffsetEnd, 1, Pred, TC, FC>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_inclusive_while_xs =
    partial_drop_while_extended_by_n_xs_c<OffsetEnd::value, 1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_while_xs = unpack<L, mp::drop_while_xs<Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_while_extended_by_n_xs = unpack<L,
      mp::drop_while_extended_by_n_xs<ExtendedByN, Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_while_extended_by_n_xs_c = unpack<L,
      mp::drop_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_while_xs = unpack<L,
      mp::partial_drop_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_while_xs_c = unpack<L,
      mp::partial_drop_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_inclusive_while_xs = unpack<L, mp::drop_inclusive_while_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_inclusive_while_xs = unpack<L,
      mp::partial_drop_inclusive_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_inclusive_while_xs_c = unpack<L,
      mp::partial_drop_inclusive_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class ExtendedByN, class Pred,
             class TC = listify, class FC = mp::clear<TC>>
    using partial_drop_while_extended_by_n_xs = unpack<L,
      mp::partial_drop_while_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, std::size_t ExtendedByN, class Pred,
             class TC = listify, class FC = mp::clear<TC>>
    using partial_drop_while_extended_by_n_xs_c = unpack<L,
      mp::partial_drop_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>>;
  }

  /// \cond
  template<class Pred, class TC, class FC>
  struct drop_while_xs<Pred, drop_front_c<1, TC>, FC>
  : drop_while_extended_by_n_xs_c<1, Pred, TC, FC>
  {};
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  constexpr int_ partial_drop_while_xs_size(int_ i, int_ size)
  {
    return (i >= size) ? size
         : (i >= 0) ? i
         : (i >= -size) ? size + i + 1
         : 0
         ;
  }

  template<int n>
  struct _drop_while_xs<n, true> : _drop_while_xs<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256,
    true
  >
  {};

  struct drop_while_xs_impl_false
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_result<sizeof...(xs)>;
  };

#define JLN_DROP_WHILE_IMPL(n, m)                                           \
  template<>                                                                \
  struct _drop_while_xs<n, true>                                            \
  {                                                                         \
    template<std::size_t remaining, class Pred, class x, class... xs>       \
    using f = typename _drop_while_xs<m, Pred::template f<x, xs...>::value> \
            ::template f<remaining-1, Pred, xs...>;                         \
  };                                                                        \
                                                                            \
  template<>                                                                \
  struct _drop_while_xs<n, false> : drop_while_xs_impl_false                \
  {}

  JLN_DROP_WHILE_IMPL(7, 6);
  JLN_DROP_WHILE_IMPL(6, 5);
  JLN_DROP_WHILE_IMPL(5, 4);
  JLN_DROP_WHILE_IMPL(4, 3);
  JLN_DROP_WHILE_IMPL(3, 2);
  JLN_DROP_WHILE_IMPL(2, 1);
  JLN_DROP_WHILE_IMPL(1, 0);

#undef JLN_DROP_WHILE_IMPL

  // _drop_while_xs<n, b> is a _search<n, !b>

  template<>
  struct _drop_while_xs<0, true>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_continue;
  };

  template<>
  struct _drop_while_xs<0, false>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_result<sizeof...(xs)>;
  };

  template<>
  struct _drop_while_xs<8, true>
  {
    template<std::size_t remaining, class Pred, class x, class... xs>
    using f = typename _drop_while_xs<7, Pred::template f<x, xs...>::value>
      ::template f<remaining-8, Pred, xs...>;
  };

  template<>
  struct _drop_while_xs<16, true>
  {
    template<
      std::size_t remaining,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_while_xs<7, Pred::template f<
        _1, _2, _3, _4, _5, _6, _7, _8, xs...
      >::value>
      ::template f<7, Pred, _2, _3, _4, _5, _6, _7, _8, xs...>
      ::template f<_drop_while_xs<remaining-8>, remaining-8, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)                                        \
  template<>                                                                 \
  struct _drop_while_xs<n, true>                                             \
  {                                                                          \
    template<                                                                \
      std::size_t remaining,                                                 \
      class Pred,                                                            \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),                                   \
      class... xs>                                                           \
    using f = typename _drop_while_xs<m, true>                               \
      ::template f<m, Pred, xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), xs...> \
      ::template f<_drop_while_xs<remaining-m>, remaining-m, Pred, xs...>;   \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool found = false>
    struct _drop_until_xs;

    template<int_ Size, class Pred, class... xs>
    using drop_until_xs_call = typename detail::_drop_until_xs<Size>
      ::template f<Size, Pred, xs...>;
  }
  /// \endcond

  /// \ingroup search

  /// Remove the first elements of a \sequence that does not satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// Same as \c drop_until, but the \predicate takes all the elements of
  /// the current position until the end of the list.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_until, partial_drop_until_xs
  /// \see take_until, take_until_xs
  /// \see search
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_until_xs
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
        ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  /// Remove the first elements of a \sequence that does not satisfy a \predicate.
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_until_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::drop_while_extended_by_n_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_until_extended_by_n_xs = drop_until_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_until_xs = drop_until_extended_by_n_xs_c<1, Pred, TC, FC>;

  /// Same as \c drop_until_extended_by_n_xs_c, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_until, drop_until_xs
  /// \see take_until, take_until_xs
  /// \see search, partial_search
  template<int_ OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC = listify, class FC = clear<TC>>
  struct partial_drop_until_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::drop_while_extended_by_n_impl<
      detail::drop_until_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
        JLN_MP_TRACE_F(Pred), xs...
      >
    >::template f<ExtendedByN, TC, FC, xs...>;
  };

  template<class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_until_xs =
    partial_drop_until_extended_by_n_xs_c<OffsetEnd::value, 0, Pred, TC, FC>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_until_xs_c =
    partial_drop_until_extended_by_n_xs_c<OffsetEnd, 0, Pred, TC, FC>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_until_extended_by_n_xs =
    partial_drop_until_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>;

  template<std::size_t OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_inclusive_until_xs_c =
    partial_drop_until_extended_by_n_xs_c<OffsetEnd, 1, Pred, TC, FC>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_inclusive_until_xs =
    partial_drop_until_extended_by_n_xs_c<OffsetEnd::value, 1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_until_xs = unpack<L, mp::drop_until_xs<Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_until_extended_by_n_xs = unpack<L,
      mp::drop_until_extended_by_n_xs<ExtendedByN, Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_until_extended_by_n_xs_c = unpack<L,
      mp::drop_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_until_xs = unpack<L,
      mp::partial_drop_until_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_until_xs_c = unpack<L,
      mp::partial_drop_until_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_inclusive_until_xs = unpack<L, mp::drop_inclusive_until_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_inclusive_until_xs = unpack<L,
      mp::partial_drop_inclusive_until_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_inclusive_until_xs_c = unpack<L,
      mp::partial_drop_inclusive_until_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class ExtendedByN, class Pred,
             class TC = listify, class FC = mp::clear<TC>>
    using partial_drop_until_extended_by_n_xs = unpack<L,
      mp::partial_drop_until_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, std::size_t ExtendedByN, class Pred,
             class TC = listify, class FC = mp::clear<TC>>
    using partial_drop_until_extended_by_n_xs_c = unpack<L,
      mp::partial_drop_until_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>>;
  }

  /// \cond
  template<class Pred, class TC, class FC>
  struct drop_until_xs<Pred, drop_front_c<1, TC>, FC>
  : drop_until_extended_by_n_xs_c<1, Pred, TC, FC>
  {};
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  template<int n>
  struct _drop_until_xs<n, false> : _drop_until_xs<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256,
    false
  >
  {};

  struct drop_until_xs_impl_true
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_result<sizeof...(xs)>;
  };

#define JLN_DROP_WHILE_IMPL(n, m)                                           \
  template<>                                                                \
  struct _drop_until_xs<n, false>                                           \
  {                                                                         \
    template<std::size_t remaining, class Pred, class x, class... xs>       \
    using f = typename _drop_until_xs<m, Pred::template f<x, xs...>::value> \
            ::template f<remaining-1, Pred, xs...>;                         \
  };                                                                        \
                                                                            \
  template<>                                                                \
  struct _drop_until_xs<n, true> : drop_until_xs_impl_true                  \
  {}

  JLN_DROP_WHILE_IMPL(7, 6);
  JLN_DROP_WHILE_IMPL(6, 5);
  JLN_DROP_WHILE_IMPL(5, 4);
  JLN_DROP_WHILE_IMPL(4, 3);
  JLN_DROP_WHILE_IMPL(3, 2);
  JLN_DROP_WHILE_IMPL(2, 1);
  JLN_DROP_WHILE_IMPL(1, 0);

#undef JLN_DROP_WHILE_IMPL

  // _drop_until_xs<n, b> is a _search<n, !b>

  template<>
  struct _drop_until_xs<0, false>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_continue;
  };

  template<>
  struct _drop_until_xs<0, true>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_result<sizeof...(xs)>;
  };

  template<>
  struct _drop_until_xs<8, false>
  {
    template<std::size_t remaining, class Pred, class x, class... xs>
    using f = typename _drop_until_xs<7, Pred::template f<x, xs...>::value>
      ::template f<remaining-8, Pred, xs...>;
  };

  template<>
  struct _drop_until_xs<16, false>
  {
    template<
      std::size_t remaining,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_until_xs<7, Pred::template f<
        _1, _2, _3, _4, _5, _6, _7, _8, xs...
      >::value>
      ::template f<7, Pred, _2, _3, _4, _5, _6, _7, _8, xs...>
      ::template f<_drop_until_xs<remaining-8>, remaining-8, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)                                        \
  template<>                                                                 \
  struct _drop_until_xs<n, false>                                            \
  {                                                                          \
    template<                                                                \
      std::size_t remaining,                                                 \
      class Pred,                                                            \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),                                   \
      class... xs>                                                           \
    using f = typename _drop_until_xs<m, false>                              \
      ::template f<m, Pred, xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), xs...> \
      ::template f<_drop_until_xs<remaining-m>, remaining-m, Pred, xs...>;   \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct starts_with_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks if the \sequence begins with the given prefix.
  /// \treturn \bool
  /// \see ends_with
  template<class Seq, class C = identity>
  struct starts_with
  {};

  namespace emp
  {
    template<class L, class Seq, class C = mp::identity>
    using starts_with = unpack<starts_with<Seq, C>, L>;
  }

  template<class... Ts, class C>
  struct starts_with<list<Ts...>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::starts_with_impl<sizeof...(Ts) <= sizeof...(xs)>
      ::template f<sizeof...(Ts), list<Ts...>, xs...>
    );
  };
}

/// \cond

namespace jln::mp
{
  /// \ingroup list

  /// Extracts \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see take_front_max, take_back, drop_front, drop_back, take_while
  template<unsigned N, class C = listify>
  struct take_front_c
  {
    template<class... xs>
    using f = typename rotate_c<N, drop_front_c<sizeof...(xs) - N, C>>
      ::template f<xs...>;
  };

  /// Extracts at most \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see take_front, take_back, take_while
  template<unsigned N, class C = listify>
  struct take_front_max_c
  {
    template<class... xs>
    using f = typename rotate_c<N, drop_front_max_c<sizeof...(xs)
                                   - detail::min(sizeof...(xs), N), C>>
      ::template f<xs...>;
  };

  template<class N, class C = listify>
  using take_front = take_front_c<N::value, C>;

  template<class N, class C = listify>
  using take_front_max = take_front_max_c<N::value, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using take_front = unpack<L, mp::take_front<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_front_c = unpack<L, mp::take_front_c<n, C>>;

    template<class L, class N, class C = mp::listify>
    using take_front_max = unpack<L, mp::take_front_max<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_front_max_c = unpack<L, mp::take_front_max_c<n, C>>;
  }

  /// \cond
  template<class C>
  struct take_front_c<0, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS_0(xs, C);
  };

  template<class C>
  struct take_front_max_c<0, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS_0(xs, C);
  };
  /// \endcond
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct take_while_impl;

    template<class>
    struct take_while_extended_by_n_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Extract the first elements of a \sequence that satisfy a \predicate.
  /// \pre \c Pred::f<x> must return a boolean, 1 or 0
  /// When an element does not satisfy the predicate,
  /// call \c TC with it and those before it.
  /// Otherwise \c FC is called on the whole sequence.
  /// \treturn \sequence
  /// \see take_front, take_back, take_while_xs
  /// \see drop_while, drop_while_xs
  /// \see search, partial_search
  template<class Pred, class TC = listify, class FC = TC>
  struct take_while
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  /// Extract the first elements of a \sequence that satisfy a \predicate.
  /// When an element satisfy the predicate,
  /// call \c TC with it and those before it + \c ExtendedByN.
  /// Otherwise \c FC is called on the whole sequence.
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct take_while_extended_by_n_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_while_extended_by_n = take_while_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_while = take_while_extended_by_n_c<1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_while = unpack<L, mp::take_while<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_inclusive_while = unpack<L, mp::take_while_extended_by_n_c<1, Pred, TC, FC>>;

    template<class ExtendedByN, class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_while_extended_by_n
      = unpack<L, mp::take_while_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>>;

    template<std::size_t ExtendedByN,
             class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_while_extended_by_n_c
      = unpack<L, mp::take_while_extended_by_n_c<ExtendedByN, Pred, TC, FC>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<>
  struct take_while_impl<_drop_while_continue>
  {
    template<class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(FC, xs...);
  };

  template<std::size_t n>
  struct take_while_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, class... xs>
    using f = typename take_front_c<sizeof...(xs)-n-1, TC>::template f<xs...>;
  };


  template<>
  struct take_while_extended_by_n_impl<_drop_while_continue>
  {
    template<std::size_t ExtendedByN, class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(FC, xs...);
  };

  template<std::size_t n>
  struct take_while_extended_by_n_impl<_drop_while_result<n>>
  {
    template<std::size_t ExtendedByN, class TC, class FC, class... xs>
    using f = typename take_front_c<
      sizeof...(xs) - (n >= ExtendedByN ? n - ExtendedByN + 1 : 0),
      TC
    >::template f<xs...>;
  };
}
/// \encond
namespace jln::mp
{
  /// \ingroup search

  /// Extracts the first elements of a \sequence that satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see take_front, take_back, take_while, partial_take_while_xs
  /// \see drop_while, drop_while_xs
  /// \see search
  template<class Pred, class TC = listify, class FC = TC>
  struct take_while_xs
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_while_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  /// Extracts the first elements of a \sequence that satisfy a \predicate.
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct take_while_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::_drop_while_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_while_extended_by_n_xs = take_while_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_while_xs = take_while_extended_by_n_xs_c<1, Pred, TC, FC>;

  /// Same as \c take_while_extended_by_n_xs_c, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while, drop_while_xs
  /// \see take_while, take_while_xs
  /// \see search, partial_search
  template<int_ OffsetEnd, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct partial_take_while_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::drop_while_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
        JLN_MP_TRACE_F(Pred), xs...
      >
    >::template f<ExtendedByN, TC, FC, xs...>;
  };

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_while_xs =
    partial_take_while_extended_by_n_xs_c<OffsetEnd::value, 0, Pred, TC, FC>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_while_xs_c =
    partial_take_while_extended_by_n_xs_c<OffsetEnd, 0, Pred, TC, FC>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_take_while_extended_by_n_xs =
    partial_take_while_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>;

  template<std::size_t OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_inclusive_while_xs_c =
    partial_take_while_extended_by_n_xs_c<OffsetEnd, 1, Pred, TC, FC>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_inclusive_while_xs =
    partial_take_while_extended_by_n_xs_c<OffsetEnd::value, 1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using take_while_xs = unpack<L, mp::take_while_xs<Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred, class TC = mp::listify, class FC = TC>
    using take_while_extended_by_n_xs = unpack<L,
      mp::take_while_extended_by_n_xs<ExtendedByN, Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = mp::listify, class FC = TC>
    using take_while_extended_by_n_xs_c = unpack<L,
      mp::take_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_take_while_xs = unpack<L,
      mp::partial_take_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_take_while_xs_c = unpack<L,
      mp::partial_take_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using take_inclusive_while_xs = unpack<L, mp::take_inclusive_while_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = TC>
    using partial_take_inclusive_while_xs = unpack<L,
      mp::partial_take_inclusive_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred,
             class TC = mp::listify, class FC = TC>
    using partial_take_inclusive_while_xs_c = unpack<L,
      mp::partial_take_inclusive_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class ExtendedByN, class Pred,
             class TC = listify, class FC = TC>
    using partial_take_while_extended_by_n_xs = unpack<L,
      mp::partial_take_while_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, std::size_t ExtendedByN, class Pred,
             class TC = listify, class FC = TC>
    using partial_take_while_extended_by_n_xs_c = unpack<L,
      mp::partial_take_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>>;
  }
}
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct index_if_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Finds the index of the first element of \sequence
  /// that satisfies the \predicate \c Pred.
  /// Calls \c TC with the index found or \c FC with the whole \sequence.
  /// \treturn \number
  template<class Pred, class TC = identity, class FC = size<>>
  struct index_if
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  /// Finds the index of the first element of \sequence that is a type \c T.
  /// Calls \c TC with the index found or \c FC with the whole \sequence.
  /// \treturn \number
  template<class T, class TC = identity, class FC = size<>>
  using index_of = index_if<is<T>, TC, FC>;

  /// Search the index of first sub-\sequence that satisfy a \predicate.
  /// \treturn \sequence
  template<class Pred, class TC = identity, class FC = size<>>
  struct index_if_xs
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  /// Same as \c index_if_xs, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  template<int_ OffsetEnd, class Pred, class TC = identity, class FC = size<>>
  struct partial_index_if_xs_c
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      detail::drop_until_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
        JLN_MP_TRACE_F(Pred), xs...
      >
    >::template f<TC, FC, xs...>;
  };

  template<class OffsetEnd, class Pred, class TC = identity, class FC = size<>>
  using partial_index_if_xs = partial_index_if_xs_c<OffsetEnd::value, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    using index_if = unpack<L, mp::index_if<Pred, TC, FC>>;

    template<class L, class T, class TC = mp::identity, class FC = mp::size<>>
    using index_of = unpack<L, mp::index_of<T, TC, FC>>;

    template<class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    using index_if_xs = unpack<L, mp::index_if_xs<Pred, TC, FC>>;

    template<class OffsetEnd, class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    using partial_index_if_xs = unpack<L, mp::partial_index_if_xs<OffsetEnd, Pred, TC, FC>>;

    template<int_ OffsetEnd, class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    using partial_index_if_xs_c = unpack<L, mp::partial_index_if_xs_c<OffsetEnd, Pred, TC, FC>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<>
  struct index_if_impl<_drop_while_continue>
  {
    template<class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(FC, xs...);
  };

  template<std::size_t n>
  struct index_if_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(TC, number<sizeof...(xs)-n-1>);
  };
}
/// \endcond
namespace jln::mp::detail
{
  template<>
  struct starts_with_impl<true>
  {
    template<unsigned n, class L, class... xs>
    using f = number<std::is_same<typename take_front_c<n>::template f<xs...>, L>::value>;
  };

  template<>
  struct starts_with_impl<false>
  {
    template<unsigned n, class L, class... xs>
    using f = false_;
  };
}

namespace jln::mp
{
  template<class T, class C>
  struct starts_with<list<T>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename conditional_c<1 <= sizeof...(xs)>
      ::template f<front<is<T>>, always<false_>>
      ::template f<xs...>
    );
  };

  template<class C>
  struct starts_with<list<>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, true_);
  };


  template<class C>
  struct optimized_starts_with_empty
  {
    using type = if_<size<>, always<true_, C>>;
  };

  template<>
  struct optimized_starts_with_empty<identity>
  {
    using type = size<>;
  };


  template<int_>
  struct optimized_index_if_xs_starts_with;

  template<>
  struct optimized_index_if_xs_starts_with<0>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = if_<typename optimized_starts_with_empty<C>::type, always<number<0>, TC>, FC>;
  };

  template<>
  struct optimized_index_if_xs_starts_with<1>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = index_if<is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_index_if_xs_starts_with<2>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = partial_index_if_xs_c<-int_(sizeof...(Ts)),
      starts_with<list<Ts...>, C>, TC, FC>;
  };

  // optimize index_if_xs with starts_with
  template<class... Ts, class C, class TC, class FC>
  struct index_if_xs<starts_with<list<Ts...>, C>, TC, FC>
  : optimized_index_if_xs_starts_with<detail::min(sizeof...(Ts), 2)>
    ::template f<C, TC, FC, Ts...>
  {};


  template<int_>
  struct optimized_drop_while_starts_with;

  template<>
  struct optimized_drop_while_starts_with<0>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = if_<typename optimized_starts_with_empty<C>::type, clear<TC>, FC>;
  };

  template<>
  struct optimized_drop_while_starts_with<1>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = drop_while<is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_drop_while_starts_with<2>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = partial_drop_while_xs_c<-int_(sizeof...(Ts)),
      starts_with<list<Ts...>, C>, TC, FC>;
  };

  template<class... Ts, class C, class TC, class FC>
  struct drop_while_xs<starts_with<list<Ts...>, C>, TC, FC>
  : optimized_drop_while_starts_with<detail::min(sizeof...(Ts), 2)>
    ::template f<C, TC, FC, Ts...>
  {};


  template<int_>
  struct optimized_take_while_starts_with;

  template<>
  struct optimized_take_while_starts_with<0>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = if_<typename optimized_starts_with_empty<C>::type, TC, FC>;
  };

  template<>
  struct optimized_take_while_starts_with<1>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = take_while<is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_take_while_starts_with<2>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = partial_take_while_xs_c<-int_(sizeof...(Ts)),
      starts_with<list<Ts...>, C>, TC, FC>;
  };

  template<class... Ts, class C, class TC, class FC>
  struct take_while_xs<starts_with<list<Ts...>, C>, TC, FC>
  : optimized_take_while_starts_with<detail::min(sizeof...(Ts), 2)>
    ::template f<C, TC, FC, Ts...>
  {};


  template<int_>
  struct optimized_take_while_extended_by_n_starts_with;

  template<>
  struct optimized_take_while_extended_by_n_starts_with<0>
  {
    template<std::size_t ExtendedByN, class C, class TC, class FC, class... Ts>
    using f = if_<typename optimized_starts_with_empty<C>::type, TC, FC>;
  };

  template<>
  struct optimized_take_while_extended_by_n_starts_with<1>
  {
    template<std::size_t ExtendedByN, class C, class TC, class FC, class... Ts>
    using f = take_while_extended_by_n_c<ExtendedByN, is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_take_while_extended_by_n_starts_with<2>
  {
    template<std::size_t ExtendedByN, class C, class TC, class FC, class... Ts>
    using f = partial_take_while_extended_by_n_xs_c<
      -int_(sizeof...(Ts)), ExtendedByN, starts_with<list<Ts...>, C>, TC, FC
    >;
  };

  template<std::size_t ExtendedByN, class... Ts, class C, class TC, class FC>
  struct take_while_extended_by_n_xs_c<ExtendedByN, starts_with<list<Ts...>, C>, TC, FC>
  : optimized_take_while_extended_by_n_starts_with<detail::min(sizeof...(Ts), 2)>
    ::template f<C, TC, FC, Ts...>
  {};
}
/// \endcond
namespace jln::mp
{
  /// \ingroup search

  /// Find the \sequence after a sub-\sequence.
  /// Calls \c TC with all the elements after the sub-\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, search_before
  template<class Seq, class TC = listify, class FC = clear<TC>>
  struct after
  {};

  template<class... Ts, class TC, class FC>
  struct after<list<Ts...>, TC, FC>
  : partial_drop_until_extended_by_n_xs_c<-int_{sizeof...(Ts)},
                                          sizeof...(Ts),
                                          starts_with<list<Ts...>>,
                                          TC, FC>
  {};

  namespace emp
  {
    template<class L, class Seq, class TC = mp::listify, class FC = mp::clear<TC>>
    using after = unpack<L, mp::after<Seq, TC, FC>>;
  }

  /// \cond
  template<class T, class TC, class FC>
  struct after<list<T>, TC, FC>
  : drop_until_extended_by_n_c<1, is<T>, TC, FC>
  {};

  template<class TC, class FC>
  struct after<list<>, TC, FC>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, TC, xs...);
  };
  /// \endcond
}
namespace jln::mp::smp
{
  template<class Seq, class TC = listify, class FC = clear<TC>>
  using after = typename mp::conditional_c<detail::_is_list<Seq>::type::value>
    ::template f<contract<mp::after<Seq, subcontract<TC>, subcontract<FC>>>, bad_contract>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Seq, class TC, class FC>
  struct _sfinae<sfinae, after<Seq, TC, FC>>
  {
    using type = smp::after<Seq, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
namespace jln::mp::smp::concepts
{
  // TODO optimize Pred = is<>, same<>, lift<std::is_same>, equal, less, not_
  // TODO optimize when FC = always
  // {unary, binary, mulary}_predicate
  template<class Pred, class TC = mp::identity, class FC = mp::always<false_>>
  using predicate = mp::try_<Pred, mp::try_or<mp::to_bool<TC>, FC>, FC>;

  template<class Pred, class TC = mp::identity, class FC = mp::always<false_>>
  using strong_predicate = mp::try_<Pred, mp::try_or<mp::as_bool<TC>, FC>, FC>;

  template<class Pred, class FC = mp::always<false_>>
  using predicate_or = predicate<Pred, mp::identity, FC>;

  template<class Pred, class FC = mp::always<false_>>
  using strong_predicate_or = strong_predicate<Pred, mp::identity, FC>;
}
namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<listify>>
  using drop_while = contract<mp::drop_while<
    concepts::strong_predicate<assume_unary<Pred>, mp::identity, mp::always<false_>>,
    mp::if_<
      mp::front<concepts::strong_predicate<assume_unary<Pred>, mp::always<true_>>>,
      assume_unary_or_more<TC>,
      violation
    >,
    subcontract<FC>
  >>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_while = drop_while<
    Pred, contract<mp::drop_front_c<1, subcontract<TC>>>, FC>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_while_extended_by_n_c = drop_while<
    Pred, contract<mp::drop_front_max_c<ExtendedByN, subcontract<TC>>>, FC>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(drop_while_extended_by_n,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, clear<TC>),
  smp::drop_while_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, drop_while<Pred, TC, FC>>
  {
    using type = smp::drop_while<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, std::size_t ExtendedByN, class Pred, class TC, class FC>
  struct _sfinae<sfinae, drop_while_extended_by_n_c<ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::drop_while_extended_by_n_c<ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class x, class C = identity>
  using always = contract<mp::always<x, assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class T, class C>
  struct _sfinae<sfinae, always<T, C>>
  {
    using type = smp::always<T, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using all_of = drop_while<Pred,
    always<false_, assume_positive_number_barrier<C>>,
    always<true_, assume_positive_number_barrier<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, all_of<Pred, C>>
  {
    using type = smp::all_of<sfinae<Pred>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup number

  template<class C = listify>
  struct numbers
  {
    template<int_... ns>
    using f = JLN_MP_DCALL_TRACE_XS(ns, C, number<ns>...);
  };

  /// \cond
  template<>
  struct numbers<listify>
  {
    template<int_... ns>
    using f = list<number<ns>...>;
  };
  /// \endcond

  namespace emp
  {
    template<int_... vs>
    using numbers = list<number<vs>...>;
  }
}
#if defined(__has_builtin)
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


namespace jln::mp
{
  /// \cond
  namespace detail
  {
#if JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
    template<std::size_t>
#else
    template<class>
#endif
    struct _make_int_sequence;
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
#if JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
    using f = typename detail::_make_int_sequence<n::value>
      ::type::template f<C>;
#else
    using f = typename detail::_make_int_sequence<
      std::make_index_sequence<n::value>>::template f<C>;
#endif
  };

  template<class C = mp::listify>
  using make_int_sequence = make_int_sequence_v<mp::numbers<C>>;

  namespace emp
  {
#if JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
    template<unsigned n, class C = mp::numbers<>>
    using make_int_sequence_v_c = typename detail::_make_int_sequence<n>
      ::type::template f<C>;

    template<unsigned n, class C = mp::listify>
    using make_int_sequence_c = typename detail::_make_int_sequence<n>
      ::type::template f<mp::numbers<C>>;
#else
    template<unsigned n, class C = mp::numbers<>>
    using make_int_sequence_v_c = typename detail::_make_int_sequence<
      std::make_index_sequence<n>>::template f<C>;

    template<unsigned n, class C = mp::listify>
    using make_int_sequence_c = typename detail::_make_int_sequence<
      std::make_index_sequence<n>>::template f<mp::numbers<C>>;
#endif

    template<class n, class C = mp::numbers<>>
    using make_int_sequence_v = make_int_sequence_v_c<n::value, C>;

    template<class n, class C = mp::listify>
    using make_int_sequence = make_int_sequence_c<n::value, C>;
  }
} // namespace jln::mp


/// \cond
namespace jln::mp::detail
{
#if JLN_MP_USE_MAKE_INTEGER_SEQ
  template<class, int_... ns>
  struct _make_int_sequence_impl
  {
    template<class C>
    using f = typename C::template f<ns...>;
  };

  template<std::size_t n>
  struct _make_int_sequence
  {
    using type = __make_integer_seq<_make_int_sequence_impl, int_, n>;
  };
#elif JLN_MP_USE_INTEGER_PACK
  template<int_... ns>
  struct _make_int_sequence_impl
  {
    template<class C>
    using f = typename JLN_MP_TRACE_F(C)::template f<ns...>;
  };

  template<std::size_t n>
  struct _make_int_sequence
  {
    using type = _make_int_sequence_impl<__integer_pack(n)...>;
  };
#else
  template<std::size_t... ns>
  struct _make_int_sequence<std::integer_sequence<std::size_t, ns...>>
  {
    template<class C>
    using f = typename JLN_MP_TRACE_F(C)::template f<int_(ns)...>;
  };
#endif
}
/// \endcond

#undef JLN_MP_USE_INTEGER_PACK
#undef JLN_MP_USE_MAKE_INTEGER_SEQ
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class F>
    struct circulant_matrix_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// square matrix in which all row vectors are composed of the
  /// same elements and each row vector is rotated one element to
  /// the right relative to the preceding row vector.
  /// \semcs
  ///   \code
  ///   circulant_matrix_with<>::f<a, b, c, d>
  ///   == list<
  ///     list<a, b, c, d>,
  ///     list<d, a, b, c>,
  ///     list<c, d, a, b>,
  ///     list<b, c, d, a>
  ///   >
  ///   \endcode
  /// \treturn \value
  /// \see anticirculant_matrix
  template<class F = listify, class C = listify>
  struct circulant_matrix_with
  {
    template<class... xs>
    using f = typename emp::make_int_sequence_v_c<
      sizeof...(xs),
      detail::circulant_matrix_impl<F>
    >::template g<C>::template f<xs...>;
  };

  template<class C = listify>
  using circulant_matrix = circulant_matrix_with<listify, C>;

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using circulant_matrix_with = unpack<L, mp::circulant_matrix_with<F, C>>;

    template<class L, class C = mp::listify>
    using circulant_matrix = unpack<L, mp::circulant_matrix<C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct circulant_matrix_impl
  {
    template<int_... i>
    struct f
    {
      template<class C>
      using g = _tee<C, rotate_c<-i, F>...>;
    };
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct smp_listify_or_monadic_xs_impl;

  template<class F, class C>
  using smp_listify_or_monadic_xs = typename smp_listify_or_monadic_xs_impl<
    std::is_same<F, smp::listify>::value>::template f<C>;
}
/// \endcond

namespace jln::mp::smp
{
  template<class F = listify, class C = listify>
  using circulant_matrix_with = contract<mp::circulant_matrix_with<
    assume_unary_or_more<F>, detail::smp_listify_or_monadic_xs<F, C>
  >>;

  template<class C = listify>
  using circulant_matrix = contract<mp::circulant_matrix<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, circulant_matrix_with<F, C>>
  {
    using type = smp::circulant_matrix_with<sfinae<F>, sfinae<C>>;
  };


  template<>
  struct smp_listify_or_monadic_xs_impl<false>
  {
    template<class C>
    using f = mp::monadic_xs<subcontract<C>>;
  };

  template<>
  struct smp_listify_or_monadic_xs_impl<true>
  {
    template<class C>
    using f = assume_lists<C>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class F>
    struct anticirculant_matrix_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// square matrix in which all row vectors are composed of the
  /// same elements and each row vector is rotated one element to
  /// the left relative to the preceding row vector.
  /// \semantics
  ///   \code
  ///   anticirculant_matrix_with<>::f<a, b, c, d>
  ///   == list<
  ///     list<a, b, c, d>,
  ///     list<b, c, d, a>,
  ///     list<c, d, a, b>,
  ///     list<d, a, b, c>
  ///   >
  ///   \endcode
  /// \treturn \value
  /// \see circulant_matrix
  template<class F = listify, class C = listify>
  struct anticirculant_matrix_with
  {
    template<class... xs>
    using f = typename emp::make_int_sequence_v_c<
      sizeof...(xs),
      detail::anticirculant_matrix_impl<F>
    >::template g<C>::template f<xs...>;
  };

  template<class C = listify>
  using anticirculant_matrix = anticirculant_matrix_with<listify, C>;

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using anticirculant_matrix_with = unpack<L, mp::anticirculant_matrix_with<F, C>>;

    template<class L, class C = mp::listify>
    using anticirculant_matrix = unpack<L, mp::anticirculant_matrix<C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct anticirculant_matrix_impl
  {
    template<int_... i>
    struct f
    {
      template<class C>
      using g = _tee<C, rotate_c<i, F>...>;
    };
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class F = listify, class C = listify>
  using anticirculant_matrix_with = contract<mp::anticirculant_matrix_with<
    assume_unary_or_more<F>, detail::smp_listify_or_monadic_xs<F, C>
  >>;

  template<class C = listify>
  using anticirculant_matrix = contract<mp::anticirculant_matrix<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, anticirculant_matrix_with<F, C>>
  {
    using type = smp::anticirculant_matrix_with<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<listify>>
  using drop_until = contract<mp::drop_until<
    concepts::strong_predicate<assume_unary<Pred>, mp::identity, mp::always<true_>>,
    mp::if_<
      mp::front<concepts::strong_predicate<assume_unary<Pred>, mp::always<true_>>>,
      assume_unary_or_more<TC>,
      violation
    >,
    subcontract<FC>
  >>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_until = drop_until<
    Pred, contract<mp::drop_front_c<1, subcontract<TC>>>, FC>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_until_extended_by_n_c = drop_until<
    Pred, contract<mp::drop_front_max_c<ExtendedByN, subcontract<TC>>>, FC>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(drop_until_extended_by_n,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, clear<TC>),
  smp::drop_until_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, drop_until<Pred, TC, FC>>
  {
    using type = smp::drop_until<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, std::size_t ExtendedByN, class Pred, class TC, class FC>
  struct _sfinae<sfinae, drop_until_extended_by_n_c<ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::drop_until_extended_by_n_c<ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using none_of = drop_until<Pred,
    always<false_, assume_positive_number_barrier<C>>,
    always<true_, assume_positive_number_barrier<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, none_of<Pred, C>>
  {
    using type = smp::none_of<sfinae<Pred>, sfinae<C>>;
  };
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = identity>
  using to_bool = try_contract<mp::to_bool<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, to_bool<C>>
  {
    using type = smp::to_bool<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup functional

  /// Invokes twice.
  /// \treturn \value
  template<class F>
  struct invoke_twice
  {
    template<class... xs>
    using f = JLN_MP_TRACE_TYPENAME JLN_MP_TRACE_F(JLN_MP_DCALL_TRACE_XS(xs, F, xs...))
      ::template f<xs...>;
  };
}
namespace jln::mp
{
  /// \ingroup number

  /// Narrowing convertion from \value to \number.
  /// \treturn \number
  template<class C = identity>
  struct as_number
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<int_{x::value}>);
  };

  namespace emp
  {
    template<class x>
    using as_number = number<int_{x::value}>;
  }
}
namespace jln::mp::smp
{
  template<class Pred, class TC, class FC = always<false_>>
  using if_ = contract<
    mp::invoke_twice<
      mp::try_<
        subcontract<Pred>,
        mp::try_<
          mp::to_bool<>,
          mp::if_<
            mp::identity,
            mp::always<subcontract<TC>>,
            mp::always<subcontract<FC>>
          >,
          mp::always<violation>
        >,
        mp::always<violation>
      >
    >
  >;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, if_<Pred, TC, FC>>
  {
    using type = smp::if_<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class x, class C = identity>
  using is = try_contract<mp::is<x, assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, is<x, C>>
  {
    using type = smp::is<x, sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT2(argument_category::unary, is);
}
/// \endcond
namespace jln::mp
{
  /// \ingroup list

  template<class N, class C = identity>
  using is_size_of = size<is<N, C>>;

  template<int_ n, class C = identity>
  using is_size_of_c = size<is<number<n>, C>>;

  namespace emp
  {
    template<class L, class N, class C = mp::identity>
    using is_size_of = unpack<L, mp::is_size_of<N, C>>;

    template<class L, int_ n, class C = mp::identity>
    using is_size_of_c = unpack<L, mp::is_size_of_c<n, C>>;
  }
}
namespace jln::mp::smp
{
  template<int_ n, class C = identity>
  using is_size_of_c = contract<mp::is_size_of_c<n, assume_positive_number<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(is_size_of, (N), (C, smp::identity), smp::is_size_of_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, is_size_of<N, C>>
  {
    using type = smp::is_size_of<N, sfinae<C>>;
  };
}
/// \endcond
// is_size_of<> is a size<>
namespace jln::mp::smp
{
  template<class C = identity>
  using size = contract<mp::size<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, size<C>>
  {
    using type = smp::size<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class x, class C = listify>
  using push_back = contract<mp::push_back<x, subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, push_back<x, C>>
  {
    using type = smp::push_back<x, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class x, class C = listify>
  using push_front = contract<mp::push_front<x, subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, push_front<x, C>>
  {
    using type = smp::push_front<x, sfinae<C>>;
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_drop_front;

  template<bool>
  struct mk_drop_front_max;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using drop_front_c = typename detail::mk_drop_front<n >= 0>
    ::template f<n, C>;

  template<int_ n, class C = listify>
  using drop_front_max_c = typename detail::mk_drop_front_max<n >= 0>
    ::template f<n, C>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(drop_front, (N), (C, smp::listify), smp::drop_front_c<N::value, C>)
JLN_MP_MAKE_REGULAR_SMP2_P(drop_front_max, (N), (C, smp::listify), smp::drop_front_max_c<N::value, C>)


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, drop_front_c<N, C>>
  {
    using type = smp::drop_front_c<N, sfinae<C>>;
  };

  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, drop_front_max_c<N, C>>
  {
    using type = smp::drop_front_max_c<N, sfinae<C>>;
  };

  template<>
  struct mk_drop_front<true>
  {
    template<int_ n, class C>
    using f = test_contract<
      mp::size<mp::greater_equal_than_c<n>>,
      mp::drop_front_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_drop_front<false>
  {
    template<int_ i, int_ start, class C>
    using f = bad_contract;
  };

  template<>
  struct mk_drop_front_max<true>
  {
    template<int_ n, class C>
    using f = contract<mp::drop_front_max_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_drop_front_max<false>
  {
    template<int_ i, int_ start, class C>
    using f = bad_contract;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = listify>
  using pop_front = drop_front_c<1, C>;
}
/// \cond
namespace jln::mp::detail
{
  template<template<class...> class Tpl, class C, int_ i = 0>
  using smp_op_default = contract<
    if_<
      size<>,
      try_<Tpl<assume_number<C>>>,
      always<number<i>, assume_number<C>>
    >
  >;

// x/0 is not a substitution failure
#if JLN_MP_MSVC
  template<template<class...> class Tpl, class C, int_ i = 0>
  using smp_op_without_zero = contract<
    if_<
      size<>,
      if_<
        pop_front<and_<>>,
        try_<Tpl<assume_number<C>>>,
        violation
      >,
      always<number<i>, assume_number<C>>
    >
  >;

  template<class C>
  using smp_op_without_zero_and_with_value = contract<
    if_<
      size<>,
      if_<
        pop_front<and_<>>,
        try_<C>,
        violation
      >,
      violation
    >
  >;
# define JLN_smp_op_without_zero detail::smp_op_without_zero
# define JLN_smp_op_without_zero_and_with_value detail::smp_op_without_zero_and_with_value
#else
# define JLN_smp_op_without_zero detail::smp_op_default
# define JLN_smp_op_without_zero_and_with_value try_contract
#endif
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = identity>
  using or_ = try_contract<mp::or_<assume_number<C>>>;

  template<class C = identity>
  using and_ = try_contract<mp::and_<assume_number<C>>>;

  template<class C = identity>
  using left_or = try_contract<mp::left_or<assume_number<C>>>;

  template<class C = identity>
  using left_and = try_contract<mp::left_and<assume_number<C>>>;

  template<class C = identity>
  using add = try_contract<mp::add<assume_number<C>>>;

  template<class C = identity>
  using add0 = detail::smp_op_default<mp::add, C>;

  template<class C = identity>
  using left_add = try_contract<mp::left_add<assume_number<C>>>;

  template<class C = identity>
  using left_add0 = detail::smp_op_default<mp::left_add, C>;

  template<class C = identity>
  using sub = try_contract<mp::sub<assume_number<C>>>;

  template<class C = identity>
  using sub0 = detail::smp_op_default<mp::sub, C>;

  template<class C = identity>
  using lshift = try_contract<mp::lshift<assume_number<C>>>;

  template<class C = identity>
  using lshift0 = detail::smp_op_default<mp::lshift, C>;

  template<class C = identity>
  using rshift = try_contract<mp::rshift<assume_number<C>>>;

  template<class C = identity>
  using rshift0 = detail::smp_op_default<mp::rshift, C>;

  template<class C = identity>
  using mul = try_contract<mp::mul<assume_number<C>>>;

  template<class C = identity>
  using mul0 = detail::smp_op_default<mp::mul, C>;

  template<class C = identity>
  using mul1 = detail::smp_op_default<mp::mul, C, 1>;

  template<class C = identity>
  using left_mul = try_contract<mp::left_mul<assume_number<C>>>;

  template<class C = identity>
  using left_mul0 = detail::smp_op_default<mp::left_mul, C>;

  template<class C = identity>
  using left_mul1 = detail::smp_op_default<mp::left_mul, C, 1>;

  template<class C = identity>
  using div = JLN_smp_op_without_zero_and_with_value<mp::div<assume_number<C>>>;

  template<class C = identity>
  using div0 = JLN_smp_op_without_zero<mp::div, C>;

  template<class C = identity>
  using div1 = JLN_smp_op_without_zero<mp::div, C, 1>;

  template<class C = identity>
  using mod = JLN_smp_op_without_zero_and_with_value<mp::mod<assume_number<C>>>;

  template<class C = identity>
  using mod0 = JLN_smp_op_without_zero<mp::mod, C>;

  template<class C = identity>
  using mod1 = JLN_smp_op_without_zero<mp::mod, C, 1>;

  template<class C = identity>
  using xor_ = try_contract<mp::xor_<assume_number<C>>>;

  template<class C = identity>
  using xor0 = detail::smp_op_default<mp::xor_, C>;

  template<class C = identity>
  using left_xor = try_contract<mp::left_xor<assume_number<C>>>;

  template<class C = identity>
  using left_xor0 = detail::smp_op_default<mp::left_xor, C>;

  template<class C = identity>
  using bit_and = try_contract<mp::bit_and<assume_number<C>>>;

  template<class C = identity>
  using bit_and0 = detail::smp_op_default<mp::bit_and, C>;

  template<class C = identity>
  using left_bit_and = try_contract<mp::left_bit_and<assume_number<C>>>;

  template<class C = identity>
  using left_bit_and0 = detail::smp_op_default<mp::left_bit_and, C>;

  template<class C = identity>
  using bit_or = try_contract<mp::bit_or<assume_number<C>>>;

  template<class C = identity>
  using bit_or0 = detail::smp_op_default<mp::bit_or, C>;

  template<class C = identity>
  using left_bit_or = try_contract<mp::left_bit_or<assume_number<C>>>;

  template<class C = identity>
  using left_bit_or0 = detail::smp_op_default<mp::left_bit_or, C>;

  template<class C = identity>
  using neg = try_contract<mp::neg<assume_number<C>>>;

  template<class C = identity>
  using unary_plus = try_contract<mp::unary_plus<assume_number<C>>>;

  template<class C = identity>
  using not_ = try_contract<mp::not_<assume_number<C>>>;

  template<class C = identity>
  using bit_not = try_contract<mp::bit_not<assume_number<C>>>;

  template<class C = identity>
  using inc = try_contract<mp::inc<assume_number<C>>>;

  template<class C = identity>
  using dec = try_contract<mp::dec<assume_number<C>>>;

  template<class C = identity>
  using equal = try_contract<mp::equal<assume_number<C>>>;

  template<class C = identity>
  using not_equal = try_contract<mp::not_equal<assume_number<C>>>;

  template<class C = identity>
  using less = try_contract<mp::less<assume_number<C>>>;

  template<class C = identity>
  using less_equal = try_contract<mp::less_equal<assume_number<C>>>;

  template<class C = identity>
  using greater = try_contract<mp::greater<assume_number<C>>>;

  template<class C = identity>
  using greater_equal = try_contract<mp::greater_equal<assume_number<C>>>;


  template<class N, class C = identity>
  using equal_to = contract<
    mp::push_front<N,
      mp::try_<mp::equal<assume_number<C>>>>>;

  template<class N, class C = identity>
  using not_equal_to = contract<
    mp::push_front<N,
      mp::try_<mp::not_equal<assume_number<C>>>>>;

  template<class N, class C = identity>
  using less_than = contract<
    mp::push_back<N,
      mp::try_<mp::less<assume_number<C>>>>>;

  template<class N, class C = identity>
  using less_equal_than = contract<
    mp::push_back<N,
      mp::try_<mp::less_equal<assume_number<C>>>>>;

  template<class N, class C = identity>
  using greater_than = contract<
    mp::push_back<N,
      mp::try_<mp::greater<assume_number<C>>>>>;

  template<class N, class C = identity>
  using greater_equal_than = contract<
    mp::push_back<N,
      mp::try_<mp::greater_equal<assume_number<C>>>>>;


  template<int_ n, class C = identity>
  using equal_to_c = equal_to<number<n>, C>;

  template<int_ n, class C = identity>
  using not_equal_to_c = not_equal_to<number<n>, C>;

  template<int_ n, class C = identity>
  using less_than_c = less_than<number<n>, C>;

  template<int_ n, class C = identity>
  using less_equal_than_c = less_equal_than<number<n>, C>;

  template<int_ n, class C = identity>
  using greater_than_c = greater_than<number<n>, C>;

  template<int_ n, class C = identity>
  using greater_equal_than_c = greater_equal_than<number<n>, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, or_<C>>
  {
    using type = smp::or_<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, and_<C>>
  {
    using type = smp::and_<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, left_or<C>>
  {
    using type = smp::left_or<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, left_and<C>>
  {
    using type = smp::left_and<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, add<C>>
  {
    using type = smp::add<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, left_add<C>>
  {
    using type = smp::left_add<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, sub<C>>
  {
    using type = smp::sub<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, lshift<C>>
  {
    using type = smp::lshift<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, rshift<C>>
  {
    using type = smp::rshift<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, mul<C>>
  {
    using type = smp::mul<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, left_mul<C>>
  {
    using type = smp::left_mul<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, div<C>>
  {
    using type = smp::div<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, mod<C>>
  {
    using type = smp::mod<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, xor_<C>>
  {
    using type = smp::xor_<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, left_xor<C>>
  {
    using type = smp::left_xor<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, bit_and<C>>
  {
    using type = smp::bit_and<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, left_bit_and<C>>
  {
    using type = smp::left_bit_and<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, bit_or<C>>
  {
    using type = smp::bit_or<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, left_bit_or<C>>
  {
    using type = smp::left_bit_or<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, neg<C>>
  {
    using type = smp::neg<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unary_plus<C>>
  {
    using type = smp::unary_plus<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, not_<C>>
  {
    using type = smp::not_<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, bit_not<C>>
  {
    using type = smp::bit_not<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, inc<C>>
  {
    using type = smp::inc<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, dec<C>>
  {
    using type = smp::dec<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, equal<C>>
  {
    using type = smp::equal<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, not_equal<C>>
  {
    using type = smp::not_equal<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, less<C>>
  {
    using type = smp::less<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, less_equal<C>>
  {
    using type = smp::less_equal<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, greater<C>>
  {
    using type = smp::greater<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, greater_equal<C>>
  {
    using type = smp::greater_equal<sfinae<C>>;
  };


  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, or_);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, and_);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, left_or);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, left_and);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, add0);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, left_add0);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, sub0);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, lshift0);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, rshift0);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, mul0);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, mul1);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, left_mul0);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, left_mul1);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, div0);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, div1);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, mod0);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, mod1);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, xor0);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, left_xor0);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, bit_and0);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, left_bit_and0);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, bit_or0);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, left_bit_or0);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::number, not_);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::number, inc);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::number, dec);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::number, neg);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::number, unary_plus);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::number, bit_not);
  // JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::binary_number, equal);
  // JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::binary_number, not_equal);
  // JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::binary_number, less);
  // JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::binary_number, less_equal);
  // JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::binary_number, greater);
  // JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::binary_number, greater_equal);
}

#undef JLN_smp_op_without_zero
#undef JLN_smp_op_without_zero_and_with_value
/// \endcond
namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a predicate holds for at least some element of a \sequence.
  /// \treturn \bool
  /// \see all_of, none_of
  template<class Pred, class C = identity>
  using any_of = none_of<Pred, not_<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using any_of = unpack<L, mp::any_of<Pred, C>>;
  }
} // namespace jln::mp
namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using any_of = none_of<Pred, not_<C>>;
}
namespace jln::mp
{
  /// \ingroup search

  /// Extract the first elements of a \sequence that does not satisfy a \predicate.
  /// \pre \c Pred::f<x> must return a boolean, 1 or 0
  /// When an element satisfy the predicate,
  /// call \c TC with it and those before it.
  /// Otherwise \c FC is called on the whole sequence.
  /// \treturn \sequence
  /// \see take_front, take_back, take_until_xs
  /// \see drop_until, drop_until_xs
  /// \see search, partial_search
  template<class Pred, class TC = listify, class FC = TC>
  struct take_until
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  /// Extract the first elements of a \sequence that does not satisfy a \predicate.
  /// When an element satisfy the predicate,
  /// call \c TC with it and those before it + \c ExtendedByN.
  /// Otherwise \c FC is called on the whole sequence.
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct take_until_extended_by_n_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_until_extended_by_n = take_until_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_until = take_until_extended_by_n_c<1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_until = unpack<L, mp::take_until<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_inclusive_until = unpack<L, mp::take_until_extended_by_n_c<1, Pred, TC, FC>>;

    template<class ExtendedByN, class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_until_extended_by_n
      = unpack<L, mp::take_until_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>>;

    template<std::size_t ExtendedByN,
             class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_until_extended_by_n_c
      = unpack<L, mp::take_until_extended_by_n_c<ExtendedByN, Pred, TC, FC>>;
  }
}
namespace jln::mp
{
  /// \ingroup search

  /// Extracts the first elements of a \sequence that does not satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see take_front, take_back, take_until, partial_take_until_xs
  /// \see drop_until, drop_until_xs
  /// \see search
  template<class Pred, class TC = listify, class FC = TC>
  struct take_until_xs
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  /// Extracts the first elements of a \sequence that does not satisfy a \predicate.
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct take_until_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_until_extended_by_n_xs = take_until_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_until_xs = take_until_extended_by_n_xs_c<1, Pred, TC, FC>;

  /// Same as \c take_until_extended_by_n_xs_c, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_until, drop_until_xs
  /// \see take_until, take_until_xs
  /// \see search, partial_search
  template<int_ OffsetEnd, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct partial_take_until_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::drop_until_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
        JLN_MP_TRACE_F(Pred), xs...
      >
    >::template f<ExtendedByN, TC, FC, xs...>;
  };

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_until_xs =
    partial_take_until_extended_by_n_xs_c<OffsetEnd::value, 0, Pred, TC, FC>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_until_xs_c =
    partial_take_until_extended_by_n_xs_c<OffsetEnd, 0, Pred, TC, FC>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_take_until_extended_by_n_xs =
    partial_take_until_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>;

  template<std::size_t OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_inclusive_until_xs_c =
    partial_take_until_extended_by_n_xs_c<OffsetEnd, 1, Pred, TC, FC>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_inclusive_until_xs =
    partial_take_until_extended_by_n_xs_c<OffsetEnd::value, 1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using take_until_xs = unpack<L, mp::take_until_xs<Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred, class TC = mp::listify, class FC = TC>
    using take_until_extended_by_n_xs = unpack<L,
      mp::take_until_extended_by_n_xs<ExtendedByN, Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = mp::listify, class FC = TC>
    using take_until_extended_by_n_xs_c = unpack<L,
      mp::take_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_take_until_xs = unpack<L,
      mp::partial_take_until_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_take_until_xs_c = unpack<L,
      mp::partial_take_until_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using take_inclusive_until_xs = unpack<L, mp::take_inclusive_until_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = TC>
    using partial_take_inclusive_until_xs = unpack<L,
      mp::partial_take_inclusive_until_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred,
             class TC = mp::listify, class FC = TC>
    using partial_take_inclusive_until_xs_c = unpack<L,
      mp::partial_take_inclusive_until_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class ExtendedByN, class Pred,
             class TC = listify, class FC = TC>
    using partial_take_until_extended_by_n_xs = unpack<L,
      mp::partial_take_until_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, std::size_t ExtendedByN, class Pred,
             class TC = listify, class FC = TC>
    using partial_take_until_extended_by_n_xs_c = unpack<L,
      mp::partial_take_until_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>>;
  }
}
namespace jln::mp
{
  /// \ingroup search

  /// Find the \sequence before a sub-\sequence.
  /// Calls \c TC with all the elements before the sub-\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, search_before
  template<class Seq, class TC = listify, class FC = clear<TC>>
  struct before
  {};

  template<class... Ts, class TC, class FC>
  struct before<list<Ts...>, TC, FC>
  : partial_take_until_xs_c<-int_{sizeof...(Ts)},
                            starts_with<list<Ts...>>,
                            TC, FC>
  {};

  namespace emp
  {
    template<class L, class Seq, class TC = mp::listify, class FC = mp::clear<TC>>
    using before = unpack<L, mp::before<Seq, TC, FC>>;
  }

  /// \cond
  template<class T, class TC, class FC>
  struct before<list<T>, TC, FC>
  : take_until<is<T>, TC, FC>
  {};

  template<class TC, class FC>
  struct before<list<>, TC, FC>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS_0(xs, TC);
  };
  /// \endcond
}
namespace jln::mp::smp
{
  template<class Seq, class TC = listify, class FC = clear<TC>>
  using before = typename mp::conditional_c<detail::_is_list<Seq>::type::value>
    ::template f<contract<mp::before<Seq, subcontract<TC>, subcontract<FC>>>, bad_contract>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Seq, class TC, class FC>
  struct _sfinae<sfinae, before<Seq, TC, FC>>
  {
    using type = smp::before<Seq, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<std::size_t n, class SubC1, class SubC2, class C>
    struct before_after_defer_i;
  }
  /// \endcond

  /// \ingroup search

  /// Find the \sequence before_after a sub-\sequence.
  /// Calls \c TC with all the elements before_after the sub-\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, search_before
  template<
    class Seq,
    class SubC1 = listify, class SubC2 = SubC1,
    class TC = listify, class FC = clear<TC>>
  struct before_after_with
  {};

  template<class Seq, class TC = listify, class FC = clear<TC>>
  using before_after = before_after_with<Seq, listify, listify, TC, FC>;

  template<class... Ts, class SubC1, class SubC2, class TC, class FC>
  struct before_after_with<list<Ts...>, SubC1, SubC2, TC, FC>
  : invoke_twice<index_if_xs<starts_with<list<Ts...>>,
                             detail::before_after_defer_i<sizeof...(Ts), SubC1, SubC2, TC>,
                             mp::always<FC>>>
  {};

  namespace emp
  {
    template<class L, class Seq, class TC = mp::listify, class FC = mp::clear<TC>>
    using before_after = unpack<L, mp::before_after<Seq, TC, FC>>;

    template<class L, class Seq,
             class SubC1 = mp::listify, class SubC2 = SubC1,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using before_after_with = unpack<L, mp::before_after_with<Seq, SubC1, SubC2, TC, FC>>;
  }

  /// \cond
  template<class T, class SubC1, class SubC2, class TC, class FC>
  struct before_after_with<list<T>, SubC1, SubC2, TC, FC>
  : invoke_twice<index_if<is<T>,
                          detail::before_after_defer_i<1, SubC1, SubC2, TC>,
                          mp::always<FC>>>
  {};

  template<class SubC1, class SubC2, class TC, class FC>
  struct before_after_with<list<>, SubC1, SubC2, TC, FC>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(TC,
      JLN_MP_DCALL_TRACE_XS_0(xs, SubC1),
      JLN_MP_DCALL_TRACE_XS(xs, SubC2, xs...)
    );
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<std::size_t n, class SubC1, class SubC2, class C>
  struct before_after_defer_i
  {
    template<class I>
    using f = tee<take_front<I, SubC1>, drop_front_c<I::value + n, SubC2>, C>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class Seq, class SubC1 = listify, class SubC2 = SubC1,
           class TC = listify, class FC = clear<TC>>
  using before_after_with = typename mp::conditional_c<detail::_is_list<Seq>::type::value>
    ::template f<
      contract<mp::before_after_with<Seq, subcontract<SubC1>, subcontract<SubC2>,
               assume_binary<TC>, subcontract<FC>>>,
      bad_contract
    >;

  template<class Seq, class TC = listify, class FC = clear<TC>>
  using before_after = before_after_with<Seq, listify, listify, TC, FC>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Seq, class SubC1, class SubC2, class TC, class FC>
  struct _sfinae<sfinae, before_after_with<Seq, SubC1, SubC2, TC, FC>>
  {
    using type = smp::before_after_with<Seq, sfinae<SubC1>, sfinae<SubC2>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class, unsigned>
    struct _cartesian;
  }
  /// \endcond

  /// \ingroup group

  /// Computes the cartesian product of \lists.
  /// \pre `emp::is_list<seqs> && ...`
  /// \post `sizeof...(result) == (emp::size<seqs> * ...)` if `sizeof...(xs) != 0` else `0`
  /// \semantics
  ///   \code
  ///   cartesian<listify>::f<
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
  struct cartesian
  {
    template<class... seqs>
    using f = typename detail::_cartesian<C, detail::min(2, sizeof...(seqs))>
      ::template f<seqs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using cartesian = unpack<L, cartesian<C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class, class>
  struct _product;

  template<class... xs, class... ys>
  struct _product<list<xs...>, list<ys...>>
  {
    using type = list<list<xs..., ys>...>;
  };

  template<class... ys>
  struct _product<list<>, list<ys...>>
  {
    using type = list<>;
  };

  template<class>
  struct _product1;

  template<class... xs>
  struct _product1<list<xs...>>
  {
    using type = list<list<xs>...>;
  };

  template<class C>
  struct _cartesian<C, 0>
  {
    template<class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  template<>
  struct _cartesian<listify, 0>
  {
    template<class...>
    using f = list<>;
  };

  template<class C>
  struct _cartesian<C, 1>
  {
    template<class seq>
    using f = JLN_MP_CALL_TRACE(C, typename _product1<seq>::type);
  };

  template<>
  struct _cartesian<listify, 1>
  {
    template<class seq>
    using f = typename _product1<seq>::type;
  };

  template<class, class>
  struct _cartesian_impl;

  template<class... seqs, class seq>
  struct _cartesian_impl<list<seqs...>, seq>
  {
    using type = typename join<>
      ::f<typename _product<seqs, seq>::type...>;
  };

  template<class C, unsigned n>
  struct _cartesian
  {
    template<class seq, class... seqs>
    using f = typename fold_left<lift_t<detail::_cartesian_impl>, unpack<C>>
      ::template f<typename _product1<seq>::type, seqs...>;
  };

  template<unsigned n>
  struct _cartesian<listify, n>
  {
    template<class seq, class... seqs>
    using f = typename fold_left<lift_t<detail::_cartesian_impl>>
      ::template f<typename _product1<seq>::type, seqs...>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = listify>
  using cartesian = test_contract<
    mp::all_of<mp::is_list<>>,
    mp::cartesian<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, cartesian<C>>
  {
    using type = smp::cartesian<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct _group;
  }
  /// \endcond

  /// \ingroup group

  /// Groups adjacent elements that respect a predicate.
  /// \semantics
  ///   \code
  ///   group_by<same<>>::f<void, void, int, void>
  ///   == list<
  ///     list<void, void>,
  ///     list<int>,
  ///     list<void>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  template<class Cmp, class C = listify>
  struct group_by
  {
    template<class... xs>
    using f = typename detail::_group<sizeof...(xs) != 0>
      ::template f<C, Cmp, xs...>;
  };

  template<class C = listify>
  using group = group_by<same<>, C>;

  namespace emp
  {
    template<class L, class Cmp, class C = mp::listify>
    using group_by = unpack<L, mp::group_by<Cmp, C>>;

    template<class L, class C = mp::listify>
    using group = unpack<L, mp::group<C>>;
  }
}


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct fold_right_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Folds right over a list using a binary predicate.
  /// fold_right consideres the first element in the input pack as the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<xs[1], ..., F::f<xs[n-2], F::f<xs[n-1], xs[0]>>>
  ///   \endcode
  /// \treturn \value
  /// \see fold_left, fold_tree, reverse_fold, fold_balanced_tree
  template<class F, class C = identity>
  struct fold_right
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::fold_right_impl<
        int(sizeof...(xs)) - 1
      >::template f<JLN_MP_TRACE_F(F)::template f, xs...>
    );
  };

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using fold_right = unpack<L,
      mp::push_front<state, mp::fold_right<F, C>>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<int n>
  struct fold_right_impl : fold_right_impl<
      n < 8 ? 4
    : n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_FOLD_RIGHT_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                               \
  struct fold_right_impl<n>                                \
  {                                                        \
    template<template<class...> class F, class state,      \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),              \
      class... xs>                                         \
    using f = mp_xs(F<, JLN_MP_COMMA, JLN_MP_NIL)          \
      typename fold_right_impl<                            \
        sizeof...(xs)                                      \
      >::template f<F, state, xs...>                       \
    mp_dup(>, JLN_MP_NIL);                                 \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_FOLD_RIGHT_SELECT)

#undef JLN_MP_FOLD_RIGHT_SELECT

#define JLN_MP_FOLD_RIGHT_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                               \
  struct fold_right_impl<n>                                \
  {                                                        \
    template<template<class...> class F, class state,      \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA)>              \
    using f = mp_xs(F<, JLN_MP_COMMA, JLN_MP_NIL)          \
      state mp_dup(>, JLN_MP_NIL);                         \
  };

  JLN_MP_GEN_XS_1_TO_4(JLN_MP_FOLD_RIGHT_SELECT)

#undef JLN_MP_FOLD_RIGHT_SELECT

  template<>
  struct fold_right_impl<0>
  {
    template<template<class...> class, class state>
    using f = state;
  };

  template<>
  struct fold_right_impl<-1>
  {};
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template <bool>
    struct _split;

    inline constexpr int_ split_keep = 0;
    inline constexpr int_ split_after = 1;
    inline constexpr int_ split_before = 2;
    inline constexpr int_ split_skip = 3;
    // inline constexpr int_ split_na = 4;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a \sequence into multiple \lists at every point that satisfy a predicate.
  /// \semantics
  ///   \code
  ///   split_if<is<_0>>::f<_0, _1, _2, _0, _3>
  ///   == list<
  ///     list<>,
  ///     list<_1, _2>,
  ///     list<_3>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see split_before_if, split_after_if
  template<class Pred = identity, class C = listify>
  struct split_if
  {
    template <class... xs>
    using f = typename detail::_split<sizeof...(xs) != 0>
      ::template f<detail::split_skip, C, JLN_MP_TRACE_F(Pred), xs...>;
  };

  template<class x, class C = listify>
  using split = split_if<is<x>, C>;

  namespace emp
  {
    template<class L, class Pred = mp::identity, class C = mp::listify>
    using split_if = unpack<L, mp::split_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using split = unpack<L, mp::split<x, C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template <class x, class state>
  struct split_state;

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_keep>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<x, xs...>, Ls...>;
  };

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_after>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<x>, list<xs...>, Ls...>;
  };

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_before>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<>, list<x, xs...>, Ls...>;
  };

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_skip>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<>, list<xs...>, Ls...>;
  };

  template<>
  struct _split<true>
  {
    template<int_ policy, class C, class Pred, class... xs>
    using f = typename fold_right<lift_t<split_state>, optimize_useless_unpack_t<unpack<C>>>
      ::template f<list<list<>>,
                   list<number<Pred::template f<xs>::value
                     ? policy : split_keep>, xs>...
      >;
  };

  template<>
  struct _split<false>
  {
    template<int_, class C, class>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<class x, class C>
  struct _group_insert_x
  {
    template<class seq, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(
      xs, C,
      typename detail::_unpack<seq>::template f<push_front<x>>,
      xs...
    );
  };

  template<class x, class F, class C>
  struct _group_insert_x<x, transform<unpack<F>, C>>
  {
    template<class seq, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(
      xs, C,
      typename detail::_unpack<seq>::template f<push_front<x, F>>,
      typename detail::_unpack<xs>::template f<F>...
    );
  };

  template<class...>
  struct _group_impl;

  template<class C, class Cmp, class x, class... xs, class... ys>
  struct _group_impl<C, Cmp, x, list<ys...>, xs...>
  {
    using type = typename fold_right<lift_t<split_state>, unpack<_group_insert_x<x, C>>>
      ::template f<list<list<>>,
                   list<number<Cmp::template f<ys, xs>::value
                     ? split_keep : split_before>, xs>...
      >;
  };

  template<class... ys>
  struct _smp_group_impl
  {
    template<class C, class Cmp, class x, class... xs>
    using f = typename fold_right<lift_t<split_state>, unpack<_group_insert_x<x, C>>>
      ::template f<list<list<>>,
                   list<number<Cmp::template f<ys, xs>::value
                     ? split_keep : split_before>, xs>...
      >;
  };

  template<class C, class Cmp, class TC, class FC, class x, class... xs, class... ys>
  struct _group_impl<C, try_<Cmp, TC, FC>, x, list<ys...>, xs...>
  {
    using type = typename try_<_smp_group_impl<ys...>>
      ::template f<C, try_<Cmp, TC, FC>, x, xs...>;
  };

  template<>
  struct _group<true>
  {
    template<class C, class Cmp, class x, class... xs>
    using f = typename _group_impl<
      C, Cmp, x,
      typename take_front_c<sizeof...(xs)>::template f<x, xs...>,
      xs...
    >::type;
  };

  template<>
  struct _group<false>
  {
    template<class C, class>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup group

  /// Groups adjacent elements by adjacent keys.
  /// \semantics
  /// \pre `emp::is_list<Keys>` == `true`
  /// \pre `emp::size<Keys>` == `sizeof...(xs)`
  ///   \code
  ///   collapse<emp::numbers<1, 1, 0, 0, 0, 1, 2, 2>>
  ///   ::f<int, int, int, int, int, int, int, int>
  ///   ==
  ///   list<
  ///     list<int, int>,
  ///     list<int, int, int>,
  ///     list<int>,
  ///     list<int, int>
  ///   >
  ///   \endcode
  /// \note \c collapse<list<xs...>>::f<xs...> == \c group<>::f<xs...>
  /// \treturn \sequence
  template<class Keys, class C = listify>
  struct collapse
  {};

#ifdef JLN_MP_DOXYGENATING
  template<class... keys, class C>
  struct collapse<list<keys...>, C>
  {
    template<class... xs>
    using f;
  };
#endif

  template<class... keys>
  using collapse_for = collapse<list<keys...>>;

  template<bool... keys>
  using collapse_for_c = collapse<list<number<keys>...>>;

  namespace emp
  {
    template<class L, class Keys, class C = mp::listify>
    using collapse = unpack<L, mp::collapse<Keys, C>>;

    template<class L, class... keys>
    using collapse_for = unpack<L, mp::collapse<mp::list<keys...>>>;

    template<class L, bool... keys>
    using collapse_for_c = unpack<L, mp::collapse<mp::list<number<keys>...>>>;
  }


  /// \cond
  namespace detail
  {
    template<class...>
    struct make_collapse;
  }

  template<class C>
  struct collapse<list<>, C>
  {
    template<class... xs>
    using f = typename detail::_group<sizeof...(xs) != 0>
      ::template f<C, list<>>;
  };

  template<class key, class... keys, class C>
  struct collapse<list<key, keys...>, C>
  : detail::make_collapse<
      typename take_front_c<sizeof...(keys)>::template f<key, keys...>,
      keys...
    >::template f<C>
  {};
  /// \endcond
}


namespace jln::mp::detail
{
  template<class C, class... ns>
  struct _collapse
  {
    template<class x, class... xs>
    using f = typename fold_right<lift_t<split_state>, unpack<_group_insert_x<x, C>>>
      ::template f<list<list<>>, list<ns, xs>...>;
  };

  template<class... xs, class... ys>
  struct make_collapse<list<ys...>, xs...>
  {
    template<class C>
    using f = _collapse<
      C, number<std::is_same<ys, xs>::value ? split_keep : split_before>...
    >;
  };
}
namespace jln::mp::smp
{
  template<class Keys, class C = listify>
  using collapse = try_contract<mp::collapse<Keys, assume_lists<C>>>;

  template<class... Keys>
  using collapse_for = collapse<mp::list<Keys...>>;

  template<bool... keys>
  using collapse_for_c = collapse<mp::list<number<keys>...>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Keys, class C>
  struct _sfinae<sfinae, collapse<Keys, C>>
  {
    using type = smp::collapse<Keys, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_ n>
    struct _repeat;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Returns a \sequence that contains a \number of copies of the same \sequence.
  /// \pre N >= 0
  /// \treturn \sequence
  template<unsigned N, class C = listify>
  struct repeat_c
  {
    template<class... xs>
    using f = emp::make_int_sequence_v_c<N,
      typename detail::_repeat<detail::min(sizeof...(xs), 2)>
        ::template impl<C, xs...>>;
  };

  template<class N, class C = listify>
  using repeat = repeat_c<N::value, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using repeat = unpack<L, mp::repeat<n, C>>;

    template<class L, int_ n, class C = mp::listify>
    using repeat_c = unpack<L, mp::repeat_c<n, C>>;
  }
}


// _first

/// \cond
namespace jln::mp::detail
{
  template<>
  struct _repeat<0>
  {
    template<class C>
    struct impl
    {
      template<int_...>
      using f = JLN_MP_CALL_TRACE_0_ARG(C);
    };
  };

  template<>
  struct _repeat<1>
  {
    template<class C, class x>
    struct impl
    {
      template<int_... ns>
      using f = JLN_MP_DCALL_TRACE_XS(ns, C, _first<x, decltype(ns)>...);
    };
  };

  template<>
  struct _repeat<2>
  {
    template<class C, class... xs>
    struct impl
    {
      template<int_... ns>
      using f = JLN_MP_DCALL_TRACE_XS(ns, join<C>, _first<list<xs...>, decltype(ns)>...);
    };
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup group

  /// Computes all possible combinations (with repetition) from the elements in a \sequence.
  /// \treturn \sequence of \list
  template<class C = listify>
  struct combine
  {
    template<class... xs>
    using f = typename repeat_c<sizeof...(xs), cartesian<C>>
      ::template f<list<xs...>>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using combine = unpack<L, mp::combine<C>>;
  }
}
namespace jln::mp::smp
{
  template<class C = listify>
  using combine = contract<mp::combine<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, combine<C>>
  {
    using type = smp::combine<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template <class C, class... Fs>
    struct _each;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions each taking the parameter corresponding to its position.
  /// \treturn \value
  /// \see tee, partial
#ifdef JLN_MP_DOXYGENATING
  template <class... Fs, class C>
  struct each
  {
    template<class... xs>
    using f = C::f<Fs::f<xs>...>;
  };
#else
  template <class... Fs>
  struct each
  : rotate_c<-1, lift<detail::_each>>
  ::template f<Fs...>
  {};
#endif

  /// \cond
  template <class C>
  struct each<C> : detail::_each<C>
  {};

  template <class F, class C>
  struct each<F, C> : detail::_each<C, F>
  {};

  template <class F0, class F1, class C>
  struct each<F0, F1, C> : detail::_each<C, F0, F1>
  {};

  template <class F0, class F1, class F2, class C>
  struct each<F0, F1, F2, C> : detail::_each<C, F0, F1, F2>
  {};
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template <class C, class... Fs>
  struct _each
  {
    template <class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, JLN_MP_DCALL_TRACE_XS(xs, Fs, xs)...);
  };
} // namespace jln::mp
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<int>
  struct _smp_each_select;
}
/// \endcond

namespace jln::mp::smp
{
  template <class... Fs>
  using each = typename detail::_smp_each_select<detail::min(5, sizeof...(Fs))>
    ::template f<Fs...>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, each<Fs...>>
  {
    using type = smp::each<sfinae<Fs>...>;
  };

  template<>
  struct _smp_each_select<1>
  {
    template<class C>
    using f = test_contract<size<not_<>>, subcontract<C>>;
  };

  template<>
  struct _smp_each_select<2>
  {
    template<class F, class C>
    using f = test_contract<size<is<number<1>>>, each<
      assume_unary<F>, monadic_xs<assume_unary<C>>>>;
  };

  template<>
  struct _smp_each_select<3>
  {
    template<class F0, class F1, class C>
    using f = test_contract<size<is<number<2>>>, each<
      assume_unary<F0>,
      assume_unary<F1>,
      monadic_xs<assume_binary<C>>>>;
  };

  template<>
  struct _smp_each_select<4>
  {
    template<class F0, class F1, class F2, class C>
    using f = test_contract<size<is<number<3>>>, each<
      assume_unary<F0>,
      assume_unary<F1>,
      assume_unary<F2>,
      monadic_xs<subcontract<C>>>>;
  };

  struct _smp_each
  {
    template<class C, class... Fs>
    using f = test_contract<size<is<number<sizeof...(Fs)>>>,
      _each<monadic_xs<subcontract<C>>, assume_unary<Fs>...>>;
  };

  template<>
  struct _smp_each_select<5>
  : mp::rotate_c<-1, detail::_smp_each>
  {};
}
/// \endcond
namespace jln::mp
{
  /// \ingroup algorithm

  /// comparison on the result of a function.
  /// \treturn \bool
  template<class F, class Cmp = less<>>
  using compare_with = each<F, F, Cmp>;

  namespace emp
  {
    template<class F, class x, class y, class Cmp = mp::less<>>
    using compare_with = typename Cmp::template f<
      typename F::template f<x>,
      typename F::template f<y>
    >;
  }
}
namespace jln::mp::smp
{
  template<class F, class Cmp = less<>>
  using compare_with = each<F, F, assume_binary<Cmp>>;
}
namespace jln::mp
{
  /// \ingroup filter

  /// Removes elements that have a corresponding element in selectors to 0.
  /// \pre `emp::unpack<Selectors, listify> == Selectors`
  /// \pre all Selectors::value are 1, 0 or a bool type
  /// \pre `sizeof...(xs) == emp::size<Selectors>`
  /// \semantics
  ///   \code
  ///   compress<numbers<1,0,1,0,1,1>>
  ///                ::f<a,b,c,d,e,f>
  ///            == list<a,  c,  e,f>
  ///   \endcode
  /// \treturn \sequence
  template<class Selectors, class C = listify>
  struct compress
  {};

  template<class... selectors, class C>
  struct compress<list<selectors...>, C>
  {
    template<class... xs>
    using f = typename join<C>::template f<
      JLN_MP_MSVC_FIX_CALL_T((wrap_in_list_c<selectors::value>), xs)...
    >;
  };

  template<class... Selectors>
  using compress_for = compress<list<Selectors...>>;

  template<bool... selectors>
  using compress_for_c = compress<list<number<selectors>...>>;

  namespace emp
  {
    template<class L, class Selectors, class C = mp::listify>
    using compress = unpack<L, mp::compress<Selectors, C>>;

    template<class L, class... Selectors>
    using compress_for = unpack<L, mp::compress<mp::list<Selectors...>>>;

    template<class L, bool... selectors>
    using compress_for_c = unpack<L, mp::compress<mp::list<number<selectors>...>>>;
  }
}
namespace jln::mp::detail
{
  template<class Selectors, class = void>
  struct smp_compress_select;
}

namespace jln::mp::smp
{
  template<class Selectors, class C = listify>
  using compress = typename detail::smp_compress_select<Selectors>
    ::template f<C>;

  template<class... Selectors>
  using compress_for = compress<mp::list<Selectors...>>;

  template<bool... selectors>
  using compress_for_c = test_contract<
    mp::size<mp::is<mp::number<sizeof...(selectors)>>>,
    mp::compress<mp::list<mp::number<selectors>...>>
  >;
}

/// \cond
namespace jln::mp::detail
{
  template<class Selectors, class>
  struct smp_compress_select
  {
    template<class C>
    using f = bad_contract;
  };

  template<class... Selectors>
  struct smp_compress_select<
    list<Selectors...>,
    std::void_t<decltype(bool{Selectors::value})...>
  >
  {
    template<class C>
    using f = test_contract<
      size<is<number<sizeof...(Selectors)>>>,
      compress<list<Selectors...>, subcontract<C>>
    >;
  };

  template<template<class> class sfinae, class Selectors, class C>
  struct _sfinae<sfinae, compress<Selectors, C>>
  {
    using type = smp::compress<Selectors, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup algorithm

  /// Perform a logical AND on the sequence of value.
  /// Conjunction is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(Xi::value) == false`, then instantiating
  /// `conjunction<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `xs[j]::value` for j > i
  /// \treturn \bool
  /// \see disjunction, drop_while, take_while
  template<class C = identity>
  using conjunction = all_of<to_bool<>, C>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using conjunction = unpack<L, mp::conjunction<C>>;
  }
}
namespace jln::mp::smp
{
  template<class C = identity>
  using conjunction = all_of<to_bool<>, C>;
}
namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a \value is contained in a \list.
  /// \treturn \bool
  template<class x, class C = identity>
  using contains = any_of<is<x>, C>;

  namespace emp
  {
    template<class L, class x, class C = mp::identity>
    using contains = unpack<L, mp::contains<x, C>>;
  }
}
namespace jln::mp::smp
{
  template<class x, class C = identity>
  using contains = contract<mp::any_of<mp::is<x>, assume_positive_number<C>>>;
}
namespace jln::mp::smp
{
  template<class F, class C = listify>
  using transform = contract<mp::transform<
    assume_unary<F>, mp::monadic_xs<subcontract<C>>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, transform<F, C>>
  {
    using type = smp::transform<sfinae<F>, sfinae<C>>;
  };

  template<>
  struct optimize_useless_transform_unpack_impl<contract<identity>>
  {
    template<class C>
    using f = optimize_useless_transform_unpack_t<contract<C>>;
  };

  template<class F, class C>
  struct optimize_useless_transform_unpack<contract<transform<F, C>>>
  {
    using type = typename optimize_useless_transform_unpack_impl<optimize_useless_unpack_t<F>>
      ::template f<C>;
  };

  template<class F, class C>
  struct optimize_useless_transform_unpack<contract<transform<F, mp::monadic_xs<C>>>>
  {
    using type =
      typename optimize_useless_transform_unpack_impl<optimize_useless_unpack_t<F>>
      ::template f<
        typename conditional_c<std::is_same_v<
          optimize_useless_transform_unpack_t<transform<F>>,
          transform<F>
        >>
        ::template f<mp::monadic_xs<C>, C>
      >;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = listify>
  using join = test_contract<
    mp::all_of<mp::is_list<>>,
    mp::join<subcontract<C>>>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, join<C>>
  {
    using type = smp::join<sfinae<C>>;
  };
} // namespace jln::mp::detail
/// \endcond
namespace jln::mp
{
  /// \ingroup utility

  /// \treturn \bool
  template <class T, class C = identity>
  using is_not = is<T, not_<C>>;
} // namespace jln::mp
namespace jln::mp::smp
{
  template<class x, class C = identity>
  using is_not = try_contract<mp::is<x, mp::not_<assume_positive_number<C>>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, is<x, not_<C>>>
  {
    using type = smp::is_not<x, sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT2(argument_category::unary, is_not);
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  struct _smp_tee;
}
/// \endcond

namespace jln::mp::smp
{
  template <class... Fs>
  using tee = typename mp::conditional_c<sizeof...(Fs) == 0>
    ::template f<
      na,
      rotate_c<-1, detail::_smp_tee>>
    ::template f<subcontract<Fs>...>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, tee<Fs...>>
  {
    using type = smp::tee<sfinae<Fs>...>;
  };

  struct _smp_tee
  {
    template<class C, class... Fs>
    using f = contract<_tee<monadic_xs<C>, Fs...>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<template<class...> class F, class C = identity>
  using lift = try_contract<mp::lift<F, assume_unary<C>>>;

  template<template<class...> class F, class C = identity>
  using lift_t = try_contract<mp::lift_t<F, assume_unary<C>>>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, template<class...> class F, class C>
  struct _sfinae<sfinae, lift_t<F, C>>
  {
    using type = smp::lift_t<F, sfinae<C>>;
  };

  template<template<class> class sfinae, template<class...> class F, class C>
  struct _sfinae<sfinae, lift<F, C>>
  {
    using type = smp::lift<F, sfinae<C>>;
  };


  JLN_MP_MAKE_EXPECTED_ARGUMENT(argument_category::binary, (class C), (lift<std::is_same, C>));
  JLN_MP_MAKE_EXPECTED_ARGUMENT(argument_category::binary, (class C), (lift_t<std::is_same, C>));
}
/// \endcond
namespace jln::mp::smp
{
  template<class Pred>
  using wrap_in_list_if = try_contract<mp::wrap_in_list_if<
    concepts::strong_predicate_or<assume_unary_or_more<Pred>, mp::violation>>>;

  template<class Pred>
  using wrap_in_list_if_not = try_contract<mp::wrap_in_list_if_not<
    concepts::strong_predicate_or<assume_unary_or_more<Pred>, mp::violation>>>;

  template<bool b>
  using wrap_in_list_c = contract<mp::wrap_in_list_c<b>>;
}

JLN_MP_MAKE_REGULAR_SMP1_P(wrap_in_list, (N), smp::wrap_in_list_c<N::value>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred>
  struct _sfinae<sfinae, _wrap_in_list_if<Pred>>
  {
    using type = smp::wrap_in_list_if<sfinae<Pred>>;
  };

  template<template<class> class sfinae, class Pred>
  struct _sfinae<sfinae, _wrap_in_list_if_not<Pred>>
  {
    using type = smp::wrap_in_list_if_not<sfinae<Pred>>;
  };

  template<template<class> class sfinae, bool b>
  struct _sfinae<sfinae, wrap_in_list_c<b>>
  {
    using type = smp::wrap_in_list_c<b>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup filter

  /// Removes all elements that satisfy a predicate.
  /// \treturn \sequence
  template<class Pred, class C = listify>
  using remove_if = transform<wrap_in_list_if_not<Pred>, join<C>>;

  /// Removes all occurence of a \value.
  /// \treturn \sequence
  template<class T, class C = listify>
  using remove = remove_if<is<T>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using remove_if = unpack<L, mp::remove_if<Pred, C>>;

    template<class L, class T, class C = mp::listify>
    using remove = unpack<L, mp::remove<T, C>>;
  }
}
namespace jln::mp
{
  /// \ingroup filter

  /// Copies all elements that satisfy a predicate.
  /// \treturn \sequence
  template<class Pred, class C = listify>
  using copy_if = remove_if<tee<Pred, not_<>>, C>;

  /// Copies all occurence of a \value.
  /// \treturn \sequence
  template<class x, class C = listify>
  using copy = remove_if<is<x, not_<>>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using copy_if = unpack<L, mp::copy_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using copy = unpack<L, mp::copy<x, C>>;
  }
}
namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using copy_if = contract<mp::transform<
    subcontract<wrap_in_list_if<assume_unary_barrier<Pred>>>,
    mp::monadic_xs<mp::join<subcontract<C>>>>>;

  template<class x, class C = listify>
  using copy = contract<mp::copy<x, subcontract<C>>>;
}
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct _remove_unique;

    template<bool>
    struct _copy_unique;

    template<class Cmp, class C>
    struct mk_remove_unique;

    template<class Cmp, class C>
    struct mk_copy_unique;
  }
  /// \endcond

  /// \ingroup filter

  /// Remove unique elements from a \sequence.
  /// \treturn \sequence
  /// \see remove_unique_if, copy_unique, copy_unique_if
  template<class C = listify>
  struct remove_unique
  {
    template<class... xs>
    using f = typename detail::_remove_unique<sizeof...(xs) < 2>::template f<C, xs...>;
  };

  /// Remove unique elements from a \sequence.
  /// \treturn \sequence
  /// \see remove_unique, copy_unique, copy_unique_if
  template<class Cmp = lift<std::is_same>, class C = listify>
  using remove_unique_if = typename detail::mk_remove_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using remove_unique = unpack<L, remove_unique<C>>;

    template<class L, class Cmp = lift<std::is_same>, class C = mp::listify>
    using remove_unique_if = unpack<L, remove_unique_if<Cmp, C>>;
  }

  /// Copy unique elements from a \sequence.
  /// \treturn \sequence
  /// \see copy_unique_if, remove_unique, remove_unique_if
  template<class C = listify>
  struct copy_unique
  {
    template<class... xs>
    using f = typename detail::_copy_unique<sizeof...(xs) < 2>::template f<C, xs...>;
  };

  /// Copy unique elements from a \sequence.
  /// \treturn \sequence
  /// \see copy_unique, remove_unique, remove_unique_if
  template<class Cmp = lift<std::is_same>, class C = listify>
  using copy_unique_if = typename detail::mk_copy_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using copy_unique = unpack<L, copy_unique<C>>;

    template<class L, class Cmp = lift<std::is_same>, class C = mp::listify>
    using copy_unique_if = unpack<L, copy_unique_if<Cmp, C>>;
  }
}


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class Cmp, class C>
    struct mk_unique;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Returns a list of the same form as L with the duplicate elements removed.
  /// \treturn \sequence
  template<class C = listify>
  using unique = typename detail::mk_unique<lift<std::is_same>, C>::type;

  /// Returns a list of the same form as L with the duplicate elements removed.
  /// \treturn \sequence
  template<class Cmp = lift<std::is_same>, class C = listify>
  using unique_if = typename detail::mk_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using unique = unpack<L, unique<C>>;

    template<class L, class Cmp = lift<std::is_same>, class C = mp::listify>
    using unique_if = unpack<L, unique_if<Cmp, C>>;
  }
}


// std::integer_sequence

/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct inherit_item {};
  template<std::size_t i, class x>
  struct inherit_impl : inherit_item<x> {};

  template<class, class...>
  struct inherit;

  template<std::size_t... ints, class... xs>
  struct inherit<std::integer_sequence<std::size_t, ints...>, xs...>
    : inherit_impl<ints, xs>...
  {};

#if JLN_MP_MSVC_LIKE
  template<class... xs>
  struct _is_set
  {
      template <class Pack>
      static auto is_set(Pack pack) -> decltype((
          static_cast<inherit_item<xs>*>(pack),...
      ), number<1>());

      static number<0> is_set(...);

      using type = decltype(is_set(static_cast<
        inherit<std::make_index_sequence<sizeof...(xs)>, xs...>*
      >(nullptr)));
  };
#endif

  template<class L, class x, class = void>
  struct _set_push_back
  {
    using type = L;
  };

  template<class... xs, class x>
  struct _set_push_back<list<xs...>, x,
    std::enable_if_t<
#if JLN_MP_MSVC_LIKE
      // workaround for MSVC which has a broken EBO
      _is_set<xs..., x>::type::value
#else
      sizeof(inherit<std::make_index_sequence<sizeof...(xs)+1>, xs..., x>) == 1
#endif
  >>
  {
    using type = list<xs..., x>;
  };

  template<class Cmp>
  struct _set_cmp_push_back
  {
    template<class x, class... xs>
    using f = typename conditional_c<
      index_if<push_back<x, Cmp>, identity, always<number<-1>>>::template f<xs...>::value == -1
    >::template f<list<xs..., x>, list<xs...>>;
  };

  template<class Cmp, class C>
  struct mk_unique
  {
    using type = push_front<list<>, fold_left<
      unpack<_set_cmp_push_back<JLN_MP_TRACE_F(Cmp)>>,
      optimize_useless_unpack_t<unpack<C>>
    >>;
  };

  template<class C>
  struct mk_unique<lift<std::is_same>, C>
  {
    using type = push_front<list<>, fold_left<
      lift_t<_set_push_back>,
      optimize_useless_unpack_t<unpack<C>>
    >>;
  };

  template<class C>
  struct mk_unique<lift_t<std::is_same>, C>
  : mk_unique<lift<std::is_same>, C>
  {};

  template<class C>
  struct mk_unique<same<>, C>
  : mk_unique<lift<std::is_same>, C>
  {};
}
/// \endcond
// inherit / inherit_item
/// \cond
namespace jln::mp::detail
{
  template<class From, class To>
  constexpr auto is_convertible_to(From, To)
    -> decltype(To(From()), true)
  {
    return true;
  }

  constexpr bool is_convertible_to(...)
  {
    return false;
  }


  template<class C, class Inherit, class... xs>
  using remove_unique_impl = typename join<C>::template f<
    typename wrap_in_list_c<!is_convertible_to(
      static_cast<Inherit*>(nullptr),
      static_cast<detail::inherit_item<xs>*>(nullptr)
    )>
    ::template f<xs>
  ...>;

  template<>
  struct _remove_unique<false>
  {
    template<class C, class... xs>
    using f = remove_unique_impl<
      C, detail::inherit<std::make_index_sequence<sizeof...(xs)>, xs...>, xs...
    >;
  };

  template<>
  struct _remove_unique<true>
  {
    template<class C, class... xs>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };


  template<class C, class Inherit, class... xs>
  using copy_unique_impl = typename join<C>::template f<
    typename wrap_in_list_c<is_convertible_to(
      static_cast<Inherit*>(nullptr),
      static_cast<detail::inherit_item<xs>*>(nullptr)
    )>
    ::template f<xs>
  ...>;

  template<>
  struct _copy_unique<false>
  {
    template<class C, class... xs>
    using f = copy_unique_impl<
      C, detail::inherit<std::make_index_sequence<sizeof...(xs)>, xs...>, xs...
    >;
  };

  template<>
  struct _copy_unique<true>
  {
    template<class C, class... xs>
    using f = JLN_MP_CALL_TRACE(C, xs...);
  };


  template<class Indexes>
  struct remove_unique_if_impl;

  template<std::size_t... ints>
  struct remove_unique_if_impl<std::integer_sequence<std::size_t, ints...>>
  {
    template<class C, class Cmp, class... xs>
    using f = typename join<C>::template f<
      JLN_MP_MSVC_FIX_CALL((
        rotate_c<ints, pop_front<index_if<
          push_back<xs, Cmp>,
          always<wrap_in_list_c<true>>,
          always<wrap_in_list_c<false>>
        >>>
        ::template f<xs...>
      ), xs)...
    >;
  };

  template<>
  struct remove_unique_if_impl<std::integer_sequence<std::size_t>>
  {
    template<class C, class Cmp, class... xs>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  template<std::size_t i>
  struct remove_unique_if_impl<std::integer_sequence<std::size_t, i>>
  : remove_unique_if_impl<std::integer_sequence<std::size_t>>
  {};

  template<class Cmp, class C>
  struct _remove_unique_if
  {
    template<class... xs>
    using f = typename detail::remove_unique_if_impl<std::make_index_sequence<sizeof...(xs)>>
      ::template f<C, Cmp, xs...>;
  };

  template<class Cmp, class C>
  struct mk_remove_unique
  {
    using type = _remove_unique_if<Cmp, C>;
  };


  template<class Indexes>
  struct copy_unique_if_impl;

  template<std::size_t... ints>
  struct copy_unique_if_impl<std::integer_sequence<std::size_t, ints...>>
  {
    template<class C, class Cmp, class... xs>
    using f = typename join<C>::template f<
      JLN_MP_MSVC_FIX_CALL((
        rotate_c<ints, pop_front<index_if<
          push_back<xs, Cmp>,
          always<wrap_in_list_c<false>>,
          always<wrap_in_list_c<true>>
        >>>
        ::template f<xs...>
      ), xs)...
    >;
  };

  template<>
  struct copy_unique_if_impl<std::integer_sequence<std::size_t>>
  : remove_unique_if_impl<std::integer_sequence<std::size_t>>
  {};

  template<std::size_t i>
  struct copy_unique_if_impl<std::integer_sequence<std::size_t, i>>
  {
    template<class C, class Cmp, class... xs>
    using f = JLN_MP_CALL_TRACE(C, xs...);
  };

  template<class Cmp, class C>
  struct _copy_unique_if
  {
    template<class... xs>
    using f = typename detail::copy_unique_if_impl<std::make_index_sequence<sizeof...(xs)>>
      ::template f<C, Cmp, xs...>;
  };

  template<class Cmp, class C>
  struct mk_copy_unique
  {
    using type = _copy_unique_if<Cmp, C>;
  };


  template<class C>
  struct mk_remove_unique<lift<std::is_same>, C>
  {
    using type = mp::remove_unique<C>;
  };

  template<class C>
  struct mk_remove_unique<lift_t<std::is_same>, C>
  {
    using type = mp::remove_unique<C>;
  };

  template<class C>
  struct mk_remove_unique<same<>, C>
  {
    using type = mp::remove_unique<C>;
  };

  template<class C>
  struct mk_remove_unique<lift<std::is_same, not_<>>, C>
  {
    using type = mp::copy_unique<C>;
  };

  template<class C>
  struct mk_remove_unique<lift_t<std::is_same, not_<>>, C>
  {
    using type = mp::copy_unique<C>;
  };

  template<class C>
  struct mk_remove_unique<same<not_<>>, C>
  {
    using type = mp::copy_unique<C>;
  };

  template<class F, class C>
  struct mk_remove_unique<tee<F, not_<>>, C>
  : mk_copy_unique<F, C>
  {};

  template<class C>
  struct mk_copy_unique<lift<std::is_same>, C>
  {
    using type = mp::copy_unique<C>;
  };

  template<class C>
  struct mk_copy_unique<lift_t<std::is_same>, C>
  {
    using type = mp::copy_unique<C>;
  };

  template<class C>
  struct mk_copy_unique<same<>, C>
  {
    using type = mp::copy_unique<C>;
  };

  template<class C>
  struct mk_copy_unique<lift<std::is_same, not_<>>, C>
  {
    using type = mp::remove_unique<C>;
  };

  template<class C>
  struct mk_copy_unique<lift_t<std::is_same, not_<>>, C>
  {
    using type = mp::remove_unique<C>;
  };

  template<class C>
  struct mk_copy_unique<same<not_<>>, C>
  {
    using type = mp::remove_unique<C>;
  };

  template<class F, class C>
  struct mk_copy_unique<tee<F, not_<>>, C>
  : mk_remove_unique<F, C>
  {};
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct smp_mk_remove_unique;

  template<class Cmp>
  struct smp_mk_copy_unique;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = listify>
  using remove_unique = contract<mp::remove_unique<subcontract<C>>>;

  template<class Cmp = contract<mp::lift<std::is_same>>, class C = listify>
  using remove_unique_if = typename detail::smp_mk_remove_unique<Cmp>::template f<C>;

  template<class C = listify>
  using copy_unique = contract<mp::copy_unique<subcontract<C>>>;

  template<class Cmp = contract<mp::lift<std::is_same>>, class C = listify>
  using copy_unique_if = typename detail::smp_mk_copy_unique<Cmp>::template f<C>;
}


// because conjunction is a index_if
namespace jln::mp
{
  /// \ingroup list

  /// Retrieves an element of a sequence at an arbitrary position.
  /// \pre `0 <= N < sizeof...(xs)`
  /// \treturn \value
  template<class N, class C = identity>
  using at = drop_front<N, front<C>>;

  template<unsigned n, class C = identity>
  using at_c = drop_front_c<n, front<C>>;

  template<class C = identity>
  using at0 = front<C>;

  template<class C = identity>
  using at1 = drop_front_c<1, front<C>>;

  template<class C = identity>
  using at2 = drop_front_c<2, front<C>>;

  template<class C = identity>
  using at3 = drop_front_c<3, front<C>>;

  template<class C = identity>
  using at4 = drop_front_c<4, front<C>>;

  template<class C = identity>
  using at5 = drop_front_c<5, front<C>>;

  template<class C = identity>
  using at6 = drop_front_c<6, front<C>>;

  template<class C = identity>
  using at7 = drop_front_c<7, front<C>>;

  template<class C = identity>
  using at8 = drop_front_c<8, front<C>>;

  template<class C = identity>
  using at9 = drop_front_c<9, front<C>>;

  namespace emp
  {
    template<class L, class i, class C = mp::identity>
    using at = unpack<L, mp::drop_front_c<i::value, mp::front<C>>>;

    template<class L, unsigned i, class C = mp::identity>
    using at_c = unpack<L, mp::drop_front_c<i, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at0 = unpack<L, mp::front<C>>;

    template<class L, class C = mp::identity>
    using at1 = unpack<L, mp::drop_front_c<1, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at2 = unpack<L, mp::drop_front_c<2, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at3 = unpack<L, mp::drop_front_c<3, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at4 = unpack<L, mp::drop_front_c<4, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at5 = unpack<L, mp::drop_front_c<5, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at6 = unpack<L, mp::drop_front_c<6, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at7 = unpack<L, mp::drop_front_c<7, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at8 = unpack<L, mp::drop_front_c<8, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at9 = unpack<L, mp::drop_front_c<9, mp::front<C>>>;
  }
}
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned> struct _compose_f;
    template<class, class> struct _compose;
  }
  /// \endcond

  /// \ingroup functional

  /// Composition of two \metafunctions or more.
  /// \semantics
  ///   \code
  ///   compose_f<foo, bar>::f<a, b> == bar<foo<a, b>>
  ///   \endcode
  /// \treturn \function
  template<template<class...> class F, template<class...> class... Fs>
  using compose_f = typename detail::_compose_f<detail::min(8, sizeof...(Fs))>
    ::template f<F, Fs...>;

  /// Composition of two \functions or more.
  /// \semantics
  ///   \code
  ///   compose<foo, bar>::f<a, b> == bar::f<foo::f<a, b>>
  ///   \endcode
  /// \treturn \function
  template<class F, class... Fs>
  using compose = typename conditional_c<sizeof...(Fs) == 0>
    ::template f<
      at1<F>,
      mp::fold_right<lift_t<detail::_compose>>
    >
    ::template f<identity, F, Fs...>;
}


/// \cond
namespace jln::mp::detail
{
#define JLN_COMPOSE_IMPL(n, mp_xs, mp_rxs, mp_dup) \
  template<template<class...> class F              \
    mp_xs(JLN_MP_COMMA template<class...> class,   \
      JLN_MP_NIL, JLN_MP_NIL)>                     \
  struct _compose_f_impl##n                        \
  {                                                \
    template<class... xs>                          \
    using f = mp_rxs(JLN_MP_NIL, <, JLN_MP_NIL)    \
      JLN_MP_DCALLF_XS(xs, F, xs...)               \
    mp_dup(>, JLN_MP_NIL);                         \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_COMPOSE_IMPL)

#undef JLN_COMPOSE_IMPL

#define JLN_COMPOSE_IMPL(n, mp_xs, mp_rxs, mp_dup)  \
  template<>                                        \
  struct _compose_f<n>                              \
  {                                                 \
    template<template<class...> class F             \
      mp_xs(JLN_MP_COMMA template<class...> class,  \
        JLN_MP_NIL, JLN_MP_NIL)>                    \
    using f = _compose_f_impl##n<F                  \
      mp_xs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL)>; \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_COMPOSE_IMPL)

#undef JLN_COMPOSE_IMPL

  template<unsigned n>
  struct _compose_f
  {
    template<
      template<class...> class F0,
      template<class...> class F1,
      template<class...> class F2,
      template<class...> class F3,
      template<class...> class F4,
      template<class...> class F5,
      template<class...> class F6,
      template<class...> class F7,
      template<class...> class... Fs>
    using f = typename _compose_f<n-8>::template f<
      _compose_f_impl7<F0, F1, F2, F3, F4, F5, F6, F7>::template f,
      Fs...
    >;
  };

  template<class F, class C>
  struct _compose
  {
    using type = tee<F, C>;
  };

  template<template<class...> class F, class x>
  struct _compose<lift<F>, x>
  {
    using type = lift<F, x>;
  };

  template<template<class...> class F, class x>
  struct _compose<lift_t<F>, x>
  {
    using type = lift_t<F, x>;
  };

  template<template<class...> class F>
  struct _compose<lift<F>, identity>
  {
    using type = lift<F>;
  };

  template<template<class...> class F>
  struct _compose<lift_t<F>, identity>
  {
    using type = lift_t<F>;
  };

  template<class F>
  struct _compose<F, identity>
  {
    using type = F;
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<class Pred, class TC>
  using smp_index_if_cond = mp::if_<
    mp::front<smp::concepts::strong_predicate<assume_unary<Pred>, mp::always<true_>>>,
    mp::size<
      mp::push_back<
        smp::sub<assume_positive_number_barrier<TC>>,
        mp::compose_f<mp::push_back, mp::size>
      >
    >,
    mp::always<violation>
  >;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class TC = identity, class FC = size<>>
  using index_if = contract<mp::invoke_twice<
    mp::drop_while<
      concepts::strong_predicate<assume_unary<Pred>, mp::not_<>>,
      detail::smp_index_if_cond<assume_unary<Pred>, TC>,
      mp::always<subcontract<FC>>
    >
  >>;

  template<class T, class TC = identity, class FC = size<>>
  using index_of = contract<mp::index_if<is<T>, subcontract<TC>, subcontract<FC>>>;

  template<class Pred, class TC = identity, class FC = size<>>
  using index_if_xs = contract<mp::invoke_twice<
    mp::drop_while_xs<
      concepts::strong_predicate<assume_unary_or_more<Pred>, mp::not_<>>,
      detail::smp_index_if_cond<assume_unary_or_more<Pred>, TC>,
      mp::always<subcontract<FC>>
    >
  >>;

  template<int_ OffsetEnd, class Pred, class TC = identity, class FC = size<>>
  using partial_index_if_xs_c = contract<mp::invoke_twice<
    mp::partial_drop_while_xs_c<
      OffsetEnd,
      concepts::strong_predicate<assume_unary_or_more<Pred>, mp::not_<>>,
      detail::smp_index_if_cond<assume_unary_or_more<Pred>, TC>,
      mp::always<subcontract<FC>>
    >
  >>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(partial_index_if_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, smp::size<>),
  smp::partial_index_if_xs_c<OffsetEnd::value, Pred, TC, FC>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, index_if<Pred, TC, FC>>
  {
    using type = smp::index_if<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, index_if_xs<Pred, TC, FC>>
  {
    using type = smp::index_if_xs<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, int_ OffsetEnd, class Pred, class TC, class FC>
  struct _sfinae<sfinae, partial_index_if_xs_c<OffsetEnd, Pred, TC, FC>>
  {
    using type = smp::partial_index_if_xs_c<OffsetEnd, sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, remove_unique<C>>
  {
    using type = smp::remove_unique<sfinae<C>>;
  };

  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, detail::_remove_unique_if<Cmp, C>>
  {
    using type = smp::remove_unique_if<sfinae<Cmp>, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, copy_unique<C>>
  {
    using type = smp::copy_unique<sfinae<C>>;
  };

  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, detail::_copy_unique_if<Cmp, C>>
  {
    using type = smp::copy_unique_if<sfinae<Cmp>, sfinae<C>>;
  };


  template<class Indexes>
  struct smp_remove_unique_if_impl;

  template<std::size_t... ints>
  struct smp_remove_unique_if_impl<std::integer_sequence<std::size_t, ints...>>
  {
    template<class C, class Cmp, class... xs>
    using f = typename join<C>::template f<
      JLN_MP_MSVC_FIX_CALL((
        rotate_c<ints, pop_front<smp::index_if<
          contract<push_back<xs, Cmp>>,
          contract<always<wrap_in_list_c<true>>>,
          contract<always<wrap_in_list_c<false>>>
        >>>
        ::template f<xs...>
      ), xs)...
    >;
  };

  template<>
  struct smp_remove_unique_if_impl<std::integer_sequence<std::size_t>>
  : remove_unique_if_impl<std::integer_sequence<std::size_t>>
  {};

  template<std::size_t i>
  struct smp_remove_unique_if_impl<std::integer_sequence<std::size_t, i>>
  : remove_unique_if_impl<std::integer_sequence<std::size_t>>
  {};

  template<class Cmp, class C>
  struct smp_remove_unique_if
  {
    template<class... xs>
    using f = typename try_<
      detail::smp_remove_unique_if_impl<std::make_index_sequence<sizeof...(xs)>>
    >::template f<C, Cmp, xs...>;
  };

  template<class Cmp>
  struct smp_mk_remove_unique
  {
    template<class C>
    using f = contract<smp_remove_unique_if<assume_binary<Cmp>, subcontract<C>>>;
  };

  template<>
  struct smp_mk_remove_unique<contract<lift<std::is_same>>>
  {
    template<class C>
    using f = smp::remove_unique<C>;
  };


  template<class Indexes>
  struct smp_copy_unique_if_impl;

  template<std::size_t... ints>
  struct smp_copy_unique_if_impl<std::integer_sequence<std::size_t, ints...>>
  {
    template<class C, class Cmp, class... xs>
    using f = typename join<C>::template f<
      JLN_MP_MSVC_FIX_CALL((
        rotate_c<ints, pop_front<smp::index_if<
          contract<push_back<xs, Cmp>>,
          contract<always<wrap_in_list_c<false>>>,
          contract<always<wrap_in_list_c<true>>>
        >>>
        ::template f<xs...>
      ), xs)...
    >;
  };

  template<>
  struct smp_copy_unique_if_impl<std::integer_sequence<std::size_t>>
  : remove_unique_if_impl<std::integer_sequence<std::size_t>>
  {};

  template<std::size_t i>
  struct smp_copy_unique_if_impl<std::integer_sequence<std::size_t, i>>
  : copy_unique_if_impl<std::integer_sequence<std::size_t, i>>
  {};

  template<class Cmp, class C>
  struct smp_copy_unique_if
  {
    template<class... xs>
    using f = typename try_<
      detail::smp_copy_unique_if_impl<std::make_index_sequence<sizeof...(xs)>>
    >::template f<C, Cmp, xs...>;
  };

  template<class Cmp>
  struct smp_mk_copy_unique
  {
    template<class C>
    using f = contract<smp_copy_unique_if<assume_binary<Cmp>, subcontract<C>>>;
  };

  template<>
  struct smp_mk_copy_unique<contract<lift<std::is_same>>>
  {
    template<class C>
    using f = smp::copy_unique<C>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup algorithm

  /// Counts all elements that satisfy a predicate.
  template<class Pred, class C = identity>
  using count_if = transform<Pred, add0<C>>;

  /// Counts all elements identical to a \value.
  template<class x, class C = identity>
  using count = transform<is<x>, add0<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using count_if = unpack<L, mp::count_if<Pred, C>>;

    template<class L, class x, class C = mp::identity>
    using count = unpack<L, mp::count<x, C>>;
  }
}
namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using count_if = transform<Pred, add0<assume_positive_number_barrier<C>>>;

  template<class x, class C = identity>
  using count = contract<mp::count<x, assume_positive_number<C>>>;
}
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class... xs>
    struct counter_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Counts all distinct elements and returns a list of pairs containing
  /// the type and the repeat count.
  /// Elements are sorted in order of first appearance.
  /// \semantics
  ///   \code
  ///   counter<F>::f<int, int, char, double, int, double>
  ///   == list<
  ///     F::f<int, number<3>>,
  ///     F::f<char, number<1>>,
  ///     F::f<double, number<2>>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list of type and \number
  template<class F, class C = listify>
  struct counter_wrapped_with
  {
    template<class... xs>
    using f = typename unique<lift<detail::counter_impl>>
      ::f<xs...>
      ::template f<C, F, xs...>;
  };

  /// Counts all distinct elements and returns a list of pairs containing
  /// the type and the repeat count.
  /// Elements are sorted in order of first appearance.
  /// \semantics
  ///   \code
  ///   counter<F>::f<int, int, char, double, int, double>
  ///   == list<
  ///     list<int, number<3>>,
  ///     list<char, number<1>>,
  ///     list<double, number<2>>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list of type and \number
  template<class C = listify>
  using counter = counter_wrapped_with<listify, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using counter = unpack<L, mp::counter<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using counter_wrapped_with = unpack<L, mp::counter_wrapped_with<F, C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
#if JLN_MP_GCC || defined(JLN_MP_COUNTER_NO_FOLD)
  template<class T>
  struct inc_if
  {
    template<class state, class x>
    using f = number<state::value + std::is_same<T, x>::value>;
  };

  template<class... xs>
  struct counter_impl
  {
    template<class C, class F, class... ys>
    using f = JLN_MP_CALL_TRACE(C,
      JLN_MP_CALL_TRACE(F, xs, typename fold_left<inc_if<xs>>::template f<number<0>, ys...>)...
    );
  };
#else
  template<class x, class... xs>
  inline constexpr auto count_unique_v = (... + std::is_same<xs, x>::value);

  template<class... xs>
  struct counter_impl
  {
    template<class C, class F, class... ys>
    using f = JLN_MP_CALL_TRACE(C,
      JLN_MP_CALL_TRACE(F, xs, mp::number<count_unique_v<xs, ys...>>)...
    );
  };
#endif
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = listify>
  using counter = contract<mp::counter<assume_lists<C>>>;

  template<class F = listify, class C = listify>
  using counter_wrapped_with = contract<mp::counter_wrapped_with<
    assume_binary<F>, detail::smp_listify_or_monadic_xs<F, C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, counter<C>>
  {
    using type = smp::counter<sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, counter_wrapped_with<F, C>>
  {
    using type = smp::counter_wrapped_with<sfinae<F>, sfinae<C>>;
  };
}
namespace jln::mp
{
  /// \ingroup algorithm

  /// Perform a logical OR on the sequence of value.
  /// Disjunction is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(xs[i]::value) != false`, then instantiating
  /// `disjunction<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `xs[j]::value` for j > i
  /// \treturn \bool
  /// \see conjunction, drop_while, take_while
  template<class C = identity>
  using disjunction = any_of<to_bool<>, C>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using disjunction = unpack<L, mp::disjunction<C>>;
  }
}
namespace jln::mp::smp
{
  template<class C = identity>
  using disjunction = any_of<to_bool<>, C>;
}
/// \cond
namespace jln::mp::detail
{
  template<bool IsZero>
  struct smp_drop_while_for_size;

  template<>
  struct smp_drop_while_for_size<true>
  {
    template<std::size_t ExtendedByN, class C>
    using f = C;
  };

  template<>
  struct smp_drop_while_for_size<false>
  {
    template<std::size_t ExtendedByN, class C>
    using f = contract<mp::drop_front_max_c<ExtendedByN, subcontract<C>>>;
  };
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_while_xs = contract<mp::drop_while_xs<
    concepts::strong_predicate<assume_unary_or_more<Pred>, mp::identity, mp::always<false_>>,
    mp::if_<
      concepts::strong_predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
      assume_unary_or_more<TC>,
      violation
    >,
    subcontract<FC>
  >>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_while_xs_c = contract<mp::partial_drop_while_xs_c<
    OffsetEnd,
    concepts::strong_predicate<assume_unary_or_more<Pred>, mp::identity, mp::always<false_>>,
    mp::if_<
      concepts::strong_predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
      assume_unary_or_more<TC>,
      violation
    >,
    subcontract<FC>
  >>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_while_xs = drop_while_xs<
    Pred, contract<mp::drop_front_c<1, subcontract<TC>>>, FC>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_inclusive_while_xs_c = partial_drop_while_xs_c<
    OffsetEnd, Pred, contract<mp::drop_front_c<1, subcontract<TC>>>, FC>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_while_extended_by_n_xs_c = drop_while_xs<
    Pred,
    typename detail::smp_drop_while_for_size<ExtendedByN == 0>::template f<ExtendedByN, TC>,
    FC>;

  template<int_ OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_while_extended_by_n_xs_c = partial_drop_while_xs_c<
    OffsetEnd, Pred,
    typename detail::smp_drop_while_for_size<ExtendedByN == 0>::template f<ExtendedByN, TC>,
    FC>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(partial_drop_while_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, smp::clear<TC>),
  smp::partial_drop_while_xs_c<OffsetEnd::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP4_P(partial_drop_inclusive_while_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, smp::clear<TC>),
  smp::partial_drop_inclusive_while_xs_c<OffsetEnd::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP4_P(drop_while_extended_by_n_xs,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, smp::clear<TC>),
  smp::drop_while_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP5_P(partial_drop_while_extended_by_n_xs,
  (OffsetEnd), (ExtendedByN), (Pred), (TC, smp::listify), (FC, smp::clear<TC>),
  smp::partial_drop_while_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, drop_while_xs<Pred, TC, FC>>
  {
    using type = smp::drop_while_xs<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, std::size_t ExtendedByN, class Pred, class TC, class FC>
  struct _sfinae<sfinae, drop_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::drop_while_extended_by_n_xs_c<ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, int_ OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC, class FC>
  struct _sfinae<sfinae, partial_drop_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::partial_drop_while_extended_by_n_xs_c<
      OffsetEnd, ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>
    >;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_until_xs = contract<mp::drop_until_xs<
    concepts::strong_predicate<assume_unary_or_more<Pred>, mp::identity, mp::always<true_>>,
    mp::if_<
      concepts::strong_predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
      assume_unary_or_more<TC>,
      violation
    >,
    subcontract<FC>
  >>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_until_xs_c = contract<mp::partial_drop_until_xs_c<
    OffsetEnd,
    concepts::strong_predicate<assume_unary_or_more<Pred>, mp::identity, mp::always<true_>>,
    mp::if_<
      concepts::strong_predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
      assume_unary_or_more<TC>,
      violation
    >,
    subcontract<FC>
  >>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_until_xs = drop_until_xs<
    Pred, contract<mp::drop_front_c<1, subcontract<TC>>>, FC>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_inclusive_until_xs_c = partial_drop_until_xs_c<
    OffsetEnd, Pred, contract<mp::drop_front_c<1, subcontract<TC>>>, FC>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_until_extended_by_n_xs_c = drop_until_xs<
    Pred,
    typename detail::smp_drop_while_for_size<ExtendedByN == 0>::template f<ExtendedByN, TC>,
    FC>;

  template<int_ OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_until_extended_by_n_xs_c = partial_drop_until_xs_c<
    OffsetEnd, Pred,
    typename detail::smp_drop_while_for_size<ExtendedByN == 0>::template f<ExtendedByN, TC>,
    FC>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(partial_drop_until_xs, (OffsetEnd), (Pred), (C, smp::listify),
  smp::partial_drop_until_xs_c<OffsetEnd::value, Pred, C>)

JLN_MP_MAKE_REGULAR_SMP3_P(partial_drop_inclusive_until_xs, (OffsetEnd), (Pred), (C, smp::listify),
  smp::partial_drop_inclusive_until_xs_c<OffsetEnd::value, Pred, C>)

JLN_MP_MAKE_REGULAR_SMP4_P(drop_until_extended_by_n_xs,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, smp::clear<TC>),
  smp::drop_until_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP5_P(partial_drop_until_extended_by_n_xs,
  (OffsetEnd), (ExtendedByN), (Pred), (TC, smp::listify), (FC, smp::clear<TC>),
  smp::partial_drop_until_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, drop_until_xs<Pred, TC, FC>>
  {
    using type = smp::drop_until_xs<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, std::size_t ExtendedByN, class Pred, class TC, class FC>
  struct _sfinae<sfinae, drop_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::drop_until_extended_by_n_xs_c<ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, int_ OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC, class FC>
  struct _sfinae<sfinae, partial_drop_until_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::partial_drop_until_extended_by_n_xs_c<
      OffsetEnd, ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>
    >;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct ends_with_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks if the \sequence ends with the given prefix.
  /// \treturn \bool
  /// \see ends_with
  template<class Seq, class C = identity>
  struct ends_with
  {};

  namespace emp
  {
    template<class L, class Seq, class C = mp::identity>
    using ends_with = unpack<ends_with<Seq, C>, L>;
  }

  template<class... Ts, class C>
  struct ends_with<list<Ts...>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::ends_with_impl<sizeof...(Ts) <= sizeof...(xs)>
      ::template f<sizeof...(Ts), list<Ts...>, xs...>
    );
  };
}

/// \cond
namespace jln::mp
{
  /// \ingroup list

  /// Extracts \c N elements from the end of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see take_back_max, take_front, drop_front, drop_back, take_while
  template<unsigned N, class C = listify>
  struct take_back_c
  {
    template<class... xs>
    using f = typename detail::drop_front_impl<
      sizeof...(xs) - N
    >::template f<sizeof...(xs) - N, C, xs...>;
  };

  /// Extracts at most \c N elements from the end of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see take_front, take_back, take_while
  template<unsigned N, class C = listify>
  struct take_back_max_c
  {
    template<class... xs>
    using f = typename detail::drop_front_impl<
      sizeof...(xs) - detail::min(N, sizeof...(xs))
    >::template f<sizeof...(xs) - detail::min(N, sizeof...(xs)), C, xs...>;
  };

  template<class N, class C = listify>
  using take_back = take_back_c<N::value, C>;

  template<class N, class C = listify>
  using take_back_max = take_back_max_c<N::value, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using take_back = unpack<L, mp::take_back<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_back_c = unpack<L, mp::take_back_c<n, C>>;

    template<class L, class N, class C = mp::listify>
    using take_back_max = unpack<L, mp::take_back_max<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_back_max_c = unpack<L, mp::take_back_max_c<n, C>>;
  }

  /// \cond
  template<class C>
  struct take_back_c<0, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS_0(xs, C);
  };

  template<class C>
  struct take_back_max_c<0, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS_0(xs, C);
  };
  /// \endcond
}
namespace jln::mp::detail
{
  template<>
  struct ends_with_impl<true>
  {
    template<unsigned n, class L, class... xs>
    using f = number<std::is_same<typename take_back_c<n>::template f<xs...>, L>::value>;
  };

  template<>
  struct ends_with_impl<false>
  {
    template<unsigned n, class L, class... xs>
    using f = false_;
  };
}

namespace jln::mp
{
  template<class T, class C>
  struct ends_with<list<T>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename conditional_c<1 <= sizeof...(xs)>
      ::template f<take_back_c<1, is<T>>, always<false_>>
      ::template f<xs...>
    );
  };

  template<class C>
  struct ends_with<list<>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, true_);
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class Seq, class C = identity>
  using ends_with = typename mp::conditional_c<detail::_is_list<Seq>::type::value>
    ::template f<contract<mp::ends_with<Seq, assume_positive_number<C>>>, bad_contract>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Seq, class C>
  struct _sfinae<sfinae, ends_with<Seq, C>>
  {
    using type = smp::ends_with<Seq, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup search

  /// Finds the first element that satisfy a \predicate.
  /// \pre \c Pred::f<x> must return a boolean, 1 or 0
  /// Calls \c TC with all the elements since the one found at the end.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see find_if_not, find, find_last_if, find_last
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_if = drop_until<Pred, TC, FC>;

  /// \see find_if, find, find_last_if, find_last
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_if_not = drop_while<Pred, TC, FC>;

  /// \see find_if, find_if_not, find_last_if, find_last
  template<class T, class TC = listify, class FC = clear<TC>>
  using find = find_if<is<T>, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using find_if = unpack<L, mp::find_if<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using find_if_not = unpack<L, mp::find_if_not<Pred, TC, FC>>;

    template<class L, class T, class TC = mp::listify, class FC = clear<TC>>
    using find = unpack<L, mp::find_if<mp::is<T>, TC, FC>>;
  }
}
namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_if = drop_until<Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_if_not = drop_while<Pred, TC, FC>;

  template<class T, class TC = listify, class FC = clear<TC>>
  using find = contract<mp::find<T, assume_unary_or_more<TC>, subcontract<FC>>>;
}
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct _recursively;

    template<class>
    struct _recursively_as_much_as_possible;

    template<class x>
    struct _recursively_next;

    template<class x>
    struct _recursively_as_much_as_possible_next;

    template<class...>
    struct _recursion_result;

    template<class...>
    struct _next_recursion;
  }
  /// \endcond

  /// \ingroup functional

  /// Stop the recursion, the input values will be used as result.
  struct stop_recursion
  {
    template<class...>
    using f = stop_recursion;
  };

  /// Specify result values and stop recursion.
  struct recursion_result
  {
    template<class... xs>
    using f = detail::_recursion_result<xs...>;
  };

  /// Specify values for the next iteration.
  struct next_recursion
  {
    template<class... xs>
    using f = detail::_next_recursion<xs...>;
  };

  /// \ingroup functional

  /// Recursively invokes \c F until \c stop_recursion or \c recursion_result.
  /// \treturn \value
  /// \see recursively_xs, recursively_as_much_as_possible
  /// \see stop_recursion, recursion_result, next_recursion
  template<class F, class C = identity>
  struct recursively
  {
    template<class... xs>
    using f = typename detail::_recursively<
      typename detail::_recursively_next<JLN_MP_DCALL_TRACE_XS(xs, F, xs...)>
      ::template g<xs...>
      ::template f<F>
      ::template f<F>
      ::template f<F>
    >::template f<F, C>;
  };

  /// Same than \c recursively, but with listify as continuation.
  /// \treturn \sequence
  /// \see recursively
  template<class F, class C = listify>
  using recursively_xs = recursively<F, C>;

  /// Recursively invokes \c F until the result is \c stop_recursion, \c recursion_result or no longer changes.
  /// \treturn \value
  /// \see recursively_as_much_as_possible_xs
  /// \see recursively
  /// \see stop_recursion, recursion_result, next_recursion
  template<class F, class C = identity>
  struct recursively_as_much_as_possible
  {
    template<class... xs>
    using f = typename detail::_recursively_as_much_as_possible<
      typename detail::_recursively_as_much_as_possible_next<JLN_MP_DCALL_TRACE_XS(xs, F, xs...)>
        ::template g<xs...>
        ::template f<F>
        ::template f<F>
        ::template f<F>
    >::template f<F, C>;
  };

  /// Same than \c recursively_as_much_as_possible, but with listify as continuation.
  /// \treturn \value
  /// \see recursively_as_much_as_possible
  template<class F, class C = listify>
  using recursively_as_much_as_possible_xs = recursively_as_much_as_possible<F, C>;

  namespace emp
  {
    template<class L, class F, class C = mp::identity>
    using recursively = unpack<L, mp::recursively<F, C>>;

    template<class L, class F, class C = mp::identity>
    using recursively_as_much_as_possible = unpack<L, mp::recursively_as_much_as_possible<F, C>>;

    template<class L, class F, class C = mp::listify>
    using recursively_xs = unpack<L, mp::recursively<F, C>>;

    template<class L, class F, class C = mp::listify>
    using recursively_as_much_as_possible_xs = unpack<L, mp::recursively_as_much_as_possible<F, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct _recursively_next
  {
    template<class>
    using f = _recursively_next;

    template<class...>
    using g = _recursively_next<_next_recursion<x>>;
  };

  template<>
  struct _recursively_next<stop_recursion>
  {
    template<class>
    using f = _recursively_next;

    template<class... xs>
    using g = _recursively_next<_recursion_result<xs...>>;
  };

  template<class... xs>
  struct _recursively_next<_recursion_result<xs...>>
  {
    template<class>
    using f = _recursively_next;

    template<class...>
    using g = _recursively_next;
  };

  template<class... xs>
  struct _recursively_next<_next_recursion<xs...>>
  {
    template<class F>
    using f = typename _recursively_next<JLN_MP_CALL_TRACE(F, xs...)>
              ::template g<xs...>;

    template<class...>
    using g = _recursively_next;
  };

  template<class... xs>
  struct _recursively<_recursively_next<_next_recursion<xs...>>>
  {
    template<class F, class C>
    using f = typename _recursively<
      typename _recursively_next<JLN_MP_CALL_TRACE(F, xs...)>
      ::template g<xs...>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
    >::template f<F, C>;
  };

  template<class... xs>
  struct _recursively<_recursively_next<_recursion_result<xs...>>>
  {
    template<class F, class C>
    using f = typename C::template f<xs...>;
  };

  template<bool>
  struct recursively_next_step;

  template<>
  struct recursively_next_step<true>
  {
    template<class x>
    using f = _recursively_as_much_as_possible_next<_recursion_result<x>>;
  };

  template<>
  struct recursively_next_step<false>
  {
    template<class x>
    using f = _recursively_as_much_as_possible_next<_next_recursion<x>>;
  };

  template<class x>
  struct _recursively_as_much_as_possible_next
  {
    template<class>
    using f = _recursively_as_much_as_possible_next;

    template<class... xs>
    using g = typename recursively_next_step<std::is_same<list<x>, list<xs...>>::value>
      ::template f<x>;
  };

  template<>
  struct _recursively_as_much_as_possible_next<stop_recursion>
  {
    template<class>
    using f = _recursively_as_much_as_possible_next;

    template<class... xs>
    using g = _recursively_as_much_as_possible_next<_recursion_result<xs...>>;
  };

  template<class... xs>
  struct _recursively_as_much_as_possible_next<_recursion_result<xs...>>
  {
    template<class>
    using f = _recursively_as_much_as_possible_next;

    template<class...>
    using g = _recursively_as_much_as_possible_next;
  };

  template<class... xs>
  struct _recursively_as_much_as_possible_next<_next_recursion<xs...>>
  {
    template<class F>
    using f = typename _recursively_as_much_as_possible_next<JLN_MP_CALL_TRACE(F, xs...)>
              ::template g<xs...>;

    template<class...>
    using g = _recursively_as_much_as_possible_next;
  };

  template<class... xs>
  struct _recursively_as_much_as_possible<_recursively_as_much_as_possible_next<_next_recursion<xs...>>>
  {
    template<class F, class C>
    using f = typename _recursively_as_much_as_possible<
      typename _recursively_as_much_as_possible_next<JLN_MP_CALL_TRACE(F, xs...)>
      ::template g<xs...>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
    >::template f<F, C>;
  };

  template<class... xs>
  struct _recursively_as_much_as_possible<_recursively_as_much_as_possible_next<_recursion_result<xs...>>>
  {
    template<class F, class C>
    using f = JLN_MP_CALL_TRACE(C, xs...);
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class F, class C = identity>
  using recursively = contract<mp::recursively<
    try_subcontract<F, mp::identity, mp::always<na, mp::recursion_result>>,
    monadic_xs<subcontract<C>>>>;

  template<class F, class C = listify>
  using recursively_xs = recursively<F, C>;

  template<class F, class C = identity>
  using recursively_as_much_as_possible = contract<mp::recursively_as_much_as_possible<
    try_subcontract<F, mp::identity, mp::always<na, mp::recursion_result>>,
    monadic_xs<subcontract<C>>>>;

  using stop_recursion = contract<mp::stop_recursion>;
  using next_recursion = contract<mp::next_recursion>;
  using recursion_result = contract<mp::recursion_result>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, recursively<F, C>>
  {
    using type = smp::recursively<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, recursively_as_much_as_possible<F, C>>
  {
    using type = smp::recursively_as_much_as_possible<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae>
  struct _sfinae<sfinae, stop_recursion>
  {
    using type = smp::stop_recursion;
  };

  template<template<class> class sfinae>
  struct _sfinae<sfinae, next_recursion>
  {
    using type = smp::next_recursion;
  };

  template<template<class> class sfinae>
  struct _sfinae<sfinae, recursion_result>
  {
    using type = smp::recursion_result;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct until_last_impl
    {};
  }
  /// \endcond

  /// \ingroup functional

  /// Uses a \c Searcher in a loop until the last result.
  /// Searcher must end with the continuations TC and FC.
  /// `until_last_t<find, is<x>, TC, FC>` is equivalent to \c find_last
  /// \treturn \sequence
  template<class Searcher>
  using until_last = typename detail::until_last_impl<Searcher>::type;

  template<template<class...> class Tpl, class Pred, class TC = listify, class FC = clear<TC>>
  using until_last_t = Tpl<Pred, recursively<
    pop_front<Tpl<Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;

  template<
    template<class...> class Tpl,
    class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_until_last_t = Tpl<OffsetEnd, Pred, recursively<
    pop_front<Tpl<OffsetEnd, Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;

  template<
    template<int_, class...> class Tpl,
    int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_until_last_t_c = Tpl<OffsetEnd, Pred, recursively<
    pop_front<Tpl<OffsetEnd, Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;

  namespace emp
  {
    template<class L, class Searcher>
    using until_last = unpack<L, mp::until_last<Searcher>>;

    template<
      class L, template<class...> class Tpl,
      class Pred, class TC = listify, class FC = clear<TC>>
    using until_last_t = unpack<L, mp::until_last_t<Tpl, Pred, TC, FC>>;

    template<
      class L, template<class...> class Tpl,
      class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
    using partial_until_last_t = unpack<L, mp::partial_until_last_t<Tpl, OffsetEnd, Pred, TC, FC>>;

    template<
      class L, template<int_, class...> class Tpl,
      int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
    using partial_until_last_t_c = unpack<L,
      mp::partial_until_last_t_c<Tpl, OffsetEnd, Pred, TC, FC>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<class F, class TC, class FC>
  struct until_last_impl<try_<F, TC, FC>>
  {
    using type = try_<typename until_last_impl<F>::type, TC, FC>;
  };

  template<class Pred, class TC>
  struct until_last_impl<if_<Pred, TC, violation>>
  {
    using type = if_<Pred, typename until_last_impl<TC>::type, violation>;
  };

  template<template<class, class> class Tpl, class TC, class FC>
  struct until_last_impl<Tpl<TC, FC>>
  {
    using type = Tpl<recursively<
      pop_front<Tpl<next_recursion, stop_recursion>>,
      TC
    >, FC>;
  };

#define JLN_MP_MK_UNTIL_LAST_IMPL(tpl_params, arg_names)                       \
  template<                                                                    \
    template<JLN_MP_UNPACK tpl_params, class, class> class Tpl,                \
    JLN_MP_UNPACK tpl_params, class TC, class FC>                              \
  struct until_last_impl<Tpl<JLN_MP_UNPACK arg_names, TC, FC>>                 \
  {                                                                            \
    using type = Tpl<JLN_MP_UNPACK arg_names, recursively<                     \
      pop_front<Tpl<JLN_MP_UNPACK arg_names, next_recursion, stop_recursion>>, \
      TC                                                                       \
    >, FC>;                                                                    \
  }

  JLN_MP_MK_UNTIL_LAST_IMPL((class Pred), (Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((class Data1, class Pred), (Data1, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((class Data1, class Data2, class Pred),
                            (Data1, Data2, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((class Data1, class Data2, class Data3, class Pred),
                            (Data1, Data2, Data3, Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, class Pred), (Data1, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, class Data2, class Pred),
                            (Data1, Data2, Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, int_ Data2, class Pred),
                            (Data1, Data2, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, int_ Data2, class Data3, class Pred),
                            (Data1, Data2, Data3, Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((std::size_t Data1, class Pred), (Data1, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((std::size_t Data1, class Data2, class Pred),
                            (Data1, Data2, Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((std::size_t Data1, std::size_t Data2, class Pred),
                            (Data1, Data2, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((std::size_t Data1, std::size_t Data2, class Data3, class Pred),
                            (Data1, Data2, Data3, Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, std::size_t Data2, class Pred),
                            (Data1, Data2, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, std::size_t Data2, class Data3, class Pred),
                            (Data1, Data2, Data3, Pred));

#undef JLN_MP_MK_UNTIL_LAST_IMPL
}
/// \endcond
namespace jln::mp
{
  /// \ingroup trait

  /// Function for \c x::type.
  /// \treturn \value
  template<class C = identity>
  struct type_
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename x::type);
  };

  template<>
  struct type_<identity>
  {
    template<class x>
    using f = typename x::type;
  };

  namespace emp
  {
    template<class x>
    using type_ = typename x::type;
  }
}
namespace jln::mp::smp
{
  template<class Searcher>
  using until_last = emp::try_<
    mp::type_<>,
    mp::lift<contract>,
    mp::always<bad_contract>,
    detail::until_last_impl<Searcher>
  >;

  template<template<class...> class Tpl, class Pred, class TC = listify, class FC = clear<TC>>
  using until_last_t = Tpl<Pred, recursively<
    pop_front<Tpl<Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;

  template<
    template<class...> class Tpl,
    class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_until_last_t = Tpl<OffsetEnd, Pred, recursively<
    pop_front<Tpl<OffsetEnd, Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;

  template<
    template<int_, class...> class Tpl,
    int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_until_last_t_c = Tpl<OffsetEnd, Pred, recursively<
    pop_front<Tpl<OffsetEnd, Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;
}

/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct until_last_impl<contract<F>>
  {
    using type = contract<typename until_last_impl<F>::type>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup search

  /// Finds the last element that satisfy a \predicate.
  /// Calls \c TC with all the elements since the last found at the end.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see find_last_if_not, find_last, find
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_last_if = until_last_t<drop_until, Pred, TC, FC>;

  /// \see find_last_if, find_last, find
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_last_if_not = until_last_t<drop_while, Pred, TC, FC>;

  /// \see find_last_if, find_last_if_not, find_last, find
  template<class T, class TC = listify, class FC = clear<TC>>
  using find_last = find_last_if<is<T>, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using find_last_if = unpack<L, mp::find_last_if<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using find_last_if_not = unpack<L, mp::find_last_if_not<Pred, TC, FC>>;

    template<class L, class T, class TC = mp::listify, class FC = clear<TC>>
    using find_last = unpack<L, mp::find_last_if<mp::is<T>, TC, FC>>;
  }
}
namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_last_if = until_last_t<drop_until, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_last_if_not = until_last_t<drop_while, Pred, TC, FC>;

  template<class T, class TC = listify, class FC = clear<TC>>
  using find_last = find_last_if<is<T>, TC, FC>;
}
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<template<class...> class, class>
    struct _flatten;

    template<class S>
    struct wrapper;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Converts a tree or list of lists into one list containing the contents of all children.
  /// \treturn \sequence
  template<class S = lift<list>, class C = listify>
  struct flatten
  {};

  template<template<class...> class S, class C>
  struct flatten<lift<S, identity>, C>
  {
    template<class... seqs>
    using f = typename detail::_join_select<sizeof...(seqs)>
      ::template f<JLN_MP_TRACE_F(C), typename detail::_flatten<S, seqs>::type...>
      ::type;
  };

  /// converts a \typelist to a \c lift<S>
  template<class L>
  using wrapper = typename detail::wrapper<L>::type;

  namespace emp
  {
    template<class L, class S = wrapper<L>, class C = mp::listify>
    using flatten = unpack<L, mp::flatten<S, C>>;

    template<class L, class... xs>
    using rewrap = typename wrapper<L>::template f<xs...>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<template<class...> class, class T>
  struct _flatten
  {
    using type = list<T>;
  };

  template<template<class...> class S, class... xs>
  struct _flatten<S, S<xs...>>
  : _join_select<sizeof...(xs)>
    ::template f<listify, typename _flatten<S, xs>::type...>
  {};

  template<template<class...> class S, class... xs>
  struct wrapper<S<xs...>>
  {
    using type = lift<S>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class S = mp::lift<list>, class C = listify>
  using flatten = try_contract<mp::flatten<S, subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class S, class C>
  struct _sfinae<sfinae, flatten<S, C>>
  {
    using type = smp::flatten<S, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class F, class C = identity>
  using fold_left = test_contract<
    mp::size<>,
    mp::fold_left<
      mp::monadic0<assume_binary<F>>,
      mp::monadic<assume_unary<C>>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, fold_left<F, C>>
  {
    using type = smp::fold_left<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct fold_left_xs_impl;

    constexpr int_ partial_fold_left_xs_size(int_ i, int_ size)
    {
      // size contains state + xs...
      return (size == 0) ? 0
        : (i >= size) ? 1
        : (i >= 0) ? i + 1
        : (i >= -size) ? size + i + 1
        : 0
        ;
    }

    template<class F, int_ n, class... xs>
    using partial_fold_left_xs_select = typename detail::fold_left_xs_impl<n-1>
      ::template f<F::template f, n-1, xs...>;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Folds left over a list using a mulary predicate.
  /// fold_left_xs consideres the first element in the input pack as the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<... F::f<xs[0], xs[1], ..., xs[n-1]>, xs[2], ..., xs[n-1]>, ..., xs[n-1]>, ...>
  ///   \endcode
  /// \treturn \value
  /// \see fold_right, fold_tree, reverse_fold, fold_balanced_tree
  template<int_ OffsetEnd, class F, class C = identity>
  struct partial_fold_left_xs_c
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      detail::partial_fold_left_xs_select<
        JLN_MP_TRACE_F(F),
        detail::partial_fold_left_xs_size(OffsetEnd, sizeof...(xs)),
        xs...
      >
    );
  };

  template<class OffsetEnd, class F, class C = identity>
  using partial_fold_left_xs = partial_fold_left_xs_c<OffsetEnd::value, F, C>;

#ifdef JLN_MP_DOXYGENATING
  template<class F, class C = identity>
  using fold_left_xs = partial_fold_left_xs_c<-1, F, C>;
#else
  template<class F, class C = identity>
  struct fold_left_xs
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      detail::partial_fold_left_xs_select<JLN_MP_TRACE_F(F), sizeof...(xs), xs...>
    );
  };
#endif

  namespace emp
  {
    template<class L, class OffsetEnd, class state, class F, class C = mp::identity>
    using partial_fold_left_xs = unpack<L,
      mp::push_front<state, mp::partial_fold_left_xs<OffsetEnd, F, C>>>;

    template<class L, int_ OffsetEnd, class state, class F, class C = mp::identity>
    using partial_fold_left_xs_c = unpack<L,
      mp::push_front<state, mp::partial_fold_left_xs_c<OffsetEnd, F, C>>>;

    template<class L, class state, class F, class C = mp::identity>
    using fold_left_xs = unpack<L,
      mp::push_front<state, mp::fold_left_xs<F, C>>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<int n>
  struct fold_left_xs_impl : fold_left_xs_impl<
      n < 8 ? 4
    : n < 16 ? 8
    : n < 64 ? 16
    : 64
  >
  {};

  template<>
  struct fold_left_xs_impl<-1>
  {};

  template<>
  struct fold_left_xs_impl<0>
  {
    template<template<class...> class, int m, class state>
    using f = state;
  };

  template<>
  struct fold_left_xs_impl<1>
  {
    template<template<class...> class F, int m, class state, class... xs>
    using f = F<state, xs...>;
  };

  template<>
  struct fold_left_xs_impl<2>
  {
    template<template<class...> class F, int m, class state,
      class _1, class... xs>
    using f = F<F<state, _1, xs...>, xs...>;
  };

  template<>
  struct fold_left_xs_impl<3>
  {
    template<template<class...> class F, int m, class state,
      class _1, class _2, class... xs>
    using f = F<F<F<state, _1, _2, xs...>, _2, xs...>, xs...>;
  };

  // newline='\n'
  // for n in (4, 8, 16, 64):
  //   args = ', '.join(f'class _{i}' for i in range(1,n))
  //   ps = [f'_{i}, ' for i in range(1, n)]
  //   print(f'''
  //   template<>
  //   struct fold_left_xs_impl<{n}>
  //   {{
  //     template<template<class...> class F, int m, class state,
  //       {args}, class... xs>
  //     using f = typename fold_left_xs_impl<
  //       m-{n-1}
  //     >::template f<F, m-{n-1}, {'F<' * (n-1)}state{''.join(f',{newline}      {"".join(ps[i:])}xs...>' for i in range(n))};
  //   }};
  // ''', end='')

  template<>
  struct fold_left_xs_impl<4>
  {
    template<template<class...> class F, int m, class state,
      class _1, class _2, class _3, class... xs>
    using f = typename fold_left_xs_impl<
      m-3
    >::template f<F, m-3, F<F<F<state,
      _1, _2, _3, xs...>,
      _2, _3, xs...>,
      _3, xs...>,
      xs...>;
  };

  template<>
  struct fold_left_xs_impl<8>
  {
    template<template<class...> class F, int m, class state,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7, class... xs>
    using f = typename fold_left_xs_impl<
      m-7
    >::template f<F, m-7, F<F<F<F<F<F<F<state,
      _1, _2, _3, _4, _5, _6, _7, xs...>,
      _2, _3, _4, _5, _6, _7, xs...>,
      _3, _4, _5, _6, _7, xs...>,
      _4, _5, _6, _7, xs...>,
      _5, _6, _7, xs...>,
      _6, _7, xs...>,
      _7, xs...>,
      xs...>;
  };

  template<>
  struct fold_left_xs_impl<16>
  {
    template<template<class...> class F, int m, class state,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13, class _14,
      class _15, class... xs>
    using f = typename fold_left_xs_impl<
      m-15
    >::template f<F, m-15, F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<state,
      _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _9, _10, _11, _12, _13, _14, _15, xs...>,
      _10, _11, _12, _13, _14, _15, xs...>,
      _11, _12, _13, _14, _15, xs...>,
      _12, _13, _14, _15, xs...>,
      _13, _14, _15, xs...>,
      _14, _15, xs...>,
      _15, xs...>,
      xs...>;
  };

  template<>
  struct fold_left_xs_impl<64>
  {
    template<template<class...> class F, int m, class state,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13,
      class _14, class _15, class _16, class _17, class _18, class _19,
      class _20, class _21, class _22, class _23, class _24, class _25,
      class _26, class _27, class _28, class _29, class _30, class _31,
      class _32, class _33, class _34, class _35, class _36, class _37,
      class _38, class _39, class _40, class _41, class _42, class _43,
      class _44, class _45, class _46, class _47, class _48, class _49,
      class _50, class _51, class _52, class _53, class _54, class _55,
      class _56, class _57, class _58, class _59, class _60, class _61,
      class _62, class _63,
      class... xs>
    using f = typename fold_left_xs_impl<
      m-63
    >::template f<F, m-63, F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<
                           F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<
                           F<F<F<F<F<F<F<F<F<F<F<
      state,
      _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16,
      _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31,
      _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46,
      _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61,
      _62, _63, xs...>,
      _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,
      _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32,
      _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47,
      _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,
      _63, xs...>,
      _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18,
      _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33,
      _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48,
      _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63,
      xs...>,
      _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19,
      _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34,
      _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49,
      _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,
      _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35,
      _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,
      _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35,
      _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21,
      _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36,
      _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51,
      _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22,
      _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37,
      _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52,
      _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23,
      _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38,
      _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53,
      _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24,
      _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39,
      _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54,
      _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25,
      _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40,
      _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55,
      _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26,
      _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41,
      _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
      _57, _58, _59, _60, _61, _62, _63, xs...>,
      _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27,
      _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42,
      _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57,
      _58, _59, _60, _61, _62, _63, xs...>,
      _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28,
      _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43,
      _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58,
      _59, _60, _61, _62, _63, xs...>,
      _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29,
      _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
      _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59,
      _60, _61, _62, _63, xs...>,
      _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,
      _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
      _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
      _61, _62, _63, xs...>,
      _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31,
      _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46,
      _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61,
      _62, _63, xs...>,
      _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32,
      _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47,
      _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,
      _63, xs...>,
      _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33,
      _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48,
      _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63,
      xs...>,
      _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34,
      _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49,
      _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35,
      _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36,
      _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51,
      _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37,
      _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52,
      _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38,
      _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53,
      _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39,
      _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54,
      _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40,
      _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55,
      _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41,
      _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
      _57, _58, _59, _60, _61, _62, _63, xs...>,
      _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42,
      _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57,
      _58, _59, _60, _61, _62, _63, xs...>,
      _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43,
      _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58,
      _59, _60, _61, _62, _63, xs...>,
      _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
      _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59,
      _60, _61, _62, _63, xs...>,
      _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
      _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
      _61, _62, _63, xs...>,
      _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46,
      _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61,
      _62, _63, xs...>,
      _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47,
      _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,
      _63, xs...>,
      _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48,
      _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63,
      xs...>,
      _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49,
      _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51,
      _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52,
      _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53,
      _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54,
      _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55,
      _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
      _57, _58, _59, _60, _61, _62, _63, xs...>,
      _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57,
      _58, _59, _60, _61, _62, _63, xs...>,
      _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58,
      _59, _60, _61, _62, _63, xs...>,
      _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59,
      _60, _61, _62, _63, xs...>,
      _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
      _61, _62, _63, xs...>,
      _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61,
      _62, _63, xs...>,
      _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,
      _63, xs...>,
      _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63,
      xs...>,
      _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _57, _58, _59, _60, _61, _62, _63, xs...>,
      _58, _59, _60, _61, _62, _63, xs...>,
      _59, _60, _61, _62, _63, xs...>,
      _60, _61, _62, _63, xs...>,
      _61, _62, _63, xs...>,
      _62, _63, xs...>,
      _63, xs...>,
      xs...>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<int_ OffsetEnd, class F, class C = identity>
  using partial_fold_left_xs_c = test_contract<
    mp::size<>,
    mp::partial_fold_left_xs_c<
      OffsetEnd,
      mp::monadic_xs<assume_binary_or_more<F>>,
      mp::monadic<assume_unary<C>>>>;

  template<class F, class C = identity>
  using fold_left_xs = test_contract<
    mp::size<>,
    mp::fold_left_xs<
      mp::monadic_xs<assume_binary_or_more<F>>,
      mp::monadic<assume_unary<C>>>>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(partial_fold_left_xs, (OffsetEnd), (F), (C, smp::identity),
  smp::partial_fold_left_xs_c<OffsetEnd::value, F, C>)


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, int_ OffsetEnd, class F, class C>
  struct _sfinae<sfinae, partial_fold_left_xs_c<OffsetEnd, F, C>>
  {
    using type = smp::partial_fold_left_xs_c<OffsetEnd, sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, fold_left_xs<F, C>>
  {
    using type = smp::fold_left_xs<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class F, class C = identity>
  using fold_right = test_contract<
    mp::size<>,
    mp::fold_right<
      mp::monadic0<assume_binary<F>>,
      mp::monadic<subcontract<C>>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, fold_right<F, C>>
  {
    using type = smp::fold_right<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct _fold_tree;

    template<uint_>
    struct _fold_balanced_tree;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Folds tree over a list using a binary predicate.
  /// recursively fold n/2 value to the left and the rest to the right.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<fold_tree::f<...xs[0..n/2]>, fold_tree::f<...xs[n/2..n]>>
  ///   \endcode
  /// \treturn \value
  /// \see fold_left, fold_right, fold_balanced_tree
  template<class F, class C = identity>
  struct fold_tree
  {
    template<class... xs>
    using f = typename detail::_fold_tree<
      detail::min(3, sizeof...(xs))
    >::template f<C, F, xs...>;
  };

  /// Folds tree over a list using a binary predicate.
  /// recursively fold (n+1)/2 value to the left and the rest to the right.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<fold_tree::f<...xs[0..(n+1)/2]>, fold_tree::f<...xs[n-(n+1)/2..n]>>
  ///   \endcode
  /// \treturn \value
  /// \see fold_left, fold_right, fold_tree
  template<class F, class C = identity>
  struct fold_balanced_tree
  {
    template<class... xs>
    using f = typename detail::_fold_balanced_tree<
      detail::min(3, sizeof...(xs))
    >::template f<C, F, xs...>;
  };

  namespace emp
  {
    template<class L, class F, class C = mp::identity>
    using fold_tree = unpack<L, mp::fold_tree<F, C>>;

    template<class L, class F, class C = mp::identity>
    using fold_balanced_tree = unpack<L, mp::fold_balanced_tree<F, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  // std::bit_ceil (c++20)
  constexpr uint_ bit_ceil(uint_ n)
  {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
  }

  template<>
  struct _fold_tree<0>
  {
    template<class C, class F>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  template<>
  struct _fold_tree<1>
  {
    template<class C, class F, class x>
    using f = JLN_MP_CALL_TRACE(C, x);
  };

  template<>
  struct _fold_tree<2>
  {
    template<class C, class F, class x, class y>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_CALL_TRACE(F, x, y));
  };

  template<class F, uint_>
  struct fold_tree_impl;

  template<class F>
  struct fold_tree_impl<F, 0>
  {
    template<class x>
    using f = x;
  };

  template<class F>
  struct fold_tree_impl<F, 1>
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(F, x, y);
  };

  template<class F, uint_ n>
  struct fold_tree_impl
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(F,
      typename take_front_c<n, fold_tree_impl<F, n/2>>::template f<xs...>,
      typename drop_front_c<n, fold_tree_impl<F, bit_ceil(sizeof...(xs)-n)/2>>::template f<xs...>
    );
  };

  template<>
  struct _fold_tree<3>
  {
    template<class C, class F, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename fold_tree_impl<F, bit_ceil(sizeof...(xs))/2>::template f<xs...>
    );
  };


  template<>
  struct _fold_balanced_tree<0>
  : _fold_tree<0>
  {};

  template<>
  struct _fold_balanced_tree<1>
  : _fold_tree<1>
  {};

  template<>
  struct _fold_balanced_tree<2>
  : _fold_tree<2>
  {};

  template<class F, uint_>
  struct fold_balanced_tree_impl;

  template<class F>
  struct fold_balanced_tree_impl<F, 1>
  {
    template<class x>
    using f = x;
  };

  template<class F>
  struct fold_balanced_tree_impl<F, 2>
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(F, x, y);
  };

  template<class F, uint_ n>
  struct fold_balanced_tree_impl
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(F,
      typename take_front_c<(n+1)/2, fold_balanced_tree_impl<F, (n+1)/2>>::template f<xs...>,
      typename drop_front_c<(n+1)/2, fold_balanced_tree_impl<F, n-(n+1)/2>>::template f<xs...>
    );
  };

  template<>
  struct _fold_balanced_tree<3>
  {
    template<class C, class F, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename fold_balanced_tree_impl<F, sizeof...(xs)>::template f<xs...>
    );
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class F, class C = identity>
  using fold_tree = contract<mp::fold_tree<
    mp::monadic_xs<assume_binary<F>>,
    mp::monadic_xs<subcontract<C>>>>;

  template<class F, class C = identity>
  using fold_balanced_tree = contract<mp::fold_balanced_tree<
    mp::monadic_xs<assume_binary<F>>,
    mp::monadic_xs<subcontract<C>>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, fold_tree<F, C>>
  {
    using type = smp::fold_tree<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, fold_balanced_tree<F, C>>
  {
    using type = smp::fold_balanced_tree<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class Cmp, class C = listify>
  using group_by = try_contract<mp::group_by<
    typename detail::optimize_try<try_<assume_binary<Cmp>>>::type,
    assume_lists<C>>>;

  template<class C = listify>
  using group = contract<mp::group<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, group_by<Cmp, C>>
  {
    using type = smp::group_by<sfinae<Cmp>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct _group_n;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a sequence by arbitrary size group.
  /// \post If `n <= 0`, then the result sequence is empty
  /// \semantics
  ///   \code
  ///   group_n<number<2>>::f<
  ///     void, void, int, void, void
  ///   > = list<
  ///     list<void, void>,
  ///     list<int, void>,
  ///     list<void>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<int_ n, class C = listify>
  struct group_n_c
  {
    template<class... xs>
    using f = typename detail::_group_n<sizeof...(xs) != 0 && 0 < n>
      ::template f<C, n, xs...>;
  };

  template<class n, class C = listify>
  using group_n = group_n_c<n::value, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using group_n = unpack<L, mp::group_n<n, C>>;

    template<class L, int_ n, class C = mp::listify>
    using group_n_c = unpack<L, mp::group_n_c<n, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<int_... i>
  struct _group_n_impl
  {
    template<class C, unsigned long long n, class... xs>
    using f = typename fold_right<lift_t<split_state>, unpack<pop_front<C>>>
      ::template f<
        list<list<>>,
        list<number<(i % n ? split_keep : split_before)>, xs>...
      >;
  };

  template<>
  struct _group_n<true>
  {
    template<class C, unsigned long long n, class... xs>
    using f = typename emp::make_int_sequence_v_c<
      sizeof...(xs), lift_c<_group_n_impl>
    >::template f<C, n, xs...>;
  };

  template<>
  struct _group_n<false>
  {
    template<class C, unsigned long long, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using group_n_c = contract<mp::group_n_c<n, assume_lists<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(group_n, (N), (C, smp::listify), smp::group_n_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, int_ n, class C>
  struct _sfinae<sfinae, group_n_c<n, C>>
  {
    using type = smp::group_n_c<n, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = listify>
  using numbers = contract<mp::numbers<assume_numbers<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, numbers<C>>
  {
    using type = smp::numbers<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = numbers<>>
  using make_int_sequence_v = try_contract<
    mp::make_int_sequence_v<subcontract<C>>>;

  template<class C = listify>
  using make_int_sequence = make_int_sequence_v<numbers<C>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, make_int_sequence_v<C>>
  {
    using type = smp::make_int_sequence_v<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::positive_number, make_int_sequence_v);
}
/// \endcond
namespace jln::mp
{
  /// \ingroup number

  /// Replaces each element of a \sequence by its corresponding index.
  /// \treturn \sequence
  template<class C = listify>
  using indices = size<make_int_sequence<C>>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using indices = unpack<L, mp::indices<C>>;
  }
} // namespace jln::mp
namespace jln::mp::smp
{
  template<class C = listify>
  using indices = contract<mp::indices<assume_numbers<C>>>;
}
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _intersperse;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Inserts a \value between each element of a \sequence.
  /// \treturn \list
  /// \see prefix, suffix
  template<class x, class C = listify>
  struct intersperse
  {
    template<class... xs>
    using f = typename detail::_intersperse<sizeof...(xs) ? 1 : 0>
      ::template f<C, x, xs...>;
  };

  namespace emp
  {
    template<class L, class x, class C = mp::listify>
    using intersperse = unpack<L, mp::intersperse<x, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<>
  struct _intersperse<0>
  {
    template<class C, class x>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  template<>
  struct _intersperse<1>
  {
    template<class C, class x, class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<pop_front<C>, list<x, xs>...>::type;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class x, class C = listify>
  using intersperse = contract<mp::intersperse<x, subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, intersperse<x, C>>
  {
    using type = smp::intersperse<x, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_ start, int_ stride, bool inc>
    struct _iota_v_c;
  }
  /// \endcond

  /// \ingroup number

  /// Generates a sequence of \int_.
  /// \treturn \sequence of \int_
  /// \see iota
  template<class C = numbers<>>
  struct iota_v
  {
    template<class start, class count, class stride = number<1>>
    using f = typename detail::_iota_v_c<start::value, stride::value, (count::value >= 0)>
      ::template f<C, count::value>;
  };

  /// \ingroup number

  /// Generates a sequence of \number.
  /// \treturn \sequence of number
  template<class C = listify>
  using iota = iota_v<numbers<C>>;

  namespace emp
  {
    template<int_ start, int_ count, int_ stride = 1, class C = mp::numbers<>>
    using iota_v_c = typename detail::_iota_v_c<start, stride, (count >= 0)>
      ::template f<C, count>;

    template<class start, class count, class stride = number<1>, class C = mp::numbers<>>
    using iota_v = iota_v_c<start::value, count::value, stride::value, C>;

    template<int_ start, int_ count, int_ stride = 1, class C = mp::listify>
    using iota_c = iota_v_c<start, count, stride, mp::numbers<C>>;

    template<class start, class count, class stride = number<1>, class C = mp::listify>
    using iota = iota_v_c<start::value, count::value, stride::value, mp::numbers<C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<int_ start, int_ stride, class C>
  struct _iota
  {
    template<int_... ns>
    using f = typename C::template f<(start + ns * stride)...>;
  };

  template<int_ start, int_ stride>
  struct _iota<start, stride, numbers<>>
  {
    template<int_... ns>
    using f = list<number<(start + ns * stride)>...>;
  };

  template<>
  struct _iota_v_c<0, 1, true>
  {
    template<class C, int_ count>
    using f = emp::make_int_sequence_v_c<count, C>;
  };

  template<int_ start, int_ stride, bool>
  struct _iota_v_c
  {
    template<class C, int_ count>
    using f = emp::make_int_sequence_v_c<
      (count < 0 ? -count : count),
      detail::_iota<start, (count < 0 ? -stride : stride), C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = listify>
  using iota = try_contract<mp::iota<assume_numbers<C>>>;

  template<class C = numbers<>>
  using iota_v = try_contract<mp::iota_v<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, iota_v<C>>
  {
    using type = smp::iota_v<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct _is_disjoint;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether \value in `seqs[0]` are disjoint from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \number
  /// \see is_disjoint, is_subset, is_subset_with
  template<class Equal = lift<std::is_same>, class C = identity>
  struct is_disjoint_with
  {
    template<class... seqs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::_is_disjoint<detail::min(3, sizeof...(seqs))>
      ::template f<JLN_MP_TRACE_F(Equal), seqs...>);
  };

  /// Checks whether \value in `seqs[0]` are disjoint from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \number
  /// \see is_disjoint_with, is_subset, is_subset_with
  template<class C = identity>
  using is_disjoint = is_disjoint_with<lift<std::is_same>, C>;

  namespace emp
  {
#ifdef JLN_MP_DOXYGENATING
    template<class L1, class L2, class C = mp::identity>
    using is_disjoint = typename is_disjoint<C>::template f<L1, L2>;

    template<class L1, class L2, class Equal = lift<std::is_same>, class C = mp::identity>
    using is_disjoint_with = typename is_disjoint_with<Equal, C>::template f<L1, L2>;
#endif
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class Pred>
  struct is_disjoint_impl
  {
    template<class... xs>
    using f = typename is_drop_while_continue<
      typename _drop_while<sizeof...(xs)>::template f<0, Pred, xs...>
    >::type;
  };

  template<class Equal, class... xs>
  struct _is_disjoint_of
  {
    template<class x>
    using f = typename is_drop_while_continue<
      typename _drop_until<sizeof...(xs)>::template f<0, push_back<x, Equal>, xs...>
    >::type;
  };

  template<>
  struct _is_disjoint<0>
  {
    template<class Equal, class... xs>
    using f = true_;
  };

  template<>
  struct _is_disjoint<1> : _is_disjoint<0>
  {};

  template<class Equal, class seq0>
  using to_is_disjoint_impl = is_disjoint_impl<
    typename _unpack<seq0>::template f<lift<_is_disjoint_of>, Equal>
  >;

  template<>
  struct _is_disjoint<2>
  {
    template<class Equal, class seq0, class seq1>
    using f = typename _unpack<seq1>
      ::template f<to_is_disjoint_impl<Equal, seq0>>;
  };

  template<>
  struct _is_disjoint<3>
  {
    template<class Equal, class seq0, class... seqs>
    using f = typename is_drop_while_continue<
      typename _drop_while<sizeof...(seqs)>::template f<
        0,
        unpack<to_is_disjoint_impl<Equal, seq0>>,
        seqs...
      >
    >::type;
  };
}

#ifndef JLN_MP_DOXYGENATING
namespace jln::mp::emp
{
  template<class L1, class L2, class C = mp::identity>
  using is_disjoint = typename C::template f<
    typename detail::_is_disjoint<2>::f<mp::lift<std::is_same>, L1, L2>
  >;

  template<class L1, class L2, class Equal = lift<std::is_same>, class C = mp::identity>
  using is_disjoint_with = typename C::template f<
    typename detail::_is_disjoint<2>::f<Equal, L1, L2>
  >;
}
#endif
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<class Equal>
  struct mk_smp_is_disjoint_with;

  template<class C, class F = listify>
  struct seqs_to_list;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = identity>
  using is_disjoint = try_contract<detail::seqs_to_list<mp::is_disjoint<assume_positive_number<C>>>>;

  template<class Equal = lift<std::is_same>, class C = identity>
  using is_disjoint_with = typename detail::mk_smp_is_disjoint_with<Equal>
    ::template f<assume_positive_number<C>>;
}


namespace jln::mp::smp
{
  template<class C>
  using unpack = try_contract<mp::unpack<subcontract<C>>>;

  template<class C>
  using unpack_append = try_contract<mp::unpack_append<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unpack<C>>
  {
    using type = smp::unpack<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unpack_append<C>>
  {
    using type = smp::unpack_append<sfinae<C>>;
  };


  template<>
  struct optimize_useless_unpack<smp::unpack<listify>>
  {
    using type = contract<identity>;
  };

  template<>
  struct optimize_useless_unpack<smp::unpack<smp::listify>>
  {
    using type = contract<identity>;
  };

  template<>
  struct optimize_useless_unpack<unpack<smp::listify>>
  {
    using type = contract<identity>;
  };

  template<>
  struct optimize_useless_unpack<smp::unpack_append<listify>>
  {
    using type = contract<identity>;
  };

  template<>
  struct optimize_useless_unpack<smp::unpack_append<smp::listify>>
  {
    using type = contract<identity>;
  };

  template<>
  struct optimize_useless_unpack<unpack_append<smp::listify>>
  {
    using type = contract<identity>;
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Equal, class C>
  struct _sfinae<sfinae, is_disjoint_with<Equal, C>>
  {
    using type = smp::is_disjoint_with<sfinae<Equal>, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_disjoint_with<lift<std::is_same>, C>>
  {
    using type = smp::is_disjoint<sfinae<C>>;
  };


  template<class C, class F>
  struct seqs_to_list
  {
    template<class... seqs>
    using f = typename C::template f<typename _unpack<seqs>::template f<F>...>;
  };


  template<class Pred>
  using smp_is_disjoint_impl = smp::drop_while<
    Pred, contract<mp::always<mp::false_>>, contract<mp::always<mp::true_>>
  >;

  template<class Equal, class... xs>
  struct smp_is_disjoint_of
  {
    template<class x>
    using f = typename smp::drop_until<
      contract<push_back<x, Equal>>,
      contract<always<false_>>,
      contract<always<true_>>
    >::template f<xs...>;
  };

  template<uint_>
  struct smp_is_disjoint_n;

  template<>
  struct smp_is_disjoint_n<0>
  {
    template<class Equal, class... xs>
    using f = true_;
  };

  template<>
  struct smp_is_disjoint_n<1>
  : try_<seqs_to_list<mp::always<true_>, mp::always<true_>>>
  {};

  template<class Equal, class seq0>
  using smp_to_is_disjoint_impl = smp::unpack<smp_is_disjoint_impl<
    typename smp::unpack<contract<lift<smp_is_disjoint_of>>>
    ::template f<seq0, Equal>
  >>;

  template<>
  struct smp_is_disjoint_n<2>
  {
    template<class Equal, class seq0, class seq1>
    using f = typename smp_to_is_disjoint_impl<Equal, seq0>
      ::template f<seq1>;
  };

  template<>
  struct smp_is_disjoint_n<3>
  {
    template<class Equal, class seq0, class... seqs>
    using f = typename smp_is_disjoint_impl<smp_to_is_disjoint_impl<Equal, seq0>>
      ::template f<seqs...>;
  };

  template<class Equal, class C>
  struct smp_is_disjoint_with
  {
    template<class... seqs>
    using f = typename C::template f<
      typename smp_is_disjoint_n<min(3, sizeof...(seqs))>
      ::template f<Equal, seqs...>
    >;
  };

  template<class Equal>
  struct mk_smp_is_disjoint_with
  {
    template<class C>
    using f = contract<smp_is_disjoint_with<
      smp::concepts::predicate<assume_binary<Equal>, mp::identity, violation>, C>>;
  };

  template<>
  struct mk_smp_is_disjoint_with<lift<std::is_same>>
  {
    template<class C>
    using f = smp::is_disjoint<C>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = identity>
  using as_bool = try_contract<mp::as_bool<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, as_bool<C>>
  {
    using type = smp::as_bool<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_>
    struct is_sorted_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks wheteher a \sequence is sorted.
  /// \treturn \number
  template<class Cmp = less<>, class C = identity>
  struct is_sorted
  {
    template<class... xs>
    using f = typename detail::is_sorted_impl<sizeof...(xs) < 3 ? sizeof...(xs) : 3>
      ::template f<C, Cmp, xs...>;
  };

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using is_sorted = unpack<L, mp::is_sorted<Cmp, C>>;
  }
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct pairwise_impl;
  }
  /// \endcond

  /// \ingroup group

  /// Returns successive overlapping pairs.
  /// \post If `sizeof...(xs) <= 1`, then the result sequence is empty
  /// \post If `sizeof...(xs) > 1`, then the number of 2-tuples is `sizeof...(xs) - 1`
  /// \semantics
  ///   \code
  ///   pairwise<>::f<a, b, c, d>
  ///   == list<
  ///     list<a, b>,
  ///     list<b, c>,
  ///     list<c, d>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see sliding, group_n
  template<class F = listify, class C = listify>
  struct pairwise_with
  {
    template<class... xs>
    using f = typename detail::pairwise_impl<rotate_c<-1>::f<xs...>>
      ::template f<C, JLN_MP_TRACE_F(F), xs...>
      ;
  };

  template<class C = listify>
  using pairwise = pairwise_with<listify, C>;

  namespace emp
  {
    template<class L, class F = mp::listify, class C = mp::listify>
    using pairwise_with = unpack<L, mp::pairwise_with<F, C>>;

    template<class L, class C = mp::listify>
    using pairwise = unpack<L, mp::pairwise<C>>;
  }
}

namespace jln::mp::detail
{
  template<class>
  struct pairwise_impl;

  template<class x, class... xs>
  struct pairwise_impl<list<x, xs...>>
  {
    template<class C, class F, class y, class... ys>
    using f = typename JLN_MP_TRACE_F(C)::template f<
      typename F::template f<xs, ys>...
    >;
  };

  template<class x>
  struct pairwise_impl<list<x>>
  {
    template<class C, class F, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  template<>
  struct pairwise_impl<list<>>
  {
    template<class C, class F>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };
}
/// \cond
namespace jln::mp::detail
{
  template<>
  struct is_sorted_impl<0>
  {
    template<class C, class Cmp, class...>
    using f = JLN_MP_CALL_TRACE(C, true_);
  };

  template<>
  struct is_sorted_impl<1> : is_sorted_impl<0>
  {};

  template<>
  struct is_sorted_impl<2>
  {
    template<class C, class Cmp, class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<bool{Cmp::template f<x, y>::value}>);
  };

  template<class F>
  struct bind_and_flip_2
  {
    template<class x, class y, class... xs>
    using f = typename F::template f<y, x>;
  };

  template<>
  struct is_sorted_impl<3>
  {
    template<class C, class Cmp, class... xs>
    using f = JLN_MP_CALL_TRACE(C, typename is_drop_while_continue<
      detail::drop_until_xs_call<
        sizeof...(xs)-1,
        bind_and_flip_2<JLN_MP_TRACE_F(Cmp)>, xs...
      >
    >::type);
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = identity>
  using is_sorted = contract<
    mp::if_<
      mp::size<mp::less_than_c<2>>,
      mp::always<true_, assume_positive_number<C>>,
      mp::if_<
        mp::size<mp::is<number<2>>>,
        mp::tee<assume_binary<Cmp>, as_bool<C>>,
        partial_drop_until_xs_c<
          -2,
          contract<detail::bind_and_flip_2<assume_binary<Cmp>>>,
          contract<mp::always<false_, assume_positive_number<C>>>,
          contract<mp::always<true_, assume_positive_number<C>>>
        >
      >
    >
  >;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, is_sorted<Cmp, C>>
  {
    using type = smp::is_sorted<sfinae<Cmp>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct _is_subset;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether \value in `seqs[0]` are subset from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \number
  /// \see is_subset
  template<class Equal = lift<std::is_same>, class C = identity>
  struct is_subset_with
  {
    template<class... seqs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::_is_subset<detail::min(3, sizeof...(seqs))>
      ::template f<JLN_MP_TRACE_F(Equal), seqs...>
    );
  };

  /// Checks whether \value in `seqs[0]` are subset from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \number
  /// \see is_subset_with
  template<class C = identity>
  using is_subset = is_subset_with<lift<std::is_same>, C>;

  namespace emp
  {
#ifdef JLN_MP_DOXYGENATING
    template<class L1, class L2, class C = mp::identity>
    using is_subset = typename is_subset<C>::template f<L1, L2>;

    template<class L1, class L2, class Equal = lift<std::is_same>, class C = mp::identity>
    using is_subset_with = typename is_subset_with<Equal, C>::template f<L1, L2>;
#endif
  }
}


namespace jln::mp
{
  /// \ingroup list

  /// Checks whether a sequence has no elements.
  /// \treturn \number
  template<class C = identity>
  using is_empty = size<not_<C>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using is_empty = unpack<L, mp::is_empty<C>>;
  }
}
/// \cond
namespace jln::mp::detail
{
  template<class Equal, class... xs>
  struct _is_subset_of
  {
    template<class x>
    using f = number<!is_drop_while_continue<
      typename _drop_until<sizeof...(xs)>::template f<0, push_back<x, Equal>, xs...>
    >::type::value>;
  };

  template<>
  struct _is_subset<0> : _is_disjoint<0>
  {};

  template<>
  struct _is_subset<1> : _is_disjoint<0>
  {};

  template<class Equal, class seq0>
  using to_is_subset_impl = is_disjoint_impl<
    typename _unpack<seq0>::template f<lift<_is_subset_of>, Equal>
  >;

  template<>
  struct _is_subset<2>
  {
    template<class Equal, class seq0, class seq1>
    using f = typename _unpack<seq1>
      ::template f<to_is_subset_impl<Equal, seq0>>;
  };

  template<>
  struct _is_subset<3>
  {
    template<class Equal, class seq0, class... seqs>
    using f = typename detail::is_drop_while_continue<
      typename _drop_while<sizeof...(seqs)>::template f<
        0,
        unpack<to_is_subset_impl<Equal, seq0>>,
        seqs...
    >>::type;
  };
}

#ifndef JLN_MP_DOXYGENATING
namespace jln::mp::emp
{
  template<class L1, class L2, class C = mp::identity>
  using is_subset = typename C::template f<
    typename detail::_is_subset<2>::f<mp::lift<std::is_same>, L1, L2>
  >;

  template<class L1, class L2, class Equal = lift<std::is_same>, class C = mp::identity>
  using is_subset_with = typename C::template f<
    typename detail::_is_subset<2>::f<Equal, L1, L2>
  >;
}
#endif
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<class Equal>
  struct mk_smp_is_subset_with;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = identity>
  using is_subset = try_contract<detail::seqs_to_list<mp::is_subset<assume_positive_number<C>>>>;

  template<class Equal = lift<std::is_same>, class C = identity>
  using is_subset_with = typename detail::mk_smp_is_subset_with<Equal>
    ::template f<assume_positive_number<C>>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Equal, class C>
  struct _sfinae<sfinae, is_subset_with<Equal, C>>
  {
    using type = smp::is_subset_with<sfinae<Equal>, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_subset_with<lift<std::is_same>, C>>
  {
    using type = smp::is_subset<sfinae<C>>;
  };


  template<class Equal, class... xs>
  struct smp_is_subset_of
  {
    template<class x>
    using f = typename smp::drop_until<
      contract<push_back<x, Equal>>,
      contract<always<true_>>,
      contract<always<false_>>
    >::template f<xs...>;
  };

  template<uint_>
  struct smp_is_subset_n;

  template<>
  struct smp_is_subset_n<0> : smp_is_disjoint_n<0>
  {};

  template<>
  struct smp_is_subset_n<1> : smp_is_disjoint_n<1>
  {};

  template<class Equal, class seq0>
  using smp_to_is_subset_impl = smp::unpack<smp_is_disjoint_impl<
    typename smp::unpack<contract<lift<smp_is_subset_of>>>
    ::template f<seq0, Equal>
  >>;

  template<>
  struct smp_is_subset_n<2>
  {
    template<class Equal, class seq0, class seq1>
    using f = typename smp_to_is_subset_impl<Equal, seq0>
      ::template f<seq1>;
  };

  template<>
  struct smp_is_subset_n<3>
  {
    template<class Equal, class seq0, class... seqs>
    using f = typename smp_is_disjoint_impl<smp_to_is_subset_impl<Equal, seq0>>
      ::template f<seqs...>;
  };

  template<class Equal, class C>
  struct smp_is_subset_with
  {
    template<class... seqs>
    using f = typename C::template f<
      typename smp_is_subset_n<min(3, sizeof...(seqs))>
      ::template f<Equal, seqs...>
    >;
  };

  template<class Equal>
  struct mk_smp_is_subset_with
  {
    template<class C>
    using f = contract<smp_is_subset_with<
      smp::concepts::predicate<assume_binary<Equal>, mp::identity, violation>, C>>;
  };

  template<>
  struct mk_smp_is_subset_with<lift<std::is_same>>
  {
    template<class C>
    using f = subcontract<smp::is_subset<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = listify>
  using unique = detail::sfinae<mp::unique<subcontract_barrier<C>>>;

  template<class Cmp = contract<mp::lift<std::is_same>>, class C = listify>
  using unique_if = detail::sfinae<mp::unique_if<
    assume_binary_barrier<Cmp>, subcontract_barrier<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<class C>
  struct smp_unique_continuation
  {
    using type = C;
  };

  template<>
  struct smp_unique_continuation<try_<unpack<lift<list>>>>
  {
    using type = mp::identity;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, push_front<list<>, fold_left<lift_t<_set_push_back>, C>>>
  {
    using type = contract<push_front<list<>, fold_left<
      lift_t<_set_push_back>, typename smp_unique_continuation<
        assume_unary<sfinae<C>>
      >::type
    >>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, push_front<list<>, fold_left<
    unpack<_set_cmp_push_back<JLN_MP_TRACE_F(contract<mp::lift<std::is_same>>)>>, C
  >>>
  {
    using type = contract<push_front<list<>, fold_left<
      lift_t<_set_push_back>, typename smp_unique_continuation<
        assume_unary<optimize_useless_unpack_t<sfinae<C>>>
      >::type
    >>>;
  };

  template<class Cmp>
  struct _smp_set_cmp_push_back
  {
    template<class x, class... xs>
    using f = typename conditional_c<
      smp::index_if<
        contract<push_back<x, Cmp>>,
        contract<identity>,
        contract<always<number<-1>>>
      >::template f<xs...>::value == -1
    >::template f<list<xs..., x>, list<xs...>>;
  };

  template<class C>
  struct smp_unique_if_continuation
  {
    using type = C;
  };

  template<>
  struct smp_unique_if_continuation<try_<unpack<lift<list>>>>
  {
    using type = contract<mp::identity>;
  };

  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, push_front<list<>, fold_left<
    unpack<_set_cmp_push_back<JLN_MP_TRACE_F(Cmp)>>, C
  >>>
  {
    using type = contract<push_front<list<>, smp::fold_left<
      contract<unpack<try_<_smp_set_cmp_push_back<
        JLN_MP_TRACE_F(assume_binary<sfinae<Cmp>>)
      >>>>,
      typename smp_unique_if_continuation<
        assume_unary<sfinae<C>>
      >::type
    >>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class Cmp, class C>
    struct mk_is_unique;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether no \values are identical.
  /// \treturn \number
  template<class C = identity>
  using is_unique = typename detail::mk_is_unique<lift<std::is_same>, C>::type;

  /// Checks whether no \values are identical.
  /// The search stops at the first value which is not unique.
  /// \treturn \number
  template<class Cmp = lift<std::is_same>, class C = identity>
  using is_unique_if = typename detail::mk_is_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using is_unique = unpack<L, is_unique<C>>;

    template<class L, class Cmp = lift<std::is_same>, class C = mp::identity>
    using is_unique_if = unpack<L, is_unique_if<Cmp, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class C>
  struct is_unique_impl
  {
    template<class... xs>
#if JLN_MP_MSVC_LIKE
    // workaround for MSVC which has a broken EBO
    using f = JLN_MP_CALL_TRACE(C, typename _is_set<xs...>::type);
#else
    using f = JLN_MP_CALL_TRACE(C,
      mp::number<sizeof(inherit<std::make_index_sequence<sizeof...(xs)>, xs...>) == 1>);
#endif
  };

  template<bool>
  struct is_unique_unpack_impl;

  template<>
  struct is_unique_unpack_impl<false>
  {
    template<class C, class seq, class... xs>
    using f = typename _unpack<seq>::template f<C, xs...>;
  };

  template<>
  struct is_unique_unpack_impl<true>
  {
    template<class C, class seq, class... xs>
    using f = void;
  };

  template<class C>
  struct is_unique_unpack
  {
    template<class seq, class... xs>
    using f = typename is_unique_unpack_impl<std::is_same<seq, void>::value>
      ::template f<C, seq, xs...>;
  };

  template<class Cmp>
  struct is_unique_set_cmp_push_back_or_void
  {
    template<class x, class... xs>
    using f = typename conditional_c<
      index_if<push_back<x, Cmp>, identity, always<number<-1>>>::template f<xs...>::value == -1
    >::template f<list<xs..., x>, void>;
  };

  template<class Cmp, class C>
  struct mk_is_unique
  {
    using type = push_front<list<>, fold_left<
      is_unique_unpack<is_unique_set_cmp_push_back_or_void<JLN_MP_TRACE_F(Cmp)>>,
      is_not<void, C>
    >>;
  };

  template<class C>
  struct mk_is_unique<lift<std::is_same>, C>
  {
    using type = is_unique_impl<C>;
  };

  template<class C>
  struct mk_is_unique<lift_t<std::is_same>, C>
  : mk_is_unique<lift<std::is_same>, C>
  {};

  template<class C>
  struct mk_is_unique<same<>, C>
  : mk_is_unique<lift<std::is_same>, C>
  {};
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = identity>
  using is_unique = contract<mp::is_unique<assume_positive_number<C>>>;

  template<class Cmp = contract<mp::lift<std::is_same>>, class C = identity>
  using is_unique_if = detail::sfinae<mp::is_unique_if<
    assume_binary_barrier<Cmp>, assume_positive_number_barrier<C>>>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_unique_impl<C>>
  {
    using type = smp::is_unique<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, push_front<list<>, fold_left<
    is_unique_unpack<is_unique_set_cmp_push_back_or_void<
      JLN_MP_TRACE_F(contract<mp::lift<std::is_same>>)
    >>, C
  >>>
  {
    using type = smp::is_unique<sfinae<C>>;
  };

  template<class Cmp>
  struct smp_is_unique_set_cmp_push_back_or_void
  {
    template<class x, class... xs>
    using f = typename conditional_c<
      smp::index_if<
        contract<push_back<x, Cmp>>,
        contract<identity>,
        contract<always<number<-1>>>
      >::template f<xs...>::value == -1
    >::template f<list<xs..., x>, void>;
  };

  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, push_front<list<>, fold_left<
    is_unique_unpack<is_unique_set_cmp_push_back_or_void<JLN_MP_TRACE_F(Cmp)>>,
    is_not<void, C>
  >>>
  {
    using type = contract<push_front<list<>, smp::fold_left<
      contract<is_unique_unpack<try_<smp_is_unique_set_cmp_push_back_or_void<
        JLN_MP_TRACE_F(assume_binary<sfinae<Cmp>>)
      >>>>,
      contract<is_not<void, assume_unary<sfinae<C>>>>
    >>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = identity>
  using front = try_contract<mp::front<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, front<C>>
  {
    using type = smp::front<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary_or_more, front);
}
/// \endcond
namespace jln::mp::smp
{
  template<int_ n, class C = identity>
  using at_c = detail::sfinae<mp::at_c<n, subcontract_barrier<C>>>;

  template<class C = identity>
  using at0 = detail::sfinae<mp::at0<subcontract_barrier<C>>>;

  template<class C = identity>
  using at1 = detail::sfinae<mp::at1<subcontract_barrier<C>>>;

  template<class C = identity>
  using at2 = detail::sfinae<mp::at2<subcontract_barrier<C>>>;

  template<class C = identity>
  using at3 = detail::sfinae<mp::at3<subcontract_barrier<C>>>;

  template<class C = identity>
  using at4 = detail::sfinae<mp::at4<subcontract_barrier<C>>>;

  template<class C = identity>
  using at5 = detail::sfinae<mp::at5<subcontract_barrier<C>>>;

  template<class C = identity>
  using at6 = detail::sfinae<mp::at6<subcontract_barrier<C>>>;

  template<class C = identity>
  using at7 = detail::sfinae<mp::at7<subcontract_barrier<C>>>;

  template<class C = identity>
  using at8 = detail::sfinae<mp::at8<subcontract_barrier<C>>>;

  template<class C = identity>
  using at9 = detail::sfinae<mp::at9<subcontract_barrier<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(at, (N), (C, smp::identity), smp::at_c<N::value, C>)
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class, class>
    struct _mismatch;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Returns mismatching info of elements from two sequences.
  /// Uses \c C when a element mismatch and \c NC when one of
  /// the sequences equals the start of the other.
  /// \semantics
  ///   `NC::f<number<-1>, number<emp::size<seq1>>>` if \c seq1 == \c seq2.
  ///   `NC::f<number<i>, number<-1>>` if \c seq2 starts with \c seq1.
  ///   `NC::f<number<i>, number<1>>` if \c seq1 starts with \c seq2.
  ///   otherwise `C::f<number<i>, number<0>>`.
  /// \treturn pair or \number
  template<class Cmp = equal<>, class C = listify, class NC = C>
  struct mismatch
  {
    template<class seq1, class seq2>
    using f = typename detail::_mismatch<seq1, seq2>::template f<JLN_MP_TRACE_F(Cmp), C, NC>;
  };

  namespace emp
  {
    template<class seq1, class seq2, class Cmp = mp::equal<>, class C = mp::listify, class NC = C>
    using mismatch = typename mismatch<Cmp, C, NC>::template f<seq1, seq2>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class Cmp, int n>
  struct _mismatch_tree;

  template<class Cmp>
  struct _mismatch_tree<Cmp, 1>
  {
    struct type
    {
      template<class x, class y>
      using f = number<Cmp::template f<x, y>::value>;
    };
  };

  template<class Cmp>
  struct _mismatch_tree<Cmp, 2>
  {
    struct type
    {
      template<class x0, class x1, class y0, class y1>
      using f = number<
        !Cmp::template f<x0, y0>::value ? 0
      : !Cmp::template f<x1, y1>::value ? 1
      : 2
      >;
    };
  };

  template<class Cmp>
  struct _mismatch_tree<Cmp, 3>
  {
    struct type
    {
      template<class x0, class x1, class x2, class y0, class y1, class y2>
      using f = number<
        !Cmp::template f<x0, y0>::value ? 0
      : !Cmp::template f<x1, y1>::value ? 1
      : !Cmp::template f<x2, y2>::value ? 2
      : 3
      >;
    };
  };

  template<class Cmp>
  struct _mismatch_tree<Cmp, 4>
  {
    struct type
    {
      template<class x0, class x1, class x2, class x3, class y0, class y1, class y2, class y3>
      using f = number<
        !Cmp::template f<x0, y0>::value ? 0
      : !Cmp::template f<x1, y1>::value ? 1
      : !Cmp::template f<x2, y2>::value ? 2
      : !Cmp::template f<x3, y3>::value ? 3
      : 4
      >;
    };
  };

  constexpr int_ _mismatch_size(int n)
  {
    // is pow 2
    if ((-n ^ n) <  -n) {
      return n/2;
    }

    if (n > 0xffff) {
      return 0x10000;
    }

    // std::bit_floor (c++20)
    int r = 1;

    if (n > 0xff) {
      r <<= 8;
      n >>= 8;
    }

    if (n > 0xf) {
      r <<= 4;
      n >>= 4;
    }

    if (n > 0b11) {
      r <<= 2;
      n >>= 2;
    }

    return (n > 0b1) ? (r << 1) : r;
  }

  template<class Cmp, int_ n, int_ size = _mismatch_size(n)>
  struct _mismatch_tree_next
  {
    template<class i, class = void>
    struct dispatch
    {
      template<class...>
      using f = i;
    };

    template<class v>
    struct dispatch<number<size>, v>
    {
      template<class... xs>
      using f = number<size +
        drop_front_c<size,
          rotate_c<n-size,
            drop_front_c<size,
              typename _mismatch_tree<Cmp, n-size>::type
            >
          >
        >::template f<xs...>
      ::value>;
    };

    template<class... xs>
    using f = typename dispatch<
      typename rotate_c<size,
        drop_front_c<n-size,
          rotate_c<size,
            drop_front_c<n-size,
              typename _mismatch_tree<Cmp, size>::type
            >
          >
        >
      >::template f<xs...>
    >::template f<xs...>;
  };

  template<class Cmp, int n>
  struct _mismatch_tree
  {
    using type = _mismatch_tree_next<Cmp, n>;
  };

  template<
    template<class...> class Txs, class... xs,
    template<class...> class Tys, class... ys>
  struct _mismatch<Txs<xs...>, Tys<ys...>>
  {
    template<class i, class n>
    struct apply_index
    {
      template<class C, class NC, class, class>
      using f = JLN_MP_CALL_TRACE(C, i, number<0>);
    };

    template<class n>
    struct apply_index<n, n>
    {
      template<class C, class NC, class i, class r>
      using f = JLN_MP_CALL_TRACE(NC, i, r);
    };

    template<bool, bool>
    struct impl
    {
      template<class Cmp, class C, class NC>
      using f = typename apply_index<
        typename _mismatch_tree<Cmp, sizeof...(xs)>::type
        ::template f<xs..., ys...>,
        number<sizeof...(xs)>
      >::template f<C, NC, number<-1>, number<sizeof...(xs)>>;
    };

    template<bool b>
    struct impl<true, b>
    {
      template<class Cmp, class C, class NC>
      using f = typename apply_index<
        typename take_front_c<
          sizeof...(xs) * 2,
          typename _mismatch_tree<Cmp, sizeof...(xs)>::type
        >::template f<xs..., ys...>,
        number<sizeof...(xs)>
      >::template f<C, NC, number<sizeof...(xs)>, number<-1>>;
    };

    template<bool b>
    struct impl<b, true>
    {
      template<class Cmp, class C, class NC>
      using f = typename apply_index<
        typename take_front_c<
          sizeof...(ys) * 2,
          typename _mismatch_tree<Cmp, sizeof...(ys)>::type
        >::template f<ys..., xs...>,
        number<sizeof...(ys)>
      >::template f<C, NC, number<sizeof...(ys)>, number<1>>;
    };

    template<class Cmp, class C, class NC>
    using f = typename impl<
      (sizeof...(xs) < sizeof...(ys)),
      (sizeof...(ys) < sizeof...(xs))
    >::template f<Cmp, C, NC>;
  };

  template<
    template<class...> class Txs,
    template<class...> class Tys, class... ys>
  struct _mismatch<Txs<>, Tys<ys...>>
  {
    template<class Cmp, class C, class NC>
    using f = JLN_MP_CALL_TRACE(NC, number<0>, number<-1>);
  };

  template<
    template<class...> class Txs, class... xs,
    template<class...> class Tys>
  struct _mismatch<Txs<xs...>, Tys<>>
  {
    template<class Cmp, class C, class NC>
    using f = JLN_MP_CALL_TRACE(NC, number<0>, number<1>);
  };

  template<template<class...> class Txs, template<class...> class Tys>
  struct _mismatch<Txs<>, Tys<>>
  {
    template<class Cmp, class C, class NC>
    using f = JLN_MP_CALL_TRACE(NC, number<-1>, number<0>);
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<class Cmp, class C, class NC>
  struct _smp_mismatch;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Cmp = equal<>, class C = listify, class NC = C>
  using mismatch = try_contract<detail::_smp_mismatch<
    assume_binary<Cmp>, assume_numbers<C>, assume_numbers<NC>>>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C, class NC>
  struct _sfinae<sfinae, mismatch<Cmp, C, NC>>
  {
    using type = smp::mismatch<sfinae<Cmp>, sfinae<C>, sfinae<NC>>;
  };

  template<class C>
  struct _smp_mismatch_check
  {
    template<class i, class direction, class = void>
    struct f
    {
      template<class Cmp, class seq1, class seq2>
      using impl = typename C::template f<i, direction>;
    };

    template<class i>
    struct f<i, number<0>, std::enable_if_t<(i::value != -1)>>
    {
      template<class Cmp, class seq1, class seq2>
      using impl = typename conditional<
        typename smp::concepts::predicate<Cmp, mp::always<true_>>
        ::template f<emp::at<seq1, i>, emp::at<seq2, i>>
      >::template f<C, violation>
      ::template f<i, number<0>>;
    };
  };

  template<class Cmp, class C, class NC>
  struct _smp_mismatch
  {
    template<class seq1, class seq2>
    using f = typename mismatch<
      smp::concepts::predicate<Cmp>,
      _smp_mismatch_check<C>,
      _smp_mismatch_check<NC>
    >
    ::template f<seq1, seq2>
    ::template impl<Cmp, seq1, seq2>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class, class>
    struct _lexicographical_compare;

    template<class Cmp>
    struct _lexicographical_compare_equal;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks if \c seq1  is lexicographically less than \c seq2.
  /// \treturn \bool
  template<class Cmp = less<>, class C = identity>
  struct lexicographical_compare
  {
    template<class seq1, class seq2>
    using f = JLN_MP_CALL_TRACE(C,
      typename mismatch<
        detail::_lexicographical_compare_equal<JLN_MP_TRACE_F(Cmp)>,
        lift<detail::_lexicographical_compare>
      >
      ::template f<seq1, seq2>
      ::template f<JLN_MP_TRACE_F(Cmp), seq1, seq2>
    );
  };

  template<class CmpLess = less<>, class CmpEq = equal<>, class C = identity>
  struct lexicographical_compare2
  {
    template<class seq1, class seq2>
    using f = JLN_MP_CALL_TRACE(C,
      typename mismatch<JLN_MP_TRACE_F(CmpEq), lift<detail::_lexicographical_compare>>
      ::template f<seq1, seq2>
      ::template f<JLN_MP_TRACE_F(CmpLess), seq1, seq2>
    );
  };

  namespace emp
  {
    template<class seq1, class seq2, class Cmp = mp::less<>, class C = mp::identity>
    using lexicographical_compare = typename lexicographical_compare<Cmp, C>
      ::template f<seq1, seq2>;

    template<
      class seq1, class seq2,
      class CmpLess = mp::less<>, class CmpEq = mp::equal<>, class C = mp::identity>
    using lexicographical_compare2 = typename lexicographical_compare2<CmpLess, CmpEq, C>
      ::template f<seq1, seq2>;
  }

  /// \cond
  template<class Cmp>
  struct lexicographical_compare<Cmp, identity>
  {
    template<class seq1, class seq2>
    using f = typename mismatch<
      detail::_lexicographical_compare_equal<Cmp>,
      lift<detail::_lexicographical_compare>
    >
    ::template f<seq1, seq2>
    ::template f<Cmp, seq1, seq2>;
  };

  template<class CmpLess, class CmpEq>
  struct lexicographical_compare2<CmpLess, CmpEq, identity>
  {
    template<class seq1, class seq2>
    using f = typename mismatch<CmpEq, lift<detail::_lexicographical_compare>>
      ::template f<seq1, seq2>
      ::template f<CmpLess, seq1, seq2>;
  };
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct _lexicographical_compare_equal
  {
    template<class x, class y>
    using f = number<!Cmp::template f<x, y>::value && !Cmp::template f<y, x>::value>;
  };

  template<class i, class n>
  struct _lexicographical_compare
  {
    template<class Cmp, class seq1, class seq2>
    using f = false_;
  };

  template<>
  struct _lexicographical_compare<number<-1>, number<0>>
  {
    template<class Cmp, class seq1, class seq2>
    using f = false_;
  };

  template<class i>
  struct _lexicographical_compare<i, number<0>>
  {
    template<class Cmp, class seq1, class seq2>
    using f = typename Cmp::template f<emp::at<seq1, i>, emp::at<seq2, i>>;
  };

  template<class i>
  struct _lexicographical_compare<i, number<-1>>
  {
    template<class Cmp, class seq1, class seq2>
    using f = true_;
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<class Cmp, class C>
  struct _smp_lexicographical_compare;

  template<class CmpLess, class CmpEq, class C>
  struct _smp_lexicographical_compare2;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = identity>
  using lexicographical_compare = try_contract<detail::_smp_lexicographical_compare<
    assume_binary<Cmp>, assume_positive_number<C>>>;

  template<class CmpLess = less<>, class CmpEq = equal<>, class C = identity>
  using lexicographical_compare2 = try_contract<detail::_smp_lexicographical_compare2<
    assume_binary<CmpLess>, assume_binary<CmpEq>, assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, lexicographical_compare<Cmp, C>>
  {
    using type = smp::lexicographical_compare<sfinae<Cmp>, sfinae<C>>;
  };

  template<template<class> class sfinae, class CmpLess, class CmpEq, class C>
  struct _sfinae<sfinae, lexicographical_compare2<CmpLess, CmpEq, C>>
  {
    using type = smp::lexicographical_compare2<sfinae<CmpLess>, sfinae<CmpEq>, sfinae<C>>;
  };

  template<class Cmp, class C>
  struct _smp_lexicographical_compare
  {
    template<class seq1, class seq2>
    using f = typename monadic<C>::template f<
      typename mismatch<
        _lexicographical_compare_equal<
          smp::concepts::predicate<Cmp, mp::identity, mp::always<true_>>
        >,
        lift<_lexicographical_compare>
      >
      ::template f<seq1, seq2>
      ::template f<smp::concepts::predicate<Cmp, mp::identity, violation>, seq1, seq2>
    >;
  };

  template<class Cmp>
  struct _smp_lexicographical_compare<Cmp, identity>
  {
    template<class seq1, class seq2>
    using f = typename mismatch<
      _lexicographical_compare_equal<
        smp::concepts::predicate<Cmp, mp::identity, mp::always<true_>>
      >,
      lift<_lexicographical_compare>
    >
    ::template f<seq1, seq2>
    ::template f<smp::concepts::predicate<Cmp, mp::identity, violation>, seq1, seq2>;
  };

  template<class CmpLess, class CmpEq, class C>
  struct _smp_lexicographical_compare2
  {
    template<class seq1, class seq2>
    using f = typename monadic<C>::template f<
      typename mismatch<
        smp::concepts::predicate<CmpEq>,
        lift<_lexicographical_compare>
      >
      ::template f<seq1, seq2>
      ::template f<
        if_<
          smp::concepts::predicate<CmpEq, mp::always<true_>>,
          CmpLess,
          violation
        >,
        seq1, seq2
      >
    >;
  };

  template<class CmpLess, class CmpEq>
  struct _smp_lexicographical_compare2<CmpLess, CmpEq, identity>
  {
    template<class seq1, class seq2>
    using f = typename mismatch<
      smp::concepts::predicate<CmpEq>,
      lift<_lexicographical_compare>
    >
    ::template f<seq1, seq2>
    ::template f<
      if_<
        smp::concepts::predicate<CmpEq, mp::always<true_>>,
        CmpLess,
        violation
      >,
      seq1, seq2
    >;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _lower_bound;

    constexpr int _lower_bound_select(unsigned n);

    template<class>
    struct optimize_cmp;
  }
  /// \endcond

  /// \ingroup search

  /// Finds first element that is not less than (i.e. greater or equal to) \c x.
  /// Calls \c FC with all the elements since the one found at the end.
  /// If no element is found, \c NFC is used.
  /// \pre \c is_sorted<Cmp>::f<xs...>
  /// \treturn \sequence
  template<class x, class Cmp = less<>, class C = listify, class NC = C>
  struct lower_bound
  {
    template<class... xs>
    using f = typename detail::_lower_bound<
      detail::_lower_bound_select(sizeof...(xs))
    >::template f<
      sizeof...(xs),
      push_back<x, JLN_MP_TRACE_F(typename detail::optimize_cmp<Cmp>::type)>,
      C, NC, xs...>;
  };

  template<int_ x, class Cmp = less<>, class C = listify, class NC = C>
  using lower_bound_c = lower_bound<number<x>, Cmp, C, NC>;

  template<class x, class C = listify, class NC = C>
  using lower_bound_than = lower_bound<x, less<>, C, NC>;

  template<int_ x, class C = listify, class NC = C>
  using lower_bound_than_c = lower_bound<number<x>, less<>, C, NC>;

  namespace emp
  {
    template<class L, class x, class Cmp = mp::less<>, class C = mp::listify, class NC = C>
    using lower_bound = unpack<L, mp::lower_bound<x, Cmp, C, NC>>;

    template<class L, int_ x, class Cmp = mp::less<>, class C = mp::listify, class NC = C>
    using lower_bound_c = unpack<L, mp::lower_bound<mp::number<x>, Cmp, C, NC>>;

    template<class L, class x, class C = mp::listify, class NC = C>
    using lower_bound_than = unpack<L, mp::lower_bound<x, mp::less<>, C, NC>>;

    template<class L, int_ x, class C = mp::listify, class NC = C>
    using lower_bound_than_c = unpack<L, mp::lower_bound<mp::number<x>, mp::less<>, C, NC>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct optimize_cmp
  {
    using type = Cmp;
  };

  template<class Cmp>
  struct optimize_cmp<flip<tee<less<Cmp>, not_<>>>>
  {
    using type = flip<less<not_<Cmp>>>;
  };

  template<class Cmp, class C>
  struct optimize_cmp<flip<tee<flip<Cmp>, C>>>
  : optimize_cmp<tee<Cmp, C>>
  {};

  template<class C>
  struct optimize_cmp<tee<less<>, C>>
  {
    using type = less<C>;
  };

  template<int>
  struct _smp_lower_bound;

  template<class Bool>
  struct _smp_conditional;

  template<>
  struct _smp_conditional<na>
  {
    template<class C, class NC>
    using f = violation;
  };

  template<>
  struct _smp_conditional<true_>
  {
    template<class C, class NC>
    using f = C;
  };

  template<>
  struct _smp_conditional<false_>
  {
    template<class C, class NC>
    using f = NC;
  };

  struct _lower_bound_violation2
  {
    template<unsigned, class...>
    using f = na;
  };

  template<class Bool>
  struct _smp_conditional2;

  template<>
  struct _smp_conditional2<na>
  {
    template<class C, class NC>
    using f = _lower_bound_violation2;
  };

  template<>
  struct _smp_conditional2<true_>
  {
    template<class C, class NC>
    using f = C;
  };

  template<>
  struct _smp_conditional2<false_>
  {
    template<class C, class NC>
    using f = NC;
  };

  constexpr int _lower_bound_select(unsigned n)
  {
    return
      n < 2 ? -int(n)
    : n < 4 ? 2
    : n < 8 ? 4
    : n < 16 ? 8
    : n < 32 ? 16
    : n < 64 ? 32
    : n < 128 ? 64
    : n < 256 ? 128
    : 256
    ;
  }

#define JLN_MP_LOWER_BOUND_IMPL(prefix, Cond)                \
  template<>                                                 \
  struct prefix##lower_bound<0>                              \
  {                                                          \
    template<unsigned n, class Pred, class C, class NC,      \
      class... xs>                                           \
    using f = JLN_MP_CALL_TRACE_0_ARG(NC);                   \
  };                                                         \
                                                             \
  /* original size == 1 */                                   \
  template<>                                                 \
  struct prefix##lower_bound<-1>                             \
  {                                                          \
    template<unsigned n, class Pred, class C, class NC,      \
      class x>                                               \
    using f = JLN_MP_CALL_TRACE_T(JLN_MP_IDENT(Cond(x)       \
      ::template f<_cartesian<NC, 0> /* for NC::f<> */, C>), \
      x);                                                    \
  };                                                         \
                                                             \
  template<>                                                 \
  struct prefix##lower_bound<1>                              \
  {                                                          \
    template<unsigned n, class Pred, class C, class NC,      \
      class x, class... xs>                                  \
    using f = JLN_MP_CALL_TRACE_T(JLN_MP_IDENT(Cond(x)       \
      ::template f<pop_front<C>, C>),                        \
      x, xs...);                                             \
  };

#define JLN_MP_LOWER_BOUND_PRED_CALL(x) \
  conditional_c<Pred::template f<x>::value>

#define JLN_MP_LOWER_BOUND_SMP_PRED_CALL(x) \
  _smp_conditional<typename Pred::template f<x>>

  JLN_MP_LOWER_BOUND_IMPL(_, JLN_MP_LOWER_BOUND_PRED_CALL)
  JLN_MP_LOWER_BOUND_IMPL(_smp_, JLN_MP_LOWER_BOUND_SMP_PRED_CALL)

#undef JLN_MP_LOWER_BOUND_IMPL

  template<unsigned> struct _lower_bound_drop_front;
  template<unsigned> struct _smp_lower_bound_drop_front;

#define JLN_MP_LOWER_BOUND_IMPL2(prefix, Cond, n, mp_xs) \
  template<>                                             \
  struct prefix##lower_bound_drop_front<n>               \
  {                                                      \
    template<int count, class Pred, class C, class NC,   \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),            \
      class... xs>                                       \
    using f = typename detail::prefix##lower_bound<      \
      _lower_bound_select(count-n)                       \
    >::template f<count-n, Pred, C, NC, xs...>;          \
  };                                                     \
                                                         \
  template<>                                             \
  struct prefix##lower_bound<n>                          \
  {                                                      \
    template<int count, class Pred, class C, class NC,   \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),            \
      class... xs>                                       \
    using f = typename Cond(_##n)::template f<           \
      prefix##lower_bound_drop_front<n>,                 \
      prefix##lower_bound<n/2>                           \
    >::template f<count, Pred, C, NC,                    \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),       \
      xs...                                              \
    >;                                                   \
  };

#undef JLN_MP_LOWER_BOUND_SMP_PRED_CALL
#define JLN_MP_LOWER_BOUND_SMP_PRED_CALL(x) \
  _smp_conditional2<typename Pred::template f<x>>

#define JLN_MP_LOWER_BOUND_IMPL(n, mp_xs, mp_rxs, mp_rep)             \
  JLN_MP_LOWER_BOUND_IMPL2(_, JLN_MP_LOWER_BOUND_PRED_CALL, n, mp_xs) \
  JLN_MP_LOWER_BOUND_IMPL2(_smp_, JLN_MP_LOWER_BOUND_SMP_PRED_CALL, n, mp_xs)

  JLN_MP_GEN_XS_2_4_8_16_32_64_128_256(JLN_MP_LOWER_BOUND_IMPL)

#undef JLN_MP_LOWER_BOUND_IMPL
#undef JLN_MP_LOWER_BOUND_PRED_CALL
#undef JLN_MP_LOWER_BOUND_SMP_PRED_CALL
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<class x, class Cmp, class C, class NC>
  struct _smp_lower_bound_impl;
}
/// \endcond

namespace jln::mp::smp
{
  template<class x, class Cmp, class C = listify, class NC = C>
  using lower_bound = contract<detail::_smp_lower_bound_impl<
    x, concepts::strong_predicate_or<assume_binary<Cmp>, violation>,
    subcontract<C>, subcontract<NC>>>;

  template<int_ x, class Cmp = less<>, class C = listify, class NC = C>
  using lower_bound_c = lower_bound<number<x>, Cmp, C, NC>;

  template<class x, class C = listify, class NC = C>
  using lower_bound_than = lower_bound<x, less<>, C, NC>;

  template<int_ x, class C = listify, class NC = C>
  using lower_bound_than_c = lower_bound<number<x>, less<>, C, NC>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class Cmp, class C, class NC>
  struct _sfinae<sfinae, lower_bound<x, Cmp, C, NC>>
  {
    using type = smp::lower_bound<x, sfinae<Cmp>, sfinae<C>, sfinae<NC>>;
  };

  template<class x, class Cmp, class C, class NC>
  struct _smp_lower_bound_impl
  {
    template<class... xs>
    using f = typename detail::_smp_lower_bound<
      detail::_lower_bound_select(sizeof...(xs))
    >::template f<sizeof...(xs), push_back<x, Cmp>, C, NC, xs...>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup value

#if __cplusplus >= 201703L
# if !JLN_MP_ENABLE_DEBUG || JLN_MP_CLANG_LIKE
  template<auto v>
  struct val
  {
    static constexpr decltype(v) value = v;
  };

  template<class T, T v>
  using typed_val = val<v>;
# else
  template<class T, T v>
  struct typed_val
  {
    static constexpr T const value = v;
  };

  template<auto v>
  using val = typed_val<std::remove_const_t<decltype(v)>, v>;
# endif
#else
  template<class T, T v>
  struct typed_val
  {
    static constexpr T const value = v;
  };
#endif
}
namespace jln::mp
{
  /// \ingroup functional

  /// Invoking \c F with its last parameters bound to bound to args.
  /// \semantics
  ///   \code
  ///   bind_back<F, c, d>::f<a, b> == F<a, b, c, d>
  ///   \endcode
  /// \treturn \sequence
  /// \see bind_front, capture_back, capture_front
  template<class F, class... BoundArgs>
  struct bind_back
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, F, xs..., BoundArgs...);
  };

  template<class F, int_... BoundArgs>
  using bind_back_c = bind_back<F, number<BoundArgs>...>;

#if JLN_MP_ENABLE_TPL_AUTO
  template<class F, auto... BoundArgs>
  using bind_back_v = bind_back<F, val<BoundArgs>...>;
#endif

  namespace emp
  {
    template<class L, class F, class... BoundArgs>
    using bind_back = unpack<L, mp::bind_back<F, BoundArgs...>>;

    template<class L, class F, int_... BoundArgs>
    using bind_back_c = unpack<L, mp::bind_back_c<F, BoundArgs...>>;

#if JLN_MP_ENABLE_TPL_AUTO
    template<class L, class F, auto... BoundArgs>
    using bind_back_v = unpack<L, mp::bind_back_v<F, BoundArgs...>>;
#endif
  }
} // namespace jln::mp
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class FillValue, class F, class EvenSizeF, class C, int_ max, class... ns>
    using matrix_longest_each_impl = _each<
      C,
      typename conditional_c<max != ns::value>
      ::template f<
        typename repeat_c<max - ns::value, F>::template f<FillValue>,
        EvenSizeF
      >
    ...>;

    constexpr int_ max_lengths(std::initializer_list<int_> l);

    template<class FillValue, class F, class EvenSizeF, class C, class... ns>
    using matrix_longest_impl = matrix_longest_each_impl<
      FillValue, F, EvenSizeF, C, max_lengths({ns::value...}), ns...>;
  }
  /// \endcond

  /// \ingroup group

  /// Fills a \sequence of \typelist to the longest size.
  /// \post `emp::size<result> == emp::max<emp::size<seqs>> && ...`
  /// \semantics
  ///   \code
  ///   left_matrix_longest_with<XX, listify>::f<
  ///     list<_1, _2>,
  ///     list<_1, _2, _3>,
  ///     list<_1, _2>,
  ///     list<_1, _2, _3, _4>
  ///   > = list<
  ///     list<XX, XX, _1, _2>,
  ///     list<XX, _1, _2, _3>,
  ///     list<XX, XX, _1, _2>,
  ///     list<_1, _2, _3, _4>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class FillValue, class F = listify, class C = listify>
  struct left_matrix_longest_with
  {
    template<class... seqs>
    using f = typename detail::matrix_longest_impl<
      FillValue,
      push_front<unpack<F>, lift<bind_back>>,
      typename detail::optimize_useless_unpack<unpack<F>>::type,
      C, unpack<size<>>::f<seqs>...
    >::template f<seqs...>;
  };

  template<class FillValue, class C = listify>
  using left_matrix_longest = left_matrix_longest_with<FillValue, listify, C>;

  /// Fills a \sequence of \typelist to the longest size.
  /// \post `emp::size<result> == emp::max<emp::size<seqs>> && ...`
  /// \semantics
  ///   \code
  ///   right_matrix_longest_with_matrix_longest_with<XX, listify>::f<
  ///     list<_1, _2>,
  ///     list<_1, _2, _3>,
  ///     list<_1, _2>,
  ///     list<_1, _2, _3, _4>
  ///   > = list<
  ///     list<_1, _2, XX, XX>,
  ///     list<_1, _2, _3, XX>,
  ///     list<_1, _2, XX, XX>,
  ///     list<_1, _2, _3, _4>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class FillValue, class F = listify, class C = listify>
  struct right_matrix_longest_with
  {
    template<class... seqs>
    using f = typename detail::matrix_longest_impl<
      FillValue,
      push_front<unpack_append<F>, lift<bind_back>>,
      typename detail::optimize_useless_unpack<unpack<F>>::type,
      C, unpack<size<>>::f<seqs>...
    >::template f<seqs...>;
  };

  template<class FillValue, class C = listify>
  using right_matrix_longest = right_matrix_longest_with<FillValue, listify, C>;

  namespace emp
  {
    template<class L, class FillValue, class F = mp::listify, class C = mp::listify>
    using left_matrix_longest_with = unpack<L, mp::left_matrix_longest_with<FillValue, F, C>>;

    template<class L, class FillValue, class C = mp::listify>
    using left_matrix_longest = unpack<L, mp::left_matrix_longest<FillValue, C>>;

    template<class L, class FillValue, class F = mp::listify, class C = mp::listify>
    using right_matrix_longest_with = unpack<L, mp::right_matrix_longest_with<FillValue, F, C>>;

    template<class L, class FillValue, class C = mp::listify>
    using right_matrix_longest = unpack<L, mp::right_matrix_longest<FillValue, C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  constexpr int_ max_lengths(std::initializer_list<int_> l)
  {
    int_ r = 0;
    for (int_ n : l) {
      if (n > r) {
        r = n;
      }
    }
    return r;
  }
}
/// \endcond
namespace jln::mp::smp
{
  template<class FillValue, class F = listify, class C = listify>
  using left_matrix_longest_with = try_contract<
    mp::left_matrix_longest_with<FillValue, subcontract<F>, monadic_xs<subcontract<C>>>>;

  template<class FillValue, class C = listify>
  using left_matrix_longest = left_matrix_longest_with<FillValue, listify, C>;

  template<class FillValue, class F = listify, class C = listify>
  using right_matrix_longest_with = try_contract<
    mp::right_matrix_longest_with<FillValue, subcontract<F>, monadic_xs<subcontract<C>>>>;

  template<class FillValue, class C = listify>
  using right_matrix_longest = right_matrix_longest_with<FillValue, listify, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class FillValue, class F, class C>
  struct _sfinae<sfinae, left_matrix_longest_with<FillValue, F, C>>
  {
    using type = smp::left_matrix_longest_with<FillValue, sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class FillValue, class F, class C>
  struct _sfinae<sfinae, right_matrix_longest_with<FillValue, F, C>>
  {
    using type = smp::right_matrix_longest_with<FillValue, sfinae<F>, sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT3(argument_category::lists, left_matrix_longest_with);
  JLN_MP_MAKE_EXPECTED_ARGUMENT3(argument_category::lists, right_matrix_longest_with);
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    constexpr int_ min_lengths(std::initializer_list<int_> l);

    template<
      template<unsigned, class> class Take,
      class F, class EvenSizeF, class C, int_ min, class... ns>
    using matrix_shortest_each_impl = _each<
      C,
      typename conditional_c<min != ns::value>
      ::template f<unpack<Take<min, F>>, EvenSizeF>
    ...>;

    template<
      template<unsigned, class> class Take,
      class F, class EvenSizeF, class C, class... ns>
    using matrix_shortest_impl = matrix_shortest_each_impl<
      Take, F, EvenSizeF, C, min_lengths({ns::value...}), ns...>;
  }
  /// \endcond

  /// \ingroup group

  /// Truncates a \sequence of \typelist to the smallest size.
  /// \post `emp::size<result> == emp::min<emp::size<seqs>> && ...`
  /// \semantics
  ///   \code
  ///   left_matrix_shortest_with<listify>::f<
  ///     list<_1, _2>,
  ///     list<_1, _2, _3>,
  ///     list<_1, _2>,
  ///     list<_1, _2, _3, _4>
  ///   > = list<
  ///     list<_1, _2>,
  ///     list<_1, _2>,
  ///     list<_1, _2>,
  ///     list<_1, _2>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class F = listify, class C = listify>
  struct left_matrix_shortest_with
  {
    template<class... seqs>
    using f = typename detail::matrix_shortest_impl<
      take_front_c,
      F, typename detail::optimize_useless_unpack<unpack<F>>::type,
      C, unpack<size<>>::f<seqs>...
    >::template f<seqs...>;
  };

  template<class C = listify>
  using left_matrix_shortest = left_matrix_shortest_with<listify, C>;

  /// Truncates a \sequence of \typelist to the smallest size.
  /// \post `emp::size<result> == emp::min<emp::size<seqs>> && ...`
  /// \semantics
  ///   \code
  ///   right_matrix_shortest_with<listify>::f<
  ///     list<_1, _2>,
  ///     list<_1, _2, _3>,
  ///     list<_1, _2>,
  ///     list<_1, _2, _3, _4>
  ///   > = list<
  ///     list<_1, _2>,
  ///     list<_2, _3>,
  ///     list<_1, _2>,
  ///     list<_3, _4>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class F = listify, class C = listify>
  struct right_matrix_shortest_with
  {
    template<class... seqs>
    using f = typename detail::matrix_shortest_impl<
      take_back_c,
      F, typename detail::optimize_useless_unpack<unpack<F>>::type,
      C, unpack<size<>>::f<seqs>...
    >::template f<seqs...>;
  };

  template<class C = listify>
  using right_matrix_shortest = right_matrix_shortest_with<listify, C>;


  namespace emp
  {
    template<class L, class F = mp::listify, class C = mp::listify>
    using left_matrix_shortest_with = unpack<L, mp::left_matrix_shortest_with<F, C>>;

    template<class L, class C = mp::listify>
    using left_matrix_shortest = unpack<L, mp::left_matrix_shortest<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using right_matrix_shortest_with = unpack<L, mp::right_matrix_shortest_with<F, C>>;

    template<class L, class C = mp::listify>
    using right_matrix_shortest = unpack<L, mp::right_matrix_shortest<C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  constexpr int_ min_lengths(std::initializer_list<int_> l)
  {
    if (l.size()) {
      auto first = l.begin();
      auto last = l.end();

      int_ r = *first++;
      for (; first != last; ++first) {
        if (*first < r) {
          r = *first;
        }
      }

      return r;
    }

    return 0;
  }
}
/// \endcond
namespace jln::mp::smp
{
  template<class F = listify, class C = listify>
  using left_matrix_shortest_with = try_contract<
    mp::left_matrix_shortest_with<subcontract<F>, monadic_xs<subcontract<C>>>>;

  template<class C = listify>
  using left_matrix_shortest = left_matrix_shortest_with<listify, C>;

  template<class F = listify, class C = listify>
  using right_matrix_shortest_with = try_contract<
    mp::right_matrix_shortest_with<subcontract<F>, monadic_xs<subcontract<C>>>>;

  template<class C = listify>
  using right_matrix_shortest = right_matrix_shortest_with<listify, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, left_matrix_shortest_with<F, C>>
  {
    using type = smp::left_matrix_shortest_with<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, right_matrix_shortest_with<F, C>>
  {
    using type = smp::right_matrix_shortest_with<sfinae<F>, sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT2(argument_category::lists, left_matrix_shortest_with);
  JLN_MP_MAKE_EXPECTED_ARGUMENT2(argument_category::lists, right_matrix_shortest_with);
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class L, class Seq1, class Seq2, class Cmp>
    struct merge_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Merges two \list into one sorted \sequence.
  /// \pre `emp::is_sorted<seq1, Cmp>`
  /// \pre `emp::is_sorted<seq2, Cmp>`
  /// \post \c emp::is_sorted<result...>
  /// \treturn \sequence
  template<class Cmp = less<>, class C = listify>
  struct merge
  {
    template<class seq1, class seq2>
    using f = typename unpack<C>::template f<
      typename detail::merge_impl<
        list<>, seq1, seq2, JLN_MP_TRACE_F(Cmp)
      >::type
    >;
  };

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = listify>
    using merge = unpack<L, mp::merge<Cmp, C>>;
  }
}


/// \cond
namespace jln::mp
{
  template<class Cmp>
  struct merge<Cmp, listify>
  {
    template<class seq1, class seq2>
    using f = typename detail::merge_impl<
      list<>, seq1, seq2, JLN_MP_TRACE_F(Cmp)
    >::type;
  };
}

namespace jln::mp::detail
{
  template <bool, class L, class Seq1, class Seq2, class Cmp>
  struct merge_insert;

  template <class... R, class T0, class T1, class... Ts, class U, class... Us, class Cmp>
  struct merge_insert<true, list<R...>, list<T0, T1, Ts...>, list<U, Us...>, Cmp>
  : merge_insert<Cmp::template f<T1, U>::value,
                 list<R..., T0>, list<T1, Ts...>, list<U, Us...>, Cmp>
  {};

  template <class... R, class T, class U, class... Us, class Cmp>
  struct merge_insert<true, list<R...>, list<T>, list<U, Us...>, Cmp>
  {
    template<class... xs> using out   = list<xs..., R..., T>;
    template<class... xs> using left  = list<xs...>;
    template<class... xs> using right = list<U, Us..., xs...>;
  };

  template <class... R, class T, class... Ts, class U0, class U1, class... Us, class Cmp>
  struct merge_insert<false, list<R...>, list<T, Ts...>, list<U0, U1, Us...>, Cmp>
  : merge_insert<Cmp::template f<T, U1>::value,
                 list<R..., U0>, list<T, Ts...>, list<U1, Us...>, Cmp>
  {};

  template <class... R, class T, class... Ts, class U, class Cmp>
  struct merge_insert<false, list<R...>, list<T, Ts...>, list<U>, Cmp>
  {
    template<class... xs> using out   = list<xs..., R..., U>;
    template<class... xs> using left  = list<T, Ts..., xs...>;
    template<class... xs> using right = list<xs...>;
  };

  template <class... R, class T0, class T1, class T2, class T3, class T4, class T5,
            class T6, class T7, class T8, class T9, class... Ts, class U0, class U1,
            class U2, class U3, class U4, class U5, class U6, class U7, class U8,
            class U9, class... Us, class Cmp>
  struct merge_impl<list<R...>, list<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, Ts...>,
                    list<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9, Us...>, Cmp>
  {
    using sub = merge_insert<Cmp::template f<T0, U0>::value, list<>,
                             list<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>,
                             list<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>, Cmp>;
    using type = typename merge_impl<typename sub::template out<R...>,
                                     typename sub::template left<Ts...>,
                                     typename sub::template right<Us...>,
                                     Cmp>::type;
  };

  template <class... R, class T, class... Ts, class U, class... Us, class Cmp>
  struct merge_impl<list<R...>, list<T, Ts...>, list<U, Us...>, Cmp>
  : conditional_c<Cmp::template f<T, U>::value>::template f<
      merge_impl<list<R..., T>, list<Ts...>, list<U, Us...>, Cmp>,
      merge_impl<list<R..., U>, list<T, Ts...>, list<Us...>, Cmp>>
  {};

  template <class... R, class... Ts, class Cmp>
  struct merge_impl<list<R...>, list<Ts...>, list<>, Cmp>
  {
    using type = list<R..., Ts...>;
  };

  template <class... R, class... Us, class Cmp>
  struct merge_impl<list<R...>, list<>, list<Us...>, Cmp>
  {
    using type = list<R..., Us...>;
  };

  template <class... R, class Cmp>
  struct merge_impl<list<R...>, list<>, list<>, Cmp>
  {
    using type = list<R...>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = listify>
  using merge = test_contract<
    mp::if_<mp::at0<mp::is_list<>>, mp::at1<mp::is_list<>>>,
    mp::merge<
      concepts::predicate<assume_binary<Cmp>, mp::identity, mp::always<true_>>,
      mp::if_<
        try_subcontract<is_sorted<Cmp>, mp::always<true_>, mp::always<false_>>,
        subcontract<C>,
        violation
      >
    >
  >;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, merge<Cmp, C>>
  {
    using type = smp::merge<sfinae<Cmp>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class F>
  using invoke_twice = contract<mp::invoke_twice<mp::try_subcontract<
    F, mp::lift<try_subcontract>, mp::always<mp::violation>>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F>
  struct _sfinae<sfinae, invoke_twice<F>>
  {
    using type = smp::invoke_twice<sfinae<F>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup algorithm

  /// Returns the first mismatching index of elements from two sequences, otherwise the size of the sequences.
  /// \treturn \number
  template<class Cmp = equal<>, class C = identity>
  using mismatch_index = mismatch<Cmp, at0<C>, if_<at0<is<number<-1>>>, at1<C>, at0<C>>>;

  namespace emp
  {
    template<class seq1, class seq2, class Cmp = mp::equal<>, class C = mp::identity>
    using mismatch_index = typename mismatch_index<Cmp, C>::template f<seq1, seq2>;
  }
}
namespace jln::mp::smp
{
  template<class Cmp = equal<>, class C = identity>
  using mismatch_index = mismatch<
    Cmp,
    mp::at0<assume_number<C>>,
    mp::if_<
      mp::at0<mp::is<number<-1>>>,
      mp::at1<assume_number<C>>,
      mp::at0<assume_number<C>>
    >
  >;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, mismatch<Cmp, at0<C>, if_<at0<is<number<-1>>>, at1<C>, at0<C>>>>
  {
    using type = smp::mismatch_index<sfinae<Cmp>, sfinae<C>>;
  };
}
namespace jln::mp::smp
{
  template<class F = listify, class C = listify>
  using pairwise_with = contract<mp::pairwise_with<
    assume_binary<F>, detail::smp_listify_or_monadic_xs<F, C>
  >>;

  template<class C = listify>
  using pairwise = contract<mp::pairwise<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, pairwise_with<F, C>>
  {
    using type = smp::pairwise_with<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, pairwise<C>>
  {
    using type = smp::pairwise<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool... bs>
    struct partition_impl;

    struct partition_caller;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a \list in two according to a predicate.
  /// The first value contains all elements for which the predicate returns true,
  /// the second value contains all elements for which predicate returns false
  /// \treturn \sequence of two \values
  template<class Pred, class F = listify, class C = listify>
  struct partition_with
  {
    template<class... xs>
    using f = typename transform<Pred, detail::partition_caller>
      ::template f<xs...>
      ::template f<C, F, xs...>;
  };

  /// Splits a \list in two according to a predicate.
  /// The first value contains all elements for which the predicate returns true,
  /// the second value contains all elements for which predicate returns false
  /// \treturn \sequence of two \lists
  /// \see partition_with
  template<class Pred, class C = listify>
  using partition = partition_with<Pred, listify, C>;

  namespace emp
  {
    template<class L, class Pred, class F = mp::listify, class C = mp::listify>
    using partition_with = unpack<L, mp::partition_with<Pred, F, C>>;

    template<class L, class Pred, class C = mp::listify>
    using partition = unpack<L, mp::partition<Pred, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<bool... bs>
  struct partition_impl
  {
    template<class C, class F, class... xs>
    using f = typename C::template f<
      typename mp::join<F>::template f<typename mp::wrap_in_list_c<bs>::template f<xs>...>,
      typename mp::join<F>::template f<typename mp::wrap_in_list_c<!bs>::template f<xs>...>
    >;
  };

  struct partition_caller
  {
    template<class... xs>
    using f = partition_impl<xs::value...>;
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<class Pred, class F, class C>
  struct smp_partition_with;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class F = listify, class C = listify>
  using partition_with = try_contract<detail::smp_partition_with<
      assume_unary<Pred>, subcontract<F>, subcontract<C>>>;

  template<class Pred, class C = listify>
  using partition = partition_with<Pred, listify, assume_lists_barrier<C>>;
}


/// \cond
namespace jln::mp::detail
{
  template<class Pred, class F, class C>
  struct smp_partition_with
  {
    template<class... xs>
    using f = typename mp::transform<
      Pred,
      mp::try_or<partition_caller, violation>
    >::template f<xs...>
     ::template f<mp::monadic_xs<C>, F, xs...>;
  };

  template<template<class> class sfinae, class Pred, class F, class C>
  struct _sfinae<sfinae, partition_with<Pred, F, C>>
  {
    using type = smp::partition_with<sfinae<Pred>, sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _permutations;

    constexpr int _permutations_select(int n);
  }
  /// \endcond

  /// \ingroup group

  /// Generates all permutations of \sequence.
  /// \post sizeof...(result) == sizeof...(xs)!
  /// \treturn \sequence of \list
  template<class C = listify>
  struct permutations
  {
    template<class... xs>
    using f = typename detail::_permutations<detail::_permutations_select(sizeof...(xs))>
      ::template f<C, xs...>;
  };

  namespace emp
  {
    template<class L, class C = listify>
    using permutations = unpack<L, mp::permutations<C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  constexpr int _permutations_select(int n)
  {
#ifdef JLN_MP_BIG_LIST_PERMUTATIONS
    // -1 with big list result (40320 elements)
    return n > 8 ? -1 : n;
#else
    // -1 with big list result (5040 elements)
    return n > 7 ? -1 : n;
#endif
  }

  template<>
  struct _permutations<-1>
  {};

  template<>
  struct _permutations<0>
  {
    template<class C, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  template<>
  struct _permutations<1>
  {
    template<class C, class x>
    using f = JLN_MP_CALL_TRACE(C, list<x>);
  };

  template<>
  struct _permutations<2>
  {
    template<class C, class x0, class x1>
    using f = JLN_MP_CALL_TRACE(C,
      list<x0, x1>, list<x1, x0>
    );
  };

  template<>
  struct _permutations<3>
  {
    template<class C, class x0, class x1, class x2>
    using f = JLN_MP_CALL_TRACE(C,
      list<x0, x1, x2>, list<x0, x2, x1>,
      list<x1, x0, x2>, list<x1, x2, x0>,
      list<x2, x0, x1>, list<x2, x1, x0>
    );
  };

  template<>
  struct _permutations<4>
  {
    template<class C, class x0, class x1, class x2, class x3>
    using f = JLN_MP_CALL_TRACE(C,
      list<x0, x1, x2, x3>, list<x0, x1, x3, x2>,
      list<x0, x2, x1, x3>, list<x0, x2, x3, x1>,
      list<x0, x3, x1, x2>, list<x0, x3, x2, x1>,

      list<x1, x0, x2, x3>, list<x1, x0, x3, x2>,
      list<x1, x2, x0, x3>, list<x1, x2, x3, x0>,
      list<x1, x3, x0, x2>, list<x1, x3, x2, x0>,

      list<x2, x0, x1, x3>, list<x2, x0, x3, x1>,
      list<x2, x1, x0, x3>, list<x2, x1, x3, x0>,
      list<x2, x3, x0, x1>, list<x2, x3, x1, x0>,

      list<x3, x0, x1, x2>, list<x3, x0, x2, x1>,
      list<x3, x1, x0, x2>, list<x3, x1, x2, x0>,
      list<x3, x2, x0, x1>, list<x3, x2, x1, x0>
    );
  };

  struct _insert_permutations4
  {
    template<class x, class x0, class x1, class x2, class x3>
    using f = list<
      list<x, x0, x1, x2, x3>, list<x, x0, x1, x3, x2>,
      list<x, x0, x2, x1, x3>, list<x, x0, x2, x3, x1>,
      list<x, x0, x3, x1, x2>, list<x, x0, x3, x2, x1>,

      list<x, x1, x0, x2, x3>, list<x, x1, x0, x3, x2>,
      list<x, x1, x2, x0, x3>, list<x, x1, x2, x3, x0>,
      list<x, x1, x3, x0, x2>, list<x, x1, x3, x2, x0>,

      list<x, x2, x0, x1, x3>, list<x, x2, x0, x3, x1>,
      list<x, x2, x1, x0, x3>, list<x, x2, x1, x3, x0>,
      list<x, x2, x3, x0, x1>, list<x, x2, x3, x1, x0>,

      list<x, x3, x0, x1, x2>, list<x, x3, x0, x2, x1>,
      list<x, x3, x1, x0, x2>, list<x, x3, x1, x2, x0>,
      list<x, x3, x2, x0, x1>, list<x, x3, x2, x1, x0>
    >;
  };

  template<>
  struct _permutations<5>
  {
    template<class C, class x0, class x1, class x2, class x3, class x4>
    using f = typename join<C>::template f<
      _insert_permutations4::f<x0, x1, x2, x3, x4>,
      _insert_permutations4::f<x1, x2, x3, x4, x0>,
      _insert_permutations4::f<x2, x3, x4, x0, x1>,
      _insert_permutations4::f<x3, x4, x0, x1, x2>,
      _insert_permutations4::f<x4, x0, x1, x2, x3>
    >;
  };

  struct _push_permutations4
  {
    template<class F, class x, class x0, class x1, class x2, class x3>
    using f = list<
      typename F::template f<x, x0, x1, x2, x3>, typename F::template f<x, x0, x1, x3, x2>,
      typename F::template f<x, x0, x2, x1, x3>, typename F::template f<x, x0, x2, x3, x1>,
      typename F::template f<x, x0, x3, x1, x2>, typename F::template f<x, x0, x3, x2, x1>,

      typename F::template f<x, x1, x0, x2, x3>, typename F::template f<x, x1, x0, x3, x2>,
      typename F::template f<x, x1, x2, x0, x3>, typename F::template f<x, x1, x2, x3, x0>,
      typename F::template f<x, x1, x3, x0, x2>, typename F::template f<x, x1, x3, x2, x0>,

      typename F::template f<x, x2, x0, x1, x3>, typename F::template f<x, x2, x0, x3, x1>,
      typename F::template f<x, x2, x1, x0, x3>, typename F::template f<x, x2, x1, x3, x0>,
      typename F::template f<x, x2, x3, x0, x1>, typename F::template f<x, x2, x3, x1, x0>,

      typename F::template f<x, x3, x0, x1, x2>, typename F::template f<x, x3, x0, x2, x1>,
      typename F::template f<x, x3, x1, x0, x2>, typename F::template f<x, x3, x1, x2, x0>,
      typename F::template f<x, x3, x2, x0, x1>, typename F::template f<x, x3, x2, x1, x0>
    >;
  };

  template<class C>
  struct _permutations5
  {
    template<class F, class x0, class x1, class x2, class x3, class x4>
    using f = typename join<C>::template f<
      _push_permutations4::f<F, x0, x1, x2, x3, x4>,
      _push_permutations4::f<F, x1, x2, x3, x4, x0>,
      _push_permutations4::f<F, x2, x3, x4, x0, x1>,
      _push_permutations4::f<F, x3, x4, x0, x1, x2>,
      _push_permutations4::f<F, x4, x0, x1, x2, x3>
    >;
  };

  template<class C>
  struct _permutations6
  {
    template<class F, class x0, class x1, class x2, class x3, class x4, class x5>
    using f = typename join<C>::template f<
      _permutations5<listify>::f<push_front<x0, F>, x1, x2, x3, x4, x5>,
      _permutations5<listify>::f<push_front<x1, F>, x2, x3, x4, x5, x0>,
      _permutations5<listify>::f<push_front<x2, F>, x3, x4, x5, x0, x1>,
      _permutations5<listify>::f<push_front<x3, F>, x4, x5, x0, x1, x2>,
      _permutations5<listify>::f<push_front<x4, F>, x5, x0, x1, x2, x3>,
      _permutations5<listify>::f<push_front<x5, F>, x0, x1, x2, x3, x4>
    >;
  };

  template<>
  struct _permutations<6>
  {
    template<class C, class x0, class x1, class x2, class x3, class x4, class x5>
    using f = typename _permutations6<C>::template f<listify, x0, x1, x2, x3, x4, x5>;
  };

  template<class C>
  struct _permutations7
  {
    template<class F, class x0, class x1, class x2, class x3, class x4, class x5, class x6>
    using f = typename join<C>::template f<
      _permutations6<listify>::f<push_front<x0, F>, x1, x2, x3, x4, x5, x6>,
      _permutations6<listify>::f<push_front<x1, F>, x2, x3, x4, x5, x6, x0>,
      _permutations6<listify>::f<push_front<x2, F>, x3, x4, x5, x6, x0, x1>,
      _permutations6<listify>::f<push_front<x3, F>, x4, x5, x6, x0, x1, x2>,
      _permutations6<listify>::f<push_front<x4, F>, x5, x6, x0, x1, x2, x3>,
      _permutations6<listify>::f<push_front<x5, F>, x6, x0, x1, x2, x3, x4>,
      _permutations6<listify>::f<push_front<x6, F>, x0, x1, x2, x3, x4, x5>
    >;
  };

  template<>
  struct _permutations<7>
  {
    template<class C, class x0, class x1, class x2, class x3, class x4, class x5, class x6>
    using f = typename _permutations7<C>::template f<listify, x0, x1, x2, x3, x4, x5, x6>;
  };

#ifdef JLN_MP_BIG_LIST_PERMUTATIONS
  template<class C>
  struct _permutations8
  {
    template<class F, class x0, class x1, class x2, class x3, class x4, class x5, class x6, class x7>
    using f = typename join<C>::template f<
      _permutations7<listify>::f<push_front<x0, F>, x1, x2, x3, x4, x5, x6, x7>,
      _permutations7<listify>::f<push_front<x1, F>, x2, x3, x4, x5, x6, x7, x0>,
      _permutations7<listify>::f<push_front<x2, F>, x3, x4, x5, x6, x7, x0, x1>,
      _permutations7<listify>::f<push_front<x3, F>, x4, x5, x6, x7, x0, x1, x2>,
      _permutations7<listify>::f<push_front<x4, F>, x5, x6, x7, x0, x1, x2, x3>,
      _permutations7<listify>::f<push_front<x5, F>, x6, x7, x0, x1, x2, x3, x4>,
      _permutations7<listify>::f<push_front<x6, F>, x7, x0, x1, x2, x3, x4, x5>,
      _permutations7<listify>::f<push_front<x7, F>, x0, x1, x2, x3, x4, x5, x6>
    >;
  };

  template<>
  struct _permutations<8>
  {
    template<class C, class x0, class x1, class x2, class x3, class x4, class x5, class x6, class x7>
    using f = typename _permutations8<C>::template f<listify, x0, x1, x2, x3, x4, x5, x6, x7>;
  };
#endif
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = listify>
  using permutations = try_contract<permutations<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, permutations<C>>
  {
    using type = smp::permutations<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, bool>
    struct _powerset;
  }
  /// \endcond

  /// \ingroup group

  /// Computes the powerset of a \sequence.
  /// \semantics
  ///   \code
  ///   powerset<>::f<a, b, c> == list<
  ///     list<>,
  ///     list<a>, list<b>, list<a, b>, list<c>,
  ///     list<a, c>, list<b, c>,
  ///     list<a, b, c>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  template<class C = listify>
  struct powerset
  {
    template<class... xs>
    using f = typename detail::_powerset<C, bool(sizeof...(xs))>
      ::type::template f<list<list<>>, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using powerset = unpack<L, mp::powerset<C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class, class>
  struct _power;

  template<class... xs, class y>
  struct _power<list<xs...>, y>
  {
    using type = list<list<xs...>, list<y, xs...>>;
  };

  template<class, class>
  struct _powerset_impl;

  template<class... seqs, class y>
  struct _powerset_impl<y, list<seqs...>>
  {
    using type = join<>::f<typename _power<seqs, y>::type...>;
  };

  template<class C, bool>
  struct _powerset
  {
    using type = fold_right<lift_t<_powerset_impl>, unpack<C>>;
  };

  template<>
  struct _powerset<listify, true>
  {
    using type = fold_right<lift_t<_powerset_impl>>;
  };

  template<class C>
  struct _powerset<C, false>
  {
    using type = _cartesian<C, 0>; // for C::f<>
  };

  template<>
  struct _powerset<listify, false>
  {
    using type = always<list<>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = listify>
  using powerset = contract<mp::powerset<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, powerset<C>>
  {
    using type = smp::powerset<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup algorithm

  /// Inserts a \value before each element of a \sequence.
  /// \treturn \list
  /// \see intersperse, suffix
  template<class x, class C = listify>
  struct prefix
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(C), list<x, xs>...>::type;
  };

  namespace emp
  {
    template<class L, class x, class C = mp::listify>
    using prefix = unpack<L, mp::prefix<x, C>>;
  }
}
namespace jln::mp::smp
{
  template<class x, class C = listify>
  using prefix = contract<mp::prefix<x, subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, prefix<x, C>>
  {
    using type = smp::prefix<x, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C>
    struct counter_to_repeat;

    template<class... xs>
    struct regroup_if_impl;
  }
  /// \endcond

  /// \ingroup group

  /// Group identical type together.
  /// Elements are sorted in order of first appearance.
  /// \semantics
  ///   \code
  ///   regroup_with<listify>::f<int, int, char, double, int, double>
  ///   == list<
  ///     list<int, int, int>,
  ///     list<char>,
  ///     list<double, double>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list of type and \number
  template<class F, class C = listify>
  using regroup_with = counter_wrapped_with<detail::counter_to_repeat<F>, C>;

  template<class C = listify>
  using regroup = regroup_with<listify, C>;

  template<class Cmp = lift<std::is_same>, class F = listify, class C = listify>
  struct regroup_if_with
  {
    template<class... xs>
    using f = typename unique_if<Cmp, lift<detail::regroup_if_impl>>
      ::template f<xs...>
      ::template f<C, F, Cmp, xs...>;
  };

  template<class Cmp = lift<std::is_same>, class C = listify>
  using regroup_if = regroup_if_with<Cmp, listify, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using regroup = unpack<L, mp::regroup<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using regroup_with = unpack<L, mp::regroup_with<F, C>>;

    template<class L, class Cmp = lift<std::is_same>, class C = mp::listify>
    using regroup_if = unpack<L, mp::regroup_if<Cmp, C>>;

    template<class L, class Cmp = lift<std::is_same>, class F = mp::listify, class C = mp::listify>
    using regroup_if_with = unpack<L, mp::regroup_if_with<Cmp, F, C>>;
  }

  /// \cond
  template<class F, class C>
  struct regroup_if_with<lift<std::is_same>, F, C> : regroup_with<F, C>
  {};
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  template<class C>
  struct counter_to_repeat
  {
    template<class x, class n>
    using f = typename repeat<n, C>::template f<x>;
  };

  template<class... xs>
  struct regroup_if_impl
  {
    template<class C, class F, class Cmp, class... ys>
    using f = JLN_MP_CALL_TRACE(C,
      typename copy_if<push_front<xs, Cmp>, F>::template f<ys...>...
    );
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<class C, class F, class Cmp>
  struct smp_regroup_if_impl;

  template<class Cmp>
  struct smp_regroup_if_select;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = listify>
  using regroup = contract<mp::regroup<assume_lists<C>>>;

  template<class F = listify, class C = listify>
  using regroup_with = contract<mp::counter_wrapped_with<
    mp::if_<
      mp::size<mp::is<mp::number<2>>>,
      detail::counter_to_repeat<assume_unary_or_more<F>>,
      violation
    >,
    detail::smp_listify_or_monadic_xs<F, C>>
  >;

  template<class Cmp = contract<mp::lift<std::is_same>>, class F = listify, class C = listify>
  using regroup_if_with = typename detail::smp_regroup_if_select<Cmp>::template f<C, F>;

  template<class Cmp = contract<mp::lift<std::is_same>>, class C = listify>
  using regroup_if = regroup_if_with<Cmp, listify, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, regroup<C>>
  {
    using type = smp::regroup<sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, regroup_with<F, C>>
  {
    using type = smp::regroup_with<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class Cmp, class F, class C>
  struct _sfinae<sfinae, regroup_if_with<Cmp, F, C>>
  {
    using type = smp::regroup_if_with<sfinae<Cmp>, sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, regroup_if_with<mp::lift<std::is_same>, F, C>>
  {
    using type = smp::regroup_with<sfinae<F>, sfinae<C>>;
  };

  template<>
  struct smp_regroup_if_select<contract<mp::lift<std::is_same>>>
  {
    template<class C, class F>
    using f = smp::regroup_with<F, C>;
  };

  template<class Cmp>
  struct smp_regroup_if_select
  {
    template<class C, class F>
    using f = smp::invoke_twice<smp::unique_if<Cmp,
      contract<detail::smp_regroup_if_impl<
        subcontract<C>,
        contract<assume_unary_or_more<F>>,
        contract<assume_binary<Cmp>>>>
    >>;
  };

  template<class C, class F, class Cmp>
  struct smp_regroup_if_impl
  {
    template<class... xs>
    using f = contract<_tee<monadic_xs<C>,
      subcontract<smp::copy_if<smp::push_front<xs, Cmp>, F>>...
    >>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using remove_if = contract<mp::transform<
    subcontract<wrap_in_list_if_not<assume_unary_barrier<Pred>>>,
    mp::monadic_xs<mp::join<subcontract<C>>>>>;

  template<class x, class C = listify>
  using remove = contract<mp::remove<x, subcontract<C>>>;
}
/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_repeat;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using repeat_c = typename detail::mk_repeat<n >= 0>
    ::template f<n, C>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(repeat, (N), (C, smp::listify), smp::repeat_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, repeat_c<N, C>>
  {
    using type = smp::repeat_c<N, sfinae<C>>;
  };

  template<>
  struct mk_repeat<true>
  {
    template<int_ n, class C>
    using f = contract<mp::repeat_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_repeat<false>
  {
    template<int_ i, class C>
    using f = bad_contract;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup algorithm

  /// Replaces every occurrence that satisfy a predicate by some \value.
  /// \treturn \sequence
  template<class Pred, class T, class C = listify>
  using replace_if = transform<if_<Pred, always<T>, identity>, C>;

  /// Replaces every occurrence of a \value by another \value.
  /// \treturn \sequence
  template<class T, class U, class C = listify>
  using replace = replace_if<is<T>, U, C>;

  namespace emp
  {
    template<class L, class T, class U, class C = mp::listify>
    using replace = unpack<L, mp::replace<T, U, C>>;

    template<class L, class Pred, class T, class C = mp::listify>
    using replace_if = unpack<L, mp::replace_if<Pred, T, C>>;
  }
}
namespace jln::mp::smp
{
  template<class Pred, class T, class C = listify>
  using replace_if = detail::sfinae<mp::replace_if<
    assume_unary_barrier<Pred>, T, subcontract_barrier<C>>>;

  template<class T, class U, class C = listify>
  using replace = contract<
    mp::replace<T, U, monadic_if_na<U, monadic_xs, subcontract<C>>>>;
}
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned>
    struct reverse_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Reverses the order of the elements of a \sequence.
  /// \treturn \sequence
  template<class C = listify>
  struct reverse
  {
    template<class... xs>
    using f = typename detail::reverse_impl<sizeof...(xs)>
      ::template f<C, sizeof...(xs), xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using reverse = unpack<L, mp::reverse<C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<unsigned n>
  struct reverse_impl2 : reverse_impl2<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

  template<unsigned n>
  struct reverse_impl : reverse_impl2<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_REVERSE_IMPL(n, mp_xs, mp_rxs, mp_rep)    \
  template<>                                             \
  struct reverse_impl2<n>                                \
  {                                                      \
    template<class C, std::size_t count                  \
      mp_xs(JLN_MP_COMMA class, JLN_MP_NIL, JLN_MP_NIL), \
      class... xs>                                       \
    using f = typename reverse<join<C>>                  \
      ::template f<xs..., list<                          \
        mp_rxs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>>;  \
  };                                                     \
  template<>                                             \
  struct reverse_impl<n>                                 \
  {                                                      \
    template<class C, std::size_t count                  \
      mp_xs(JLN_MP_COMMA class, JLN_MP_NIL, JLN_MP_NIL), \
      class... xs>                                       \
    using f = JLN_MP_CALL_TRACE(C,                       \
      mp_rxs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA));     \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_MP_REVERSE_IMPL)

#undef JLN_MP_REVERSE_IMPL

#define JLN_MP_REVERSE_IMPL(n, mp_xs, mp_rxs, mp_rep) \
  template<>                                          \
  struct reverse_impl2<n>                             \
  {                                                   \
    template<class C, std::size_t count,              \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),         \
      class... xs>                                    \
    using f = typename reverse_impl2<                 \
      count-n                                         \
    >::template f<C, count-n, xs..., list<            \
      mp_rxs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>>; \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_REVERSE_IMPL)

#undef JLN_MP_REVERSE_IMPL
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = listify>
  using reverse = contract<mp::reverse<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, reverse<C>>
  {
    using type = smp::reverse<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct reverse_fold_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Folds right over a list using a binary predicate.
  /// reverse_fold consideres the first element in the input pack as the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<... F::f<F::f<state, xs[n-1]>, x[n-2]>, ..., x[0]>
  ///   \endcode
  /// \treturn \value
  /// \see fold_left, fold_right, fold_tree, fold_balanced_tree
#ifdef JLN_MP_DOXYGENATING
  template<class F, class C = identity>
  using reverse_fold = reverse<fold_left<F, C>>;
#else
  template<class F, class C = identity>
  struct reverse_fold
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::reverse_fold_impl<
        int(sizeof...(xs)) - 1
      >::template f<JLN_MP_TRACE_F(F)::template f, xs...>
    );
  };
#endif

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using reverse_fold = unpack<L,
      mp::push_front<state, mp::reverse_fold<F, C>>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<int n>
  struct reverse_fold_impl : reverse_fold_impl<
      n < 8 ? 4
    : n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_REVERSE_FOLD_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                                 \
  struct reverse_fold_impl<n>                                \
  {                                                          \
    template<template<class...> class F, class state,        \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),                \
      class... xs>                                           \
    using f = mp_dup(F<, JLN_MP_NIL)                         \
      typename reverse_fold_impl<                            \
        sizeof...(xs)                                        \
      >::template f<F, state, xs...>,                        \
    mp_rxs(JLN_MP_NIL, >, JLN_MP_COMMA);                     \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_REVERSE_FOLD_SELECT)

#undef JLN_MP_REVERSE_FOLD_SELECT

#define JLN_MP_REVERSE_FOLD_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                                 \
  struct reverse_fold_impl<n>                                \
  {                                                          \
    template<template<class...> class F, class state,        \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA)>                \
    using f = mp_dup(F<, JLN_MP_NIL)                         \
      state, mp_rxs(JLN_MP_NIL, >, JLN_MP_COMMA);            \
  };

  JLN_MP_GEN_XS_1_TO_4(JLN_MP_REVERSE_FOLD_SELECT)

#undef JLN_MP_REVERSE_FOLD_SELECT

  template<>
  struct reverse_fold_impl<0>
  {
    template<template<class...> class, class state>
    using f = state;
  };

  template<>
  struct reverse_fold_impl<-1>
  {};
}
/// \endcond
namespace jln::mp::smp
{
  template<class F, class C = identity>
  using reverse_fold = test_contract<
    mp::size<>,
    mp::reverse_fold<
      mp::monadic0<assume_unary<F>>,
      mp::monadic<subcontract<C>>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, reverse_fold<F, C>>
  {
    using type = smp::reverse_fold<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template <int_ n, class C = listify>
  using rotate_c = contract<mp::rotate_c<n, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(rotate, (N), (C, smp::listify), smp::rotate_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, int_ N, class C>
  struct _sfinae<sfinae, rotate_c<N, C>>
  {
    using type = smp::rotate_c<N, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned>
    struct _scan_left;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Fold a \sequence to the left and return a list containing the successive reduction states.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   C::f<
  ///     xs[0],
  ///     F::f<xs[0], xs[1]>,
  ///     F::f<F::f<xs[0], xs[1]>, xs[2]>,
  ///     ...
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class F, class C = listify>
  struct scan_left
  {
    template<class... xs>
    using f = typename detail::_scan_left<sizeof...(xs)>
      ::template f<sizeof...(xs), C, JLN_MP_TRACE_F(F)::template f, xs...>;
  };

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using scan_left = unpack<L, mp::scan_left<F, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<unsigned n>
  struct _scan_left : _scan_left<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256
  >
  {};

  template<>
  struct _scan_left<0>
  {
    template<unsigned remaining, class C, template<class...> class F,
      class... xs>
    using f = typename join<C>::template f<xs...>;
  };

  template<>
  struct _scan_left<1>
  {
    template<unsigned remaining, class C, template<class...> class F,
      class _0, class... xs>
    using f = typename join<C>::template f<xs..., list<_0>>;
  };

  template<>
  struct _scan_left<2>
  {
    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class... xs>
    using f = typename join<C>::template f<xs..., list<_0, F<_0, _1>>>;
  };

  // for n in range(3,9):
  //   args=', '.join(f'class _{i}' for i in range(1,n))
  //   ps=', '.join(f'_{i}' for i in range(n))
  //   rs=', '.join(f'class r{i} = F<r{i-1}, _{i}>' for i in range(1, n-1))
  //   l=', '.join(f'r{i}' for i in range(n-1))
  //   sep=', ' if n > 2 else ''
  //   print(f'''
  //   template<>
  //   struct _scan_left<{n}>
  //   {{
  //     template<template<class...> class F,
  //       class r0, {args}{sep}{rs}>
  //     using g = list<{l}, F<r{n-2}, _{n-1}>>;
  //
  //     template<unsigned remaining, class C, template<class...> class F,
  //       class _0, {args}, class... xs>
  //     using f = typename join<C>::template f<xs..., g<F, {ps}>>;
  //   }};''')

  template<>
  struct _scan_left<3>
  {
    template<template<class...> class F,
      class r0, class _1, class _2, class r1 = F<r0, _1>>
    using g = list<r0, r1, F<r1, _2>>;

    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class _2, class... xs>
    using f = typename join<C>::template f<xs..., g<F, _0, _1, _2>>;
  };

  template<>
  struct _scan_left<4>
  {
    template<template<class...> class F,
      class r0, class _1, class _2, class _3,
      class r1 = F<r0, _1>, class r2 = F<r1, _2>>
    using g = list<r0, r1, r2, F<r2, _3>>;

    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class _2, class _3, class... xs>
    using f = typename join<C>::template f<xs..., g<F, _0, _1, _2, _3>>;
  };

  template<>
  struct _scan_left<5>
  {
    template<template<class...> class F,
      class r0, class _1, class _2, class _3, class _4,
      class r1 = F<r0, _1>, class r2 = F<r1, _2>, class r3 = F<r2, _3>>
    using g = list<r0, r1, r2, r3, F<r3, _4>>;

    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class _2, class _3, class _4, class... xs>
    using f = typename join<C>::template f<xs..., g<F, _0, _1, _2, _3, _4>>;
  };

  template<>
  struct _scan_left<6>
  {
    template<template<class...> class F,
      class r0, class _1, class _2, class _3, class _4, class _5,
      class r1 = F<r0, _1>, class r2 = F<r1, _2>, class r3 = F<r2, _3>,
      class r4 = F<r3, _4>>
    using g = list<r0, r1, r2, r3, r4, F<r4, _5>>;

    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class _2, class _3, class _4, class _5,
      class... xs>
    using f = typename join<C>
      ::template f<xs..., g<F, _0, _1, _2, _3, _4, _5>>;
  };

  template<>
  struct _scan_left<7>
  {
    template<template<class...> class F,
      class r0, class _1, class _2, class _3, class _4, class _5, class _6,
      class r1 = F<r0, _1>, class r2 = F<r1, _2>, class r3 = F<r2, _3>,
      class r4 = F<r3, _4>, class r5 = F<r4, _5>>
    using g = list<r0, r1, r2, r3, r4, r5, F<r5, _6>>;

    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class _2, class _3, class _4, class _5, class _6,
      class... xs>
    using f = typename join<C>
      ::template f<xs..., g<F, _0, _1, _2, _3, _4, _5, _6>>;
  };

  template<>
  struct _scan_left<8>
  {
    template<template<class...> class F,
      class r0, class _1, class _2, class _3, class _4, class _5, class _6,
      class _7, class r1 = F<r0, _1>, class r2 = F<r1, _2>,
      class r3 = F<r2, _3>, class r4 = F<r3, _4>, class r5 = F<r4, _5>,
      class r6 = F<r5, _6>>
    using g = list<r0, r1, r2, r3, r4, r5, r6, F<r6, _7>>;

    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class _2, class _3, class _4, class _5, class _6,
      class _7, class... xs>
    using f = typename join<C>::template f<xs..., g<F, _0, _1, _2, _3, _4, _5, _6, _7>>;
  };

  template<class state, class l>
  struct scan_continuation
  {
    template<
      unsigned remaining, class Next, class C,
      template<class...> class F, class... xs>
    using f = typename Next::template f<remaining, C, F, state, xs..., l>;
  };

  // for n in [8,16,32,64,128]:
  //   args=', '.join(f'class _{i}' for i in range(1, n))
  //   ps=', '.join(f'_{i}' for i in range(n))
  //   rs=', '.join(f'class r{i} = F<r{i-1}, _{i}>' for i in range(1, n-1))
  //   l=', '.join(f'r{i}' for i in range(n-1))
  //   print(f'''
  //   template<>
  //   struct _scan_left<{n*2}>
  //   {{
  //     template<template<class...> class F,
  //       class r0, {args},
  //       {rs},
  //     using g = scan_continuation<F<r{n-2}, _{n-1}>, list<{l}>>;
  //
  //     template<unsigned remaining, class C, template<class...> class F,
  //       class _0, {args},
  //       class... xs>
  //     using f = typename g<F, {ps}>
  //       ::template f<remaining-{n-1}, _scan_left<remaining-{n-1}>, C, F, xs...>;
  //   }};''')

  template<>
  struct _scan_left<16>
  {
    template<
      template<class...> class F, class r0, class _1, class _2, class _3,
      class _4, class _5, class _6, class _7, class r1 = F<r0, _1>,
      class r2 = F<r1, _2>, class r3 = F<r2, _3>, class r4 = F<r3, _4>,
      class r5 = F<r4, _5>, class r6 = F<r5, _6>>
    using g = scan_continuation<F<r6, _7>, list<r0, r1, r2, r3, r4, r5, r6>>;

    template<
      unsigned remaining, class C, template<class...> class F, class _0,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class... xs>
    using f = typename g<F, _0, _1, _2, _3, _4, _5, _6, _7>::template f<
      remaining - 7, _scan_left<remaining - 7>, C, F, xs...>;
  };

  template<>
  struct _scan_left<32>
  {
    template<
      template<class...> class F, class r0, class _1, class _2, class _3,
      class _4, class _5, class _6, class _7, class _8, class _9, class _10,
      class _11, class _12, class _13, class _14, class _15, class r1 = F<r0, _1>,
      class r2 = F<r1, _2>, class r3 = F<r2, _3>, class r4 = F<r3, _4>,
      class r5 = F<r4, _5>, class r6 = F<r5, _6>, class r7 = F<r6, _7>,
      class r8 = F<r7, _8>, class r9 = F<r8, _9>, class r10 = F<r9, _10>,
      class r11 = F<r10, _11>, class r12 = F<r11, _12>, class r13 = F<r12, _13>,
      class r14 = F<r13, _14>>
    using g = scan_continuation<F<r14, _15>, list<
      r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12,
      r13, r14>>;

    template<
      unsigned remaining, class C, template<class...> class F, class _0,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13,
      class _14, class _15,
      class... xs>
    using f = typename g<
      F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15
    >::template f<remaining - 15, _scan_left<remaining - 15>, C, F, xs...>;
  };

  template<>
  struct _scan_left<64>
  {
    template<
      template<class...> class F, class r0, class _1, class _2, class _3,
      class _4, class _5, class _6, class _7, class _8, class _9, class _10,
      class _11, class _12, class _13, class _14, class _15, class _16,
      class _17, class _18, class _19, class _20, class _21, class _22,
      class _23, class _24, class _25, class _26, class _27, class _28,
      class _29, class _30, class _31, class r1 = F<r0, _1>,
      class r2 = F<r1, _2>, class r3 = F<r2, _3>, class r4 = F<r3, _4>,
      class r5 = F<r4, _5>, class r6 = F<r5, _6>, class r7 = F<r6, _7>,
      class r8 = F<r7, _8>, class r9 = F<r8, _9>, class r10 = F<r9, _10>,
      class r11 = F<r10, _11>, class r12 = F<r11, _12>, class r13 = F<r12, _13>,
      class r14 = F<r13, _14>, class r15 = F<r14, _15>, class r16 = F<r15, _16>,
      class r17 = F<r16, _17>, class r18 = F<r17, _18>, class r19 = F<r18, _19>,
      class r20 = F<r19, _20>, class r21 = F<r20, _21>, class r22 = F<r21, _22>,
      class r23 = F<r22, _23>, class r24 = F<r23, _24>, class r25 = F<r24, _25>,
      class r26 = F<r25, _26>, class r27 = F<r26, _27>, class r28 = F<r27, _28>,
      class r29 = F<r28, _29>, class r30 = F<r29, _30>>
    using g = scan_continuation<F<r30, _31>, list<
      r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12,
      r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23,
      r24, r25, r26, r27, r28, r29, r30>>;

    template<
      unsigned remaining, class C, template<class...> class F, class _0,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13,
      class _14, class _15, class _16, class _17, class _18, class _19,
      class _20, class _21, class _22, class _23, class _24, class _25,
      class _26, class _27, class _28, class _29, class _30, class _31,
      class... xs>
    using f = typename g<
      F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15,
      _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,
      _31
    >::template f<remaining - 31, _scan_left<remaining - 31>, C, F, xs...>;
  };

  template<>
  struct _scan_left<128>
  {
    template<
      template<class...> class F, class r0, class _1, class _2, class _3,
      class _4, class _5, class _6, class _7, class _8, class _9, class _10,
      class _11, class _12, class _13, class _14, class _15, class _16,
      class _17, class _18, class _19, class _20, class _21, class _22,
      class _23, class _24, class _25, class _26, class _27, class _28,
      class _29, class _30, class _31, class _32, class _33, class _34,
      class _35, class _36, class _37, class _38, class _39, class _40,
      class _41, class _42, class _43, class _44, class _45, class _46,
      class _47, class _48, class _49, class _50, class _51, class _52,
      class _53, class _54, class _55, class _56, class _57, class _58,
      class _59, class _60, class _61, class _62, class _63,
      class r1 = F<r0, _1>, class r2 = F<r1, _2>, class r3 = F<r2, _3>,
      class r4 = F<r3, _4>, class r5 = F<r4, _5>, class r6 = F<r5, _6>,
      class r7 = F<r6, _7>, class r8 = F<r7, _8>, class r9 = F<r8, _9>,
      class r10 = F<r9, _10>, class r11 = F<r10, _11>, class r12 = F<r11, _12>,
      class r13 = F<r12, _13>, class r14 = F<r13, _14>, class r15 = F<r14, _15>,
      class r16 = F<r15, _16>, class r17 = F<r16, _17>, class r18 = F<r17, _18>,
      class r19 = F<r18, _19>, class r20 = F<r19, _20>, class r21 = F<r20, _21>,
      class r22 = F<r21, _22>, class r23 = F<r22, _23>, class r24 = F<r23, _24>,
      class r25 = F<r24, _25>, class r26 = F<r25, _26>, class r27 = F<r26, _27>,
      class r28 = F<r27, _28>, class r29 = F<r28, _29>, class r30 = F<r29, _30>,
      class r31 = F<r30, _31>, class r32 = F<r31, _32>, class r33 = F<r32, _33>,
      class r34 = F<r33, _34>, class r35 = F<r34, _35>, class r36 = F<r35, _36>,
      class r37 = F<r36, _37>, class r38 = F<r37, _38>, class r39 = F<r38, _39>,
      class r40 = F<r39, _40>, class r41 = F<r40, _41>, class r42 = F<r41, _42>,
      class r43 = F<r42, _43>, class r44 = F<r43, _44>, class r45 = F<r44, _45>,
      class r46 = F<r45, _46>, class r47 = F<r46, _47>, class r48 = F<r47, _48>,
      class r49 = F<r48, _49>, class r50 = F<r49, _50>, class r51 = F<r50, _51>,
      class r52 = F<r51, _52>, class r53 = F<r52, _53>, class r54 = F<r53, _54>,
      class r55 = F<r54, _55>, class r56 = F<r55, _56>, class r57 = F<r56, _57>,
      class r58 = F<r57, _58>, class r59 = F<r58, _59>, class r60 = F<r59, _60>,
      class r61 = F<r60, _61>, class r62 = F<r61, _62>>
    using g = scan_continuation<F<r62, _63>, list<
      r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15,
      r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29,
      r30, r31, r32, r33, r34, r35, r36, r37, r38, r39, r40, r41, r42, r43,
      r44, r45, r46, r47, r48, r49, r50, r51, r52, r53, r54, r55, r56, r57,
      r58, r59, r60, r61, r62>>;

    template<
      unsigned remaining, class C, template<class...> class F, class _0,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13,
      class _14, class _15, class _16, class _17, class _18, class _19,
      class _20, class _21, class _22, class _23, class _24, class _25,
      class _26, class _27, class _28, class _29, class _30, class _31,
      class _32, class _33, class _34, class _35, class _36, class _37,
      class _38, class _39, class _40, class _41, class _42, class _43,
      class _44, class _45, class _46, class _47, class _48, class _49,
      class _50, class _51, class _52, class _53, class _54, class _55,
      class _56, class _57, class _58, class _59, class _60, class _61,
      class _62, class _63, class... xs>
    using f = typename g<
      F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15,
      _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,
      _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
      _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
      _61, _62,
      _63>::template f<remaining - 63, _scan_left<remaining - 63>, C, F, xs...>;
  };

  template<>
  struct _scan_left<256>
  {
    template<
      template<class...> class F, class r0, class _1, class _2, class _3,
      class _4, class _5, class _6, class _7, class _8, class _9, class _10,
      class _11, class _12, class _13, class _14, class _15, class _16,
      class _17, class _18, class _19, class _20, class _21, class _22,
      class _23, class _24, class _25, class _26, class _27, class _28,
      class _29, class _30, class _31, class _32, class _33, class _34,
      class _35, class _36, class _37, class _38, class _39, class _40,
      class _41, class _42, class _43, class _44, class _45, class _46,
      class _47, class _48, class _49, class _50, class _51, class _52,
      class _53, class _54, class _55, class _56, class _57, class _58,
      class _59, class _60, class _61, class _62, class _63, class _64,
      class _65, class _66, class _67, class _68, class _69, class _70,
      class _71, class _72, class _73, class _74, class _75, class _76,
      class _77, class _78, class _79, class _80, class _81, class _82,
      class _83, class _84, class _85, class _86, class _87, class _88,
      class _89, class _90, class _91, class _92, class _93, class _94,
      class _95, class _96, class _97, class _98, class _99, class _100,
      class _101, class _102, class _103, class _104, class _105, class _106,
      class _107, class _108, class _109, class _110, class _111, class _112,
      class _113, class _114, class _115, class _116, class _117, class _118,
      class _119, class _120, class _121, class _122, class _123, class _124,
      class _125, class _126, class _127, class r1 = F<r0, _1>,
      class r2 = F<r1, _2>, class r3 = F<r2, _3>, class r4 = F<r3, _4>,
      class r5 = F<r4, _5>, class r6 = F<r5, _6>, class r7 = F<r6, _7>,
      class r8 = F<r7, _8>, class r9 = F<r8, _9>, class r10 = F<r9, _10>,
      class r11 = F<r10, _11>, class r12 = F<r11, _12>, class r13 = F<r12, _13>,
      class r14 = F<r13, _14>, class r15 = F<r14, _15>, class r16 = F<r15, _16>,
      class r17 = F<r16, _17>, class r18 = F<r17, _18>, class r19 = F<r18, _19>,
      class r20 = F<r19, _20>, class r21 = F<r20, _21>, class r22 = F<r21, _22>,
      class r23 = F<r22, _23>, class r24 = F<r23, _24>, class r25 = F<r24, _25>,
      class r26 = F<r25, _26>, class r27 = F<r26, _27>, class r28 = F<r27, _28>,
      class r29 = F<r28, _29>, class r30 = F<r29, _30>, class r31 = F<r30, _31>,
      class r32 = F<r31, _32>, class r33 = F<r32, _33>, class r34 = F<r33, _34>,
      class r35 = F<r34, _35>, class r36 = F<r35, _36>, class r37 = F<r36, _37>,
      class r38 = F<r37, _38>, class r39 = F<r38, _39>, class r40 = F<r39, _40>,
      class r41 = F<r40, _41>, class r42 = F<r41, _42>, class r43 = F<r42, _43>,
      class r44 = F<r43, _44>, class r45 = F<r44, _45>, class r46 = F<r45, _46>,
      class r47 = F<r46, _47>, class r48 = F<r47, _48>, class r49 = F<r48, _49>,
      class r50 = F<r49, _50>, class r51 = F<r50, _51>, class r52 = F<r51, _52>,
      class r53 = F<r52, _53>, class r54 = F<r53, _54>, class r55 = F<r54, _55>,
      class r56 = F<r55, _56>, class r57 = F<r56, _57>, class r58 = F<r57, _58>,
      class r59 = F<r58, _59>, class r60 = F<r59, _60>, class r61 = F<r60, _61>,
      class r62 = F<r61, _62>, class r63 = F<r62, _63>, class r64 = F<r63, _64>,
      class r65 = F<r64, _65>, class r66 = F<r65, _66>, class r67 = F<r66, _67>,
      class r68 = F<r67, _68>, class r69 = F<r68, _69>, class r70 = F<r69, _70>,
      class r71 = F<r70, _71>, class r72 = F<r71, _72>, class r73 = F<r72, _73>,
      class r74 = F<r73, _74>, class r75 = F<r74, _75>, class r76 = F<r75, _76>,
      class r77 = F<r76, _77>, class r78 = F<r77, _78>, class r79 = F<r78, _79>,
      class r80 = F<r79, _80>, class r81 = F<r80, _81>, class r82 = F<r81, _82>,
      class r83 = F<r82, _83>, class r84 = F<r83, _84>, class r85 = F<r84, _85>,
      class r86 = F<r85, _86>, class r87 = F<r86, _87>, class r88 = F<r87, _88>,
      class r89 = F<r88, _89>, class r90 = F<r89, _90>, class r91 = F<r90, _91>,
      class r92 = F<r91, _92>, class r93 = F<r92, _93>, class r94 = F<r93, _94>,
      class r95 = F<r94, _95>, class r96 = F<r95, _96>, class r97 = F<r96, _97>,
      class r98 = F<r97, _98>, class r99 = F<r98, _99>,
      class r100 = F<r99, _100>, class r101 = F<r100, _101>,
      class r102 = F<r101, _102>, class r103 = F<r102, _103>,
      class r104 = F<r103, _104>, class r105 = F<r104, _105>,
      class r106 = F<r105, _106>, class r107 = F<r106, _107>,
      class r108 = F<r107, _108>, class r109 = F<r108, _109>,
      class r110 = F<r109, _110>, class r111 = F<r110, _111>,
      class r112 = F<r111, _112>, class r113 = F<r112, _113>,
      class r114 = F<r113, _114>, class r115 = F<r114, _115>,
      class r116 = F<r115, _116>, class r117 = F<r116, _117>,
      class r118 = F<r117, _118>, class r119 = F<r118, _119>,
      class r120 = F<r119, _120>, class r121 = F<r120, _121>,
      class r122 = F<r121, _122>, class r123 = F<r122, _123>,
      class r124 = F<r123, _124>, class r125 = F<r124, _125>,
      class r126 = F<r125, _126>>
    using g = scan_continuation<F<r126, _127>, list<
      r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15,
      r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29,
      r30, r31, r32, r33, r34, r35, r36, r37, r38, r39, r40, r41, r42, r43,
      r44, r45, r46, r47, r48, r49, r50, r51, r52, r53, r54, r55, r56, r57,
      r58, r59, r60, r61, r62, r63, r64, r65, r66, r67, r68, r69, r70, r71,
      r72, r73, r74, r75, r76, r77, r78, r79, r80, r81, r82, r83, r84, r85,
      r86, r87, r88, r89, r90, r91, r92, r93, r94, r95, r96, r97, r98, r99,
      r100, r101, r102, r103, r104, r105, r106, r107, r108, r109, r110,
      r111, r112, r113, r114, r115, r116, r117, r118, r119, r120, r121,
      r122, r123, r124, r125, r126>>;

    template<
      unsigned remaining, class C, template<class...> class F, class _0,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13,
      class _14, class _15, class _16, class _17, class _18, class _19,
      class _20, class _21, class _22, class _23, class _24, class _25,
      class _26, class _27, class _28, class _29, class _30, class _31,
      class _32, class _33, class _34, class _35, class _36, class _37,
      class _38, class _39, class _40, class _41, class _42, class _43,
      class _44, class _45, class _46, class _47, class _48, class _49,
      class _50, class _51, class _52, class _53, class _54, class _55,
      class _56, class _57, class _58, class _59, class _60, class _61,
      class _62, class _63, class _64, class _65, class _66, class _67,
      class _68, class _69, class _70, class _71, class _72, class _73,
      class _74, class _75, class _76, class _77, class _78, class _79,
      class _80, class _81, class _82, class _83, class _84, class _85,
      class _86, class _87, class _88, class _89, class _90, class _91,
      class _92, class _93, class _94, class _95, class _96, class _97,
      class _98, class _99, class _100, class _101, class _102, class _103,
      class _104, class _105, class _106, class _107, class _108, class _109,
      class _110, class _111, class _112, class _113, class _114, class _115,
      class _116, class _117, class _118, class _119, class _120, class _121,
      class _122, class _123, class _124, class _125, class _126, class _127,
      class... xs>
    using f = typename g<
      F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15,
      _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,
      _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
      _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
      _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75,
      _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90,
      _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104,
      _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116,
      _117, _118, _119, _120, _121, _122, _123, _124, _125, _126, _127>::
      template f<remaining - 127, _scan_left<remaining - 127>, C, F, xs...>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class F, class C = listify>
  using scan_left = contract<mp::scan_left<
    monadic_xs<assume_binary<F>>,
    monadic_xs<subcontract<C>>
  >>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, scan_left<F, C>>
  {
    using type = smp::scan_left<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class F, class C>
    struct scan_right_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Fold a \sequence to the right and return a list containing the successive reduction states.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   C::f<
  ///     ...
  ///     F::f<xs[n-3], F::f<xs[n-2], xs[n-1]>>,
  ///     F::f<xs[n-2], xs[n-1]>,
  ///     xs[n-1],
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class F, class C = listify>
  using scan_right = reverse<detail::scan_right_impl<F, C>>;

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using scan_right = unpack<L, mp::scan_right<F, C>>;
  }
}


// scan_continuation

/// \cond
namespace jln::mp::detail
{
  template<unsigned n>
  struct _scan_right : _scan_right<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256
  >
  {};

  template<unsigned>
  struct _scan_right;

  template<class F, class C>
  struct scan_right_impl
  {
    template<class... xs>
    using f = typename _scan_right<sizeof...(xs)>
    ::template f<sizeof...(xs), C, JLN_MP_TRACE_F(F)::template f, xs...>;
  };

  template<>
  struct _scan_right<0>
  {
    template<unsigned remaining, class C, template<class...> class F,
      class... xs>
    using f = typename join<C>::template f<xs...>;
  };

  template<>
  struct _scan_right<1>
  {
    template<unsigned remaining, class C, template<class...> class F,
      class _0, class... xs>
    using f = typename join<C>::template f<list<_0>, xs...>;
  };

  template<>
  struct _scan_right<2>
  {
    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class... xs>
    using f = typename join<C>::template f<list<F<_1, _0>, _0>, xs...>;
  };

  // for n in range(3,9):
  //   args=', '.join(f'class _{i}' for i in range(1,n))
  //   ps=', '.join(f'_{i}' for i in range(n))
  //   rs=', '.join(f'class r{i} = F<_{i}, r{i-1}>' for i in range(1, n-1))
  //   l=', '.join(f'r{i}' for i in range(n-2, -1, -1))
  //   sep=', ' if n > 2 else ''
  //   print(f'''
  //   template<>
  //   struct _scan_right<{n}>
  //   {{
  //     template<template<class...> class F,
  //       class r0, {args}{sep}{rs}>
  //     using g = list<F<_{n-1}, r{n-2}>, {l}>;
  //
  //     template<unsigned remaining, class C, template<class...> class F,
  //       class _0, {args}, class... xs>
  //     using f = typename join<C>::template f<g<F, {ps}>, xs...>;
  //   }};''')

  template<>
  struct _scan_right<3>
  {
    template<template<class...> class F, class r0, class _1, class _2,
             class r1 = F<_1, r0>>
    using g = list<F<_2, r1>, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class... xs>
    using f = typename join<C>::template f<xs..., g<F, _0, _1, _2>>;
  };

  template<>
  struct _scan_right<4>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
              class r1 = F<_1, r0>, class r2 = F<_2, r1>>
    using g = list<F<_3, r2>, r2, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class... xs>
    using f = typename join<C>::template f<g<F, _0, _1, _2, _3>, xs...>;
  };

  template<>
  struct _scan_right<5>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class r1 = F<_1, r0>, class r2 = F<_2, r1>,
             class r3 = F<_3, r2>>
    using g = list<F<_4, r3>, r3, r2, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class... xs>
    using f = typename join<C>::template f<g<F, _0, _1, _2, _3, _4>, xs...>;
  };

  template<>
  struct _scan_right<6>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class _5, class r1 = F<_1, r0>, class r2 = F<_2, r1>,
             class r3 = F<_3, r2>, class r4 = F<_4, r3>>
    using g = list<F<_5, r4>, r4, r3, r2, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
              class _1, class _2, class _3, class _4, class _5, class... xs>
    using f = typename join<C>::template f<g<F, _0, _1, _2, _3, _4, _5>, xs...>;
  };

  template<>
  struct _scan_right<7>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class _5, class _6, class r1 = F<_1, r0>,
             class r2 = F<_2, r1>, class r3 = F<_3, r2>, class r4 = F<_4, r3>,
             class r5 = F<_5, r4>>
    using g = list<F<_6, r5>, r5, r4, r3, r2, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class... xs>
    using f = typename join<C>::template f<g<F, _0, _1, _2, _3, _4, _5, _6>, xs...>;
  };

  template<>
  struct _scan_right<8>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class _5, class _6, class _7, class r1 = F<_1, r0>,
             class r2 = F<_2, r1>, class r3 = F<_3, r2>, class r4 = F<_4, r3>,
             class r5 = F<_5, r4>, class r6 = F<_6, r5>>
    using g = list<F<_7, r6>, r6, r5, r4, r3, r2, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class _7, class... xs>
    using f = typename join<C>::template f<g<F, _0, _1, _2, _3, _4, _5, _6, _7>, xs...>;
  };

  // for n in [8,16,32,64,128]:
  //   args=', '.join(f'class _{i}' for i in range(1, n))
  //   ps=', '.join(f'_{i}' for i in range(n))
  //   rs=', '.join(f'class r{i} = F<_{i}, r{i-1}>' for i in range(1, n-1))
  //   l=', '.join(f'r{i}' for i in range(n-2,-1,-1))
  //   print(f'''
  //   template<>
  //   struct _scan_right<{n*2}>
  //   {{
  //     template<template<class...> class F,
  //       class r0, {args},
  //       {rs}>
  //     using g = scan_continuation<F<_{n-1}, r{n-2}>, list<{l}>>;
  //
  //     template<unsigned remaining, class C, template<class...> class F,
  //       class _0, {args},
  //       class... xs>
  //     using f = typename g<F, {ps}>
  //       ::template f<remaining-{n-1}, _scan_right<remaining-{n-1}>, C, F, xs..
  // .>;
  //   }};''')

  template<> struct _scan_right<16>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class _5, class _6, class _7, class r1 = F<_1, r0>,
             class r2 = F<_2, r1>, class r3 = F<_3, r2>, class r4 = F<_4, r3>,
             class r5 = F<_5, r4>, class r6 = F<_6, r5>>
    using g = scan_continuation<F<_7, r6>, list<r6, r5, r4, r3, r2, r1, r0>>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class _7, class... xs>
    using f = typename g<F, _0, _1, _2, _3, _4, _5, _6, _7>::template f<
        remaining - 7, _scan_right<remaining - 7>, C, F, xs...>;
  };

  template<> struct _scan_right<32> {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class _5, class _6, class _7, class _8, class _9,
             class _10, class _11, class _12, class _13, class _14, class _15,
             class r1 = F<_1, r0>, class r2 = F<_2, r1>, class r3 = F<_3, r2>,
             class r4 = F<_4, r3>, class r5 = F<_5, r4>, class r6 = F<_6, r5>,
             class r7 = F<_7, r6>, class r8 = F<_8, r7>, class r9 = F<_9, r8>,
             class r10 = F<_10, r9>, class r11 = F<_11, r10>,
             class r12 = F<_12, r11>, class r13 = F<_13, r12>,
             class r14 = F<_14, r13>>
    using g =
        scan_continuation<F<_15, r14>, list<r14, r13, r12, r11, r10, r9, r8, r7,
                                            r6, r5, r4, r3, r2, r1, r0>>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class _7, class _8, class _9, class _10, class _11, class _12,
             class _13, class _14, class _15, class... xs>
    using f = typename g<F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,
                         _13, _14, _15>::
        template f<remaining - 15, _scan_right<remaining - 15>, C, F, xs...>;
  };

  template<> struct _scan_right<64> {
    template<
        template<class...> class F, class r0, class _1, class _2, class _3,
        class _4, class _5, class _6, class _7, class _8, class _9, class _10,
        class _11, class _12, class _13, class _14, class _15, class _16,
        class _17, class _18, class _19, class _20, class _21, class _22,
        class _23, class _24, class _25, class _26, class _27, class _28,
        class _29, class _30, class _31, class r1 = F<_1, r0>,
        class r2 = F<_2, r1>, class r3 = F<_3, r2>, class r4 = F<_4, r3>,
        class r5 = F<_5, r4>, class r6 = F<_6, r5>, class r7 = F<_7, r6>,
        class r8 = F<_8, r7>, class r9 = F<_9, r8>, class r10 = F<_10, r9>,
        class r11 = F<_11, r10>, class r12 = F<_12, r11>, class r13 = F<_13, r12>,
        class r14 = F<_14, r13>, class r15 = F<_15, r14>, class r16 = F<_16, r15>,
        class r17 = F<_17, r16>, class r18 = F<_18, r17>, class r19 = F<_19, r18>,
        class r20 = F<_20, r19>, class r21 = F<_21, r20>, class r22 = F<_22, r21>,
        class r23 = F<_23, r22>, class r24 = F<_24, r23>, class r25 = F<_25, r24>,
        class r26 = F<_26, r25>, class r27 = F<_27, r26>, class r28 = F<_28, r27>,
        class r29 = F<_29, r28>, class r30 = F<_30, r29>>
    using g =
        scan_continuation<F<_31, r30>,
                          list<r30, r29, r28, r27, r26, r25, r24, r23, r22, r21,
                               r20, r19, r18, r17, r16, r15, r14, r13, r12, r11,
                               r10, r9, r8, r7, r6, r5, r4, r3, r2, r1, r0>>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class _7, class _8, class _9, class _10, class _11, class _12,
             class _13, class _14, class _15, class _16, class _17, class _18,
             class _19, class _20, class _21, class _22, class _23, class _24,
             class _25, class _26, class _27, class _28, class _29, class _30,
             class _31, class... xs>
    using f = typename g<F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,
                         _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23,
                         _24, _25, _26, _27, _28, _29, _30, _31>::
        template f<remaining - 31, _scan_right<remaining - 31>, C, F, xs...>;
  };

  template<> struct _scan_right<128> {
    template<
        template<class...> class F, class r0, class _1, class _2, class _3,
        class _4, class _5, class _6, class _7, class _8, class _9, class _10,
        class _11, class _12, class _13, class _14, class _15, class _16,
        class _17, class _18, class _19, class _20, class _21, class _22,
        class _23, class _24, class _25, class _26, class _27, class _28,
        class _29, class _30, class _31, class _32, class _33, class _34,
        class _35, class _36, class _37, class _38, class _39, class _40,
        class _41, class _42, class _43, class _44, class _45, class _46,
        class _47, class _48, class _49, class _50, class _51, class _52,
        class _53, class _54, class _55, class _56, class _57, class _58,
        class _59, class _60, class _61, class _62, class _63,
        class r1 = F<_1, r0>, class r2 = F<_2, r1>, class r3 = F<_3, r2>,
        class r4 = F<_4, r3>, class r5 = F<_5, r4>, class r6 = F<_6, r5>,
        class r7 = F<_7, r6>, class r8 = F<_8, r7>, class r9 = F<_9, r8>,
        class r10 = F<_10, r9>, class r11 = F<_11, r10>, class r12 = F<_12, r11>,
        class r13 = F<_13, r12>, class r14 = F<_14, r13>, class r15 = F<_15, r14>,
        class r16 = F<_16, r15>, class r17 = F<_17, r16>, class r18 = F<_18, r17>,
        class r19 = F<_19, r18>, class r20 = F<_20, r19>, class r21 = F<_21, r20>,
        class r22 = F<_22, r21>, class r23 = F<_23, r22>, class r24 = F<_24, r23>,
        class r25 = F<_25, r24>, class r26 = F<_26, r25>, class r27 = F<_27, r26>,
        class r28 = F<_28, r27>, class r29 = F<_29, r28>, class r30 = F<_30, r29>,
        class r31 = F<_31, r30>, class r32 = F<_32, r31>, class r33 = F<_33, r32>,
        class r34 = F<_34, r33>, class r35 = F<_35, r34>, class r36 = F<_36, r35>,
        class r37 = F<_37, r36>, class r38 = F<_38, r37>, class r39 = F<_39, r38>,
        class r40 = F<_40, r39>, class r41 = F<_41, r40>, class r42 = F<_42, r41>,
        class r43 = F<_43, r42>, class r44 = F<_44, r43>, class r45 = F<_45, r44>,
        class r46 = F<_46, r45>, class r47 = F<_47, r46>, class r48 = F<_48, r47>,
        class r49 = F<_49, r48>, class r50 = F<_50, r49>, class r51 = F<_51, r50>,
        class r52 = F<_52, r51>, class r53 = F<_53, r52>, class r54 = F<_54, r53>,
        class r55 = F<_55, r54>, class r56 = F<_56, r55>, class r57 = F<_57, r56>,
        class r58 = F<_58, r57>, class r59 = F<_59, r58>, class r60 = F<_60, r59>,
        class r61 = F<_61, r60>, class r62 = F<_62, r61>>
    using g = scan_continuation<
        F<_63, r62>,
        list<r62, r61, r60, r59, r58, r57, r56, r55, r54, r53, r52, r51, r50, r49,
             r48, r47, r46, r45, r44, r43, r42, r41, r40, r39, r38, r37, r36, r35,
             r34, r33, r32, r31, r30, r29, r28, r27, r26, r25, r24, r23, r22, r21,
             r20, r19, r18, r17, r16, r15, r14, r13, r12, r11, r10, r9, r8, r7,
             r6, r5, r4, r3, r2, r1, r0>>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class _7, class _8, class _9, class _10, class _11, class _12,
             class _13, class _14, class _15, class _16, class _17, class _18,
             class _19, class _20, class _21, class _22, class _23, class _24,
             class _25, class _26, class _27, class _28, class _29, class _30,
             class _31, class _32, class _33, class _34, class _35, class _36,
             class _37, class _38, class _39, class _40, class _41, class _42,
             class _43, class _44, class _45, class _46, class _47, class _48,
             class _49, class _50, class _51, class _52, class _53, class _54,
             class _55, class _56, class _57, class _58, class _59, class _60,
             class _61, class _62, class _63, class... xs>
    using f = typename g<F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,
                         _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23,
                         _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34,
                         _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
                         _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
                         _57, _58, _59, _60, _61, _62, _63>::
        template f<remaining - 63, _scan_right<remaining - 63>, C, F, xs...>;
  };

  template<> struct _scan_right<256> {
    template<
        template<class...> class F, class r0, class _1, class _2, class _3,
        class _4, class _5, class _6, class _7, class _8, class _9, class _10,
        class _11, class _12, class _13, class _14, class _15, class _16,
        class _17, class _18, class _19, class _20, class _21, class _22,
        class _23, class _24, class _25, class _26, class _27, class _28,
        class _29, class _30, class _31, class _32, class _33, class _34,
        class _35, class _36, class _37, class _38, class _39, class _40,
        class _41, class _42, class _43, class _44, class _45, class _46,
        class _47, class _48, class _49, class _50, class _51, class _52,
        class _53, class _54, class _55, class _56, class _57, class _58,
        class _59, class _60, class _61, class _62, class _63, class _64,
        class _65, class _66, class _67, class _68, class _69, class _70,
        class _71, class _72, class _73, class _74, class _75, class _76,
        class _77, class _78, class _79, class _80, class _81, class _82,
        class _83, class _84, class _85, class _86, class _87, class _88,
        class _89, class _90, class _91, class _92, class _93, class _94,
        class _95, class _96, class _97, class _98, class _99, class _100,
        class _101, class _102, class _103, class _104, class _105, class _106,
        class _107, class _108, class _109, class _110, class _111, class _112,
        class _113, class _114, class _115, class _116, class _117, class _118,
        class _119, class _120, class _121, class _122, class _123, class _124,
        class _125, class _126, class _127, class r1 = F<_1, r0>,
        class r2 = F<_2, r1>, class r3 = F<_3, r2>, class r4 = F<_4, r3>,
        class r5 = F<_5, r4>, class r6 = F<_6, r5>, class r7 = F<_7, r6>,
        class r8 = F<_8, r7>, class r9 = F<_9, r8>, class r10 = F<_10, r9>,
        class r11 = F<_11, r10>, class r12 = F<_12, r11>, class r13 = F<_13, r12>,
        class r14 = F<_14, r13>, class r15 = F<_15, r14>, class r16 = F<_16, r15>,
        class r17 = F<_17, r16>, class r18 = F<_18, r17>, class r19 = F<_19, r18>,
        class r20 = F<_20, r19>, class r21 = F<_21, r20>, class r22 = F<_22, r21>,
        class r23 = F<_23, r22>, class r24 = F<_24, r23>, class r25 = F<_25, r24>,
        class r26 = F<_26, r25>, class r27 = F<_27, r26>, class r28 = F<_28, r27>,
        class r29 = F<_29, r28>, class r30 = F<_30, r29>, class r31 = F<_31, r30>,
        class r32 = F<_32, r31>, class r33 = F<_33, r32>, class r34 = F<_34, r33>,
        class r35 = F<_35, r34>, class r36 = F<_36, r35>, class r37 = F<_37, r36>,
        class r38 = F<_38, r37>, class r39 = F<_39, r38>, class r40 = F<_40, r39>,
        class r41 = F<_41, r40>, class r42 = F<_42, r41>, class r43 = F<_43, r42>,
        class r44 = F<_44, r43>, class r45 = F<_45, r44>, class r46 = F<_46, r45>,
        class r47 = F<_47, r46>, class r48 = F<_48, r47>, class r49 = F<_49, r48>,
        class r50 = F<_50, r49>, class r51 = F<_51, r50>, class r52 = F<_52, r51>,
        class r53 = F<_53, r52>, class r54 = F<_54, r53>, class r55 = F<_55, r54>,
        class r56 = F<_56, r55>, class r57 = F<_57, r56>, class r58 = F<_58, r57>,
        class r59 = F<_59, r58>, class r60 = F<_60, r59>, class r61 = F<_61, r60>,
        class r62 = F<_62, r61>, class r63 = F<_63, r62>, class r64 = F<_64, r63>,
        class r65 = F<_65, r64>, class r66 = F<_66, r65>, class r67 = F<_67, r66>,
        class r68 = F<_68, r67>, class r69 = F<_69, r68>, class r70 = F<_70, r69>,
        class r71 = F<_71, r70>, class r72 = F<_72, r71>, class r73 = F<_73, r72>,
        class r74 = F<_74, r73>, class r75 = F<_75, r74>, class r76 = F<_76, r75>,
        class r77 = F<_77, r76>, class r78 = F<_78, r77>, class r79 = F<_79, r78>,
        class r80 = F<_80, r79>, class r81 = F<_81, r80>, class r82 = F<_82, r81>,
        class r83 = F<_83, r82>, class r84 = F<_84, r83>, class r85 = F<_85, r84>,
        class r86 = F<_86, r85>, class r87 = F<_87, r86>, class r88 = F<_88, r87>,
        class r89 = F<_89, r88>, class r90 = F<_90, r89>, class r91 = F<_91, r90>,
        class r92 = F<_92, r91>, class r93 = F<_93, r92>, class r94 = F<_94, r93>,
        class r95 = F<_95, r94>, class r96 = F<_96, r95>, class r97 = F<_97, r96>,
        class r98 = F<_98, r97>, class r99 = F<_99, r98>,
        class r100 = F<_100, r99>, class r101 = F<_101, r100>,
        class r102 = F<_102, r101>, class r103 = F<_103, r102>,
        class r104 = F<_104, r103>, class r105 = F<_105, r104>,
        class r106 = F<_106, r105>, class r107 = F<_107, r106>,
        class r108 = F<_108, r107>, class r109 = F<_109, r108>,
        class r110 = F<_110, r109>, class r111 = F<_111, r110>,
        class r112 = F<_112, r111>, class r113 = F<_113, r112>,
        class r114 = F<_114, r113>, class r115 = F<_115, r114>,
        class r116 = F<_116, r115>, class r117 = F<_117, r116>,
        class r118 = F<_118, r117>, class r119 = F<_119, r118>,
        class r120 = F<_120, r119>, class r121 = F<_121, r120>,
        class r122 = F<_122, r121>, class r123 = F<_123, r122>,
        class r124 = F<_124, r123>, class r125 = F<_125, r124>,
        class r126 = F<_126, r125>>
    using g = scan_continuation<
        F<_127, r126>,
        list<r126, r125, r124, r123, r122, r121, r120, r119, r118, r117, r116,
             r115, r114, r113, r112, r111, r110, r109, r108, r107, r106, r105,
             r104, r103, r102, r101, r100, r99, r98, r97, r96, r95, r94, r93, r92,
             r91, r90, r89, r88, r87, r86, r85, r84, r83, r82, r81, r80, r79, r78,
             r77, r76, r75, r74, r73, r72, r71, r70, r69, r68, r67, r66, r65, r64,
             r63, r62, r61, r60, r59, r58, r57, r56, r55, r54, r53, r52, r51, r50,
             r49, r48, r47, r46, r45, r44, r43, r42, r41, r40, r39, r38, r37, r36,
             r35, r34, r33, r32, r31, r30, r29, r28, r27, r26, r25, r24, r23, r22,
             r21, r20, r19, r18, r17, r16, r15, r14, r13, r12, r11, r10, r9, r8,
             r7, r6, r5, r4, r3, r2, r1, r0>>;

    template<
        unsigned remaining, class C, template<class...> class F, class _0,
        class _1, class _2, class _3, class _4, class _5, class _6, class _7,
        class _8, class _9, class _10, class _11, class _12, class _13, class _14,
        class _15, class _16, class _17, class _18, class _19, class _20,
        class _21, class _22, class _23, class _24, class _25, class _26,
        class _27, class _28, class _29, class _30, class _31, class _32,
        class _33, class _34, class _35, class _36, class _37, class _38,
        class _39, class _40, class _41, class _42, class _43, class _44,
        class _45, class _46, class _47, class _48, class _49, class _50,
        class _51, class _52, class _53, class _54, class _55, class _56,
        class _57, class _58, class _59, class _60, class _61, class _62,
        class _63, class _64, class _65, class _66, class _67, class _68,
        class _69, class _70, class _71, class _72, class _73, class _74,
        class _75, class _76, class _77, class _78, class _79, class _80,
        class _81, class _82, class _83, class _84, class _85, class _86,
        class _87, class _88, class _89, class _90, class _91, class _92,
        class _93, class _94, class _95, class _96, class _97, class _98,
        class _99, class _100, class _101, class _102, class _103, class _104,
        class _105, class _106, class _107, class _108, class _109, class _110,
        class _111, class _112, class _113, class _114, class _115, class _116,
        class _117, class _118, class _119, class _120, class _121, class _122,
        class _123, class _124, class _125, class _126, class _127, class... xs>
    using f = typename g<
        F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15,
        _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,
        _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
        _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
        _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75,
        _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90,
        _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104,
        _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116,
        _117, _118, _119, _120, _121, _122, _123, _124, _125, _126, _127>::
        template f<remaining - 127, _scan_right<remaining - 127>, C, F, xs...>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class F, class C = listify>
  using scan_right = contract<mp::scan_right<
    monadic_xs<assume_binary<F>>,
    monadic_xs<subcontract<C>>
  >>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, scan_right<F, C>>
  {
    using type = smp::scan_right<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup list

  /// Removes \c N elements from the end of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see drop_back_max, drop_front, take_front, take_back, drop_while
  template<unsigned N, class C = listify>
  struct drop_back_c
  : rotate_c<-int_(N), drop_front_c<N, C>>
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  /// Removes at most \c N elements from the end of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see drop_back, drop_front, drop_while
  template<unsigned N, class C = listify>
  struct drop_back_max_c
  {
    template<class... xs>
    using f = typename rotate_c<-int_(N),
      drop_front_c<detail::min(N, sizeof...(xs)), C>
    >::template f<xs...>;
  };

  template<class N, class C = listify>
  using drop_back = drop_back_c<N::value, C>;

  template<class N, class C = listify>
  using drop_back_max = drop_back_max_c<N::value, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using drop_back = unpack<L, mp::drop_back<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using drop_back_c = unpack<L, mp::drop_back_c<n, C>>;

    template<class L, class N, class C = mp::listify>
    using drop_back_max = unpack<L, mp::drop_back_max<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using drop_back_max_c = unpack<L, mp::drop_back_max_c<n, C>>;
  }

  /// \cond
  template<class C>
  struct drop_back_c<0, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };

  template<class C>
  struct drop_back_max_c<0, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };
  /// \endcond
}
/// \cond
namespace jln::mp::detail
{
  template<std::size_t ExtendedByN, class C>
  struct smp_take_drop_for_size
  {
    template<class... xs>
    using f = mp::drop_back_c<
      sizeof...(xs) >= ExtendedByN ? sizeof...(xs) - ExtendedByN : 0,
      subcontract<C>
    >;
  };
}
/// \endcond

namespace jln::mp::smp
{
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_while_extended_by_n_c = contract<mp::invoke_twice<
    mp::drop_while<
      concepts::strong_predicate<assume_unary<Pred>, mp::identity, mp::always<false_>>,
      mp::if_<
        mp::front<concepts::strong_predicate<assume_unary<Pred>, mp::always<true_>>>,
        detail::smp_take_drop_for_size<ExtendedByN, TC>,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_while = take_while_extended_by_n_c<0, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_while = take_while_extended_by_n_c<1, Pred, TC, FC>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(take_while_extended_by_n,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::take_while_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, take_while<Pred, TC, FC>>
  {
    using type = smp::take_while<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, std::size_t ExtendedByN, class Pred, class TC, class FC>
  struct _sfinae<sfinae, take_while_extended_by_n_c<ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::take_while_extended_by_n_c<ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_until_extended_by_n_xs_c = contract<mp::invoke_twice<
    mp::drop_until_xs<
      concepts::strong_predicate<assume_unary_or_more<Pred>, mp::identity, mp::always<true_>>,
      mp::if_<
        concepts::strong_predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
        detail::smp_take_drop_for_size<ExtendedByN, TC>,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_until_xs = take_until_extended_by_n_xs_c<0, Pred, TC, FC>;

  template<int_ OffsetEnd, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_take_until_extended_by_n_xs_c = contract<mp::invoke_twice<
    mp::partial_drop_until_xs_c<
      OffsetEnd,
      concepts::strong_predicate<assume_unary_or_more<Pred>, mp::identity, mp::always<true_>>,
      mp::if_<
        concepts::strong_predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
        detail::smp_take_drop_for_size<ExtendedByN, TC>,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_until_xs_c = partial_take_until_extended_by_n_xs_c<OffsetEnd, 0, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_until_xs = take_until_extended_by_n_xs_c<1, Pred, TC, FC>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_inclusive_until_xs_c = partial_take_until_extended_by_n_xs_c<
    OffsetEnd, 1, Pred, TC, FC>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(partial_take_until_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_take_until_xs_c<OffsetEnd::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP4_P(partial_take_inclusive_until_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_take_inclusive_until_xs_c<OffsetEnd::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP4_P(take_until_extended_by_n_xs,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::take_until_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP5_P(partial_take_until_extended_by_n_xs,
  (OffsetEnd), (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_take_until_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>)


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, take_until_xs<Pred, TC, FC>>
  {
    using type = smp::take_until_xs<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, std::size_t ExtendedByN, class Pred, class TC, class FC>
  struct _sfinae<sfinae, take_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::take_until_extended_by_n_xs_c<
      ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>
    >;
  };

  template<template<class> class sfinae, int_ OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC, class FC>
  struct _sfinae<sfinae, partial_take_until_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::partial_take_until_extended_by_n_xs_c<
      OffsetEnd, ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>
    >;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup search

  /// Search the first sub-\sequence that satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// Calls \c TC with all the elements from sub-\sequence found at the end.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search_before, partial_search, after, index_if
  /// \see search_before_extended_by_n
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using search = drop_until_xs<Pred, TC, FC>;

  /// Search elements before sub-\sequence that satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// Calls \c TC with the elements from the beginning to sub-\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, partial_search, after, index_if
  /// \see search_before_extended_by_n
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using search_before = take_until_xs<Pred, TC, FC>;

  /// Search elements before sub-\sequence that satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// Calls \c TC with the elements from the beginning to sub-\sequence found + \c ExtendedByN.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, search_before, partial_search, after, index_if
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using search_before_extended_by_n = take_until_extended_by_n_xs<ExtendedByN, Pred, TC, FC>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using search_before_extended_by_n_c = take_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>;

  /// Same \c search, but it stops when there is StopWhenAtLeast::value element or less.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see search, search_before, after, index_if
  /// \see search_before_extended_by_n
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search = partial_drop_until_xs_c<-int_{StopWhenAtLeast::value}-1, Pred, TC, FC>;

  template<std::size_t StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_c = partial_drop_until_xs_c<-int_{StopWhenAtLeast}-1, Pred, TC, FC>;

  /// Same \c search_before, but it stops when there is StopWhenAtLeast::value element or less.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see search, search_before, partial_search, after, index_if
  /// \see search_before_extended_by_n, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_before = partial_take_until_xs_c<-int_{StopWhenAtLeast::value}-1, Pred, TC, FC>;

  template<std::size_t StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_before_c = partial_take_until_xs_c<-int_{StopWhenAtLeast}-1, Pred, TC, FC>;

  /// Same \c search_before, but it stops when there is StopWhenAtLeast::value element or less.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see search, search_before, partial_search, after, index_if
  /// \see search_before_extended_by_n, partial_search_before
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<std::size_t StopWhenAtLeast, std::size_t ExtendedByN, class Pred,
           class TC = listify, class FC = clear<TC>>
  using partial_search_before_extended_by_n_c = partial_take_until_extended_by_n_xs_c<
    -int_{StopWhenAtLeast}-1, ExtendedByN, Pred, TC, FC>;

  template<class StopWhenAtLeast, class ExtendedByN, class Pred,
           class TC = listify, class FC = clear<TC>>
  using partial_search_before_extended_by_n = partial_take_until_extended_by_n_xs_c<
    -int_{StopWhenAtLeast::value}-1, ExtendedByN::value, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using search = unpack<L, mp::search<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using search_before = unpack<L, mp::search_before<Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using search_before_extended_by_n = unpack<L,
      mp::search_before_extended_by_n<ExtendedByN, Pred, TC, FC>>;


    template<class L, class StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search = unpack<L, mp::partial_search<Pred, StopWhenAtLeast, TC, FC>>;

    template<class L, class StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before = unpack<L,
      mp::partial_search_before<Pred, StopWhenAtLeast, TC, FC>>;

    template<class L, class StopWhenAtLeast, class ExtendedByN, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before_extended_by_n = unpack<L,
      mp::partial_search_before_extended_by_n<StopWhenAtLeast, ExtendedByN, Pred, TC, FC>>;


    template<class L, std::size_t StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_c = unpack<L, mp::partial_search_c<StopWhenAtLeast, Pred, TC, FC>>;

    template<class L, std::size_t StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before_c = unpack<L,
      mp::partial_search_before_c<StopWhenAtLeast, Pred, TC, FC>>;

    template<class L, std::size_t StopWhenAtLeast, std::size_t ExtendedByN, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before_extended_by_n_c = unpack<L,
      mp::partial_search_before_extended_by_n_c<StopWhenAtLeast, ExtendedByN, Pred, TC, FC>>;
  }
}
namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using search = drop_until_xs<Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using search_before = take_until_xs<Pred, TC, FC>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using search_before_extended_by_n_c = take_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>;

  template<std::size_t StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_c = partial_drop_until_xs_c<-int_{StopWhenAtLeast}-1, Pred, TC, FC>;

  template<std::size_t StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_before_c = partial_take_until_xs_c<-int_{StopWhenAtLeast}-1, Pred, TC, FC>;

  template<std::size_t StopWhenAtLeast, std::size_t ExtendedByN, class Pred,
           class TC = listify, class FC = clear<TC>>
  using partial_search_before_extended_by_n_c = partial_take_until_extended_by_n_xs_c<
    -int_{StopWhenAtLeast}-1, ExtendedByN, Pred, TC, FC>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(search_before_extended_by_n,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, smp::clear<TC>),
  smp::search_before_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP4_P(partial_search,
  (StopWhenAtLeast), (Pred), (TC, smp::listify), (FC, smp::clear<TC>),
  smp::partial_search_c<StopWhenAtLeast::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP4_P(partial_search_before,
  (StopWhenAtLeast), (Pred), (TC, smp::listify), (FC, smp::clear<TC>),
  smp::partial_search_before_c<StopWhenAtLeast::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP5_P(partial_search_before_extended_by_n,
  (StopWhenAtLeast), (ExtendedByN), (Pred), (TC, smp::listify), (FC, smp::clear<TC>),
  smp::partial_search_before_extended_by_n_c<
    StopWhenAtLeast::value, ExtendedByN::value, Pred, TC, FC>)
namespace jln::mp
{
  /// \ingroup search

  /// Remove the first elements of a \sequence that does not satisfy a \predicate.
  /// \pre \c Pred::f<x> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see skip_while, skip_until_xs
  /// \see drop_while, drop_until
  /// \see take_while, take_until
  template<class Pred, class TC = listify, class FC = TC>
  using skip_until = drop_until<Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_until = drop_inclusive_until<Pred, TC, clear<FC>>;

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_until_extended_by_n = drop_until_extended_by_n_c<
    ExtendedByN::value, Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_until_extended_by_n_c = drop_until_extended_by_n_c<
    ExtendedByN, Pred, TC, clear<FC>>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_until = unpack<L, mp::skip_until<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_inclusive_until = unpack<L, mp::skip_inclusive_until<Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_until_extended_by_n_c = unpack<L,
      mp::skip_until_extended_by_n_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_until_extended_by_n = unpack<L,
      mp::skip_until_extended_by_n<ExtendedByN, Pred, TC, FC>>;
  }
}
namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = TC>
  using skip_until = drop_until<Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_until = drop_inclusive_until<Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_until_extended_by_n_c = skip_until<
    Pred, contract<mp::drop_front_max_c<ExtendedByN, subcontract<TC>>>, subcontract<clear<FC>>>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(skip_until_extended_by_n,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::skip_until_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>)
namespace jln::mp
{
  /// \ingroup search

  /// Remove the first elements of a \sequence that does not satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see skip_until, partial_skip_until_xs, skip_inclusive_until_xs
  /// \see take_until_xs, take_while_xs
  /// \see drop_until_xs, drop_while_xs
  template<class Pred, class TC = listify, class FC = TC>
  using skip_until_xs = drop_until_xs<Pred, TC, clear<FC>>;

  /// Same as \c drop_until_xs, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see skip_until, skip_until_xs, skip_inclusive_until_xs
  /// \see take_until_xs, take_while_xs
  /// \see drop_until_xs, drop_while_xs
  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_until_xs_c = partial_drop_until_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_until_xs = partial_drop_until_xs<OffsetEnd, Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_until_xs = drop_inclusive_until_xs<Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_until_xs_c
    = partial_drop_inclusive_until_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_until_xs
    = partial_drop_inclusive_until_xs<OffsetEnd, Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_until_extended_by_n_xs_c
    = drop_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, clear<FC>>;

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_until_extended_by_n_xs
    = drop_until_extended_by_n_xs<ExtendedByN, Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_skip_until_extended_by_n_xs_c
    = partial_drop_until_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_skip_until_extended_by_n_xs
    = partial_drop_until_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_until_xs = unpack<L, mp::skip_until_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_until_xs = unpack<L,
      mp::partial_skip_until_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_until_xs_c = unpack<L,
      mp::partial_skip_until_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_inclusive_until_xs = unpack<L, mp::skip_inclusive_until_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_inclusive_until_xs = unpack<L,
      mp::partial_skip_inclusive_until_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_inclusive_until_xs_c = unpack<L,
      mp::partial_skip_inclusive_until_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_until_extended_by_n_xs_c = unpack<L,
      mp::drop_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, clear<FC>>>;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_until_extended_by_n_xs = unpack<L,
      mp::drop_until_extended_by_n_xs<ExtendedByN, Pred, TC, clear<FC>>>;

    template<class L, int_ OffsetEnd, std::size_t ExtendedByN,
             class Pred, class TC = listify, class FC = TC>
    using partial_skip_until_extended_by_n_xs_c = unpack<L,
      mp::partial_drop_until_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>>;

    template<class L, class OffsetEnd, class ExtendedByN,
             class Pred, class TC = listify, class FC = TC>
    using partial_skip_until_extended_by_n_xs = unpack<L,
      mp::partial_drop_until_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>>;
  }
}
namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = TC>
  using skip_until_xs = drop_until_xs<Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_until_xs_c = partial_drop_until_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_until_xs = drop_inclusive_until_xs<Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_until_xs_c
    = partial_drop_inclusive_until_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_until_extended_by_n_xs_c
    = drop_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC = listify, class FC = TC>
  using partial_skip_until_extended_by_n_xs_c
    = partial_drop_until_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(partial_skip_until_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_skip_until_xs_c<OffsetEnd::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP4_P(partial_skip_inclusive_until_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_skip_inclusive_until_xs_c<OffsetEnd::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP4_P(skip_until_extended_by_n_xs,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::skip_until_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP5_P(partial_skip_until_extended_by_n_xs,
  (OffsetEnd), (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_skip_until_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>)
namespace jln::mp
{
  /// \ingroup search

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// \pre \c Pred::f<x> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see skip_until, skip_while_xs
  /// \see drop_while, drop_until
  /// \see take_while, take_until
  template<class Pred, class TC = listify, class FC = TC>
  using skip_while = drop_while<Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_while = drop_inclusive_while<Pred, TC, clear<FC>>;

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n = drop_while_extended_by_n_c<
    ExtendedByN::value, Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n_c = drop_while_extended_by_n_c<
    ExtendedByN, Pred, TC, clear<FC>>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_while = unpack<L, mp::skip_while<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_inclusive_while = unpack<L, mp::skip_inclusive_while<Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_while_extended_by_n_c = unpack<L,
      mp::skip_while_extended_by_n_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_while_extended_by_n = unpack<L,
      mp::skip_while_extended_by_n<ExtendedByN, Pred, TC, FC>>;
  }
}
namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = TC>
  using skip_while = drop_while<Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_while = drop_inclusive_while<Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n_c = skip_while<
    Pred, contract<mp::drop_front_max_c<ExtendedByN, subcontract<TC>>>, subcontract<clear<FC>>>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(skip_while_extended_by_n,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::skip_while_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>)
namespace jln::mp
{
  /// \ingroup search

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// Same as \c skip_while, but the \predicate takes all the elements of
  /// the current position until the end of the list.
  /// \treturn \sequence
  /// \see skip_while, partial_skip_while_xs, skip_inclusive_while_xs
  /// \see take_while_xs, take_until_xs
  /// \see drop_while_xs, drop_until_xs
  template<class Pred, class TC = listify, class FC = TC>
  using skip_while_xs = drop_while_xs<Pred, TC, clear<FC>>;

  /// Same as \c skip_while_xs, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see skip_while, skip_while_xs, skip_inclusive_while_xs
  /// \see take_while_xs, take_until_xs
  /// \see drop_while_xs, drop_until_xs
  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_xs_c = partial_drop_while_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_xs = partial_drop_while_xs<OffsetEnd, Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_while_xs = drop_inclusive_while_xs<Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_while_xs_c
    = partial_drop_inclusive_while_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_while_xs
    = partial_drop_inclusive_while_xs<OffsetEnd, Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n_xs_c
    = drop_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, clear<FC>>;

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n_xs
    = drop_while_extended_by_n_xs<ExtendedByN, Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_extended_by_n_xs_c
    = partial_drop_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_extended_by_n_xs
    = partial_drop_while_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_while_xs = unpack<L, mp::skip_while_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_while_xs = unpack<L,
      mp::partial_skip_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_while_xs_c = unpack<L,
      mp::partial_skip_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_inclusive_while_xs = unpack<L, mp::skip_inclusive_while_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_inclusive_while_xs = unpack<L,
      mp::partial_skip_inclusive_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_inclusive_while_xs_c = unpack<L,
      mp::partial_skip_inclusive_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_while_extended_by_n_xs_c = unpack<L,
      mp::drop_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, clear<FC>>>;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_while_extended_by_n_xs = unpack<L,
      mp::drop_while_extended_by_n_xs<ExtendedByN, Pred, TC, clear<FC>>>;

    template<class L, int_ OffsetEnd, std::size_t ExtendedByN,
             class Pred, class TC = listify, class FC = TC>
    using partial_skip_while_extended_by_n_xs_c = unpack<L,
      mp::partial_drop_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>>;

    template<class L, class OffsetEnd, class ExtendedByN,
             class Pred, class TC = listify, class FC = TC>
    using partial_skip_while_extended_by_n_xs = unpack<L,
      mp::partial_drop_while_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>>;
  }
}
namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = TC>
  using skip_while_xs = drop_while_xs<Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_xs_c = partial_drop_while_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_while_xs = drop_inclusive_while_xs<Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_while_xs_c
    = partial_drop_inclusive_while_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n_xs_c
    = drop_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_extended_by_n_xs_c
    = partial_drop_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(partial_skip_while_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_skip_while_xs_c<OffsetEnd::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP4_P(partial_skip_inclusive_while_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_skip_inclusive_while_xs_c<OffsetEnd::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP4_P(skip_while_extended_by_n_xs,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::skip_while_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP5_P(partial_skip_while_extended_by_n_xs,
  (OffsetEnd), (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_skip_while_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>)
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int n>
    struct sort_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Sorts the elements of a \sequence according to an ordering relation.
  /// \post \c is_sorted<result...>
  /// \treturn \sequence
  template<class Cmp = less<>, class C = listify>
  struct sort
  {
    template<class... xs>
    using f = typename unpack<C>::template f<
      typename detail::sort_impl<sizeof...(xs)>
      ::template f<Cmp, xs...>
    >;
  };

  template<class Cmp = less<>, class C = listify>
  using stable_sort = sort<Cmp, C>;

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = listify>
    using sort = unpack<L, mp::sort<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = listify>
    using stable_sort = unpack<L, mp::sort<Cmp, C>>;
  }
}


namespace jln::mp
{
  /// \cond
  template<class Cmp>
  struct sort<Cmp, listify>
  {
    template<class... xs>
    using f = typename detail::sort_impl<sizeof...(xs)>
      ::template f<Cmp, xs...>;
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_list2;

  template<>
  struct mk_list2<false>
  {
    template<class... xs>
    using f = list<xs...>;
  };

  template<>
  struct mk_list2<true>
  {
    template<class x, class y>
    using f = list<y, x>;
  };


  template<int n>
  struct sort_impl : sort_impl<
      n <= 8 ? 8
    : n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : 128
  >
  {};

  template<>
  struct sort_impl<0>
  {
    template<class Cmp>
    using f = list<>;
  };

  template<>
  struct sort_impl<1>
  {
    template<class Cmp, class x>
    using f = list<x>;
  };

  template<class Cmp, class x, class y>
  using sort_pair = typename mk_list2<JLN_MP_TRACE_F(Cmp)::template f<y, x>::value>
    ::template f<x, y>;

  template<>
  struct sort_impl<2>
  {
    template<class Cmp, class x, class y>
    using f = sort_pair<Cmp, x, y>;
  };

  template<>
  struct sort_impl<3>
  {
    template<class Cmp, class x1, class x2, class x3>
    using f = typename merge_impl<
      list<>,
      sort_pair<Cmp, x1, x2>,
      list<x3>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<4>
  {
    template<class Cmp, class x1, class x2, class x3, class x4>
    using f = typename merge_impl<
      list<>,
      sort_pair<Cmp, x1, x2>,
      sort_pair<Cmp, x3, x4>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<5>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5>
    using f = typename merge_impl<
      list<>,
      sort_pair<Cmp, x1, x2>,
      typename sort_impl<3>::template f<Cmp, x3, x4, x5>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<6>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<3>::template f<Cmp, x1, x2, x3>,
      typename sort_impl<3>::template f<Cmp, x4, x5, x6>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<7>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6, class x7>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<4>::template f<Cmp, x1, x2, x3, x4>,
      typename sort_impl<3>::template f<Cmp, x5, x6, x7>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<8>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6, class x7, class x8>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<4>::template f<Cmp, x1, x2, x3, x4>,
      typename sort_impl<4>::template f<Cmp, x5, x6, x7, x8>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<16>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6, class x7, class x8, class... xs>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<8>::template f<Cmp, x1, x2, x3, x4, x5, x6, x7, x8>,
      typename sort_impl<sizeof...(xs)>::template f<Cmp, xs...>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<32>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6, class x7, class x8, class x9, class x10, class x11,
             class x12, class x13, class x14, class x15, class x16, class... xs>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<16>::template f<
        Cmp, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16>,
      typename sort_impl<sizeof...(xs)>::template f<Cmp, xs...>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<64>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6, class x7, class x8, class x9, class x10, class x11,
             class x12, class x13, class x14, class x15, class x16, class x17,
             class x18, class x19, class x20, class x21, class x22, class x23,
             class x24, class x25, class x26, class x27, class x28, class x29,
             class x30, class x31, class x32, class... xs>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<32>::template f<
        Cmp, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15,
        x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29,
        x30, x31, x32>,
      typename sort_impl<sizeof...(xs)>::template f<Cmp, xs...>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<128>
  {
    template<class Cmp, class... xs>
    using f = typename merge_impl<
      list<>,
      typename take_front_c<sizeof...(xs) / 2, sort<Cmp>>::template f<xs...>,
      typename drop_front_c<sizeof...(xs) / 2, sort<Cmp>>::template f<xs...>,
      Cmp
    >::type;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = listify>
  using sort = contract<mp::sort<
    concepts::strong_predicate_or<assume_binary<Cmp>, mp::always<true_>>,
    mp::if_<
      mp::try_or<is_sorted<Cmp>, mp::always<false_>>,
      subcontract<C>,
      violation
    >
  >>;

  template<class Cmp = less<>, class C = listify>
  using stable_sort = sort<Cmp, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, sort<Cmp, C>>
  {
    using type = smp::sort<sfinae<Cmp>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class F, class C = listify>
  using split_if = try_contract<
    mp::split_if<assume_unary<F>, assume_lists<C>>>;

  template<class x, class C = listify>
  using split = contract<mp::split<x, assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, split_if<F, C>>
  {
    using type = smp::split_if<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup group

  /// Splits a \sequence into multiple \lists at every point that satisfy a predicate.
  /// The split value is inserted at the end of the previous list.
  /// \semantics
  ///   \code
  ///   split_after_if<is<_0>>::f<_0, _1, _2, _0, _3>
  ///   == list<
  ///     list<_0>,
  ///     list<_1, _2, _0>,
  ///     list<_3>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see split_if, split_before_if
  template<class Pred, class C = listify>
  struct split_after_if
  {
    template <class... xs>
    using f = typename detail::_split<sizeof...(xs) != 0>
      ::template f<detail::split_after, C, JLN_MP_TRACE_F(Pred), xs...>;
  };

  template<class x, class C = listify>
  using split_after = split_after_if<is<x>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using split_after_if = unpack<L, mp::split_after_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using split_after = unpack<L, mp::split_after<x, C>>;
  }
}
namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using split_after_if = try_contract<
    mp::split_after_if<assume_unary<Pred>, assume_lists<C>>>;

  template<class x, class C = listify>
  using split_after = contract<mp::split_after<x, assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, split_after_if<F, C>>
  {
    using type = smp::split_after_if<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_take_front;

  template<bool>
  struct mk_take_front_max;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using take_front_c = typename detail::mk_take_front<n >= 0>
    ::template f<n, C>;

  template<int_ n, class C = listify>
  using take_front_max_c = typename detail::mk_take_front_max<n >= 0>
    ::template f<n, C>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(take_front, (N), (C, smp::listify), smp::take_front_c<N::value, C>)
JLN_MP_MAKE_REGULAR_SMP2_P(take_front_max, (N), (C, smp::listify), smp::take_front_max_c<N::value, C>)


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, take_front_c<N, C>>
  {
    using type = smp::take_front_c<N, sfinae<C>>;
  };

  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, take_front_max_c<N, C>>
  {
    using type = smp::take_front_max_c<N, sfinae<C>>;
  };

  template<>
  struct mk_take_front<true>
  {
    template<int_ n, class C>
    using f = test_contract<
      mp::size<mp::greater_equal_than_c<n>>,
      mp::take_front_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_take_front<false>
  {
    template<int_ i, int_ start, class C>
    using f = bad_contract;
  };

  template<>
  struct mk_take_front_max<true>
  {
    template<int_ n, class C>
    using f = contract<mp::take_front_max_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_take_front_max<false>
  {
    template<int_ i, int_ start, class C>
    using f = bad_contract;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup group

  /// Splits a sequence at an arbitrary position.
  /// \pre i >= 0 && i <= sizeof...(xs)
  /// \treturn \sequence of two \values
  template<unsigned i, class F = listify, class C = listify>
  using split_at_with_c = tee<take_front_c<i, F>, drop_front_c<i, F>, C>;

  template<class i, class F = listify, class C = listify>
  using split_at_with = split_at_with_c<i::value, F, C>;

  /// Splits a sequence at an arbitrary position.
  /// \pre i >= 0 && i <= sizeof...(xs)
  /// \treturn \sequence of two \lists
  template<unsigned i, class C = listify>
  using split_at_c = tee<take_front_c<i>, drop_front_c<i>, C>;

  template<class i, class C = listify>
  using split_at = split_at_c<i::value, C>;

  namespace emp
  {
    template<class L, class i, class F = mp::listify, class C = mp::listify>
    using split_at_with = unpack<L, mp::split_at_with<i, F, C>>;

    template<class L, unsigned i, class F = mp::listify, class C = mp::listify>
    using split_at_with_c = unpack<L, mp::split_at_with_c<i, F, C>>;

    template<class L, class i, class C = mp::listify>
    using split_at = unpack<L, mp::split_at<i, C>>;

    template<class L, unsigned i, class C = mp::listify>
    using split_at_c = unpack<L, mp::split_at_c<i, C>>;
  }
}
/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_smp_split_at;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ i, class F = listify, class C = listify>
  using split_at_with_c = typename detail::mk_smp_split_at<i >= 0>
    ::template f<i, C, mp::split_at_with_c, assume_binary<F>>;

  template<int_ i, class C = listify>
  using split_at_c = typename detail::mk_smp_split_at<i >= 0>
    ::template f<i, C, mp::split_at_c>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(split_at, (I), (C, smp::listify), smp::split_at_c<I::value, C>)
JLN_MP_MAKE_REGULAR_SMP3_P(split_at_with,
  (I), (F, smp::listify), (C, smp::listify), smp::split_at_with_c<I::value, F, C>)


/// \cond
namespace jln::mp::detail
{
  template<>
  struct mk_smp_split_at<true>
  {
    template<int_ i, class C, template<unsigned, class...> class Tpl, class... F>
    using f = test_contract<
      mp::size<mp::greater_equal_than_c<i>>,
      Tpl<i, F..., assume_binary_list<C>>>;
  };

  template<>
  struct mk_smp_split_at<false>
  {
    template<int_ i, class C, template<unsigned, class...> class Tpl, class... F>
    using f = bad_contract;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup group

  /// Splits a \sequence into multiple \lists at every point that satisfy a predicate.
  /// The split value is inserted at the beginning of the following list.
  /// \semantics
  ///   \code
  ///   split_before_if<is<_0>>::f<_0, _1, _2, _0, _3>
  ///   ==
  ///   list<
  ///     list<>,
  ///     list<_0, _1, _2>,
  ///     list<_0, _3>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see split_if, split_after_if
  template<class Pred, class C = listify>
  struct split_before_if
  {
    template <class... xs>
    using f = typename detail::_split<sizeof...(xs) != 0>
      ::template f<detail::split_before, C, JLN_MP_TRACE_F(Pred), xs...>;
  };

  template<class x, class C = listify>
  using split_before = split_before_if<is<x>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using split_before_if = unpack<L, mp::split_before_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using split_before = unpack<L, mp::split_before<x, C>>;
  }
}
namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using split_before_if = try_contract<
    mp::split_before_if<assume_unary<Pred>, assume_lists<C>>>;

  template<class x, class C = listify>
  using split_before = contract<mp::split_before<x, assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, split_before_if<F, C>>
  {
    using type = smp::split_before_if<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned position, class C1, class C2, class C, class... xs>
    using _split_from_i = typename C::template f<
      typename take_front_c<position, C1>::template f<xs...>,
      typename drop_front_c<position, C2>::template f<xs...>
    >;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a sequence at an arbitrary position returns by \c GetIndex.
  /// \pre `GetIndex::f<xs...>::value >= 0 && GetIndex::f<xs...>::value <= sizeof...(xs)`
  /// \treturn \sequence of two \values
  template<class GetIndex, class SubC1 = listify, class SubC2 = SubC1, class C = listify>
  struct split_from2
  {
    template<class... xs>
    using f = typename detail::_split_from_i<
      JLN_MP_DCALL_V_TRACE_XS(xs, GetIndex, xs...), SubC1, SubC2, C, xs...>;
  };

  template<class GetIndex, class C = listify>
  using split_from = split_from2<GetIndex, listify, listify, C>;

  namespace emp
  {
    template<class L, class GetIndex,
      class SubC1 = mp::listify, class SubC2 = SubC1, class C = mp::listify>
    using split_from2 = unpack<L, mp::split_from2<GetIndex, SubC1, SubC2, C>>;

    template<class L, class GetIndex, class C = mp::listify>
    using split_from = unpack<L, mp::split_from2<GetIndex, mp::listify, mp::listify, C>>;
  }
}
/// \cond
namespace jln::mp::detail
{
  template<class SubC1, class SubC2, class C>
  struct _smp_split_from;
}
/// \endcond

namespace jln::mp::smp
{
  template<class GetIndex, class SubC1 = listify, class SubC2 = SubC1, class C = listify>
  using split_from2 = contract<mp::invoke_twice<mp::tee<
    subcontract<GetIndex>,
    detail::_smp_split_from<subcontract<SubC1>, subcontract<SubC2>, subcontract<C>>
  >>>;

  template<class GetIndex, class C = listify>
  using split_from = contract<mp::invoke_twice<mp::tee<
    subcontract<GetIndex>,
    detail::_smp_split_from<mp::listify, mp::listify, assume_lists<C>>
  >>>;
}

/// \cond
namespace jln::mp::detail
{
  struct smp_split_from_i
  {
    template<class position, class C1, class C2, class C, class... xs>
    using f = _split_from_i<position::value, C1, C2, C, xs...>;
  };

  template<class SubC1, class SubC2, class C>
  struct _smp_split_from
  {
    template<class i, class = void>
    struct impl
    {
      template<class... xs>
      using f = na;
    };

    template<class i>
    struct impl<i, decltype(void(unsigned{i::value}))>
    {
      template<class... xs>
      using f = typename conditional_c<i::value <= sizeof...(xs)>
        ::template f<smp_split_from_i, violation>
        ::template f<i, SubC1, SubC2, monadic_xs<C>, xs...>;
    };

    template<class i>
    using f = impl<i>;
  };


  template<template<class> class sfinae, class GetIndex, class SubC1, class SubC2, class C>
  struct _sfinae<sfinae, split_from2<GetIndex, SubC1, SubC2, C>>
  {
    using type = smp::split_from2<sfinae<GetIndex>, sfinae<SubC1>, sfinae<SubC2>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class Seq, class C = identity>
  using starts_with = typename mp::conditional_c<detail::_is_list<Seq>::type::value>
    ::template f<contract<mp::starts_with<Seq, assume_positive_number<C>>>, bad_contract>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Seq, class C>
  struct _sfinae<sfinae, starts_with<Seq, C>>
  {
    using type = smp::starts_with<Seq, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup algorithm

  /// Inserts a \value after each element of a \sequence.
  /// \treturn \list
  /// \see intersperse, prefix
  template<class x, class C = listify>
  struct suffix
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(C), list<xs, x>...>::type;
  };

  namespace emp
  {
    template<class L, class x, class C = mp::listify>
    using suffix = unpack<L, mp::suffix<x, C>>;
  }
}
namespace jln::mp::smp
{
  template<class x, class C = listify>
  using suffix = contract<mp::suffix<x, subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, suffix<x, C>>
  {
    using type = smp::suffix<x, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_until_extended_by_n_c = contract<mp::invoke_twice<
    mp::drop_until<
      concepts::strong_predicate<assume_unary<Pred>, mp::identity, mp::always<true_>>,
      mp::if_<
        mp::front<concepts::strong_predicate<assume_unary<Pred>, mp::always<true_>>>,
        detail::smp_take_drop_for_size<ExtendedByN, TC>,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_until = take_until_extended_by_n_c<0, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_until = take_until_extended_by_n_c<1, Pred, TC, FC>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(take_until_extended_by_n,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::take_until_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, take_until<Pred, TC, FC>>
  {
    using type = smp::take_until<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, std::size_t ExtendedByN, class Pred, class TC, class FC>
  struct _sfinae<sfinae, take_until_extended_by_n_c<ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::take_until_extended_by_n_c<ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_while_extended_by_n_xs_c = contract<mp::invoke_twice<
    mp::drop_while_xs<
      concepts::strong_predicate<assume_unary_or_more<Pred>, mp::identity, mp::always<false_>>,
      mp::if_<
        concepts::strong_predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
        detail::smp_take_drop_for_size<ExtendedByN, TC>,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_while_xs = take_while_extended_by_n_xs_c<0, Pred, TC, FC>;

  template<int_ OffsetEnd, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_take_while_extended_by_n_xs_c = contract<mp::invoke_twice<
    mp::partial_drop_while_xs_c<
      OffsetEnd,
      concepts::strong_predicate<assume_unary_or_more<Pred>, mp::identity, mp::always<false_>>,
      mp::if_<
        concepts::strong_predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
        detail::smp_take_drop_for_size<ExtendedByN, TC>,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_while_xs_c = partial_take_while_extended_by_n_xs_c<OffsetEnd, 0, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_while_xs = take_while_extended_by_n_xs_c<1, Pred, TC, FC>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_inclusive_while_xs_c = partial_take_while_extended_by_n_xs_c<
    OffsetEnd, 1, Pred, TC, FC>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(partial_take_while_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_take_while_xs_c<OffsetEnd::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP4_P(partial_take_inclusive_while_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_take_inclusive_while_xs_c<OffsetEnd::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP4_P(take_while_extended_by_n_xs,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::take_while_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP5_P(partial_take_while_extended_by_n_xs,
  (OffsetEnd), (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_take_while_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>)


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, take_while_xs<Pred, TC, FC>>
  {
    using type = smp::take_while_xs<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, std::size_t ExtendedByN, class Pred, class TC, class FC>
  struct _sfinae<sfinae, take_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::take_while_extended_by_n_xs_c<
      ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>
    >;
  };

  template<template<class> class sfinae, int_ OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC, class FC>
  struct _sfinae<sfinae, partial_take_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::partial_take_while_extended_by_n_xs_c<
      OffsetEnd, ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>
    >;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class F>
    struct unfold_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  template<class value, class next = value>
  using Some = mp::list<value, next>;

  using None = mp::stop_recursion;

  /// Unfold \c F until returning \c None.
  /// When \c F returns `Some<value,next>`, \c value is added to the
  /// results list and \c next is used for the next iteration.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   unfold<
  ///     if_<
  ///       less_than_c<5>,
  ///       inc<lift<Some>>,
  ///       None
  ///     >
  ///   >::f<
  ///     number<0>
  ///   >
  ///   == list<number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   \endcode
  /// \treturn \list
  /// \see fold_left, fold_right, recursively
  template<class F, class C = listify>
  using unfold = mp::recursively<detail::unfold_impl<F>, mp::pop_front<C>>;

  namespace emp
  {
    template<class state, class F, class C = mp::listify>
    using unfold = JLN_MP_CALL_TRACE(JLN_MP_IDENT(mp::unfold<F, C>), state);
  }
}

/// \cond
namespace jln::mp::detail
{
  template<class>
  struct unfold_next
  {};

  template<>
  struct unfold_next<None>
  {
    template<class... xs>
    using f = stop_recursion;
  };

  template<class x, class next>
  struct unfold_next<list<x, next>>
  {
    template<class... xs>
    using f = _next_recursion<next, xs..., x>;
  };

  template<class F>
  struct unfold_impl
  {
    template<class state, class... xs>
    using f = typename unfold_next<JLN_MP_CALL_TRACE(F, state)>::template f<xs...>;
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct smp_unfold_impl;
}
/// \endcond

namespace jln::mp::smp
{
  template<class F, class C = listify>
  using unfold = test_contract<
    mp::size<mp::is<mp::number<1>>>,
    mp::recursively<
      detail::smp_unfold_impl<try_subcontract<F>>,
      monadic0<mp::pop_front<subcontract<C>>>
    >
  >;

  using None = contract<mp::None>;
  using Some = contract<mp::listify>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, unfold<F, C>>
  {
    using type = smp::unfold<sfinae<F>, sfinae<C>>;
  };

  template<class>
  struct smp_unfold_next
  {
    template<class... xs>
    using f = _recursion_result<na, na>;
  };

  template<>
  struct smp_unfold_next<None>
  {
    template<class... xs>
    using f = stop_recursion;
  };

  template<class x, class next>
  struct smp_unfold_next<list<x, next>>
  {
    template<class... xs>
    using f = _next_recursion<next, xs..., x>;
  };

  template<class F>
  struct smp_unfold_impl
  {
    template<class state, class... xs>
    using f = typename smp_unfold_next<typename F::template f<state>>::template f<xs...>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup filter

  /// List unique elements, preserving order.
  /// Remember only the element just seen.
  /// \semantics
  ///   \code
  ///   unique_justseen_by<same<>>::f<void, void, int, void>
  ///     == list<void, int, void>
  ///   \endcode
  /// \treturn \sequence
  template<class Cmp, class C = listify>
  using unique_justseen_by = group_by<Cmp, transform<unpack<front<>>, C>>;

  template<class C = listify>
  using unique_justseen = unique_justseen_by<same<>, C>;

  namespace emp
  {
    template<class L, class Cmp, class C = mp::listify>
    using unique_justseen_by = unpack<L, mp::unique_justseen_by<Cmp, C>>;

    template<class L, class C = mp::listify>
    using unique_justseen = unpack<L, mp::unique_justseen<C>>;
  }
}
namespace jln::mp::smp
{
  template<class Cmp, class C = listify>
  using unique_justseen_by = group_by<Cmp, contract<
      mp::transform<mp::unpack<mp::front<>>, subcontract<C>>>>;

  template<class C = listify>
  using unique_justseen = unique_justseen_by<same<>, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, unique_justseen_by<Cmp, C>>
  {
    using type = smp::unique_justseen_by<sfinae<Cmp>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = listify>
  using flip = try_contract<mp::flip<assume_binary_or_more<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, flip<C>>
  {
    using type = smp::flip<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::binary_or_more, flip);
}
/// \endcond
namespace jln::mp
{
  /// \ingroup search

  /// Finds first element that is greater that \c x.
  /// Invokes \c FC with all the elements since the one found at the end.
  /// If no element is found, \c NFC is used.
  /// \pre \c is_sorted<Cmp>::f<xs...>
  /// \treturn \sequence
  template<class x, class Cmp = less<>, class C = listify, class NC = C>
  using upper_bound = lower_bound<x, flip<tee<Cmp, not_<>>>, C, NC>;

  template<int_ x, class Cmp = less<>, class C = listify, class NC = C>
  using upper_bound_c = upper_bound<number<x>, Cmp, C, NC>;

  template<class x, class C = listify, class NC = C>
  using upper_bound_than = upper_bound<x, less<>, C, NC>;

  template<int_ x, class C = listify, class NC = C>
  using upper_bound_than_c = upper_bound<number<x>, less<>, C, NC>;

  namespace emp
  {
    template<class L, class x, class Cmp = mp::less<>, class C = mp::listify, class NC = C>
    using upper_bound = unpack<L, mp::upper_bound<x, Cmp, C, NC>>;

    template<class L, int_ x, class Cmp = mp::less<>, class C = mp::listify, class NC = C>
    using upper_bound_c = unpack<L, mp::upper_bound<mp::number<x>, Cmp, C, NC>>;

    template<class L, class x, class C = mp::listify, class NC = C>
    using upper_bound_than = unpack<L, mp::upper_bound<x, mp::less<>, C, NC>>;

    template<class L, int_ x, class C = mp::listify, class NC = C>
    using upper_bound_than_c = unpack<L, mp::upper_bound<mp::number<x>, mp::less<>, C, NC>>;
  }
}
namespace jln::mp::smp
{
  template<class x, class Cmp, class C = listify, class NC = C>
  using upper_bound = contract<detail::_smp_lower_bound_impl<
    x, mp::flip<concepts::predicate<assume_binary<Cmp>, mp::not_<>, violation>>,
    subcontract<C>, subcontract<NC>
  >>;

  template<int_ x, class Cmp = less<>, class C = listify, class NC = C>
  using upper_bound_c = upper_bound<number<x>, Cmp, C, NC>;

  template<class x, class C = listify, class NC = C>
  using upper_bound_than = upper_bound<x, less<>, C, NC>;

  template<int_ x, class C = listify, class NC = C>
  using upper_bound_than_c = upper_bound<number<x>, less<>, C, NC>;
}
namespace jln::mp::smp
{
  template<class F = listify, class C = listify>
  using zip_with = test_contract<
    mp::all_of<mp::is_list<>>,
    mp::if_<
      mp::transform<mp::unpack<mp::size<>>, mp::same<>>,
      mp::zip_with<assume_unary_or_more<F>, detail::smp_listify_or_monadic_xs<F, C>>,
      violation
    >
  >;

  template<class C = listify>
  using zip = zip_with<listify, C>;

}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, zip_with<F, C>>
  {
    using type = smp::zip_with<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup group

  /// Turns rows into columns, and columns into rows.
  /// Missing values are filled-in with fillvalue.
  /// This is similar to transposing a matrix.
  /// \semantics
  ///   \code
  ///   zip_longest<_0>::f<
  ///     list<_1, _2, _3>,
  ///     list<_a, _b, _c, _d>
  ///   > = list<
  ///     list<_1, _a>,
  ///     list<_2, _b>,
  ///     list<_3, _c>
  ///     list<_0, _d>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see zip
  template<class FillValue, class C = listify>
  using zip_longest = right_matrix_longest<FillValue, zip<C>>;

  template<class FillValue, class F = listify, class C = listify>
  using zip_longest_with = right_matrix_longest<FillValue, zip_with<F, C>>;

  namespace emp
  {
    template<class L, class FillValue, class C = mp::listify>
    using zip_longest = unpack<L, mp::zip_longest<FillValue, C>>;

    template<class L, class FillValue, class F = mp::listify, class C = mp::listify>
    using zip_longest_with = unpack<L, mp::zip_longest_with<FillValue, F, C>>;
  }
}
namespace jln::mp::smp
{
  template<class FillValue, class C = listify>
  using zip_longest = right_matrix_longest<FillValue, zip<C>>;

  template<class FillValue, class F = listify, class C = listify>
  using zip_longest_with = right_matrix_longest<FillValue, zip_with<F, C>>;
}
namespace jln::mp::smp
{
  template<class F, class... BoundArgs>
  using bind_back = contract<mp::bind_back<subcontract<F>, BoundArgs...>>;

  template<class F, int_... BoundArgs>
  using bind_back_c = bind_back<F, number<BoundArgs>...>;

#if JLN_MP_ENABLE_TPL_AUTO
  template<class F, auto... BoundArgs>
  using bind_back_v = bind_back<F, val<BoundArgs>...>;
#endif
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class... BoundArgs>
  struct _sfinae<sfinae, bind_back<F, BoundArgs...>>
  {
    using type = smp::bind_back<sfinae<F>, BoundArgs...>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup functional

  /// Invoking \c F with its first parameters bound to bound to args.
  /// \semantics
  ///   \code
  ///   bind_front<F, a, b>::f<c, d> == F<a, b, c, d>
  ///   \endcode
  /// \treturn \sequence
  /// \see bind_back, capture_front, capture_back
  template<class F, class... BoundArgs>
  struct bind_front
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, F, BoundArgs..., xs...);
  };

  template<class F, int_... BoundArgs>
  using bind_front_c = bind_front<F, number<BoundArgs>...>;

#if JLN_MP_ENABLE_TPL_AUTO
  template<class F, auto... BoundArgs>
  using bind_front_v = bind_front<F, val<BoundArgs>...>;
#endif

  namespace emp
  {
    template<class L, class F, class... BoundArgs>
    using bind_front = unpack<L, mp::bind_front<F, BoundArgs...>>;

    template<class L, class F, int_... BoundArgs>
    using bind_front_c = unpack<L, mp::bind_front_c<F, BoundArgs...>>;

#if JLN_MP_ENABLE_TPL_AUTO
    template<class L, class F, auto... BoundArgs>
    using bind_front_v = unpack<L, mp::bind_front_v<F, BoundArgs...>>;
#endif
  }
} // namespace jln::mp
namespace jln::mp::smp
{
  template<class F, class... BoundArgs>
  using bind_front = contract<mp::bind_front<subcontract<F>, BoundArgs...>>;

  template<class F, int_... BoundArgs>
  using bind_front_c = bind_front<F, number<BoundArgs>...>;

#if JLN_MP_ENABLE_TPL_AUTO
  template<class F, auto... BoundArgs>
  using bind_front_v = bind_front<F, val<BoundArgs>...>;
#endif
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class... BoundArgs>
  struct _sfinae<sfinae, bind_front<F, BoundArgs...>>
  {
    using type = smp::bind_front<sfinae<F>, BoundArgs...>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup functional

  /// Invoking \c F with its last parameters bound to bound to args.
  /// \semantics
  ///   \code
  ///   capture_back<c, d>::f<F, a, b> == F<a, b, c, d>
  ///   \endcode
  /// \treturn \sequence
  /// \see capture_front, bind_back, bind_front
  template<class... BoundArgs>
  struct capture_back
  {
    template<class F, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, F, xs..., BoundArgs...);
  };

#if __cplusplus >= 201703L
  template<JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using capture_back_c = capture_back<val<BoundArgs>...>;
#else
  template<int_... BoundArgs>
  using capture_back_c = capture_back<typed_val<int_, BoundArgs>...>;
#endif

  template<JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  struct capture_back_v_c
  {
    template<class F, class... xs>
    using f = typename F::template f<xs::value..., BoundArgs...>;
  };

  template<class... BoundArgs>
  using capture_back_v = capture_back_v_c<BoundArgs::value...>;

  namespace emp
  {
    template<class L, class... BoundArgs>
    using capture_back = unpack<L, mp::capture_back<BoundArgs...>>;

    template<class L, class... BoundArgs>
    using capture_back_v = unpack<L, mp::capture_back_v<BoundArgs...>>;

    template<class L, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
    using capture_back_v_c = unpack<L, mp::capture_back_v_c<BoundArgs...>>;
  }
}
namespace jln::mp::smp
{
  template<class... xs>
  using capture_back = try_contract<mp::capture_back<xs...>>;

#if __cplusplus >= 201703L
  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  using capture_back_c = capture_back<val<xs>...>;
#else
  template<int_... xs>
  using capture_back_c = capture_back<typed_val<int_, xs>...>;
#endif

  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  using capture_back_v_c = try_contract<mp::capture_back_v_c<xs...>>;

  template<class... xs>
  using capture_back_v = typename try_<
    mp::lift<mp::capture_back_v, mp::lift<try_contract>>,
    mp::identity,
    always<bad_contract>
  >::template f<xs...>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, capture_back<xs...>>
  {
    using type = smp::capture_back<xs...>;
  };

  template<template<class> class sfinae, JLN_MP_TPL_AUTO_OR_INT... xs>
  struct _sfinae<sfinae, capture_back_v_c<xs...>>
  {
    using type = smp::capture_back_v_c<xs...>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup functional

  /// Invoking \c F with its first parameters bound to bound to args.
  /// \semantics
  ///   \code
  ///   capture_front<a, b>::f<F, c, d> == F<a, b, c, d>
  ///   \endcode
  /// \treturn \sequence
  /// \see capture_back, bind_front, bind_back
  template<class... BoundArgs>
  struct capture_front
  {
    template<class F, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, F, BoundArgs..., xs...);
  };

#if __cplusplus >= 201703L
  template<JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using capture_front_c = capture_front<val<BoundArgs>...>;
#else
  template<int_... BoundArgs>
  using capture_front_c = capture_front<typed_val<int_, BoundArgs>...>;
#endif

  template<JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  struct capture_front_v_c
  {
    template<class F, class... xs>
    using f = typename F::template f<BoundArgs..., xs::value...>;
  };

  template<class... BoundArgs>
  using capture_front_v = capture_front_v_c<BoundArgs::value...>;

  namespace emp
  {
    template<class L, class... BoundArgs>
    using capture_front = unpack<L, mp::capture_front<BoundArgs...>>;

    template<class L, class... BoundArgs>
    using capture_front_v = unpack<L, mp::capture_front_v<BoundArgs...>>;

    template<class L, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
    using capture_front_v_c = unpack<L, mp::capture_front_v_c<BoundArgs...>>;
  }
}
namespace jln::mp::smp
{
  template<class... xs>
  using capture_front = try_contract<mp::capture_front<xs...>>;

#if __cplusplus >= 201703L
  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  using capture_front_c = capture_front<val<xs>...>;
#else
  template<int_... xs>
  using capture_front_c = capture_front<typed_val<int_, xs>...>;
#endif

  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  using capture_front_v_c = try_contract<mp::capture_front_v_c<xs...>>;

  template<class... xs>
  using capture_front_v = typename try_<
    mp::lift<mp::capture_front_v, mp::lift<try_contract>>,
    mp::identity,
    always<bad_contract>
  >::template f<xs...>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, capture_front<xs...>>
  {
    using type = smp::capture_front<xs...>;
  };

  template<template<class> class sfinae, JLN_MP_TPL_AUTO_OR_INT... xs>
  struct _sfinae<sfinae, capture_front_v_c<xs...>>
  {
    using type = smp::capture_front_v_c<xs...>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class, class...>
    struct _cascade;
  }
  /// \endcond

  /// \ingroup functional

  /// Recursively invokes \functions to nested \typelist of \typelists.
  /// \semantics
  ///   \code
  ///     cascade<F0,F1,F2> = transform<unpack<transform<unpack<F2>, F1>>, F0>
  ///   \endcode
  template<class F, class... Fs>
  using cascade = typename detail::_cascade<F, Fs...>::type;
}


/// \cond
namespace jln::mp::detail
{
  template<class F, class... Fs>
  struct _cascade
  {
    using type = transform<unpack<typename _cascade<Fs...>::type>, F>;
  };

  template<class F0, class F1>
  struct _cascade<F0, F1>
  {
    using type = transform<unpack<F1>, F0>;
  };

  template<class F>
  struct _cascade<F>
  {
    using type = transform<F>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class F, class... Fs>
  using cascade = typename detail::sfinae<mp::cascade<
    subcontract_barrier<F>,
    subcontract_barrier<Fs>...
  >>;
}
namespace jln::mp::smp
{
  template <template<class...> class F, template<class...> class... Fs>
  using compose_f = mp::detail::sfinae<
    mp::compose<mp::lift<F>, mp::lift<Fs>...>
  >;

  template<class F, class... Fs>
  using compose = mp::detail::sfinae<
    mp::compose<subcontract_barrier<F>, subcontract_barrier<Fs>...>
  >;
}
namespace jln::mp
{
#ifdef __cpp_nontype_template_parameter_class
#if __cpp_nontype_template_parameter_class >= 201806L
  /// \ingroup functional

  /// Invokes a lambda function.
  /// \treturn \value
  template<auto F, class C = identity>
  struct eval
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, decltype(F.template operator()<xs...>()));
  };

  namespace emp
  {
    template<auto F, class... xs>
    using eval = decltype(F.template operator()<xs...>());
  }
#endif
#endif
}
#ifdef __cpp_nontype_template_parameter_class
#if __cpp_nontype_template_parameter_class >= 201806L

namespace jln::mp::smp
{
  template <auto F, class C = identity>
  using eval = try_contract<mp::eval<F, assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, auto F, class C>
  struct _sfinae<sfinae, eval<F, C>>
  {
    using type = smp::eval<F, sfinae<C>>;
  };
}
/// \endcond
#endif
#endif
namespace jln::mp
{
  /// \ingroup functional

  /// Invokes a function computing the fixed point of a function.
  /// \treturn \value
  /// \see recurse, recurse_fix
  template<class C>
  struct fix
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, fix<C>, xs...);
  };

  namespace emp
  {
    template<class F, class... xs>
    using fix = typename fix<F>::template f<xs...>;
  }
}
namespace jln::mp::smp
{
  template <class C>
  using fix = try_contract<fix<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, fix<C>>
  {
    using type = smp::fix<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup functional

  /// Checks whether \c F::f<xs...> is invocable.
  /// \pre \c F::f<xs...> must be a SFINAE compatible expression
  /// \treturn \bool
  template<class F, class C = identity>
  using is_invocable = try_<F, always<true_, C>, always<false_, C>>;

  namespace emp
  {
    template<class F, class... xs>
    using is_invocable = typename mp::is_invocable<F>::template f<xs...>;
  }
}
namespace jln::mp::smp
{
  template<class F, class C = identity>
  using is_invocable = contract<mp::is_invocable<subcontract<F>, assume_positive_number<C>>>;
}
#ifdef __cpp_generic_lambdas
#if __cpp_generic_lambdas >= 201707L

# ifdef __cpp_consteval
#   if __cpp_consteval >= 201811L
#     define JLN_MP_CONSTEVAL_OR_CONSTEXPR consteval
#   endif
# endif
# ifndef JLN_MP_CONSTEVAL_OR_CONSTEXPR
#   define JLN_MP_CONSTEVAL_OR_CONSTEXPR constexpr
# endif

namespace jln::mp
{
  /// \ingroup functional

  class default_make_id_tag {};

  /// \cond
  namespace detail::mkid
  {
    JLN_MP_DIAGNOSTIC_PUSH()
    JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wnon-template-friend")
    template <class T, int X>
    struct flag
    {
      friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto f(flag<T, X>);
    };
    JLN_MP_DIAGNOSTIC_POP()

    template <class T, int X>
    struct injecter
    {
      friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto f(flag<T, X>) { return X; }
    };

    template <class T = default_make_id_tag, int X = 0, auto v = []{}>
    JLN_MP_CONSTEVAL_OR_CONSTEXPR auto next_id()
    {
      if constexpr (requires { f(flag<T, X+10>{}); }) {
        if constexpr (requires { f(flag<T, X+100>{}); }) {
          if constexpr (requires { f(flag<T, X+1000>{}); }) {
            if constexpr (requires { f(flag<T, X+10000>{}); }) {
              return next_id<T, X+10001, v>();
            }
            else if constexpr (requires { f(flag<T, X+3000>{}); }) {
              return next_id<T, X+3001, v>();
            }
            else {
              return next_id<T, X+1001, v>();
            }
          }
          else if constexpr (requires { f(flag<T, X+300>{}); }) {
            return next_id<T, X+301, v>();
          }
          else {
            return next_id<T, X+101, v>();
          }
        }
        else if constexpr (requires { f(flag<T, X+30>{}); }) {
          return next_id<T, X+31, v>();
        }
        else {
          return next_id<T, X+11, v>();
        }
      }
      else if constexpr (requires { f(flag<T, X>{}); }) {
        if constexpr (requires { f(flag<T, X+2>{}); }) {
          if constexpr (requires { f(flag<T, X+4>{}); }) {
            return next_id<T, X+5, v>();
          }
          else if constexpr (requires { f(flag<T, X+3>{}); }) {
            return next_id<T, X+4, v>();
          }
          else {
            return next_id<T, X+3, v>();
          }
        }
        else if constexpr (requires { f(flag<T, X+1>{}); }) {
            return next_id<T, X+2, v>();
        }
        else {
            return next_id<T, X+1, v>();
        }
      }
      else {
        void(injecter<T, X>{});
        return f(flag<T, X>{});
      }
    }
  }
  /// \endcond

  using detail::mkid::next_id;

  /// Generates a unique id per type.
  template<class T>
  struct id_of
  {
    static constexpr int value = next_id<default_make_id_tag, 0, []{}>();
  };

  template<class T>
  static constexpr int id_of_v = id_of<T>::value;

  template<class T>
  using id_of_t = number<id_of<T>::value>;


  /// Generates a unique id per type for a specified tag.
  template<class Tag, class T>
  struct tagged_id_of
  {
    static constexpr int value = next_id<Tag, 0, []{}>();
  };

  template<class Tag, class T>
  static constexpr int tagged_id_of_v = tagged_id_of<Tag, T>::value;

  template<class Tag, class T>
  using tagged_id_of_t = number<tagged_id_of<Tag, T>::value>;


  /// Generates a unique id per type.
  /// \treturn \number
  template<class Tag, class C = identity>
  struct make_id_for
  {
    template<class T>
    using f = JLN_MP_CALL_TRACE(C, tagged_id_of_t<Tag, T>);
  };

  template<class C = identity>
  using make_id = make_id_for<default_make_id_tag, C>;

  /// \cond
  template<class T>
  struct tagged_id_of<default_make_id_tag, T>
  : id_of<T>
  {};

  template<>
  struct make_id_for<default_make_id_tag, identity>
  {
    template<class T>
    using f = id_of_t<T>;
  };

  template<class Tag>
  struct make_id_for<Tag, identity>
  {
    template<class T>
    using f = tagged_id_of_t<Tag, T>;
  };

  template<class C>
  struct make_id_for<default_make_id_tag, C>
  {
    template<class T>
    using f = JLN_MP_CALL_TRACE(C, id_of_t<T>);
  };
  /// \endcond
}

#endif
#endif
#ifdef __cpp_generic_lambdas
#if __cpp_generic_lambdas >= 201707L

namespace jln::mp::smp
{
  template<class Tag, class C = identity>
  using make_id_for = try_contract<mp::make_id_for<Tag, assume_positive_number<C>>>;

  template<class C = identity>
  using make_id = try_contract<mp::make_id_for<default_make_id_tag, assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Tag, class C>
  struct _sfinae<sfinae, make_id_for<Tag, C>>
  {
    using type = smp::make_id_for<Tag, C>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT2(argument_category::unary, make_id_for);
}
/// \endcond

#endif
#endif
namespace jln::mp::smp
{
  template <class C>
  using memoize = contract<memoize<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, memoize<C>>
  {
    using type = smp::memoize<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template <class F, class C = identity>
  using not_fn = contract<concepts::predicate<F, not_<C>, violation>>;
}
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template <class C, class... Fs>
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
  template <class... Fs, class C>
  struct partial
  {
    template<class... xs>
    using f;
  };
#else
  template <class... Fs>
  struct partial
  : rotate_c<-1, lift<detail::_partial>>
  ::template f<Fs...>
  {};
#endif
}

/// \cond
namespace jln::mp::detail
{
  constexpr int on_select(std::size_t nf, std::size_t nx)
  {
    return (nf < nx) ? 1 : (nf > nx) ? 2 : 0;
  }

  template <int, class C, class... Fs>
  struct _partial_select;

  // each
  template <class C, class... Fs>
  struct _partial_select<0, C, Fs...>
  : _each<C, Fs...>
  {};

  template <class C, class... Fs>
  struct _partial_select<1, C, Fs...>
  {
    template<class... xs>
    using f = typename _join_select<2>::f<
      JLN_MP_TRACE_F(C),
      typename take_front_c<sizeof...(Fs), _each<listify, Fs...>>::template f<xs...>,
      typename drop_front_c<sizeof...(Fs)>::template f<xs...>
    >::type;
  };

  template <class C, class... Fs>
  struct _partial_select<2, C, Fs...>
  {
    template<class... xs>
    using f = typename _join_select<2>::f<
      JLN_MP_TRACE_F(C),
      typename take_front_c<sizeof...(xs)+1, lift<_each>>
        ::template f<listify, Fs...>
        ::template f<xs...>,
      typename drop_front_c<sizeof...(xs), lift<tee>>
        ::template f<Fs..., listify>
        ::template f<>
    >::type;
  };

  template <class C, class... Fs>
  struct _partial
  {
    template<class... xs>
    using f = typename _partial_select<on_select(sizeof...(Fs), sizeof...(xs)), C, Fs...>
      ::template f<xs...>;
  };
} // namespace jln::mp
/// \endcond
/// \cond
namespace jln::mp::detail
{
  struct _smp_partial;
}
/// \endcond

namespace jln::mp::smp
{
  template <class... Fs>
  using partial = typename mp::conditional_c<sizeof...(Fs) == 0>
    ::template f<
      na,
      rotate_c<-1, detail::_smp_partial>>
    ::template f<subcontract<Fs>...>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, partial<Fs...>>
  {
    using type = smp::partial<sfinae<Fs>...>;
  };

  struct _smp_partial
  {
    template<class C, class... Fs>
    using f = contract<mp::partial<Fs..., monadic_xs<C>>>;
  };
}
/// \endcond
#ifdef __cpp_generic_lambdas
#if __cpp_generic_lambdas >= 201707L

namespace jln::mp
{
  /// \ingroup functional

  /// \cond
  namespace detail::rand
  {
    JLN_MP_DIAGNOSTIC_PUSH()
    JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wnon-template-friend")
    template <int X>
    struct flag
    {
      friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto f(flag<X>);
    };
    JLN_MP_DIAGNOSTIC_POP()

    struct random_data
    {
      unsigned z;
      unsigned w;
    };

    template <int X, unsigned z, unsigned w>
    struct injecter
    {
      friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto f(flag<X>) { return random_data{z,w}; }
    };

    #ifndef JLN_MP_RANDOM_SEED_Z
    #   define JLN_MP_RANDOM_SEED_Z 0
    #endif
    #ifndef JLN_MP_RANDOM_SEED_W
    #   define JLN_MP_RANDOM_SEED_W 0
    #endif
    // -1 -> do not use __TIME__
    // 0 -> use __TIME__
    // >= 0 -> use value as __TIME__
    #ifndef JLN_MP_RANDOM_SEED_TIME
    #   define JLN_MP_RANDOM_SEED_TIME -1
    #endif

    #if JLN_MP_RANDOM_SEED_TIME >= 0
    #  if JLN_MP_RANDOM_SEED_TIME == 0
    JLN_MP_DIAGNOSTIC_PUSH()
    JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Wdate-time")
    constexpr unsigned t = unsigned((__TIME__[0] * 10 + __TIME__[1]) * 3600
                                  + (__TIME__[3] * 10 + __TIME__[4]) * 60
                                  + (__TIME__[6] * 10 + __TIME__[7]));
    JLN_MP_DIAGNOSTIC_POP()
    #    undef JLN_MP_RANDOM_SEED_TIME
    #    define JLN_MP_RANDOM_SEED_TIME t
    #  endif
    #  if JLN_MP_RANDOM_SEED_Z == 0
    #    define JLN_MP_RANDOM_SEED_Z \
           (JLN_MP_RANDOM_SEED_TIME >> 16) ? (JLN_MP_RANDOM_SEED_TIME >> 16) : 362436069
    #  endif
    #  if JLN_MP_RANDOM_SEED_W == 0
    #    define JLN_MP_RANDOM_SEED_W \
           (JLN_MP_RANDOM_SEED_TIME % 4294967296) ? (JLN_MP_RANDOM_SEED_TIME % 4294967296) : 521288629
    #  endif
    #else
    #  if JLN_MP_RANDOM_SEED_Z == 0
    #    undef JLN_MP_RANDOM_SEED_Z
    #    define JLN_MP_RANDOM_SEED_Z 362436069
    #  endif
    #  if JLN_MP_RANDOM_SEED_W == 0
    #    undef JLN_MP_RANDOM_SEED_W
    #    define JLN_MP_RANDOM_SEED_W 521288629
    #  endif
    #endif

    inline JLN_MP_CONSTEVAL_OR_CONSTEXPR auto f(flag<0>)
    {
      return random_data{JLN_MP_RANDOM_SEED_Z, JLN_MP_RANDOM_SEED_W};
    }

    #undef JLN_MP_RANDOM_SEED_Z
    #undef JLN_MP_RANDOM_SEED_W
    #undef JLN_MP_RANDOM_SEED_TIME

    template<class>
    struct tagged;

    /// \pre id >= 1
    /// \pre random_for_id<id-1>() must have been called
    template <int id>
    JLN_MP_CONSTEVAL_OR_CONSTEXPR unsigned random_for_id()
    {
      constexpr auto data = f(flag<id-1>{});
      // algorithm found on https://www.codeproject.com/Articles/25172/Simple-Random-Number-Generation
      constexpr unsigned z = 36969 * (data.z & 65535) + (data.z >> 16);
      constexpr unsigned w = 18000 * (data.w & 65535) + (data.w >> 16);
      void(injecter<id, z, w>{});
      return (z << 16) + w;
    }

    template <class Tag = random_data, auto v = []{}>
    JLN_MP_CONSTEVAL_OR_CONSTEXPR unsigned next_random()
    {
      return random_for_id<next_id<tagged<Tag>, 1, v>()>();
    }
  }
  /// \endcond

  using detail::rand::next_random;

  namespace emp
  {
    template<auto v = []{}>
    using random = number<next_random<detail::rand::random_data, v>()>;

    template<auto v = []{}>
    static constexpr unsigned random_v = next_random<detail::rand::random_data, v>();
  }

  /// Generate a random number.
  /// The seed can be configured with JLN_MP_RANDOM_SEED_TIME
  /// or JLN_MP_RANDOM_SEED_W and JLN_MP_RANDOM_SEED_Z
  /// \treturn number
  template<class C = identity, auto = []{}>
  struct random
  #ifdef JLN_MP_DOXYGENATING
  {
    template<class... xs>
    using f;
  }
  #endif
  ;

/// \cond
#if JLN_MP_CLANG
  namespace detail
  {
    template<std::size_t, auto v = []{}>
    using random_impl = number<next_random<detail::rand::random_data, v>()>;
  }

  template<class C, auto>
  struct random
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, detail::random_impl<sizeof...(xs)>);
  };

  template<>
  struct random<identity>
  {
    template<class... xs>
    using f = detail::random_impl<sizeof...(xs)>;
  };
#else
  template<class C, auto>
  struct random
  {
    template<class...>
    using f = JLN_MP_CALL_TRACE(C, number<next_random<detail::rand::random_data, []{}>()>);
  };

  template<auto v>
  struct random<identity, v>
  {
    template<class...>
    using f = number<next_random<detail::rand::random_data, []{}>()>;
  };
#endif
/// \endcond
}

#endif
#endif
#ifdef __cpp_generic_lambdas
#if __cpp_generic_lambdas >= 201707L

namespace jln::mp::smp
{
  template<class C = identity>
  using random = contract<mp::random<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C, auto v>
  struct _sfinae<sfinae, random<C, v>>
  {
    using type = contract<mp::random<assume_positive_number<C>, v>>;
  };

  template<class C, auto v>
  struct expected_argument<random<C, v>>
  : number<argument_category::unary_or_more>
  {};
}
/// \endcond

#endif
#endif
namespace jln::mp
{
  /// \ingroup functional

  /// Apply a function until some \predicate is satisfied.
  /// \treturn \value
  /// \see until_xs
  template<class Pred, class F, class C = identity>
  using until = recursively<if_<Pred, stop_recursion, F>, C>;

  /// Apply a function until some \predicate is satisfied.
  /// \treturn \value
  /// \see until
  template<class Pred, class F, class C = listify>
  using until_xs = recursively<if_<Pred, stop_recursion, F>, C>;

  namespace emp
  {
    template<class L, class Pred, class F, class C = mp::identity>
    using until = unpack<L, mp::until<Pred, F, C>>;

    template<class L, class Pred, class F, class C = mp::listify>
    using until_xs = unpack<L, mp::until<Pred, F, C>>;
  }
}
namespace jln::mp::smp
{
  template<class Pred, class F, class C = identity>
  using until = recursively<if_<Pred, stop_recursion, F>, C>;

  template<class Pred, class F, class C = listify>
  using until_xs = recursively<if_<Pred, stop_recursion, F>, C>;
}
namespace jln::mp
{
  /// \ingroup functional

  /// Apply a function while some \predicate is satisfied.
  /// \treturn \value
  /// \see while_xs
  template<class Pred, class F, class C = identity>
  using while_ = recursively<if_<Pred, F, stop_recursion>, C>;

  /// Apply a function while some \predicate is satisfied.
  /// \treturn \value
  /// \see while
  template<class Pred, class F, class C = listify>
  using while_xs = recursively<if_<Pred, F, stop_recursion>, C>;

  namespace emp
  {
    template<class L, class Pred, class F, class C = mp::identity>
    using while_ = unpack<L, mp::while_<Pred, F, C>>;

    template<class L, class Pred, class F, class C = mp::listify>
    using while_xs = unpack<L, mp::while_<Pred, F, C>>;
  }
}
namespace jln::mp::smp
{
  template<class Pred, class F, class C = identity>
  using while_ = recursively<if_<Pred, F, stop_recursion>, C>;

  template<class Pred, class F, class C = listify>
  using while_xs = recursively<if_<Pred, F, stop_recursion>, C>;
}
namespace jln::mp
{
  /// \ingroup list

  /// Inserts elements at the end of \c L list.
  /// \treturn \sequence
  template<class L, class C = listify>
  using append = push_front<L, unpack_append<C>>;

  namespace emp
  {
    template<class L, class... xs>
    using append = unpack_append<L, listify, xs...>;
  }
}
namespace jln::mp::smp
{
  template<class L, class C = listify>
  using append = contract<mp::push_front<L, subcontract<unpack_append<C>>>>;
}
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class seq>
    struct _as_list
    {};
  }
  /// \endcond

  /// \ingroup list

  /// Extracts type paramaters of a template class or union, then constructs a \list.
  /// \pre \c seq must be compatible with \typelist or \c detail::_as_list<seq>::type.
  /// \treturn \list
  template<class C = identity>
  struct as_list
  {
    template<class seq>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_as_list<seq>::type);
  };

  namespace emp
  {
    template<class seq, class C = mp::identity>
    using as_list = typename as_list<C>::template f<seq>;
  }
}

/// \cond
namespace jln::mp
{
  template<>
  struct as_list<identity>
  {
    template<class seq>
    using f = typename detail::_as_list<seq>::type;
  };
}

namespace jln::mp::detail
{
  template<template<class...> class seq, class... xs>
  struct _as_list<seq<xs...>>
  {
    using type = list<xs...>;
  };

  template<template<class T, T...> class seq, class T, T... ns>
  struct _as_list<seq<T, ns...>>
  {
    using type = list<number<ns>...>;
  };

  template<template<auto...> class seq, auto... ns>
  struct _as_list<seq<ns...>>
  {
    using type = list<number<ns>...>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = identity>
  using as_list = try_contract<mp::as_list<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, as_list<C>>
  {
    using type = smp::as_list<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup list

  /// Retrieves the last element of a sequence.
  /// \treturn \value
  template<class C = identity>
  using back = rotate_c<-1, front<C>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using back = unpack<L, mp::back<C>>;
  }
}
namespace jln::mp::smp
{
  template<class C = identity>
  using back = mp::detail::sfinae<mp::back<assume_unary<C>>>;
}
/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_drop_back;

  template<bool>
  struct mk_drop_back_max;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using drop_back_c = typename detail::mk_drop_back<n >= 0>
    ::template f<n, C>;

  template<int_ n, class C = listify>
  using drop_back_max_c = typename detail::mk_drop_back_max<n >= 0>
    ::template f<n, C>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(drop_back, (N), (C, smp::listify), smp::drop_back_c<N::value, C>)
JLN_MP_MAKE_REGULAR_SMP2_P(drop_back_max, (N), (C, smp::listify), smp::drop_back_max_c<N::value, C>)


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, drop_back_c<N, C>>
  {
    using type = smp::drop_back_c<N, sfinae<C>>;
  };

  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, drop_back_max_c<N, C>>
  {
    using type = smp::drop_back_max_c<N, sfinae<C>>;
  };

  template<>
  struct mk_drop_back<true>
  {
    template<int_ n, class C>
    using f = test_contract<
      mp::size<mp::greater_equal_than_c<n>>,
      mp::drop_back_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_drop_back<false>
  {
    template<int_ i, int_ start, class C>
    using f = bad_contract;
  };

  template<>
  struct mk_drop_back_max<true>
  {
    template<int_ n, class C>
    using f = contract<mp::drop_back_max_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_drop_back_max<false>
  {
    template<int_ i, int_ start, class C>
    using f = bad_contract;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup list

  /// Removes all elements between two arbitrary indices of a sequence.
  /// \pre `0 <= start < sizeof...(xs)`
  /// \pre `0 <= start + size < sizeof...(xs)`
  /// \treturn \sequence
  template<unsigned start, unsigned size = 1, class C = listify>
  struct erase_c
  {
    template<class... xs>
    using f = typename join<C>::template f<
      typename take_front_c<start>::template f<xs...>,
      typename drop_front_c<detail::min(
        sizeof...(xs),
        start + size
      )>::template f<xs...>
    >;
  };

  template<class start, class size = number<1>, class C = listify>
  using erase = erase_c<start::value, size::value, C>;

  namespace emp
  {
    template<class L, class start, class size = mp::number<1>, class C = mp::listify>
    using erase = unpack<L, mp::erase<start, size, C>>;

    template<class L, unsigned start, unsigned size = 1, class C = mp::listify>
    using erase_c = unpack<L, mp::erase_c<start, size, C>>;
  }
}
/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_smp_erase;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ start, int_ size = 1, class C = listify>
  using erase_c = typename detail::mk_smp_erase<start >= 0 && size >= 0>
    ::template f<start, size, C>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(erase, (start), (size, number<1>), (C, smp::listify),
  smp::erase_c<start::value, size::value, C>)


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, unsigned start, unsigned size, class C>
  struct _sfinae<sfinae, erase_c<start, size, C>>
  {
    using type = smp::erase_c<start, size, sfinae<C>>;
  };

  template<>
  struct mk_smp_erase<true>
  {
    template<int_ start, int_ size, class C>
    using f = test_contract<
      mp::size<mp::greater_equal_than_c<start>>,
      mp::erase_c<start, size, subcontract<C>>>;
  };

  template<>
  struct mk_smp_erase<false>
  {
    template<int_ i, int_ start, class C>
    using f = bad_contract;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup list

  /// Inserts all elements of \c seq at an arbitrary position.
  /// \pre `0 <= i < sizeof...(xs)`
  /// \pre seq must be a \list
  /// \treturn \sequence
  template<unsigned i, class seq, class C = listify>
  using insert_range_c = tee<take_front_c<i>, always<seq>, drop_front_c<i>, join<C>>;

  template<class i, class seq, class C = listify>
  using insert_range = insert_range_c<i::value, seq, C>;

  namespace emp
  {
    template<class L, class i, class seq, class C = mp::listify>
    using insert_range = unpack<L, mp::insert_range<i, seq, C>>;

    template<class L, int_ i, class seq, class C = mp::listify>
    using insert_range_c = unpack<L, mp::insert_range_c<i, seq, C>>;
  }
}
/// \cond
namespace jln::mp::detail
{
  template<class>
  struct smp_insert_range_dispatch;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ i, class seq, class C = listify>
  using insert_range_c = typename detail::smp_insert_range_dispatch<seq>
    ::template f<i, C>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(insert_range, (I), (seq), (C, smp::listify),
  smp::insert_range_c<I::value, seq, C>)

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct smp_insert_range_dispatch2;

  template<>
  struct smp_insert_range_dispatch2<false>
  {
    template<int_ i, class C>
    using f = bad_contract;
  };

  template<>
  struct smp_insert_range_dispatch2<true>
  {
    template<int_ i, class L, class C>
    using f = test_contract<
      size<greater_equal_than_c<i>>,
      tee<take_front_c<i>, always<L>, drop_front_c<i>, join<subcontract<C>>>
    >;
  };

  template<class... xs>
  struct smp_insert_range_dispatch<list<xs...>>
  {
    template<int_ i, class C>
    using f = typename smp_insert_range_dispatch2<i >= 0>
      ::template f<i, list<xs...>, C>;
  };

  template<>
  struct smp_insert_range_dispatch<list<>>
  {
    template<int_ i, class C>
    using f = C;
  };

  template<class>
  struct smp_insert_range_dispatch
  {
    template<int_ i, class C>
    using f = bad_contract;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup list

  /// Inserts an elements at an arbitrary position.
  /// \pre `0 <= i < sizeof...(xs)`
  /// \treturn \sequence
  template<class i, class x, class C = listify>
  using insert = insert_range<i, list<x>, C>;

  template<unsigned i, class x, class C = listify>
  using insert_c = insert_range_c<i, list<x>, C>;

  namespace emp
  {
    template<class L, class i, class x, class C = mp::listify>
    using insert = unpack<L, mp::insert<i, x, C>>;

    template<class L, int_ i, class x, class C = mp::listify>
    using insert_c = unpack<L, mp::insert_c<i, x, C>>;
  }
}
namespace jln::mp::smp
{
  template<int_ i, class x, class C = listify>
  using insert_c = typename detail::smp_insert_range_dispatch2<true>
    ::template f<i, list<x>, C>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(insert, (I), (x), (C, smp::listify), smp::insert_c<I::value, x, C>)
namespace jln::mp::smp
{
  template<class C = identity>
  using is_empty = contract<mp::is_empty<assume_positive_number<C>>>;
}
namespace jln::mp::smp
{
  template<class C = identity>
  using is_list = try_contract<mp::is_list<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_list<C>>
  {
    using type = smp::is_list<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, is_list);
}
/// \endcond
namespace jln::mp
{
  /// \ingroup list

  /// Difference between the number of parameter \c xs and \c I::value.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   size<push_front<I, sub<C>>>
  ///   \endcode
  /// \treturn \number
  template <int_ I, class C = identity>
  struct offset_c
  {
    template <class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<I - int_{sizeof...(xs)}>);
  };

  /// \cond
  template <int_ I>
  struct offset_c<I, identity>
  {
    template <class... xs>
    using f = number<I - int_{sizeof...(xs)}>;
  };
  /// \endcond

  template<class I, class C = identity>
  using offset = offset_c<I::value, C>;

  namespace emp
  {
    template<class L, class I, class C = mp::identity>
    using offset = unpack<L, mp::offset<I, C>>;

    template<class L, int_ i, class C = mp::identity>
    using offset_c = unpack<L, mp::offset_c<i, C>>;
  }
}
namespace jln::mp::smp
{
  template <int_ i, class C = identity>
  using offset_c = contract<mp::offset_c<i, assume_number<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(offset, (N), (C, smp::identity), smp::offset_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, int_ I, class C>
  struct _sfinae<sfinae, offset_c<I, C>>
  {
    using type = smp::offset_c<I, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup list

  /// Removes the last element of sequence.
  /// \pre `sizeof...(xs) > 0`
  /// \treturn \sequence
  template<class C = listify>
  using pop_back = rotate_c<-1, pop_front<C>>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using pop_back = unpack<L, mp::pop_back<C>>;
  }
}
namespace jln::mp::smp
{
  template<class C = listify>
  using pop_back = rotate_c<-1, pop_front<C>>;
}
namespace jln::mp
{
  /// \ingroup list

  /// Inserts elements at the start of \c L list.
  /// \treturn \sequence
  template<class L, class C = listify>
  using prepend = push_front<L, unpack<C>>;

  namespace emp
  {
    template<class L, class... xs>
    using prepend = unpack<L, listify, xs...>;
  }
}
namespace jln::mp::smp
{
  template<class L, class C = listify>
  using prepend = contract<mp::push_front<L, subcontract<unpack<C>>>>;
}
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_ beg, int_ end, class C, bool _
      = !(beg == -1
      || ((beg >= 0 ? end >= 0 : end < 0) && beg >= end)),
      bool = _ && (beg >= 0),
      bool = _ && (end >= 0)>
    struct _range;
  }
  /// \endcond

  /// \ingroup list

  /// Returns a contiguous subsequence of a \sequence.
  /// A negative value represents an index starting from the end.
  /// if finally, \c end <= \c beg, then an empty \list is returned.
  /// \treturn \sequence
  template<int_ beg, int_ end, class C = listify>
  struct range_c : detail::_range<beg, end, C>::type
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  template<class beg, class end, class C = listify>
  using range = range_c<beg::value, end::value, C>;

  namespace emp
  {
    template<class L, class beg, class end, class C = mp::listify>
    using range = unpack<L, mp::range<beg, end, C>>;

    template<class L, int_ beg, int_ end, class C = mp::listify>
    using range_c = unpack<L, mp::range_c<beg, end, C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<int_ beg, int_ end, class C>
  struct _range<beg, end, C, false, false, false>
  {
    using type = _cartesian<C, 0>; // for C::f<>
  };

  template<int_ beg, int_ end>
  struct _range<beg, end, listify, false, false, false>
  {
    using type = always<list<>>;
  };

  template<class C>
  struct _range<0, -1, C, true, true, false>
  {
    using type = C;
  };

  template<int_ beg, int_ end, class C, bool b1, bool b2>
  struct _range<beg, end, C, true, b1, b2>
  {
    struct impl
    {
      template<class... xs>
      using f = typename range_c<
        (beg >= 0
          ? beg
          : (sizeof...(xs) <= -beg
            ? 0
            : int_(sizeof...(xs)) + beg)),
        (end >= 0
          ? end
          : (sizeof...(xs) <= -end
            ? 0
            : int_(sizeof...(xs)) + (end+1))),
        C
      >::template f<xs...>;
    };

    using type = impl;
  };

  template<int_ beg, int_ end, int_ n, class C,
    bool = (beg < n), bool = (end < n)>
  struct _range_impl // true, true
  {
    using type = rotate_c<end, drop_front_c<n - end + beg, C>>;
  };

  template<int_ end, int_ n, class C>
  struct _range_impl<0, end, n, C, true, true>
  {
    using type = take_front_c<end, C>;
  };

  template<int_ beg, int_ end, int_ n, class C>
  struct _range_impl<beg, end, n, C, true, false>
  {
    using type = drop_front_c<beg, C>;
  };

  template<int_ end, int_ n, class C>
  struct _range_impl<0, end, n, C, true, false>
  {
    using type = JLN_MP_TRACE_F(C);
  };

  template<int_ beg, int_ end, int_ n, class C>
  struct _range_impl<beg, end, n, C, false, false>
  {
    using type = _cartesian<C, 0>; // for C::f<>
  };

  template<int_ beg, int_ end, int_ n>
  struct _range_impl<beg, end, n, listify, false, false>
  {
    using type = always<list<>>;
  };

  template<int_ beg, int_ end, class C>
  struct _range<beg, end, C, true, true, true>
  {
    struct impl
    {
      template<class... xs>
      using f = typename _range_impl<beg, end, sizeof...(xs), C>
        ::type::template f<xs...>;
    };

    using type = impl;
  };

  template<int_ beg, class C>
  struct _range<beg, -1, C, true, true, false>
  {
    struct impl
    {
      template<class... xs>
      using f = typename _range_impl<beg, sizeof...(xs), sizeof...(xs), C>
        ::type::template f<xs...>;
    };

    using type = impl;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<int_ beg, int_ end, class C = listify>
  using range_c = contract<mp::range_c<
    beg, end, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(range, (beg), (end), (C, smp::listify),
  smp::range_c<beg::value, end::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, int_ beg, int_ end, class C>
  struct _sfinae<sfinae, range_c<beg, end, C>>
  {
    using type = smp::range_c<beg, end, sfinae<C>>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _slice;

    constexpr unsigned slide_select(unsigned nx, unsigned size, unsigned stride);
  }
  /// \endcond

  /// \ingroup list

  /// Returns a subset of elements in a \c xs picked at regular intervals in range.
  /// \pre `0 <= start <= sizeof...(xs)`
  /// \pre `0 < stride`
  /// \pre `0 <= size`
  /// \pre `0 <= (size - 1) * stride + start + 1 <= sizeof...(xs)`
  /// \treturn \sequence
  template<unsigned start, unsigned size, unsigned stride = 1, class C = listify>
  struct slice_c
  {
    template<class... xs>
    using f = typename detail::_slice<
      detail::slide_select(sizeof...(xs) - start, size, stride)
    >
    ::template f<start, size, stride, C, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class start, class size, class stride = number<1>, class C = listify>
  using slice = slice_c<start::value, size::value, stride::value, C>;

  namespace emp
  {
    template<class L, class start, class size, class stride = number<1>, class C = mp::listify>
    using slice = unpack<L, slice<start, size, stride, C>>;

    template<class L, unsigned start, unsigned size, unsigned stride = 1, class C = mp::listify>
    using slice_c = unpack<L, slice_c<start, size, stride, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  constexpr unsigned slide_select(unsigned nx, unsigned size, unsigned stride)
  {
    return !size ? 0
      : size == 1 ? 3
      : stride <= 1 ? 2
      : nx < stride ? 2
      : 1;
  }

  template<>
  struct _slice<2>
  {
    template<int_ start, int_ size, unsigned /*stride*/, class C, int_ len>
    using f = rotate_c<start + size, drop_front_c<len - size, C>>;
  };

#if JLN_MP_MSVC
  template<unsigned size, unsigned stride, unsigned i, class x>
  using slice_impl_msvc = typename wrap_in_list_c<(i <= size && i % stride == 0)>::template f<x>;
#endif

  template<unsigned size, unsigned stride, class C>
  struct _slice_impl
  {
    template<int_... ints>
    struct impl
    {
      template<class... xs>
      using f = typename join<C>::template f<
#if JLN_MP_MSVC
        slice_impl_msvc<size, stride, ints, xs>...
#else
        typename wrap_in_list_c<(ints <= size && ints % stride == 0)>
        ::template f<xs>...
#endif
      >;
    };
  };

  template<>
  struct _slice<1>
  {
    template<unsigned start, unsigned size, unsigned stride, class C, std::size_t len>
    using f = drop_front_c<
      start,
      typename emp::make_int_sequence_v_c<
        len - start,
        lift_c<_slice_impl<size * stride - stride + 1, stride, C>
               ::template impl>
      >
    >;
  };

  template<>
  struct _slice<0>
  {
    template<unsigned start, unsigned size, unsigned /*stride*/, class C, std::size_t len>
    using f = clear<C>;
  };

  template<>
  struct _slice<3>
  {
    template<unsigned start, unsigned size, unsigned /*stride*/, class C, std::size_t len>
    using f = drop_front_c<start, front<C>>;
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct smp_slice_select;
}
/// \endcond

namespace jln::mp::smp
{
  template<unsigned start, unsigned size, unsigned stride = 1, class C = listify>
  using slice_c = typename detail::smp_slice_select<(stride > 0)>
    ::template f<start, size, stride, C>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(slice, (start), (size), (stride, number<1>), (C, smp::listify),
  smp::slice_c<start::value, size::value, stride::value, C>)


/// \cond
namespace jln::mp::detail
{
  template<>
  struct smp_slice_select<false>
  {
    template<unsigned start, unsigned size, unsigned stride, class C>
    using f = bad_contract;
  };

  template<unsigned start, unsigned size, unsigned stride>
  struct smp_slice_check
  {
    template<class... xs>
    using f = mp::number<start <= sizeof...(xs)
                      && (size - 1) * stride + start + 1 <= sizeof...(xs)>;
  };

  template<>
  struct smp_slice_select<true>
  {
    template<unsigned start, unsigned size, unsigned stride, class C>
    using f = test_contract<
      smp_slice_check<start, size, stride>,
      mp::slice_c<start, size, stride, subcontract<C>>>;
  };

  template<template<class> class sfinae, unsigned start, unsigned size, unsigned stride, class C>
  struct _sfinae<sfinae, slice_c<start, size, stride, C>>
  {
    using type = smp::slice_c<start, size, stride, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    constexpr int_ sliding_stride(int_ size, int_ stride);

    template<int_ size, int_ stride, int_>
    struct mk_sliding;
  }
  /// \endcond

  /// \ingroup list

  /// Returns sliding windows of width \c size.
  /// \pre `stride != 0`
  /// \pre `size >= 0`
  /// \treturn \sequence of \list
  /// Given a sequence and a count n, place a window over the first n elements of the underlying range. Return the contents of that window as the first element of the adapted range, then slide the window forward one element at a time until hitting the end of the underlying range.
  /// \semantics
  ///     If `stride < 0`, then `stride = stride + size`
  ///     If `sizeof...(xs) < size`, then `f = C::f<xs...>`
  ///     If `stride > 1`, the last window may be smaller than \c size
  template<class size, class stride, class C = listify>
  using sliding_with_stride = typename detail::mk_sliding<
    size::value, stride::value,
    detail::sliding_stride(size::value, stride::value)
  >::template f<C>;

  template<int_ size, int_ stride = 1, class C = listify>
  using sliding_with_stride_c = typename detail::mk_sliding<size, stride,
    detail::sliding_stride(size, stride)
  >::template f<C>;

  template<class size, class C = listify>
  using sliding = sliding_with_stride_c<size::value, 1, C>;

  template<int_ size, class C = listify>
  using sliding_c = sliding_with_stride_c<size, 1, C>;

  namespace emp
  {
    template<class L, class size, class stride, class C = mp::listify>
    using sliding_with_stride = unpack<L, mp::sliding_with_stride<size, stride, C>>;

    template<class L, int_ size, int_ stride, class C = mp::listify>
    using sliding_with_stride_c = unpack<L, mp::sliding_with_stride_c<size, stride, C>>;

    template<class L, class size, class C = mp::listify>
    using sliding = unpack<L, mp::sliding<size, C>>;

    template<class L, int_ size, class C = mp::listify>
    using sliding_c = unpack<L, mp::sliding_c<size, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  constexpr int_ sliding_stride(int_ size, int_ stride)
  {
    if (!stride || size < 1) {
      return size == 0 ? -2 : -1;
    }

    if (stride < 0) {
      stride += size;
      if (stride <= 0) {
        return -1;
      }
    }

    return stride;
  }

  template<int>
  struct _sliding;

  constexpr int sliding_select(int n, int_ size, int_ stride);

  template<int_ size, int_ stride, class C>
  struct sliding_
  {
    template<class... xs>
    using f = typename detail::_sliding<detail::sliding_select(
      sizeof...(xs), size, stride)
    >::template f<C, size, stride, xs...>;
  };

  template<int_ size, int_, int_ stride>
  struct mk_sliding
  {
    template<class C>
    using f = sliding_<size, stride, optimize_useless_transform_unpack_t<C>>;
  };

  template<class C>
  struct sliding_nostride
  {};

  template<class C>
  struct sliding_0size
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS_0(xs, C);
  };

  template<int_ size, int_ stride>
  struct mk_sliding<size, stride, -1>
  {
    template<class C>
    using f = sliding_nostride<C>;
  };

  template<int_ size, int_ stride>
  struct mk_sliding<size, stride, -2>
  {
    template<class C>
    using f = sliding_0size<C>;
  };

  constexpr int_ slinding_pivot(int_ nx, int_ size, int_ stride)
  {
    return nx - (nx - size + stride - 1) / stride * stride - 1;
  }

  constexpr int sliding_select(int n, int_ size, int_ stride)
  {
    return n <= size ? (n ? 1 : 0)         // C<list<xs...>>
      : size == 1 ? (stride == 1 ? 2 : 3)  // C<list<xs>...> / slice<0, n/stride, stride>
      : stride > n ? 9                     // take_front
      : stride == 1 ? (size == 2 ? 4 : 5)  // common case
      : stride == size ? 6                 // group_n
      // slice<zip_longest> / slice<zip>
      : ((n - size) % stride) ? (slinding_pivot(n, size, stride) < 0 ? 7 : 8) : 7;
  }

  template<>
  struct _sliding<-1>
  {};

  // sizeof...(xs) == 0
  template<>
  struct _sliding<0>
  {
    template<class C, int_, int_, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  // sizeof...(xs) < size
  template<>
  struct _sliding<1>
  {
    template<class C, int_, int_, class... xs>
    using f = JLN_MP_CALL_TRACE(C, list<xs...>);
  };

  // size=1  stride=1
  template<>
  struct _sliding<2>
  {
    template<class C, int_, int_, class... xs>
    using f = JLN_MP_CALL_TRACE(C, list<xs>...);
  };

  // size=1  stride!=1
  template<>
  struct _sliding<3>
  {
    template<class C, int_, int_ stride, class... xs>
    using f = typename _slice<1>
      ::template f<0, (sizeof...(xs) + stride - 1) / stride, stride, transform<listify, C>, sizeof...(xs)>
      ::template f<xs...>;
  };

  // stride>size
  template<>
  struct _sliding<9>
  {
    template<class C, int_ size, int_, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename rotate_c<size, drop_front_c<sizeof...(xs)-size>>::template f<xs...>
    );
  };

  // size=2  stride=1  (pairwise)
  template<>
  struct _sliding<4>
  {
    template<class C, int_, int_, class... xs>
    using f = typename detail::pairwise_impl<rotate_c<-1>::f<xs...>>
      ::template f<C, listify, xs...>
      ;
  };

  // size>2  stride=1
  template<>
  struct _sliding<5>
  {
    struct impl
    {
      template<int_... i>
      struct f
      {
        template<class C, int_ size, class drop_front>
        using g = _tee<zip<C>, rotate_c<i-size, drop_front>...>;
      };
    };

    template<class C, int_ size, int_, class... xs>
    using f = typename emp::make_int_sequence_v_c<size, impl>
      ::template g<C, size-1, drop_front_c<size-1>>
      ::template f<xs...>;
  };

  // stride=size (group_n)
  template<>
  struct _sliding<6>
  {
    template<class C, int_ size, int_, class... xs>
    using f = typename emp::make_int_sequence_v_c<
      sizeof...(xs), lift_c<_group_n_impl>
    >::template f<C, size, xs...>;
  };

  // size>1  stride>1  (all list = size)
  template<>
  struct _sliding<7>
  {
    struct impl
    {
      template<int_... i>
      struct f
      {
        template<class C, int_ size, int_ stride>
        using g = _tee<zip<C>, slice_c<i, size, stride>...>;
      };
    };

    template<class C, int_ size, int_ stride, class... xs>
    using f = typename emp::make_int_sequence_v_c<size, impl>
      ::template g<C, (sizeof...(xs) - size) / stride + 1, stride>
      ::template f<xs...>;
  };

  constexpr int_ slinding8_pivot(int_ nx, int_ size, int_ stride)
  {
    int_ r = slinding_pivot(nx, size, stride);
    return r < 0 ? size : r;
  }

  // size>1  stride>1  (last list < size)
  template<>
  struct _sliding<8>
  {
    template<class F, class C>
    struct adjust
    {
      template<class x, class... xs>
      using f = typename C::template f<xs..., typename F::template f<x>>;
    };

    struct impl
    {
      template<int_... i>
      struct f
      {
        template<class C, int_ size, int_ stride, int_ pivot>
        using g = _tee<zip<
          rotate_c<-1, adjust<unpack<rotate_c<-1, pop_front<>>>, C>>
        >, slice_c<i, size - (pivot < i), stride,
          typename conditional_c<(pivot < i)>::template f<push_back<void>, listify>
        >...>;
      };
    };

    template<class C, int_ size, int_ stride, class... xs>
    using f = typename emp::make_int_sequence_v_c<size, impl>
      ::template g<
        C,
        (sizeof...(xs) - size) / stride + 2,
        stride,
        slinding8_pivot(sizeof...(xs), size, stride)
      >
      ::template f<xs...>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<int_ size, class C = listify>
  using sliding_c = try_contract<mp::sliding_c<size, assume_lists<C>>>;

  template<int_ size, int_ stride, class C = listify>
  using sliding_with_stride_c = try_contract<
    mp::sliding_with_stride_c<size, stride, assume_lists<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(sliding, (size), (C, smp::listify),
  smp::sliding_c<size::value, C>)

JLN_MP_MAKE_REGULAR_SMP3_P(sliding_with_stride, (size), (stride), (C, smp::listify),
  smp::sliding_with_stride_c<size::value, stride::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<class C>
  using smp_sliding_nostride = try_contract<sliding_nostride<subcontract<C>>>;

  template<class C>
  using smp_sliding_0size = try_contract<sliding_0size<subcontract<C>>>;

  template<template<class> class sfinae, int_ size, int_ stride, class C>
  struct _sfinae<sfinae, sliding_<size, stride, C>>
  {
    using type = smp::sliding_with_stride_c<size, stride, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, sliding_nostride<C>>
  {
    using type = smp_sliding_nostride<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, sliding_0size<C>>
  {
    using type = smp_sliding_0size<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned i, unsigned j, bool = (i < j), bool = (i == j)>
    struct _select_swap_index;
  }
  /// \endcond

  /// \ingroup list

  /// Swap elements at indexes \c I and \c J of a \sequence.
  /// \pre `0 < I < sizeof...(xs)`
  /// \pre `0 < J < sizeof...(xs)`
  /// \treturn \sequence
  /// \note `swap_index<I, J>` == `swap_index<J, I>`
  template<class I, class J, class C = listify>
  using swap_index = typename detail::_select_swap_index<
    unsigned{I::value}, unsigned{J::value}>::template f<C>;

  template<unsigned i, unsigned j, class C = listify>
  using swap_index_c = typename detail::_select_swap_index<
    i, j>::template f<C>;

  namespace emp
  {
    template<class L, class I, class J, class C = mp::listify>
    using swap_index = unpack<L, swap_index<I, J, C>>;

    template<class L, unsigned i, unsigned j, class C = mp::listify>
    using swap_index_c = unpack<L, swap_index_c<i, j, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<unsigned i, unsigned j, class C>
  struct swap_elem
  {
    template<class... xs>
    using f = typename join<C>::template f<
      typename rotate_c<i, drop_front_c<sizeof...(xs) - i>>::template f<xs...>,
      list<typename at_c<j>::template f<xs...>>,
      typename rotate_c<j, drop_front_c<sizeof...(xs) - j + i + 1>>::template f<xs...>,
      list<typename at_c<i>::template f<xs...>>,
      typename drop_front_c<j+1>::template f<xs...>
    >;
  };

  template<unsigned i, unsigned j, bool, bool>
  struct _select_swap_index
  {
    template<class C>
    using f = swap_elem<i, j, C>;
  };

  template<unsigned i, unsigned j>
  struct _select_swap_index<i, j, false, false>
  {
    template<class C>
    using f = swap_elem<j, i, C>;
  };

  template<unsigned i, class C>
  struct if_valid_index
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };

  template<unsigned i, unsigned j>
  struct _select_swap_index<i, j, false, true>
  {
    template<class C>
    using f = if_valid_index<i, C>;
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<class>
  struct _smp_swap_index;
}
/// \endcond

namespace jln::mp::smp
{
  template<unsigned i, unsigned j, class C = listify>
  using swap_index_c = typename detail::_smp_swap_index<
    mp::swap_index_c<i, j, C>>::type;
}

JLN_MP_MAKE_REGULAR_SMP3_P(swap_index, (i), (j), (C, smp::listify),
  smp::swap_index_c<i::value, j::value, C>)


/// \cond
namespace jln::mp::detail
{
  template<unsigned i, class C>
  struct _smp_swap_index<if_valid_index<i, C>>
  {
    using type = test_contract<size<greater_than_c<i>>, subcontract<C>>;
  };

  template<unsigned i, unsigned j, class C>
  struct _smp_swap_index<swap_elem<i, j, C>>
  {
    using type = test_contract<size<greater_than_c<j>>, swap_elem<i, j, subcontract<C>>>;
  };

  template<template<class> class sfinae, unsigned i, class C>
  struct _sfinae<sfinae, if_valid_index<i, C>>
  : detail::_smp_swap_index<if_valid_index<i, sfinae<C>>>
  {};

  template<template<class> class sfinae, unsigned i, unsigned j, class C>
  struct _sfinae<sfinae, swap_elem<i, j, C>>
  : detail::_smp_swap_index<swap_elem<i, j, sfinae<C>>>
  {};
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_take_back;

  template<bool>
  struct mk_take_back_max;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using take_back_c = typename detail::mk_take_back<n >= 0>
    ::template f<n, C>;

  template<int_ n, class C = listify>
  using take_back_max_c = typename detail::mk_take_back_max<n >= 0>
    ::template f<n, C>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(take_back, (N), (C, smp::listify), smp::take_back_c<N::value, C>)
JLN_MP_MAKE_REGULAR_SMP2_P(take_back_max, (N), (C, smp::listify), smp::take_back_max_c<N::value, C>)


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, take_back_c<N, C>>
  {
    using type = smp::take_back_c<N, sfinae<C>>;
  };

  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, take_back_max_c<N, C>>
  {
    using type = smp::take_back_max_c<N, sfinae<C>>;
  };

  template<>
  struct mk_take_back<true>
  {
    template<int_ n, class C>
    using f = test_contract<
      mp::size<mp::greater_equal_than_c<n>>,
      mp::take_back_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_take_back<false>
  {
    template<int_ i, int_ start, class C>
    using f = bad_contract;
  };

  template<>
  struct mk_take_back_max<true>
  {
    template<int_ n, class C>
    using f = contract<mp::take_back_max_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_take_back_max<false>
  {
    template<int_ i, int_ start, class C>
    using f = bad_contract;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = identity>
  using as_number = try_contract<mp::as_number<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, as_number<C>>
  {
    using type = smp::as_number<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class x>
    struct _is_number;
  }
  /// \endcond

  /// \ingroup number

  /// Checks whether a \value is a \number.
  /// \treturn \bool
  template<class C = identity>
  struct is_number
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_is_number<x>::type);
  };

  namespace emp
  {
    template<class x>
    using is_number = typename detail::_is_number<x>::type;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct _is_number
  {
    using type = false_;
  };

  template<int_ x>
  struct _is_number<number<x>>
  {
    using type = true_;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = identity>
  using is_number = try_contract<mp::is_number<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_number<C>>
  {
    using type = smp::is_number<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, is_number);
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    struct _pow;
  }
  /// \endcond

  /// \ingroup number

  template<class Cmp = less<>, class C = identity>
  using min = fold_left<if_<flip<Cmp>, at1<>, at0<>>, C>;

  template<class Cmp = less<>, class C = identity>
  using min0 = if_<size<>, min<Cmp, C>, always<number<0>, C>>;


  template<class Cmp = less<>, class C = identity>
  using max = fold_left<if_<Cmp, at1<>, at0<>>, C>;

  template<class Cmp = less<>, class C = identity>
  using max0 = if_<size<>, max<Cmp, C>, always<number<0>, C>>;


  template<class Min, class Max, class Cmp = less<>, class C = identity>
  using clamp = if_<push_back<Min, Cmp>, always<Min>,
    if_<push_front<Max, Cmp>, always<Max>, identity>>;

  template<int_ min, int_ max, class Cmp = less<>, class C = identity>
  using clamp_c = clamp<number<min>, number<max>, Cmp, C>;


  template<class Cmp = less<>, class C = identity>
  using abs = tee<identity, neg<>, max<Cmp, C>>;


  template<class C = identity>
  using pow = fold_left<detail::_pow, C>;

  template<class C = identity>
  using pow0 = if_<size<>, pow<C>, always<number<0>, C>>;

  template<class C = identity>
  using pow1 = if_<size<>, pow<C>, always<number<1>, C>>;


  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using min = unpack<L, mp::min<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using min0 = unpack<L, mp::min0<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using max = unpack<L, mp::max<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using max0 = unpack<L, mp::max0<Cmp, C>>;

    template<class L, class Min, class Max, class Cmp = mp::less<>, class C = mp::identity>
    using clamp = unpack<L, mp::clamp<Min, Max, Cmp, C>>;

    template<class L, int_ min, int_ max, class Cmp = mp::less<>, class C = mp::identity>
    using clamp_c = unpack<L, mp::clamp_c<min, max, Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using abs = unpack<L, mp::abs<Cmp, C>>;

    template<class L, class C = mp::identity>
    using pow = unpack<L, mp::pow<C>>;

    template<class L, class C = mp::identity>
    using pow0 = unpack<L, mp::pow0<C>>;

    template<class L, class C = mp::identity>
    using pow1 = unpack<L, mp::pow1<C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<int_ b, int_ e, int_ r = 1>
  struct _ipow
  : _ipow<(b * b), (e / 2), (e % 2 ? b * r : r)>
  {};

  struct _pow
  {
    template<class base, class exponent>
    using f = typename _ipow<base::value, exponent::value, 1>::type;
  };

  template<int_ b, int_ r>
  struct _ipow<b, 0, r>
  {
    using type = number<1>;
  };

  template<int_ b, int_ r>
  struct _ipow<b, 1, r>
  {
    using type = number<b * r>;
  };

  template<int_ b, int_ r>
  struct _ipow<b, -1, r>
  {
    using type = number<1 / (b * r)>;
  };

  template<int_ r>
  struct _ipow<0, -1, r>
  {};
}
/// \endcond
namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = identity>
  using min = fold_left<if_<
    contract<mp::flip<concepts::predicate<assume_binary<Cmp>>>>,
    contract<mp::at1<>>,
    contract<mp::at0<>>
  >, C>;

  template<class Cmp = less<>, class C = identity>
  using min0 = if_<contract<mp::size<>>, min<Cmp, C>, always<number<0>, C>>;


  template<class Cmp = less<>, class C = identity>
  using max = fold_left<if_<
    contract<concepts::predicate<assume_binary<Cmp>>>,
    contract<mp::at1<>>,
    contract<mp::at0<>>
  >, C>;

  template<class Cmp = less<>, class C = identity>
  using max0 = if_<contract<mp::size<>>, max<Cmp, C>, always<number<0>, C>>;


  template<class Min, class Max, class Cmp = less<>, class C = identity>
  using clamp = detail::sfinae<mp::clamp<Min, Max, subcontract_barrier<Cmp>, subcontract_barrier<C>>>;

  template<int_ min, int_ max, class Cmp = less<>, class C = identity>
  using clamp_c = clamp<number<min>, number<max>, Cmp, C>;


  template<class Cmp = less<>, class C = identity>
  using abs = detail::sfinae<mp::abs<subcontract_barrier<Cmp>, subcontract_barrier<C>>>;


  template<class C = identity>
  using pow = detail::sfinae<mp::pow<subcontract_barrier<C>>>;

  template<class C = identity>
  using pow0 = if_<contract<mp::size<>>, pow<C>, always<number<0>, C>>;

  template<class C = identity>
  using pow1 = if_<contract<mp::size<>>, pow<C>, always<number<1>, C>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, _pow>
  {
    using type = try_contract<_pow>;
  };
}
/// \endcond
namespace jln::mp
{
  using detail::sfinae;
  using detail::sfinae_once;
}
namespace jln::mp
{
  /// \ingroup trait

  /// Wrapper for alignof keyword
  /// \treturn \number
  template<class C = identity>
  struct alignof_
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<alignof(x)>);
  };

  namespace emp
  {
    template<class x>
    using alignof_ = number<alignof(x)>;
  }
}
namespace jln::mp::smp
{
  template<class C = identity>
  using alignof_ = try_contract<mp::alignof_<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, alignof_<C>>
  {
    using type = smp::alignof_<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<bool b>
  using conditional_c = try_contract<mp::conditional_c<b>>;
}

JLN_MP_MAKE_REGULAR_SMP1_P(conditional, (x), smp::conditional_c<bool(x::value)>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, bool b>
  struct _sfinae<sfinae, conditional_c<b>>
  {
    using type = smp::conditional_c<b>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT(argument_category::binary, (bool b), (conditional_c<b>));
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class x, class = void>
    struct _has_type;
  }
  /// \endcond

  /// \ingroup trait

  /// Checks whether a \value to a type member.
  /// \treturn \bool
  template<class C = identity>
  struct has_type
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_has_type<x>::type);
  };

  namespace emp
  {
    template<class x>
    using has_type = typename detail::_has_type<x>::type;

    template<class x>
    inline constexpr bool has_type_v = detail::_has_type<x>::type::value;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<class x, class>
  struct _has_type
  {
    using type = false_;
  };

  template<class x>
  struct _has_type<x, std::void_t<typename x::type>>
  {
    using type = true_;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = identity>
  using has_type = try_contract<mp::has_type<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, has_type<C>>
  {
    using type = smp::has_type<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, has_type);
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class x, class = void>
    struct _has_value_type;
  }
  /// \endcond

  /// \ingroup trait

  /// Checks whether a \value to a type member.
  /// \treturn \bool
  template<class C = identity>
  struct has_value_type
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_has_value_type<x>::type);
  };

  namespace emp
  {
    template<class x>
    using has_value_type = typename detail::_has_value_type<x>::type;

    template<class x>
    inline constexpr bool has_value_type_v = detail::_has_value_type<x>::type::value;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<class x, class>
  struct _has_value_type
  {
    using type = false_;
  };

  template<class x>
  struct _has_value_type<x, std::void_t<typename x::type>>
  {
    using type = true_;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = identity>
  using has_value_type = try_contract<mp::has_value_type<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, has_value_type<C>>
  {
    using type = smp::has_value_type<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, has_value_type);
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<template<class...> class Tpl, class T>
    struct _is_specialization_of;
  }
  /// \endcond

  /// \ingroup trait

  /// Checks whether \c x is \c Tpl<xs...>
  /// \treturn \bool
  template<template<class...> class Tpl, class C = identity>
  struct is_specialization_of
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::_is_specialization_of<Tpl, x>::type);
  };

  namespace emp
  {
    template<template<class...> class Tpl, class x>
    using is_specialization_of = typename detail::_is_specialization_of<Tpl, x>::type;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<template<class...> class Tpl, class T>
  struct _is_specialization_of
  {
    using type = false_;
  };

  template<template<class...> class Tpl, class... Ts>
  struct _is_specialization_of<Tpl, Tpl<Ts...>>
  {
    using type = true_;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<template<class...> class Tpl, class C = identity>
  using is_specialization_of = try_contract<mp::is_specialization_of<Tpl, assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, template<class...> class Tpl, class C>
  struct _sfinae<sfinae, is_specialization_of<Tpl, C>>
  {
    using type = smp::is_specialization_of<Tpl, sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT(argument_category::unary,
    (template<class...> class Tpl, class C),
    (is_specialization_of<Tpl, C>));
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct iterate_impl;
  }
  /// \endcond

  /// \ingroup utility

  /// Apply a function \c n times to its argument.
  /// \treturn \value
  template<uint_ n, class F, class C = identity>
  struct iterate_c
  {
    template<class x>
    using f = typename detail::iterate_impl<n>
      ::template f<n, C, JLN_MP_TRACE_F(F), x>;
  };

  /// Apply a function \c n times to its argument.
  /// \treturn \value
  template<class n, class F, class C = identity>
  using iterate = iterate_c<n::value, F, C>;

  namespace emp
  {
    template<class L, class n, class F, class C = mp::identity>
    using iterate = unpack<L, mp::iterate<n, F, C>>;

    template<class L, uint_ n, class F, class C = mp::identity>
    using iterate_c = unpack<L, mp::iterate_c<n, F, C>>;
  }
} // namespace jln::mp


/// \cond
namespace jln::mp::detail
{
  template<uint_ n>
  struct iterate_impl : iterate_impl<
      n <= 16 ? 8
    : n <= 32 ? 16
    : n <= 64 ? 32
    : n <= 128 ? 64
    : 128
  >
  {
  };

  template<>
  struct iterate_impl<0>
  {
    template<uint_ i, class C, class F, class x>
    using f = JLN_MP_CALL_TRACE(C, x);
  };

#define JLN_MP_ITERATE(n, mp_xs, mp_rsx, mp_rep)  \
  template<>                                      \
  struct iterate_impl<n>                          \
  {                                               \
    template<uint_ i, class C, class F, class x>  \
    using f = JLN_MP_CALL_TRACE(C,                \
      mp_rep(typename F::template f<, JLN_MP_NIL) \
      x                                           \
      mp_rep(>, JLN_MP_NIL)                       \
    );                                            \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_ITERATE)

#undef JLN_MP_ITERATE

#define JLN_MP_ITERATE(n, mp_xs, mp_rsx, mp_rep)    \
  template<>                                        \
  struct iterate_impl<n>                            \
  {                                                 \
    template<uint_ i, class C, class F, class x>    \
    using f = typename iterate_impl<i-n>            \
      ::template f<i-n, C, F,                       \
        mp_rep(typename F::template f<, JLN_MP_NIL) \
        x                                           \
        mp_rep(>, JLN_MP_NIL)                       \
      >;                                            \
  };

  JLN_MP_GEN_XS_8_16_32_64_128(JLN_MP_ITERATE)

#undef JLN_MP_ITERATE
}
/// \endcond
namespace jln::mp::smp
{
  template<uint_ n, class F, class C = identity>
  using iterate_c = test_contract<mp::is_size_of_c<1>, mp::iterate_c<
    n,
    mp::monadic0<assume_unary<F>>,
    mp::monadic0<assume_unary<C>>>
  >;
}

JLN_MP_MAKE_REGULAR_SMP3_P(iterate, (n), (F), (C, smp::identity),
    smp::iterate_c<mp::uint_{n::value}, F, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, uint_ n, class F, class C>
  struct _sfinae<sfinae, iterate_c<n, F, C>>
  {
    using type = smp::iterate_c<n, sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup trait

  /// Wrapper for sizeof keyword
  /// \treturn \number
  template<class C = identity>
  struct sizeof_
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<sizeof(x)>);
  };

  namespace emp
  {
    template<class x>
    using sizeof_ = number<sizeof(x)>;
  }
}
namespace jln::mp::smp
{
  template<class C = identity>
  using sizeof_ = try_contract<mp::sizeof_<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, sizeof_<C>>
  {
    using type = smp::sizeof_<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp::traits
{
  /// \ingroup trait

#define JLN_MP_MAKE_TRAIT(Name)                   \
  template<class C = identity>                    \
  struct Name                                     \
  {                                               \
    template<class... xs>                         \
    using f = JLN_MP_CALL_TRACE(C,                \
      typename std::Name<xs...>::type);           \
  };                                              \
                                                  \
  namespace emp                                   \
  {                                               \
    template<class... xs>                         \
    using Name = typename std::Name<xs...>::type; \
  }                                               \
                                                  \
  template<>                                      \
  struct Name<identity>                           \
  {                                               \
    template<class... xs>                         \
    using f = typename std::Name<xs...>::type;    \
  }


  // primary type categories:
#if __cplusplus >= 201703L
  JLN_MP_MAKE_TRAIT(is_void);
#endif
#if __cplusplus >= 201402L
  JLN_MP_MAKE_TRAIT(is_null_pointer);
#endif
  JLN_MP_MAKE_TRAIT(is_integral);
  JLN_MP_MAKE_TRAIT(is_floating_point);
  JLN_MP_MAKE_TRAIT(is_array);
  JLN_MP_MAKE_TRAIT(is_pointer);
  JLN_MP_MAKE_TRAIT(is_lvalue_reference);
  JLN_MP_MAKE_TRAIT(is_rvalue_reference);
  JLN_MP_MAKE_TRAIT(is_member_object_pointer);
  JLN_MP_MAKE_TRAIT(is_member_function_pointer);
  JLN_MP_MAKE_TRAIT(is_enum);
  JLN_MP_MAKE_TRAIT(is_union);
  JLN_MP_MAKE_TRAIT(is_class);
  JLN_MP_MAKE_TRAIT(is_function);

  // composite type categories:
  JLN_MP_MAKE_TRAIT(is_reference);
  JLN_MP_MAKE_TRAIT(is_arithmetic);
  JLN_MP_MAKE_TRAIT(is_fundamental);
  JLN_MP_MAKE_TRAIT(is_object);
  JLN_MP_MAKE_TRAIT(is_scalar);
  JLN_MP_MAKE_TRAIT(is_compound);
  JLN_MP_MAKE_TRAIT(is_member_pointer);

  // type properties:
  JLN_MP_MAKE_TRAIT(is_const);
  JLN_MP_MAKE_TRAIT(is_volatile);
  JLN_MP_MAKE_TRAIT(is_trivial);
  JLN_MP_MAKE_TRAIT(is_trivially_copyable);
  JLN_MP_MAKE_TRAIT(is_standard_layout);
#if __cplusplus <= 201703L
  JLN_MP_MAKE_TRAIT(is_pod);
#endif
  JLN_MP_MAKE_TRAIT(is_empty);
  JLN_MP_MAKE_TRAIT(is_polymorphic);
  JLN_MP_MAKE_TRAIT(is_abstract);
#if __cplusplus >= 201402L
  JLN_MP_MAKE_TRAIT(is_final);
#endif
#if __cplusplus >= 201703L
  JLN_MP_MAKE_TRAIT(is_aggregate);
#endif
  JLN_MP_MAKE_TRAIT(is_signed);
  JLN_MP_MAKE_TRAIT(is_unsigned);
#if defined(__cpp_lib_bounded_array_traits) && __cpp_lib_bounded_array_traits
  JLN_MP_MAKE_TRAIT(is_bounded_array);
  JLN_MP_MAKE_TRAIT(is_unbounded_array);
#endif
  JLN_MP_MAKE_TRAIT(is_constructible);
  JLN_MP_MAKE_TRAIT(is_default_constructible);
  JLN_MP_MAKE_TRAIT(is_copy_constructible);
  JLN_MP_MAKE_TRAIT(is_move_constructible);
  JLN_MP_MAKE_TRAIT(is_assignable);
  JLN_MP_MAKE_TRAIT(is_copy_assignable);
  JLN_MP_MAKE_TRAIT(is_move_assignable);
#if __cplusplus >= 201703L
  JLN_MP_MAKE_TRAIT(is_swappable_with);
  JLN_MP_MAKE_TRAIT(is_swappable);
  JLN_MP_MAKE_TRAIT(is_nothrow_swappable_with);
  JLN_MP_MAKE_TRAIT(is_nothrow_swappable);
#endif
  JLN_MP_MAKE_TRAIT(is_destructible);
  JLN_MP_MAKE_TRAIT(is_trivially_constructible);
  JLN_MP_MAKE_TRAIT(is_trivially_default_constructible);
  JLN_MP_MAKE_TRAIT(is_trivially_copy_constructible);
  JLN_MP_MAKE_TRAIT(is_trivially_move_constructible);
  JLN_MP_MAKE_TRAIT(is_trivially_assignable);
  JLN_MP_MAKE_TRAIT(is_trivially_copy_assignable);
  JLN_MP_MAKE_TRAIT(is_trivially_move_assignable);
  JLN_MP_MAKE_TRAIT(is_trivially_destructible);
  JLN_MP_MAKE_TRAIT(is_nothrow_constructible);
  JLN_MP_MAKE_TRAIT(is_nothrow_default_constructible);
  JLN_MP_MAKE_TRAIT(is_nothrow_copy_constructible);
  JLN_MP_MAKE_TRAIT(is_nothrow_move_constructible);
  JLN_MP_MAKE_TRAIT(is_nothrow_assignable);
  JLN_MP_MAKE_TRAIT(is_nothrow_copy_assignable);
  JLN_MP_MAKE_TRAIT(is_nothrow_move_assignable);
  JLN_MP_MAKE_TRAIT(is_nothrow_destructible);
  JLN_MP_MAKE_TRAIT(has_virtual_destructor);
#if __cplusplus >= 201703L
  JLN_MP_MAKE_TRAIT(has_unique_object_representations);
#endif

  // type property queries:
  JLN_MP_MAKE_TRAIT(alignment_of);
  JLN_MP_MAKE_TRAIT(rank);

  template<class C = identity>
  struct extent
  {
    template<class x, class... i>
    using f = JLN_MP_CALL_TRACE(C, typename std::extent<x, i::value...>::type);
  };

  namespace emp
  {
    template<class x, class i = number<0>>
    using extent = typename std::extent<x, i::value>::type;
  }

  /// \cond
  template<>
  struct extent<identity>
  {
    template<class x, class i = number<0>>
    using f = typename std::extent<x, i::value>::type;
  };
  /// \endcond

  // type relations:
  JLN_MP_MAKE_TRAIT(is_same);
  JLN_MP_MAKE_TRAIT(is_base_of);
  JLN_MP_MAKE_TRAIT(is_convertible);
#if defined(__cpp_lib_is_nothrow_convertible) && __cpp_lib_is_nothrow_convertible
  JLN_MP_MAKE_TRAIT(is_nothrow_convertible);
#endif
#if defined(__cpp_lib_is_layout_compatible) && __cpp_lib_is_layout_compatible
  JLN_MP_MAKE_TRAIT(is_layout_compatible);
#endif
#if defined(__cpp_lib_is_pointer_interconvertible) && __cpp_lib_is_pointer_interconvertible
  JLN_MP_MAKE_TRAIT(is_pointer_interconvertible_base_of);
#endif
#if __cplusplus >= 201703L
  JLN_MP_MAKE_TRAIT(is_invocable);
  JLN_MP_MAKE_TRAIT(is_invocable_r);
  JLN_MP_MAKE_TRAIT(is_nothrow_invocable);
  JLN_MP_MAKE_TRAIT(is_nothrow_invocable_r);
#endif

  // const-volatile modifications:
  JLN_MP_MAKE_TRAIT(remove_const);
  JLN_MP_MAKE_TRAIT(remove_volatile);
  JLN_MP_MAKE_TRAIT(remove_cv);
  JLN_MP_MAKE_TRAIT(add_const);
  JLN_MP_MAKE_TRAIT(add_volatile);
  JLN_MP_MAKE_TRAIT(add_cv);

  // reference modifications:
  JLN_MP_MAKE_TRAIT(remove_reference);
  JLN_MP_MAKE_TRAIT(add_lvalue_reference);
  JLN_MP_MAKE_TRAIT(add_rvalue_reference);

  // sign modifications:
  JLN_MP_MAKE_TRAIT(make_signed);
  JLN_MP_MAKE_TRAIT(make_unsigned);

  // array modifications:
  JLN_MP_MAKE_TRAIT(remove_extent);
  JLN_MP_MAKE_TRAIT(remove_all_extents);

  // pointer modifications:
  JLN_MP_MAKE_TRAIT(remove_pointer);
  JLN_MP_MAKE_TRAIT(add_pointer);

  // other transformations:
  JLN_MP_MAKE_TRAIT(decay);
#if defined(__cpp_lib_unwrap_ref) && __cpp_lib_unwrap_ref
  JLN_MP_MAKE_TRAIT(unwrap_ref_decay);
  JLN_MP_MAKE_TRAIT(unwrap_reference);
#endif
#if defined(__cpp_lib_remove_cvref) && __cpp_lib_remove_cvref
  JLN_MP_MAKE_TRAIT(remove_cvref);
#endif
#if __cplusplus >= 202002L
  JLN_MP_MAKE_TRAIT(common_reference);
  JLN_MP_MAKE_TRAIT(basic_common_reference);
#else
  JLN_MP_MAKE_TRAIT(result_of);
#endif
  JLN_MP_MAKE_TRAIT(underlying_type);
  JLN_MP_MAKE_TRAIT(common_type);
#if __cplusplus >= 201703L
  JLN_MP_MAKE_TRAIT(invoke_result);
#endif

  template<class C = identity>
  struct aligned_storage
  {
    template<class Len, class... Alignment>
    using f = JLN_MP_CALL_TRACE(C,
      typename std::aligned_storage<Len::value, Alignment::value...>::type
    );
  };

  namespace emp
  {
    template<class Len, class... Alignment>
    using aligned_storage = typename std::aligned_storage<
      Len::value, Alignment::value...>::type;
  }

  /// \cond
  template<>
  struct aligned_storage<identity>
  {
    template<class Len, class... Alignment>
    using f = typename std::aligned_storage<Len::value, Alignment::value...>::type;
  };
  /// \endcond

  template<class C = identity>
  struct aligned_union
  {
    template<class len, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename std::aligned_union<len::value, xs...>::type
    );
  };

  namespace emp
  {
    template<class len, class... xs>
    using aligned_union = typename std::aligned_union<len::value, xs...>::type;
  }

  /// \cond
  template<>
  struct aligned_union<identity>
  {
    template<class len, class... xs>
    using f = typename std::aligned_union<len::value, xs...>::type;
  };
  /// \endcond
}
namespace jln::mp
{

#define JLN_MP_SMP_MAKE_TRAIT(Name)                 \
  namespace smp::traits                             \
  {                                                 \
    template <class C = identity>                   \
    using Name = try_contract<                      \
      mp::traits::Name<assume_unary<C>>>;           \
  }                                                 \
                                                    \
  namespace detail                                  \
  {                                                 \
    template<template<class> class sfinae, class C> \
    struct _sfinae<sfinae, traits::Name<C>>         \
    {                                               \
      using type = smp::traits::Name<sfinae<C>>;    \
    };                                              \
  }

#define JLN_MP_SMP_MAKE_TRAIT2(Name)         \
  JLN_MP_SMP_MAKE_TRAIT(Name)                \
  namespace detail                           \
  {                                          \
    JLN_MP_MAKE_EXPECTED_ARGUMENT1(          \
      argument_category::unary, traits::Name \
    );                                       \
  }


  // primary type categories:
#if __cplusplus >= 201703L
  JLN_MP_SMP_MAKE_TRAIT2(is_void)
#endif
#if __cplusplus >= 201402L
  JLN_MP_SMP_MAKE_TRAIT2(is_null_pointer)
#endif
  JLN_MP_SMP_MAKE_TRAIT2(is_integral)
  JLN_MP_SMP_MAKE_TRAIT2(is_floating_point)
  JLN_MP_SMP_MAKE_TRAIT2(is_array)
  JLN_MP_SMP_MAKE_TRAIT2(is_pointer)
  JLN_MP_SMP_MAKE_TRAIT2(is_lvalue_reference)
  JLN_MP_SMP_MAKE_TRAIT2(is_rvalue_reference)
  JLN_MP_SMP_MAKE_TRAIT2(is_member_object_pointer)
  JLN_MP_SMP_MAKE_TRAIT2(is_member_function_pointer)
  JLN_MP_SMP_MAKE_TRAIT2(is_enum)
  JLN_MP_SMP_MAKE_TRAIT2(is_union)
  JLN_MP_SMP_MAKE_TRAIT2(is_class)
  JLN_MP_SMP_MAKE_TRAIT2(is_function)

  // composite type categories:
  JLN_MP_SMP_MAKE_TRAIT2(is_reference)
  JLN_MP_SMP_MAKE_TRAIT2(is_arithmetic)
  JLN_MP_SMP_MAKE_TRAIT2(is_fundamental)
  JLN_MP_SMP_MAKE_TRAIT2(is_object)
  JLN_MP_SMP_MAKE_TRAIT2(is_scalar)
  JLN_MP_SMP_MAKE_TRAIT2(is_compound)
  JLN_MP_SMP_MAKE_TRAIT2(is_member_pointer)

  // type properties:
  JLN_MP_SMP_MAKE_TRAIT2(is_const)
  JLN_MP_SMP_MAKE_TRAIT2(is_volatile)
  JLN_MP_SMP_MAKE_TRAIT(is_trivial)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_copyable)
  JLN_MP_SMP_MAKE_TRAIT(is_standard_layout)
#if __cplusplus <= 201703L
  JLN_MP_SMP_MAKE_TRAIT(is_pod)
#endif
  JLN_MP_SMP_MAKE_TRAIT(is_empty)
  JLN_MP_SMP_MAKE_TRAIT(is_polymorphic)
  JLN_MP_SMP_MAKE_TRAIT(is_abstract)
#if __cplusplus >= 201402L
  JLN_MP_SMP_MAKE_TRAIT(is_final)
#endif
#if __cplusplus >= 201703L
  JLN_MP_SMP_MAKE_TRAIT(is_aggregate)
#endif
  JLN_MP_SMP_MAKE_TRAIT2(is_signed)
  JLN_MP_SMP_MAKE_TRAIT2(is_unsigned)
#if defined(__cpp_lib_bounded_array_traits) && __cpp_lib_bounded_array_traits
  JLN_MP_SMP_MAKE_TRAIT2(is_bounded_array)
  JLN_MP_SMP_MAKE_TRAIT2(is_unbounded_array)
#endif
  JLN_MP_SMP_MAKE_TRAIT(is_constructible)
  JLN_MP_SMP_MAKE_TRAIT(is_default_constructible)
  JLN_MP_SMP_MAKE_TRAIT(is_copy_constructible)
  JLN_MP_SMP_MAKE_TRAIT(is_move_constructible)
  JLN_MP_SMP_MAKE_TRAIT(is_assignable)
  JLN_MP_SMP_MAKE_TRAIT(is_copy_assignable)
  JLN_MP_SMP_MAKE_TRAIT(is_move_assignable)
#if __cplusplus >= 201703L
  JLN_MP_SMP_MAKE_TRAIT(is_swappable_with)
  JLN_MP_SMP_MAKE_TRAIT(is_swappable)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_swappable_with)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_swappable)
#endif
  JLN_MP_SMP_MAKE_TRAIT(is_destructible)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_constructible)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_default_constructible)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_copy_constructible)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_move_constructible)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_assignable)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_copy_assignable)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_move_assignable)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_destructible)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_constructible)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_default_constructible)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_copy_constructible)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_move_constructible)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_assignable)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_copy_assignable)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_move_assignable)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_destructible)
  JLN_MP_SMP_MAKE_TRAIT(has_virtual_destructor)
#if __cplusplus >= 201703L
  JLN_MP_SMP_MAKE_TRAIT(has_unique_object_representations)
#endif

  // type property queries:
  JLN_MP_SMP_MAKE_TRAIT(alignment_of)
  JLN_MP_SMP_MAKE_TRAIT2(rank)

  JLN_MP_SMP_MAKE_TRAIT2(extent)

  // type relations:
  JLN_MP_SMP_MAKE_TRAIT2(is_same)
  JLN_MP_SMP_MAKE_TRAIT(is_base_of)
  JLN_MP_SMP_MAKE_TRAIT(is_convertible)
#if defined(__cpp_lib_is_nothrow_convertible) && __cpp_lib_is_nothrow_convertible
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_convertible)
#endif
#if defined(__cpp_lib_is_layout_compatible) && __cpp_lib_is_layout_compatible
  JLN_MP_SMP_MAKE_TRAIT(is_layout_compatible)
#endif
#if defined(__cpp_lib_is_pointer_interconvertible) && __cpp_lib_is_pointer_interconvertible
  JLN_MP_SMP_MAKE_TRAIT(is_pointer_interconvertible_base_of)
#endif
#if __cplusplus >= 201703L
  JLN_MP_SMP_MAKE_TRAIT(is_invocable)
  JLN_MP_SMP_MAKE_TRAIT(is_invocable_r)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_invocable)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_invocable_r)
#endif

  // const-volatile modifications:
  JLN_MP_SMP_MAKE_TRAIT2(remove_const)
  JLN_MP_SMP_MAKE_TRAIT2(remove_volatile)
  JLN_MP_SMP_MAKE_TRAIT2(remove_cv)
  JLN_MP_SMP_MAKE_TRAIT2(add_const)
  JLN_MP_SMP_MAKE_TRAIT2(add_volatile)
  JLN_MP_SMP_MAKE_TRAIT2(add_cv)

  // reference modifications:
  JLN_MP_SMP_MAKE_TRAIT2(remove_reference)
  JLN_MP_SMP_MAKE_TRAIT2(add_lvalue_reference)
  JLN_MP_SMP_MAKE_TRAIT2(add_rvalue_reference)

  // sign modifications:
  JLN_MP_SMP_MAKE_TRAIT(make_signed)
  JLN_MP_SMP_MAKE_TRAIT(make_unsigned)

  // array modifications:
  JLN_MP_SMP_MAKE_TRAIT2(remove_extent)
  JLN_MP_SMP_MAKE_TRAIT2(remove_all_extents)

  // pointer modifications:
  JLN_MP_SMP_MAKE_TRAIT(remove_pointer)
  JLN_MP_SMP_MAKE_TRAIT(add_pointer)

  // other transformations:
  JLN_MP_SMP_MAKE_TRAIT2(decay)
#if defined(__cpp_lib_unwrap_ref) && __cpp_lib_unwrap_ref
  JLN_MP_SMP_MAKE_TRAIT2(unwrap_ref_decay)
  JLN_MP_SMP_MAKE_TRAIT2(unwrap_reference)
#endif
#if defined(__cpp_lib_remove_cvref) && __cpp_lib_remove_cvref
  JLN_MP_SMP_MAKE_TRAIT2(remove_cvref)
#endif
#if __cplusplus >= 202002L
  JLN_MP_SMP_MAKE_TRAIT(common_reference)
  JLN_MP_SMP_MAKE_TRAIT(basic_common_reference)
#else
  JLN_MP_SMP_MAKE_TRAIT(result_of)
#endif
  JLN_MP_SMP_MAKE_TRAIT(underlying_type)
  JLN_MP_SMP_MAKE_TRAIT(common_type)
#if __cplusplus >= 201703L
  JLN_MP_SMP_MAKE_TRAIT(invoke_result)
#endif

  JLN_MP_SMP_MAKE_TRAIT(aligned_storage)
  JLN_MP_SMP_MAKE_TRAIT(aligned_union)
}
namespace jln::mp::smp
{
  template<class C = identity>
  using type_ = try_contract<mp::type_<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, type_<C>>
  {
    using type = smp::type_<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup trait

  /// Function for \c x::value_type.
  /// \treturn \value
  template<class C = identity>
  struct value_type
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename x::value_type);
  };

  template<>
  struct value_type<identity>
  {
    template<class x>
    using f = typename x::value_type;
  };

  namespace emp
  {
    template<class x>
    using value_type = typename x::value_type;
  }
}
namespace jln::mp::smp
{
  template<class C = identity>
  using value_type = try_contract<mp::value_type<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, value_type<C>>
  {
    using type = smp::value_type<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \ingroup value

  /// Converts \c x to \val.
  /// \pre \c emp::has_value<x> == \c true
  /// \treturn \bool
  template<class C = identity>
  struct as_val
  {
#if __cplusplus >= 201703L
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, val<x::value>);
#else
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typed_value<decltype(x::value), x::value>);
#endif
  };

  /// \cond
  template<>
  struct as_val<identity>
  {
#if __cplusplus >= 201703L
    template<class x>
    using f = val<x::value>;
#else
    template<class x>
    using f = typed_value<decltype(x::value), x::value>;
#endif
  };
  /// \endcond

  namespace emp
  {
    template<class x, class C = mp::identity>
    using as_val = typename mp::as_val<C>::template f<x>;
  }
}
namespace jln::mp::smp
{
  template<class C = identity>
  using as_val = try_contract<mp::as_val<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, as_val<C>>
  {
    using type = smp::as_val<sfinae<C>>;
  };
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class x, class = void>
    struct _has_value;
  }
  /// \endcond

  /// \ingroup value

  /// Checks whether \c x has a value member.
  /// \treturn \bool
  template<class C = identity>
  struct has_value
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_has_value<x>::type);
  };

  namespace emp
  {
    template<class x>
    using has_value = typename detail::_has_value<x>::type;

    template<class x>
    inline constexpr bool has_value_v = detail::_has_value<x>::type::value;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<class x, class>
  struct _has_value
  {
    using type = false_;
  };

  template<class x>
  struct _has_value<x, decltype(void(x::value))>
  {
    using type = true_;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = identity>
  using has_value = try_contract<mp::has_value<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, has_value<C>>
  {
    using type = smp::has_value<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, has_value);
}
/// \endcond
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class x>
    struct _is_val;
  }
  /// \endcond

  /// \ingroup value

  /// Checks whether \c x is a \val.
  /// \treturn \bool
  template<class C = identity>
  struct is_val
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_is_val<x>::type);
  };

  namespace emp
  {
    template<class x>
    using is_val = typename detail::_is_val<x>::type;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct _is_val
  {
    using type = false_;
  };

#if __cplusplus >= 201703L
  template<auto x>
  struct _is_val<val<x>>
#else
  template<class T, T x>
  struct _is_val<typed_value<T, x>>
#endif
  {
    using type = true_;
  };
}
/// \endcond
namespace jln::mp::smp
{
  template<class C = identity>
  using is_val = try_contract<mp::is_val<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_val<C>>
  {
    using type = smp::is_val<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, is_val);
}
/// \endcond
JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wlogical-op")

namespace jln::mp
{
  /// \ingroup value

  template<class C = identity>
  struct val_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(xs::value || ... || false)>);
  };

  template<class C = identity>
  struct val_left_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(false || ... || xs::value)>);
  };


  template<class C = identity>
  struct val_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(xs::value && ... && true)>);
  };

  template<class C = identity>
  struct val_left_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(true && ... && xs::value)>);
  };


  template<class C = identity>
  struct val_add
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(xs::value + ...)>);
  };

  template<class C = identity>
  using val_add0 = if_<size<>, val_add<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_left_add
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... + xs::value)>);
  };

  template<class C = identity>
  using val_left_add0 = if_<size<>, val_left_add<C>, always<val<0>, C>>;


  template<class C = identity>
  struct val_sub
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... - xs::value)>);
  };

  template<class C = identity>
  using val_sub0 = if_<size<>, val_sub<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_lshift
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... << xs::value)>);
  };

  template<class C = identity>
  using val_lshift0 = if_<size<>, val_lshift<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_rshift
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... >> xs::value)>);
  };

  template<class C = identity>
  using val_rshift0 = if_<size<>, val_rshift<C>, always<val<0>, C>>;


  template<class C = identity>
  struct val_mul
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(xs::value * ...)>);
  };

  template<class C = identity>
  using val_mul0 = if_<size<>, val_mul<C>, always<val<0>, C>>;

  template<class C = identity>
  using val_mul1 = if_<size<>, val_mul<C>, always<val<1>, C>>;

  template<class C = identity>
  struct val_left_mul
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... * xs::value)>);
  };

  template<class C = identity>
  using val_left_mul0 = if_<size<>, val_left_mul<C>, always<val<0>, C>>;

  template<class C = identity>
  using val_left_mul1 = if_<size<>, val_left_mul<C>, always<val<1>, C>>;


  template<class C = identity>
  struct val_div
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... / xs::value)>);
  };

  template<class C = identity>
  using val_div0 = if_<size<>, val_div<C>, always<val<0>, C>>;

  template<class C = identity>
  using val_div1 = if_<size<>, val_div<C>, always<val<1>, C>>;

  template<class C = identity>
  struct val_mod
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... % xs::value)>);
  };

  template<class C = identity>
  using val_mod0 = if_<size<>, val_mod<C>, always<val<0>, C>>;

  template<class C = identity>
  using val_mod1 = if_<size<>, val_mod<C>, always<val<1>, C>>;


  template<class C = identity>
  struct val_xor
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(xs::value ^ ...)>);
  };

  template<class C = identity>
  using val_xor0 = if_<size<>, val_xor<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_left_xor
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... ^ xs::value)>);
  };

  template<class C = identity>
  using val_left_xor0 = if_<size<>, val_left_xor<C>, always<val<0>, C>>;


  template<class C = identity>
  struct val_bit_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(xs::value & ...)>);
  };

  template<class C = identity>
  using val_bit_and0 = if_<size<>, val_bit_and<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_left_bit_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... & xs::value)>);
  };

  template<class C = identity>
  using val_left_bit_and0 = if_<size<>, val_bit_and<C>, always<val<0>, C>>;


  template<class C = identity>
  struct val_bit_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(xs::value | ...)>);
  };

  template<class C = identity>
  using val_bit_or0 = if_<size<>, val_bit_or<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_left_bit_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... | xs::value)>);
  };

  template<class C = identity>
  using val_left_bit_or0 = if_<size<>, val_left_bit_or<C>, always<val<0>, C>>;


  template<class C = identity>
  struct val_neg
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, val<(-x::value)>);
  };

  template<class C = identity>
  struct val_unary_plus
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, val<(+x::value)>);
  };

  template<class C = identity>
  struct val_not
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, val<(!x::value)>);
  };

  template<class C = identity>
  struct val_bit_not
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, val<(~x::value)>);
  };

  template<class C = identity>
  struct val_inc
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value+1)>);
  };

  template<class C = identity>
  struct val_dec
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value-1)>);
  };

  template<class C = identity>
  struct val_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value == y::value)>);
  };

  template<class C = identity>
  struct val_not_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value != y::value)>);
  };

  template<class C = identity>
  struct val_less
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value < y::value)>);
  };

  template<class C = identity>
  struct val_less_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value <= y::value)>);
  };

  template<class C = identity>
  struct val_greater
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value > y::value)>);
  };

  template<class C = identity>
  struct val_greater_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value >= y::value)>);
  };


  template<class N, class C = identity>
  using val_equal_to = push_back<N, val_equal<C>>;

  template<class N, class C = identity>
  using val_not_equal_to = push_back<N, val_not_equal<C>>;

  template<class N, class C = identity>
  using val_less_than = push_back<N, val_less<C>>;

  template<class N, class C = identity>
  using val_less_equal_than = push_back<N, val_less_equal<C>>;

  template<class N, class C = identity>
  using val_greater_than = push_back<N, val_greater<C>>;

  template<class N, class C = identity>
  using val_greater_equal_than = push_back<N, val_greater_equal<C>>;


  template<auto x, class C = identity>
  using val_equal_to_c = val_equal_to<val<x>, C>;

  template<auto x, class C = identity>
  using val_not_equal_to_c = val_not_equal_to<val<x>, C>;

  template<auto x, class C = identity>
  using val_less_than_c = val_less_than<val<x>, C>;

  template<auto x, class C = identity>
  using val_less_equal_than_c = val_less_equal_than<val<x>, C>;

  template<auto x, class C = identity>
  using val_greater_than_c = val_greater_than<val<x>, C>;

  template<auto x, class C = identity>
  using val_greater_equal_than_c = val_greater_equal_than<val<x>, C>;
}

namespace jln::mp::emp
{
  template<class L, class C = mp::identity>
  using val_or_seq = unpack<L, mp::val_or<C>>;

  template<class L, class C = mp::identity>
  using val_and_seq = unpack<L, mp::val_and<C>>;

  template<class L, class C = mp::identity>
  using val_left_or_seq = unpack<L, mp::val_left_or<C>>;

  template<class L, class C = mp::identity>
  using val_left_and_seq = unpack<L, mp::val_left_and<C>>;

  template<class L, class C = mp::identity>
  using val_add_seq = unpack<L, mp::val_add<C>>;

  template<class L, class C = mp::identity>
  using val_add0_seq = unpack<L, mp::val_add0<C>>;

  template<class L, class C = mp::identity>
  using val_left_add_seq = unpack<L, mp::val_left_add<C>>;

  template<class L, class C = mp::identity>
  using val_left_add0_seq = unpack<L, mp::val_left_add0<C>>;

  template<class L, class C = mp::identity>
  using val_sub_seq = unpack<L, mp::val_sub<C>>;

  template<class L, class C = mp::identity>
  using val_sub0_seq = unpack<L, mp::val_sub0<C>>;

  template<class L, class C = mp::identity>
  using val_lshift_seq = unpack<L, mp::val_lshift<C>>;

  template<class L, class C = mp::identity>
  using val_lshift0_seq = unpack<L, mp::val_lshift0<C>>;

  template<class L, class C = mp::identity>
  using val_rshift_seq = unpack<L, mp::val_rshift<C>>;

  template<class L, class C = mp::identity>
  using val_rshift0_seq = unpack<L, mp::val_rshift0<C>>;

  template<class L, class C = mp::identity>
  using val_mul_seq = unpack<L, mp::val_mul<C>>;

  template<class L, class C = mp::identity>
  using val_mul0_seq = unpack<L, mp::val_mul0<C>>;

  template<class L, class C = mp::identity>
  using val_mul1_seq = unpack<L, mp::val_mul1<C>>;

  template<class L, class C = mp::identity>
  using val_left_mul_seq = unpack<L, mp::val_left_mul<C>>;

  template<class L, class C = mp::identity>
  using val_left_mul0_seq = unpack<L, mp::val_left_mul0<C>>;

  template<class L, class C = mp::identity>
  using val_left_mul1_seq = unpack<L, mp::val_left_mul1<C>>;

  template<class L, class C = mp::identity>
  using val_div_seq = unpack<L, mp::val_div<C>>;

  template<class L, class C = mp::identity>
  using val_div0_seq = unpack<L, mp::val_div0<C>>;

  template<class L, class C = mp::identity>
  using val_div1_seq = unpack<L, mp::val_div1<C>>;

  template<class L, class C = mp::identity>
  using val_mod_seq = unpack<L, mp::val_mod<C>>;

  template<class L, class C = mp::identity>
  using val_mod0_seq = unpack<L, mp::val_mod0<C>>;

  template<class L, class C = mp::identity>
  using val_mod1_seq = unpack<L, mp::val_mod1<C>>;

  template<class L, class C = mp::identity>
  using val_xor_seq = unpack<L, mp::val_xor<C>>;

  template<class L, class C = mp::identity>
  using val_xor0_seq = unpack<L, mp::val_xor0<C>>;

  template<class L, class C = mp::identity>
  using val_left_xor_seq = unpack<L, mp::val_left_xor<C>>;

  template<class L, class C = mp::identity>
  using val_left_xor0_seq = unpack<L, mp::val_left_xor0<C>>;

  template<class L, class C = mp::identity>
  using val_bit_and_seq = unpack<L, mp::val_bit_and<C>>;

  template<class L, class C = mp::identity>
  using val_bit_and0_seq = unpack<L, mp::val_bit_and0<C>>;

  template<class L, class C = mp::identity>
  using val_left_bit_and_seq = unpack<L, mp::val_left_bit_and<C>>;

  template<class L, class C = mp::identity>
  using val_left_bit_and0_seq = unpack<L, mp::val_left_bit_and0<C>>;

  template<class L, class C = mp::identity>
  using val_bit_or_seq = unpack<L, mp::val_bit_or<C>>;

  template<class L, class C = mp::identity>
  using val_bit_or0_seq = unpack<L, mp::val_bit_or0<C>>;

  template<class L, class C = mp::identity>
  using val_left_bit_or_seq = unpack<L, mp::val_left_bit_or<C>>;

  template<class L, class C = mp::identity>
  using val_left_bit_or0_seq = unpack<L, mp::val_left_bit_or0<C>>;


  template<auto... xs>
  using val_or_c = val<(xs || ... || false)>;

  template<auto... xs>
  using val_and_c = val<(xs && ... && true)>;

  template<auto... xs>
  using val_left_or_c = val<(false || ... || xs)>;

  template<auto... xs>
  using val_left_and_c = val<(true && ... && xs)>;

  template<auto... xs>
  using val_add_c = val<(xs + ...)>;

  template<auto... xs>
  using val_add0_c = val_add_c<xs..., 0>;

  template<auto... xs>
  using val_left_add_c = val<(... + xs)>;

  template<auto... xs>
  using val_left_add0_c = val_left_add_c<xs..., 0>;

  template<auto... xs>
  using val_sub_c = val<(... - xs)>;

  template<auto... xs>
  using val_sub0_c = val_sub_c<xs..., 0>;

  template<auto... xs>
  using val_lshift_c = val<(... << xs)>;

  template<auto... xs>
  using val_lshift0_c = val_lshift_c<xs..., 0>;

  template<auto... xs>
  using val_rshift_c = val<(... >> xs)>;

  template<auto... xs>
  using val_rshift0_c = val_rshift_c<xs..., 0>;

  template<auto... xs>
  using val_mul_c = val<(xs * ...)>;

  template<auto... xs>
  using val_mul0_c = val_mul_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<auto... xs>
  using val_mul1_c = val_mul_c<xs..., 1>;

  template<auto... xs>
  using val_left_mul_c = val<(... * xs)>;

  template<auto... xs>
  using val_left_mul0_c = val_left_mul_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<auto... xs>
  using val_left_mul1_c = val_left_mul_c<xs..., 1>;

  template<auto... xs>
  using val_div_c = val<(... / xs)>;

  template<auto... xs>
  using val_div0_c = val_div_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<auto... xs>
  using val_div1_c = val_div_c<xs..., 1>;

  template<auto... xs>
  using val_mod_c = val<(... % xs)>;


  template<class... xs>
  using val_or = val<(xs::value || ... || false)>;

  template<class... xs>
  using val_and = val<(xs::value && ... && true)>;

  template<class... xs>
  using val_left_or = val<(false || ... || xs::value)>;

  template<class... xs>
  using val_left_and = val<(true && ... && xs::value)>;

  template<class... xs>
  using val_add = val<(xs::value + ...)>;

  template<class... xs>
  using val_add0 = typename mp::val_add0<>::template f<xs...>;

  template<class... xs>
  using val_left_add = val<(... + xs::value)>;

  template<class... xs>
  using val_left_add0 = typename mp::val_add0<>::template f<xs...>;

  template<class... xs>
  using val_sub = val<(... - xs::value)>;

  template<class... xs>
  using val_sub0 = typename mp::val_sub0<>::template f<xs...>;

  template<class... xs>
  using val_lshift = val<(... << xs::value)>;

  template<class... xs>
  using val_lshift0 = typename mp::val_lshift0<>::template f<xs...>;

  template<class... xs>
  using val_rshift = val<(... >> xs::value)>;

  template<class... xs>
  using val_rshift0 = typename mp::val_rshift0<>::template f<xs...>;

  template<class... xs>
  using val_mul = val<(xs::value * ...)>;

  template<class... xs>
  using val_mul0 = typename mp::val_mul0<>::template f<xs...>;

  template<class... xs>
  using val_mul1 = typename mp::val_mul1<>::template f<xs...>;

  template<class... xs>
  using val_left_mul = val<(... * xs::value)>;

  template<class... xs>
  using val_left_mul0 = typename mp::val_left_mul0<>::template f<xs...>;

  template<class... xs>
  using val_left_mul1 = typename mp::val_left_mul1<>::template f<xs...>;

  template<class... xs>
  using val_div = val<(... / xs::value)>;

  template<class... xs>
  using val_div0 = typename mp::val_div0<>::template f<xs...>;

  template<class... xs>
  using val_div1 = typename mp::val_div1<>::template f<xs...>;

  template<class... xs>
  using val_mod = val<(... % xs::value)>;

  template<class... xs>
  using val_mod0 = typename mp::val_mod0<>::template f<xs...>;

  template<class... xs>
  using val_mod1 = typename mp::val_mod1<>::template f<xs...>;

  template<class... xs>
  using val_xor_ = val<(xs::value ^ ...)>;

  template<class... xs>
  using val_xor0 = typename mp::val_xor0<>::template f<xs...>;

  template<class... xs>
  using val_left_xor = val<(... ^ xs::value)>;

  template<class... xs>
  using val_left_xor0 = typename mp::val_left_xor0<>::template f<xs...>;

  template<class... xs>
  using val_bit_and = val<(xs::value & ...)>;

  template<class... xs>
  using val_bit_and0 = typename mp::val_bit_and0<>::template f<xs...>;

  template<class... xs>
  using val_left_bit_and = val<(... & xs::value)>;

  template<class... xs>
  using val_left_bit_and0 = typename mp::val_left_bit_and0<>::template f<xs...>;

  template<class... xs>
  using val_bit_or = val<(xs::value | ...)>;

  template<class... xs>
  using val_bit_or0 = typename mp::val_bit_or0<>::template f<xs...>;

  template<class... xs>
  using val_left_bit_or = val<(... | xs::value)>;

  template<class... xs>
  using val_left_bit_or0 = typename mp::val_left_bit_or0<>::template f<xs...>;


  template<class x, class C = mp::identity>
  using val_neg = typename mp::val_neg<C>::template f<x>;

  template<class x, class C = mp::identity>
  using val_unary_plus = typename mp::val_unary_plus<C>::template f<x>;

  template<class x, class C = mp::identity>
  using val_not = typename mp::val_not<C>::template f<x>;

  template<class x, class C = mp::identity>
  using val_bit_not = typename mp::val_bit_not<C>::template f<x>;

  template<class x, class C = mp::identity>
  using val_inc = typename mp::val_inc<C>::template f<x>;

  template<class x, class C = mp::identity>
  using val_dec = typename mp::val_dec<C>::template f<x>;

  template<class x, class y, class C = mp::identity>
  using val_equal = typename mp::val_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using val_not_equal = typename mp::val_not_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using val_less = typename mp::val_less<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using val_less_equal = typename mp::val_less_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using val_greater = typename mp::val_greater<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using val_greater_equal = typename mp::val_greater_equal<C>::template f<x, y>;
}

/// \cond
namespace jln::mp::detail
{
  template<bool, template<auto...> class f, int_ d>
  struct val_emp_op;

  template<template<auto...> class F, int_ d>
  struct val_emp_op<true, F, d>
  {
    template<auto... xs>
    using f = F<xs...>;
  };

  template<template<auto...> class F, int_ d>
  struct val_emp_op<false, F, d>
  {
    template<auto...>
    using f = val<d>;
  };
}
/// \endcond

namespace jln::mp::emp
{
  template<auto... xs>
  using val_mod0_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_mod_c, 0>
    ::template f<xs...>;

  template<auto... xs>
  using val_mod1_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_mod_c, 1>
    ::template f<xs...>;

  template<auto... xs>
  using val_xor_c = val<(xs ^ ...)>;

  template<auto... xs>
  using val_xor0_c = val_xor_c<xs..., 0, 0>;

  template<auto... xs>
  using val_left_xor_c = val<(... ^ xs)>;

  template<auto... xs>
  using val_left_xor0_c = val_left_xor_c<xs..., 0, 0>;

  template<auto... xs>
  using val_bit_and_c = val<(xs & ...)>;

  template<auto... xs>
  using val_bit_and0_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_bit_and_c, 0>
    ::template f<xs...>;

  template<auto... xs>
  using val_left_bit_and_c = val<(... & xs)>;

  template<auto... xs>
  using val_left_bit_and0_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_left_bit_and_c, 0>
    ::template f<xs...>;

  template<auto... xs>
  using val_bit_or_c = val<(xs | ...)>;

  template<auto... xs>
  using val_bit_or0_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_bit_or_c, 0>
    ::template f<xs...>;

  template<auto... xs>
  using val_left_bit_or_c = val<(... | xs)>;

  template<auto... xs>
  using val_left_bit_or0_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_left_bit_or_c, 0>
    ::template f<xs...>;
}

JLN_MP_DIAGNOSTIC_POP()

/// \cond
namespace jln::mp
{
  template<>
  struct val_or<identity>
  {
    template<class... xs>
    using f = val<(xs::value || ... || false)>;
  };

  template<>
  struct val_left_or<identity>
  {
    template<class... xs>
    using f = val<(false || ... || xs::value)>;
  };


  template<>
  struct val_and<identity>
  {
    template<class... xs>
    using f = val<(xs::value && ... && true)>;
  };

  template<>
  struct val_left_and<identity>
  {
    template<class... xs>
    using f = val<(true && ... && xs::value)>;
  };


  template<>
  struct val_add<identity>
  {
    template<class... xs>
    using f = val<(xs::value + ...)>;
  };


  template<>
  struct val_not<identity>
  {
    template<class x>
    using f = val<(!x::value)>;
  };


  template<>
  struct val_equal<identity>
  {
    template<class x, class y>
    using f = val<(x::value == y::value)>;
  };

  template<>
  struct val_not_equal<identity>
  {
    template<class x, class y>
    using f = val<(x::value != y::value)>;
  };

  template<>
  struct val_less<identity>
  {
    template<class x, class y>
    using f = val<(x::value < y::value)>;
  };

  template<>
  struct val_less_equal<identity>
  {
    template<class x, class y>
    using f = val<(x::value <= y::value)>;
  };

  template<>
  struct val_greater<identity>
  {
    template<class x, class y>
    using f = val<(x::value > y::value)>;
  };

  template<>
  struct val_greater_equal<identity>
  {
    template<class x, class y>
    using f = val<(x::value >= y::value)>;
  };
}
/// \endcond
/// \cond
namespace jln::mp::detail
{
  template<template<class...> class Tpl, class C, int i = 0>
  using smp_opv_default = contract<
    if_<
      size<>,
      try_<Tpl<assume_unary<C>>>,
      always<val<i>, assume_unary<C>>
    >
  >;

// x/0 is not a substitution failure
#if JLN_MP_MSVC
  template<template<class...> class Tpl, class C, int i = 0>
  using smp_opv_without_zero = contract<
    if_<
      size<>,
      if_<
        pop_front<and_<>>,
        try_<Tpl<assume_unary<C>>>,
        violation
      >,
      always<val<i>, assume_unary<C>>
    >
  >;

  template<class C>
  using smp_opv_without_zero_and_with_value = contract<
    if_<
      size<>,
      if_<
        pop_front<and_<>>,
        try_<C>,
        violation
      >,
      violation
    >
  >;
# define JLN_smp_opv_without_zero detail::smp_opv_without_zero
# define JLN_smp_opv_without_zero_and_with_value detail::smp_opv_without_zero_and_with_value
#else
# define JLN_smp_opv_without_zero detail::smp_opv_default
# define JLN_smp_opv_without_zero_and_with_value try_contract
#endif
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = identity>
  using val_or = try_contract<mp::val_or<assume_unary<C>>>;

  template<class C = identity>
  using val_and = try_contract<mp::val_and<assume_unary<C>>>;

  template<class C = identity>
  using val_left_or = try_contract<mp::val_left_or<assume_unary<C>>>;

  template<class C = identity>
  using val_left_and = try_contract<mp::val_left_and<assume_unary<C>>>;

  template<class C = identity>
  using val_add = try_contract<mp::val_add<assume_unary<C>>>;

  template<class C = identity>
  using val_add0 = detail::smp_opv_default<mp::val_add, C>;

  template<class C = identity>
  using val_left_add = try_contract<mp::val_left_add<assume_unary<C>>>;

  template<class C = identity>
  using val_left_add0 = detail::smp_opv_default<mp::val_left_add, C>;

  template<class C = identity>
  using val_sub = try_contract<mp::val_sub<assume_unary<C>>>;

  template<class C = identity>
  using val_sub0 = detail::smp_opv_default<mp::val_sub, C>;

  template<class C = identity>
  using val_lshift = try_contract<mp::val_lshift<assume_unary<C>>>;

  template<class C = identity>
  using val_lshift0 = detail::smp_opv_default<mp::val_lshift, C>;

  template<class C = identity>
  using val_rshift = try_contract<mp::val_rshift<assume_unary<C>>>;

  template<class C = identity>
  using val_rshift0 = detail::smp_opv_default<mp::val_rshift, C>;

  template<class C = identity>
  using val_mul = try_contract<mp::val_mul<assume_unary<C>>>;

  template<class C = identity>
  using val_mul0 = detail::smp_opv_default<mp::val_mul, C>;

  template<class C = identity>
  using val_mul1 = detail::smp_opv_default<mp::val_mul, C, 1>;

  template<class C = identity>
  using val_left_mul = try_contract<mp::val_left_mul<assume_unary<C>>>;

  template<class C = identity>
  using val_left_mul0 = detail::smp_opv_default<mp::val_left_mul, C>;

  template<class C = identity>
  using val_left_mul1 = detail::smp_opv_default<mp::val_left_mul, C, 1>;

  template<class C = identity>
  using val_div = JLN_smp_opv_without_zero_and_with_value<mp::val_div<assume_unary<C>>>;

  template<class C = identity>
  using val_div0 = JLN_smp_opv_without_zero<mp::val_div, C>;

  template<class C = identity>
  using val_div1 = JLN_smp_opv_without_zero<mp::val_div, C, 1>;

  template<class C = identity>
  using val_mod = JLN_smp_opv_without_zero_and_with_value<mp::val_mod<assume_unary<C>>>;

  template<class C = identity>
  using val_mod0 = JLN_smp_opv_without_zero<mp::val_mod, C>;

  template<class C = identity>
  using val_mod1 = JLN_smp_opv_without_zero<mp::val_mod, C, 1>;

  template<class C = identity>
  using val_xor = try_contract<mp::val_xor<assume_unary<C>>>;

  template<class C = identity>
  using val_xor0 = detail::smp_opv_default<mp::val_xor, C>;

  template<class C = identity>
  using val_left_xor = try_contract<mp::val_left_xor<assume_unary<C>>>;

  template<class C = identity>
  using val_left_xor0 = detail::smp_opv_default<mp::val_left_xor, C>;

  template<class C = identity>
  using val_bit_and = try_contract<mp::val_bit_and<assume_unary<C>>>;

  template<class C = identity>
  using val_bit_and0 = detail::smp_opv_default<mp::val_bit_and, C>;

  template<class C = identity>
  using val_left_bit_and = try_contract<mp::val_left_bit_and<assume_unary<C>>>;

  template<class C = identity>
  using val_left_bit_and0 = detail::smp_opv_default<mp::val_left_bit_and, C>;

  template<class C = identity>
  using val_bit_or = try_contract<mp::val_bit_or<assume_unary<C>>>;

  template<class C = identity>
  using val_bit_or0 = detail::smp_opv_default<mp::val_bit_or, C>;

  template<class C = identity>
  using val_left_bit_or = try_contract<mp::val_left_bit_or<assume_unary<C>>>;

  template<class C = identity>
  using val_left_bit_or0 = detail::smp_opv_default<mp::val_left_bit_or, C>;

  template<class C = identity>
  using val_neg = try_contract<mp::val_neg<assume_unary<C>>>;

  template<class C = identity>
  using val_unary_plus = try_contract<mp::val_unary_plus<assume_unary<C>>>;

  template<class C = identity>
  using val_not = try_contract<mp::val_not<assume_unary<C>>>;

  template<class C = identity>
  using val_bit_not = try_contract<mp::val_bit_not<assume_unary<C>>>;

  template<class C = identity>
  using val_inc = try_contract<mp::val_inc<assume_unary<C>>>;

  template<class C = identity>
  using val_dec = try_contract<mp::val_dec<assume_unary<C>>>;

  template<class C = identity>
  using val_equal = try_contract<mp::val_equal<assume_unary<C>>>;

  template<class C = identity>
  using val_not_equal = try_contract<mp::val_not_equal<assume_unary<C>>>;

  template<class C = identity>
  using val_less = try_contract<mp::val_less<assume_unary<C>>>;

  template<class C = identity>
  using val_less_equal = try_contract<mp::val_less_equal<assume_unary<C>>>;

  template<class C = identity>
  using val_greater = try_contract<mp::val_greater<assume_unary<C>>>;

  template<class C = identity>
  using val_greater_equal = try_contract<mp::val_greater_equal<assume_unary<C>>>;

  template<class x, class C = identity>
  using val_equal_to = contract<
    mp::push_back<x,
      mp::try_<mp::val_equal<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using val_not_equal_to = contract<
    mp::push_back<x,
      mp::try_<mp::val_not_equal<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using val_less_than = contract<
    mp::push_back<x,
      mp::try_<mp::val_less<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using val_less_equal_than = contract<
    mp::push_back<x,
      mp::try_<mp::val_less_equal<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using val_greater_than = contract<
    mp::push_back<x,
      mp::try_<mp::val_greater<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using val_greater_equal_than = contract<
    mp::push_back<x,
      mp::try_<mp::val_greater_equal<assume_unary<C>>>>>;

  template<auto x, class C = identity>
  using val_equal_to_c = val_equal_to<val<x>, C>;

  template<auto x, class C = identity>
  using val_not_equal_to_c = val_not_equal_to<val<x>, C>;

  template<auto x, class C = identity>
  using val_less_than_c = val_less_than<val<x>, C>;

  template<auto x, class C = identity>
  using val_less_equal_than_c = val_less_equal_than<val<x>, C>;

  template<auto x, class C = identity>
  using val_greater_than_c = val_greater_than<val<x>, C>;

  template<auto x, class C = identity>
  using val_greater_equal_than_c = val_greater_equal_than<val<x>, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_or<C>>
  {
    using type = smp::val_or<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_and<C>>
  {
    using type = smp::val_and<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_left_or<C>>
  {
    using type = smp::val_left_or<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_left_and<C>>
  {
    using type = smp::val_left_and<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_add<C>>
  {
    using type = smp::val_add<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_left_add<C>>
  {
    using type = smp::val_left_add<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_sub<C>>
  {
    using type = smp::val_sub<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_lshift<C>>
  {
    using type = smp::val_lshift<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_rshift<C>>
  {
    using type = smp::val_rshift<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_mul<C>>
  {
    using type = smp::val_mul<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_left_mul<C>>
  {
    using type = smp::val_left_mul<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_div<C>>
  {
    using type = smp::val_div<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_mod<C>>
  {
    using type = smp::val_mod<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_xor<C>>
  {
    using type = smp::val_xor<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_left_xor<C>>
  {
    using type = smp::val_left_xor<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_bit_and<C>>
  {
    using type = smp::val_bit_and<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_left_bit_and<C>>
  {
    using type = smp::val_left_bit_and<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_bit_or<C>>
  {
    using type = smp::val_bit_or<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_left_bit_or<C>>
  {
    using type = smp::val_left_bit_or<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_neg<C>>
  {
    using type = smp::val_neg<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_unary_plus<C>>
  {
    using type = smp::val_unary_plus<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_not<C>>
  {
    using type = smp::val_not<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_bit_not<C>>
  {
    using type = smp::val_bit_not<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_inc<C>>
  {
    using type = smp::val_inc<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_dec<C>>
  {
    using type = smp::val_dec<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_equal<C>>
  {
    using type = smp::val_equal<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_not_equal<C>>
  {
    using type = smp::val_not_equal<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_less<C>>
  {
    using type = smp::val_less<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_less_equal<C>>
  {
    using type = smp::val_less_equal<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_greater<C>>
  {
    using type = smp::val_greater<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_greater_equal<C>>
  {
    using type = smp::val_greater_equal<sfinae<C>>;
  };
}

#undef JLN_smp_opv_without_zero
#undef JLN_smp_opv_without_zero_and_with_value
/// \endcond
#if __cplusplus >= 201703L
namespace jln::mp
{
  /// \ingroup value

  template<class C = listify>
  struct values
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, val<xs::value>...);
  };

  template<class C = listify>
  struct typed_values
  {
    template<class T, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, val<T(xs::value)>...);
  };

  namespace emp
  {
    template<auto... xs>
    using values = list<val<xs>...>;

    template<class T, T... xs>
    using typed_values = list<val<T(xs)>...>;
  }
} // namespace jln::mp
#else
namespace jln::mp
{
  template<class C>
  struct values
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, typed_val<decltype(xs::value), xs::value>...);
  };

  template<class C>
  struct typed_values
  {
    template<class T, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, typed_val<T, xs::value>...);
  };

  namespace emp
  {
    template<class T, T... xs>
    using typed_values = list<typed_val<T, xs>...>;
  }
}
#endif
namespace jln::mp::smp
{
  template<class C = listify>
  using values = try_contract<mp::values<subcontract<C>>>;

  template<class C = listify>
  using typed_values = try_contract<mp::values<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, values<C>>
  {
    using type = smp::values<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, typed_values<C>>
  {
    using type = smp::typed_values<sfinae<C>>;
  };
}
/// \endcond


#endif
