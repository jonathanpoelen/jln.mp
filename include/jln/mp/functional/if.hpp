#pragma once

#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// A conditional expression.
  /// \treturn \value
  template<class Pred, class TC, class FC = always<false_>>
  struct if_
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE_T(
      (mp::conditional_c<bool(call<Pred, xs...>::value)>::template f<TC, FC>),
      xs...);
  };

  namespace emp
  {
    template<class Pred, class TC, class FC, class... xs>
    using if_ = JLN_MP_CALL_TRACE((conditional<call<Pred, xs...>, TC, FC>), xs...);
  }
}
