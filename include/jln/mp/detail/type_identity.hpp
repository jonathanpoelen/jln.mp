#pragma once

#if __cplusplus > 201703L
#include <type_traits>

namespace jln::mp::detail
{
  using std::type_identity;
}
#else
namespace jln::mp::detail
{
  template<class T>
  struct type_identity
  {
    using type = T;
  };
}
#endif
