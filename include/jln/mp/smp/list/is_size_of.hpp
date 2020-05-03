#pragma once

#include "../functional/identity.hpp"
#include "../list/size.hpp"
#include "../utility/same_as.hpp"
#include "../../list/is_size_of.hpp"

namespace jln::mp::smp
{
  template<int_ n, class C = identity>
  using is_size_of_c = contract<mp::is_size_of_c<n, assume_number<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(is_size_of, (N), (C, smp::identity), smp::is_size_of_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, is_size_of<N, C>>
  {
    using type = smp::is_size_of<N, sfinae<C>>;
  };
}
/// \endcond
