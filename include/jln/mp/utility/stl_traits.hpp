#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/number/number.hpp>

#include <jln/mp/detail/unpack.hpp>
#include <jln/mp/detail/is_same.hpp>
#include <jln/mp/detail/enumerate.hpp> // JLN_MP_NIL

#include <type_traits>

namespace jln::mp::traits
{
  /// \ingroup trait

  // TODO add emp::*_v
  // TODO using std::*_v for msvc

  // TODO remove duplicates in JLN_MP_MAKE_TRAIT*

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

#define JLN_MP_MAKE_TRAIT_V_T(Name, Params, Type, ...) \
  JLN_MP_MAKE_TRAIT_V(Name, Params, Type, __VA_ARGS__) \
  JLN_MP_MAKE_TRAIT(Name, Params, std::integral_constant<Type, __VA_ARGS__>)


#ifndef JLN_MP_USE_OPTIONAL_BUILTIN
#  define JLN_MP_USE_OPTIONAL_BUILTIN 1
#endif

#define JLN_MP_FN_PTR(...) static_cast<__VA_ARGS__>(nullptr)
#define JLN_MP_DECLVAL(T) static_cast<T(*)()>(nullptr)()
#define JLN_MP_DECLVAL_NOTHROW(T) static_cast<T(*)() noexcept>(nullptr)()

#define JLN_MP_TRAIT_BUILTIN_IMPL_IS(Name, Params) \
  std::integral_constant<bool, Name(JLN_MP_UNPACK Params)>

#define JLN_MP_TRAIT_BUILTIN_IMPL_SIZE(Name, Params) \
  std::integral_constant<std::size_t, Name(JLN_MP_UNPACK Params)>

#define JLN_MP_TRAIT_BUILTIN_IMPL_T(Name, Params) \
  Name(JLN_MP_UNPACK Params)

#define JLN_MP_TRAIT_STD_IMPL(Name, Params) \
  typename std::Name<JLN_MP_UNPACK Params>::type

#define JLN_MP_TRAIT_STD_IMPL_V(Name, Params) \
  std::Name<JLN_MP_UNPACK Params>::value


#define JLN_MP_MAKE_TRAIT_DISPATCH_I(Name, ToImpl, ImplName, Params, Values) \
  JLN_MP_MAKE_TRAIT(Name, Params, ToImpl(ImplName, Values))
#define JLN_MP_MAKE_TRAIT_DISPATCH(...) JLN_MP_MAKE_TRAIT_DISPATCH_I(__VA_ARGS__)

#define JLN_MP_MAKE_TRAIT_P1(...) JLN_MP_MAKE_TRAIT_DISPATCH_I(__VA_ARGS__, (class x), (x))
#define JLN_MP_MAKE_TRAIT_P2(...) JLN_MP_MAKE_TRAIT_DISPATCH_I(__VA_ARGS__, (class x, class y), (x, y))
#define JLN_MP_MAKE_TRAIT_XS(...) JLN_MP_MAKE_TRAIT_DISPATCH_I(__VA_ARGS__, (class... xs), (xs...))

#define JLN_MP_MAKE_STD_TRAIT_P1(Name) JLN_MP_MAKE_TRAIT_P1(Name, JLN_MP_TRAIT_STD_IMPL, Name)
#define JLN_MP_MAKE_STD_TRAIT_P2(Name) JLN_MP_MAKE_TRAIT_P2(Name, JLN_MP_TRAIT_STD_IMPL, Name)
#define JLN_MP_MAKE_STD_TRAIT_XS(Name) JLN_MP_MAKE_TRAIT_XS(Name, JLN_MP_TRAIT_STD_IMPL, Name)

#define JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_V_IS(Name, Params, ...)            \
  JLN_MP_MAKE_TRAIT(Name, Params, std::integral_constant<bool, __VA_ARGS__>); \
  JLN_MP_MAKE_TRAIT_V(Name, Params, bool, __VA_ARGS__)

#define JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(Name) \
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_V_IS(Name, (class x), __##Name(x))

#define JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P2_V_IS(Name) \
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_V_IS(Name, (class x, class y), __##Name(x, y))

#define JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_X_XS_V_IS(Name) \
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_V_IS(Name, (class x, class... xs), __##Name(x, xs...))

#define JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(Name) \
    JLN_MP_MAKE_TRAIT(Name, (class x), std::integral_constant<bool, emp::Name##_v<x>>)

#define JLN_MP_MAKE_TRAIT_FROM_EMP_P2_IS(Name) \
    JLN_MP_MAKE_TRAIT(Name, (class x, class y), std::integral_constant<bool, emp::Name##_v<x, y>>)

#define JLN_MP_MAKE_TRAIT_FROM_EMP_PTXS_IS(Name) \
    JLN_MP_MAKE_TRAIT(Name, (class T, class... Args), std::integral_constant<bool, emp::Name##_v<T, Args...>>)

#define JLN_MP_MAKE_TRAIT_FROM_EMP_P1_T(Name) \
    JLN_MP_MAKE_TRAIT(Name, (class x), emp::Name##_t<x>)

#define JLN_MP_MAKE_TRAIT_FROM_EMP_P2_T(Name) \
    JLN_MP_MAKE_TRAIT(Name, (class x, class y), emp::Name##_t<x, y>)

#define JLN_MP_MAKE_TRAIT_FROM_EMP_PTXS_T(Name) \
    JLN_MP_MAKE_TRAIT(Name, (class T, class... Args), emp::Name##_t<T, Args...>)

#define JLN_MP_MAKE_TRAIT_DISPATCH_V_I(Type, Name, ToImpl, ToImplV, ImplName, Params, Values) \
  JLN_MP_MAKE_TRAIT(Name, Params, ToImpl(ImplName, Values));                                  \
  JLN_MP_MAKE_TRAIT_V(Name, Params, Type, ToImplV(ImplName, Values))
#define JLN_MP_MAKE_TRAIT_DISPATCH_V(...) JLN_MP_MAKE_TRAIT_DISPATCH_V_I(__VA_ARGS__)

#define JLN_MP_MAKE_STD_TRAIT_V_P1(type, name) \
  JLN_MP_MAKE_TRAIT_DISPATCH_V_I(type, name,   \
    JLN_MP_TRAIT_STD_IMPL, JLN_MP_TRAIT_STD_IMPL_V, name, (class x), (x))

#define JLN_MP_MAKE_STD_TRAIT_P1_V_IS(name)  \
  JLN_MP_MAKE_TRAIT_DISPATCH_V_I(bool, name, \
    JLN_MP_TRAIT_STD_IMPL, JLN_MP_TRAIT_STD_IMPL_V, name, (class x), (x))

#define JLN_MP_MAKE_STD_TRAIT_P2_V_IS(name)  \
  JLN_MP_MAKE_TRAIT_DISPATCH_V_I(bool, name, \
    JLN_MP_TRAIT_STD_IMPL, JLN_MP_TRAIT_STD_IMPL_V, name, (class x, class y), (x, y))

#define JLN_MP_MAKE_STD_TRAIT_X_XS_V_IS(name) \
  JLN_MP_MAKE_TRAIT_DISPATCH_V_I(bool, name,  \
    JLN_MP_TRAIT_STD_IMPL, JLN_MP_TRAIT_STD_IMPL_V, name, (class x, class... xs), (x, xs...))

#define JLN_MP_MAKE_TRAIT_V_P1(...) JLN_MP_MAKE_TRAIT_DISPATCH_V_I(__VA_ARGS__, (class x), (x))
#define JLN_MP_MAKE_TRAIT_V_P2(...) JLN_MP_MAKE_TRAIT_DISPATCH_V_I(__VA_ARGS__, (class x, class y), (x, y))
#define JLN_MP_MAKE_TRAIT_V_XS(...) JLN_MP_MAKE_TRAIT_DISPATCH_V_I(__VA_ARGS__, (class... xs), (xs...))

#define JLN_MP_MAKE_STD_TRAIT_V_P2(Type, Name) JLN_MP_MAKE_TRAIT_V_P2(Type, Name, JLN_MP_TRAIT_STD_IMPL, Name)
#define JLN_MP_MAKE_STD_TRAIT_V_XS(Type, Name) JLN_MP_MAKE_TRAIT_V_XS(Type, Name, JLN_MP_TRAIT_STD_IMPL, Name)

#define JLN_MP_TRAIT_COND_00 0
#define JLN_MP_TRAIT_COND_01 1
#define JLN_MP_TRAIT_COND_10 1
#define JLN_MP_TRAIT_COND_11 1

#if JLN_MP_GCC || JLN_MP_CLANG || JLN_MP_MSVC
#  define JLN_MP_TRAIT_COND_BUILTIN0 1
#else
#  define JLN_MP_TRAIT_COND_BUILTIN0 0
#endif

#if JLN_MP_GCC
#  define JLN_MP_TRAIT_COND_GCC0 1
#  if JLN_MP_GCC >= 800
#    define JLN_MP_TRAIT_COND_GCC90 1
#  else
#    define JLN_MP_TRAIT_COND_GCC90 1
#  endif
#else
#  define JLN_MP_TRAIT_COND_GCC0 0
#  define JLN_MP_TRAIT_COND_GCC90 0
#endif

#if JLN_MP_MSVC
#  define JLN_MP_TRAIT_COND_MSVC0 1
#  if JLN_MP_MSVC >= 2000
#    define JLN_MP_TRAIT_COND_MSVC_200 1
#  else
#    define JLN_MP_TRAIT_COND_MSVC_200 0
#  endif
#else
#  define JLN_MP_TRAIT_COND_MSVC0 0
#  define JLN_MP_TRAIT_COND_MSVC_200 0
#endif

#if JLN_MP_CLANG
#  define JLN_MP_TRAIT_COND_CLANG0 1
#else
#  define JLN_MP_TRAIT_COND_CLANG0 0
#endif

#define JLN_MP_TRAIT_COND_EVAL_I(a, b) JLN_MP_TRAIT_COND_##a##b
#define JLN_MP_TRAIT_COND_EVAL(a, b) JLN_MP_TRAIT_COND_EVAL_I(a, b)
#define JLN_MP_TRAIT_COND_SELECT_0(yes, no) JLN_MP_UNPACK no
#define JLN_MP_TRAIT_COND_SELECT_1(yes, no) JLN_MP_UNPACK yes
#define JLN_MP_TRAIT_COND_SELECT_II(cond, yes, no) cond(yes, no)
#define JLN_MP_TRAIT_COND_SELECT_I(cond, yes, no) \
  JLN_MP_TRAIT_COND_SELECT_II(JLN_MP_TRAIT_COND_SELECT_##cond, yes, no)
#define JLN_MP_TRAIT_COND_SELECT(cond, yes, no) JLN_MP_TRAIT_COND_SELECT_I(cond, yes, no)

#define JLN_MP_TRAIT_BUILTIN_IMPL(stl_name, builtin_name, builtin_impl, cond1, cond2, cond3) \
  JLN_MP_TRAIT_COND_SELECT(                                                                  \
    JLN_MP_TRAIT_COND_EVAL(JLN_MP_TRAIT_COND_EVAL(cond1, 0),                                 \
      JLN_MP_TRAIT_COND_EVAL(JLN_MP_TRAIT_COND_EVAL(cond2, 0),                               \
        JLN_MP_TRAIT_COND_EVAL(JLN_MP_TRAIT_COND_EVAL(cond3, 0),                             \
          JLN_MP_HAS_BUILTIN(builtin_name)))),                                               \
    (builtin_impl, builtin_name), (JLN_MP_TRAIT_STD_IMPL, stl_name))

#define JLN_MP_TRAIT_BUILTIN2_IS(stl_name, builtin_name, cond1, cond2, cond3) \
  stl_name, JLN_MP_TRAIT_BUILTIN_IMPL(                                        \
    stl_name, builtin_name, JLN_MP_TRAIT_BUILTIN_IMPL_IS, cond1, cond2, cond3)

#define JLN_MP_TRAIT_BUILTIN_IS(stl_name, cond1, cond2, cond3) \
  stl_name, JLN_MP_TRAIT_BUILTIN_IMPL(                         \
    stl_name, __##stl_name, JLN_MP_TRAIT_BUILTIN_IMPL_IS, cond1, cond2, cond3)

#define JLN_MP_TRAIT_BUILTIN_T(stl_name, cond1, cond2, cond3) \
  stl_name, JLN_MP_TRAIT_BUILTIN_IMPL(                        \
    stl_name, __##stl_name, JLN_MP_TRAIT_BUILTIN_IMPL_T, cond1, cond2, cond3)



#if JLN_MP_GCC || JLN_MP_CLANG || JLN_MP_MSVC
#  define JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P1_IS JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS
#  define JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P2_IS JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P2_V_IS
#else
#  define JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P1_IS(name)         \
    JLN_MP_TRAIT_COND_SELECT(                                  \
      JLN_MP_TRAIT_COND_EVAL(JLN_MP_HAS_BUILTIN(__##name), 0), \
      JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS,              \
      JLN_MP_MAKE_STD_TRAIT_P1_V_IS                            \
    )(name)
#  define JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P2_IS(name)         \
    JLN_MP_TRAIT_COND_SELECT(                                  \
      JLN_MP_TRAIT_COND_EVAL(JLN_MP_HAS_BUILTIN(__##name), 0), \
      JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P2_V_IS,              \
      JLN_MP_MAKE_STD_TRAIT_P2_V_IS                            \
    )(name)
#endif

#define JLN_MP_TRAIT_BUILTIN_PARAM(...) (__VA_ARGS__)
#define JLN_MP_TRAIT_ALIAS_PARAM(...) <__VA_ARGS__>

#define JLN_MP_TRAIT_SELECT_BUILTIN_OR_V_IMPL(v_name, builtin_name, cond1, cond2) \
  JLN_MP_TRAIT_COND_SELECT(                                                       \
    JLN_MP_TRAIT_COND_EVAL(JLN_MP_TRAIT_COND_EVAL(cond1, 0),                      \
      JLN_MP_TRAIT_COND_EVAL(JLN_MP_TRAIT_COND_EVAL(cond2, 0),                    \
        JLN_MP_HAS_BUILTIN(builtin_name))),                                       \
    (builtin_name JLN_MP_TRAIT_BUILTIN_PARAM), (v_name JLN_MP_TRAIT_ALIAS_PARAM))

#define JLN_MP_TRAIT_SELECT_BUILTIN_OR_V(name, cond1, cond2) \
  JLN_MP_TRAIT_SELECT_BUILTIN_OR_V_IMPL(name##_v, __##name, cond1, cond2)

#define JLN_MP_TRAIT_SELECT_IMPL(builtin_name, cond1, cond2, builtin_impl, impl) \
  JLN_MP_TRAIT_COND_SELECT(                                                      \
    JLN_MP_TRAIT_COND_EVAL(JLN_MP_TRAIT_COND_EVAL(cond1, 0),                     \
      JLN_MP_TRAIT_COND_EVAL(JLN_MP_TRAIT_COND_EVAL(cond2, 0),                   \
        JLN_MP_HAS_BUILTIN(builtin_name))),                                      \
    builtin_impl, impl)

#define JLN_MP_TRAIT_BUILTIN_V_IMPL(stl_name, builtin_name, builtin_impl, cond1, cond2, cond3) \
  JLN_MP_TRAIT_COND_SELECT(                                                                    \
    JLN_MP_TRAIT_COND_EVAL(JLN_MP_TRAIT_COND_EVAL(cond1, 0),                                   \
      JLN_MP_TRAIT_COND_EVAL(JLN_MP_TRAIT_COND_EVAL(cond2, 0),                                 \
        JLN_MP_TRAIT_COND_EVAL(JLN_MP_TRAIT_COND_EVAL(cond3, 0),                               \
          JLN_MP_HAS_BUILTIN(builtin_name)))),                                                 \
    (builtin_impl, builtin_name), (JLN_MP_TRAIT_STD_IMPL, stl_name))

#define JLN_MP_TRAIT_BUILTIN_IS2(stl_name, cond1, cond2, cond3) \
  stl_name, JLN_MP_TRAIT_BUILTIN_V_IMPL(                        \
    stl_name, __##stl_name, JLN_MP_TRAIT_BUILTIN_IMPL_IS, cond1, cond2, cond3)



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


  // TODO
  namespace detail
  {
    struct false_t { static constexpr bool value = false; };
    struct true_t { static constexpr bool value = true; };

    // TODO
    template<class T>
    struct add_rvalue
    {
      using type = T&&;
    };

    template<>
    struct add_rvalue<void>
    {
      using type = void;
    };

    template<class T>
    typename add_rvalue<T>::type declval();
  }


  // https://en.cppreference.com/w/cpp/feature_test

  // type properties:
#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_const))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_const);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_const_v = false;
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_const_v<const x> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_const);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_volatile))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_volatile);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_volatile_v = false;
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_volatile_v<volatile x> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_volatile);
#endif

#if JLN_MP_GCC || JLN_MP_MSVC || JLN_MP_MSVC >= 2000 || JLN_MP_HAS_BUILTIN(__is_trivial)
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_trivial);
#elif JLN_MP_MSVC || (JLN_MP_HAS_BUILTIN(__is_trivially_constructible) && JLN_MP_HAS_BUILTIN(__is_trivially_copyable))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_V_IS(is_trivial, (class x),
    __is_trivially_constructible(x) && __is_trivially_copyable(x));
#else
  JLN_MP_MAKE_STD_TRAIT_P1_V_IS(is_trivial);
#endif

  JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P1_IS(is_trivially_copyable);
  JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P1_IS(is_standard_layout);
#if __cplusplus <= 201703L
  JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P1_IS(is_pod);
#endif
  JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P1_IS(is_empty);
  JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P1_IS(is_polymorphic);
  JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P1_IS(is_abstract);
  JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P1_IS(is_final);
  JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P1_IS(is_aggregate);

#if defined(__cpp_lib_is_implicit_lifetime) && __cpp_lib_is_implicit_lifetime >= 202302L
  // TODO
  JLN_MP_MAKE_STD_TRAIT_P1(is_implicit_lifetime);
#else
  // TODO
//   JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_V_IS(is_implicit_lifetime, (class x), );
// std::disjunction<
// std::is_scalar<T>,
// std::is_array<T>,
// std::is_aggregate<T>,
// std::conjunction<
//
//       std::is_trivially_destructible<T>,
//       std::disjunction<
//
//             std::is_trivially_default_constructible<T>,
//             std::is_trivially_copy_constructible<T>,
// std::is_trivially_move_constructible<T>>>> {};
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && JLN_MP_HAS_BUILTIN(__is_signed)
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_signed);
#else
  namespace detail
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_signed_impl_v = false;
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
  }
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_signed_v
      = detail::is_signed_impl_v<volatile const x>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_signed);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && JLN_MP_HAS_BUILTIN(__is_unsigned)
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_unsigned);
#else
  namespace detail
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_unsigned_impl_v = false;
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
  }
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_unsigned_v
      = detail::is_unsigned_impl_v<volatile const x>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_unsigned);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && JLN_MP_HAS_BUILTIN(__is_bounded_array)
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_bounded_array);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_bounded_array_v = false;
    template<class x, std::size_t n> JLN_MP_CONSTEXPR_VAR bool is_bounded_array_v<x[n]> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_bounded_array);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && JLN_MP_HAS_BUILTIN(__is_unbounded_array)
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_unbounded_array);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_unbounded_array_v = false;
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_unbounded_array_v<x[]> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_unbounded_array);
#endif

  // TODO
  JLN_MP_MAKE_TRAIT_P2(JLN_MP_TRAIT_BUILTIN2_IS(is_convertible, __is_convertible_to, CLANG, MSVC, 0));
  namespace emp
  {
    template<class from, class to>
    JLN_MP_CONSTEXPR_VAR bool is_convertible_v = is_convertible<from, to>::value;
  }

#if JLN_MP_USE_OPTIONAL_BUILTIN && JLN_MP_HAS_BUILTIN(__is_scoped_enum)
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_scoped_enum);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_scoped_enum_v =
      JLN_MP_TRAIT_SELECT_BUILTIN_OR_V(is_enum, BUILTIN, 0)(x)
      &&
      JLN_MP_TRAIT_SELECT_BUILTIN_OR_V_IMPL(is_convertible_v, __is_convertible_to, CLANG, MSVC)(x, int)
    ;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_scoped_enum);
#endif

#if defined(__cpp_lib_has_unique_object_representations) && __cpp_lib_has_unique_object_representations >= 201606L
  // TODO /!\ gcc implementation
  JLN_MP_MAKE_TRAIT_P1(JLN_MP_TRAIT_BUILTIN_IS(has_unique_object_representations, MSVC, 0, 0));
#endif

  // type categories:
#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_void))
  #define JLN_MP_IS_VOID(...) __is_void(__VA_ARGS__)
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_void);
#elif JLN_MP_USE_OPTIONAL_BUILTIN && JLN_MP_HAS_BUILTIN(__is_same)
  #define JLN_MP_IS_VOID(...) \
    __is_same(volatile const __VA_ARGS__, volatile const void)
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_V_IS(is_void, (class x), JLN_MP_IS_VOID(x));
#else
  #define JLN_MP_IS_VOID(...) emp::is_void_v<__VA_ARGS__>
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_void_v = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_void_v<void> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_void_v<const void> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_void_v<volatile void> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_void_v<volatile const void> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_void);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_same))
  #define JLN_MP_IS_NULL_POINTER(...) \
    __is_same(volatile const __VA_ARGS__, volatile const decltype(nullptr))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_V_IS(is_null_pointer, (class x), JLN_MP_IS_NULL_POINTER(x));
#else
  #define JLN_MP_IS_NULL_POINTER(...) /*emp::*/is_null_pointer_v<__VA_ARGS__>
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_null_pointer_v = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_null_pointer_v<decltype(nullptr)> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_null_pointer_v<const decltype(nullptr)> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_null_pointer_v<volatile decltype(nullptr)> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_null_pointer_v<volatile const decltype(nullptr)> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_null_pointer);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_integral))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_integral);
#else
  namespace detail
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v = false;
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
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const short> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const unsigned short> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const int> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const unsigned int> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const long> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const unsigned long> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const long long> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_integral_impl_v<volatile const unsigned long long> = true;

    // TODO int128 ?
  }
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_integral_v
      = detail::is_integral_impl_v<volatile const x>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_integral);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_floating_point))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_floating_point);
#else
  namespace detail
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_floating_point_impl_v = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_floating_point_impl_v<volatile const float> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_floating_point_impl_v<volatile const double> = true;
    template<> JLN_MP_CONSTEXPR_VAR bool is_floating_point_impl_v<volatile const long double> = true;
  }
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_floating_point_v
      = detail::is_floating_point_impl_v<volatile const x>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_floating_point);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_array))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_array);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_array_v = false;
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_array_v<x[]> = true;
    template<class x, std::size_t n> JLN_MP_CONSTEXPR_VAR bool is_array_v<x[n]> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_array);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_pointer))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_pointer);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_pointer_v = false;
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_pointer_v<x*> = true;
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_pointer_v<x* const> = true;
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_pointer_v<x* volatile> = true;
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_pointer_v<x* volatile const> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_pointer);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_lvalue_reference))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_lvalue_reference);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_lvalue_reference_v = false;
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_lvalue_reference_v<x&> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_lvalue_reference);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_rvalue_reference))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_rvalue_reference);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_rvalue_reference_v = false;
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_rvalue_reference_v<x&&> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_rvalue_reference);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_reference))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_reference);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_reference_v = false;
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_reference_v<x&> = true;
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_reference_v<x&&> = true;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_reference);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_function))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_function);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_function_v =
      !is_const_v<const x> && !is_reference_v<x>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_function);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_member_object_pointer))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_member_object_pointer);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_member_object_pointer_v = false;
    template<class x, class m> JLN_MP_CONSTEXPR_VAR
    bool is_member_object_pointer_v<x m::*> = !is_function_v<x>;
    template<class x, class m> JLN_MP_CONSTEXPR_VAR
    bool is_member_object_pointer_v<x m::* const> = !is_function_v<x>;
    template<class x, class m> JLN_MP_CONSTEXPR_VAR
    bool is_member_object_pointer_v<x m::* volatile> = !is_function_v<x>;
    template<class x, class m> JLN_MP_CONSTEXPR_VAR
    bool is_member_object_pointer_v<x m::* volatile const> = !is_function_v<x>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_member_object_pointer);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_member_function_pointer))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_member_function_pointer);
#else
  namespace emp
  {
    // TODO msvc call spec and gcc
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_member_function_pointer_v = false;
    template<class x, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_function_pointer_v<x C::*> = is_function_v<x>;
    template<class x, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_function_pointer_v<x C::* const> = is_function_v<x>;
    template<class x, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_function_pointer_v<x C::* volatile> = is_function_v<x>;
    template<class x, class C> JLN_MP_CONSTEXPR_VAR
    bool is_member_function_pointer_v<x C::* volatile const> = is_function_v<x>;
    // TODO this is slow
    // #define JLN_MP_MEM_FUN_PTR(qualif)                                                  \
    //     template<class R, class C, class... Ts> JLN_MP_CONSTEXPR_VAR                    \
    //     bool is_member_function_pointer_v<R(C::*)(Ts...) qualif> = true;                \
    //     template<class R, class C, class... Ts> JLN_MP_CONSTEXPR_VAR                    \
    //     bool is_member_function_pointer_v<R(C::* const)(Ts...) qualif> = true;          \
    //     template<class R, class C, class... Ts> JLN_MP_CONSTEXPR_VAR                    \
    //     bool is_member_function_pointer_v<R(C::* volatile)(Ts...) qualif> = true;       \
    //     template<class R, class C, class... Ts> JLN_MP_CONSTEXPR_VAR                    \
    //     bool is_member_function_pointer_v<R(C::* volatile const)(Ts...) qualif> = true; \
    //     template<class R, class C, class... Ts> JLN_MP_CONSTEXPR_VAR                    \
    //     bool is_member_function_pointer_v<R(C::*)(Ts..., ...) qualif> = true;           \
    //     template<class R, class C, class... Ts> JLN_MP_CONSTEXPR_VAR                    \
    //     bool is_member_function_pointer_v<R(C::* const)(Ts..., ...) qualif> = true;     \
    //     template<class R, class C, class... Ts> JLN_MP_CONSTEXPR_VAR                    \
    //     bool is_member_function_pointer_v<R(C::* volatile)(Ts..., ...) qualif> = true;  \
    //     template<class R, class C, class... Ts> JLN_MP_CONSTEXPR_VAR                    \
    //     bool is_member_function_pointer_v<R(C::* volatile const)(Ts..., ...) qualif> = true;
    // JLN_MP_DEFINE_CV_REF_NOEXCEPT(JLN_MP_MEM_FUN_PTR)
    // #undef JLN_MP_MEM_FUN_PTR
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_member_function_pointer);
#endif

  JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P1_IS(is_enum);
  JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P1_IS(is_union);
  JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P1_IS(is_class);

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_arithmetic))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_arithmetic);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_arithmetic_v =
      is_integral_v<x> || is_floating_point_v<x>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_arithmetic);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_fundamental))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_fundamental);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_fundamental_v =
      is_arithmetic_v<x> || JLN_MP_IS_VOID(x) || JLN_MP_IS_NULL_POINTER(x);
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_fundamental);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_object))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_object);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_object_v =
      is_const_v<const x> && !is_void_v<x>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_object);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_member_pointer))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_member_pointer);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_member_pointer_v =
      is_member_object_pointer_v<x> || is_member_function_pointer_v<x>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_member_pointer);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_scalar))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_scalar);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_scalar_v =
      is_arithmetic_v<x> || __is_enum(x) || is_pointer_v<x>
        || is_member_pointer_v<x> || JLN_MP_IS_NULL_POINTER(x);
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_scalar);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_CLANG || JLN_MP_HAS_BUILTIN(__is_compound))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_compound);
#else
  namespace emp
  {
    template<class x> JLN_MP_CONSTEXPR_VAR bool is_compound_v = !is_fundamental_v<x>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_compound);
#endif

  namespace emp
  {
    template<class...>
    using void_t = void;

    // TODO
    template<class x>
    using type_identity_t = x;
  }

  namespace detail
  {
    // TODO real trait is_referencable
    template<class T, class = void>
    struct is_referencable_impl : false_
    {};

    template<class T>
    struct is_referencable_impl<T, emp::void_t<T&>> : true_
    {};

    // TODO
    // add_reference { lvalue = T&; rvalue = T&&; }
    // add_lvalue_reference = add_reference<T>::lvalue;

    template<class T, bool = is_referencable_impl<T volatile const>::value>
    struct add_lvalue_reference_impl
    {
      using type = T;
    };

    template<class T>
    struct add_lvalue_reference_impl<T, true>
    {
      using type = T&;
    };

    template<class T, bool = is_referencable_impl<T volatile const>::value>
    struct add_rvalue_reference_impl
    {
      using type = T;
    };

    template<class T>
    struct add_rvalue_reference_impl<T, true>
    {
      using type = T&&;
    };
  }

  JLN_MP_MAKE_TRAIT_WRAP_T(add_lvalue_reference, (class T), detail::add_lvalue_reference_impl<T>);
  JLN_MP_MAKE_TRAIT_WRAP_T(add_rvalue_reference, (class T), detail::add_rvalue_reference_impl<T>);

  // supported operations
  // TODO faster with concepts?
#if /*JLN_MP_USE_OPTIONAL_BUILTIN &&*/ (JLN_MP_GCC || JLN_MP_CLANG || JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_constructible))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_X_XS_V_IS(is_constructible);
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_V_IS(
    is_default_constructible, (class T), __is_constructible(T));
  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_copy_constructible_v
      = __is_constructible(T, add_lvalue_reference_t<T const>);

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_move_constructible_v
      = __is_constructible(T, add_rvalue_reference_t<T>);
  }
  // JLN_MP_MAKE_TRAIT_FROM_EMP_PTXS_IS(is_constructible);
  // JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_default_constructible);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_copy_constructible);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_move_constructible);
#else
#  if JLN_MP_FEATURE_CONCEPTS
  namespace emp
  {
    template<class T, class... Args>
    JLN_MP_CONSTEXPR_VAR bool is_constructible_v
      = requires { T(static_cast<Args&&>(static_cast<Args*>(nullptr))...); };

    // TODO faster that builtin with gcc (others too?)
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_default_constructible_v
      = requires { T{}; }; // T() does not work with when T = U[n]

    // JLN_MP_DECLVAL(T const&) faster ?
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_copy_constructible_v
      = requires { T(*static_cast<T const*>(nullptr)); };

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_move_constructible_v
      = requires { T(static_cast<T&&>(*static_cast<T*>(nullptr))); };
  }
#  endif
  namespace emp
  {
    // template<class... Args> JLN_MP_CONSTEXPR_VAR bool is_constructible_v<void, Args...> = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_default_constructible_v<void> = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_copy_constructible_v<void> = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_move_constructible_v<void> = false;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_PTXS_IS(is_constructible);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_default_constructible);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_copy_constructible);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_move_constructible);
#endif

// TODO faster with concepts?
#if /*JLN_MP_USE_OPTIONAL_BUILTIN &&*/ (JLN_MP_GCC || JLN_MP_CLANG || JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_trivially_constructible))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_X_XS_V_IS(is_trivially_constructible);
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_V_IS(
    is_trivially_default_constructible, (class T), __is_trivially_constructible(T));
  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_copy_constructible_v
      = __is_trivially_constructible(T, add_lvalue_reference_t<T const>);

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_move_constructible_v
      = __is_trivially_constructible(T, add_rvalue_reference_t<T>);
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_trivially_copy_constructible);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_trivially_move_constructible);
#else
#  if JLN_MP_FEATURE_CONCEPTS
  namespace emp
  {
    template<class T, class... Args>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_constructible_v
      = requires { T(static_cast<Args&&>(static_cast<Args*>(nullptr))...); };

    // TODO faster that builtin with gcc (others too?)
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_default_constructible_v
      = requires { T{}; }; // T() does not work with when T = U[n]

    // JLN_MP_DECLVAL(T const&) faster ?
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_copy_constructible_v
      = requires { T(*static_cast<T const*>(nullptr)); };

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_move_constructible_v
      = requires { T(static_cast<T&&>(*static_cast<T*>(nullptr))); };
  }
#  endif
  namespace emp
  {
    // template<class... Args> JLN_MP_CONSTEXPR_VAR bool is_trivially_constructible_v<void, Args...> = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_trivially_default_constructible_v<void> = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_trivially_copy_constructible_v<void> = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_trivially_move_constructible_v<void> = false;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_PTXS_IS(is_trivially_constructible);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_trivially_default_constructible);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_trivially_copy_constructible);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_trivially_move_constructible);
#endif

// TODO faster with concepts?
#if /*JLN_MP_USE_OPTIONAL_BUILTIN &&*/ (JLN_MP_GCC || JLN_MP_CLANG || JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_nothrow_constructible))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_X_XS_V_IS(is_nothrow_constructible);
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_V_IS(
    is_nothrow_default_constructible, (class T), __is_nothrow_constructible(T));
  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_copy_constructible_v
      = __is_nothrow_constructible(T, add_lvalue_reference_t<T const>);

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_move_constructible_v
      = __is_nothrow_constructible(T, add_rvalue_reference_t<T>);
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_nothrow_copy_constructible);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_nothrow_move_constructible);
#else
#  if JLN_MP_FEATURE_CONCEPTS
  namespace emp
  {
    template<class T, class... Args>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_constructible_v
      = requires { T(static_cast<Args&&>(static_cast<Args*>(nullptr))...); };

    // TODO faster that builtin with gcc (others too?)
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_default_constructible_v
      = requires { T{}; }; // T() does not work with when T = U[n]

    // JLN_MP_DECLVAL(T const&) faster ?
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_copy_constructible_v
      = requires { T(*static_cast<T const*>(nullptr)); };

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_move_constructible_v
      = requires { T(static_cast<T&&>(*static_cast<T*>(nullptr))); };
  }
#  endif
  namespace emp
  {
    // template<class... Args> JLN_MP_CONSTEXPR_VAR bool is_nothrow_constructible_v<void, Args...> = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_nothrow_default_constructible_v<void> = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_nothrow_copy_constructible_v<void> = false;
    template<> JLN_MP_CONSTEXPR_VAR bool is_nothrow_move_constructible_v<void> = false;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_PTXS_IS(is_nothrow_constructible);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_nothrow_default_constructible);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_nothrow_copy_constructible);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_nothrow_move_constructible);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_GCC || JLN_MP_CLANG || JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_assignable))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P2_V_IS(is_assignable);
  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_copy_assignable_v
      = __is_assignable(T, add_lvalue_reference_t<T const>);

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_move_assignable_v
      = __is_assignable(T, add_rvalue_reference_t<T>);
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_copy_assignable);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_move_assignable);
#else
#  if JLN_MP_FEATURE_CONCEPTS
  namespace emp
  {
    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool is_assignable_v
      = requires { JLN_MP_DECLVAL(T&&) = JLN_MP_DECLVAL(U&&); };

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_copy_assignable_v
      = requires { JLN_MP_DECLVAL(T&) = JLN_MP_DECLVAL(T const&); };

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_move_assignable_v
      = requires { JLN_MP_DECLVAL(T&) = JLN_MP_DECLVAL(T&&); };
  }
#  else
  namespace detail
  {
    template<class, class T, class U>
    struct is_assignable_impl
      : false_t
    {};

    template<class T, class U>
    struct is_assignable_impl<
      decltype(void(JLN_MP_DECLVAL(T&&) = JLN_MP_DECLVAL(U&&))), T, U
    > : true_t
    {};
  }
  namespace emp
  {
    // TODO T -> T volatile ?
    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool is_assignable_v
      = detail::is_assignable_impl<void, T, U>::value;

    // TODO T -> T volatile ?
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_copy_assignable_v
      = detail::is_assignable_impl<void,
          add_lvalue_reference_t<T>, add_lvalue_reference_t<T const>>::value;

    // TODO T -> T volatile ?
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_move_assignable_v
      = detail::is_assignable_impl<void,
          add_lvalue_reference_t<T>, add_rvalue_reference_t<T>>::value;
  }
#  endif
  JLN_MP_MAKE_TRAIT_FROM_EMP_PTXS_IS(is_assignable);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_copy_assignable);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_move_assignable);
#endif

#if /*JLN_MP_USE_OPTIONAL_BUILTIN && */(JLN_MP_GCC || JLN_MP_CLANG || JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_trivially_assignable))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P2_V_IS(is_trivially_assignable);
  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_copy_assignable_v
      = __is_trivially_assignable(add_lvalue_reference_t<T>, add_lvalue_reference_t<T const>);

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_move_assignable_v
      = __is_trivially_assignable(add_lvalue_reference_t<T>, add_rvalue_reference_t<T>);
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_trivially_copy_assignable);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_trivially_move_assignable);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_GCC || JLN_MP_CLANG || JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_nothrow_assignable))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P2_V_IS(is_nothrow_assignable);
  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_copy_assignable_v
      = __is_nothrow_assignable(add_lvalue_reference_t<T>, add_lvalue_reference_t<T const>);

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_move_assignable_v
      = __is_nothrow_assignable(add_lvalue_reference_t<T>, add_rvalue_reference_t<T>);
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_nothrow_copy_assignable);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_nothrow_move_assignable);
#else
  namespace detail
  {
    template<class T, class U, class = void>
    struct is_nothrow_assignable_impl
      : false_t
    {};

    template<class T, class U>
    struct is_nothrow_assignable_impl<
      T, U, std::enable_if_t<noexcept(JLN_MP_DECLVAL_NOTHROW(T&&) = JLN_MP_DECLVAL_NOTHROW(U&&))>
    > : true_t
    {};
  }
  namespace emp
  {
    // TODO T -> T volatile ?
    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_assignable_v
      = detail::is_nothrow_assignable_impl<T, U>::value;

    // TODO T -> T volatile ?
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_copy_assignable_v
      = detail::is_nothrow_assignable_impl<
          add_lvalue_reference_t<T>, add_lvalue_reference_t<T const>>::value;

    // TODO T -> T volatile ?
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_move_assignable_v
      = detail::is_nothrow_assignable_impl<
          add_lvalue_reference_t<T>, add_rvalue_reference_t<T>>::value;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_PTXS_IS(is_nothrow_assignable);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_nothrow_copy_assignable);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_nothrow_move_assignable);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_destructible))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_destructible);
#else
#  if JLN_MP_FEATURE_CONCEPTS
  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_destructible_v
      = requires { JLN_MP_DECLVAL(T&).~T(); };
  }
#  else
  namespace detail
  {
    template<class, class T>
    struct is_destructible_impl
      : false_t
    {};

    template<class T>
    struct is_destructible_impl<
      decltype(void(JLN_MP_DECLVAL(T&).~T())), T
    > : true_t
    {};

    template<class T>
    struct is_destructible_impl<void, T&>
      : true_t
    {};

    template<class T>
    struct is_destructible_impl<void, T&&>
      : true_t
    {};

    // TODO remove_all_extents
    template<class T, std::size_t n>
    struct is_destructible_impl<void, T[n]>
      : is_destructible_impl<void, T>
    {};
  }
  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_destructible_v
      = detail::is_destructible_impl<void, T>::value;

    // TODO
    // template<class T>
    // JLN_MP_CONSTEXPR_VAR bool is_destructible_v<T&> = is_destructible_v<T>;
  }
#  endif
  namespace emp
  {
    template<> JLN_MP_CONSTEXPR_VAR bool is_destructible_v<void> = false;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_destructible);
#endif

#if JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_trivially_destructible)
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_trivially_destructible);
#elif JLN_MP_HAS_BUILTIN(__has_trivial_destructor)
  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_destructible_v
      = is_destructible_v<T> && __has_trivial_destructor(T);
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_trivially_destructible);
#else
  // this implementation is not compliant and fails with classes and unions
  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_destructible_v = is_scalar_v<T>;

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_destructible_v<T&> = true;

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_destructible_v<T&&> = true;

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_destructible_v<T[]> = false;

    template<class T, std::size_t n>
    JLN_MP_CONSTEXPR_VAR bool is_trivially_destructible_v<T[n]> = is_trivially_destructible_v<T>;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_trivially_destructible);
#endif

#if JLN_MP_USE_OPTIONAL_BUILTIN && (JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__is_nothrow_destructible))
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(is_nothrow_destructible);
#else
#  if JLN_MP_FEATURE_CONCEPTS
  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_destructible_v
      = requires { JLN_MP_DECLVAL(T&).~T(); };
  }
#  else
  namespace detail
  {
    template<class, class T>
    struct is_nothrow_destructible_impl
      : false_t
    {};

    template<class T>
    struct is_nothrow_destructible_impl<
      std::enable_if_t<noexcept(JLN_MP_DECLVAL_NOTHROW(T&).~T())>, T
    > : true_t
    {};

    template<class T>
    struct is_nothrow_destructible_impl<void, T&>
      : true_t
    {};

    template<class T>
    struct is_nothrow_destructible_impl<void, T&&>
      : true_t
    {};

    // TODO remove_all_extents
    template<class T, std::size_t n>
    struct is_nothrow_destructible_impl<void, T[n]>
      : is_nothrow_destructible_impl<void, T>
    {};
  }
  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_destructible_v
      = detail::is_nothrow_destructible_impl<void, T>::value;

    // TODO
    // template<class T>
    // JLN_MP_CONSTEXPR_VAR bool is_nothrow_destructible_v<T&> = is_nothrow_destructible_v<T>;
  }
#  endif
  namespace emp
  {
    template<> JLN_MP_CONSTEXPR_VAR bool is_nothrow_destructible_v<void> = false;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_nothrow_destructible);
#endif

  namespace detail
  {
    // TODO remove std::enable_if
    template<class T>
    std::enable_if_t<emp::is_move_constructible_v<T> && emp::is_move_assignable_v<T>>
    swap(T&, T&) noexcept(emp::is_nothrow_move_constructible_v<T>
                       && emp::is_nothrow_move_assignable_v<T>);

    template<class, class T>
    struct is_swappable_impl : false_t
    {};

    template<class, class T>
    struct is_nothrow_swappable_impl : false_t
    {};

    template<class T, std::size_t N>
    std::enable_if_t<is_swappable_impl<void, T>::value>
    swap(T(&)[N], T(&)[N]) noexcept(is_nothrow_swappable_impl<void, T>::value);

    template<class, class T, class U>
    struct is_swappable_impl_with;

    template<class, class T, class U>
    struct is_nothrow_swappable_with_impl;

#if JLN_MP_FEATURE_CONCEPTS
    // TODO alias of value (using from this in emp)
    template<class, class T>
    struct is_swappable_impl : number<requires{ swap(JLN_MP_DECLVAL(T&), JLN_MP_DECLVAL(T&)); }>
    {};

    // TODO alias of value (using from this in emp)
    template<class, class T, class U>
    struct is_swappable_with_impl : number<requires{
      swap(JLN_MP_DECLVAL(T&), JLN_MP_DECLVAL(U&));
      swap(JLN_MP_DECLVAL(U&), JLN_MP_DECLVAL(T&));
    }>
    {};
#else
    template<class T>
    struct is_swappable_impl<
      decltype(void(swap(JLN_MP_DECLVAL(T&), JLN_MP_DECLVAL(T&)))), T
    > : true_t
    {};

    template<class T>
    struct is_nothrow_swappable_impl<
      std::enable_if_t<noexcept(swap(JLN_MP_DECLVAL_NOTHROW(T&), JLN_MP_DECLVAL_NOTHROW(T&)))>, T
    > : true_t
    {};

    template<class, class T, class U>
    struct is_swappable_with_impl
      : false_t
    {};

    JLN_MP_DIAGNOSTIC_PUSH()
    JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wcomma")
    template<class T, class U>
    struct is_swappable_with_impl<
      decltype(
        void(swap(JLN_MP_DECLVAL(T&&), JLN_MP_DECLVAL(U&&))),
        void(swap(JLN_MP_DECLVAL(T&&), JLN_MP_DECLVAL(U&&)))
      ), T, U
    > : true_t
    {};
    JLN_MP_DIAGNOSTIC_POP()

    template<class, class T, class U>
    struct is_nothrow_swappable_with_impl
      : false_t
    {};

    template<class T, class U>
    struct is_nothrow_swappable_with_impl<
      std::enable_if_t<noexcept(
        void(swap(JLN_MP_DECLVAL_NOTHROW(T&&), JLN_MP_DECLVAL_NOTHROW(U&&))),
        swap(JLN_MP_DECLVAL_NOTHROW(T&&), JLN_MP_DECLVAL_NOTHROW(U&&))
      )>, T, U
    > : true_t
    {};
#endif
  }

  namespace emp
  {
    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_swappable_v
      = detail::is_swappable_impl<void, add_lvalue_reference_t<T>>::value;

    template<class T>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_swappable_v
      = detail::is_nothrow_swappable_impl<void, add_lvalue_reference_t<T>>::value;


    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool is_swappable_with_v
      = detail::is_swappable_with_impl<void, T, U>::value;

    template<class T, class U>
    JLN_MP_CONSTEXPR_VAR bool is_nothrow_swappable_with_v
      = detail::is_nothrow_swappable_with_impl<void, T, U>::value;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_swappable);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(is_nothrow_swappable);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P2_IS(is_swappable_with);
  JLN_MP_MAKE_TRAIT_FROM_EMP_P2_IS(is_nothrow_swappable_with);

#if JLN_MP_MSVC || JLN_MP_HAS_BUILTIN(__has_virtual_destructor)
  JLN_MP_MAKE_TRAIT_DISPATCH_BUILTIN_P1_V_IS(has_virtual_destructor);
#else
  // TODO use STL
  namespace emp
  {
    template<class T> JLN_MP_CONSTEXPR_VAR bool has_virtual_destructor = false;
  }
  JLN_MP_MAKE_TRAIT_FROM_EMP_P1_IS(has_virtual_destructor);
#endif

  // relationships and property queries

  // TODO see detail/is_same.hpp
  JLN_MP_MAKE_TRAIT_P2(JLN_MP_TRAIT_BUILTIN_IS(is_same, 0, 0, 0));

  // TODO see set/set_contains.hpp
  JLN_MP_MAKE_TRAIT_BUILTIN_OR_STD_P2_IS(is_base_of);

#if defined(__cpp_lib_is_nothrow_convertible) && __cpp_lib_is_nothrow_convertible >= 201806L
  // TODO
  // JLN_MP_MAKE_TRAIT_P2(JLN_MP_TRAIT_BUILTIN_IS(is_nothrow_convertible, CLANG, 0, 0));
#endif
#if defined(__cpp_lib_is_layout_compatible) && __cpp_lib_is_layout_compatible >= 201907L
  JLN_MP_MAKE_TRAIT_P2(JLN_MP_TRAIT_BUILTIN_IS(is_layout_compatible, MSVC, 0, 0));
#endif
#if defined(__cpp_lib_is_pointer_interconvertible) && __cpp_lib_is_pointer_interconvertible >= 201907L
  // TODO
  // JLN_MP_MAKE_TRAIT_P2(JLN_MP_TRAIT_BUILTIN_IS(is_pointer_interconvertible_base_of, MSVC, 0, 0));
  // JLN_MP_MAKE_TRAIT_P2(JLN_MP_TRAIT_BUILTIN_IS(is_pointer_interconvertible_with_class, MSVC, 0, 0));
#endif


  JLN_MP_MAKE_TRAIT_V_T(alignment_of, (class T), std::size_t, alignof(T));


  namespace emp
  {
    template <class T>
    JLN_MP_CONSTEXPR_VAR std::size_t rank_v = 0;

    template <class T>
    JLN_MP_CONSTEXPR_VAR std::size_t rank_v<T[]> = rank_v<T> + 1;

    template <class T, std::size_t n>
    JLN_MP_CONSTEXPR_VAR std::size_t rank_v<T[n]> = rank_v<T> + 1;
  }
  JLN_MP_MAKE_TRAIT(rank, (class T), std::integral_constant<std::size_t, emp::rank_v<T>>);


#if JLN_MP_USE_OPTIONAL_BUILTIN && JLN_MP_HAS_BUILTIN(__array_extent)
  JLN_MP_MAKE_TRAIT_V_T(extent, (class T, class Dim = number<0>),
    std::size_t, __array_extent(T, Dim::value));
  namespace emp
  {
    template <class T, unsigned Dim = 0>
    JLN_MP_CONSTEXPR_VAR std::size_t extent_c_v = __array_extent(T, Dim);
  }
#else
  namespace emp
  {
    template <class T, unsigned Dim = 0>
    JLN_MP_CONSTEXPR_VAR std::size_t extent_c_v = 0;

    template <class T, unsigned Dim>
    JLN_MP_CONSTEXPR_VAR std::size_t extent_c_v<T[], Dim> = extent_c_v<T, Dim - 1>;

    template <class T, std::size_t n>
    JLN_MP_CONSTEXPR_VAR std::size_t extent_c_v<T[n], 0> = n;

    template <class T, unsigned Dim, std::size_t n>
    JLN_MP_CONSTEXPR_VAR std::size_t extent_c_v<T[n], Dim> = extent_c_v<T, Dim - 1>;

    template <class T, class Dim = number<0>>
    JLN_MP_CONSTEXPR_VAR std::size_t extent_v = extent_c_v<T, Dim::value>;
  }
  JLN_MP_MAKE_TRAIT(extent, (class T, class Dim = number<0>),
    std::integral_constant<std::size_t, emp::extent_c_v<T, Dim::value>>);
#endif

  namespace detail
  {
    // TODO no stl
    template <class T>
    JLN_MP_CONSTEXPR_VAR bool is_reference_wrapper_v = false;

    template <class T>
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

    template <typename AlwaysVoid, typename, typename...>
    struct invoke_result {};

    template <typename F, typename...Args>
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
  // TODO
  JLN_MP_MAKE_STD_TRAIT_XS(is_invocable);
  // TODO https://en.cppreference.com/w/cpp/utility/functional (C++23)
  JLN_MP_MAKE_STD_TRAIT_XS(is_invocable_r);
  JLN_MP_MAKE_STD_TRAIT_XS(is_nothrow_invocable);
  // TODO https://en.cppreference.com/w/cpp/utility/functional (C++23)
  JLN_MP_MAKE_STD_TRAIT_XS(is_nothrow_invocable_r);
#endif
#if defined(__cpp_lib_reference_from_temporary) && __cpp_lib_reference_from_temporary >= 202202L
  JLN_MP_MAKE_STD_TRAIT_P2(reference_constructs_from_temporary);
  JLN_MP_MAKE_STD_TRAIT_P2(reference_converts_from_temporary);
#endif

  // const-volatile modifications:
  // TODO no stl (good gcc / clang / msvc)
  JLN_MP_MAKE_TRAIT_WRAP_T(remove_const, (class T), std::remove_const<T>);
  // TODO no stl (good gcc / clang / msvc)
  JLN_MP_MAKE_TRAIT_WRAP_T(remove_volatile, (class T), std::remove_const<T>);
  // TODO no stl (good gcc / ~clang)
  JLN_MP_MAKE_TRAIT_WRAP_T(remove_cv, (class T), std::remove_cv<T>);

  namespace emp
  {
    template<class T> using add_const_t = T const;
    template<class T> using add_volatile_t = T volatile;
    template<class T> using add_cv_t = T const volatile;

  // TODO no stl
    using std::add_const;
  // TODO no stl
    using std::add_volatile;
  // TODO no stl
    using std::add_cv;
  }
  JLN_MP_MAKE_TRAIT_NO_EMP(add_const, (class T), T const);
  JLN_MP_MAKE_TRAIT_NO_EMP(add_volatile, (class T), T volatile);
  JLN_MP_MAKE_TRAIT_NO_EMP(add_cv, (class T), T const volatile);

  // reference modifications:
  // TODO no stl (good gcc / clang / ~msvc)
  JLN_MP_MAKE_TRAIT_WRAP_T(remove_reference, (class T), std::remove_reference<T>);


  // sign modifications:

  namespace detail
  {
    template<int>
    struct mk_min_rank
    {};

    template<>
    struct mk_min_rank<1>
    {
      using signed_type = signed char;
      using unsigned_type = unsigned char;
    };

    template<>
    struct mk_min_rank<2>
    {
      using signed_type = signed short;
      using unsigned_type = unsigned short;
    };

    template<>
    struct mk_min_rank<3>
    {
      using signed_type = signed int;
      using unsigned_type = unsigned int;
    };

    template<>
    struct mk_min_rank<4>
    {
      using signed_type = signed long;
      using unsigned_type = unsigned long;
    };

    template<>
    struct mk_min_rank<5>
    {
      using signed_type = signed long long;
      using unsigned_type = unsigned long long;
    };

    template<std::size_t n>
    struct select_min_rank : mk_min_rank<
      n <= 1 ? 1 :
      n <= sizeof(short) ? 2 :
      n <= sizeof(int) ? 3 :
      n <= sizeof(long) ? 4 :
      n <= sizeof(long long) ? 5 :
      n
    >
    {};

    template<class T>
    struct mk_signed
    {
      // If T is an integral (except bool) or enumeration type, provides the
      // member typedef type which is the signed integer type corresponding to
      // T, with the same cv-qualifiers. Otherwise, the program is ill-formed.
      static_assert((emp::is_integral_v<T> || emp::is_enum_v<T>)
                 && !JLN_MP_IS_SAME_V(T, bool volatile const),
        "make_signed<T> requires that T shall be a (possibly cv-qualified) "
        "integral type or enumeration but not a bool type.");

      // If T is an enumeration type or char, wchar_t, char8_t (since C++20),
      // char16_t, char32_t, the signed integer type with the smallest rank
      // having the same sizeof as T is provided.
      using type = typename select_min_rank<sizeof(T)>::signed_type;
    };

    // If T is signed or unsigned char, short, int, long, long long,
    // the signed type from this list corresponding to T is provided.
    template<> struct mk_signed<const volatile char>          { using type = signed char; };
    template<> struct mk_signed<const volatile unsigned char> { using type = signed char; };
    template<> struct mk_signed<const volatile   signed char> { using type = signed char; };
    template<> struct mk_signed<const volatile unsigned short> { using type = signed short; };
    template<> struct mk_signed<const volatile   signed short> { using type = signed short; };
    template<> struct mk_signed<const volatile unsigned int> { using type = signed int; };
    template<> struct mk_signed<const volatile   signed int> { using type = signed int; };
    template<> struct mk_signed<const volatile unsigned long> { using type = signed long; };
    template<> struct mk_signed<const volatile   signed long> { using type = signed long; };
    template<> struct mk_signed<const volatile unsigned long long> { using type = signed long long; };
    template<> struct mk_signed<const volatile   signed long long> { using type = signed long long; };
    // TODO support of __uint128_t, __int128_t, etc

    template<class T>
    struct mk_unsigned
    {
      // If T is an integral (except bool) or enumeration type, provides the
      // member typedef type which is the unsigned integer type corresponding to
      // T, with the same cv-qualifiers. Otherwise, the program is ill-formed.
      static_assert((emp::is_integral_v<T> || emp::is_enum_v<T>)
                 && !JLN_MP_IS_SAME_V(T, bool volatile const),
        "make_unsigned<T> requires that T shall be a (possibly cv-qualified) "
        "integral type or enumeration but not a bool type.");

      // If T is an enumeration type or char, wchar_t, char8_t (since C++20),
      // char16_t, char32_t, the unsigned integer type with the smallest rank
      // having the same sizeof as T is provided.
      using type = typename select_min_rank<sizeof(T)>::unsigned_type;
    };

    // If T is unsigned or signed char, short, int, long, long long,
    // the unsigned type from this list corresponding to T is provided.
    template<> struct mk_unsigned<const volatile char>          { using type = unsigned char; };
    template<> struct mk_unsigned<const volatile unsigned char> { using type = unsigned char; };
    template<> struct mk_unsigned<const volatile   signed char> { using type = unsigned char; };
    template<> struct mk_unsigned<const volatile unsigned short> { using type = unsigned short; };
    template<> struct mk_unsigned<const volatile   signed short> { using type = unsigned short; };
    template<> struct mk_unsigned<const volatile unsigned int> { using type = unsigned int; };
    template<> struct mk_unsigned<const volatile   signed int> { using type = unsigned int; };
    template<> struct mk_unsigned<const volatile unsigned long> { using type = unsigned long; };
    template<> struct mk_unsigned<const volatile   signed long> { using type = unsigned long; };
    template<> struct mk_unsigned<const volatile unsigned long long> { using type = unsigned long long; };
    template<> struct mk_unsigned<const volatile   signed long long> { using type = unsigned long long; };
    // TODO support of __uint128_t, __int128_t, etc

    // TODO
    // template<bool IsConst, bool IsVolatile>
    // struct match_cv_select
    // {
    //   template<class T> using f = T;
    // };
    //
    // template<bool IsVolatile>
    // struct match_cv_select<true, IsVolatile>
    // {
    //   template<class T> using f = T const;
    // };
    //
    // template<bool IsConst>
    // struct match_cv_select<IsConst, true>
    // {
    //   template<class T> using f = T volatile;
    // };
    //
    // template<>
    // struct match_cv_select<true, true>
    // {
    //   template<class T> using f = T volatile const;
    // };

    template<class Qualified, class UnQualified>
    struct match_cv { using type = UnQualified; };

    template<class Qualified, class UnQualified>
    struct match_cv<Qualified const, UnQualified> { using type = UnQualified const; };

    template<class Qualified, class UnQualified>
    struct match_cv<Qualified volatile, UnQualified> { using type = UnQualified volatile; };

    template<class Qualified, class UnQualified>
    struct match_cv<Qualified volatile const, UnQualified> { using type = UnQualified volatile const; };
  }

  JLN_MP_MAKE_TRAIT_WRAP_T(make_signed, (class T),
    detail::match_cv<T, typename detail::mk_signed<T volatile const>::type>);
  JLN_MP_MAKE_TRAIT_WRAP_T(make_unsigned, (class T),
    detail::match_cv<T, typename detail::mk_unsigned<T volatile const>::type>);

  namespace emp
  {
    // TODO no stl
    using std::remove_extent;
    // TODO no stl
    using std::remove_all_extents;
    // TODO no stl (good clang, msvc)
    using std::remove_pointer;
  }
  JLN_MP_MAKE_TRAIT_T(remove_extent, (class T), emp::remove_extent<T>);
  JLN_MP_MAKE_TRAIT_T(remove_all_extents, (class T), emp::remove_all_extents<T>);
  JLN_MP_MAKE_TRAIT_T(remove_pointer, (class T), emp::remove_pointer<T>);

  namespace detail
  {
    // TODO replace with std::add_pointer ?

    template<class T, class = void>
    struct add_pointer_impl
    {
      using type = T;
    };

    // TODO replace remove_reference_t with specialization of T& and T&& ?

    template<class T>
    struct add_pointer_impl<T, emp::void_t<emp::remove_reference_t<T>*>>
    {
      using type = emp::remove_reference_t<T>*;
    };
  }
  JLN_MP_MAKE_TRAIT_WRAP_T(add_pointer, (class T), detail::add_pointer_impl<T>);

  // TODO remove that
  JLN_MP_MAKE_TRAIT(aligned_storage, (class Len, class... Alignment),
    typename std::aligned_storage<Len::value, Alignment::value...>::type);
  // TODO remove that
  JLN_MP_MAKE_TRAIT(aligned_union, (class Len, class... xs),
    typename std::aligned_union<Len::value, xs...>::type);

  namespace detail
  {
    /* decay:
     * remove_reference -> decay_impl{
     *    is_array
     *      ? remove_extent -> add_pointer
     *      : is_function
     *          ? add_pointer
     *          : remove_cv
     * }
     */

    // TODO faster with __is_function and __is_array ?

    // is_function
    template<class T, class = void>
    struct decay_impl2
    {
      using type = T;
    };

    // is_function
    template<class T>
    struct decay_impl2<T, emp::void_t<T*>>
    {
      using type = T*;
    };

    // not is_function
    template<class T>
    struct decay_impl2<T const volatile, void>
    {
      using type = T;
    };

    // not is_array
    template<class T>
    struct decay_impl
      : decay_impl2<T volatile const> // a function is always cv unqualified
    {};

    template<class T>
    struct decay_impl<T[]>
    {
      using type = T*;
    };

    template<class T, std::size_t n>
    struct decay_impl<T[n]>
    {
      using type = T*;
    };
  }
  JLN_MP_MAKE_TRAIT_WRAP_T(decay, (class T), detail::decay_impl<emp::remove_reference_t<T>>);

#if defined(__cpp_lib_unwrap_ref) && __cpp_lib_unwrap_ref >= 201811L
  JLN_MP_MAKE_STD_TRAIT_P1(unwrap_ref_decay);
  JLN_MP_MAKE_STD_TRAIT_P1(unwrap_reference);
#endif
#if defined(__cpp_lib_remove_cvref) && __cpp_lib_remove_cvref >= 201711L
  JLN_MP_MAKE_STD_TRAIT_P1(remove_cvref);
#else
  JLN_MP_MAKE_TRAIT(remove_cvref, (class x),
    typename std::remove_cv<typename std::remove_reference<x>::type>::type);
#endif
#if __cplusplus >= 202002L
// TODO __cpp_lib_common_reference 	Make std::common_reference_t of std::reference_wrapper a reference type 	202302L 	<type_traits> 	(C++23) 	P2655R3
// TODO __cpp_lib_common_reference_wrapper 	Make std::common_reference_t of std::reference_wrapper a reference type 	202302L 	<functional> 	(C++23) 	P2655R3
  JLN_MP_MAKE_STD_TRAIT_XS(common_reference);
  JLN_MP_MAKE_STD_TRAIT_XS(basic_common_reference);
#else
  // TODO remove that
  JLN_MP_MAKE_STD_TRAIT_P1(result_of);
#endif
  JLN_MP_MAKE_TRAIT_P1(JLN_MP_TRAIT_BUILTIN_T(underlying_type, MSVC, 0, 0));
  JLN_MP_MAKE_STD_TRAIT_XS(common_type);

#undef JLN_MP_TRAIT_BUILTIN_IMPL_IS
#undef JLN_MP_TRAIT_STD_IMPL
#undef JLN_MP_MAKE_TRAIT
#undef JLN_MP_MAKE_TRAIT_P1_I
#undef JLN_MP_MAKE_TRAIT_P2_I
#undef JLN_MP_MAKE_TRAIT_XS_I
#undef JLN_MP_MAKE_TRAIT_P1
#undef JLN_MP_MAKE_TRAIT_P2
#undef JLN_MP_MAKE_TRAIT_XS
#undef JLN_MP_MAKE_STD_TRAIT_P1
#undef JLN_MP_MAKE_STD_TRAIT_P2
#undef JLN_MP_MAKE_STD_TRAIT_XS
#undef JLN_MP_TRAIT_COND_CLANG
#undef JLN_MP_TRAIT_COND_MSVC
#undef JLN_MP_TRAIT_COND_GCC
#undef JLN_MP_TRAIT_COND_EVAL_I
#undef JLN_MP_TRAIT_COND_EVAL
#undef JLN_MP_TRAIT_COND_SELECT_0
#undef JLN_MP_TRAIT_COND_SELECT_1
#undef JLN_MP_TRAIT_COND_SELECT_II
#undef JLN_MP_TRAIT_COND_SELECT_I
#undef JLN_MP_TRAIT_COND_SELECT
#undef JLN_MP_TRAIT_BUILTIN2_IS
#undef JLN_MP_TRAIT_BUILTIN
#undef JLN_MP_CONSTEXPR_VAR

#undef JLN_MP_IS_VOID
#undef JLN_MP_IS_NULL_POINTER
}
