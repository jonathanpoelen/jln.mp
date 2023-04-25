#pragma once

#include <jln/mp/algorithm/drop_while.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct take_while_impl;

    template<class>
    struct take_while_extended_by_n_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Extract the first elements of a \sequence that satisfy a \predicate.
  /// When an element does not satisfy the predicate,
  /// call \c TC with it and those before it.
  /// Otherwise \c FC is called on the whole sequence.
  /// \treturn \sequence
  /// \see take_front, take_back, take_while_xs
  /// \see drop_while, drop_while_xs
  /// \see search, partial_search
  template<class Pred, class TC = listify, class FC = TC>
  struct take_while
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Extract the first plus at most \c ExtendedByN elements of a \sequence that satisfy a \predicate.
  /// When an element satisfy the predicate,
  /// call \c TC with it and those before it plus at most \c ExtendedByN.
  /// Otherwise \c FC is called on the whole sequence.
  /// \semantics
  ///   \code
  ///   call<take_while_extended_by_n_c<2, is_not<number<2>>>,
  ///     number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   //  predicate not satisfied ^ (+1)   ^ +2
  ///   ==
  ///   list<number<0>, number<1>, number<2>, number<3>>
  ///
  ///   call<take_while_extended_by_n_c<2, is_not<number<5>>>,
  ///     number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   //                                   predicate not satisfied ^ (+1)
  ///   ==
  ///   list<number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   \endcode
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct take_while_extended_by_n_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_while_extended_by_n = take_while_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_while = take_while_extended_by_n_c<1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_while = unpack<L, mp::take_while<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_inclusive_while = unpack<L, mp::take_while_extended_by_n_c<1, Pred, TC, FC>>;

    template<class ExtendedByN, class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_while_extended_by_n
      = unpack<L, mp::take_while_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>>;

    template<std::size_t ExtendedByN,
             class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_while_extended_by_n_c
      = unpack<L, mp::take_while_extended_by_n_c<ExtendedByN, Pred, TC, FC>>;
  }
}


#include <jln/mp/list/take_front.hpp>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct take_while_impl<_drop_while_continue>
    : drop_while_impl<_drop_while_continue>
  {};

  template<std::size_t n>
  struct take_while_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, std::size_t m>
    using f = take_front_c<m-n-1, TC>;
  };


  template<>
  struct take_while_extended_by_n_impl<_drop_while_continue>
    : drop_while_extended_by_n_impl<_drop_while_continue>
  {};

  template<std::size_t n>
  struct take_while_extended_by_n_impl<_drop_while_result<n>>
  {
    template<std::size_t ExtendedByN, class TC, class FC, std::size_t m>
    using f = take_front_c<m - (n >= ExtendedByN ? n - ExtendedByN + 1 : 0), TC>;
  };
}
/// \encond
