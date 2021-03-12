#pragma once

#include <jln/mp/algorithm/search.hpp>
#include <jln/mp/algorithm/starts_with.hpp>
#include <jln/mp/list/take_front.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct before_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Find the \sequence before a sub-\sequence.
  /// Calls \c TC with the elements from the beginning to sub-\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \return \sequence
#ifdef JLN_MP_DOXYGENATING
  template<class Seq, class TC = listify, class FC = clear<TC>>
  struct before;

  template<class... Ts, class TC, class FC>
  struct before<list<Ts...>, TC, FC>
  : search<starts_with<list<Ts...>>, drop_back_c<sizeof...(Ts), TC>, FC>
  {};
#else
  template<class Seq, class TC = listify, class FC = TC>
  struct before
  {
    template<class... xs>
    using f = typename detail::before_impl<
      typename detail::_search<
        detail::n_8_or_more_16_32_64_128_256(sizeof...(xs)), false
      >::template f<sizeof...(xs), starts_with<Seq>, xs...>
    >::template f<TC, FC, xs...>;
  };
#endif

  namespace emp
  {
    template<class L, class Seq, class TC = mp::listify, class FC = TC>
    using before = unpack<L, mp::before<Seq, TC, FC>>;
  }

  /// \cond
  template<class TC, class FC>
  struct before<list<>, TC, FC>
  {
    template<class... xs>
    using f = JLN_MP_DCALL(0 <= sizeof...(xs), TC, xs...);
  };
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  template<>
  struct before_impl<_drop_while_continue>
  {
    template<class TC, class FC, class... xs>
    using f = typename FC::template f<xs...>;
  };

  template<std::size_t n>
  struct before_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, class... xs>
    using f = typename take_front<number<sizeof...(xs)-n-1>, TC>::template f<xs...>;
  };
}
/// \endcond
