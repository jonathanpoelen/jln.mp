#pragma once

#include "identity.hpp"
#include "../list/list.hpp"
#include "../number/number.hpp"
#include "../utility/always.hpp"
#include "../utility/same_as.hpp"


namespace jln::mp
{
  struct na {};

  using is_na = same_as<na>;
  using violation = always<na>;

  /// \cond
  namespace detail
  {
    template<class, class, class = void>
    struct _try_impl;

    template<class x>
    struct _try_dispatch;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes \c TC::f<result> whetehr \c F::f<xs...> is a valid expression
  /// other than \c na, otherwhise invokes \c FC::f<xs...>.
  /// \pre \c F::f<xs...> must be a SFINAE compatible expression
  /// \treturn \value
  template<class F, class TC = identity, class FC = violation>
  struct try_;

  template<class F, class FC>
  using try_or = try_<F, identity, FC>;

  template<class F, class TC, class FC>
  struct try_
  {
    template<class... xs>
    using f = typename detail::_try_dispatch<
      typename detail::_try_impl<F, list<xs...>>::type
    >::template f<TC, FC, xs...>;
  };

  namespace emp
  {
    template<class F, class TC, class FC, class... xs>
    using try_ = typename try_<F, TC, FC>::template f<xs...>;

    template<class F, class FC, class... xs>
    using try_or = typename try_<F, mp::identity, FC>::template f<xs...>;
  }
}


namespace jln::mp
{
  /// \cond
  template<class F>
  struct try_<F, always<true_>, always<false_>>
  {
    template<class... xs>
    using f = number<!std::is_same<na,
      typename detail::_try_impl<F, list<xs...>>::type
    >::value>;
  };

  template<class F>
  struct try_<F, identity, violation>
  {
    template<class... xs>
    using f = typename detail::_try_impl<F, list<xs...>>::type;
  };
  /// \endcond
}

/// \cond
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

  template<class x>
  struct _try_dispatch
  {
    template<class TC, class FC, class...>
    using f = typename TC::template f<x>;
  };

  template<>
  struct _try_dispatch<na>
  {
    template<class TC, class FC, class... xs>
    using f = typename FC::template f<xs...>;
  };
}
/// \endcond
