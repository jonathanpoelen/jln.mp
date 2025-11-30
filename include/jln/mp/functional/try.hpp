// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/same.hpp>
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

#if JLN_MP_FEATURE_CONCEPTS
  template<class T>
  concept not_same_as_na = !JLN_MP_IS_SAME(T, na);
#endif

  /// \cond
  namespace detail
  {
    template<class x>
    struct try_dispatch;

#if JLN_MP_REQUIRES_AS_FAST_SFINAE && (!JLN_MP_GCC || JLN_MP_GCC >= 1500)
    template<bool>
    struct try_select;

#elif JLN_MP_MEMOIZED_ALIAS && !JLN_MP_WORKAROUND(JLN_MP_MSVC, < 1942)
    template<class, class, class = void>
    struct _try_impl;

#   define JLN_MP_CALL_TRY_IMPL(F, params) detail::_try_impl<F, list<params>>::type
#elif JLN_MP_CUDA
#   define JLN_MP_CALL_TRY_IMPL(F, params) detail::memoizer_impl<void, F, params>::try_type
#else
#   define JLN_MP_CALL_TRY_IMPL(F, params) detail::memoizer_impl<F, params>::try_type
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
#if JLN_MP_REQUIRES_AS_FAST_SFINAE && (!JLN_MP_GCC || JLN_MP_GCC >= 1500)
    template<class... xs>
    using f = typename detail::try_select<requires {
      requires not_same_as_na<typename F::template f<xs...>>;
    }>
    ::template f<F, TC, FC, xs...>;
#else
    template<class... xs>
    using f = typename detail::try_dispatch<
      typename JLN_MP_CALL_TRY_IMPL(F, xs...)
    >
    ::template f<TC, FC, xs...>;
#endif
  };

  template<class F, class FC = violation>
  using try_or_else = try_<F, identity, FC>;

  template<class F, class FT = na>
  using try_or = try_<F, identity, always<FT>>;

  /// Checks whether \c F::f<xs...> is invocable.
  /// \pre \c F::f<xs...> must be a SFINAE compatible expression
  /// \treturn \bool
  template<class F, class C = identity>
  using is_invocable = try_<F, always<true_, C>, always<false_, C>>;

  /// Checks whether \c F::f<xs...> is not invocable.
  /// \pre \c F::f<xs...> must be a SFINAE compatible expression
  /// \treturn \bool
  template<class F, class C = identity>
  using is_not_invocable = try_<F, always<false_, C>, always<true_, C>>;

  namespace emp
  {
    template<class F, class TC, class FC, class... xs>
    using try_ = typename mp::try_<F, TC, FC>::template f<xs...>;

    template<class F, class FC, class... xs>
    using try_or_else = typename mp::try_<F, mp::identity, FC>::template f<xs...>;

    template<class F, class FT, class... xs>
    using try_or = typename mp::try_<F, mp::identity, always<FT>>::template f<xs...>;

    template<class F, class... xs>
    inline constexpr bool is_invocable_v =
#if JLN_MP_REQUIRES_AS_FAST_SFINAE && (!JLN_MP_GCC || JLN_MP_GCC >= 1500)
      requires { requires not_same_as_na<typename F::template f<xs...>>; }
#else
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(
        JLN_MP_IS_SAME(na, typename JLN_MP_CALL_TRY_IMPL(F, xs...))
      )
#endif
    ;

    template<class F, class... xs>
    inline constexpr bool is_not_invocable_v = !is_invocable_v<F, xs...>;

    template<class F, class... xs>
    using is_invocable = number<is_invocable_v<F, xs...>>;

    template<class F, class... xs>
    using is_not_invocable = number<!is_invocable_v<F, xs...>>;
  }
}


/// \cond
namespace jln::mp
{
  template<class F>
  struct try_<F, always<true_>, always<false_>>
  {
    template<class... xs>
    using f = number<emp::is_invocable_v<F, xs...>>;
  };

  template<class F>
  struct try_<F, always<false_>, always<true_>>
  {
    template<class... xs>
    using f = number<!emp::is_invocable_v<F, xs...>>;
  };

#if !(JLN_MP_REQUIRES_AS_FAST_SFINAE && (!JLN_MP_GCC || JLN_MP_GCC >= 1500))
  template<class F>
  struct try_<F, identity, violation>
  {
    template<class... xs>
    using f = typename JLN_MP_CALL_TRY_IMPL(F, xs...);
  };
#endif
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

#if JLN_MP_REQUIRES_AS_FAST_SFINAE && (!JLN_MP_GCC || JLN_MP_GCC >= 1500)
namespace jln::mp::detail
{
  template<bool>
  struct try_select
  {
    template<class F, class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(TC, typename F::template f<xs...>);
  };

  template<>
  struct try_select<false>
  {
    template<class F, class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(FC, xs...);
  };
}

#elif JLN_MP_MEMOIZED_ALIAS && !JLN_MP_WORKAROUND(JLN_MP_MSVC, < 1942)
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
