#pragma once

#include "../functional/identity.hpp"
#include "../functional/call.hpp"
#include "../number/number.hpp"

#include <type_traits>

namespace jln::mp::traits
{

#define JLN_MP_MAKE_TRAIT(Name)                                 \
  template<class C = identity>                                  \
  struct Name                                                   \
  {                                                             \
    template<class... xs>                                       \
    using f = typename detail::dcall<(sizeof...(xs) < 1000000)> \
      ::template f<C, typename std::Name<xs...>::type>;         \
  };                                                            \
                                                                \
  namespace emp                                                 \
  {                                                             \
    template<class... xs>                                       \
    using Name = typename std::Name<xs...>::type;               \
  }                                                             \
                                                                \
  template<>                                                    \
  struct Name<identity>                                         \
  {                                                             \
    template<class... xs>                                       \
    using f = typename std::Name<xs...>::type;                  \
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
#if __cplusplus < 202002L
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
#if __cplusplus >= 202002L
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
    using f = call<C, typename std::extent<x, i::value...>::type>;
  };

  namespace emp
  {
    template<class x, class i = number<0>>
    using extent = typename std::extent<x, i::value>::type;
  }

  template<>
  struct extent<identity>
  {
    template<class x, class i = number<0>>
    using f = typename std::extent<x, i::value>::type;
  };

  // type relations:
  JLN_MP_MAKE_TRAIT(is_same);
  JLN_MP_MAKE_TRAIT(is_base_of);
  JLN_MP_MAKE_TRAIT(is_convertible);
#if __cplusplus >= 202002L
  JLN_MP_MAKE_TRAIT(is_nothrow_convertible);
  JLN_MP_MAKE_TRAIT(is_layout_compatible);
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
#if __cplusplus >= 202002L
  JLN_MP_MAKE_TRAIT(remove_cvref);
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
    using f = call<C, typename std::aligned_storage<Len::value, Alignment::value...>::type>;
  };

  namespace emp
  {
    template<class Len, class... Alignment>
    using aligned_storage = typename std::aligned_storage<
      Len::value, Alignment::value...>::type;
  }

  template<>
  struct aligned_storage<identity>
  {
    template<class Len, class... Alignment>
    using f = typename std::aligned_storage<Len::value, Alignment::value...>::type;
  };

  template<class C = identity>
  struct aligned_union
  {
    template<class len, class... xs>
    using f = call<C, typename std::aligned_union<len::value, xs...>::type>;
  };

  namespace emp
  {
    template<class len, class... xs>
    using aligned_union = typename std::aligned_union<len::value, xs...>::type;
  }

  template<>
  struct aligned_union<identity>
  {
    template<class len, class... xs>
    using f = typename std::aligned_union<len::value, xs...>::type;
  };
}
