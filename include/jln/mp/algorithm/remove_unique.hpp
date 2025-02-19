// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/algorithm/same.hpp>

// #if ! JLN_MP_GCC
#include <jln/mp/algorithm/make_int_sequence.hpp>
// #endif


namespace jln::mp
{
  /// \cond
  namespace detail
  {
#if JLN_MP_GCC
    template<bool>
    struct _remove_unique;

    template<bool>
    struct _copy_unique;
#else
    template<class, int_t... i>
    struct _remove_unique;

    template<class, int_t... i>
    struct _copy_unique;
#endif

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
#if JLN_MP_GCC
    using f = typename detail::_remove_unique<sizeof...(xs) < 2>
#else
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), detail::_remove_unique)
#endif
      ::template f<C, xs...>;
  };

  /// Remove unique elements from a \sequence.
  /// \treturn \sequence
  /// \see remove_unique, copy_unique, copy_unique_if
  template<class Cmp = same<>, class C = listify>
  using remove_unique_if = typename detail::mk_remove_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using remove_unique = typename detail::_unpack<remove_unique<C>, L>::type;

    template<class L, class Cmp = mp::same<>, class C = mp::listify>
    using remove_unique_if = typename detail::_unpack<remove_unique_if<Cmp, C>, L>::type;
  }

  /// Copy unique elements from a \sequence.
  /// \treturn \sequence
  /// \see copy_unique_if, remove_unique, remove_unique_if
  template<class C = listify>
  struct copy_unique
  {
    template<class... xs>
#if JLN_MP_GCC
    using f = typename detail::_copy_unique<sizeof...(xs) < 2>
#else
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), detail::_copy_unique)
#endif
      ::template f<C, xs...>;
  };

  /// Copy unique elements from a \sequence.
  /// \treturn \sequence
  /// \see copy_unique, remove_unique, remove_unique_if
  template<class Cmp = same<>, class C = listify>
  using copy_unique_if = typename detail::mk_copy_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using copy_unique = typename detail::_unpack<copy_unique<C>, L>::type;

    template<class L, class Cmp = mp::same<>, class C = mp::listify>
    using copy_unique_if = typename detail::_unpack<copy_unique_if<Cmp, C>, L>::type;
  }
}


#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/algorithm/any_of.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/list/wrap_in_list.hpp>

// #if JLN_MP_GCC
#include <jln/mp/algorithm/is_unique.hpp> // indexed_inherit
// #else
#include <jln/mp/utility/inherit.hpp>
// #endif

/// \cond
namespace jln::mp::detail
{
#if JLN_MP_GCC
#if !JLN_MP_FEATURE_CONCEPTS
  template<class From, class To, class = decltype(To(From()))>
  constexpr bool is_convertible_to(From, To)
  {
    return true;
  }

  constexpr bool is_convertible_to(...)
  {
    return false;
  }
#endif

  template<class Inherit, class x>
  using remove_unique_elem_impl =
    typename wrap_in_list_c<
#if JLN_MP_FEATURE_CONCEPTS
      !requires{ static_cast<list<x>*>(static_cast<Inherit*>(nullptr)); }
#else
      !is_convertible_to(
        static_cast<Inherit*>(nullptr),
        static_cast<list<x>*>(nullptr)
      )
#endif
    >
    ::template f<x>;

  template<class C, class Inherit, class... xs>
  using remove_unique_impl = typename join<C>
    ::template f<remove_unique_elem_impl<Inherit, xs>...>;

  template<>
  struct _remove_unique<false>
  {
    template<class C, class... xs>
    using f = remove_unique_impl<
      C,
      typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), indexed_inherit)::template f<xs...>,
      xs...
    >;
  };

  template<>
  struct _remove_unique<true>
    : call_trace_c0_arg
  {};


  template<class Inherit, class x>
  using copy_unique_elem_impl =
    typename wrap_in_list_c<
#if JLN_MP_FEATURE_CONCEPTS
      requires{ static_cast<list<x>*>(static_cast<Inherit*>(nullptr)); }
#else
      is_convertible_to(
        static_cast<Inherit*>(nullptr),
        static_cast<list<x>*>(nullptr)
      )
#endif
    >
    ::template f<x>;

  template<class C, class Inherit, class... xs>
  using copy_unique_impl = typename join<C>
    ::template f<copy_unique_elem_impl<Inherit, xs>...>;

  template<>
  struct _copy_unique<false>
  {
    template<class C, class... xs>
    using f = copy_unique_impl<
      C,
      typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), indexed_inherit)::template f<xs...>,
      xs...
    >;
  };

  template<>
  struct _copy_unique<true>
  {
    template<class C, class... xs>
    using f = JLN_MP_CALL_TRACE(C, xs...);
  };
#else
  template<class C, class Inherit, Inherit* ptr, class... S>
  using remove_copy_unique_filter = typename join<C>
    ::template f<decltype(S::f(ptr))...>;


  template<class x>
  struct remove_unique_elem_impl
  {
    template<class i>
    static list<> f(list<x, i>*);

    static list<x> f(...);
  };

  template<class, int_t... i>
  struct _remove_unique
  {
    template<class C, class... xs>
    using f = remove_copy_unique_filter<
      C, inherit<list<xs, number<i>>...>, nullptr, remove_unique_elem_impl<xs>...
    >;
  };


  template<class x>
  struct copy_unique_elem_impl
  {
    template<class i>
    static list<x> f(list<x, i>*);

    static list<> f(...);
  };

  template<class, int_t... i>
  struct _copy_unique
  {
    template<class C, class... xs>
    using f = remove_copy_unique_filter<
      C, inherit<list<xs, number<i>>...>, nullptr, copy_unique_elem_impl<xs>...
    >;
  };
#endif


  template<class, int_t... ints>
  struct remove_unique_if_impl
  {
    template<class C, class Cmp, class... xs>
    using f = typename join<C>::template f<
      JLN_MP_MSVC_FIX_CALL((
        rotate_impl<ints>::template f<
          ints,
          pop_front<any_of<
            push_back<xs, Cmp>,
            cfe<wrap_in_list>
          >>::template f,
          xs...
        >
      ), xs)...
    >;
  };

  template<>
  struct remove_unique_if_impl<int_t>
    : call_trace_c0_arg
  {};

  template<int_t i>
  struct remove_unique_if_impl<int_t, i>
  : remove_unique_if_impl<int_t>
  {};

  template<class Cmp, class C>
  struct _remove_unique_if
  {
    template<class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), remove_unique_if_impl)
      ::template f<C, Cmp, xs...>;
  };

  template<class Cmp, class C>
  struct mk_remove_unique
  {
    using type = _remove_unique_if<Cmp, C>;
  };


  template<class, int_t... ints>
  struct copy_unique_if_impl
  {
    template<class C, class Cmp, class... xs>
    using f = typename join<C>::template f<
      JLN_MP_MSVC_FIX_CALL((
        rotate_impl<ints>::template f<
          ints,
          pop_front<none_of<
            push_back<xs, Cmp>,
            cfe<wrap_in_list>
          >>::template f,
          xs...
        >
      ), xs)...
    >;
  };

  template<>
  struct copy_unique_if_impl<int_t>
  : remove_unique_if_impl<int_t>
  {};

  template<int_t i>
  struct copy_unique_if_impl<int_t, i>
  {
    template<class C, class Cmp, class... xs>
    using f = JLN_MP_CALL_TRACE(C, xs...);
  };

  template<class Cmp, class C>
  struct _copy_unique_if
  {
    template<class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), copy_unique_if_impl)
      ::template f<C, Cmp, xs...>;
  };

  template<class Cmp, class C>
  struct mk_copy_unique
  {
    using type = _copy_unique_if<Cmp, C>;
  };


  template<class C>
  struct mk_remove_unique<same<>, C>
  {
    using type = mp::remove_unique<C>;
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
  struct mk_copy_unique<same<>, C>
  {
    using type = mp::copy_unique<C>;
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
