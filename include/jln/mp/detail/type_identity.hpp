#pragma once

#include <type_traits>

#ifdef __cpp_lib_type_identity
#  if __cpp_lib_type_identity > 201806L
#    define JLN_MP_USE_STD_TYPE_IDENTITY
#  endif
#endif

namespace jln::mp::detail
{
#ifdef JLN_MP_USE_STD_TYPE_IDENTITY
  using std::type_identity;
#else
  template<class T>
  struct type_identity
  {
    using type = T;
  };
#endif
}

#undef JLN_MP_USE_TYPE_IDENTITY
