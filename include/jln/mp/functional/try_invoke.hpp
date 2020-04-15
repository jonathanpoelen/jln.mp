#pragma once

#include "identity.hpp"
#include "../list/list.hpp"
#include "../number/number.hpp"
#include "../utility/always.hpp"
#include "../utility/same_as.hpp"


namespace jln::mp
{
  struct na;
  using is_na = same_as<na>;
  using violation = always<na>;

  namespace detail
  {
    template<class, class, class = void>
    struct _try_invoke;

    template<class x>
    struct _try_invoke_dispatch;
  }

  template<class F, class TC = identity, class FC = violation>
  struct try_invoke;

  template<class F, class FC>
  using try_invoke_or = try_invoke<F, identity, FC>;

  template<class F, class TC, class FC>
  struct try_invoke
  {
    template<class... xs>
    using f = typename detail::_try_invoke_dispatch<
      typename detail::_try_invoke<F, list<xs...>>::type
    >::template f<TC, FC, xs...>;
  };

  namespace emp
  {
    template<class F, class TC, class FC, class... xs>
    using try_invoke = typename try_invoke<F, TC, FC>::template f<xs...>;

    template<class F, class FC, class... xs>
    using try_invoke_or = typename try_invoke<F, mp::identity, FC>::template f<xs...>;
  }
}


namespace jln::mp
{
  template<class F>
  struct try_invoke<F, always<true_>, always<false_>>
  {
    template<class... xs>
    using f = number<!std::is_same<na,
      typename detail::_try_invoke<F, list<xs...>>::type
    >::value>;
  };

  template<class F>
  struct try_invoke<F, identity, violation>
  {
    template<class... xs>
    using f = typename detail::_try_invoke<F, list<xs...>>::type;
  };
}

namespace jln::mp::detail
{
  template<class, class, class>
  struct _try_invoke
  {
    using type = na;
  };

  template<class F, class... xs>
  struct _try_invoke<F, list<xs...>, std::void_t<typename F::template f<xs...>>>
  {
    using type = typename F::template f<xs...>;
  };

  template<class x>
  struct _try_invoke_dispatch
  {
    template<class TC, class FC, class...>
    using f = typename TC::template f<x>;
  };

  template<>
  struct _try_invoke_dispatch<na>
  {
    template<class TC, class FC, class... xs>
    using f = typename FC::template f<xs...>;
  };
}
