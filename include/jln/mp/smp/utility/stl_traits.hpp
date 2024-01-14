// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/utility/stl_traits.hpp>
#include <jln/mp/smp/functional/identity.hpp>

namespace jln::mp
{

#define JLN_MP_SMP_MAKE_BASIC_TRAIT(Name)           \
  namespace smp::traits                             \
  {                                                 \
    template<class C = identity>                    \
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

#define JLN_MP_SMP_MAKE_TRAIT(Name, arity, output) \
  JLN_MP_SMP_MAKE_BASIC_TRAIT(Name)


  // primary type categories:
#if __cplusplus >= 201703L
  JLN_MP_SMP_MAKE_TRAIT(is_void, 1, types::boolean)
#endif
#if __cplusplus >= 201402L
  JLN_MP_SMP_MAKE_TRAIT(is_null_pointer, 1, types::boolean)
#endif
  JLN_MP_SMP_MAKE_TRAIT(is_integral, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_floating_point, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_array, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_pointer, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_lvalue_reference, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_rvalue_reference, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_member_object_pointer, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_member_function_pointer, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_enum, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_union, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_class, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_function, 1, types::boolean)

  // composite type categories:
  JLN_MP_SMP_MAKE_TRAIT(is_reference, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_arithmetic, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_fundamental, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_object, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_scalar, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_compound, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_member_pointer, 1, types::boolean)

  // type properties:
  JLN_MP_SMP_MAKE_TRAIT(is_const, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_volatile, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_trivial, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_copyable, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_standard_layout, 1, types::boolean)
#if __cplusplus <= 201703L
  JLN_MP_SMP_MAKE_TRAIT(is_pod, 1, types::boolean)
#endif
  JLN_MP_SMP_MAKE_TRAIT(is_empty, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_polymorphic, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_abstract, 1, types::boolean)
#if __cplusplus >= 201402L
  JLN_MP_SMP_MAKE_TRAIT(is_final, 1, types::boolean)
#endif
#if __cplusplus >= 201703L
  JLN_MP_SMP_MAKE_TRAIT(is_aggregate, 1, types::boolean)
#endif
  JLN_MP_SMP_MAKE_TRAIT(is_signed, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_unsigned, 1, types::boolean)
#if defined(__cpp_lib_bounded_array_traits) && __cpp_lib_bounded_array_traits
  JLN_MP_SMP_MAKE_TRAIT(is_bounded_array, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_unbounded_array, 1, types::boolean)
#endif
  JLN_MP_SMP_MAKE_TRAIT(is_constructible, -1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_default_constructible, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_copy_constructible, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_move_constructible, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_assignable, 2, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_copy_assignable, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_move_assignable, 1, types::boolean)
#if __cplusplus >= 201703L
  JLN_MP_SMP_MAKE_TRAIT(is_swappable_with, 2, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_swappable, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_swappable_with, 2, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_swappable, 1, types::boolean)
#endif
  JLN_MP_SMP_MAKE_TRAIT(is_destructible, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_constructible, -1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_default_constructible, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_copy_constructible, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_move_constructible, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_assignable, 2, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_copy_assignable, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_move_assignable, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_trivially_destructible, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_constructible, -1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_default_constructible, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_copy_constructible, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_move_constructible, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_assignable, 2, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_copy_assignable, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_move_assignable, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_destructible, 1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(has_virtual_destructor, 1, types::boolean)
#if __cplusplus >= 201703L
  JLN_MP_SMP_MAKE_TRAIT(has_unique_object_representations, 1, types::boolean)
#endif

  // type property queries:
  JLN_MP_SMP_MAKE_TRAIT(alignment_of, 1, types::number)
  JLN_MP_SMP_MAKE_TRAIT(rank, 1, types::number)

  JLN_MP_SMP_MAKE_BASIC_TRAIT(extent)

  // type relations:
  JLN_MP_SMP_MAKE_TRAIT(is_same, 2, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_base_of, 2, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_convertible, 2, types::boolean)
#if defined(__cpp_lib_is_nothrow_convertible) && __cpp_lib_is_nothrow_convertible
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_convertible, 2, types::boolean)
#endif
#if defined(__cpp_lib_is_layout_compatible) && __cpp_lib_is_layout_compatible
  JLN_MP_SMP_MAKE_TRAIT(is_layout_compatible, 2, types::boolean)
#endif
#if defined(__cpp_lib_is_pointer_interconvertible) && __cpp_lib_is_pointer_interconvertible
  JLN_MP_SMP_MAKE_TRAIT(is_pointer_interconvertible_base_of, 2, types::boolean)
#endif
#if __cplusplus >= 201703L
  JLN_MP_SMP_MAKE_TRAIT(is_invocable, -1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_invocable_r, -1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_invocable, -1, types::boolean)
  JLN_MP_SMP_MAKE_TRAIT(is_nothrow_invocable_r, -1, types::boolean)
#endif

  // const-volatile modifications:
  JLN_MP_SMP_MAKE_TRAIT(remove_const, 1, types::any)
  JLN_MP_SMP_MAKE_TRAIT(remove_volatile, 1, types::any)
  JLN_MP_SMP_MAKE_TRAIT(remove_cv, 1, types::any)
  JLN_MP_SMP_MAKE_TRAIT(add_const, 1, types::any)
  JLN_MP_SMP_MAKE_TRAIT(add_volatile, 1, types::any)
  JLN_MP_SMP_MAKE_TRAIT(add_cv, 1, types::any)

  // reference modifications:
  JLN_MP_SMP_MAKE_TRAIT(remove_reference, 1, types::any)
  JLN_MP_SMP_MAKE_TRAIT(add_lvalue_reference, 1, types::any)
  JLN_MP_SMP_MAKE_TRAIT(add_rvalue_reference, 1, types::any)

  // sign modifications:
  JLN_MP_SMP_MAKE_TRAIT(make_signed, 1, types::any)
  JLN_MP_SMP_MAKE_TRAIT(make_unsigned, 1, types::any)

  // array modifications:
  JLN_MP_SMP_MAKE_TRAIT(remove_extent, 1, types::any)
  JLN_MP_SMP_MAKE_TRAIT(remove_all_extents, 1, types::any)

  // pointer modifications:
  JLN_MP_SMP_MAKE_TRAIT(remove_pointer, 1, types::any)
  JLN_MP_SMP_MAKE_TRAIT(add_pointer, 1, types::any)

  // other transformations:
  JLN_MP_SMP_MAKE_TRAIT(decay, 1, types::any)
#if defined(__cpp_lib_unwrap_ref) && __cpp_lib_unwrap_ref \
  /* unwrap_reference is missing from <type_traits> with libc++-15 */ \
  && (!JLN_MP_LIBCXX || JLN_MP_LIBCXX >= 16000)
  JLN_MP_SMP_MAKE_TRAIT(unwrap_ref_decay, 1, types::any)
  JLN_MP_SMP_MAKE_TRAIT(unwrap_reference, 1, types::any)
#endif
#if defined(__cpp_lib_remove_cvref) && __cpp_lib_remove_cvref
  JLN_MP_SMP_MAKE_TRAIT(remove_cvref, 1, types::any)
#endif
#if __cplusplus >= 202002L
  JLN_MP_SMP_MAKE_TRAIT(common_reference, 1, types::any)
  JLN_MP_SMP_MAKE_TRAIT(basic_common_reference, 1, types::any)
#else
  JLN_MP_SMP_MAKE_TRAIT(result_of, 1, types::any)
#endif
  JLN_MP_SMP_MAKE_TRAIT(underlying_type, 1, types::any)
  JLN_MP_SMP_MAKE_TRAIT(common_type, 1, types::any)
#if __cplusplus >= 201703L
  JLN_MP_SMP_MAKE_TRAIT(invoke_result, 1, types::any)
#endif

  JLN_MP_SMP_MAKE_TRAIT(aligned_storage, 1, types::any)
  JLN_MP_SMP_MAKE_TRAIT(aligned_union, 1, types::any)

#undef JLN_MP_SMP_MAKE_BASIC_TRAIT
#undef JLN_MP_SMP_MAKE_TRAIT
}
