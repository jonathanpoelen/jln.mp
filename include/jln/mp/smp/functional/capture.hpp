#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/functional/capture.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class... xs>
  decltype(((void(xs::value), ...), try_contract<mp::capture_v<xs...>>{})) smp_capture_v(xs*...);

  bad_contract smp_capture_v(...);

  template<class... xs>
  decltype(((void(xs::value), ...), try_contract<mp::reverse_capture_v<xs...>>{})) smp_reverse_capture_v(xs*...);

  bad_contract smp_reverse_capture_v(...);
}
/// \endcond

namespace jln::mp::smp
{
  template<class... xs>
  using capture = try_contract<mp::capture<xs...>>;

  template<class... xs>
  using capture_v = decltype(detail::smp_capture_v(static_cast<xs*>(nullptr)...));

#if __cplusplus >= 201703L
  template<auto... xs>
  using capture_c = capture<val<xs>...>;

  template<auto... xs>
  using capture_v_c = try_contract<mp::capture_v_c<xs...>>;
#else
  template<int_... xs>
  using capture_c = capture<number<xs>...>;

  template<int_... xs>
  using capture_v_c = try_contract<mp::capture_v_c<xs...>>;
#endif

  template<class... xs>
  using reverse_capture = try_contract<mp::reverse_capture<xs...>>;

  template<class... xs>
  using reverse_capture_v = decltype(detail::smp_reverse_capture_v(
    static_cast<xs*>(nullptr)...));

#if __cplusplus >= 201703L
  template<auto... xs>
  using reverse_capture_c = reverse_capture<val<xs>...>;

  template<int_... xs>
  using reverse_capture_v_c = try_contract<mp::capture_v_c<xs...>>;
#else
  template<int_... xs>
  using reverse_capture_c = reverse_capture<number<xs>...>;

  template<int_... xs>
  using reverse_capture_v_c = try_contract<mp::capture_v_c<xs...>>;
#endif
}

/// \cond
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

  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, reverse_capture<xs...>>
  {
    using type = smp::reverse_capture<xs...>;
  };

  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, reverse_capture_v<xs...>>
  {
    using type = smp::reverse_capture_v<xs...>;
  };

#if __cplusplus >= 201703L
  template<template<class> class sfinae, auto... xs>
#else
  template<template<class> class sfinae, int_... xs>
#endif
  struct _sfinae<sfinae, reverse_capture_v_c<xs...>>
  {
    using type = smp::reverse_capture_v_c<xs...>;
  };
}
/// \endcond
