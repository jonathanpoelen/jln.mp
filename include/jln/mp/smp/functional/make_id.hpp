#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/functional/make_id.hpp>

#ifdef __cpp_generic_lambdas
#if __cpp_generic_lambdas >= 201707L

namespace jln::mp::smp
{
  template<class Tag, class C = identity>
  using make_id_for = try_contract<mp::make_id_for<Tag, assume_unary<C>>>;

  template<class C = identity>
  using make_id = try_contract<mp::make_id_for<default_make_id_tag, assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Tag, class C>
  struct _sfinae<sfinae, make_id_for<Tag, C>>
  {
    using type = smp::make_id_for<Tag, C>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT2(argument_category::unary, make_id_for);
}
/// \endcond

#endif
#endif
