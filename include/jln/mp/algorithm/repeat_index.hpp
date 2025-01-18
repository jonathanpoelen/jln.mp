// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, int_t... ints>
    struct repeat_index_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Creates a sequence of index sequence,
  /// taking the size of each as a parameter.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   repeat_index_with_v_c<>::f<3, 0, 2, 1>
  ///   ==
  ///   list<
  ///     list<number<0>, number<0>, number<0>>,
  ///     list<>,
  ///     list<number<2>, number<2>>,
  ///     list<number<3>>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class F = listify, class C = listify>
  struct repeat_index_with_v_c
  {
    template<unsigned... ns>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(
      sizeof...(ns), detail::repeat_index_impl
    )
    ::template f<C, F, ns...>;
  };

  template<class F = listify, class C = listify>
  struct repeat_index_with
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... ns>
    using f = typename repeat_index_with_v_c<F, C>::template f<ns::value...>;
#elif !JLN_MP_MSVC
    template<class... ns>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(
      sizeof...(ns), detail::repeat_index_impl
    )
    ::template f<C, F, ns::value...>;
#else
    template<class... ns>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(
      sizeof...(ns), detail::repeat_index_impl
    )
    ::template f<C, F, unsigned{ns::value}...>;
#endif
  };

  template<class C = listify>
  using repeat_index_v_c = repeat_index_with_v_c<listify, C>;

  template<class C = listify>
  using repeat_index = repeat_index_with<listify, C>;

  namespace emp
  {
    template<class L, class F = listify, class C = listify>
    using repeat_index_with
      = typename detail::_unpack<mp::repeat_index_with<F, C>, L>::type;

    template<class L, class C = listify>
    using repeat_index
      = typename detail::_unpack<mp::repeat_index_with<listify, C>, L>::type;
  }
}


#include <jln/mp/algorithm/repeat.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class, int_t... ints>
  struct repeat_index_impl
  {
    template<class C, class F, unsigned... ns>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_REPEAT_VALUE_T(F, ns, number<ints>)...);
  };
}
/// \endcond
