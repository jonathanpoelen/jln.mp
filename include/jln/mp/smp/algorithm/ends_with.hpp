#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/algorithm/ends_with.hpp>
#include <jln/mp/list/is_list.hpp>

namespace jln::mp::smp
{
  template<class Seq, class C = identity>
  using ends_with = typename mp::conditional_c<detail::_is_list<Seq>::type::value>
    ::template f<contract<mp::ends_with<Seq, assume_number<C>>>, bad_contract>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Seq, class C>
  struct _sfinae<sfinae, ends_with<Seq, C>>
  {
    using type = smp::ends_with<Seq, sfinae<C>>;
  };
}
/// \endcond
