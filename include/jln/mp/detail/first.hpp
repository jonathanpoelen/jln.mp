#pragma once

#include "../utility/conditional.hpp"

namespace jln::mp::detail
{
  template<class x, class... xs>
#if defined(__GNUC__) and !defined(__clang__)
  using first = x;
#else
  using first = typename conditional_c<0 <= sizeof...(xs)>::template f<x, void>;
#endif
}
