#pragma once

#include "../utility/conditional.hpp"
#include "../utility/always.hpp"
#include "../number/number.hpp"
#include "../functional/call.hpp"

namespace jln::mp
{
  /// \ingroup functional

  /// A conditional expression.
  /// \return \value
  template<class Pred, class TC, class FC = always<false_>>
  struct if_
  {
    template<class... xs>
    using f = typename mp::conditional_c<bool(call<Pred, xs...>::value)>
      ::template f<TC, FC>
      ::template f<xs...>;
  };

  namespace emp
  {
    template<class Pred, class TC, class FC, class... xs>
    using if_ = typename conditional<call<Pred, xs...>, TC, FC>
      ::template f<xs...>;
  }
}
