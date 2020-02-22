#pragma once

#include "../../functional/capture.hpp"
#include "../../functional/try_invoke.hpp"
#include "../../detail/first.hpp"

namespace jln::mp::detail
{
  template<class... xs>
  std::bool_constant<(((void(xs::value), ...), 1))> all_has_value(xs*...);

  std::false_type all_has_value(...);

#if defined(__GNUC__) && !defined(__clang__)
  template<class... xs>
  struct smp_capture_v
  {
    template<class C>
    using f = typename C::template f<first<xs, C>::value...>;
  };
#else
  template<class>
  struct smp_capture_v_select;
#endif
}

namespace jln::mp::smp
{
  template<class... xs>
  using capture = try_contract<mp::capture<xs...>>;

  template<class... xs>
  // TODO or not
#if defined(__GNUC__) && !defined(__clang__)
  using capture_v = try_contract<detail::smp_capture_v<xs...>>;
#else
  // using capture_v = try_contract<mp::capture_v<xs...>>;
  using capture_v = typename detail::smp_capture_v_select<
    // TODO detail::_has_value<xs>::type::value && ...
    decltype(detail::all_has_value(static_cast<xs*>(nullptr)...))
  >::template f<xs...>;
#endif

  template<auto... xs>
  using capture_c = try_contract<mp::capture_c<xs...>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, capture<xs...>>
  {
    using type = smp::capture<xs...>;
  };

  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, capture_v<xs...>>
  {
    using type = smp::capture_v<xs...>;
  };

  template<template<class> class sfinae, auto... xs>
  struct _sfinae<sfinae, capture_c<xs...>>
  {
    using type = smp::capture_c<xs...>;
  };

#if !defined(__GNUC__) || defined(__clang__)
  template<>
  struct smp_capture_v_select<std::false_type>
  {
    template<class... xs>
    using f = bad_contract;
  };

  template<>
  struct smp_capture_v_select<std::true_type>
  {
    template<class... xs>
    using f = try_contract<mp::capture_v<xs...>>;
  };
#endif
}
