#pragma once

#include "../assume.hpp"
#include "../../functional/try.hpp"
#include "../../list/wrap_in_list.hpp"

namespace jln::mp::smp
{
  template<class Pred>
  using wrap_in_list_if = try_contract<
    mp::wrap_in_list_if<try_assume_unary_or_more<Pred>>>;

  template<class Pred>
  using wrap_in_list_if_not = try_contract<
    mp::wrap_in_list_if_not<try_assume_unary_or_more<Pred>>>;

  template<bool b>
  using wrap_in_list_c = contract<mp::wrap_in_list_c<b>>;
}

JLN_MP_MAKE_REGULAR_SMP1_P(wrap_in_list, (N), smp::wrap_in_list_c<N::value>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred>
  struct _sfinae<sfinae, _wrap_in_list_if<Pred>>
  {
    using type = smp::wrap_in_list_if<sfinae<Pred>>;
  };

  template<template<class> class sfinae, class Pred>
  struct _sfinae<sfinae, _wrap_in_list_if_not<Pred>>
  {
    using type = smp::wrap_in_list_if_not<sfinae<Pred>>;
  };

  template<template<class> class sfinae, bool b>
  struct _sfinae<sfinae, wrap_in_list_c<b>>
  {
    using type = smp::wrap_in_list_c<b>;
  };
}
/// \endcond