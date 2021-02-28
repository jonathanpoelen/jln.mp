#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/functional/recursively.hpp>

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using recursively = contract<mp::recursively<
    try_subcontract<F, mp::identity, mp::always<na, mp::recursion_result>>,
    monadic<subcontract<C>>>>;

  template<class F, class C = identity>
  using recursively_as_much_as_possible = contract<mp::recursively_as_much_as_possible<
    try_subcontract<F, mp::identity, mp::always<na, mp::recursion_result>>,
    monadic<subcontract<C>>>>;

  using stop_recursion = contract<mp::stop_recursion>;
  using next_recursion = contract<mp::next_recursion>;
  using recursion_result = contract<mp::recursion_result>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, recursively<F, C>>
  {
    using type = smp::recursively<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, recursively_as_much_as_possible<F, C>>
  {
    using type = smp::recursively_as_much_as_possible<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae>
  struct _sfinae<sfinae, stop_recursion>
  {
    using type = smp::stop_recursion;
  };

  template<template<class> class sfinae>
  struct _sfinae<sfinae, next_recursion>
  {
    using type = smp::next_recursion;
  };

  template<template<class> class sfinae>
  struct _sfinae<sfinae, recursion_result>
  {
    using type = smp::recursion_result;
  };
}
/// \endcond
