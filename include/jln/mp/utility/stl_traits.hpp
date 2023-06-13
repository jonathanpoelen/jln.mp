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

#if JLN_MP_MSVC
# define JLN_MP_USE_OPTIONAL_BUILTIN_EXISTS_WITH_MSVC(Name) JLN_MP_USE_OPTIONAL_BUILTIN
#else
# define JLN_MP_USE_OPTIONAL_BUILTIN_EXISTS_WITH_MSVC(Name) JLN_MP_HAS_OPTIONAL_BUILTIN(Name)
#endif

// TODO replace some call to JLN_MP_USE_OPTIONAL_BUILTIN with JLN_MP_USE_OPTIONAL_BUILTIN_EXISTS_WITH_MSVC

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

// TODO type_identity ?

// TODO MSVC: #pragma warning(disable: 4180)  // qualifier applied to function type has no meaning; ignored

// TODO defined(__cpp_*) && __cpp_* >= XXX -> __cpp_* >= XXX + disable warn

// TODO macro that forces use of std::


// TODO template<class T, class = void> struct xxxx_impl;
// TODO template<class T> struct xxxx_impl<T, void_t<.....>>;
// TODO template<class T> struct xxxx = xxxx_impl<T>;
// TODO ->
// TODO template<class T> struct xxxx {};
// TODO template<class T> requires { .... } struct xxxx {};

// TODO template<class T> struct X { using type = T; }; -> template<class T> struct X : type_identity<T> {} ?

// TODO no stl but predeclaration stl (reference_wrapper and co)


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


// TODO
namespace std
{
  template<class> class reference_wrapper;
  template<class, class> class pair;
  template<class...> class tuple;
}

namespace jln::mp::traits
{
  /// \ingroup trait

  // TODO remove duplicates in JLN_MP_MAKE_TRAIT*


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

// MAKE_TRAIT_SVT_*
//            ^ implements struct (struct Name : ... {})
//             ^ implements value (Name_v = ...)
//              ^ implements alias (Name_t = ...)

#define JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(Name, Params, Type, ...) \
  namespace emp                                                    \
  {                                                                \
    template<JLN_MP_UNPACK Params>                                 \
    JLN_MP_CONSTEXPR_VAR Type Name##_v = __VA_ARGS__;              \
                                                                   \
    template<JLN_MP_UNPACK Params>                                 \
    struct Name : integral_constant<Type, __VA_ARGS__> {};         \
                                                                   \
    template<JLN_MP_UNPACK Params>                                 \
    using Name##_t = integral_constant<Type, __VA_ARGS__>;         \
  }                                                                \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, emp::integral_constant<Type, __VA_ARGS__>)


#define JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(Name, Params, Type, Values)           \
  namespace emp                                                               \
  {                                                                           \
    template<JLN_MP_UNPACK Params>                                            \
    struct Name : integral_constant<Type, Name##_v<JLN_MP_UNPACK Values>> {}; \
                                                                              \
    template<JLN_MP_UNPACK Params>                                            \
    using Name##_t = integral_constant<Type, Name##_v<JLN_MP_UNPACK Values>>; \
  }                                                                           \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, emp::integral_constant<Type, emp::Name##_v<JLN_MP_UNPACK Values>>)


#define JLN_MP_MAKE_TRAIT_ST_FROM_S(Name, Params, ...) \
  namespace emp                                        \
  {                                                    \
    template<JLN_MP_UNPACK Params>                     \
    struct Name : __VA_ARGS__ {};                      \
                                                       \
    template<JLN_MP_UNPACK Params>                     \
    using Name##_t = typename __VA_ARGS__::type;       \
  }                                                    \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, typename __VA_ARGS__::type)


#define JLN_MP_MAKE_TRAIT_T_FROM_S(Name, Params, ...) \
  namespace emp                                       \
  {                                                   \
    template<JLN_MP_UNPACK Params>                    \
    using Name##_t = typename __VA_ARGS__::type;      \
  }                                                   \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, typename __VA_ARGS__::type)


#define JLN_MP_MAKE_TRAIT_ST_FROM_STD(Name, Params, Values) \
  namespace emp                                             \
  {                                                         \
    using std::Name;                                        \
    using std::Name##_t;                                    \
  }                                                         \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, std::Name##_t<JLN_MP_UNPACK Values>)


#define JLN_MP_MAKE_TRAIT_T_FROM_EXPR_V_x_SV_FROM_STD(Name, Params, Type, ...) \
  namespace emp                                                                \
  {                                                                            \
    using std::Name;                                                           \
    using std::Name##_v;                                                       \
                                                                               \
    template<JLN_MP_UNPACK Params>                                             \
    using Name##_t = integral_constant<Type, __VA_ARGS__>;                     \
  }                                                                            \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, emp::integral_constant<Type, __VA_ARGS__>)


#define JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(Name, Params, Type, Values) \
  JLN_MP_MAKE_TRAIT_T_FROM_EXPR_V_x_SV_FROM_STD(                                 \
    Name, Params, Type, std::Name##_v<JLN_MP_UNPACK Values>)


#define JLN_MP_MAKE_TRAIT_VT_FROM_EXPR_V_x_S_FROM_STD(Name, Params, Type, ...) \
  namespace emp                                                                \
  {                                                                            \
    using std::Name;                                                           \
                                                                               \
    template<JLN_MP_UNPACK Params>                                             \
    JLN_MP_CONSTEXPR_VAR Type Name##_v = __VA_ARGS__;                          \
                                                                               \
    template<JLN_MP_UNPACK Params>                                             \
    using Name##_t = integral_constant<Type, __VA_ARGS__>;                     \
  }                                                                            \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, emp::integral_constant<Type, __VA_ARGS__>)


#define JLN_MP_MAKE_TRAIT_ST_FROM_EXPR_V_x_V_FROM_STD(Name, Params, Type, ...) \
  namespace emp                                                                \
  {                                                                            \
    using std::Name##_v;                                                       \
                                                                               \
    template<JLN_MP_UNPACK Params>                                             \
    struct Name : integral_constant<Type, __VA_ARGS__> {};                     \
                                                                               \
    template<JLN_MP_UNPACK Params>                                             \
    using Name##_t = integral_constant<Type, __VA_ARGS__>;                     \
  }                                                                            \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, emp::integral_constant<Type, __VA_ARGS__>)


#define JLN_MP_MAKE_TRAIT_ST_FROM_EXPR_T(Name, Params, ...) \
  namespace emp                                             \
  {                                                         \
    template<JLN_MP_UNPACK Params>                          \
    struct Name { using type = __VA_ARGS__; };              \
                                                            \
    template<JLN_MP_UNPACK Params>                          \
    using Name##_t = __VA_ARGS__;                           \
  }                                                         \
  JLN_MP_MAKE_TRAIT_NO_EMP(Name, Params, __VA_ARGS__)


#if JLN_MP_USE_LIBMS
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_T_FROM_EXPR_V_x_SV_FROM_STD
#elif JLN_MP_USE_LIBCXX
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_VT_FROM_EXPR_V_x_S_FROM_STD
#else
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V
#endif

#if JLN_MP_USE_LIBCXX
# define JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_T_FROM_EXPR_V_x_SV_FROM_STD
# define JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_VT_FROM_EXPR_V_x_S_FROM_STD
# define JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST JLN_MP_MAKE_TRAIT_ST_FROM_STD
#else
# define JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V
# define JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V
# define JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(Name, Params, Values) \
    JLN_MP_MAKE_TRAIT_ST_FROM_EXPR_T(Name, Params, __##Name Values)
#endif

#if JLN_MP_USE_LIBCXX
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_TS_STD_V_LIBCXX_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_T_FROM_EXPR_V_x_SV_FROM_STD
#elif JLN_MP_USE_LIBMS
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_TS_STD_V_LIBCXX_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_ST_FROM_EXPR_V_x_V_FROM_STD
#else
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_TS_STD_V_LIBCXX_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V
#endif

#if JLN_MP_USE_LIBCXX || JLN_MP_USE_LIBMS
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_T_FROM_EXPR_V_x_SV_FROM_STD
#else
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V
#endif

#if JLN_MP_USE_LIBCXX || JLN_MP_USE_LIBMS
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_LIBSTDCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_T_FROM_EXPR_V_x_SV_FROM_STD
#elif JLN_MP_USE_LIBSTDCXX
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_LIBSTDCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_VT_FROM_EXPR_V_x_S_FROM_STD
#else
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_LIBSTDCXX_BUILTIN_VT_STD_S_OTHER_F \
    JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V
#endif

#if JLN_MP_USE_LIBMS
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_T_FROM_EXPR_V_x_SV_FROM_STD
#else
# define JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F \
    JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V
#endif


#define JLN_MP_FN_PTR(...) static_cast<__VA_ARGS__>(nullptr)
#define JLN_MP_DECLVAL(...) static_cast<__VA_ARGS__(*)()>(nullptr)()
#define JLN_MP_DECLVAL_NOTHROW(...) static_cast<__VA_ARGS__(*)() noexcept>(nullptr)()


JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wdeprecated-volatile")

// TODO remove
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
    using enable_if_t = typename enable_if<B, T>::type;

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


  // not standard
  //@{
  namespace detail
  {
    // TODO requires { ... } ?
    template<class T, class = void>
    JLN_MP_CONSTEXPR_VAR bool is_referenceable_impl_v = false;

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_referenceable_impl_v<T, emp::void_t<T&>> = true;
  }
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_referenceable, (class T), bool,
    detail::is_referenceable_impl_v<T volatile const>);

  // TODO add_const_lvalue_reference ?
  // TODO is_trivially_relocatable
  //@}


  // https://en.cppreference.com/w/cpp/feature_test


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_const)
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_const, (class T), bool, __is_const(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_const, (class T), bool, (T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_const_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_const_v<T const> = true;
  }
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_const, (class T), bool, (T));
#endif
#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_const)
# define JLN_MP_IS_CONST_V(...) __is_const(__VA_ARGS__)
#else
# define JLN_MP_IS_CONST_V(...) emp::is_const_v<__VA_ARGS__>
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_volatile)
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_volatile, (class T), bool, __is_volatile(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_volatile, (class T), bool, (T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_volatile_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_volatile_v<T volatile> = true;
  }
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_volatile, (class T), bool, (T));
#endif


  // not standard
  //@{
  namespace detail
  {
    template<class T, bool = false>
    JLN_MP_CONSTEXPR_VAR bool is_complete_type_impl_v = !JLN_MP_IS_CONST_V(T);

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_complete_type_impl_v<T, !sizeof(T)> = true;
  }
  // is_complete_type = !is_unbounded_array && (is_function || when the expression sizeof(T) is valid)
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_complete_type, (class T), bool,
    detail::is_complete_type_impl_v<T volatile const>);


  namespace detail
  {
    template<class T, bool = false>
    JLN_MP_CONSTEXPR_VAR bool is_complete_or_unbounded_type_impl_v = !JLN_MP_IS_CONST_V(T);

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_complete_or_unbounded_type_impl_v<T, !sizeof(T)> = true;

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_complete_or_unbounded_type_impl_v<T[]> = true;

    template<>
    JLN_MP_CONSTEXPR_VAR bool is_complete_or_unbounded_type_impl_v<void volatile const> = true;
  }
  // is_complete_type = is_function || is_void || when the expression sizeof(T) is valid
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_complete_or_unbounded_type, (class T), bool,
    detail::is_complete_or_unbounded_type_impl_v<T volatile const>);
  //@}


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
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_trivial, (class T), bool, (T))
#endif


  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_trivially_copyable, (class T), bool, __is_trivially_copyable(T));


#if JLN_MP_USE_LIBMS || JLN_MP_USE_LIBCXX
# define JLN_MP_MAKE_TRAIT_D(Name, Params, Values) \
    JLN_MP_MAKE_TRAIT_T_FROM_EXPR_V_x_SV_FROM_STD(Name, Params, bool, __##Name Values)
#elif JLN_MP_USE_LIBSTDCXX
# define JLN_MP_MAKE_TRAIT_D(Name, Params, Values) \
    JLN_MP_MAKE_TRAIT_VT_FROM_EXPR_V_x_S_FROM_STD(Name, Params, bool, __##Name Values)
#else
# define JLN_MP_MAKE_TRAIT_D(Name, Params, Values) \
    JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(Name, Params, bool, __##Name Values)
#endif

#if JLN_MP_CXX_VERSION <= 17
  JLN_MP_MAKE_TRAIT_D(is_pod, (class T), (T));
#endif
  JLN_MP_MAKE_TRAIT_D(is_abstract, (class T), (T));
  JLN_MP_MAKE_TRAIT_D(is_aggregate, (class T), (T));
  JLN_MP_MAKE_TRAIT_D(is_base_of, (class T, class U), (T, U));
  JLN_MP_MAKE_TRAIT_D(is_class, (class T), (T));
  JLN_MP_MAKE_TRAIT_D(is_empty, (class T), (T));
  JLN_MP_MAKE_TRAIT_D(is_enum, (class T), (T));
  JLN_MP_MAKE_TRAIT_D(is_final, (class T), (T));
  JLN_MP_MAKE_TRAIT_D(is_polymorphic, (class T), (T));
  JLN_MP_MAKE_TRAIT_D(is_union, (class T), (T));

#undef JLN_MP_MAKE_TRAIT_D


#if ! JLN_MP_BUILTIN_HIDDEN_BY_LIBSTDCXX && JLN_MP_HAS_OPTIONAL_BUILTIN(__is_signed) && (!JLN_MP_INT128_AS_INTEGRAL || JLN_MP_CLANG_LIKE)
  JLN_MP_MAKE_TRAIT_T_FROM_EXPR_V_x_SV_FROM_STD(is_signed, (class T), bool, __is_signed(T));
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
    JLN_MP_DIAGNOSTIC_POP()
# endif // __is_signed

# if JLN_MP_INT128_AS_INTEGRAL
    template<> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v<volatile const JLN_MP_INT128_T> = true;
# endif
  }
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_signed, (class T), bool, detail::is_signed_impl_v<T volatile const>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_unsigned) && (!JLN_MP_INT128_AS_INTEGRAL || JLN_MP_CLANG_LIKE)
  JLN_MP_MAKE_TRAIT_T_FROM_EXPR_V_x_SV_FROM_STD(is_unsigned, (class T), bool, __is_unsigned(T));
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
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_unsigned, (class T), bool, detail::is_unsigned_impl_v<T volatile const>);
#endif


#if JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_bounded_array, (class T), bool, (T));
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_unbounded_array, (class T), bool, (T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_bounded_array_v = false;
    template<class T, std::size_t N> JLN_MP_CONSTEXPR_VAR bool is_bounded_array_v<T[N]> = true;

    template<class T> JLN_MP_CONSTEXPR_VAR bool is_unbounded_array_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_unbounded_array_v<T[]> = true;
  }
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_bounded_array, (class T), bool, (T));
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_unbounded_array, (class T), bool, (T));
#endif


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
  JLN_MP_MAKE_TRAIT_ST_FROM_S(add_lvalue_reference, (class T), detail::add_lvalue_reference_impl<T>);
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
  JLN_MP_MAKE_TRAIT_ST_FROM_S(add_rvalue_reference, (class T), detail::add_rvalue_reference_impl<T>);
#endif


  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_OTHER_F(
    has_unique_object_representations, (class T), bool, __has_unique_object_representations(T));


#if ! JLN_MP_BUILTIN_HIDDEN_BY_LIBSTDCXX && JLN_MP_HAS_OPTIONAL_BUILTIN(__is_void)
  #define JLN_MP_IS_VOID_V(...) __is_void(__VA_ARGS__)
  JLN_MP_MAKE_TRAIT_T_FROM_EXPR_V_x_SV_FROM_STD(is_void, (class T), bool, __is_void(T));
#elif JLN_MP_HAS_OPTIONAL_BUILTIN(__is_same)
  #define JLN_MP_IS_VOID_V(...) \
    __is_same(volatile const __VA_ARGS__, volatile const void)
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_void, (class T), bool, JLN_MP_IS_VOID_V(T));
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
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_void, (class T), bool, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_same)
  #define JLN_MP_IS_NULL_POINTER_V(...) \
    __is_same(__VA_ARGS__ volatile const, decltype(nullptr) volatile const)
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_null_pointer, (class T), bool, JLN_MP_IS_NULL_POINTER_V(T));
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
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_null_pointer, (class T), bool, (T));
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
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_integral, (class T), bool, detail::is_integral_impl_v<T volatile const>);
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
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_floating_point, (class T), bool, detail::is_floating_point_impl_v<T volatile const>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_array)
  #define JLN_MP_IS_ARRAY_V(...) __is_array(__VA_ARGS__)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_array, (class T), bool, __is_array(T));
#elif JLN_MP_USE_LIBMS
  #define JLN_MP_IS_ARRAY_V(...) emp::is_array_v<__VA_ARGS__>
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_array, (class T), bool, (T));
#else
  #define JLN_MP_IS_ARRAY_V(...) emp::is_array_v<__VA_ARGS__>
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_array_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_array_v<T[]> = true;
    template<class T, std::size_t N> JLN_MP_CONSTEXPR_VAR bool is_array_v<T[N]> = true;
  }
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_array, (class T), bool, (T));
#endif


#if ! JLN_MP_BUILTIN_HIDDEN_BY_LIBSTDCXX && JLN_MP_HAS_OPTIONAL_BUILTIN(__is_pointer)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_pointer, (class T), bool, __is_pointer(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_pointer, (class T), bool, (T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_pointer_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_pointer_v<T*> = true;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_pointer_v<T* const> = true;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_pointer_v<T* volatile> = true;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_pointer_v<T* volatile const> = true;
  }
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_pointer, (class T), bool, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_lvalue_reference)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_lvalue_reference, (class T), bool, __is_lvalue_reference(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_lvalue_reference, (class T), bool, (T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_lvalue_reference_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_lvalue_reference_v<T&> = true;
  }
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_lvalue_reference, (class T), bool, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_rvalue_reference)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_rvalue_reference, (class T), bool, __is_rvalue_reference(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_rvalue_reference, (class T), bool, (T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_rvalue_reference_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_rvalue_reference_v<T&&> = true;
  }
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_rvalue_reference, (class T), bool, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_reference)
  #define JLN_MP_IS_REFERENCE_V(...) __is_reference(__VA_ARGS__)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_reference, (class T), bool, __is_reference(T));
#elif JLN_MP_USE_LIBMS
  #define JLN_MP_IS_REFERENCE_V(...) std::is_reference_v<__VA_ARGS__>
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_reference, (class T), bool, (T));
#else
  #define JLN_MP_IS_REFERENCE_V(...) emp::is_reference_v<__VA_ARGS__>
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_reference_v = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_reference_v<T&> = true;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_reference_v<T&&> = true;
  }
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_reference, (class T), bool, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_function)
  #define JLN_MP_IS_FUNCTION_V(...) __is_function(__VA_ARGS__)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_function, (class T), bool, __is_function(T));
#else
  #define JLN_MP_IS_FUNCTION_V(...) emp::is_function_v<__VA_ARGS__>
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_function_v = !JLN_MP_IS_CONST_V(T const);
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_function_v<T&> = false;
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_function_v<T&&> = false;
  }
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_function, (class T), bool, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_member_object_pointer)
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_TS_STD_V_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_member_object_pointer, (class T), bool, __is_member_object_pointer(T));
#else
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool is_member_object_pointer_v = false;

    // TODO !is_function_v<T> -> is_const_v<T const> ?

    template<class T, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_object_pointer_v<T C::*> = !is_function_v<T>;

    template<class T, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_object_pointer_v<T C::* const> = !is_function_v<T>;

    template<class T, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_object_pointer_v<T C::* volatile> = !is_function_v<T>;

    template<class T, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_object_pointer_v<T C::* volatile const> = !is_function_v<T>;
  }
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_member_object_pointer, (class T), bool, (T));
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
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_member_function_pointer, (class T), bool, (T));
#endif


#if ! JLN_MP_BUILTIN_HIDDEN_BY_LIBSTDCXX && JLN_MP_HAS_OPTIONAL_BUILTIN(__is_arithmetic)
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_arithmetic, (class T), bool, __is_arithmetic(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_arithmetic, (class T), bool, (T));
#else
  // TODO or *_FROM_EMP_V
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_arithmetic, (class T), bool,
    emp::is_integral_v<T> || emp::is_floating_point_v<T>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_fundamental)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_fundamental, (class T), bool, __is_fundamental(T));
#elif JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_fundamental, (class T), bool, (T));
#else
  // TODO or *_FROM_EMP_V
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_fundamental, (class T), bool,
    emp::is_arithmetic_v<T> || JLN_MP_IS_VOID_V(T) || JLN_MP_IS_NULL_POINTER_V(T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_object)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_object, (class T), bool, __is_object(T));
#else
  // TODO or *_FROM_EMP_V
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_object, (class T), bool,
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
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_member_pointer, (class T), bool, (T));
#endif


#if ! JLN_MP_BUILTIN_HIDDEN_BY_LIBSTDCXX && JLN_MP_HAS_OPTIONAL_BUILTIN(__is_scalar)
  #define JLN_MP_IS_SCALAR_V(...) __is_scalar(__VA_ARGS__)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_scalar, (class T), bool, __is_scalar(T));
#else
  #define JLN_MP_IS_SCALAR_V(...) /*emp::*/is_scalar_v<__VA_ARGS__>
  // TODO or *_FROM_EMP_V
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_scalar, (class T), bool,
    emp::is_arithmetic_v<T> || __is_enum(T) || emp::is_pointer_v<T>
    || emp::is_member_pointer_v<T> || JLN_MP_IS_NULL_POINTER_V(T));
#endif


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


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_compound)
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_BUILTIN_T_STD_SV_OTHER_F(
    is_compound, (class T), bool, __is_compound(T));
#else
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_compound, (class T), bool, !emp::is_fundamental_v<T>);
#endif


#if JLN_MP_USE_OPTIONAL_BUILTIN_EXISTS_WITH_MSVC(__is_convertible_to)
  #define JLN_MP_IS_CONVERTIBLE_V(...) __is_convertible_to(__VA_ARGS__)
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_convertible, (class From, class To), bool, __is_convertible_to(From, To));
#elif JLN_MP_FEATURE_CONCEPTS
  // TODO slow with clang ?
  #define JLN_MP_IS_CONVERTIBLE_V(...) emp::is_convertible_v<__VA_ARGS__>
  namespace detail
  {
    template<class To, bool v>
    JLN_MP_CONSTEXPR_VAR bool is_convertible_impl_v = v;

    // template<class To>
    // JLN_MP_CONSTEXPR_VAR bool is_convertible_impl_v<To, true>
    //   = !JLN_MP_IS_ARRAY_V(To) && !JLN_MP_IS_FUNCTION_V(To);

    // !is_array

    template<class To>
    JLN_MP_CONSTEXPR_VAR bool is_convertible_impl_v<To[], true> = false;

    template<class To, std::size_t N>
    JLN_MP_CONSTEXPR_VAR bool is_convertible_impl_v<To[N], true> = false;

    // !is_function

    template<class To>
    JLN_MP_CONSTEXPR_VAR bool is_convertible_impl_v<To, true> = JLN_MP_IS_CONST_V(To const);

    template<class To>
    JLN_MP_CONSTEXPR_VAR bool is_convertible_impl_v<To&, true> = true;

    template<class To>
    JLN_MP_CONSTEXPR_VAR bool is_convertible_impl_v<To&&, true> = true;
  }
  namespace emp
  {
    template<class From, class To>
    JLN_MP_CONSTEXPR_VAR bool is_convertible_v = detail::is_convertible_impl_v<
      To, requires{ JLN_MP_FN_PTR(void(*)(To))(JLN_MP_DECLVAL(From&&)); }
    >;

    template<>
    JLN_MP_CONSTEXPR_VAR bool is_convertible_v<void, void> = true;
  }
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_convertible, (class From, class To), bool, (From, To));
#else
  #define JLN_MP_IS_CONVERTIBLE_V(...) detail::is_convertible_impl_v<__VA_ARGS__>
  namespace detail
  {
    template<class From, class To, class = void>
    JLN_MP_CONSTEXPR_VAR bool is_convertible_impl_v = false;

    template<>
    JLN_MP_CONSTEXPR_VAR bool is_convertible_impl_v<void, void> = true;

    // TODO is_complete_or_unbounded
    template<class From, class To>
    JLN_MP_CONSTEXPR_VAR bool is_convertible_impl_v<
      From, To,
      decltype(JLN_MP_FN_PTR(void(*)(To))(JLN_MP_DECLVAL(From&&)))
    > = !JLN_MP_IS_ARRAY_V(To) && !JLN_MP_IS_FUNCTION_V(To);
  }
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_convertible, (class From, class To), bool,
    detail::is_convertible_impl_v<From, To>);
#endif


  namespace detail
  {
    template<bool>
    struct is_nothrow_convertible_impl
    {
      template<class From, class To>
      static constexpr bool v
        = noexcept(JLN_MP_FN_PTR(void(*)(To)noexcept)(JLN_MP_DECLVAL_NOTHROW(From&&)));
    };

    template<>
    struct is_nothrow_convertible_impl<false>
    {
      // TODO sharing alias or simple is_nothrow_convertible_impl_v<bool, From, To>
      template<class From, class To>
      static constexpr bool v = false;
    };
  }
  namespace emp
  {
    template<class From, class To>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_convertible_v
      = detail::is_nothrow_convertible_impl<JLN_MP_IS_CONVERTIBLE_V(From, To)>
        ::template v<From, To>;

    template<class From>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_convertible_v<From, void> = true;
  }
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_nothrow_convertible, (class From, class To), bool, (From, To));


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__is_scoped_enum)
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_scoped_enum, (class T), bool, __is_scoped_enum(T));
#else
  // TODO or *_FROM_EMP_V
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_scoped_enum, (class T), bool,
      // TODO requires { int(*static_cast<T*>(nullptr)); }
    __is_enum(T) && !JLN_MP_IS_CONVERTIBLE_V(T, int));
#endif


  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_FROM_LIBMS_BUILTIN_T_STD_SV_LIBCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_constructible, (class T, class... Args), bool, __is_constructible(T, Args...));


  // TODO is_complete_or_unbounded
#if JLN_MP_FEATURE_CONCEPTS
  // T() does not work with when T = U[n]
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_default_constructible, (class T), bool, requires { T{}; });
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


#if JLN_MP_USE_OPTIONAL_BUILTIN_EXISTS_WITH_MSVC(__is_assignable)
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
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_assignable, (class T, class U), bool, JLN_MP_IS_ASSIGNABLE_V(T, U));
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_copy_assignable, (class T), bool, JLN_MP_IS_COPY_ASSIGNABLE_V(T));
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_move_assignable, (class T), bool, JLN_MP_IS_MOVE_ASSIGNABLE_V(T));
#endif


#if JLN_MP_USE_OPTIONAL_BUILTIN_EXISTS_WITH_MSVC(__is_nothrow_assignable)
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
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_nothrow_assignable, (class T, class U), bool,
    detail::is_nothrow_assignable_impl_v<T, U>);
  // TODO is_complete_or_unbounded
  // TODO use JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V ?
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_nothrow_copy_assignable, (class T), bool, (T));
  // TODO is_complete_or_unbounded
  // TODO use JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V ?
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_nothrow_move_assignable, (class T), bool, (T));
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


#if JLN_MP_USE_OPTIONAL_BUILTIN_EXISTS_WITH_MSVC(__is_destructible)
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
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_destructible, (class T), bool,
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
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_trivially_destructible, (class T), bool,
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
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_trivially_destructible, (class T), bool, (T));
  #define JLN_MP_IS_TRIVIALLY_DESTRUCTIBLE_V(...) emp::is_trivially_destructible_v<__VA_ARGS__>
# endif
#endif


#if JLN_MP_USE_OPTIONAL_BUILTIN_EXISTS_WITH_MSVC(__is_nothrow_destructible)
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
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_nothrow_destructible, (class T), bool,
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
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_implicit_lifetime, (class T), bool, (T));
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
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_swappable, (class T), bool, (T));
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_nothrow_swappable, (class T), bool, (T));
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_swappable_with, (class T, class U), bool, (T, U));
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(is_nothrow_swappable_with, (class T, class U), bool, (T, U));


#if JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__has_virtual_destructor)
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(has_virtual_destructor, (class T), bool, __has_virtual_destructor(T));
#elif ! JLN_MP_NO_STL
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(has_virtual_destructor, (class T), bool, (T));
#else
  // this implementation is not compliant and fails with classes and unions
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(has_virtual_destructor, (class T), bool, false);
#endif


  JLN_MP_MAKE_TRAIT_FROM_LIBMS_LIBCXX_BUILTIN_T_STD_SV_LIBSTDCXX_BUILTIN_VT_STD_S_OTHER_F(
    is_same, (class T, class U), bool, JLN_MP_IS_SAME_V(T, U));


// TODO no stl
#if ! JLN_MP_NO_STL && defined(__cpp_lib_is_layout_compatible) && __cpp_lib_is_layout_compatible >= 201907L
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_layout_compatible, (class T, class U), bool, (T, U));
#elif JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_layout_compatible)
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(
    is_layout_compatible, (class T, class U), bool, __is_layout_compatible(T, U));
#else
  // TODO is_complete_or_unbounded
  // TODO https://en.cppreference.com/w/cpp/language/data_members#Standard-layout
  // TODO https://en.cppreference.com/w/cpp/language/classes#Standard-layout_class
  // A signed integer type and its unsigned counterpart are not layout-compatible. char is layout-compatible with neither signed char nor unsigned char.
  // Similar types are not layout-compatible if they are not the same type after ignoring top-level cv-qualification.
  // An enumeration type and its underlying type are not layout-compatible.
  // Array types of layout-compatible but different element types (ignoring cv-qualification) are not layout-compatible, even if they are of equal length.
#endif


#if JLN_MP_USE_OPTIONAL_BUILTIN_EXISTS_WITH_MSVC(__is_pointer_interconvertible_base_of)
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(is_pointer_interconvertible_base_of,
    (class Base, class Derived), bool, __is_pointer_interconvertible_base_of(Base, Derived));
#elif !JLN_MP_NO_STL && defined(__cpp_lib_is_pointer_interconvertible) && __cpp_lib_is_pointer_interconvertible >= 201907L
  JLN_MP_MAKE_TRAIT_T_FROM_EXPR_V_x_SV_FROM_STD(is_pointer_interconvertible_base_of,
    (class Base, class Derived), bool, emp::is_pointer_interconvertible_base_of_v<Base, Derived>);
#endif


  namespace emp
  {
#if !JLN_MP_NO_STL && defined(__cpp_lib_is_pointer_interconvertible) && __cpp_lib_is_pointer_interconvertible >= 201907L
    using std::is_pointer_interconvertible_with_class;
#else
    template <class C, class Mem>
    constexpr bool is_pointer_interconvertible_with_class(Mem C::* m) noexcept
    {
#if JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_pointer_interconvertible_with_class)
      return __is_pointer_interconvertible_with_class(C, m);
#elif JLN_MP_HAS_BUILTIN(__builtin_is_pointer_interconvertible_with_class)
      return __builtin_is_pointer_interconvertible_with_class(m);
#else
      (void)m;
      return false;
#endif
    }
#endif
  }


  // TODO LIBMS || LIBCPP -> use std::
  // TODO is_complete_or_unbounded
#if JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(alignment_of, (class T), std::size_t, (T));
#else
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(alignment_of, (class T), std::size_t, alignof(T));
#endif


#if JLN_MP_USE_LIBMS
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(rank, (class T), std::size_t, (T));
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
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(rank, (class T), std::size_t, (T));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__array_extent)
  namespace emp
  {
    template<class T, unsigned Dim = 0>
    JLN_MP_CONSTEXPR_VAR std::size_t extent_c_v = __array_extent(T, Dim);

    template<class T, class Dim = number<0>>
    JLN_MP_CONSTEXPR_VAR std::size_t extent_v = __array_extent(T, Dim::value);

    template<class T, unsigned Dim = 0>
    using extent_c_t = emp::integral_constant<std::size_t, __array_extent(T, Dim)>;

    template<class T, class Dim = number<0>>
    using extent_t = emp::integral_constant<std::size_t, __array_extent(T, Dim::value)>;
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
    using extent_c_t = emp::integral_constant<std::size_t, extent_c_v<T, Dim>>;

    template<class T, class Dim = number<0>>
    using extent_t = emp::integral_constant<std::size_t, extent_c_v<T, Dim::value>>;
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


#if defined(__cpp_lib_is_invocable) && __cpp_lib_is_invocable >= 201703L
  // TODO https://en.cppreference.com/w/cpp/utility/functional (C++23)
  // TODO
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_invocable, (class Fn, class... Args), bool, (Fn, Args...));
  // TODO
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_invocable_r, (class R, class Fn, class... Args), bool, (R, Fn, Args...));
  // TODO
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_nothrow_invocable, (class Fn, class... Args), bool, (Fn, Args...));
  // TODO
  JLN_MP_MAKE_TRAIT_T_FROM_STD_V_x_SV_FROM_STD(is_nothrow_invocable_r, (class R, class Fn, class... Args), bool, (R, Fn, Args...));
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_const)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(remove_const, (class T), (T));
#elif ! JLN_MP_NO_STL
  JLN_MP_MAKE_TRAIT_ST_FROM_STD(remove_const, (class T), (T));
#else
  namespace emp
  {
    template<class T> struct remove_const { using type = T; };
    template<class T> struct remove_const<T const> { using type = T; };
  }
  JLN_MP_MAKE_TRAIT_T_FROM_S(remove_const, (class T), emp::remove_const<T const>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_volatile)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(remove_volatile, (class T), (T));
#elif ! JLN_MP_NO_STL
  JLN_MP_MAKE_TRAIT_ST_FROM_STD(remove_volatile, (class T), (T));
#else
  namespace emp
  {
    template<class T> struct remove_volatile { using type = T; };
    template<class T> struct remove_volatile<T volatile> { using type = T; };
  }
  JLN_MP_MAKE_TRAIT_T_FROM_S(remove_volatile, (class T), emp::remove_volatile<T volatile>);
#endif


#if ! JLN_MP_BUILTIN_HIDDEN_BY_LIBSTDCXX && JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_cv)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(remove_cv, (class T), (T));
#elif JLN_MP_HAS_BUILTIN(__remove_const) && JLN_MP_HAS_BUILTIN(__remove_volatile)
  JLN_MP_MAKE_TRAIT_ST_FROM_EXPR_T(remove_cv, (class T), __remove_const(__remove_volatile(T)));
#elif JLN_MP_USE_LIBSTDCXX
  JLN_MP_MAKE_TRAIT_ST_FROM_STD(remove_cv, (class T), (T));
#else
  namespace emp
  {
    template<class T> struct remove_cv { using type = T; };
    template<class T> struct remove_cv<T const> { using type = T; };
    template<class T> struct remove_cv<T volatile> { using type = T; };
    template<class T> struct remove_cv<T volatile const> { using type = T; };
  }
  JLN_MP_MAKE_TRAIT_T_FROM_S(remove_cv, (class T), emp::remove_cv<T volatile const>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_extents)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(remove_extents, (class T), (T));
#elif ! JLN_MP_NO_STL
  JLN_MP_MAKE_TRAIT_ST_FROM_STD(remove_extent, (class T), (T));
#else
  namespace emp
  {
    template<class T> struct remove_extent { using type = T; };
    template<class T> struct remove_extent<T[]> { using type = T; };
    template<class T, std::size_t N> struct remove_extent<T[N]> { using type = T; };
  }
  JLN_MP_MAKE_TRAIT_T_FROM_S(remove_extent, (class T), emp::remove_extent<T>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_all_extents)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(remove_all_extents, (class T), (T));
#elif ! JLN_MP_NO_STL
  JLN_MP_MAKE_TRAIT_ST_FROM_STD(remove_all_extents, (class T), (T));
#else
  namespace emp
  {
    template<class T> struct remove_all_extents { using type = T; };
    template<class T> struct remove_all_extents<T[]> : remove_all_extents<T> {};
    template<class T, std::size_t N> struct remove_all_extents<T[N]> : remove_all_extents<T> {};
  }
  JLN_MP_MAKE_TRAIT_T_FROM_S(remove_all_extents, (class T), emp::remove_all_extents<T>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_pointer)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_FROM_LIBCXX_STD_ST_OTHER_BUILTIN_ST(remove_pointer, (class T), (T));
#elif ! JLN_MP_NO_STL
  JLN_MP_MAKE_TRAIT_ST_FROM_STD(remove_pointer, (class T), (T));
#else
  namespace emp
  {
    template<class T> struct remove_pointer { using type = T; };
    template<class T> struct remove_pointer<T*> { using type = T; };
    template<class T> struct remove_pointer<T* const> { using type = T; };
    template<class T> struct remove_pointer<T* volatile> { using type = T; };
    template<class T> struct remove_pointer<T* volatile const> { using type = T; };
  }
  JLN_MP_MAKE_TRAIT_T_FROM_S(remove_pointer, (class T), emp::remove_pointer<T>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_reference_t)
  // TODO use builtin / std::... with macro
# if JLN_MP_USE_LIBCXX
  JLN_MP_MAKE_TRAIT_ST_FROM_STD(remove_reference, (class T), (T));
# else
  JLN_MP_MAKE_TRAIT_ST_FROM_EXPR_T(remove_reference, (class T), __remove_reference_t(T))
# endif
#elif ! JLN_MP_NO_STL
  JLN_MP_MAKE_TRAIT_ST_FROM_STD(remove_reference, (class T), (T));
#else
  namespace emp
  {
    template<class T> struct remove_reference { using type = T; };
    template<class T> struct remove_reference<T&> { using type = T; };
    template<class T> struct remove_reference<T&&> { using type = T; };
  }
  JLN_MP_MAKE_TRAIT_T_FROM_S(remove_reference, (class T), emp::remove_reference<T>);
#endif


#if JLN_MP_HAS_OPTIONAL_BUILTIN(__remove_cvref)
  #define JLN_MP_REMOVE_CVREF_T(...) __remove_cvref(__VA_ARGS__)
  // TODO use builtin / std::... with macro
  JLN_MP_MAKE_TRAIT_ST_FROM_EXPR_T(remove_cvref, (class T), __remove_cvref(T));
#else
  #define JLN_MP_REMOVE_CVREF_T(...) typename emp::remove_cvref<__VA_ARGS__>::type
  namespace emp
  {
    template<class T> struct remove_cvref { using type = T; };
    template<class T> struct remove_cvref<T&> { using type = T; };
    template<class T> struct remove_cvref<T&&> { using type = T; };
    template<class T> struct remove_cvref<T const> { using type = T; };
    template<class T> struct remove_cvref<T const&> { using type = T; };
    template<class T> struct remove_cvref<T const&&> { using type = T; };
    template<class T> struct remove_cvref<T volatile> { using type = T; };
    template<class T> struct remove_cvref<T volatile&> { using type = T; };
    template<class T> struct remove_cvref<T volatile&&> { using type = T; };
    template<class T> struct remove_cvref<T volatile const> { using type = T; };
    template<class T> struct remove_cvref<T volatile const&> { using type = T; };
    template<class T> struct remove_cvref<T volatile const&&> { using type = T; };
  }
  JLN_MP_MAKE_TRAIT_T_FROM_S(remove_cvref, (class T), emp::remove_cvref<T>);
#endif


#if JLN_MP_HAS_BUILTIN(__reference_constructs_from_temporary)
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(reference_constructs_from_temporary,
      (class T, class U), bool, __reference_constructs_from_temporary(T, U));
#else
// __reference_binds_to_temporary + check are faster only when __reference_binds_to_temporary gives true.
// As this case is not the most common, it is disabled.
# if JLN_MP_HAS_BUILTIN(__reference_binds_to_temporary) && 0
  namespace detail
  {
# if JLN_MP_FEATURE_CONCEPTS
    template<bool v, class UnrefT, class T, class U, bool constructible = __is_constructible(T, U)>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_impl_v = v;

    template<class UnrefT, class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_impl_v<false, UnrefT, T, U, true>
      = requires { JLN_MP_FN_PTR(void(*)(UnrefT volatile const*))(JLN_MP_DECLVAL(U volatile const*)); };
# else
    template<bool v, class UnrefT, class T, class U, class = void>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_impl_v = v;

    template<class UnrefT, class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_impl_v<false, UnrefT, T, U,
      decltype(JLN_MP_FN_PTR(void(*)(UnrefT volatile const*))(JLN_MP_DECLVAL(U volatile const*)))
    > = __is_constructible(T, U);
# endif
  }
  namespace emp
  {
    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v = false;

    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v<T&, U>
      = detail::reference_constructs_from_temporary_impl_v<
        __reference_binds_to_temporary(T&, U), T, T&, U>;

    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v<T&&, U>
      = detail::reference_constructs_from_temporary_impl_v<
        __reference_binds_to_temporary(T&&, U), T, T&&, U>;

    // fast-path
    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v<T&, U&>
      = __reference_binds_to_temporary(T&, U&);

    // fast-path
    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v<T&&, U&>
      = __reference_binds_to_temporary(T&&, U&);

    // fast-path
    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v<T&, U&&>
      = __reference_binds_to_temporary(T&, U&&);

    // fast-path
    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v<T&&, U&&>
      = __reference_binds_to_temporary(T&&, U&&);
  }
#else
  namespace detail
  {
    template<bool Constructible, bool UIsRef>
    struct reference_constructs_from_temporary_impl
    {
      // TODO sharing
      template<class...>
      static constexpr bool v = false;
    };

    template<>
    struct reference_constructs_from_temporary_impl<true, false>
    {
      // TODO sharing
      template<class...>
      static constexpr bool v = true;
    };

# if ! JLN_MP_FEATURE_CONCEPTS
    template<class T, class U, class = void>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_impl_v = true;

    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_impl_v<
      T, U, decltype(JLN_MP_FN_PTR(void(*)(T*))(JLN_MP_DECLVAL(U*)))
    > = false;
# endif

    template<>
    struct reference_constructs_from_temporary_impl<true, true>
    {
      // T and U are cv qualified
      template<class T, class U>
# if JLN_MP_FEATURE_CONCEPTS
      static constexpr bool v = ! requires { JLN_MP_FN_PTR(void(*)(T*))(JLN_MP_DECLVAL(U*)); };
# else
      static constexpr bool v = reference_constructs_from_temporary_impl_v<T, U>;
# endif
    };
  }
  namespace emp
  {
    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v = false;

    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v<T&, U&> = false;

    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v<T&, U>
      = __is_constructible(T&, U);

    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v<T const&, U>
      = detail::reference_constructs_from_temporary_impl<
        __is_constructible(T const&, U), false
      >::template v<T volatile const, U volatile const>;

    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v<T const&, U&>
      = detail::reference_constructs_from_temporary_impl<
        __is_constructible(T const&, U&), true
      >::template v<T volatile const, U volatile const>;

    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v<T const&, U&&>
      = detail::reference_constructs_from_temporary_impl<
        __is_constructible(T const&, U&&), true
      >::template v<T volatile const, U volatile const>;

    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v<T&&, U>
      = detail::reference_constructs_from_temporary_impl<
        __is_constructible(T&&, U), false
      >::template v<T volatile const, U volatile const>;

    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v<T&&, U&>
      = detail::reference_constructs_from_temporary_impl<
        __is_constructible(T&&, U&), true
      >::template v<T volatile const, U volatile const>;

    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool reference_constructs_from_temporary_v<T&&, U&&>
      = detail::reference_constructs_from_temporary_impl<
        __is_constructible(T&&, U&&), true
      >::template v<T volatile const, U volatile const>;
  }
#endif
  // TODO If T is an lvalue reference type to a const- but not volatile-qualified object type or an rvalue reference type, both std::remove_reference_t<T> and std::remove_reference_t<U> shall be complete types, cv void, or an arrays of unknown bound; otherwise the behavior is undefined.
  JLN_MP_MAKE_TRAIT_ST_FROM_EMP_V(reference_constructs_from_temporary, (class T, class U), bool, (T, U));
#endif


#if JLN_MP_HAS_BUILTIN(__reference_converts_from_temporary)
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(reference_converts_from_temporary,
      (class T, class U), bool, __reference_converts_from_temporary(T, U));
#else
  // TODO don't work with explicit ctor-copyable type (gives true instead of false for <T&&, T> and <T const&, T>). How to check `T x = a` ?
  // TODO If T is an lvalue reference type to a const- but not volatile-qualified object type or an rvalue reference type, both std::remove_reference_t<T> and std::remove_reference_t<U> shall be complete types, cv void, or an arrays of unknown bound; otherwise the behavior is undefined.
  JLN_MP_MAKE_TRAIT_SVT_FROM_EXPR_V(reference_converts_from_temporary,
    (class T, class U), bool, emp::reference_constructs_from_temporary_v<T, U>);
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
  JLN_MP_MAKE_TRAIT_ST_FROM_S(add_pointer, (class T), detail::add_pointer_impl<T>);
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
  JLN_MP_MAKE_TRAIT_NO_EMP(add_cv, (class T), T volatile const);
  JLN_MP_MAKE_TRAIT_NO_EMP(add_const, (class T), T const);
  JLN_MP_MAKE_TRAIT_NO_EMP(add_volatile, (class T), T volatile);


  // not standard
  //@{
  namespace detail
  {
    template<class From> struct copy_cv_impl : identity {};
    template<class From> struct copy_cv_impl<From const> : add_const<> {};
    template<class From> struct copy_cv_impl<From volatile> : add_volatile<> {};
    template<class From> struct copy_cv_impl<From volatile const> : add_cv<> {};

    template<class From> struct copy_cvref_impl : identity {};
    template<class From> struct copy_cvref_impl<From const> : add_const<> {};
    template<class From> struct copy_cvref_impl<From volatile> : add_volatile<> {};
    template<class From> struct copy_cvref_impl<From volatile const> : add_cv<> {};

    template<class From> struct copy_cvref_impl<From&> : add_lvalue_reference<> {};
#if JLN_MP_HAS_OPTIONAL_BUILTIN(__add_lvalue_reference)
    template<class From> struct copy_cvref_impl<From const&> { template<class To> using f = __add_lvalue_reference(To const); };
    template<class From> struct copy_cvref_impl<From volatile&> { template<class To> using f = __add_lvalue_reference(To volatile); };
    template<class From> struct copy_cvref_impl<From volatile const&> { template<class To> using f = __add_lvalue_reference(To volatile const); };
#else
    struct copy_const_lref    { template<class T> using f = typename add_lvalue_reference_impl<T const>::type; };
    struct copy_volatile_lref { template<class T> using f = typename add_lvalue_reference_impl<T volatile>::type; };
    struct copy_cv_lref       { template<class T> using f = typename add_lvalue_reference_impl<T volatile const>::type; };

    template<class From> struct copy_cvref_impl<From const&> : copy_const_lref {};
    template<class From> struct copy_cvref_impl<From volatile&> : copy_volatile_lref {};
    template<class From> struct copy_cvref_impl<From volatile const&> : copy_cv_lref {};
#endif

    template<class From> struct copy_cvref_impl<From&&> : add_rvalue_reference<> {};
#if JLN_MP_HAS_OPTIONAL_BUILTIN(__add_rvalue_reference)
    template<class From> struct copy_cvref_impl<From const&&> { template<class To> using f = __add_rvalue_reference(To const); };
    template<class From> struct copy_cvref_impl<From volatile&&> { template<class To> using f = __add_rvalue_reference(To volatile); };
    template<class From> struct copy_cvref_impl<From volatile const&&> { template<class To> using f = __add_rvalue_reference(To volatile const); };
#else
    struct copy_const_rref    { template<class T> using f = typename add_rvalue_reference_impl<T const>::type; };
    struct copy_volatile_rref { template<class T> using f = typename add_rvalue_reference_impl<T volatile>::type; };
    struct copy_cv_rref       { template<class T> using f = typename add_rvalue_reference_impl<T volatile const>::type; };

    template<class From> struct copy_cvref_impl<From const&&> : copy_const_rref {};
    template<class From> struct copy_cvref_impl<From volatile&&> : copy_volatile_rref {};
    template<class From> struct copy_cvref_impl<From volatile const&&> : copy_cv_rref {};
#endif
  }
  namespace emp
  {
    template<class From, class To>
    using copy_cv_t = typename detail::copy_cv_impl<From>::template f<To>;

    template<class From, class To>
    using copy_cvref_t = typename detail::copy_cvref_impl<From>::template f<To>;
  }
  //@}


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

#if JLN_MP_INT128_AS_INTEGRAL
    template<>
    struct mk_min_rank<-6>
    {
      using signed_type = JLN_MP_INT128_T;
      using unsigned_type = JLN_MP_UINT128_T;
    };
#endif

    template<std::size_t n>
    struct select_min_rank : mk_min_rank<
      n <= 1 ? -1 :
      n <= sizeof(short) ? -2 :
      n <= sizeof(int) ? -3 :
      n <= sizeof(long) ? -4 :
      n <= sizeof(long long) ? -5 :
#if JLN_MP_INT128_AS_INTEGRAL
      n <= sizeof(JLN_MP_INT128_T) ? -6 :
#endif
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

# define JLN_MP_MK_SIGNED_CV
#else
# define JLN_MP_MK_SIGNED_CV const volatile
#endif

    // If T is signed or unsigned char, short, int, long, long long,
    // the signed type from this list corresponding to T is provided.
    template<> struct make_signed<JLN_MP_MK_SIGNED_CV char>          { using type = signed char; };
    template<> struct make_signed<JLN_MP_MK_SIGNED_CV unsigned char> { using type = signed char; };
    template<> struct make_signed<JLN_MP_MK_SIGNED_CV   signed char> { using type = signed char; };
    template<> struct make_signed<JLN_MP_MK_SIGNED_CV unsigned short> { using type = signed short; };
    template<> struct make_signed<JLN_MP_MK_SIGNED_CV   signed short> { using type = signed short; };
    template<> struct make_signed<JLN_MP_MK_SIGNED_CV unsigned int> { using type = signed int; };
    template<> struct make_signed<JLN_MP_MK_SIGNED_CV   signed int> { using type = signed int; };
    template<> struct make_signed<JLN_MP_MK_SIGNED_CV unsigned long> { using type = signed long; };
    template<> struct make_signed<JLN_MP_MK_SIGNED_CV   signed long> { using type = signed long; };
    template<> struct make_signed<JLN_MP_MK_SIGNED_CV unsigned long long> { using type = signed long long; };
    template<> struct make_signed<JLN_MP_MK_SIGNED_CV   signed long long> { using type = signed long long; };

#if JLN_MP_INT128_AS_INTEGRAL
    template<> struct make_signed<JLN_MP_MK_SIGNED_CV JLN_MP_INT128_T> { using type = JLN_MP_INT128_T; };
    template<> struct make_signed<JLN_MP_MK_SIGNED_CV JLN_MP_UINT128_T> { using type = JLN_MP_INT128_T; };
#endif

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
    template<> struct make_unsigned<JLN_MP_MK_SIGNED_CV char>          { using type = unsigned char; };
    template<> struct make_unsigned<JLN_MP_MK_SIGNED_CV unsigned char> { using type = unsigned char; };
    template<> struct make_unsigned<JLN_MP_MK_SIGNED_CV   signed char> { using type = unsigned char; };
    template<> struct make_unsigned<JLN_MP_MK_SIGNED_CV unsigned short> { using type = unsigned short; };
    template<> struct make_unsigned<JLN_MP_MK_SIGNED_CV   signed short> { using type = unsigned short; };
    template<> struct make_unsigned<JLN_MP_MK_SIGNED_CV unsigned int> { using type = unsigned int; };
    template<> struct make_unsigned<JLN_MP_MK_SIGNED_CV   signed int> { using type = unsigned int; };
    template<> struct make_unsigned<JLN_MP_MK_SIGNED_CV unsigned long> { using type = unsigned long; };
    template<> struct make_unsigned<JLN_MP_MK_SIGNED_CV   signed long> { using type = unsigned long; };
    template<> struct make_unsigned<JLN_MP_MK_SIGNED_CV unsigned long long> { using type = unsigned long long; };
    template<> struct make_unsigned<JLN_MP_MK_SIGNED_CV   signed long long> { using type = unsigned long long; };

#if JLN_MP_INT128_AS_INTEGRAL
    template<> struct make_unsigned<JLN_MP_MK_SIGNED_CV JLN_MP_INT128_T> { using type = JLN_MP_UINT128_T; };
    template<> struct make_unsigned<JLN_MP_MK_SIGNED_CV JLN_MP_UINT128_T> { using type = JLN_MP_UINT128_T; };
#endif

#undef JLN_MP_MK_SIGNED_CV

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
  }
#if JLN_MP_CLANG || JLN_MP_MSVC
  namespace emp
  {
    using detail::make_signed;
    using detail::make_unsigned;
  }
  JLN_MP_MAKE_TRAIT_T_FROM_S(make_signed, (class T), detail::make_signed<T>);
  JLN_MP_MAKE_TRAIT_T_FROM_S(make_unsigned, (class T), detail::make_unsigned<T>);
#else
  namespace emp
  {
    template<class T> using make_signed_t
      = typename detail::copy_cv_impl<T>
      ::template f<typename detail::make_signed<T volatile const>::type>;

    template<class T> using make_unsigned_t
      = typename detail::copy_cv_impl<T>
      ::template f<typename detail::make_unsigned<T volatile const>::type>;

    template<class T> struct make_signed { using type = make_signed_t<T>; };
    template<class T> struct make_unsigned { using type = make_unsigned_t<T>; };
  }
  JLN_MP_MAKE_TRAIT_NO_EMP(make_signed, (class T), emp::make_signed_t<T>);
  JLN_MP_MAKE_TRAIT_NO_EMP(make_unsigned, (class T), emp::make_unsigned_t<T>);
#endif


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
#if JLN_MP_HAS_OPTIONAL_BUILTIN(__add_pointer)
    template<class T> struct decay_maybe_func { using type = __add_pointer(T); };
#else
    template<class T> struct decay_maybe_func : add_pointer_impl<T> {};
#endif
    // not is_function
    template<class T> struct decay_maybe_func<T volatile const> { using type = T; };
  }
  namespace emp
  {
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
  JLN_MP_MAKE_TRAIT_T_FROM_S(decay, (class T), emp::decay<T>);


#if ! JLN_MP_NO_STL && defined(__cpp_lib_unwrap_ref) && __cpp_lib_unwrap_ref >= 201811L
  JLN_MP_MAKE_TRAIT_ST_FROM_STD(unwrap_reference, (class T), (T));
#else
  namespace emp
  {
    template<class T> struct unwrap_reference { using type = T; };
    #if ! JLN_MP_NO_STL
    template<class T> struct unwrap_reference<std::reference_wrapper<T>> { using type = T&; };
    #endif
  }
  JLN_MP_MAKE_TRAIT_T_FROM_S(unwrap_reference, (class T), emp::unwrap_reference<T>);
#endif


  namespace emp
  {
    template<class T> struct unwrap_ref_decay : unwrap_reference<decay_t<T>> {};
    template<class T> using unwrap_ref_decay_t = unwrap_reference_t<decay_t<T>>;
  }
  JLN_MP_MAKE_TRAIT_NO_EMP(unwrap_ref_decay, (class T), emp::unwrap_ref_decay_t<T>);


  namespace detail
  {
    struct invoke_caller_deref
    {
      template<class T>
      using f = decltype(*JLN_MP_DECLVAL(T));
    };

    struct invoke_caller_unwrap
    {
      template<class T>
      using f = decltype(JLN_MP_DECLVAL(T).get());
    };

    template<class Td, bool>
    struct invoke_caller_impl;

    template<class Td>
    struct invoke_caller_impl<Td, true>
      : identity
    {};

    template<class Td>
    struct invoke_caller_impl<Td, false>
      : invoke_caller_deref
    {};

    // TODO no stl
    template<class Td>
    struct invoke_caller_impl<std::reference_wrapper<Td>, false>
      : invoke_caller_unwrap
    {};

    template<class C, class T, class Td = typename emp::decay<T>::type>
    using invoke_caller = typename invoke_caller_impl<Td, __is_base_of(C, Td)>::template f<T&&>;

    template<class, bool>
    struct invoke_mem_fn;

    template<class C>
    struct invoke_mem_fn<C, true>
    {
      template<class F, class T, class... Args>
      using f = decltype((JLN_MP_DECLVAL(invoke_caller<C, T>).*JLN_MP_DECLVAL(F))(JLN_MP_DECLVAL(Args&&)...));
    };

    template<class C>
    struct invoke_mem_fn<C, false>
    {
      template<class F, class T>
      using f = decltype(JLN_MP_DECLVAL(invoke_caller<C, T>).*JLN_MP_DECLVAL(F));
    };

    struct invoke_fn
    {
      template<class F, class... Args>
      using f = decltype(JLN_MP_DECLVAL(F&&)(JLN_MP_DECLVAL(Args&&)...));
    };

    template<class T>
    struct invoke_impl : invoke_fn
    {};

    template<class C, class M>
    struct invoke_impl<M C::*> : invoke_mem_fn<C, emp::is_function_v<M>>
    {};

    template<class AlwaysVoid, class F, class... Args>
    struct invoke_result
    {};

    template<class F, class... Args>
    struct invoke_result<
      emp::void_t<typename invoke_impl<typename emp::decay<F>::type>::template f<F, Args...>>,
      F, Args...>
    {
      using type = typename invoke_impl<typename emp::decay<F>::type>::template f<F, Args...>;
    };
  } // namespace detail
  // TODO is_complete_or_unbounded
  JLN_MP_MAKE_TRAIT_ST_FROM_S(invoke_result, (class F, class... Args),
    detail::invoke_result<void, F, Args...>);


// If T is a complete enumeration (enum) type, provides a member typedef type that names the underlying type of T.
#if 0
  // Otherwise, the behavior is undefined. (until C++20)
  JLN_MP_MAKE_TRAIT_ST_FROM_EXPR_T(underlying_type, (class T), __underlying_type(T));
#else
  // Otherwise, if T is not an enumeration type, there is no member type. (since C++20)
  namespace detail
  {
    template<class T, bool = __is_enum(T)>
    struct underlying_type_impl { using type = __underlying_type(T); };

    template<class T> struct underlying_type_impl<T, false> {};
  }
  JLN_MP_MAKE_TRAIT_ST_FROM_S(underlying_type, (class T), detail::underlying_type_impl<T>);
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

    template<class T, class U>
    using cond_res = decltype(false ? JLN_MP_DECLVAL(T) : JLN_MP_DECLVAL(U));

    template<>
    struct common_type_decayed_dispatch<true>
    {
#if JLN_MP_CXX_VERSION >= 20
      // TODO class = void => bool = requires { ... };
      template<class T, class U, class = void>
      struct lvalue_cond
      {};

      template<class T, class U>
      struct lvalue_cond<T, U, decltype(void(false ? JLN_MP_DECLVAL(T) : JLN_MP_DECLVAL(U)))>
      {
        using type = emp::decay_t<decltype(false ? JLN_MP_DECLVAL(T) : JLN_MP_DECLVAL(U))>;
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
      struct f<T, U, TRval, URval, emp::void_t<cond_res<TRval, URval>>>
      {
        using type = emp::decay_t<cond_res<TRval, URval>>;
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

    template<class T0, class T1, class T2, class T3, class T4, class... R>
    struct common_type<T0, T1, T2, T3, T4, R...>
#if JLN_MP_FEATURE_CONCEPTS
      : detail::common_type_fold<requires{ typename common_type<T0, T1, T2, T3>::type; }>
        ::template f<common_type<T0, T1, T2, T3>, T4, R...>
#else
      : detail::common_type_fold<common_type<T0, T1, T2, T3>>::template f<T4, R...>
#endif
    {};
  }
  JLN_MP_MAKE_TRAIT_T_FROM_S(common_type, (class... Ts), emp::common_type<Ts...>);


  namespace emp
  {
    template<class T, class U, template<class> class TQual, template<class> class UQual>
    struct basic_common_reference
#if ! JLN_MP_NO_STL && JLN_MP_CXX_VERSION >= 20
      : std::basic_common_reference<T, U, TQual, UQual>;
#endif
    {};

    template<class... Ts>
    struct common_reference;
  }
  namespace detail
  {
    /*
     * common_reference<> -> no member type
     * common_reference<T> -> T
     * common_reference<T, U> -> {
     *  is_reference<T> && is_reference<U> && VALID(simple_common_ref_t<T, U> -> ExprType)
     *  or {
     *    TQ = add cv ref for T
     *    UQ = add cv ref for U
     *    VALID(basic_common_reference_t<remove_cvref_t<T>, remove_cvref_t<U>, TQ, UQ> -> ExprType)
     *  }
     *  or {
     *    template<class T> T val();
     *    VALID(decltype(false ? val<T>() : val<U>()) -> ExprType)
     *  }
     *  or common_type<T, U>
     * }
     * common_reference<T, U, R...> -> {
     *  VALID(common_reference_t<T, U> -> ExprType)
     *    ? common_reference<ExprType, R...>
     *    : no member type
     * }
     *
     * simple_common_ref<T&, U&> -> {
     *  T -> cv1 X
     *  U -> cv2 Y
     *  cv12 = cv1 cv2
     *  VALID(decltype(false ? declval<cv12 X&>() : declval<cv12 Y&>()) -> C)
     *  is_reference<C> ? C : no member type
     * }
     * simple_common_ref<T&&, U&&> -> {
     *  VALID(simple_common_ref_t<T&, U&> -> C)
     *  is_convertible<T, C> && is_convertible<U, C> ? C : no member type
     * }
     * simple_common_ref<T&, U&&> -> {
     *  VALID(decltype(false ? declval<T&>() : declval<U const&>()) -> D)
     *  is_convertible<U&&, D> ? D : no member type
     * }
     * simple_common_ref<T&&, U&> -> {
     *  VALID(decltype(false ? declval<U&>() : declval<T const&>()) -> D)
     *  is_convertible<T&&, D> ? D : no member type
     * }
     */

    template<class T, class U>
    using cond_cv_res = decltype(false
      ? JLN_MP_DECLVAL(typename copy_cv_impl<U>::template f<T>&)
      : JLN_MP_DECLVAL(typename copy_cv_impl<T>::template f<U>&)
    );

    template<class T, class U, int bullet = 1, class = void>
    struct common_reference_impl : common_reference_impl<T, U, bullet + 1>
    {};

    // simple_common_ref<T&, U&>
    template<class T, class U, class = void>
    struct common_ref
    {};

    template<class T, class U>
    struct common_ref<T, U, emp::enable_if_t<
      JLN_MP_IS_REFERENCE_V(cond_cv_res<T, U>)
    >>
    {
      using type = cond_cv_res<T, U>;
    };

    template<class T, class U>
    struct common_reference_impl<T&, U&, 1, emp::void_t<
      typename common_ref<T, U>::type
    >>
      : common_ref<T, U>
    {};

    template<class T, class U>
    using common_ref_C = emp::remove_reference_t<typename common_ref<T, U>::type>&&;

    template<class T, class U>
    struct common_reference_impl<T&&, U&&, 1, emp::enable_if_t<
        JLN_MP_IS_CONVERTIBLE_V(T&&, common_ref_C<T, U>)
     && JLN_MP_IS_CONVERTIBLE_V(U&&, common_ref_C<T, U>)
    >>
    {
      using type = common_ref_C<T, U>;
    };

    template<class T, class U>
    struct common_reference_impl<T&, U&&, 1, emp::enable_if_t<
      JLN_MP_IS_CONVERTIBLE_V(U&&, typename common_ref<T, U const>::type)
    >>
      : common_ref<T, U const>
    {};

    template<class T, class U>
    struct common_reference_impl<T&&, U&, 1, emp::enable_if_t<
      JLN_MP_IS_CONVERTIBLE_V(T&&, typename common_ref<U, T const>::type)
    >>
      : common_ref<U, T const>
    {};

    template<class T, class U>
    using basic_common_ref_t = typename emp::basic_common_reference<
      JLN_MP_REMOVE_CVREF_T(T),
      JLN_MP_REMOVE_CVREF_T(U),
      copy_cvref_impl<T>::template f,
      copy_cvref_impl<U>::template f
    >::type;

    template<class T, class U>
    struct common_reference_impl<T, U, 2, emp::void_t<basic_common_ref_t<T, U>>>
    {
      using type = basic_common_ref_t<T, U>;
    };

    template<class T, class U>
    struct common_reference_impl<T, U, 3,
      decltype(void(false ? JLN_MP_DECLVAL(T) : JLN_MP_DECLVAL(U)))>
    {
      using type = decltype(false ? JLN_MP_DECLVAL(T) : JLN_MP_DECLVAL(U));
    };

    template<class T, class U>
    struct common_reference_impl<T, U, 4, void> : common_type2<T, U>
    {};

#if JLN_MP_FEATURE_CONCEPTS
    template<bool>
    struct common_reference_fold;

    template<>
    struct common_reference_fold<true>
    {
      template<class CommonRef, class... xs>
      using f = emp::common_reference<typename CommonRef::type, xs...>;
    };

    template<>
    struct common_reference_fold<false>
    {
      template<class, class...>
      using f = emp::common_reference<>;
    };
#else
    template<class CommonRef, class = void>
    struct common_reference_fold
    {
      template<class...>
      using f = emp::common_reference<>;
    };

    template<class CommonRef>
    struct common_reference_fold<CommonRef, emp::void_t<typename CommonRef::type>>
    {
      template<class... xs>
      using f = emp::common_reference<typename CommonRef::type, xs...>;
    };
#endif
  }
  namespace emp
  {
    template<>
    struct common_reference<>
    {};

    template<class T>
    struct common_reference<T>
    {
      using type = T;
    };

    template<class T, class U>
    struct common_reference<T, U> : detail::common_reference_impl<T, U>
    {};

    template<class T, class U, class... R>
    struct common_reference<T, U, R...>
#if JLN_MP_FEATURE_CONCEPTS
      : detail::common_reference_fold<requires{ typename common_reference<T, U>::type; }>
        ::template f<common_reference<T, U>, R...>
#else
      : detail::common_reference_fold<common_reference<T, U>>::template f<R...>
#endif
    {};

    template<class T0, class T1, class T2, class T3, class T4, class... R>
    struct common_reference<T0, T1, T2, T3, T4, R...>
#if JLN_MP_FEATURE_CONCEPTS
      : detail::common_reference_fold<requires{ typename common_reference<T0, T1, T2, T3>::type; }>
        ::template f<common_reference<T0, T1, T2, T3>, T4, R...>
#else
      : detail::common_reference_fold<common_reference<T0, T1, T2, T3>>::template f<T4, R...>
#endif
    {};
  }
  // TODO undefined if any of the types in T... is an incomplete type other than (possibly cv-qualified) void.
  JLN_MP_MAKE_TRAIT_T_FROM_S(common_reference, (class... Ts), emp::common_reference<Ts...>);


  // __cpp_lib_common_reference_wrapper (C++23) P2655
  namespace emp
  {
    // TODO no stl
    template<class T, class U, template<class> class TQual, template<class> class UQual>
    struct basic_common_reference<std::reference_wrapper<T>, std::reference_wrapper<U>, TQual, UQual>
      : detail::common_reference_impl<TQual<T>, UQual<U>, 3>
    {};
  }
  // TODO no stl
#if JLN_MP_FEATURE_CONCEPTS
  namespace emp
  {
    template<class T, class U, template<class> class TQual, template<class> class UQual>
      requires JLN_MP_IS_CONVERTIBLE_V(
        TQual<std::reference_wrapper<T>>, common_reference_t<T&, UQual<U>>)
    struct basic_common_reference<std::reference_wrapper<T>, U, TQual, UQual>
      : common_reference<T&, UQual<U>>
    {};

    template<class T, class U, template<class> class TQual, template<class> class UQual>
      requires JLN_MP_IS_CONVERTIBLE_V(
        TQual<std::reference_wrapper<T>>, common_reference_t<T&, UQual<U>>)
    struct basic_common_reference<U, std::reference_wrapper<T>, UQual, TQual>
      : common_reference<T&, UQual<U>>
    {};

    template<class T1, class T2, class U1, class U2,
             template<class> class TQual, template<class> class UQual>
      requires requires { typename std::pair<common_reference_t<TQual<T1>, UQual<U1>>,
                                             common_reference_t<TQual<T2>, UQual<U2>>>; }
    struct basic_common_reference<std::pair<T1, T2>, std::pair<U1, U2>, TQual, UQual>
    {
      using type = std::pair<common_reference_t<TQual<T1>, UQual<U1>>,
                             common_reference_t<TQual<T2>, UQual<U2>>>;
    };

    template<class... Ts, class... Us, template<class> class TQual, template<class> class UQual>
      requires requires { typename std::tuple<common_reference_t<TQual<Ts>, UQual<Us>>...>; }
    struct basic_common_reference<std::tuple<Ts...>, std::tuple<Us...>, TQual, UQual>
    {
      using type = std::tuple<common_reference_t<TQual<Ts>, UQual<Us>>...>;
    };
  }
#else
  namespace detail
  {
    template<class From, class CommonType, class = void>
    struct basic_common_reference_convertible_impl
    {};

    template<class From, class CommonType>
    struct basic_common_reference_convertible_impl<From, CommonType,
      emp::enable_if_t<JLN_MP_IS_CONVERTIBLE_V(From, typename CommonType::type)>
    >
      : CommonType
    {};

    template<template<class> class TQual, template<class> class UQual,
             class Ts, class Us, class = void>
    struct basic_common_reference_tuple_like_impl
    {
      template<template<class...> class Tpl>
      using f = emp::enable_if<false>;
    };

    template<template<class> class TQual, template<class> class UQual, class... Ts, class... Us>
    struct basic_common_reference_tuple_like_impl<TQual, UQual, list<Ts...>, list<Us...>,
      emp::void_t<emp::common_reference_t<TQual<Ts>, UQual<Us>>...>>
    {
      template<template<class...> class Tpl>
      using f = emp::type_identity<Tpl<emp::common_reference_t<TQual<Ts>, UQual<Us>>...>>;
    };
  }
  namespace emp
  {
    template<class T, class U, template<class> class TQual, template<class> class UQual>
    struct basic_common_reference<std::reference_wrapper<T>, U, TQual, UQual>
      : detail::basic_common_reference_convertible_impl<
          TQual<std::reference_wrapper<T>>, common_reference<T&, UQual<U>>>
    {};

    template<class T, class U, template<class> class TQual, template<class> class UQual>
    struct basic_common_reference<U, std::reference_wrapper<T>, UQual, TQual>
      : detail::basic_common_reference_convertible_impl<
          TQual<std::reference_wrapper<T>>, common_reference<T&, UQual<U>>>
    {};

    template<class T1, class T2, class U1, class U2,
             template<class> class TQual, template<class> class UQual>
    struct basic_common_reference<std::pair<T1, T2>, std::pair<U1, U2>, TQual, UQual>
      : detail::basic_common_reference_tuple_like_impl<TQual, UQual, list<T1, T2>, list<U1, U2>>
        ::template f<std::pair>
    {};

    template<class... Ts, class... Us, template<class> class TQual, template<class> class UQual>
    struct basic_common_reference<std::tuple<Ts...>, std::tuple<Us...>, TQual, UQual>
      : detail::basic_common_reference_tuple_like_impl<TQual, UQual, list<Ts...>, list<Us...>>
        ::template f<std::tuple>
    {};
  }
#endif


  // not standard
  //@{
  namespace detail
  {
    template<class R, class... Ts>
    using enable_if_convertible_xs = emp::enable_if_t<(... && JLN_MP_IS_CONVERTIBLE_V(Ts, R))>;

    template<class, class... Ts>
    struct true_common_type_impl
    {};

    template<class... Ts>
    struct true_common_type_impl<
      enable_if_convertible_xs<typename emp::common_type<Ts...>::type, Ts...>,
      Ts...
    >
      : emp::common_type<Ts...>
    {};

    template<class, class... Ts>
    struct true_common_reference_impl
    {};

    template<class... Ts>
    struct true_common_reference_impl<
      enable_if_convertible_xs<typename emp::common_reference<Ts...>::type, Ts...>,
      Ts...
    >
      : emp::common_reference<Ts...>
    {};
  }
  // common_type may result in a type that is not compatible with Ts parameters.
  // In this case, true_common_type does not contain a type type member
  JLN_MP_MAKE_TRAIT_ST_FROM_S(true_common_type, (class... Ts), detail::true_common_type_impl<void, Ts...>);
  // common_reference may result in a type that is not compatible with Ts parameters.
  // In this case, true_common_reference does not contain a type type member
  JLN_MP_MAKE_TRAIT_ST_FROM_S(true_common_reference, (class... Ts), detail::true_common_reference_impl<void, Ts...>);
  //@}


  // https://en.cppreference.com/w/cpp/experimental/is_detected
  // TODO move in not standard block

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

JLN_MP_DIAGNOSTIC_POP()

#undef JLN_MP_TRAIT_BUILTIN_IMPL_IS
#undef JLN_MP_MAKE_TRAIT
#undef JLN_MP_CONSTEXPR_VAR

#undef JLN_MP_IS_VOID_V
#undef JLN_MP_IS_NULL_POINTER_V

#undef JLN_MP_IS_CONST_V
// TODO undef
}
