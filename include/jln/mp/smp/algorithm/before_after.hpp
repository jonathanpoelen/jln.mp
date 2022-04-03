#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/clear.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/before_after.hpp>
#include <jln/mp/list/is_list.hpp>

namespace jln::mp::smp
{
  template<class Seq, class TC = listify, class FC = clear<TC>>
  using before_after = typename mp::conditional_c<detail::_is_list<Seq>::type::value>
    ::template f<contract<mp::before_after<Seq, subcontract<TC>, subcontract<FC>>>, bad_contract>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Seq, class TC, class FC>
  struct _sfinae<sfinae, before_after<Seq, TC, FC>>
  {
    using type = smp::before_after<Seq, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
