#pragma once

#include "../functional/try_invoke.hpp"
#include "../algorithm/transform.hpp"
#include "../number/operators.hpp"
#include "../list/front.hpp"

#include <type_traits>


namespace jln::mp::detail
{
  template<bool>
  struct _monadicify;
}

namespace jln::mp
{
  template<class C, class FC = violation>
  using monadic = if_<same_as<na>, FC, C>;

  template<class C, class FC = violation>
  using monadic0 = if_<front<same_as<na>>, FC, C>;

  template<class C, class FC = violation>
  using monadic_xs = if_<transform<same_as<na>, or_<>>, FC, C>;

  template<class T, class C, class FC = violation>
  using monadic_if_na = typename detail::_monadicify<
    std::is_same<na, T>::value>::template f<monadic, C, FC>;

  template<class T, class C, class FC = violation>
  using monadic0_if_na = typename detail::_monadicify<
    std::is_same<na, T>::value>::template f<monadic0, C, FC>;

  template<class T, class C, class FC = violation>
  using monadic_xs_if_na = typename detail::_monadicify<
    std::is_same<na, T>::value>::template f<monadic_xs, C, FC>;
}

namespace jln::mp::detail
{
  template<bool>
  struct _monadicify
  {
    template<template<class, class> class F, class C, class FC>
    using f = F<C, FC>;
  };

  template<>
  struct _monadicify<false>
  {
    template<template<class, class> class F, class C, class FC>
    using f = C;
  };
}
