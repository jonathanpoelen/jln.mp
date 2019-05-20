#pragma once

#include "../functional/when.hpp"

namespace jln::mp
{
  template<class continuation = identity>
  struct size
  {
    template<class... xs>
    using f = number<sizeof...(xs)>;
  };

  namespace smp
  {
    template<class continuation = identity>
    using size = when<always<true_>, mp::size<when_continuation<continuation>>>;
  }
} // namespace jln::mp
