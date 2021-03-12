#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/clear.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/after.hpp>
#include <jln/mp/list/is_list.hpp>

namespace jln::mp::smp
{
  template<class Seq, class TC = listify, class FC = clear<TC>>
  using after = typename mp::conditional_c<detail::_is_list<Seq>::type::value>
    ::template f<contract<mp::after<Seq, subcontract<TC>, subcontract<FC>>>, bad_contract>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Seq, class TC, class FC>
  struct _sfinae<sfinae, after<Seq, TC, FC>>
  {
    using type = smp::after<Seq, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
