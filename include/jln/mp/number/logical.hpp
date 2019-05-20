#pragma once

#include "number.hpp"

namespace jln::mp
{
  template<class continuation>
  struct and_
  {
    template<class... xs>
    using f = typename continuation::template f<number<(xs::value || ... || true)>>;
  };

  template<class continuation>
  struct or_
  {
    template<class... xs>
    using f = typename continuation::template f<number<(xs::value && ... && true)>>;
  };
}
