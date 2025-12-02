// SPDX-FileCopyrightText: 2025 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/unique.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct unique_by_kv_impl_select;


    struct unique_by_kv_next_impl
    {
      template<class Set, class kv>
      using f =
        typename unique_by_kv_impl_select<JLN_MP_IS_BASE_OF(typename kv::key, Set)>
        ::template f<Set, kv>;
    };

    using unique_by_kv_impl = fold<JLN_MP_SIMPLE_MEMOIZER(unique_by_kv_next_impl)>;

    template<template<class...> class C, class S>
    struct flat_recursive_unique_by_kv;
  }
  /// \endcond

  /// \ingroup filter

  /// Value for \c unique_by_kv.
  template<class k, class v>
  struct unique_by_kv_entry : list<k>
  {
    using key = list<k>;
  };

  /// Returns a list of values associated with unique keys,
  /// preserving the order of appearance.
  /// \pre \c xs must be a \c unique_by_kv_entry
  /// \semantics
  ///   \code
  ///   unique_by_kv<>::f<
  ///     unique_by_kv_entry<K0, A>,
  ///     unique_by_kv_entry<K1, B>,
  ///     unique_by_kv_entry<K0, C>,
  ///     unique_by_kv_entry<K2, D>,
  ///     unique_by_kv_entry<K1, E>,
  ///     unique_by_kv_entry<K3, F>
  ///   > == list<A, B, D, F>
  ///   \endcode
  /// \treturn \sequence
  /// \see unique, unique_if, unique_by
  template<class C = listify>
  struct unique_by_kv
  {
    template<class... kv>
    using f = typename detail::flat_recursive_unique_by_kv<
      C::template f,
      typename detail::unique_by_kv_impl::f<inherit<>, kv...>
    >::type;
  };

  /// Returns a list with duplicate elements removed,
  /// using the function \c KeyF to determine uniqueness,
  /// preserving the order of appearance.
  /// \c unique_by<identity> is equivalent to \c unique<>.
  /// \semantics
  ///   \code
  ///   unique_by<unpack<add<>>>::f<
  ///     emp::numbers<0, 0>,
  ///     emp::numbers<1, 0>,
  ///     emp::numbers<2, -1>,
  ///     emp::numbers<3, 2>,
  ///     emp::numbers<1, 4>,
  ///     emp::numbers<2, 1>,
  ///     emp::numbers<3, 0>
  ///   > == list<
  ///     emp::numbers<0, 0>,
  ///     emp::numbers<1, 0>,
  ///     emp::numbers<3, 2>,
  ///     emp::numbers<2, 1>,
  ///   >
  ///   \endcode
  /// \treturn \sequence
  /// \see unique, unique_if, unique_by_kv
  template<class KeyF, class C = listify>
  struct unique_by
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(
      unique_by_kv<C>,
      unique_by_kv_entry<JLN_MP_CALL_TRACE(KeyF, xs), xs>...
    );
#else
    template<class... xs>
    using f = typename detail::flat_recursive_unique_by_kv<
      C::template f,
      typename detail::unique_by_kv_impl
        ::f<inherit<>, unique_by_kv_entry<JLN_MP_CALL_TRACE(KeyF, xs), xs>...>
    >::type;
#endif
  };

  namespace emp
  {
    template<class L, class KeyF, class C = mp::listify>
    using unique_by = typename detail::_unpack<unique_by<KeyF, C>, L>::type;

    template<class L, class C = mp::listify>
    using unique_by_kv = typename detail::_unpack<unique_by_kv<C>, L>::type;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct unique_by_kv_impl_select
  {
    template<class Set, class kv>
    using f = inherit<Set, kv>;
  };

  template<>
  struct unique_by_kv_impl_select<true>
    : unique_impl_select<true>
  {};

  template<template<class...> class C, class S>
  struct flat_recursive_unique_by_kv
  {
    using type = C<>;
  };

  template<template<class...> class C, class s, class k, class v>
  struct flat_recursive_unique_by_kv<C, inherit<s, unique_by_kv_entry<k, v>>>
  : _join_select<2>::f<
      C,
      typename flat_recursive_unique_by_kv<list, s>::type,
      list<v>
    >
  {};

  template<
    template<class...> class C, class s,
    class k0, class v0, class k1, class v1, class k2, class v2, class k3, class v3,
    class k4, class v4, class k5, class v5, class k6, class v6, class k7, class v7
  >
  struct flat_recursive_unique_by_kv<
    C,
    JLN_MP_REPEAT_8(inherit<, JLN_MP_NIL)
    s
    , unique_by_kv_entry<k0, v0>>, unique_by_kv_entry<k1, v1>>
    , unique_by_kv_entry<k2, v2>>, unique_by_kv_entry<k3, v3>>
    , unique_by_kv_entry<k4, v4>>, unique_by_kv_entry<k5, v5>>
    , unique_by_kv_entry<k6, v6>>, unique_by_kv_entry<k7, v7>>
  >
  : _join_select<2>::f<
      C,
      typename flat_recursive_unique_by_kv<list, s>::type,
      list<v0, v1, v2, v3, v4, v5, v6, v7>
    >
  {};

    template<
    template<class...> class C, class s,
    class k0, class v0, class k1, class v1, class k2, class v2, class k3, class v3,
    class k4, class v4, class k5, class v5, class k6, class v6, class k7, class v7,
    class k8, class v8, class k9, class v9, class k10, class v10, class k11, class v11,
    class k12, class v12, class k13, class v13, class k14, class v14, class k15, class v15,
    class k16, class v16, class k17, class v17, class k18, class v18, class k19, class v19,
    class k20, class v20, class k21, class v21, class k22, class v22, class k23, class v23,
    class k24, class v24, class k25, class v25, class k26, class v26, class k27, class v27,
    class k28, class v28, class k29, class v29, class k30, class v30, class k31, class v31
  >
  struct flat_recursive_unique_by_kv<
    C,
    JLN_MP_REPEAT_32(inherit<, JLN_MP_NIL)
    s
    , unique_by_kv_entry<k0, v0>>, unique_by_kv_entry<k1, v1>>
    , unique_by_kv_entry<k2, v2>>, unique_by_kv_entry<k3, v3>>
    , unique_by_kv_entry<k4, v4>>, unique_by_kv_entry<k5, v5>>
    , unique_by_kv_entry<k6, v6>>, unique_by_kv_entry<k7, v7>>
    , unique_by_kv_entry<k8, v8>>, unique_by_kv_entry<k9, v9>>
    , unique_by_kv_entry<k10, v10>>, unique_by_kv_entry<k11, v11>>
    , unique_by_kv_entry<k12, v12>>, unique_by_kv_entry<k13, v13>>
    , unique_by_kv_entry<k14, v14>>, unique_by_kv_entry<k15, v15>>
    , unique_by_kv_entry<k16, v16>>, unique_by_kv_entry<k17, v17>>
    , unique_by_kv_entry<k18, v18>>, unique_by_kv_entry<k19, v19>>
    , unique_by_kv_entry<k20, v20>>, unique_by_kv_entry<k21, v21>>
    , unique_by_kv_entry<k22, v22>>, unique_by_kv_entry<k23, v23>>
    , unique_by_kv_entry<k24, v24>>, unique_by_kv_entry<k25, v25>>
    , unique_by_kv_entry<k26, v26>>, unique_by_kv_entry<k27, v27>>
    , unique_by_kv_entry<k28, v28>>, unique_by_kv_entry<k29, v29>>
    , unique_by_kv_entry<k30, v30>>, unique_by_kv_entry<k31, v31>>
  >
  : _join_select<2>::f<
      C,
      typename flat_recursive_unique_by_kv<list, s>::type,
      list<
        v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11,
        v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,
        v22, v23, v24, v25, v26, v27, v28, v29, v30, v31
      >
    >
  {};
}

namespace jln::mp
{
  template<class C>
  struct unique_by<identity, C> : unique<C>
  {};

#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_DEBUG
  template<template<class...> class C>
  struct unique_by<identity, cfe<C>> : unique<cfe<C>>
  {};

  template<template<class...> class C>
  struct unique_by_kv<cfe<C>>
  {
    template<class... kv>
    using f = typename detail::flat_recursive_unique_by_kv<
      C,
      typename detail::unique_by_kv_impl::f<inherit<>, kv...>
    >::type;
  };

  template<class KeyF, template<class...> class C>
  struct unique_by<KeyF, cfe<C>>
  {
    template<class... xs>
    using f = typename detail::flat_recursive_unique_by_kv<
      C,
      typename detail::unique_by_kv_impl
        ::f<inherit<>, unique_by_kv_entry<JLN_MP_CALL_TRACE(KeyF, xs), xs>...>
    >::type;
  };
#endif
}
/// \endcond
