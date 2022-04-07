#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/utility/stl_traits.hpp>
#include <jln/mp/smp/functional/identity.hpp>

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
