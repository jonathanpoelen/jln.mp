#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/list/listify.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup number

  template<class C = listify>
  struct numbers
  {
    template<int_... ns>
    using f = JLN_MP_DCALL_TRACE_XS(ns, C, number<ns>...);
  };

  /// \cond
  template<template<class...> class C>
  struct numbers<lift<C>>
  {
    template<int_... ns>
    using f = C<number<ns>...>;
  };
  /// \endcond

  namespace emp
  {
    template<int_... vs>
    using numbers = list<number<vs>...>;
  }
}
