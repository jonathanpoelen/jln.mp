#pragma once

#include <jln/mp/list/drop_while.hpp>
#include <jln/mp/list/clear.hpp>
#include <jln/mp/utility/is.hpp>
#include <jln/mp/functional/not_fn.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct find_if_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Finds the first element that satisfy a \predicate.
  /// Calls \c TC with all the elements since the one found at the end.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct find_if
  {
    template<class... xs>
    using f = typename detail::find_if_impl<
      typename detail::_drop_while<
        detail::n_8_or_more_16_32_64_128_256(sizeof...(xs)), true
      >::template f<0, detail::to_not_fn_t<Pred>, xs...>
    >::template f<TC, FC, xs...>;
  };

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_if_not = find_if<not_fn<Pred>, TC, FC>;

  template<class T, class TC = listify, class FC = clear<TC>>
  using find = find_if<is<T>, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using find_if = unpack<L, mp::find_if<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using find_if_not = unpack<L, mp::find_if_not<Pred, TC, FC>>;

    template<class L, class T, class TC = mp::listify, class FC = clear<TC>>
    using find = unpack<L, mp::find_if<mp::is<T>, TC, FC>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<>
  struct find_if_impl<_drop_while_continue>
  {
    template<class TC, class FC, class... xs>
    using f = typename FC::template f<xs...>;
  };

  template<std::size_t n>
  struct find_if_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, class... xs>
    using f = typename drop_front<number<sizeof...(xs)-n-1>, TC>::template f<xs...>;
  };
}
/// \endcond
