// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/tee.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class F, class C>
    struct not_fn_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Returns the negation of \c F.
  /// \treturn \bool
  template<class F, class C = identity>
  using not_fn = typename detail::not_fn_impl<F, C>::type;

  namespace emp
  {
    template<class F, class... xs>
    using not_of = mp::number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(
      JLN_MP_DCALL_V_TRACE_XS(xs, F, xs...)::value
    )>;

    template<class L, class F, class C = mp::identity>
    using not_fn = typename detail::_unpack<mp::not_fn<F, C>, L>::type;
  }
}


#include <jln/mp/list/push_back.hpp>
#include <jln/mp/list/push_front.hpp>
#include <jln/mp/algorithm/same.hpp>
#include <jln/mp/utility/is.hpp>
#include <jln/mp/functional/continuation.hpp>
#include <jln/mp/number/to_bool.hpp>
#include <jln/mp/number/not.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct to_not_fn;

  template<class F>
  using to_not_fn_t = typename to_not_fn<F>::type;

  template<class Pred>
  struct to_not_fn
  {
    using type = tee<Pred, not_<>>;
  };

  template<>
  struct to_not_fn<not_<>>
  {
    using type = not_<not_<>>;
  };

  template<>
  struct to_not_fn<not_<not_<>>>
  {
    using type = not_<>;
  };

  template<class C>
  struct to_not_fn<not_<to_bool<C>>>
  : to_not_fn<not_<C>>
  {};

  template<class C>
  struct to_not_fn<not_<not_<not_<C>>>>
  : to_not_fn<not_<C>>
  {};

  template<>
  struct to_not_fn<identity>
  {
    using type = not_<>;
  };

  template<class PredNot>
  struct optimise_not_not;

  template<class PredNot>
  struct optimise_not_not<not_<not_<PredNot>>>
  {
    using type = PredNot;
  };

  template<class PredNot>
  struct optimise_not_not
  {
    using type = PredNot;
  };

  template<class C>
  struct to_not_fn<to_bool<C>>
  {
    using type = to_bool<typename optimise_not_not<to_not_fn_t<C>>::type>;
  };

  template<class x, class C>
  struct to_not_fn<is<x, C>>
  {
    using type = is<x, typename optimise_not_not<to_not_fn_t<C>>::type>;
  };

  template<class C>
  struct to_not_fn<same<C>>
  {
    using type = same<typename optimise_not_not<to_not_fn_t<C>>::type>;
  };

  template<class PredNot>
  struct to_not_fn_cfe;

  template<template<class...> class F, class C, class Not>
  struct to_not_fn_cfe<cfe<F, tee<C, Not>>>
  {
    using type = tee<cfe<F, C>, Not>;
  };

  template<class PredNot>
  struct to_not_fn_cfe
  {
    using type = PredNot;
  };

  template<template<class...> class F, class C>
  struct to_not_fn<cfe<F, C>>
  : to_not_fn_cfe<cfe<F, to_not_fn_t<C>>>
  {};

  template<class x, class C>
  struct to_not_fn<push_front<x, C>>
  {
    using type = push_front<x, to_not_fn_t<C>>;
  };

  template<class x, class C>
  struct to_not_fn<push_back<x, C>>
  {
    using type = push_back<x, to_not_fn_t<C>>;
  };

  template<class Pred>
  struct to_not_fn_tee;

  template<class Pred>
  struct to_not_fn_tee<tee<Pred, not_<>>>
  {
    using type = tee<Pred, not_<not_<>>>;
  };

  template<class Pred>
  struct to_not_fn_tee
  : to_not_fn<Pred>
  {};

  template<class Pred>
  struct to_not_fn<tee<Pred, not_<>>>
  : to_not_fn_tee<to_not_fn_t<Pred>>
  {};

  template<class PredNot>
  struct to_not_fn_tee2;

  template<class PredNot>
  struct to_not_fn_tee2<tee<PredNot, not_<>>>
  : to_not_fn<PredNot>
  {};

  template<class PredNot>
  struct to_not_fn_tee2<tee<PredNot, not_<not_<>>>>
  : to_not_fn<PredNot>
  {};

  template<class PredNot>
  struct to_not_fn_tee2
  {
    using type = PredNot;
  };

  template<class Pred, class C>
  struct to_not_fn<tee<Pred, C>>
  : to_not_fn_tee2<tee<Pred, to_not_fn_t<C>>>
  {};

  template<class F, class C>
  struct not_fn_impl
  : to_not_fn<tee<F, C>>
  {};

  template<class F>
  struct not_fn_impl<F, identity>
  : to_not_fn<F>
  {};
}
/// \endcond
