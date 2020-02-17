#pragma once

namespace jln::mp::detail
{
  // TODO C++20
  template<class T>
  struct type_identity
  {
    using type = T;
  };
}
