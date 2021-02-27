#pragma once

#include <jln/mp/algorithm/fold_right.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/utility/is.hpp>
#include <jln/mp/utility/unpack.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template <bool>
    struct _split;

    inline constexpr int_ split_keep = 0;
    inline constexpr int_ split_after = 1;
    inline constexpr int_ split_before = 2;
    inline constexpr int_ split_skip = 3;
    // inline constexpr int_ split_na = 4;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a \sequence into multiple \lists at every point that satisfy a predicate.
  /// \semantics
  ///   \code
  ///   call<split_if<is<void>, _0, _1, _2, _0, _3> == list<
  ///     list<>,
  ///     list<_1, _2>,
  ///     list<_3>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see split_before_if, split_after_if
  template<class Pred = identity, class C = listify>
  struct split_if
  {
    template <class... xs>
    using f = typename detail::_split<sizeof...(xs) != 0>
      ::template f<detail::split_skip, C, Pred, xs...>;
  };

  template<class x, class C = listify>
  using split = split_if<is<x>, C>;

  namespace emp
  {
    template<class L, class Pred = mp::identity, class C = mp::listify>
    using split_if = unpack<L, mp::split_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using split = unpack<L, mp::split<x, C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template <class x, class state>
  struct split_state;

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_keep>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<x, xs...>, Ls...>;
  };

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_after>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<x>, list<xs...>, Ls...>;
  };

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_before>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<>, list<x, xs...>, Ls...>;
  };

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_skip>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<>, list<xs...>, Ls...>;
  };

  template<>
  struct _split<true>
  {
    template<int_ policy, class C, class Pred, class... xs>
    using f = call<
      fold_right<lift_t<split_state>, optimize_useless_unpack_t<unpack<C>>>,
      list<list<>>,
      list<number<bool{Pred::template f<xs>::value}
        ? policy : split_keep>, xs>...
    >;
  };

  template<>
  struct _split<false>
  {
    template<int_, class C, class>
    using f = typename C::template f<>;
  };
}
/// \endcond
