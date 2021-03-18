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
    struct _iterate;
  }
  /// \endcond

  /// \ingroup utility

  /// Apply a function \c n times to its argument.
  /// \treturn \value
  template <class n, class F, class C = identity>
  struct iterate
  {
    template<class x>
    using f = typename detail::_iterate<detail::n_8_or_more_16_32_64_128_256(n::value)>
      ::template f<n::value, C, F, x>;
  };

  /// Apply a function \c n times to its argument.
  /// \treturn \value
  template <uint_ n, class F, class C = identity>
  using iterate_c = iterate<number<n>, F, C>;

  namespace emp
  {
    template<class L, class n, class F, class C = mp::identity>
    using iterate = unpack<L, mp::iterate<n, F, C>>;

    template<class L, uint_ n, class F, class C = mp::identity>
    using iterate_c = unpack<L, mp::iterate<number<n>, F, C>>;
  }
} // namespace jln::mp


/// \cond
namespace jln::mp::detail
{
  template<>
  struct _iterate<0>
  {
    template<uint_ i, class C, class F, class x>
    using f = typename C::template f<x>;
  };

#define JLN_MP_ITERATE(n, mp_xs, mp_rsx, mp_rep)  \
  template<>                                      \
  struct _iterate<n>                              \
  {                                               \
    template<uint_ i, class C, class F, class x>  \
    using f = typename C::template f<             \
      mp_rep(typename F::template f<, JLN_MP_NIL) \
      x                                           \
      mp_rep(>, JLN_MP_NIL)                       \
    >;                                            \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_ITERATE)

#undef JLN_MP_ITERATE

#define JLN_MP_ITERATE(n, mp_xs, mp_rsx, mp_rep)                   \
  template<>                                                       \
  struct _iterate<n>                                               \
  {                                                                \
    template<uint_ i, class C, class F, class x>                   \
    using f = typename _iterate<n_8_or_more_16_32_64_128_256(i-n)> \
      ::template f<i-n, C, F,                                      \
        mp_rep(typename F::template f<, JLN_MP_NIL)                \
        x                                                          \
        mp_rep(>, JLN_MP_NIL)                                      \
      >;                                                           \
  };

  JLN_MP_GEN_XS_16_32_64_128_256(JLN_MP_ITERATE)

#undef JLN_MP_ITERATE
}
/// \endcond
