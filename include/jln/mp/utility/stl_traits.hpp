// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/detail/compiler.hpp>

#include <type_traits>

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


#if defined(_GLIBCXX_RELEASE)
#  define JLN_MP_LIBSTDCXX _GLIBCXX_RELEASE
#else
#  define JLN_MP_LIBSTDCXX 0
#endif

#if defined(_LIBCPP_VERSION)
#  define JLN_MP_LIBCXX _LIBCPP_VERSION
#else
#  define JLN_MP_LIBCXX 0
#endif

#if defined(_MSVC_STL_UPDATE)
#  define JLN_MP_LIBMS _MSVC_STL_UPDATE
#else
#  define JLN_MP_LIBMS 0
#endif


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
    template<class x, class i>
    using f = JLN_MP_CALL_TRACE(C, typename std::extent<x, i::value>::type);
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
// is_nothrow_convertible is an alias, not a class: https://github.com/microsoft/STL/issues/4317
# if JLN_MP_WORKAROUND(JLN_MP_LIBMS, <= 202401)
  template<class C = identity>
  struct is_nothrow_convertible
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      std::bool_constant<std::is_nothrow_convertible_v<xs...>>);
  };

  namespace emp
  {
    template<class... xs>
    using is_nothrow_convertible = std::bool_constant<std::is_nothrow_convertible_v<xs...>>;
  }

  template<>
  struct is_nothrow_convertible<identity>
  {
    template<class... xs>
    using f = std::bool_constant<std::is_nothrow_convertible_v<xs...>>;
  };
# else
  JLN_MP_MAKE_TRAIT(is_nothrow_convertible);
# endif
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
#if defined(__cpp_lib_unwrap_ref) && __cpp_lib_unwrap_ref \
  /* unwrap_reference is missing from <type_traits> with libc++-15 */ \
  && (!JLN_MP_LIBCXX || JLN_MP_LIBCXX >= 16000)
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

// deprecated with C++23
#if __cplusplus < 202302L
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
#endif

#undef JLN_MP_MAKE_TRAIT
}
