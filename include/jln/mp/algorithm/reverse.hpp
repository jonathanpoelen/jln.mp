#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/detail/enumerate.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned>
    struct _reverse;

    constexpr unsigned _rotate_select(unsigned n)
    {
      return (detail::n_8_or_less_16_64_256(n) == n) * 20
        + detail::n_8_or_less_16_64_256(n);
    }
  }
  /// \endcond

  /// \ingroup algorithm

  /// Reverses the order of the elements of a \sequence.
  /// \treturn \sequence
  template<class C = listify>
  struct reverse
  {
    template<class... xs>
    using f = typename detail::_reverse<
      detail::_rotate_select(sizeof...(xs))
    >::template f<C, sizeof...(xs), xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using reverse = unpack<L, mp::reverse<C>>;
  }
}


#include <jln/mp/list/join.hpp>
#include <jln/mp/utility/conditional.hpp>

/// \cond
namespace jln::mp::detail
{
#define JLN_MP_REVERSE_IMPL(n, mp_xs, mp_rxs, mp_rep)    \
  template<>                                             \
  struct _reverse<n>                                     \
  {                                                      \
    template<class C, std::size_t count                  \
      mp_xs(JLN_MP_COMMA class, JLN_MP_NIL, JLN_MP_NIL), \
      class... xs>                                       \
    using f = typename reverse<join<C>>                  \
      ::template f<xs..., list<                          \
        mp_rxs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>>;  \
  };                                                     \
  template<>                                             \
  struct _reverse<n+20>                                  \
  {                                                      \
    template<class C, std::size_t count                  \
      mp_xs(JLN_MP_COMMA class, JLN_MP_NIL, JLN_MP_NIL), \
      class... xs>                                       \
    using f = JLN_MP_CALL_TRACE((C),                     \
      mp_rxs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA));     \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_MP_REVERSE_IMPL)

#undef JLN_MP_REVERSE_IMPL

#define JLN_MP_REVERSE_IMPL(n, mp_xs, mp_rxs, mp_rep) \
  template<>                                          \
  struct _reverse<n>                                  \
  {                                                   \
    template<class C, std::size_t count,              \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),         \
      class... xs>                                    \
    using f = typename _reverse<                      \
      detail::n_8_or_less_16_64_256(count-n)          \
    >::template f<C, count-n, xs..., list<            \
      mp_rxs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>>; \
  };                                                  \
  template<>                                          \
  struct _reverse<n+20>                               \
  {                                                   \
    template<class C, std::size_t count,              \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),         \
      class... xs>                                    \
    using f = typename C::template f<                 \
      mp_rxs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>;  \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_REVERSE_IMPL)

#undef JLN_MP_REVERSE_IMPL
}
/// \endcond
