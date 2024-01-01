// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/memoize.hpp>
#include <jln/mp/list/list.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/is.hpp>


namespace jln::mp
{
  using is_na = is<na>;
  using violation = always<na>;

  /// \cond
  namespace detail
  {
    template<class x>
    struct try_dispatch;

#if JLN_MP_MEMOIZED_ALIAS
    template<class, class, class = void>
    struct _try_impl;

    #define JLN_MP_CALL_TRY_IMPL(F, params) detail::_try_impl<F, list<params>>::type
#else
    #define JLN_MP_CALL_TRY_IMPL(F, params) detail::memoizer_impl<F, params>::try_type
#endif
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes \c TC::f<result> whether \c FC::f<xs...> is a valid expression
  /// other than \c na, otherwhise invokes \c FC::f<xs...>.
  /// \pre \c F::f<xs...> must be a SFINAE compatible expression
  /// \treturn \value
  template<class F, class TC = identity, class FC = violation>
  struct try_
  {
    template<class... xs>
    using f = typename detail::try_dispatch<
      typename JLN_MP_CALL_TRY_IMPL(F, xs...)
    >::template f<TC, FC, xs...>;
  };

  template<class F, class FC = always<false_>>
  using try_or = try_<F, identity, FC>;

  namespace emp
  {
    template<class F, class TC, class FC, class... xs>
    using try_ = typename try_<F, TC, FC>::template f<xs...>;

    template<class F, class FC, class... xs>
    using try_or = typename mp::try_<F, mp::identity, FC>::template f<xs...>;
  }
}


/// \cond
namespace jln::mp
{
  template<class F>
  struct try_<F, always<true_>, always<false_>>
  {
    template<class... xs>
    using f = number<!std::is_same<na,
      typename detail::memoizer_impl<F, xs...>::try_type
    >::value>;
  };

  template<class F>
  struct try_<F, always<false_>, always<true_>>
  {
    template<class... xs>
    using f = number<std::is_same<na,
      typename detail::memoizer_impl<F, xs...>::try_type
    >::value>;
  };

  template<class F>
  struct try_<F, identity, violation>
  {
    template<class... xs>
    using f = typename JLN_MP_CALL_TRY_IMPL(F, xs...);
  };
}

namespace jln::mp::detail
{
  template<class x>
  struct try_dispatch
  {
    template<class TC, class FC, class...>
    using f = JLN_MP_CALL_TRACE(TC, x);
  };

  template<>
  struct try_dispatch<na>
  {
    template<class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(FC, xs...);
  };
}

#if JLN_MP_MEMOIZED_ALIAS
#include <type_traits>

namespace jln::mp::detail
{
  template<class, class, class>
  struct _try_impl
  {
    using type = na;
  };

  template<class F, class... xs>
  struct _try_impl<F, list<xs...>, std::void_t<typename F::template f<xs...>>>
  {
    using type = typename F::template f<xs...>;
  };
}
#endif

#undef JLN_MP_CALL_TRY_IMPL
/// \endcond
