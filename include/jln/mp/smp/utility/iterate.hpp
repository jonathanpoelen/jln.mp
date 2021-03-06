#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/utility/iterate.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/list/is_size_of.hpp>

namespace jln::mp::smp
{
  template<uint_ n, class F, class C = identity>
  using iterate_c = test_contract<mp::is_size_of_c<1>, mp::iterate<
    mp::number<n>,
    mp::monadic0<assume_unary<F>>,
    mp::monadic0<assume_unary<C>>>
  >;
}

JLN_MP_MAKE_REGULAR_SMP3_P(iterate, (n), (F), (C, smp::identity),
    smp::iterate_c<mp::uint_{n::value}, F, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class n, class F, class C>
  struct _sfinae<sfinae, iterate<n, F, C>>
  {
    using type = smp::iterate<n, sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
