// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/detail/enumerate.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct iterate_impl;
  }
  /// \endcond

  /// \ingroup utility

  /// Apply a function \c n times to its argument.
  /// \treturn \value
  template<uint_ n, class F, class C = identity>
  struct iterate_c
  {
    template<class x>
    using f = typename detail::iterate_impl<n>
      ::template f<n, C, JLN_MP_TRACE_F(F), x>;
  };

  /// Apply a function \c n times to its argument.
  /// \treturn \value
  template<class n, class F, class C = identity>
  using iterate = iterate_c<n::value, F, C>;

  namespace emp
  {
    template<class L, class n, class F, class C = mp::identity>
    using iterate = unpack<L, mp::iterate<n, F, C>>;

    template<class L, uint_ n, class F, class C = mp::identity>
    using iterate_c = unpack<L, mp::iterate_c<n, F, C>>;
  }
} // namespace jln::mp


/// \cond
namespace jln::mp::detail
{
  template<uint_ n>
  struct iterate_impl : iterate_impl<
      n <= 16 ? 8
    : n <= 32 ? 16
    : n <= 64 ? 32
    : n <= 128 ? 64
    : 128
  >
  {
  };

  template<>
  struct iterate_impl<0>
  {
    template<uint_ i, class C, class F, class x>
    using f = JLN_MP_CALL_TRACE(C, x);
  };

#define JLN_MP_ITERATE(n, mp_xs, mp_rsx, mp_rep)  \
  template<>                                      \
  struct iterate_impl<n>                          \
  {                                               \
    template<uint_ i, class C, class F, class x>  \
    using f = JLN_MP_CALL_TRACE(C,                \
      mp_rep(typename F::template f<, JLN_MP_NIL) \
      x                                           \
      mp_rep(>, JLN_MP_NIL)                       \
    );                                            \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_ITERATE)

#undef JLN_MP_ITERATE

#define JLN_MP_ITERATE(n, mp_xs, mp_rsx, mp_rep)    \
  template<>                                        \
  struct iterate_impl<n>                            \
  {                                                 \
    template<uint_ i, class C, class F, class x>    \
    using f = typename iterate_impl<i-n>            \
      ::template f<i-n, C, F,                       \
        mp_rep(typename F::template f<, JLN_MP_NIL) \
        x                                           \
        mp_rep(>, JLN_MP_NIL)                       \
      >;                                            \
  };

  JLN_MP_GEN_XS_8_16_32_64_128(JLN_MP_ITERATE)

#undef JLN_MP_ITERATE
}
/// \endcond
