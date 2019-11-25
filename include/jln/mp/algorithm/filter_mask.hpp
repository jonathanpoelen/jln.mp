#pragma once

#include "remove.hpp"
#include "../list/join.hpp"

namespace jln::mp::detail
{
  template<bool... bools>
  struct filter_mask
  {
    template<class C, class... xs>
    using f = typename join<C>::template f<
      typename _wrap_if<bools>::template f<xs>
    ...>;
  };
}
