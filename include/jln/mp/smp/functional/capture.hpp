#pragma once

#include "../assume.hpp"
#include "../../functional/capture.hpp"

namespace jln::mp::detail
{
  template<class... xs>
  decltype(((void(xs::value), ...), try_contract<mp::capture_v<xs...>>{})) smp_capture_v(xs*...);

  bad_contract smp_capture_v(...);

  template<class... xs>
  decltype(((void(xs::value), ...), try_contract<mp::reverse_capture_v<xs...>>{})) smp_reverse_capture_v(xs*...);

  bad_contract smp_reverse_capture_v(...);
}

namespace jln::mp::smp
{
  template<class... xs>
  using capture = try_contract<mp::capture<xs...>>;

  template<class... xs>
  using capture_v = decltype(detail::smp_capture_v(static_cast<xs*>(nullptr)...));

  template<auto... xs>
  using capture_c = try_contract<mp::capture_c<xs...>>;

  template<class... xs>
  using reverse_capture = try_contract<mp::reverse_capture<xs...>>;

  template<class... xs>
  using reverse_capture_v = decltype(detail::smp_reverse_capture_v(
    static_cast<xs*>(nullptr)...));

  template<auto... xs>
  using reverse_capture_c = try_contract<mp::reverse_capture_c<xs...>>;
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

  template<template<class> class sfinae, auto... xs>
  struct _sfinae<sfinae, reverse_capture_c<xs...>>
  {
    using type = smp::reverse_capture_c<xs...>;
  };
}
