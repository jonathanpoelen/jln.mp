// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/number/number.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct _batched;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a sequence by arbitrary size group.
  /// \post If `n <= 0`, then the result sequence is empty
  /// \semantics
  ///   \code
  ///   batched<number<2>>::f<
  ///     void, void, int, void, void
  ///   > = list<
  ///     list<void, void>,
  ///     list<int, void>,
  ///     list<void>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<int_ n, class C = listify>
  struct batched_c
  {
    template<class... xs>
    using f = typename detail::_batched<sizeof...(xs) != 0 && 0 < n>
      ::template f<C, n, xs...>;
  };

  template<class n, class C = listify>
  using batched = batched_c<n::value, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using batched = unpack<L, mp::batched<n, C>>;

    template<class L, int_ n, class C = mp::listify>
    using batched_c = unpack<L, mp::batched_c<n, C>>;
  }
}


#include <jln/mp/algorithm/split.hpp>
#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/algorithm/make_int_sequence.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class, int_... i>
  struct _batched_impl
  {
    template<class C, int_ n, class... xs>
    using f = typename fold_right<JLN_MP_LIFT_WRAP(split_state), unpack<pop_front<C>>>
      ::template f<
        list<list<>>,
        list<number<(i % n ? split_keep : split_before)>, xs>...
      >;
  };

  template<>
  struct _batched<true>
  {
    template<class C, int_ n, class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), _batched_impl)
      ::template f<C, n, xs...>;
  };

  template<>
  struct _batched<false>
  {
    template<class C, int_, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };
}
/// \endcond