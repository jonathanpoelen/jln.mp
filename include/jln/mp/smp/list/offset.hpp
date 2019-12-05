#pragma once

#include "../functional/identity.hpp"
#include "../../functional/try_invoke.hpp"
#include "../../number/as_number.hpp"
#include "../../list/offset.hpp"

namespace jln::mp::detail
{
  template<bool>
  struct _smp_offset
  {
    template<class I, class C>
    using f = valid_contract<
      mp::offset<number<I::value>, subcontract<C>>>;
  };

  template<>
  struct _smp_offset<false>
  {
    template<class I, class C>
    using f = bad_contract;
  };
}

namespace jln::mp::smp
{
  template <class I, class C = identity>
  using offset = typename detail::_smp_offset<
    mp::is_invocable<mp::as_number<>>::f<I>::value
  >::template f<I, C>;

  template <int_ i, class C = identity>
  using offset_c = valid_contract<mp::offset<number<i>, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class I, class C>
  struct _sfinae<sfinae, offset<I, C>>
  {
    using type = smp::offset<I, sfinae<C>>;
  };
}
