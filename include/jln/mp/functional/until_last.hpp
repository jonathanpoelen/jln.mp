// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
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


#include <jln/mp/functional/if.hpp>
#include <jln/mp/functional/try.hpp>
#include <cstddef>

/// \cond
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

#define JLN_MP_MK_UNTIL_LAST_IMPL(tpl_params, arg_names)                       \
  template<                                                                    \
    template<JLN_MP_UNPACK tpl_params, class, class> class Tpl,                \
    JLN_MP_UNPACK tpl_params, class TC, class FC>                              \
  struct until_last_impl<Tpl<JLN_MP_UNPACK arg_names, TC, FC>>                 \
  {                                                                            \
    using type = Tpl<JLN_MP_UNPACK arg_names, recursively<                     \
      pop_front<Tpl<JLN_MP_UNPACK arg_names, next_recursion, stop_recursion>>, \
      TC                                                                       \
    >, FC>;                                                                    \
  }

  JLN_MP_MK_UNTIL_LAST_IMPL((class Pred), (Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((class Data1, class Pred), (Data1, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((class Data1, class Data2, class Pred),
                            (Data1, Data2, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((class Data1, class Data2, class Data3, class Pred),
                            (Data1, Data2, Data3, Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, class Pred), (Data1, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, class Data2, class Pred),
                            (Data1, Data2, Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, int_ Data2, class Pred),
                            (Data1, Data2, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, int_ Data2, class Data3, class Pred),
                            (Data1, Data2, Data3, Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((std::size_t Data1, class Pred), (Data1, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((std::size_t Data1, class Data2, class Pred),
                            (Data1, Data2, Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((std::size_t Data1, std::size_t Data2, class Pred),
                            (Data1, Data2, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((std::size_t Data1, std::size_t Data2, class Data3, class Pred),
                            (Data1, Data2, Data3, Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, std::size_t Data2, class Pred),
                            (Data1, Data2, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, std::size_t Data2, class Data3, class Pred),
                            (Data1, Data2, Data3, Pred));

#undef JLN_MP_MK_UNTIL_LAST_IMPL
}
/// \endcond
