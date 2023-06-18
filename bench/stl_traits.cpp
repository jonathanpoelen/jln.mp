// S = xxx<...>::type
// V = xxx_v<...>
// T = xxx_t<...>
// B = xxx<...>
// values: S, V, T, SV, ST, SVT, B
#ifndef BENCH_TYPE
# define BENCH_TYPE SVT
#endif

#ifndef BENCH_STD
# define BENCH_STD 0
#endif

#ifndef BENCH_ALL
# define BENCH_ALL 0
#endif

#ifndef BENCH_SHOW_SOURCE
# define BENCH_SHOW_SOURCE 0
#endif

#ifdef IN_IDE_PARSER
# define NREPEAT 0
#else
# ifndef NREPEAT
#   define NREPEAT 800
# endif
#endif

#if BENCH_STD
# define NAMESPACE std
#else
# define NAMESPACE jln::mp::traits::emp
#endif


#if BENCH_SHOW_SOURCE
# if BENCH_STD
#   include <type_traits>
# endif
# include <jln/mp/detail/unpack.hpp>
# include <jln/mp/detail/compiler.hpp>
#else
# include <jln/mp/algorithm/transform.hpp>
# include <jln/mp/algorithm/make_int_sequence.hpp>

# include <jln/mp/utility/stl_traits.hpp>
# include <type_traits>
#endif


#define PP_CONCAT(a, b) PP_CONCAT_I(a, b)
#define PP_CONCAT_I(a, b) a##b

#if BENCH_SHOW_SOURCE
# define BENCH_DECL(nrep, wrapper, expr) \
  PRINT [T = number<0>..number<nrep>] expr;
#else
# define BENCH_DECL(nrep, wrapper, expr)                                            \
  namespace PP_CONCAT(n, __COUNTER__) {                                             \
    struct wrapper { template<class T> using f = expr; };                           \
    using l = jln::mp::emp::make_int_sequence_c<nrep, jln::mp::transform<wrapper>>; \
  }
#endif

#define BENCH_S(n, algo, values) \
  BENCH_DECL(n, bs, typename algo<JLN_MP_UNPACK values>::type)

#define BENCH_T(n, algo, values) \
  BENCH_DECL(n, bt, algo##_t<JLN_MP_UNPACK values>)

#define BENCH_V(n, algo, values) \
  BENCH_DECL(n, bv, jln::mp::number<algo##_v<JLN_MP_UNPACK values>>)

#define BENCH_B(n, algo, values) \
  BENCH_DECL(n, b, algo<JLN_MP_UNPACK values>)

#define BENCH_ST(n, algo, values) \
  BENCH_S(n, algo, values)        \
  BENCH_T(n, algo, values)

#define BENCH_SV(n, algo, values) \
  BENCH_S(n, algo, values)        \
  BENCH_V(n, algo, values)

#define BENCH_0(n, algo, values)

#define BENCH_SELECT_ST_S BENCH_S
#define BENCH_SELECT_ST_V BENCH_0
#define BENCH_SELECT_ST_T BENCH_T
#define BENCH_SELECT_ST_SV BENCH_S
#define BENCH_SELECT_ST_ST BENCH_ST
#define BENCH_SELECT_ST_SVT BENCH_ST
#define BENCH_SELECT_ST_B BENCH_B

#define BENCH_SELECT_SV_S BENCH_S
#define BENCH_SELECT_SV_V BENCH_V
#define BENCH_SELECT_SV_T BENCH_0
#define BENCH_SELECT_SV_SV BENCH_SV
#define BENCH_SELECT_SV_ST BENCH_S
#define BENCH_SELECT_SV_SVT BENCH_SV
#define BENCH_SELECT_SV_B BENCH_B

#define BENCH_SELECT(bench_filter, bench_accept) BENCH_SELECT_##bench_accept##_##bench_filter

#define BENCH(n, bench_filter, bench_accept, algo, values) \
  BENCH_SELECT(bench_filter, bench_accept)(n, NAMESPACE::algo, values)


template<class T>
struct X
{
  enum class E : int;
};

template<class T, class U>
void swap(X<T>&, X<U>&) noexcept;


JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Wundef")

#if BENCH_ALL
# define BENCH_IS_CONST 1
# define BENCH_IS_VOLATILE 1
# define BENCH_IS_TRIVIAL 1
# define BENCH_IS_TRIVIALLY_COPYABLE 1
# define BENCH_IS_ABSTRACT 1
# define BENCH_IS_AGGREGATE 1
# define BENCH_IS_BASE_OF 1
# define BENCH_IS_CLASS 1
# define BENCH_IS_EMPTY 1
# define BENCH_IS_ENUM 1
# define BENCH_IS_FINAL 1
# define BENCH_IS_POLYMORPHIC 1
# define BENCH_IS_UNION 1
# define BENCH_IS_SIGNED 1
# define BENCH_IS_UNSIGNED 1
# define BENCH_IS_BOUNDED_ARRAY 1
# define BENCH_ADD_LVALUE_REFERENCE 1
# define BENCH_ADD_RVALUE_REFERENCE 1
# define BENCH_HAS_UNIQUE_OBJECT_REPRESENTATIONS 1
# define BENCH_IS_VOID 1
# define BENCH_IS_NULL_POINTER 1
# define BENCH_IS_INTEGRAL 1
# define BENCH_IS_FLOATING_POINT 1
# define BENCH_IS_ARRAY 1
# define BENCH_IS_POINTER 1
# define BENCH_IS_LVALUE_REFERENCE 1
# define BENCH_IS_RVALUE_REFERENCE 1
# define BENCH_IS_REFERENCE 1
# define BENCH_IS_FUNCTION 1
# define BENCH_IS_MEMBER_OBJECT_POINTER 1
# define BENCH_IS_MEMBER_FUNCTION_POINTER 1
# define BENCH_IS_ARITHMETIC 1
# define BENCH_IS_FUNDAMENTAL 1
# define BENCH_IS_OBJECT 1
# define BENCH_IS_MEMBER_POINTER 1
# define BENCH_IS_SCALAR 1
# define BENCH_IS_STANDARD_LAYOUT 1
# define BENCH_IS_COMPOUND 1
# define BENCH_IS_CONVERTIBLE 1
# define BENCH_IS_NOTHROW_CONVERTIBLE 1
# define BENCH_IS_SCOPED_ENUM 1
# define BENCH_IS_CONSTRUCTIBLE 1
# define BENCH_IS_DEFAULT_CONSTRUCTIBLE 1
# define BENCH_IS_COPY_CONSTRUCTIBLE 1
# define BENCH_IS_MOVE_CONSTRUCTIBLE 1
# define BENCH_IS_TRIVIALLY_CONSTRUCTIBLE 1
# define BENCH_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE 1
# define BENCH_IS_TRIVIALLY_COPY_CONSTRUCTIBLE 1
# define BENCH_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE 1
# define BENCH_IS_NOTHROW_CONSTRUCTIBLE 1
# define BENCH_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE 1
# define BENCH_IS_NOTHROW_COPY_CONSTRUCTIBLE 1
# define BENCH_IS_NOTHROW_MOVE_CONSTRUCTIBLE 1
# define BENCH_IS_ASSIGNABLE 1
# define BENCH_IS_COPY_ASSIGNABLE 1
# define BENCH_IS_MOVE_ASSIGNABLE 1
# define BENCH_IS_NOTHROW_ASSIGNABLE 1
# define BENCH_IS_NOTHROW_COPY_ASSIGNABLE 1
# define BENCH_IS_NOTHROW_MOVE_ASSIGNABLE 1
# define BENCH_IS_TRIVIALLY_ASSIGNABLE 1
# define BENCH_IS_TRIVIALLY_COPY_ASSIGNABLE 1
# define BENCH_IS_TRIVIALLY_MOVE_ASSIGNABLE 1
# define BENCH_IS_DESTRUCTIBLE 1
# define BENCH_IS_TRIVIALLY_DESTRUCTIBLE 1
# define BENCH_IS_NOTHROW_DESTRUCTIBLE 1
# define BENCH_IS_IMPLICIT_LIFETIME 1
# define BENCH_IS_SWAPPABLE 1
# define BENCH_IS_NOTHROW_SWAPPABLE 1
# define BENCH_IS_SWAPPABLE_WITH 1
# define BENCH_IS_NOTHROW_SWAPPABLE_WITH 1
# define BENCH_HAS_VIRTUAL_DESTRUCTOR 1
# define BENCH_IS_SAME 1
# define BENCH_IS_LAYOUT_COMPATIBLE 1
# define BENCH_IS_POINTER_INTERCONVERTIBLE_BASE_OF 1
# define BENCH_ALIGNMENT_OF 1
# define BENCH_RANK 1
# define BENCH_EXTENT 1
# define BENCH_REMOVE_CONST 1
# define BENCH_REMOVE_VOLATILE 1
# define BENCH_REMOVE_CV 1
# define BENCH_REMOVE_EXTENTS 1
# define BENCH_REMOVE_ALL_EXTENTS 1
# define BENCH_REMOVE_POINTER 1
# define BENCH_REMOVE_REFERENCE 1
# define BENCH_REMOVE_CVREF 1
# define BENCH_REFERENCE_CONSTRUCTS_FROM_TEMPORARY 1
# define BENCH_REFERENCE_CONVERTS_FROM_TEMPORARY 1
# define BENCH_ADD_POINTER 1
# define BENCH_ADD_CV 1
# define BENCH_ADD_CONST 1
# define BENCH_ADD_VOLATILE 1
# define BENCH_MAKE_SIGNED 1
# define BENCH_MAKE_UNSIGNED 1
# define BENCH_DECAY 1
# define BENCH_UNWRAP_REFERENCE 1
# define BENCH_UNWRAP_REF_DECAY 1
# define BENCH_INVOKE_RESULT 1
# define BENCH_IS_INVOCABLE 1
# define BENCH_IS_INVOCABLE_R 1
# define BENCH_IS_NOTHROW_INVOCABLE 1
# define BENCH_IS_NOTHROW_INVOCABLE_R 1
# define BENCH_UNDERLYING_TYPE 1
# define BENCH_COMMON_TYPE 1
# define BENCH_COMMON_REFERENCE 1
#endif


#if BENCH_IS_CONST
  BENCH(NREPEAT, BENCH_TYPE, SV, is_const, (T))
#endif

#if BENCH_IS_VOLATILE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_volatile, (T))
#endif

#if BENCH_IS_TRIVIAL
  BENCH(NREPEAT, BENCH_TYPE, SV, is_trivial, (T))
#endif

#if BENCH_IS_TRIVIALLY_COPYABLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_trivially_copyable, (T))
#endif

#if BENCH_IS_ABSTRACT
  BENCH(NREPEAT, BENCH_TYPE, SV, is_abstract, (T))
#endif

#if BENCH_IS_AGGREGATE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_aggregate, (T))
#endif

#if BENCH_IS_BASE_OF
  BENCH(NREPEAT, BENCH_TYPE, SV, is_base_of, (T, T))
#endif

#if BENCH_IS_CLASS
  BENCH(NREPEAT, BENCH_TYPE, SV, is_class, (T))
#endif

#if BENCH_IS_EMPTY
  BENCH(NREPEAT, BENCH_TYPE, SV, is_empty, (T))
#endif

#if BENCH_IS_ENUM
  BENCH(NREPEAT, BENCH_TYPE, SV, is_enum, (T))
#endif

#if BENCH_IS_FINAL
  BENCH(NREPEAT, BENCH_TYPE, SV, is_final, (T))
#endif

#if BENCH_IS_POLYMORPHIC
  BENCH(NREPEAT, BENCH_TYPE, SV, is_polymorphic, (T))
#endif

#if BENCH_IS_UNION
  BENCH(NREPEAT, BENCH_TYPE, SV, is_union, (T))
#endif

#if BENCH_IS_SIGNED
  BENCH(NREPEAT, BENCH_TYPE, SV, is_signed, (T))
#endif

#if BENCH_IS_UNSIGNED
  BENCH(NREPEAT, BENCH_TYPE, SV, is_unsigned, (T))
#endif

#if BENCH_IS_BOUNDED_ARRAY && (! BENCH_STD || __cpp_lib_bounded_array_traits >= 201902L)
  BENCH(NREPEAT, BENCH_TYPE, SV, is_bounded_array, (T))
#endif

#if BENCH_ADD_LVALUE_REFERENCE
  BENCH(NREPEAT, BENCH_TYPE, ST, add_lvalue_reference, (T))
#endif

#if BENCH_ADD_RVALUE_REFERENCE
  BENCH(NREPEAT, BENCH_TYPE, ST, add_rvalue_reference, (T))
#endif

#if BENCH_HAS_UNIQUE_OBJECT_REPRESENTATIONS
  BENCH(NREPEAT, BENCH_TYPE, SV, has_unique_object_representations, (T))
#endif

#if BENCH_IS_VOID
  BENCH(NREPEAT, BENCH_TYPE, SV, is_void, (T))
#endif

#if BENCH_IS_NULL_POINTER
  BENCH(NREPEAT, BENCH_TYPE, SV, is_null_pointer, (T))
#endif

#if BENCH_IS_INTEGRAL
  BENCH(NREPEAT, BENCH_TYPE, SV, is_integral, (T))
#endif

#if BENCH_IS_FLOATING_POINT
  BENCH(NREPEAT, BENCH_TYPE, SV, is_floating_point, (T))
#endif

#if BENCH_IS_ARRAY
  BENCH(NREPEAT, BENCH_TYPE, SV, is_array, (T))
#endif

#if BENCH_IS_POINTER
  BENCH(NREPEAT, BENCH_TYPE, SV, is_pointer, (T))
#endif

#if BENCH_IS_LVALUE_REFERENCE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_lvalue_reference, (T))
#endif

#if BENCH_IS_RVALUE_REFERENCE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_rvalue_reference, (T))
#endif

#if BENCH_IS_REFERENCE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_reference, (T))
#endif

#if BENCH_IS_FUNCTION
  BENCH(NREPEAT, BENCH_TYPE, SV, is_function, (T))
#endif

#if BENCH_IS_MEMBER_OBJECT_POINTER
# if ! BENCH_IS_MEMBER_OBJECT_POINTER_DISABLE_T
  BENCH(NREPEAT, BENCH_TYPE, SV, is_member_object_pointer, (T))
# endif
# if ! BENCH_IS_MEMBER_OBJECT_POINTER_DISABLE_MEM_T
  BENCH(NREPEAT, BENCH_TYPE, SV, is_member_object_pointer, (int T::*))
# endif
#endif

#if BENCH_IS_MEMBER_FUNCTION_POINTER
# if ! BENCH_IS_MEMBER_FUNCTION_POINTER_DISABLE_T
  BENCH(NREPEAT, BENCH_TYPE, SV, is_member_function_pointer, (T))
# endif
# if ! BENCH_IS_MEMBER_FUNCTION_POINTER_DISABLE_MEM_T
  BENCH(NREPEAT, BENCH_TYPE, SV, is_member_function_pointer, (int(T::*)()))
# endif
#endif

#if BENCH_IS_MEMBER_POINTER
# if ! BENCH_IS_MEMBER_POINTER_DISABLE_T
  BENCH(NREPEAT, BENCH_TYPE, SV, is_member_pointer, (T))
# endif
# if ! BENCH_IS_MEMBER_POINTER_DISABLE_MEM_T
  BENCH(NREPEAT, BENCH_TYPE, SV, is_member_pointer, (int T::*))
# endif
#endif

#if BENCH_IS_ARITHMETIC
  BENCH(NREPEAT, BENCH_TYPE, SV, is_arithmetic, (T))
#endif

#if BENCH_IS_FUNDAMENTAL
  BENCH(NREPEAT, BENCH_TYPE, SV, is_fundamental, (T))
#endif

#if BENCH_IS_OBJECT
  BENCH(NREPEAT, BENCH_TYPE, SV, is_object, (T))
#endif

#if BENCH_IS_SCALAR
  BENCH(NREPEAT, BENCH_TYPE, SV, is_scalar, (T))
#endif

#if BENCH_IS_STANDARD_LAYOUT
  BENCH(NREPEAT, BENCH_TYPE, SV, is_standard_layout, (T))
#endif

#if BENCH_IS_COMPOUND
  BENCH(NREPEAT, BENCH_TYPE, SV, is_compound, (T))
#endif

#if BENCH_IS_CONVERTIBLE
# if ! BENCH_IS_CONVERTIBLE_DISABLE_T
  BENCH(NREPEAT, BENCH_TYPE, SV, is_convertible, (T, T))
# endif
# if ! BENCH_IS_CONVERTIBLE_DISABLE_REF
  BENCH(NREPEAT, BENCH_TYPE, SV, is_convertible, (T&, T&))
# endif
# if ! BENCH_IS_CONVERTIBLE_DISABLE_REF_FALSE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_convertible, (T&, int))
# endif
#endif

#if BENCH_IS_NOTHROW_CONVERTIBLE && (! BENCH_STD || __cpp_lib_is_nothrow_convertible >= 201806L)
# if ! BENCH_IS_NOTHROW_CONVERTIBLE_DISABLE_T
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_convertible, (T, T))
# endif
# if ! BENCH_IS_NOTHROW_CONVERTIBLE_DISABLE_REF
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_convertible, (T&, T&))
# endif
# if ! BENCH_IS_NOTHROW_CONVERTIBLE_DISABLE_REF_FALSE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_convertible, (T&, int))
# endif
#endif

#if BENCH_IS_SCOPED_ENUM && (! BENCH_STD || __cpp_lib_is_scoped_enum >= 202011L)
# if ! BENCH_IS_SCOPED_ENUM_DISABLE_T
  BENCH(NREPEAT, BENCH_TYPE, SV, is_scoped_enum, (T))
# endif
# if ! BENCH_IS_SCOPED_ENUM_DISABLE_E
  BENCH(NREPEAT, BENCH_TYPE, SV, is_scoped_enum, (typename X<T>::E))
# endif
#endif

#if BENCH_IS_CONSTRUCTIBLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_constructible, (T))
#endif

#if BENCH_IS_DEFAULT_CONSTRUCTIBLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_default_constructible, (T))
#endif

#if BENCH_IS_COPY_CONSTRUCTIBLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_copy_constructible, (T))
#endif

#if BENCH_IS_MOVE_CONSTRUCTIBLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_move_constructible, (T))
#endif

#if BENCH_IS_TRIVIALLY_CONSTRUCTIBLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_trivially_constructible, (T))
#endif

#if BENCH_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_trivially_default_constructible, (T))
#endif

#if BENCH_IS_TRIVIALLY_COPY_CONSTRUCTIBLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_trivially_copy_constructible, (T))
#endif

#if BENCH_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_trivially_move_constructible, (T))
#endif

#if BENCH_IS_NOTHROW_CONSTRUCTIBLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_constructible, (T))
#endif

#if BENCH_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_default_constructible, (T))
#endif

#if BENCH_IS_NOTHROW_COPY_CONSTRUCTIBLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_copy_constructible, (T))
#endif

#if BENCH_IS_NOTHROW_MOVE_CONSTRUCTIBLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_move_constructible, (T))
#endif

#if BENCH_IS_ASSIGNABLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_assignable, (T, T))
#endif

#if BENCH_IS_COPY_ASSIGNABLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_copy_assignable, (T))
#endif

#if BENCH_IS_MOVE_ASSIGNABLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_move_assignable, (T))
#endif

#if BENCH_IS_NOTHROW_ASSIGNABLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_assignable, (T, T))
#endif

#if BENCH_IS_NOTHROW_COPY_ASSIGNABLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_copy_assignable, (T))
#endif

#if BENCH_IS_NOTHROW_MOVE_ASSIGNABLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_move_assignable, (T))
#endif

#if BENCH_IS_TRIVIALLY_ASSIGNABLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_trivially_assignable, (T, T))
#endif

#if BENCH_IS_TRIVIALLY_COPY_ASSIGNABLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_trivially_copy_assignable, (T))
#endif

#if BENCH_IS_TRIVIALLY_MOVE_ASSIGNABLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_trivially_move_assignable, (T))
#endif

#if BENCH_IS_DESTRUCTIBLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_destructible, (T))
#endif

#if BENCH_IS_TRIVIALLY_DESTRUCTIBLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_trivially_destructible, (T))
#endif

#if BENCH_IS_NOTHROW_DESTRUCTIBLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_destructible, (T))
#endif

#if BENCH_IS_IMPLICIT_LIFETIME && (! BENCH_STD || __cpp_lib_is_implicit_lifetime >= 202302L)
  BENCH(NREPEAT, BENCH_TYPE, SV, is_implicit_lifetime, (T))
#endif

#if BENCH_IS_SWAPPABLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_swappable, (T))
#endif

#if BENCH_IS_NOTHROW_SWAPPABLE
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_swappable, (T))
#endif

#if BENCH_IS_SWAPPABLE_WITH
# if ! BENCH_IS_SWAPPABLE_WITH_DISABLE_REF
  BENCH(NREPEAT, BENCH_TYPE, SV, is_swappable_with, (T&, T&))
# endif
# if ! BENCH_IS_SWAPPABLE_WITH_DISABLE_REF2
  BENCH(NREPEAT, BENCH_TYPE, SV, is_swappable_with, (X<T>&, X<T[1]>&))
# endif
#endif

#if BENCH_IS_NOTHROW_SWAPPABLE_WITH
# if ! BENCH_IS_NOTHROW_SWAPPABLE_WITH_DISABLE_REF
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_swappable_with, (T&, T&))
# endif
# if ! BENCH_IS_NOTHROW_SWAPPABLE_WITH_DISABLE_REF2
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_swappable_with, (X<T>&, X<T[1]>&))
# endif
#endif

#if BENCH_HAS_VIRTUAL_DESTRUCTOR
  BENCH(NREPEAT, BENCH_TYPE, SV, has_virtual_destructor, (T))
#endif

#if BENCH_IS_SAME
  BENCH(NREPEAT, BENCH_TYPE, SV, is_same, (T, T))
#endif

// #if BENCH_IS_LAYOUT_COMPATIBLE
//   BENCH(NREPEAT, BENCH_TYPE, SV, is_layout_compatible, (T, T))
// #endif

// #if BENCH_IS_POINTER_INTERCONVERTIBLE_BASE_OF
//   BENCH(NREPEAT, BENCH_TYPE, SV, is_pointer_interconvertible_base_of, (T, T))
// #endif

#if BENCH_ALIGNMENT_OF
  BENCH(NREPEAT, BENCH_TYPE, SV, alignment_of, (T))
#endif

#if BENCH_RANK
# if ! BENCH_RANK_DISABLE_T
  BENCH(NREPEAT, BENCH_TYPE, SV, rank, (T))
# endif
# if ! BENCH_RANK_DISABLE_ARRAY
  BENCH(NREPEAT, BENCH_TYPE, SV, rank, (T[1]))
# endif
#endif

#if BENCH_EXTENT
# if BENCH_STD
#   define EXTENT_NAME extent
# else
#   define EXTENT_NAME extent_c
# endif
# if ! BENCH_EXTENT_DISABLE_T
  BENCH(NREPEAT, BENCH_TYPE, SV, EXTENT_NAME, (T))
# endif
# if ! BENCH_EXTENT_DISABLE_ARRAY
  BENCH(NREPEAT, BENCH_TYPE, SV, EXTENT_NAME, (T[1]))
# endif
#endif

#if BENCH_REMOVE_CONST
  BENCH(NREPEAT, BENCH_TYPE, ST, remove_const, (T))
#endif

#if BENCH_REMOVE_VOLATILE
  BENCH(NREPEAT, BENCH_TYPE, ST, remove_volatile, (T))
#endif

#if BENCH_REMOVE_CV
  BENCH(NREPEAT, BENCH_TYPE, ST, remove_cv, (T))
#endif

#if BENCH_REMOVE_EXTENTS
  BENCH(NREPEAT, BENCH_TYPE, ST, remove_extent, (T))
#endif

#if BENCH_REMOVE_ALL_EXTENTS
  BENCH(NREPEAT, BENCH_TYPE, ST, remove_all_extents, (T))
#endif

#if BENCH_REMOVE_POINTER
  BENCH(NREPEAT, BENCH_TYPE, ST, remove_pointer, (T))
#endif

#if BENCH_REMOVE_REFERENCE
  BENCH(NREPEAT, BENCH_TYPE, ST, remove_reference, (T))
#endif

#if BENCH_REMOVE_CVREF && (! BENCH_STD || __cpp_lib_remove_cvref >= 201711L)
  BENCH(NREPEAT, BENCH_TYPE, ST, remove_cvref, (T))
#endif

#if BENCH_REFERENCE_CONSTRUCTS_FROM_TEMPORARY && (! BENCH_STD || __cpp_lib_reference_from_temporary >= 202202L)
  BENCH(NREPEAT, BENCH_TYPE, ST, reference_constructs_from_temporary, (T&, T&))
#endif

#if BENCH_REFERENCE_CONVERTS_FROM_TEMPORARY && (! BENCH_STD || __cpp_lib_reference_from_temporary >= 202202L)
  BENCH(NREPEAT, BENCH_TYPE, ST, reference_converts_from_temporary, (T&, T&))
#endif

#if BENCH_ADD_POINTER
  BENCH(NREPEAT, BENCH_TYPE, ST, add_pointer, (T))
#endif

#if BENCH_ADD_CV
  BENCH(NREPEAT, BENCH_TYPE, ST, add_cv, (T))
#endif

#if BENCH_ADD_CONST
  BENCH(NREPEAT, BENCH_TYPE, ST, add_const, (T))
#endif

#if BENCH_ADD_VOLATILE
  BENCH(NREPEAT, BENCH_TYPE, ST, add_volatile, (T))
#endif

#if BENCH_MAKE_SIGNED
  BENCH(NREPEAT, BENCH_TYPE, ST, make_signed, (typename X<T>::E))
#endif

#if BENCH_MAKE_UNSIGNED
  BENCH(NREPEAT, BENCH_TYPE, ST, make_unsigned, (typename X<T>::E))
#endif

#if BENCH_DECAY
# if ! BENCH_DECAY_DISABLE_T
  BENCH(NREPEAT, BENCH_TYPE, ST, decay, (T))
# endif
# if ! BENCH_DECAY_DISABLE_REF
  BENCH(NREPEAT, BENCH_TYPE, ST, decay, (T&))
# endif
#endif

#if BENCH_UNWRAP_REFERENCE && (! BENCH_STD || __cpp_lib_unwrap_ref >= 201811L) \
  /* unwrap_reference is missing from <type_traits> with libc++-15 */ \
  && (! _LIBCPP_VERSION || _LIBCPP_VERSION >= 16000)
  BENCH(NREPEAT, BENCH_TYPE, ST, unwrap_reference, (T))
#endif

#if BENCH_UNWRAP_REF_DECAY && (! BENCH_STD || __cpp_lib_unwrap_ref >= 201811L) \
  /* unwrap_ref_decay is missing from <type_traits> with libc++-15 */ \
  && (! _LIBCPP_VERSION || _LIBCPP_VERSION >= 16000)
  BENCH(NREPEAT, BENCH_TYPE, ST, unwrap_ref_decay, (T))
#endif

#if BENCH_INVOKE_RESULT
# if ! BENCH_INVOKE_RESULT_DISABLE_FN
  BENCH(NREPEAT, BENCH_TYPE, ST, invoke_result, (int(*)(T), T))
# endif
# if ! BENCH_INVOKE_RESULT_DISABLE_MEM_VAR
  BENCH(NREPEAT, BENCH_TYPE, ST, invoke_result, (int T::*, T))
# endif
# if ! BENCH_INVOKE_RESULT_DISABLE_MEM_FN
  BENCH(NREPEAT, BENCH_TYPE, ST, invoke_result, (int(T::*)(), T))
# endif
#endif

#if BENCH_IS_INVOCABLE
# if ! BENCH_IS_INVOCABLE_DISABLE_FN
  BENCH(NREPEAT, BENCH_TYPE, SV, is_invocable, (int(*)(T), T))
# endif
# if ! BENCH_IS_INVOCABLE_DISABLE_MEM_VAR
  BENCH(NREPEAT, BENCH_TYPE, SV, is_invocable, (int T::*, T))
# endif
# if ! BENCH_IS_INVOCABLE_DISABLE_MEM_FN
  BENCH(NREPEAT, BENCH_TYPE, SV, is_invocable, (int(T::*)(), T))
# endif
#endif

#if BENCH_IS_INVOCABLE_R
# if ! BENCH_IS_INVOCABLE_R_DISABLE_FN
  BENCH(NREPEAT, BENCH_TYPE, SV, is_invocable_r, (int, int(*)(T), T))
# endif
# if ! BENCH_IS_INVOCABLE_R_DISABLE_MEM_VAR
  BENCH(NREPEAT, BENCH_TYPE, SV, is_invocable_r, (int, int T::*, T))
# endif
# if ! BENCH_IS_INVOCABLE_R_DISABLE_MEM_FN
  BENCH(NREPEAT, BENCH_TYPE, SV, is_invocable_r, (int, int(T::*)(), T))
# endif
#endif

#if BENCH_IS_NOTHROW_INVOCABLE
# if ! BENCH_IS_NOTHROW_INVOCABLE_DISABLE_FN
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_invocable, (int(*)(T), T))
# endif
# if ! BENCH_IS_NOTHROW_INVOCABLE_DISABLE_MEM_VAR
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_invocable, (int T::*, T))
# endif
# if ! BENCH_IS_NOTHROW_INVOCABLE_DISABLE_MEM_FN
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_invocable, (int(T::*)(), T))
# endif
#endif

#if BENCH_IS_NOTHROW_INVOCABLE_R
# if ! BENCH_IS_NOTHROW_INVOCABLE_R_DISABLE_FN
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_invocable_r, (int, int(*)(T), T))
# endif
# if ! BENCH_IS_NOTHROW_INVOCABLE_R_DISABLE_MEM_VAR
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_invocable_r, (int, int T::*, T))
# endif
# if ! BENCH_IS_NOTHROW_INVOCABLE_R_DISABLE_MEM_FN
  BENCH(NREPEAT, BENCH_TYPE, SV, is_nothrow_invocable_r, (int, int(T::*)(), T))
# endif
#endif

#if BENCH_UNDERLYING_TYPE
  BENCH(NREPEAT, BENCH_TYPE, ST, underlying_type, (typename X<T>::E))
#endif

#if BENCH_COMMON_TYPE
  BENCH(NREPEAT, BENCH_TYPE, ST, common_type, (T, T&, T&&, T const&))
#endif

#if BENCH_COMMON_REFERENCE && (! BENCH_STD || __cpp_lib_common_reference >= 202302L)
  BENCH(NREPEAT, BENCH_TYPE, ST, common_reference, (T&, T const&, T&&))
#endif

JLN_MP_DIAGNOSTIC_POP()
