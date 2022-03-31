#pragma once

#include <jln/mp/list/clear.hpp>
#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/functional/recursively.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct until_last_impl
    {};
  }
  /// \endcond

  /// \ingroup functional

  /// Uses a \c Searcher in a loop until the last result.
  /// Searcher must end with the continuations TC and FC.
  /// `until_last_t<find, is<x>, TC, FC>` is equivalent to \c find_last
  /// \treturn \sequence
  template<class Searcher>
  using until_last = typename detail::until_last_impl<Searcher>::type;

  template<template<class...> class Tpl, class Pred, class TC = listify, class FC = clear<TC>>
  using until_last_t = Tpl<Pred, recursively<
    pop_front<Tpl<Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;

  template<
    template<class...> class Tpl,
    class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_until_last_t = Tpl<OffsetEnd, Pred, recursively<
    pop_front<Tpl<OffsetEnd, Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;

  template<
    template<int_, class...> class Tpl,
    int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_until_last_t_c = Tpl<OffsetEnd, Pred, recursively<
    pop_front<Tpl<OffsetEnd, Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;

  namespace emp
  {
    template<class L, class Searcher>
    using until_last = unpack<L, mp::until_last<Searcher>>;

    template<
      class L, template<class...> class Tpl,
      class Pred, class TC = listify, class FC = clear<TC>>
    using until_last_t = unpack<L, mp::until_last_t<Tpl, Pred, TC, FC>>;

    template<
      class L, template<class...> class Tpl,
      class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
    using partial_until_last_t = unpack<L, mp::partial_until_last_t<Tpl, OffsetEnd, Pred, TC, FC>>;

    template<
      class L, template<int_, class...> class Tpl,
      int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
    using partial_until_last_t_c = unpack<L,
      mp::partial_until_last_t_c<Tpl, OffsetEnd, Pred, TC, FC>>;
  }
}

/// \cond
#include <jln/mp/functional/if.hpp>
#include <jln/mp/functional/try.hpp>

namespace jln::mp::detail
{
  template<class F, class TC, class FC>
  struct until_last_impl<try_<F, TC, FC>>
  {
    using type = try_<typename until_last_impl<F>::type, TC, FC>;
  };

  template<class Pred, class TC>
  struct until_last_impl<if_<Pred, TC, violation>>
  {
    using type = if_<Pred, typename until_last_impl<TC>::type, violation>;
  };

  template<template<class, class> class Tpl, class TC, class FC>
  struct until_last_impl<Tpl<TC, FC>>
  {
    using type = Tpl<recursively<
      pop_front<Tpl<next_recursion, stop_recursion>>,
      TC
    >, FC>;
  };

  template<template<class, class, class> class Tpl, class Pred, class TC, class FC>
  struct until_last_impl<Tpl<Pred, TC, FC>>
  {
    using type = Tpl<Pred, recursively<
      pop_front<Tpl<Pred, next_recursion, stop_recursion>>,
      TC
    >, FC>;
  };

  template<
    template<class, class, class, class> class Tpl,
    class Data, class Pred, class TC, class FC>
  struct until_last_impl<Tpl<Data, Pred, TC, FC>>
  {
    using type = Tpl<Data, Pred, recursively<
      pop_front<Tpl<Data, Pred, next_recursion, stop_recursion>>,
      TC
    >, FC>;
  };

  template<
    template<class, class, class, class, class> class Tpl,
    class Data1, class Data2, class Pred, class TC, class FC>
  struct until_last_impl<Tpl<Data1, Data2, Pred, TC, FC>>
  {
    using type = Tpl<Data1, Data2, Pred, recursively<
      pop_front<Tpl<Data1, Data2, Pred, next_recursion, stop_recursion>>,
      TC
    >, FC>;
  };

  template<template<int_, class, class> class Tpl, int_ OffsetEnd, class TC, class FC>
  struct until_last_impl<Tpl<OffsetEnd, TC, FC>>
  {
    using type = Tpl<OffsetEnd, recursively<
      pop_front<Tpl<OffsetEnd, next_recursion, stop_recursion>>,
      TC
    >, FC>;
  };

  template<template<int_, class, class, class> class Tpl, int_ OffsetEnd, class Pred, class TC, class FC>
  struct until_last_impl<Tpl<OffsetEnd, Pred, TC, FC>>
  {
    using type = Tpl<OffsetEnd, Pred, recursively<
      pop_front<Tpl<OffsetEnd, Pred, next_recursion, stop_recursion>>,
      TC
    >, FC>;
  };

  template<
    template<int_, class, class, class, class> class Tpl,
    int_ OffsetEnd, class Data, class Pred, class TC, class FC>
  struct until_last_impl<Tpl<OffsetEnd, Data, Pred, TC, FC>>
  {
    using type = Tpl<OffsetEnd, Data, Pred, recursively<
      pop_front<Tpl<OffsetEnd, Data, Pred, next_recursion, stop_recursion>>,
      TC
    >, FC>;
  };
}
/// \endcond
