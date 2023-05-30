#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/number/number.hpp>

#include <jln/mp/detail/unpack.hpp>
#include <jln/mp/detail/is_same.hpp>
#include <jln/mp/detail/enumerate.hpp> // JLN_MP_NIL

#ifndef JLN_MP_NO_STL
# define JLN_MP_NO_STL 0
#endif

#ifndef JLN_MP_USE_OPTIONAL_BUILTIN
# define JLN_MP_USE_OPTIONAL_BUILTIN 1
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN
# define JLN_MP_HAS_OPTIONAL_BUILTIN JLN_MP_HAS_BUILTIN
#else
# define JLN_MP_HAS_OPTIONAL_BUILTIN(Name) 0
#endif

#ifndef JLN_MP_INT128_AS_INTEGRAL
# define JLN_MP_INT128_AS_INTEGRAL 0
#endif

#if JLN_MP_INT128_AS_INTEGRAL
# ifdef JLN_MP_INT128_INCLUDE
#   include JLN_MP_INT128_INCLUDE
# endif

# ifndef JLN_MP_INT128_T
#   define JLN_MP_INT128_T __int128
# endif

# ifndef JLN_MP_UINT128_T
#   define JLN_MP_UINT128_T unsigned JLN_MP_INT128_T
# endif
#endif

// TODO MSVC: #pragma warning(disable: 4180)  // qualifier applied to function type has no meaning; ignored

// TODO defined(__cpp_*) && __cpp_* >= XXX -> __cpp_* >= XXX + disable warn

// TODO mp::* use detail::*_v instead of emp::*_v

// TODO macro that forces use of std::

// TODO is_trivially_relocatable

// TODO is_complete
// template<typename T, typename = void>
// struct is_complete_type : public false_type {};
//
// template<typename T>
// struct is_complete_type<T, void_t<decltype(sizeof(T) != 0)>> : public true_type {};
//
// template<>
// struct is_complete_type<const volatile void> : public false_type {};
// template<>
// struct is_complete_type<const void> : public false_type {};
// template<>
// struct is_complete_type<volatile void> : public false_type {};
// template<>
// struct is_complete_type<void> : public false_type {};
//
// template<typename T>
// struct is_complete_type<T, enable_if_t<is_function_v<T>>> : public true_type {};


// TODO is_array_of_known_bounds = extent_v<T> != 0
// TODO is_array_of_unknown_bounds = is_array_v<T> && extent_v<T> == 0



// TODO remove
#include <type_traits>

#if ! JLN_MP_NO_STL
#  include <type_traits>

#  if defined(_GLIBCXX_RELEASE)
#    define JLN_MP_USE_LIBSTDCXX 1
#  else
#    define JLN_MP_USE_LIBSTDCXX 0
#  endif

#  if defined(_LIBCPP_VERSION)
#    define JLN_MP_USE_LIBCXX 1
#  else
#    define JLN_MP_USE_LIBCXX 0
#  endif

#  if JLN_MP_MSVC_LIKE && !JLN_MP_USE_LIBCXX
#    define JLN_MP_USE_LIBMS 1
#  else
#    define JLN_MP_USE_LIBMS 0
#  endif
#else
#  define JLN_MP_USE_LIBSTDCXX 0
#  define JLN_MP_USE_LIBCXX 0
#  define JLN_MP_USE_LIBMS 0
#endif


// note some builtin are hidden by libstdc++ with clang
// namespace xxx { using __is_signed = ...; } // __is_signed builtin is now hidden
#if defined(_GLIBCXX_RELEASE)
#  define JLN_MP_BUILTIN_HIDDEN_BY_LIBSTDCXX 1
#else
#  define JLN_MP_BUILTIN_HIDDEN_BY_LIBSTDCXX 0
#endif


namespace jln::mp::traits
{
  /// \ingroup trait

  // TODO remove duplicates in JLN_MP_MAKE_TRAIT*


#define JLN_MP_MAKE_TRAIT_FROM_F(Name, Params, Type, ...) \
  template<class C = identity>                            \
  struct Name                                             \
  {                                                       \
    template<JLN_MP_UNPACK Params>                        \
    using f = JLN_MP_CALL_TRACE(C,                        \
      std::integral_constant<Type, __VA_ARGS__>);         \
  };                                                      \
                                                          \
  namespace emp                                           \
  {                                                       \
    template<JLN_MP_UNPACK Params>                        \
    using Name##_t                                        \
      = std::integral_constant<Type, __VA_ARGS__>;        \
                                                          \
    template<JLN_MP_UNPACK Params>                        \
    JLN_MP_CONSTEXPR_VAR Type Name##_v = __VA_ARGS__;     \
                                                          \
    template<JLN_MP_UNPACK Params>                        \
    struct Name                                           \
      : std::integral_constant<Type, __VA_ARGS__> {};     \
  }                                                       \
                                                          \
  template<>                                              \
  struct Name<identity>                                   \
  {                                                       \
    template<JLN_MP_UNPACK Params>                        \
    using f = std::integral_constant<Type, __VA_ARGS__>;  \
  }


#define JLN_MP_MAKE_TRAIT_V(Name, Params, Type, ...)  \
  namespace emp                                       \
  {                                                   \
    template<JLN_MP_UNPACK Params>                    \
    JLN_MP_CONSTEXPR_VAR Type Name##_v = __VA_ARGS__; \
  }

#define JLN_MP_MAKE_TRAIT_WRAP_T(Name, Params, ...) \
  template<class C = identity>                      \
  struct Name                                       \
  {                                                 \
    template<JLN_MP_UNPACK Params>                  \
    using f = JLN_MP_CALL_TRACE(C,                  \
      typename __VA_ARGS__::type);                  \
  };                                                \
                                                    \
  namespace emp                                     \
  {                                                 \
    template<JLN_MP_UNPACK Params>                  \
    using Name##_t = typename __VA_ARGS__::type;    \
                                                    \
    template<JLN_MP_UNPACK Params>                  \
    struct Name : __VA_ARGS__ {};                   \
  }                                                 \
                                                    \
  template<>                                        \
  struct Name<identity>                             \
  {                                                 \
    template<JLN_MP_UNPACK Params>                  \
    using f = typename __VA_ARGS__::type;           \
  }

#define JLN_MP_MAKE_TRAIT_T(Name, Params, ...)   \
  template<class C = identity>                   \
  struct Name                                    \
  {                                              \
    template<JLN_MP_UNPACK Params>               \
    using f = JLN_MP_CALL_TRACE(C,               \
      typename __VA_ARGS__::type);               \
  };                                             \
                                                 \
  namespace emp                                  \
  {                                              \
    template<JLN_MP_UNPACK Params>               \
    using Name##_t = typename __VA_ARGS__::type; \
  }                                              \
                                                 \
  template<>                                     \
  struct Name<identity>                          \
  {                                              \
    template<JLN_MP_UNPACK Params>               \
    using f = typename __VA_ARGS__::type;        \
  }

#define JLN_MP_MAKE_TRAIT(Name, Params, ...)     \
  template<class C = identity>                   \
  struct Name                                    \
  {                                              \
    template<JLN_MP_UNPACK Params>               \
    using f = JLN_MP_CALL_TRACE(C, __VA_ARGS__); \
  };                                             \
                                                 \
  namespace emp                                  \
  {                                              \
    template<JLN_MP_UNPACK Params>               \
    using Name = __VA_ARGS__;                    \
  }                                              \
                                                 \
  template<>                                     \
  struct Name<identity>                          \
  {                                              \
    template<JLN_MP_UNPACK Params>               \
    using f = __VA_ARGS__;                       \
  }

#define JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, ...) \
  template<class C = identity>                      \
  struct Name                                       \
  {                                                 \
    template<JLN_MP_UNPACK Params>                  \
    using f = JLN_MP_CALL_TRACE(C, __VA_ARGS__);    \
  };                                                \
                                                    \
  template<>                                        \
  struct Name<identity>                             \
  {                                                 \
    template<JLN_MP_UNPACK Params>                  \
    using f = __VA_ARGS__;                          \
  }

// STD_SVT
//  ^ implementation
//     ^ use struct (using std::name)
//      ^ use value alias (using std::name_v)
//       ^ use type alias (using std::name_t)
// STD_SVAT
//       ^ alias for T based on V (using std::name_t = std::integral_constant<Type, std::name_v<...>)

#define JLN_MP_MAKE_TRAIT_FROM_STD_SVAT_IMPL( \
    Name, Params, ...)                        \
  namespace emp                               \
  {                                           \
    using std::Name;                          \
    using std::Name##_v;                      \
    template<JLN_MP_UNPACK Params>            \
    using Name##_t = __VA_ARGS__;             \
  }                                           \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, __VA_ARGS__)

#define JLN_MP_MAKE_TRAIT_FROM_STD_ST( \
    Name, Params, Values)              \
  namespace emp                        \
  {                                    \
    using std::Name;                   \
    using std::Name##_t;               \
  }                                    \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, std::Name##_t<JLN_MP_UNPACK Values>)

#define JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(Name, Params, Type, Values) \
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT_IMPL(                             \
    Name, Params, emp::integral_constant<Type, std::Name##_v<JLN_MP_UNPACK Values>>)

#define JLN_MP_MAKE_TRAIT_FROM_BUILTIN_T_STD_SV( \
    Name, Params, Type, ...)                     \
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT_IMPL(          \
    Name, Params, emp::integral_constant<Type, __VA_ARGS__>)

#define JLN_MP_MAKE_TRAIT_FROM_BUILTIN_VT_STD_S(      \
  Name, Params, Type, ...)                            \
  namespace emp                                       \
  {                                                   \
    using std::Name;                                  \
    template<JLN_MP_UNPACK Params>                    \
    JLN_MP_CONSTEXPR_VAR Type Name##_v = __VA_ARGS__; \
    template<JLN_MP_UNPACK Params>                    \
    using Name##_t                                    \
      = emp::integral_constant<Type, __VA_ARGS__>;    \
  }                                                   \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, emp::integral_constant<Type, __VA_ARGS__>)

#define JLN_MP_MAKE_TRAIT_IS_ST(Name, Params, Type, ...)        \
  namespace emp                                                 \
  {                                                             \
    template<JLN_MP_UNPACK Params>                              \
    struct Name : emp::integral_constant<Type, __VA_ARGS__> {}; \
    template<JLN_MP_UNPACK Params>                              \
    using Name##_t = emp::integral_constant<Type, __VA_ARGS__>; \
  }                                                             \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, emp::integral_constant<Type, __VA_ARGS__>)

#define JLN_MP_MAKE_TRAIT_FROM_EMP_V(Name, Params, Type, Values) \
  JLN_MP_MAKE_TRAIT_IS_ST(Name, Params, Type, emp::Name##_v<JLN_MP_UNPACK Values>)

#define JLN_MP_MAKE_TRAIT_IS(Name, Params, Type, ...)           \
  namespace emp                                                 \
  {                                                             \
    template<JLN_MP_UNPACK Params>                              \
    JLN_MP_CONSTEXPR_VAR Type Name##_v = __VA_ARGS__;           \
                                                                \
    template<JLN_MP_UNPACK Params>                              \
    struct Name : emp::integral_constant<Type, __VA_ARGS__> {}; \
                                                                \
    template<JLN_MP_UNPACK Params>                              \
    using Name##_t = emp::integral_constant<Type, __VA_ARGS__>; \
  }                                                             \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, emp::integral_constant<Type, __VA_ARGS__>)

#define JLN_MP_MAKE_TRAIT_FROM_BUILTIN_TS_STD_V(   \
  Name, Params, Type, ...)                         \
  namespace emp                                    \
  {                                                \
    using std::Name##_v;                           \
    template<JLN_MP_UNPACK Params>                 \
    struct Name                                    \
      : emp::integral_constant<Type, __VA_ARGS__>  \
    {};                                            \
    template<JLN_MP_UNPACK Params>                 \
    using Name##_t                                 \
      = emp::integral_constant<Type, __VA_ARGS__>; \
  }                                                \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, emp::integral_constant<Type, __VA_ARGS__>)

#define JLN_MP_MAKE_TRAIT_FROM_ST(             \
  Name, Params, ...)                           \
  namespace emp                                \
  {                                            \
    template<JLN_MP_UNPACK Params>             \
    struct Name { using type = __VA_ARGS__; }; \
    template<JLN_MP_UNPACK Params>             \
    using Name##_t = __VA_ARGS__;              \
  }                                            \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, __VA_ARGS__)


#if JLN_MP_USE_LIBMS
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_BUILTIN_T_STD_SV
#elif JLN_MP_USE_LIBCXX
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_BUILTIN_VT_STD_S
#else
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_F
#endif

#if JLN_MP_USE_LIBCXX
# define JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_BUILTIN_T_STD_SV
# define JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_BUILTIN_VT_STD_S
# define JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST JLN_MP_MAKE_TRAIT_FROM_STD_ST
#else
# define JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_F
# define JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_F
# define JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(Name, Params, Values) \
    JLN_MP_MAKE_TRAIT_FROM_ST(Name, Params, __##Name Values)
#endif

#if JLN_MP_USE_LIBCXX
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_TS_STD_V_LIBCXX_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_BUILTIN_T_STD_SV
#elif JLN_MP_USE_LIBMS
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_TS_STD_V_LIBCXX_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_BUILTIN_TS_STD_V
#else
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_TS_STD_V_LIBCXX_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_F
#endif

#if JLN_MP_USE_LIBCXX || JLN_MP_USE_LIBMS
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_BUILTIN_T_STD_SV
#else
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_F
#endif

#if JLN_MP_USE_LIBCXX || JLN_MP_USE_LIBMS
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_LIBSTDCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_BUILTIN_T_STD_SV
#elif JLN_MP_USE_LIBSTDCXX
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_LIBSTDCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_BUILTIN_VT_STD_S
#else
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_LIBSTDCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_F
#endif

#if JLN_MP_USE_LIBMS
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_BUILTIN_T_STD_SV
#else
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_FROM_F
#endif


#define JLN_MP_FN_PTR(...) static_cast<__VA_ARGS__>(nullptr)
#define JLN_MP_DECLVAL(T) static_cast<T(*)()>(nullptr)()
#define JLN_MP_DECLVAL_NOTHROW(T) static_cast<T(*)() noexcept>(nullptr)()


#ifdef __cpp_noexcept_function_type
# define JLN_MP_DEFINE_CV_REF_NOEXCEPT(F) \
    F(JLN_MP_NIL)                         \
    F(&)                                  \
    F(&&)                                 \
    F(const)                              \
    F(const&)                             \
    F(const&&)                            \
    F(volatile)                           \
    F(volatile&)                          \
    F(volatile&&)                         \
    F(volatile const)                     \
    F(volatile const&)                    \
    F(volatile const&&)                   \
    F(noexcept)                           \
    F(& noexcept)                         \
    F(&& noexcept)                        \
    F(const noexcept)                     \
    F(const& noexcept)                    \
    F(const&& noexcept)                   \
    F(volatile noexcept)                  \
    F(volatile& noexcept)                 \
    F(volatile&& noexcept)                \
    F(volatile const noexcept)            \
    F(volatile const& noexcept)           \
    F(volatile const&& noexcept)
#else // __cpp_noexcept_function_type
#define JLN_MP_DEFINE_CV_REF_NOEXCEPT(F) \
    F(JLN_MP_NIL)                        \
    F(&)                                 \
    F(&&)                                \
    F(const)                             \
    F(const&)                            \
    F(const&&)                           \
    F(volatile)                          \
    F(volatile&)                         \
    F(volatile&&)                        \
    F(volatile const)                    \
    F(volatile const&)                   \
    F(volatile const&&)
#endif // __cpp_noexcept_function_type


  namespace emp
  {
    using nullptr_t = decltype(nullptr);

#if JLN_MP_NO_STL
    template<class...>
    using void_t = void;

    template<bool B, class T = void>
    struct enable_if
    {};

    template<class T>
    struct enable_if<true, T>
    {
      using type = T;
    };

    template<bool B, class T = void>
    using enable_if_t = typename std::enable_if<B, T>::type;

    template<class T, T v>
    struct integral_constant
    {
      static constexpr T value = v;
      using value_type = T;
      using type = integral_constant;
      constexpr operator value_type() const noexcept { return value; }
      constexpr value_type operator()() const noexcept { return value; }
    };

    using true_type = integral_constant<bool, true>;
    using false_type = integral_constant<bool, false>;
#else
    using std::void_t;
    using std::enable_if;
    using std::integral_constant;
    using std::true_type;
    using std::false_type;
    using std::enable_if_t;
#endif

#if JLN_MP_NO_STL || !defined(__cpp_lib_type_identity) || __cpp_lib_type_identity < 201806L
    template<class T>
    struct type_identity
    {
        using type = T;
    };

    template<class T>
    using type_identity_t = typename type_identity<T>::type;
#else
    using std::type_identity;
    using std::type_identity_t;
#endif
  }


  // https://en.cppreference.com/w/cpp/feature_test

#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_const)
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(is_const, (class T), bool, __is_const(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_const, (class T), bool, (T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_const_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_const_v<T const> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_const, (class T), bool, (T));
#endif
#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_const)
# define JLN_MP_IS_CONST_V(...) __is_const(__VA_ARGS__)
#else
# define JLN_MP_IS_CONST_V(...) emp::is_const_v<__VA_ARGS__>
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_volatile)
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(is_volatile, (class T), bool, __is_volatile(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_volatile, (class T), bool, (T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_volatile_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_volatile_v<T volatile> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_volatile, (class T), bool, (T));
#endif


#if JLN_MP_MSVC >= 2000 || JLN_MP_HAS_BUILTIN(__is_trivial)
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_trivial, (class T), bool, __is_trivial(T));
#elif JLN_MP_MSVC || (JLN_MP_HAS_BUILTIN(__is_trivially_constructible) && JLN_MP_HAS_BUILTIN(__is_trivially_copyable))
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    is_trivial, (class T), bool, __is_trivially_constructible(T) && __is_trivially_copyable(T));
#elif ! JLN_MP_NO_STL
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_trivial, (class T), bool, (T))
#endif


  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(is_trivially_copyable, (class T), bool, __is_trivially_copyable(T));


#if JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_standard_layout)
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_standard_layout, (class T), bool, __is_standard_layout(T));
#else
  // TODO is_complete_or_unbounded
  // this implementation is not compliant
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_standard_layout_v
      = JLN_MP_IS_SCALAR_V(typename remove_all_extents<T>::type>);
  }
#endif


#if JLN_MP_USE_LIBMS || JLN_MP_USE_LIBCXX
# define JLN_MP_MAKE_TRAIT_D(Name, Params, Values) \
    JLN_MP_MAKE_TRAIT_FROM_BUILTIN_T_STD_SV(Name, Params, bool, __##Name Values)
#elif JLN_MP_USE_LIBSTDCXX
# define JLN_MP_MAKE_TRAIT_D(Name, Params, Values) \
    JLN_MP_MAKE_TRAIT_FROM_BUILTIN_VT_STD_S(Name, Params, bool, __##Name Values)
#else
# define JLN_MP_MAKE_TRAIT_D(Name, Params, Values) \
    JLN_MP_MAKE_TRAIT_FROM_F(Name, Params, bool, __##Name Values)
#endif

#if __cplusplus <= 201703L
  JLN_MP_MAKE_TRAIT_D(is_pod, (class T), (T));
#endif
  JLN_MP_MAKE_TRAIT_D(is_empty, (class T), (T));
  JLN_MP_MAKE_TRAIT_D(is_polymorphic, (class T), (T));
  JLN_MP_MAKE_TRAIT_D(is_abstract, (class T), (T));
  JLN_MP_MAKE_TRAIT_D(is_final, (class T), (T));
  JLN_MP_MAKE_TRAIT_D(is_aggregate, (class T), (T));
  JLN_MP_MAKE_TRAIT_D(is_enum, (class T), (T));
  JLN_MP_MAKE_TRAIT_D(is_union, (class T), (T));
  JLN_MP_MAKE_TRAIT_D(is_class, (class T), (T));
  JLN_MP_MAKE_TRAIT_D(is_base_of, (class T, class U), (T, U));

#undef JLN_MP_MAKE_TRAIT_D


#if ! JLN_MP_BUILTIN_HIDDEN_BY_LIBSTDCXX && JLN_MP_HAS_OPTIONAL_BUILTIN(__is_signed) && (!JLN_MP_INT128_AS_INTEGRAL || JLN_MP_CLANG_LIKE)
  JLN_MP_MAKE_TRAIT_FROM_BUILTIN_T_STD_SV(is_signed, (class T), bool, __is_signed(T));
#else
  namespace detail
  {
# if ! JLN_MP_BUILTIN_HIDDEN_BY_LIBSTDCXX && JLN_MP_HAS_OPTIONAL_BUILTIN(__is_signed)
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v = __is_signed(T);
# else
    JLN_MP_DIAGNOSTIC_PUSH()
    JLN_MP_DIAGNOSTIC_MSVC_IGNORE(4296) // '<': expression is always false
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v<volatile const char> = char(-1) < char(0);
    template<> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v<volatile const signed char> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v<volatile const wchar_t> = wchar_t(-1) < wchar_t(0);
    template<> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v<volatile const short> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v<volatile const int> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v<volatile const long> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v<volatile const long long> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v<volatile const float> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v<volatile const double> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v<volatile const long double> = true;
    // TODO __uint128_t, __int128_t
    JLN_MP_DIAGNOSTIC_POP()
# endif // __is_signed

# if JLN_MP_INT128_AS_INTEGRAL
    template<> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v<volatile const JLN_MP_INT128_T> = true;
# endif
  }
  JLN_MP_MAKE_TRAIT_IS(is_signed, (class T), bool, detail::is_signed_impl_v<T volatile const>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_unsigned) && (!JLN_MP_INT128_AS_INTEGRAL || JLN_MP_CLANG_LIKE)
  JLN_MP_MAKE_TRAIT_FROM_BUILTIN_T_STD_SV(is_unsigned, (class T), bool, __is_unsigned(T));
#else
  namespace detail
  {
# if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_unsigned)
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_unsigned_impl_v = __is_unsigned(T);
# else
    JLN_MP_DIAGNOSTIC_PUSH()
    JLN_MP_DIAGNOSTIC_MSVC_IGNORE(4296) // '<': expression is always false
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_unsigned_impl_v = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_unsigned_impl_v<volatile const bool> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_unsigned_impl_v<volatile const char> = char(0) < char(-1);
    template<> JLN_MP_CONSTEXPR_VAR bool is_unsigned_impl_v<volatile const unsigned char> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_unsigned_impl_v<volatile const wchar_t> = wchar_t(0) < wchar_t(-1);
#ifdef __cpp_char8_t
    template<> JLN_MP_CONSTEXPR_VAR bool is_unsigned_impl_v<volatile const char8_t> = true;
#endif
    template<> JLN_MP_CONSTEXPR_VAR bool is_unsigned_impl_v<volatile const char16_t> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_unsigned_impl_v<volatile const char32_t> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_unsigned_impl_v<volatile const unsigned short> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_unsigned_impl_v<volatile const unsigned int> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_unsigned_impl_v<volatile const unsigned long> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_unsigned_impl_v<volatile const unsigned long long> = true;
    JLN_MP_DIAGNOSTIC_POP()
# endif // __is_unsigned

# if JLN_MP_INT128_AS_INTEGRAL
    template<> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v<volatile const JLN_MP_UINT128_T> = true;
# endif
  }
  JLN_MP_MAKE_TRAIT_IS(is_unsigned, (class T), bool, detail::is_unsigned_impl_v<T volatile const>);
#endif


#if JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_bounded_array, (class T), bool, (T));
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_unbounded_array, (class T), bool, (T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_bounded_array_v = false;
    template<class T, std::size_t N> JLN_MP_CONSTEXPR_VAR bool is_bounded_array_v<T[N]> = true;

    template<class T> JLN_MP_CONSTEXPR_VAR bool is_unbounded_array_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_unbounded_array_v<T[]> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_bounded_array, (class T), bool, (T));
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_unbounded_array, (class T), bool, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_convertible_to)
  #define JLN_MP_IS_CONVERTIBLE_V(...) __is_convertible_to(__VA_ARGS__)
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_convertible, (class From, class To), bool, __is_convertible_to(From, To));
#elif JLN_MP_FEATURE_CONCEPTS
  #define JLN_MP_IS_CONVERTIBLE_V(...) emp::is_convertible_v<__VA_ARGS__>
  namespace emp
  {
    template<class From, class To>
    JLN_MP_CONSTEXPR_VAR bool is_convertible_v
      = requires{ JLN_MP_FN_PTR(void(*)(From))(JLN_MP_DECLVAL(To&&)); };
  }
  // TODO void -> void = ok
  // TODO JLN_MP_DECLVAL(PtrFunc&&) -> error
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_convertible);
#else
  #define JLN_MP_IS_CONVERTIBLE_V(...) detail::is_convertible_impl_v<__VA_ARGS__>
  namespace detail
  {
    template<class From, class To, class = void>
    JLN_MP_CONSTEXPR_VAR bool is_convertible_impl_v = false;

    // TODO void -> void = ok
    // TODO JLN_MP_DECLVAL(PtrFunc&&) -> error
    // TODO is_complete_or_unbounded
    template<class From, class To>
    JLN_MP_CONSTEXPR_VAR bool is_convertible_impl_v<
      From, To, decltype(JLN_MP_FN_PTR(void(*)(From))(JLN_MP_DECLVAL(To)))> = true;
  }
  JLN_MP_MAKE_TRAIT_IS(is_convertible, (class From, class To), bool,
    detail::is_convertible_impl_v<From, To>);
#endif


#if defined(__cpp_lib_is_nothrow_convertible) && __cpp_lib_is_nothrow_convertible >= 201806L
  // TODO
  // JLN_MP_MAKE_TRAIT_P2(JLN_MP_TRAIT_BUILTIN_IS(is_nothrow_convertible, CLANG, 0, 0));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_scoped_enum)
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_scoped_enum, (class T), bool, __is_scoped_enum(T));
#else
  // TODO or *_FROM_EMP_V
  JLN_MP_MAKE_TRAIT_IS(is_scoped_enum, (class T), bool,
      // TODO requires { int(*static_cast<T*>(nullptr)); }
    __is_enum(T) && !JLN_MP_IS_CONVERTIBLE_V(T, int));
#endif


  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    has_unique_object_representations, (class T), bool, __has_unique_object_representations(T));


#if ! JLN_MP_BUILTIN_HIDDEN_BY_LIBSTDCXX && JLN_MP_HAS_OPTIONAL_BUILTIN(__is_void)
  #define JLN_MP_IS_VOID_V(...) __is_void(__VA_ARGS__)
  JLN_MP_MAKE_TRAIT_FROM_BUILTIN_T_STD_SV(is_void, (class T), bool, __is_void(T));
#elif JLN_MP_HAS_OPTIONAL_BUILTIN(__is_same)
  #define JLN_MP_IS_VOID_V(...) \
    __is_same(volatile const __VA_ARGS__, volatile const void)
  JLN_MP_MAKE_TRAIT_FROM_F(is_void, (class T), bool, JLN_MP_IS_VOID_V(T));
#else
  #define JLN_MP_IS_VOID_V(...) emp::is_void_v<__VA_ARGS__>
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_void_v = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_void_v<void> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_void_v<void const> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_void_v<void volatile> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_void_v<void volatile const> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_void, (class T), bool, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_same)
  #define JLN_MP_IS_NULL_POINTER_V(...) \
    __is_same(__VA_ARGS__ volatile const, decltype(nullptr) volatile const)
  JLN_MP_MAKE_TRAIT_FROM_F(is_null_pointer, (class T), bool, JLN_MP_IS_NULL_POINTER_V(T));
#else
  #define JLN_MP_IS_NULL_POINTER_V(...) emp::is_null_pointer_v<__VA_ARGS__>
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_null_pointer_v = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_null_pointer_v<decltype(nullptr)> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_null_pointer_v<decltype(nullptr) const> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_null_pointer_v<decltype(nullptr) volatile> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_null_pointer_v<decltype(nullptr) volatile const> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_null_pointer, (class T), bool, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_integral) && (!JLN_MP_INT128_AS_INTEGRAL || JLN_MP_CLANG_LIKE)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_integral, (class T), bool, __is_integral(T));
#else
  namespace detail
  {
# if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_integral)
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v = __is_integral(T);
# else
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const bool> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const char> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const signed char> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const unsigned char> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const wchar_t> = true;
#ifdef __cpp_char8_t
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const char8_t> = true;
#endif
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const char16_t> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const char32_t> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const   signed short> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const unsigned short> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const   signed int> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const unsigned int> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const   signed long> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const unsigned long> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const   signed long long> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const unsigned long long> = true;
# endif // __is_integral

# if JLN_MP_INT128_AS_INTEGRAL
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const JLN_MP_INT128_T> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const JLN_MP_UINT128_T> = true;
# endif
  }
  JLN_MP_MAKE_TRAIT_IS(is_integral, (class T), bool, detail::is_integral_impl_v<T volatile const>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_floating_point)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_floating_point, (class T), bool, __is_floating_point(T));
#else
  namespace detail
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_floating_point_impl_v = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_floating_point_impl_v<volatile const float> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_floating_point_impl_v<volatile const double> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_floating_point_impl_v<volatile const long double> = true;
  }
  JLN_MP_MAKE_TRAIT_IS(is_floating_point, (class T), bool, detail::is_floating_point_impl_v<T volatile const>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_array)
  #define JLN_MP_IS_ARRAY_V(...) __is_array(__VA_ARGS__)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_array, (class T), bool, __is_array(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_array, (class T), bool, (T));
#else
  #define JLN_MP_IS_ARRAY_V(...) /*emp::*/is_array_v<__VA_ARGS__>
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_array_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_array_v<T[]> = true;
    template<class T, std::size_t N> JLN_MP_CONSTEXPR_VAR bool is_array_v<T[N]> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_array, (class T), bool, (T));
#endif


#if ! JLN_MP_BUILTIN_HIDDEN_BY_LIBSTDCXX && JLN_MP_HAS_OPTIONAL_BUILTIN(__is_pointer)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_pointer, (class T), bool, __is_pointer(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_pointer, (class T), bool, (T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_pointer_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_pointer_v<T*> = true;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_pointer_v<T* const> = true;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_pointer_v<T* volatile> = true;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_pointer_v<T* volatile const> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_pointer, (class T), bool, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_lvalue_reference)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_lvalue_reference, (class T), bool, __is_lvalue_reference(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_lvalue_reference, (class T), bool, (T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_lvalue_reference_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_lvalue_reference_v<T&> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_lvalue_reference, (class T), bool, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_rvalue_reference)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_rvalue_reference, (class T), bool, __is_rvalue_reference(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_rvalue_reference, (class T), bool, (T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_rvalue_reference_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_rvalue_reference_v<T&&> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_rvalue_reference, (class T), bool, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_reference)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_reference, (class T), bool, __is_reference(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_reference, (class T), bool, (T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_reference_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_reference_v<T&> = true;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_reference_v<T&&> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_reference, (class T), bool, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_function)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_function, (class T), bool, __is_function(T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_function_v = !JLN_MP_IS_CONST_V(T const);
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_function_v<T&> = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_function_v<T&&> = false;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_function, (class T), bool, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_member_object_pointer)
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_TS_STD_V_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_member_object_pointer, (class T), bool, __is_member_object_pointer(T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_member_object_pointer_v = false;

    template<class T, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_object_pointer_v<T C::*> = !is_function_v<T>;

    template<class T, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_object_pointer_v<T C::* const> = !is_function_v<T>;

    template<class T, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_object_pointer_v<T C::* volatile> = !is_function_v<T>;

    template<class T, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_object_pointer_v<T C::* volatile const> = !is_function_v<T>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_member_object_pointer, (class T), bool, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_member_function_pointer)
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_member_function_pointer, (class T), bool, __is_member_function_pointer(T));
#else
  namespace emp
  {
    // TODO msvc call spec and gcc
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_member_function_pointer_v = false;

    template<class T, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_function_pointer_v<T C::*> = is_function_v<T>;

    template<class T, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_function_pointer_v<T C::* const> = is_function_v<T>;

    template<class T, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_function_pointer_v<T C::* volatile> = is_function_v<T>;

    template<class T, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_function_pointer_v<T C::* volatile const> = is_function_v<T>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_member_function_pointer, (class T), bool, (T));
#endif


#if ! JLN_MP_BUILTIN_HIDDEN_BY_LIBSTDCXX && JLN_MP_HAS_OPTIONAL_BUILTIN(__is_arithmetic)
  JLN_MP_MAKE_TRAIT_FROM_F(is_arithmetic, (class T), bool, __is_arithmetic(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_arithmetic, (class T), bool, (T));
#else
  // TODO or *_FROM_EMP_V
  JLN_MP_MAKE_TRAIT_IS(is_arithmetic, (class T), bool,
    emp::is_integral_v<T> || emp::is_floating_point_v<T>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_fundamental)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_fundamental, (class T), bool, __is_fundamental(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_fundamental, (class T), bool, (T));
#else
  // TODO or *_FROM_EMP_V
  JLN_MP_MAKE_TRAIT_IS(is_fundamental, (class T), bool,
    emp::is_arithmetic_v<T> || JLN_MP_IS_VOID_V(T) || JLN_MP_IS_NULL_POINTER_V(T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_object)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_object, (class T), bool, __is_object(T));
#else
  // TODO or *_FROM_EMP_V
  JLN_MP_MAKE_TRAIT_IS(is_object, (class T), bool,
    JLN_MP_IS_CONST_V(T const) && !JLN_MP_IS_VOID_V(T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_member_pointer)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_member_pointer, (class T), bool, __is_member_pointer(T));
#else
  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_member_pointer_v = false;

    template<class T, class C>
    JLN_MP_CONSTEXPR_VAR bool is_member_pointer_v<T C::*> = true;

    template<class T, class C>
    JLN_MP_CONSTEXPR_VAR bool is_member_pointer_v<T C::* const> = true;

    template<class T, class C>
    JLN_MP_CONSTEXPR_VAR bool is_member_pointer_v<T C::* volatile> = true;

    template<class T, class C>
    JLN_MP_CONSTEXPR_VAR bool is_member_pointer_v<T C::* volatile const> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_member_pointer, (class T), bool, (T));
#endif


#if ! JLN_MP_BUILTIN_HIDDEN_BY_LIBSTDCXX && JLN_MP_HAS_OPTIONAL_BUILTIN(__is_scalar)
  #define JLN_MP_IS_SCALAR_V(...) __is_scalar(__VA_ARGS__)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_scalar, (class T), bool, __is_scalar(T));
#else
  #define JLN_MP_IS_SCALAR_V(...) /*emp::*/is_scalar_v<__VA_ARGS__>
  // TODO or *_FROM_EMP_V
  JLN_MP_MAKE_TRAIT_IS(is_scalar, (class T), bool,
    emp::is_arithmetic_v<T> || __is_enum(T) || emp::is_pointer_v<T>
    || emp::is_member_pointer_v<T> || JLN_MP_IS_NULL_POINTER_V(T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_compound)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_compound, (class T), bool, __is_compound(T));
#else
  JLN_MP_MAKE_TRAIT_IS(is_compound, (class T), bool, !emp::is_fundamental_v<T>);
#endif


  namespace detail
  {
    // TODO requires { ... } ?
    template<class T, class = void>
    static constexpr bool is_referenceable_impl_v = false;

    template<class T>
    static constexpr bool is_referenceable_impl_v<T, emp::void_t<T&>> = true;
  }
  JLN_MP_MAKE_TRAIT_IS(is_referenceable, (class T), bool,
    detail::is_referenceable_impl_v<T volatile const>);


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__add_lvalue_reference)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(add_lvalue_reference, (class T), (T));
#else
  namespace detail
  {
    template<class T, bool = is_referenceable_impl_v<T volatile const>>
    struct add_lvalue_reference_impl { using type = T; };

    template<class T>
    struct add_lvalue_reference_impl<T, true> { using type = T&; };
  }
  JLN_MP_MAKE_TRAIT_WRAP_T(add_lvalue_reference, (class T), detail::add_lvalue_reference_impl<T>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__add_rvalue_reference)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(add_rvalue_reference, (class T), (T));
#else
  namespace detail
  {
    template<class T, bool = is_referenceable_impl_v<T volatile const>>
    struct add_rvalue_reference_impl { using type = T; };

    template<class T>
    struct add_rvalue_reference_impl<T, true> { using type = T&&; };
  }
  JLN_MP_MAKE_TRAIT_WRAP_T(add_rvalue_reference, (class T), detail::add_rvalue_reference_impl<T>);
#endif


  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_constructible, (class T, class... Args), bool, __is_constructible(T, Args...));


  // TODO is_complete_or_unbounded
#if JLN_MP_FEATURE_CONCEPTS
  // T() does not work with when T = U[n]
  JLN_MP_MAKE_TRAIT_FROM_F(is_default_constructible, (class T), bool, requires { T{}; });
#else
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    is_default_constructible, (class T), bool, __is_constructible(T));
#endif

  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    is_copy_constructible, (class T), bool, __is_constructible(T, emp::add_lvalue_reference_t<T const>));

  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    is_move_constructible, (class T), bool,
      __is_constructible(T, T /*emp::add_rvalue_reference_t<T>*/));


  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_trivially_constructible, (class T, class... Args), bool,
      __is_trivially_constructible(T, Args...));

  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_trivially_default_constructible, (class T), bool, __is_trivially_constructible(T));

  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    is_trivially_copy_constructible, (class T), bool,
      __is_trivially_constructible(T, emp::add_lvalue_reference_t<T const>));

  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    is_trivially_move_constructible, (class T), bool,
      __is_trivially_constructible(T, T /*emp::add_rvalue_reference_t<T>*/));


  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_nothrow_constructible, (class T, class... Args), bool, __is_nothrow_constructible(T, Args...));

  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_nothrow_default_constructible, (class T), bool, __is_nothrow_constructible(T));

  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    is_nothrow_copy_constructible, (class T), bool,
      __is_nothrow_constructible(T, emp::add_lvalue_reference_t<T const>));

  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    is_nothrow_move_constructible, (class T), bool,
      __is_nothrow_constructible(T, T /*emp::add_rvalue_reference_t<T>*/));


#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_assignable))
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_assignable, (class T, class U), bool, __is_assignable(T, U));

  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    is_copy_assignable, (class T), bool,
      __is_assignable(emp::add_lvalue_reference_t<T>, emp::add_lvalue_reference_t<T const>));

  #define JLN_MP_IS_MOVE_ASSIGNABLE_V(...) \
    __is_assignable(emp::add_lvalue_reference_t<__VA_ARGS__>, __VA_ARGS__)

  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    is_move_assignable, (class T), bool, JLN_MP_IS_MOVE_ASSIGNABLE_V(T));
#else
# if JLN_MP_FEATURE_CONCEPTS
  #define JLN_MP_IS_ASSIGNABLE_V(T, U) \
    requires { JLN_MP_DECLVAL(T&&) = JLN_MP_DECLVAL(U&&); }

  #define JLN_MP_IS_COPY_ASSIGNABLE_V(...) \
    requires { JLN_MP_DECLVAL(__VA_ARGS__&) = JLN_MP_DECLVAL(__VA_ARGS__&&); }

  #define JLN_MP_IS_MOVE_ASSIGNABLE_V(...) \
    requires { JLN_MP_DECLVAL(__VA_ARGS__&) = JLN_MP_DECLVAL(__VA_ARGS__ const&); }
# else
  namespace detail
  {
    template<class T, class U, class = void>
    JLN_MP_CONSTEXPR_VAR bool is_assignable_impl_v = false;

    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool is_assignable_impl_v<
      T, U, decltype(void(JLN_MP_DECLVAL(T&&) = JLN_MP_DECLVAL(U&&)))
    > = true;
  }
  #define JLN_MP_IS_ASSIGNABLE_V(...) detail::is_assignable_impl_v<__VA_ARGS__>

  #define JLN_MP_IS_COPY_ASSIGNABLE_V(...)                                 \
    detail::is_assignable_impl_v<emp::add_lvalue_reference_t<__VA_ARGS__>, \
                                  emp::add_lvalue_reference_t<__VA_ARGS__ const>>

  #define JLN_MP_IS_MOVE_ASSIGNABLE_V(...) \
    detail::is_assignable_impl_v<emp::add_lvalue_reference_t<__VA_ARGS__>, __VA_ARGS__>
# endif
  // TODO or *_FROM_EMP_V xxxxxx

  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_IS(is_assignable, (class T, class U), bool, JLN_MP_IS_ASSIGNABLE_V(T, U));
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_IS(is_copy_assignable, (class T), bool, JLN_MP_IS_COPY_ASSIGNABLE_V(T));
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_IS(is_move_assignable, (class T), bool, JLN_MP_IS_MOVE_ASSIGNABLE_V(T));
#endif


  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_trivially_assignable, (class T, class U), bool, __is_trivially_assignable(T, U));

  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    is_trivially_copy_assignable, (class T), bool,
      __is_trivially_assignable(emp::add_lvalue_reference_t<T>, emp::add_lvalue_reference_t<T const>));

  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    is_trivially_move_assignable, (class T), bool,
      __is_trivially_assignable(emp::add_lvalue_reference_t<T>, T /*emp::add_rvalue_reference_t<T>*/));


#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_nothrow_assignable))
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_nothrow_assignable, (class T, class U), bool, __is_nothrow_assignable(T, U));

  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    is_nothrow_copy_assignable, (class T), bool,
      __is_nothrow_assignable(emp::add_lvalue_reference_t<T>, emp::add_lvalue_reference_t<T const>));

  #define JLN_MP_IS_NOTHROW_MOVE_ASSIGNABLE_V(...) \
    __is_nothrow_assignable(emp::add_lvalue_reference_t<__VA_ARGS__>, __VA_ARGS__)

  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    is_nothrow_move_assignable, (class T), bool, JLN_MP_IS_NOTHROW_MOVE_ASSIGNABLE_V(T));
#else
  namespace detail
  {
    template<class T, class U, bool = true>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_assignable_impl_v = false;

    // TODO add_rvalue_reference from caller ?
    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_assignable_impl_v<
      T, U, noexcept(JLN_MP_DECLVAL_NOTHROW(T&&) = JLN_MP_DECLVAL_NOTHROW(U&&))
    > = true;
  }
  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_copy_assignable_v
      = detail::is_nothrow_assignable_impl_v<
          add_lvalue_reference_t<T>, add_lvalue_reference_t<T const>>;

    // TODO use emp version ?
    #define JLN_MP_IS_NOTHROW_MOVE_ASSIGNABLE_V(...) \
      detail::is_nothrow_assignable_impl_v<emp::add_lvalue_reference_t<__VA_ARGS__>, __VA_ARGS__>

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_move_assignable_v
      = JLN_MP_IS_NOTHROW_MOVE_ASSIGNABLE_V(T);
  }
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_IS(is_nothrow_assignable, (class T, class U), bool,
    detail::is_nothrow_assignable_impl_v<T, U>);
  // TODO is_complete_or_unbounded
  // TODO use JLN_MP_MAKE_TRAIT_IS ?
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_nothrow_copy_assignable, (class T), bool, (T));
  // TODO is_complete_or_unbounded
  // TODO use JLN_MP_MAKE_TRAIT_IS ?
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_nothrow_move_assignable, (class T), bool, (T));
#endif


#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_destructible))
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_destructible, (class T), bool, __is_destructible(T));
#else
  namespace detail
  {
#if JLN_MP_FEATURE_CONCEPTS
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_destructible_impl_v = requires { JLN_MP_DECLVAL(T*)->~T(); };
#else
    template<class T, class = void>
    JLN_MP_CONSTEXPR_VAR bool is_destructible_impl_v = false;

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_destructible_impl_v<T, decltype(JLN_MP_DECLVAL(T*)->~T())> = true;
#endif

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_destructible_impl_v<T&> = true;

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_destructible_impl_v<T&&> = true;

    // TODO remove_all_extents
    template<class T, std::size_t n>
    JLN_MP_CONSTEXPR_VAR bool is_destructible_impl_v<T[n]> = is_destructible_impl_v<T>;
  }
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_IS(is_destructible, (class T), bool,
    detail::is_destructible_impl_v<T volatile const>);
#endif


#if JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_trivially_destructible)
  #define JLN_MP_IS_TRIVIALLY_DESTRUCTIBLE_V(...) __is_trivially_destructible(__VA_ARGS__)
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_trivially_destructible, (class T), bool, __is_trivially_destructible(T));
#else
# if JLN_MP_HAS_BUILTIN(__has_trivial_destructor)
  // TODO is_complete_or_unbounded
  #define JLN_MP_IS_TRIVIALLY_DESTRUCTIBLE_V(...) \
    emp::is_destructible_v<T> && __has_trivial_destructor(T)
  // TODO or *_FROM_EMP_V
  JLN_MP_MAKE_TRAIT_IS(is_trivially_destructible, (class T), bool,
    JLN_MP_IS_TRIVIALLY_DESTRUCTIBLE_V(T));
# else
  // this implementation is not compliant and fails with classes and unions
  namespace emp
  {
    // TODO is_complete_or_unbounded
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_destructible_v = is_scalar_v<T>;

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_destructible_v<T&> = true;

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_destructible_v<T&&> = true;

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_destructible_v<T[]> = false;

    // TODO remove_all_extents
    template<class T, std::size_t n>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_destructible_v<T[n]> = is_trivially_destructible_v<T>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_trivially_destructible, (class T), bool, (T));
  #define JLN_MP_IS_TRIVIALLY_DESTRUCTIBLE_V(...) emp::is_trivially_destructible_v<__VA_ARGS__>
# endif
#endif


#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_nothrow_destructible))
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_nothrow_destructible, (class T), bool, __is_nothrow_destructible(T));
#else
  namespace detail
  {
#if JLN_MP_FEATURE_CONCEPTS
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_destructible_impl_v
      = requires { JLN_MP_DECLVAL_NOTHROW(T*)->~T(); };
#else
    template<class T, bool = true>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_destructible_impl_v = false;

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_destructible_impl_v<
      T, noexcept(JLN_MP_DECLVAL_NOTHROW(T*)->~T())
    > = true;
#endif

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_destructible_impl_v<T&> = true;

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_destructible_impl_v<T&&> = true;

    // TODO remove_all_extents
    template<class T, std::size_t n>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_destructible_impl_v<T[n]>
      = is_nothrow_destructible_impl_v<T>;
  }
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_IS(is_nothrow_destructible, (class T), bool,
    detail::is_nothrow_destructible_impl_v<T volatile const>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_implicit_lifetime)
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_implicit_lifetime, (class T), bool, __is_implicit_lifetime(T));
#else
  namespace detail
  {
    template<bool>
    struct is_implicit_lifetime_impl;

    template<>
    struct is_implicit_lifetime_impl<true>
    {
      template<class T>
      static constexpr bool v = true;
    };

    template<>
    struct is_implicit_lifetime_impl<false>
    {
      template<class T>
      static constexpr bool v = JLN_MP_IS_TRIVIALLY_DESTRUCTIBLE_V(T)
        && (__is_trivially_constructible(T)
          || __is_trivially_constructible(T, emp::add_lvalue_reference_t<T const>)
          || __is_trivially_constructible(T, T /*emp::add_rvalue_reference_t<T>*/)
        );
    };
  }
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_implicit_lifetime_v
      = detail::is_implicit_lifetime_impl<
        JLN_MP_IS_SCALAR_V(T)
      || JLN_MP_IS_ARRAY_V(T)
#if JLN_MP_HAS_BUILTIN(__is_aggregate)
      || __is_aggregate(T)
#endif
      >::template v<T volatile const>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_implicit_lifetime, (class T), bool, (T));
#endif


  namespace detail
  {
    template<class T>
    emp::enable_if_t<__is_constructible(T, T) && JLN_MP_IS_MOVE_ASSIGNABLE_V(T)>
    swap(T&, T&) noexcept(__is_nothrow_constructible(T, T)
                       && JLN_MP_IS_NOTHROW_MOVE_ASSIGNABLE_V(T));

    template<class T, class = void>
    JLN_MP_CONSTEXPR_VAR bool is_swappable_impl_v = false;

    template<class T, bool = true>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_swappable_impl_v = false;

    template<class T, std::size_t N>
    emp::enable_if_t<is_swappable_impl_v<T&>>
    swap(T(&)[N], T(&)[N]) noexcept(is_nothrow_swappable_impl_v<T&>);

#if JLN_MP_FEATURE_CONCEPTS
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_swappable_impl_v<T, void>
      = requires{ swap(JLN_MP_DECLVAL(T), JLN_MP_DECLVAL(T)); };

    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool is_swappable_with_impl_v = requires{
      swap(JLN_MP_DECLVAL(T), JLN_MP_DECLVAL(U));
      swap(JLN_MP_DECLVAL(U), JLN_MP_DECLVAL(T));
    };
#else
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_swappable_impl_v<
      T, decltype(void(swap(JLN_MP_DECLVAL(T), JLN_MP_DECLVAL(T))))
    > = true;

    template<class T, class U, class = void>
    JLN_MP_CONSTEXPR_VAR bool is_swappable_with_impl_v = false;

    JLN_MP_DIAGNOSTIC_PUSH()
    JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wcomma")
    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool is_swappable_with_impl_v<
      // TODO decltype((....)) <- no Wcomma ?
      T, U, decltype(
        swap(JLN_MP_DECLVAL(T), JLN_MP_DECLVAL(U)),
        void(swap(JLN_MP_DECLVAL(T), JLN_MP_DECLVAL(U)))
      )
    > = true;
    JLN_MP_DIAGNOSTIC_POP()
#endif

    // TODO enable_if_t -> int[noexcept(...)] ? /!\ gcc
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_swappable_impl_v<
      T, noexcept(swap(JLN_MP_DECLVAL_NOTHROW(T), JLN_MP_DECLVAL_NOTHROW(T)))
    > = true;

    template<class T, class U, class = void>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_swappable_with_impl_v = false;

    // TODO enable_if_t -> int[noexcept(...)] ? /!\ gcc
    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_swappable_with_impl_v<
      T, U, emp::enable_if_t<noexcept(
        void(swap(JLN_MP_DECLVAL_NOTHROW(T), JLN_MP_DECLVAL_NOTHROW(U))),
        swap(JLN_MP_DECLVAL_NOTHROW(T), JLN_MP_DECLVAL_NOTHROW(U))
      )>
    > = true;
  }

  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_swappable_v
      = detail::is_swappable_impl_v<add_lvalue_reference_t<T>>;

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_swappable_v
      = detail::is_nothrow_swappable_impl_v<add_lvalue_reference_t<T>>;

    // TODO T, T -> is_swappable_v<T> ?
    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool is_swappable_with_v
      = detail::is_swappable_with_impl_v<add_rvalue_reference_t<T>, add_rvalue_reference_t<U>>;

    // TODO T, T -> is_nothrow_swappable_v<T> ?
    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_swappable_with_v
      = detail::is_nothrow_swappable_with_impl_v<add_rvalue_reference_t<T>, add_rvalue_reference_t<U>>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_swappable, (class T), bool, (T));
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_nothrow_swappable, (class T), bool, (T));
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_swappable_with, (class T, class U), bool, (T, U));
  JLN_MP_MAKE_TRAIT_FROM_EMP_V(is_nothrow_swappable_with, (class T, class U), bool, (T, U));


#if JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__has_virtual_destructor)
  JLN_MP_MAKE_TRAIT_FROM_F(has_virtual_destructor, (class T), bool, __has_virtual_destructor(T));
#elif ! JLN_MP_NO_STL
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(has_virtual_destructor, (class T), bool, (T));
#else
  // this implementation is not compliant and fails with classes and unions
  JLN_MP_MAKE_TRAIT_IS(has_virtual_destructor, (class T), bool, false);
#endif


  JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_LIBSTDCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_same, (class T, class U), bool, JLN_MP_IS_SAME_V(T, U));


// TODO no stl
// #if JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_layout_compatible)
//   JLN_MP_MAKE_TRAIT_FROM_BUILTIN_T_STD_SV(
//     is_layout_compatible, (class T, class U), bool, __is_layout_compatible(T, U));
// #elif ! JLN_MP_NO_STL && defined(__cpp_lib_is_layout_compatible) && __cpp_lib_is_layout_compatible >= 201907L
//   JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_layout_compatible, (class T, class U), bool, (T, U));
// #else
//   // TODO
// #endif


#if defined(__cpp_lib_is_pointer_interconvertible) && __cpp_lib_is_pointer_interconvertible >= 201907L
  // TODO
  // JLN_MP_MAKE_TRAIT_P2(JLN_MP_TRAIT_BUILTIN_IS(is_pointer_interconvertible_base_of, MSVC, 0, 0));
  // JLN_MP_MAKE_TRAIT_P2(JLN_MP_TRAIT_BUILTIN_IS(is_pointer_interconvertible_with_class, MSVC, 0, 0));
#else
  // TODO
#endif


  // TODO LIBMS || LIBCPP -> use std::
  // TODO is_complete_or_unbounded
#if JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(alignment_of, (class T), std::size_t, (T));
#else
  JLN_MP_MAKE_TRAIT_FROM_F(alignment_of, (class T), std::size_t, alignof(T));
#endif


#if JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(rank, (class T), std::size_t, (T));
#else
  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR std::size_t rank_v = 0;

    template<class T>
    JLN_MP_CONSTEXPR_VAR std::size_t rank_v<T[]> = rank_v<T> + 1;

    template<class T, std::size_t n>
    JLN_MP_CONSTEXPR_VAR std::size_t rank_v<T[n]> = rank_v<T> + 1;
  }
  JLN_MP_MAKE_TRAIT(rank, (class T), std::integral_constant<std::size_t, emp::rank_v<T>>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__array_extent)
  namespace emp
  {
    template<class T, unsigned Dim = 0>
    JLN_MP_CONSTEXPR_VAR std::size_t extent_c_v = __array_extent(T, Dim);

    template<class T, class Dim = number<0>>
    JLN_MP_CONSTEXPR_VAR std::size_t extent_v = __array_extent(T, Dim::value);

    template<class T, unsigned Dim = 0>
    using extent_c_t = emp::integral_constant<T, __array_extent(T, Dim)>;

    template<class T, class Dim = number<0>>
    using extent_t = emp::integral_constant<T, __array_extent(T, Dim::value)>;
  }
#else
  namespace emp
  {
    template<class T, unsigned Dim = 0>
    JLN_MP_CONSTEXPR_VAR std::size_t extent_c_v = 0;

    template<class T, unsigned Dim>
    JLN_MP_CONSTEXPR_VAR std::size_t extent_c_v<T[], Dim> = extent_c_v<T, Dim - 1>;

    template<class T, std::size_t n>
    JLN_MP_CONSTEXPR_VAR std::size_t extent_c_v<T[n], 0> = n;

    template<class T, unsigned Dim, std::size_t n>
    JLN_MP_CONSTEXPR_VAR std::size_t extent_c_v<T[n], Dim> = extent_c_v<T, Dim - 1>;


    template<class T, class Dim = number<0>>
    JLN_MP_CONSTEXPR_VAR std::size_t extent_v = extent_c_v<T, Dim::value>;

    template<class T, unsigned Dim = 0>
    using extent_c_t = emp::integral_constant<T, extent_c_v<T, Dim>>;

    template<class T, class Dim = number<0>>
    using extent_t = emp::integral_constant<T, extent_c_v<T, Dim::value>>;
  }
#endif
  namespace emp
  {
    template<class T, unsigned Dim = 0>
    struct extent_c : extent_c_t<T, Dim> {};

    template<class T, class Dim = number<0>>
    using extent = extent_c<T, Dim::value>;
  }
  JLN_MP_MAKE_TRAIT_NO_EMP(extent, (class T, class Dim = number<0>), emp::extent_c_t<T, Dim::value>);


  namespace detail
  {
    // TODO no stl
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_reference_wrapper_v = false;

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_reference_wrapper_v<std::reference_wrapper<T>> = true;

    // TODO cppreference implementation

    template<class T>
    struct invoke_impl
    {
      template<class F, class... Args>
      static auto call(F&& f, Args&&... args)
        -> decltype(static_cast<F&&>(f)(static_cast<Args&&>(args)...));
    };

    template<class C, class M>
    struct invoke_impl<M C::*>
    {
      template<class T, class Td = typename std::decay<T>::type,
        class = typename std::enable_if<std::is_base_of<C, Td>::value>::type
      >
      static auto get(T&& t) -> T&&;

      template<class T, class Td = typename std::decay<T>::type,
        class = typename std::enable_if<is_reference_wrapper_v<Td>>::type
      >
      static auto get(T&& t) -> decltype(t.get());

      template<class T, class Td = typename std::decay<T>::type,
        class = typename std::enable_if<!std::is_base_of<C, Td>::value>::type,
        class = typename std::enable_if<!is_reference_wrapper_v<Td>>::type
      >
      static auto get(T&& t) -> decltype(*static_cast<T&&>(t));

      template<class T, class... Args, class M1,
          class = typename std::enable_if<std::is_function<M1>::value>::type
      >
      static auto call(M1 C::*pmf, T&& t, Args&&... args)
        -> decltype((invoke_impl::get(static_cast<T&&>(t)).*pmf)(static_cast<Args&&>(args)...));

      template<class T>
      static auto call(M C::*pmd, T&& t)
        -> decltype(invoke_impl::get(static_cast<T&&>(t)).*pmd);
    };

    template<class F, class... Args, class Fd = typename std::decay<F>::type>
    auto INVOKE(F&& f, Args&&... args)
        -> decltype(invoke_impl<Fd>::call(static_cast<F&&>(f), static_cast<Args&&>(args)...));

    template<typename AlwaysVoid, typename, typename...>
    struct invoke_result {};

    template<typename F, typename...Args>
    struct invoke_result<
      decltype(void(detail::INVOKE(std::declval<F>(), std::declval<Args>()...))),
      F, Args...>
    {
      using type = decltype(detail::INVOKE(std::declval<F>(), std::declval<Args>()...));
    };
  } // namespace detail

  JLN_MP_MAKE_TRAIT_WRAP_T(invoke_result, (class F, class... Args),
    detail::invoke_result<void, F, Args...>);


#if defined(__cpp_lib_is_invocable) && __cpp_lib_is_invocable >= 201703L
  // TODO https://en.cppreference.com/w/cpp/utility/functional (C++23)
  // TODO
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_invocable, (class Fn, class... Args), bool, (Fn, Args...));
  // TODO
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_invocable_r, (class R, class Fn, class... Args), bool, (R, Fn, Args...));
  // TODO
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_nothrow_invocable, (class Fn, class... Args), bool, (Fn, Args...));
  // TODO
  JLN_MP_MAKE_TRAIT_FROM_STD_SVAT(is_nothrow_invocable_r, (class R, class Fn, class... Args), bool, (R, Fn, Args...));
#endif


#if defined(__cpp_lib_reference_from_temporary) && __cpp_lib_reference_from_temporary >= 202202L
  JLN_MP_MAKE_TRAIT_FROM_STD_ST(reference_constructs_from_temporary, (class T, class U), (T, U));
  JLN_MP_MAKE_TRAIT_FROM_STD_ST(reference_converts_from_temporary, (class T, class U), (T, U));
#else
  // TODO
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_const)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(remove_const, (class T), (T));
#elif ! JLN_MP_NO_STL
  JLN_MP_MAKE_TRAIT_FROM_STD_ST(remove_const, (class T), (T));
#elif JLN_MP_GCC
  namespace detail
  {
    template<class T> struct remove_const_impl { using type = T; };
    template<class T> struct remove_const_impl<T const> { using type = T; };
  }
  namespace emp
  {
    template<class T> using remove_const = detail::remove_const_impl<T const>;
  }
  JLN_MP_MAKE_TRAIT_T(remove_const, (class T), detail::remove_const_impl<T const>);
#else
  namespace emp
  {
    template<class T> struct remove_const { using type = T; };
    template<class T> struct remove_const<T const> { using type = T; };
  }
  JLN_MP_MAKE_TRAIT_T(remove_const, (class T), emp::remove_const<T>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_volatile)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(remove_volatile, (class T), (T));
#elif ! JLN_MP_NO_STL
  JLN_MP_MAKE_TRAIT_FROM_STD_ST(remove_volatile, (class T), (T));
#elif JLN_MP_GCC
  namespace detail
  {
    template<class T> struct remove_volatile_impl { using type = T; };
    template<class T> struct remove_volatile_impl<T volatile> { using type = T; };
  }
  namespace emp
  {
    template<class T> using remove_volatile = detail::remove_volatile_impl<T volatile>;
  }
  JLN_MP_MAKE_TRAIT_T(remove_volatile, (class T), detail::remove_volatile_impl<T volatile>);
#else
  namespace emp
  {
    template<class T> struct remove_volatile { using type = T; };
    template<class T> struct remove_volatile<T volatile> { using type = T; };
  }
  JLN_MP_MAKE_TRAIT_T(remove_volatile, (class T), emp::remove_volatile<T>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_extents)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(remove_extents, (class T), (T));
#elif ! JLN_MP_NO_STL
  JLN_MP_MAKE_TRAIT_FROM_STD_ST(remove_extent, (class T), (T));
#else
  namespace emp
  {
    template<class T> struct remove_extent { using type = T; };
    template<class T> struct remove_extent<T[]> { using type = T; };
    template<class T, std::size_t N> struct remove_extent<T[N]> { using type = T; };
  }
  JLN_MP_MAKE_TRAIT_T(remove_extent, (class T), emp::remove_extent<T>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_all_extents)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(remove_all_extents, (class T), (T));
#elif ! JLN_MP_NO_STL
  JLN_MP_MAKE_TRAIT_FROM_STD_ST(remove_all_extents, (class T), (T));
#else
  namespace emp
  {
    template<class T> struct remove_all_extents { using type = T; };
    template<class T> struct remove_all_extents<T[]> : remove_all_extents<T> {};
    template<class T, std::size_t N> struct remove_all_extents<T[N]> : remove_all_extents<T> {};
  }
  JLN_MP_MAKE_TRAIT_T(remove_all_extents, (class T), emp::remove_all_extents<T>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_pointer)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(remove_pointer, (class T), (T));
#elif ! JLN_MP_NO_STL
  JLN_MP_MAKE_TRAIT_FROM_STD_ST(remove_pointer, (class T), (T));
#else
  namespace emp
  {
    template<class T> struct remove_pointer { using type = T; };
    template<class T> struct remove_pointer<T*> { using type = T; };
    template<class T> struct remove_pointer<T* const> { using type = T; };
    template<class T> struct remove_pointer<T* volatile> { using type = T; };
    template<class T> struct remove_pointer<T* volatile const> { using type = T; };
  }
  JLN_MP_MAKE_TRAIT_T(remove_pointer, (class T), emp::remove_pointer<T>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_reference_t)
  // TODO use builtin / std::... with macro
# if JLN_MP_USE_LIBCXX
  JLN_MP_MAKE_TRAIT_FROM_STD_ST(remove_reference, (class T), (T));
# else
  JLN_MP_MAKE_TRAIT_FROM_ST(remove_reference, (class T), __remove_reference_t(T))
# endif
#elif ! JLN_MP_NO_STL
  JLN_MP_MAKE_TRAIT_FROM_STD_ST(remove_reference, (class T), (T));
#else
  namespace emp
  {
    template<class T> struct remove_reference { using type = T; };
    template<class T> struct remove_reference<T&> { using type = T; };
    template<class T> struct remove_reference<T&&> { using type = T; };
  }
  JLN_MP_MAKE_TRAIT_T(remove_reference, (class T), emp::remove_reference<T>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_cv)
  // TODO use builtin / std::... with macro
# if JLN_MP_BUILTIN_HIDDEN_BY_LIBSTDCXX && JLN_MP_HAS_BUILTIN(__remove_const) && JLN_MP_HAS_BUILTIN(__remove_volatile)
  JLN_MP_MAKE_TRAIT_FROM_ST(remove_cv, (class T), __remove_const(__remove_volatile(T)));
# else
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(remove_cv, (class T), (T));
# endif
#elif JLN_MP_USE_LIBSTDCXX
  JLN_MP_MAKE_TRAIT_FROM_STD_ST(remove_cv, (class T), (T));
#elif JLN_MP_GCC
  namespace detail
  {
    template<class T> struct remove_cv_impl { using type = T; };
    template<class T> struct remove_cv_impl<T volatile const> { using type = T; };
  }
  namespace emp
  {
    template<class T> struct remove_cv : detail::remove_cv_impl<T volatile const> {};
    template<class T> using remove_cv_t = typename detail::remove_cv_impl<T volatile const>::type;
  }
  JLN_MP_MAKE_TRAIT_NO_EMP(remove_cv, (class T),
    typename detail::remove_cv_impl<T volatile const>::type);
#else
  namespace emp
  {
    template<class T> struct remove_cv { using type = T; };
    template<class T> struct remove_cv<T const> { using type = T; };
    template<class T> struct remove_cv<T volatile> { using type = T; };
    template<class T> struct remove_cv<T volatile const> { using type = T; };
  }
  JLN_MP_MAKE_TRAIT_T(remove_cv, (class T), emp::remove_cv<T>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_cvref)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_FROM_ST(remove_cvref, (class T), __remove_cvref(T));
#elif JLN_MP_USE_LIBSTDCXX && defined(__cpp_lib_remove_cvref) && __cpp_lib_remove_cvref >= 201711L
  JLN_MP_MAKE_TRAIT_FROM_STD_ST(remove_cvref, (class T), (T));
#else
  namespace emp
  {
    // TODO remove_cv_impl may not exist
    #if ! JLN_MP_USE_LIBSTDCXX && JLN_MP_GCC
    template<typename T> struct remove_cvref : detail::remove_cv_impl<T volatile const> {};
    template<typename T> struct remove_cvref<T&> : detail::remove_cv_impl<T volatile const> {};
    template<typename T> struct remove_cvref<T&&> : detail::remove_cv_impl<T volatile const> {};
    #else
    template<typename T> struct remove_cvref : remove_cv<T> {};
    template<typename T> struct remove_cvref<T&> : remove_cv<T> {};
    template<typename T> struct remove_cvref<T&&> : remove_cv<T> {};
    #endif
  }
  JLN_MP_MAKE_TRAIT_T(remove_cvref, (class T), emp::remove_cvref<T>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__add_pointer)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(add_pointer, (class T), (T));
#else
namespace detail
  {
    template<class T, class = void> struct add_pointer_impl { using type = T; };
    template<class T> struct add_pointer_impl<T, emp::void_t<T*>> { using type = T*; };
    template<class T> struct add_pointer_impl<T&, emp::void_t<T*>> { using type = T*; };
    template<class T> struct add_pointer_impl<T&&, emp::void_t<T*>> { using type = T*; };
  }
  JLN_MP_MAKE_TRAIT_WRAP_T(add_pointer, (class T), detail::add_pointer_impl<T>);
#endif


  namespace emp
  {
    template<class T> using add_cv_t = T volatile const;
    template<class T> using add_const_t = T const;
    template<class T> using add_volatile_t = T volatile;

    #if ! JLN_MP_NO_STL
    using std::add_cv;
    using std::add_const;
    using std::add_volatile;
    #else
    template<class T> struct add_cv { using type = T volatile const; };
    template<class T> struct add_const { using type = T const; };
    template<class T> struct add_volatile { using type = T volatile; };
    #endif
  }
  JLN_MP_MAKE_TRAIT_NO_EMP(add_const, (class T), T const);
  JLN_MP_MAKE_TRAIT_NO_EMP(add_volatile, (class T), T volatile);
  JLN_MP_MAKE_TRAIT_NO_EMP(add_cv, (class T), T volatile const);


  namespace detail
  {
    template<int>
    struct mk_min_rank
    {};

    template<>
    struct mk_min_rank<-1>
    {
      using signed_type = signed char;
      using unsigned_type = unsigned char;
    };

    template<>
    struct mk_min_rank<-2>
    {
      using signed_type = signed short;
      using unsigned_type = unsigned short;
    };

    template<>
    struct mk_min_rank<-3>
    {
      using signed_type = signed int;
      using unsigned_type = unsigned int;
    };

    template<>
    struct mk_min_rank<-4>
    {
      using signed_type = signed long;
      using unsigned_type = unsigned long;
    };

    template<>
    struct mk_min_rank<-5>
    {
      using signed_type = signed long long;
      using unsigned_type = unsigned long long;
    };

    template<std::size_t n>
    struct select_min_rank : mk_min_rank<
      n <= 1 ? -1 :
      n <= sizeof(short) ? -2 :
      n <= sizeof(int) ? -3 :
      n <= sizeof(long) ? -4 :
      n <= sizeof(long long) ? -5 :
      int(n)
    >
    {};

    template<class T>
    struct make_signed
    {
      // If T is an integral (except bool) or enumeration type, provides the
      // member typedef type which is the signed integer type corresponding to
      // T, with the same cv-qualifiers. Otherwise, the program is ill-formed.
      static_assert((emp::is_integral_v<T> || __is_enum(T))
                 && !JLN_MP_IS_SAME_V(T, bool volatile const),
        "make_signed<T> requires that T shall be a (possibly cv-qualified) "
        "integral type or enumeration but not a bool type.");

      // If T is an enumeration type or char, wchar_t, char8_t (since C++20),
      // char16_t, char32_t, the signed integer type with the smallest rank
      // having the same sizeof as T is provided.
      using type = typename select_min_rank<sizeof(T)>::signed_type;
    };

#if JLN_MP_CLANG || JLN_MP_MSVC
    template<class T> struct make_signed<T const>
    { using type = typename make_signed<T>::type const; };
    template<class T> struct make_signed<T volatile>
    { using type = typename make_signed<T>::type volatile; };
    template<class T> struct make_signed<T volatile const>
    { using type = typename make_signed<T>::type volatile const; };
#endif

    // If T is signed or unsigned char, short, int, long, long long,
    // the signed type from this list corresponding to T is provided.
    template<> struct make_signed<volatile const char>          { using type = signed char; };
    template<> struct make_signed<volatile const unsigned char> { using type = signed char; };
    template<> struct make_signed<volatile const   signed char> { using type = signed char; };
    template<> struct make_signed<volatile const unsigned short> { using type = signed short; };
    template<> struct make_signed<volatile const   signed short> { using type = signed short; };
    template<> struct make_signed<volatile const unsigned int> { using type = signed int; };
    template<> struct make_signed<volatile const   signed int> { using type = signed int; };
    template<> struct make_signed<volatile const unsigned long> { using type = signed long; };
    template<> struct make_signed<volatile const   signed long> { using type = signed long; };
    template<> struct make_signed<volatile const unsigned long long> { using type = signed long long; };
    template<> struct make_signed<volatile const   signed long long> { using type = signed long long; };
    // TODO support of __uint128_t, __int128_t, etc

    template<class T>
    struct make_unsigned
    {
      // If T is an integral (except bool) or enumeration type, provides the
      // member typedef type which is the unsigned integer type corresponding to
      // T, with the same cv-qualifiers. Otherwise, the program is ill-formed.
      static_assert((emp::is_integral_v<T> || __is_enum(T))
                 && !JLN_MP_IS_SAME_V(T, bool volatile const),
        "make_unsigned<T> requires that T shall be a (possibly cv-qualified) "
        "integral type or enumeration but not a bool type.");

      // If T is an enumeration type or char, wchar_t, char8_t (since C++20),
      // char16_t, char32_t, the unsigned integer type with the smallest rank
      // having the same sizeof as T is provided.
      using type = typename select_min_rank<sizeof(T)>::unsigned_type;
    };

#if JLN_MP_CLANG || JLN_MP_MSVC
    template<class T> struct make_unsigned<T const>
    { using type = typename make_unsigned<T>::type const; };
    template<class T> struct make_unsigned<T volatile>
    { using type = typename make_unsigned<T>::type volatile; };
    template<class T> struct make_unsigned<T volatile const>
    { using type = typename make_unsigned<T>::type volatile const; };
#endif

    // If T is unsigned or signed char, short, int, long, long long,
    // the unsigned type from this list corresponding to T is provided.
    template<> struct make_unsigned<volatile const char>          { using type = unsigned char; };
    template<> struct make_unsigned<volatile const unsigned char> { using type = unsigned char; };
    template<> struct make_unsigned<volatile const   signed char> { using type = unsigned char; };
    template<> struct make_unsigned<volatile const unsigned short> { using type = unsigned short; };
    template<> struct make_unsigned<volatile const   signed short> { using type = unsigned short; };
    template<> struct make_unsigned<volatile const unsigned int> { using type = unsigned int; };
    template<> struct make_unsigned<volatile const   signed int> { using type = unsigned int; };
    template<> struct make_unsigned<volatile const unsigned long> { using type = unsigned long; };
    template<> struct make_unsigned<volatile const   signed long> { using type = unsigned long; };
    template<> struct make_unsigned<volatile const unsigned long long> { using type = unsigned long long; };
    template<> struct make_unsigned<volatile const   signed long long> { using type = unsigned long long; };
    // TODO support of __uint128_t, __int128_t, etc

    // TODO copy_const / copy_volatile / copy_cv / copy_reference / copy_cvref

    // TODO
    // template<bool IsConst, bool IsVolatile, bool IsLRef, bool isRRef>
    // struct copy_cvref_select;
    //
    // template<> struct copy_cvref_select<false, false, false, false> : identity {};
    // template<> struct copy_cvref_select<true, false, false, false> : add_const<> {};
    // template<> struct copy_cvref_select<false, true, false, false> : add_volatile<> {};
    // template<> struct copy_cvref_select<true, true, false, false> : add_cv<> {};
    //
    // template<> struct copy_cvref_select<false, false, true, false> : add_lvalue_reference<> {};
    // template<> struct copy_cvref_select<true, false, true, false> : add_const<> {};
    // template<> struct copy_cvref_select<false, true, true, false> : add_volatile<> {};
    // template<> struct copy_cvref_select<true, true, true, false> : add_cv<> {};
    //
    // template<> struct copy_cvref_select<false, false, false, true> : add_rvalue_reference<> {};
    // template<> struct copy_cvref_select<true, false, false, true> : add_const<> {};
    // template<> struct copy_cvref_select<false, true, false, true> : add_volatile<> {};
    // template<> struct copy_cvref_select<true, true, false, true> : add_cv<> {};
    //
    // template<class Qualified, class UnQualified>
    // struct match_cv { using type = UnQualified; };
    //
    // template<class Qualified, class UnQualified>
    // struct match_cv<Qualified const, UnQualified> { using type = UnQualified const; };
    //
    // template<class Qualified, class UnQualified>
    // struct match_cv<Qualified volatile, UnQualified> { using type = UnQualified volatile; };
    //
    // template<class Qualified, class UnQualified>
    // struct match_cv<Qualified volatile const, UnQualified> { using type = UnQualified volatile const; };

    template<int>
    struct copy_cvref_impl;

    template<> struct copy_cvref_impl<0> : identity {};
    template<> struct copy_cvref_impl<1> : add_const<> {};
    template<> struct copy_cvref_impl<2> : add_volatile<> {};
    template<> struct copy_cvref_impl<3> : add_cv<> {};

    // TODO unimplemented
    template<> struct copy_cvref_impl<10> : add_lvalue_reference<> {};
    template<> struct copy_cvref_impl<11> { template<class T> using f = void; };
    template<> struct copy_cvref_impl<12> : add_volatile<> {};
    template<> struct copy_cvref_impl<13> : add_cv<> {};

    // TODO unimplemented
    template<> struct copy_cvref_impl<20> : add_rvalue_reference<> {};
    template<> struct copy_cvref_impl<21> : add_const<> {};
    template<> struct copy_cvref_impl<22> : add_volatile<> {};
    template<> struct copy_cvref_impl<23> : add_cv<> {};

    template<class T> JLN_MP_CONSTEXPR_VAR bool cv_select = 0;
    template<class T> JLN_MP_CONSTEXPR_VAR bool cv_select<T const> = 1;
    template<class T> JLN_MP_CONSTEXPR_VAR bool cv_select<T volatile> = 2;
    template<class T> JLN_MP_CONSTEXPR_VAR bool cv_select<T volatile const> = 3;
  }

#if JLN_MP_CLANG || JLN_MP_MSVC
  namespace emp
  {
    using detail::make_signed;
    using detail::make_unsigned;
  }
  JLN_MP_MAKE_TRAIT_T(make_signed, (class T), detail::make_signed<T>);
  JLN_MP_MAKE_TRAIT_T(make_unsigned, (class T), detail::make_unsigned<T>);
#else
  namespace emp
  {
    template<class T> using make_signed_t
      = typename detail::copy_cvref_impl<detail::cv_select<T>>
      ::template f<typename detail::make_signed<T volatile const>::type>;

    template<class T> using make_unsigned_t
      = typename detail::copy_cvref_impl<detail::cv_select<T>>
      ::template f<typename detail::make_unsigned<T volatile const>::type>;

    template<class T> struct make_signed { using type = make_signed_t<T>; };
    template<class T> struct make_unsigned { using type = make_unsigned_t<T>; };
  }
  JLN_MP_MAKE_TRAIT_NO_EMP(make_signed, (class T), emp::make_signed_t<T>);
  JLN_MP_MAKE_TRAIT_NO_EMP(make_unsigned, (class T), emp::make_unsigned_t<T>);
#endif


  // TODO
  // namespace emp
  // {
  //   template<class Qualified, class UnQualified>
  //   using copy_cv = typename detail::copy_cvref_impl<detail::cv_select<Qualified>>
  //     ::template f<UnQualified>;
  // }


  namespace detail
  {
    /* decay:
     * remove_reference -> {
     *  is_array
     *    ? remove_extent -> add_pointer
     *    : is_function
     *        ? add_pointer
     *        : remove_cv
     * }
     */

    // is_function
    // TODO add_pointer_impl may not exist
    template<class T, class = void> struct decay_maybe_func : add_pointer_impl<T> {};
    // not is_function
    template<class T> struct decay_maybe_func<T volatile const> { using type = T; };
  }
  namespace emp
  {
    // TODO __remove_reference_t
    template<class T> struct decay : detail::decay_maybe_func<T volatile const> {};
    template<class T> struct decay<T&> : detail::decay_maybe_func<T volatile const> {};
    template<class T> struct decay<T&&> : detail::decay_maybe_func<T volatile const> {};
    template<class T> struct decay<T[]> { using type = T*; };
    template<class T> struct decay<T(&)[]> { using type = T*; };
    template<class T> struct decay<T(&&)[]> { using type = T*; };
    template<class T, std::size_t N> struct decay<T[N]> { using type = T*; };
    template<class T, std::size_t N> struct decay<T(&)[N]> { using type = T*; };
    template<class T, std::size_t N> struct decay<T(&&)[N]> { using type = T*; };
  }
  JLN_MP_MAKE_TRAIT_T(decay, (class T), emp::decay<T>);


#if ! JLN_MP_NO_STL && defined(__cpp_lib_unwrap_ref) && __cpp_lib_unwrap_ref >= 201811L
  JLN_MP_MAKE_TRAIT_FROM_STD_ST(unwrap_reference, (class T), (T));
#else
  namespace emp
  {
    template<class T> struct unwrap_reference { using type = T; };
    #if ! JLN_MP_NO_STL
    template<class T> struct unwrap_reference<std::reference_wrapper<T>> { using type = T&; };
    #endif
  }
  JLN_MP_MAKE_TRAIT_T(unwrap_reference, (class T), emp::unwrap_reference<T>);
#endif


  namespace emp
  {
    template<class T> struct unwrap_ref_decay : unwrap_reference<decay_t<T>> {};
    template<class T> using unwrap_ref_decay_t = unwrap_reference_t<decay_t<T>>;
  }
  JLN_MP_MAKE_TRAIT_NO_EMP(unwrap_ref_decay, (class T), emp::unwrap_ref_decay_t<T>);


#if __cplusplus >= 202002L
// TODO __cpp_lib_common_reference 	Make std::common_reference_t of std::reference_wrapper a reference type 	202302L 	<type_traits> 	(C++23) 	P2655R3
// TODO __cpp_lib_common_reference_wrapper 	Make std::common_reference_t of std::reference_wrapper a reference type 	202302L 	<functional> 	(C++23) 	P2655R3
  JLN_MP_MAKE_TRAIT_FROM_STD_ST(common_reference, (class... Ts), (Ts...));
  // TODO JLN_MP_MAKE_TRAIT_FROM_STD_ST(basic_common_reference, (class T, class U, template<class> class TQual, template<class> class UQual), (T, U, TQual, UQual));
#else
  // TODO remove that or alias on invoke_result
  JLN_MP_MAKE_TRAIT_FROM_STD_ST(result_of, (class Sig), (Sig));
#endif


#if 1
  JLN_MP_MAKE_TRAIT_FROM_ST(underlying_type, (class T), __underlying_type(T));
#else
  namespace detail
  {
    template<class T, bool = __is_enum(T)>
    struct underlying_type_impl { using type = __underlying_type(T); };

    template<class T> struct underlying_type_impl<T, false> {};
  }
  JLN_MP_MAKE_TRAIT_WRAP_T(underlying_type, (class T), detail::underlying_type_impl<T>);
#endif


  namespace emp
  {
    /*
     * common_type<> -> no member type
     * common_type<T> -> common_type<T, T>
     * common_type<T, U> -> {user specialization} or {
     *  decay_t<T> == T && decay_t<U> == U
     *    ? VALID(decltype(false ? declval<T>() : declval<U>()) -> ExprType)
     *        ? decay_t<ExprType>
     *        : (< C++20)
     *            ? no member type
     *            : VALID({decltype(false ? declval<const remove_reference_t<T>&>()
     *                                    : declval<const remove_reference_t<U>&>())
     *                    } -> ExprType)
     *                ? decay_t<ExprType>
     *                : no member type
     *    : common_type<decay_t<T>, decay_t<U>>
     * }
     * common_type<T, U, R...> -> {
     *  VALID({typename common_type<T, U>::type} -> ExprType)
     *    ? common_type<ExprType, R...>::type
     *    : no member type
     * }
     */
    template<class... Ts>
    struct common_type;
  }
  namespace detail
  {
    template<bool>
    struct common_type_decayed_dispatch;

    template<>
    struct common_type_decayed_dispatch<false>
    {
      template<class T, class U>
      using f = emp::common_type<T, U>;
    };

    template<class T, class U, class DT = emp::decay_t<T>, class DU = emp::decay_t<U>>
    using common_type2 = typename common_type_decayed_dispatch<
      JLN_MP_IS_SAME_V(T, DT) && JLN_MP_IS_SAME_V(U, DU)
    >::template f<DT, DU>;

    template<>
    struct common_type_decayed_dispatch<true>
    {
      template<class T, class U>
      using cond = decltype(false ? JLN_MP_DECLVAL(T) : JLN_MP_DECLVAL(U));

#if JLN_MP_CXX_VERSION >= 20
      template<class T, class U, class = void>
      struct lvalue_cond
      {};

      template<class T, class U>
      struct lvalue_cond<T, U, emp::void_t<cond<T, U>>>
      {
        using type = emp::decay_t<cond<T, U>>;
      };
#endif

      // TODO use std::common_type<T, U> when JLN_MP_TRAITS_USE_COMMON_TYPE2
      template<class T, class U,
        class TRal = emp::add_rvalue_reference_t<T>,
        class URal = emp::add_rvalue_reference_t<U>,
        class = void>
      struct f
#if JLN_MP_CXX_VERSION >= 20
        : lvalue_cond<
          // TODO when T or U is void, this `f` struct is not selected -> remove add_lvalue_reference ?
          emp::add_lvalue_reference_t<T const>,
          emp::add_lvalue_reference_t<U const>
        >
#endif
      {};

      template<class T, class U, class TRval, class URval>
      struct f<T, U, TRval, URval, emp::void_t<cond<TRval, URval>>>
      {
        using type = emp::decay_t<cond<TRval, URval>>;
      };
    };

#if JLN_MP_FEATURE_CONCEPTS
    template<bool>
    struct common_type_fold;

    template<>
    struct common_type_fold<true>
    {
      template<class CommonType, class... xs>
      using f = emp::common_type<typename CommonType::type, xs...>;
    };

    template<>
    struct common_type_fold<false>
    {
      template<class, class...>
      using f = emp::common_type<>;
    };
#else
    template<class CommonType, class = void>
    struct common_type_fold
    {
      template<class...>
      using f = emp::common_type<>;
    };

    template<class CommonType>
    struct common_type_fold<CommonType, emp::void_t<typename CommonType::type>>
    {
      template<class... xs>
      using f = emp::common_type<typename CommonType::type, xs...>;
    };
#endif
  }
  namespace emp
  {
    template<>
    struct common_type<>
    {};

    template<class T>
    struct common_type<T>
      : common_type<T, T>
    {};

    template<class T, class U>
    struct common_type<T, U>
      : detail::common_type2<T, U>
    {};

    template<class T, class U, class... R>
    struct common_type<T, U, R...>
#if JLN_MP_FEATURE_CONCEPTS
      : detail::common_type_fold<requires{ typename common_type<T, U>::type; }>
        ::template f<common_type<T, U>, R...>
#else
      : detail::common_type_fold<common_type<T, U>>::template f<R...>
#endif
    {};
  }
  JLN_MP_MAKE_TRAIT_T(common_type, (class... Ts), emp::common_type<Ts...>);


  // https://en.cppreference.com/w/cpp/experimental/is_detected

  namespace detail
  {
    template<class Default, class AlwaysVoid, template<class...> class Op, class... Args>
    struct detector
    {
      using value_t = emp::false_type;
      using type = Default;
    };

    template<class Default, template<class...> class Op, class... Args>
    struct detector<Default, emp::void_t<Op<Args...>>, Op, Args...>
    {
      using value_t = emp::true_type;
      using type = Op<Args...>;
    };
  }
  // TODO replace with find_if<> ?
  namespace emp
  {
    struct nonesuch
    {
        ~nonesuch() = delete;
        nonesuch(nonesuch const&) = delete;
        void operator=(nonesuch const&) = delete;
    };

    /// The alias template detected_or is an alias for an unspecified class type with two public member typedefs value_t and type, which are defined as follows:
    /// - If the template-id Op<Args...> denotes a valid type, then value_t is an alias for std::true_type, and type is an alias for Op<Args...>;
    /// - Otherwise, value_t is an alias for std::false_type and type is an alias for Default.
    template<class Default, template<class...> class Op, class... Args>
    using detected_or = detail::detector<Default, void, Op, Args...>;

#ifdef JLN_MP_DOXYGENATING
    template<template<class...> class Op, class... Args>
    using is_detected = typename detected_or<nonesuch, Op, Args...>::value_t;

    template<template<class...> class Op, class... Args>
    using detected_t = typename detected_or<nonesuch, Op, Args...>::type;

    template<class Default, template<class...> class Op, class... Args>
    using detected_or_t = typename detected_or<Default, Op, Args...>::type;
#else
    template<template<class...> class Op, class... Args>
    using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

    template<template<class...> class Op, class... Args>
    using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;

    template<class Default, template<class...> class Op, class... Args>
    using detected_or_t = typename detail::detector<Default, void, Op, Args...>::type;
#endif

    template<template<class...> class Op, class... Args>
    JLN_MP_CONSTEXPR_VAR bool is_detected_v = is_detected<Op, Args...>::value;
  }


#undef JLN_MP_TRAIT_BUILTIN_IMPL_IS
#undef JLN_MP_MAKE_TRAIT
#undef JLN_MP_CONSTEXPR_VAR

#undef JLN_MP_IS_VOID_V
#undef JLN_MP_IS_NULL_POINTER_V

#undef JLN_MP_IS_CONST_V
// TODO undef
}
