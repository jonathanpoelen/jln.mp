#pragma once

#include <jln/mp/detail/enumerate.hpp>
#include <jln/mp/list/listify.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/unpack.hpp>

#include <cstddef>
#if defined(_MSC_VER) || defined(__clang__)
# include <type_traits>
#endif

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned>
    struct _drop_front;

#if defined(_MSC_VER) || defined(__clang__)
    template<int_ i, std::size_t n, class = void>
    struct validate_index
    {};

    template<int_ i, std::size_t n>
    struct validate_index<i, n, std::enable_if_t<(int_(n) - i >= 0)>>
    {
      static constexpr int_ value = i;
    };
#else
    template<int_ i, std::size_t n>
    using validate_index = number<(0 * std::size_t{int_(n) - i}) + i>;
#endif
  }
  /// \endcond

  /// \ingroup list

  /// Removes \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  template<class N, class C = listify>
  struct drop_front
  {
    template<class... xs>
    using f = typename detail::_drop_front<
      detail::n_8_or_less_16_64_256(
        detail::validate_index<N::value, sizeof...(xs)>::value
      )
    >::template f<N::value, C, xs...>;
  };

  /// Removes at most \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  template<class N, class C = listify>
  struct drop_front_max
  {
    template<class... xs>
    using f = typename detail::_drop_front<
      detail::n_8_or_less_16_64_256(
        detail::min(std::size_t{N::value}, sizeof...(xs))
      )
    >::template f<detail::min(std::size_t{N::value}, sizeof...(xs)), C, xs...>;
  };

  template<int_ n, class C = listify>
  using drop_front_c = drop_front<number<n>, C>;

  template<int_ n, class C = listify>
  using drop_front_max_c = drop_front_max<number<n>, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using drop_front = unpack<L, mp::drop_front<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using drop_front_c = unpack<L, mp::drop_front<number<n>, C>>;

    template<class L, class N, class C = mp::listify>
    using drop_front_max = unpack<L, mp::drop_front_max<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using drop_front_max_c = unpack<L, mp::drop_front_max<number<n>, C>>;
  }

  /// \cond
  template<class C>
  struct drop_front<number<0>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C, xs...);
  };

  template<class C>
  struct drop_front<number<1>, C>
  {
    template<class, class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C, xs...);
  };

  template<class C>
  struct drop_front<number<2>, C>
  {
    template<class, class, class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C, xs...);
  };

  template<class C>
  struct drop_front<number<3>, C>
  {
    template<class, class, class, class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C, xs...);
  };

  template<class C>
  struct drop_front<number<4>, C>
  {
    template<class, class, class, class, class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C, xs...);
  };

  template<class C>
  struct drop_front<number<5>, C>
  {
    template<class, class, class, class, class, class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C, xs...);
  };

  template<class C>
  struct drop_front_max<number<0>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C, xs...);
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
#define JLN_MP_DROP_IMPL(n, _, mp_rxs, mp_rep) \
  template<>                                   \
  struct _drop_front<n>                        \
  {                                            \
    template<unsigned size, class C,           \
      mp_rep(class JLN_MP_COMMA, JLN_MP_NIL)   \
      class... xs>                             \
    using f = typename C::template f<xs...>;   \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_MP_DROP_IMPL)

#undef JLN_MP_DROP_IMPL

#define JLN_MP_DROP_IMPL(n, mp_xs, mp_rxs, mp_rep) \
  JLN_MP_DROP_IMPL2(n, mp_xs, mp_rxs, mp_rep,      \
    n_8_or_less_16_64_256)

#define JLN_MP_DROP_IMPL2(n, _, mp_rxs, mp_rep, next_int) \
  template<>                                              \
  struct _drop_front<n>                                   \
  {                                                       \
    template<unsigned size, class C,                      \
      mp_rep(class JLN_MP_COMMA, JLN_MP_NIL)              \
      class... xs>                                        \
    using f = typename _drop_front<next_int (size-n)>     \
      ::template f<(size-n), C, xs...>;                   \
  };

  JLN_MP_GEN_XS_8_args(JLN_MP_DROP_IMPL2, JLN_MP_NIL)
  JLN_MP_GEN_XS_16_64_256(JLN_MP_DROP_IMPL)

#undef JLN_MP_DROP_IMPL2
#undef JLN_MP_DROP_IMPL
}
/// \endcond
