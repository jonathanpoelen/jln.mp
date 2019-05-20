#pragma once

#include "../number/number.hpp"
#include "conditional.hpp"
#include "call.hpp"

#include <type_traits>

namespace jln::mp
{
  namespace detail
  {
    template<template<class> class sfinae, class x>
    struct _sfinae;

    template<class continuation>
    struct _when_continuation;

    template<class function, class... xs, class = std::void_t<typename function::template f<xs...>>>
    true_ _is_invocable(function*, xs*...);
    false_ _is_invocable(...);

    template<class predicate>
    struct _when_is_predicate;

    template <unsigned n>
    struct _rotate;

    constexpr unsigned _rotate_step(unsigned n)
    {
      return
        n <= 8 ? n
      : n < 16 ? 8
      : n < 64 ? 16
      : n < 256 ? 64
      : 256
      ;
    }

    constexpr unsigned _rotate_size(unsigned n, unsigned size) {
      return n >= size ? (size == 0 ? 0 : n % size) : n;
    }

    template <class continuation, class... functions>
    struct _demux;

    template<class x, class = void>
    struct _has_value;
  }

  struct identity
  {
    template<class x>
    using f = x;
  };

  template<class x, class continuation = identity>
  struct always
  {
    template<class... xs>
    using f = typename continuation::template f<x>;
  };

  template<class predicate, class true_continuation, class false_continuation = always<false_>>
  struct if_
  {
    template<class... xs>
    using f = typename mp::conditional_c<predicate::template f<xs...>::value>
      ::template f<true_continuation, false_continuation>
      ::template f<xs...>;
  };

  template<class function, class continuation = identity>
  struct is_invocable
  {
    template<class... xs>
    using f = typename continuation::template f<decltype(detail::_is_invocable(static_cast<function*>(nullptr), static_cast<xs*>(nullptr)...))>;
  };

  template<template<class...> class function, class continuation = identity>
  struct cfl
  {
    template<class... xs>
    using f = call<continuation, typename function<xs...>::type>;
  };

  template<template<class...> class function, class continuation = identity>
  struct cfe
  {
    template<class... xs>
    using f = call<continuation, function<xs...>>;
  };

  template<class... vals>
  class list {};

  using listify = cfe<list>;

  template <class n, class continuation = listify>
  struct rotate
  {
    template<class... xs>
    using f = typename detail::_rotate<
      detail::_rotate_step(
        detail::_rotate_size(n::value, sizeof...(xs)))
    >::template f<detail::_rotate_size(n::value, sizeof...(xs)),
      continuation, xs...>;
  };

  // TODO DOXY template<class... functions, class continuation>
  template <typename... xs>
  struct demux : rotate<number<sizeof...(xs)-1>, cfe<detail::_demux>>::template f<xs...>
  {};

  template<class continuation = identity>
  struct has_value
  {
    template<class x>
    using f = typename continuation
      ::template f<typename detail::_has_value<x>::type>;
  };

  template<class predicate, class continuation = identity>
  using is_invocable_predicate = if_<is_invocable<predicate>, demux<predicate, has_value<continuation>>>;

  namespace eager
  {
    template<class x>
    using identity = x;

    template<class predicate, class true_continuation, class false_continuation, class... xs>
    using if_ = typename mp::conditional_c<predicate::template f<xs...>::value>
      ::template f<true_continuation, false_continuation>
      ::template f<xs...>;

    template</*TODO DOXY: class function, */class... xs>
    using is_invocable = decltype(detail::_is_invocable(static_cast<xs*>(nullptr)...));
  }

  template<class continuation>
  using when_continuation = typename detail::_when_continuation<continuation>::type;

  template<class predicate, class continuation>
  struct when;

  namespace smp
  {
    using identity = when<mp::is_invocable<mp::identity>, mp::identity>;

    template<class x, class continuation = identity>
    using always = when<mp::always<true_>, mp::always<x, when_continuation<continuation>>>;

    template<class predicate, class true_continuation, class false_continuation>
    using if_ = when<
      mp::is_invocable_predicate<predicate>,
      mp::if_<predicate,
        when_continuation<true_continuation>,
        when_continuation<false_continuation>>>;

    template<class function, class continuation = identity>
    using is_invocable = when<mp::is_invocable<function>, when_continuation<continuation>>;

    template<template<class...> class function, class continuation = identity>
    using cfl = when<
      mp::if_<mp::is_invocable<mp::cfe<function>>, mp::is_invocable<mp::cfl<function>>, mp::always<false_>>,
      mp::cfl<function, when_continuation<continuation>>>;

    template<template<class...> class function, class continuation = identity>
    using cfe = when<mp::is_invocable<mp::cfe<function>>, mp::cfe<function, when_continuation<continuation>>>;
  }

  struct unsatisfactory_concept_error;
  using unsatisfactory_concept = always<unsatisfactory_concept_error>;

  template<class predicate, class continuation>
  struct when
  {
    template<class... xs>
    using f = typename mp::conditional_c<predicate::template f<xs...>::value>
      ::template f<continuation, unsatisfactory_concept>
      ::template f<xs...>
      ::template f<>;
  };
}


#include "../config/enumerate.hpp"

namespace jln::mp::detail
{
  template<class predicate, class continuation>
  struct _when;

  // TODO _when_impl<c> = demux<c, cfe<always>>
  template<class function>
  struct _when_impl
  {
    template<class... xs>
    using f = always<typename function::template f<xs...>>;
  };

  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, when<xs...>>
  {
    using type = when<xs...>;
  };

  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, _when<xs...>>
  {
    using type = _when<xs...>;
  };

  template<template<class> class sfinae>
  struct _sfinae<sfinae, identity>
  {
    using type = smp::identity;
  };

  template<template<class> class sfinae>
  struct _sfinae<sfinae, listify>
  {
    using type = when<always<true_>, _when_impl<listify>>;
  };

  template<template<class> class sfinae, template<class...> class function, class continuation>
  struct _sfinae<sfinae, cfl<function, continuation>>
  {
    using type = smp::cfl<function, sfinae<continuation>>;
  };

  template<template<class> class sfinae, template<class...> class function, class continuation>
  struct _sfinae<sfinae, cfe<function, continuation>>
  {
    using type = smp::cfe<function, sfinae<continuation>>;
  };


  template<class predicate, class continuation>
  struct _when
  {
    template<class... xs>
    using f = typename mp::conditional_c<predicate::template f<xs...>::value>
      ::template f<continuation, unsatisfactory_concept>
      ::template f<xs...>;
  };

  // TODO _when_capture_n<1, identity>
  struct _when_identity
  {
    template<class... xs>
    struct impl
    {
      using type = unsatisfactory_concept;
    };

    template<class x>
    struct impl<x>
    {
      using type = always<x>;
    };

    template<class... xs>
    using f = typename impl<xs...>::type;
  };

  template<class function>
  struct _when_continuation
  {
    using type = if_<is_invocable<function>, _when_impl<function>, unsatisfactory_concept>;
  };

  template<>
  struct _when_continuation<identity>
  {
    using type = _when_identity;
  };

  template<>
  struct _when_continuation<listify>
  {
    using type = _when_impl<listify>;
  };

  template<class predicate, class continuation>
  struct _when_continuation<when<predicate, continuation>>
  {
    using type = _when<predicate, continuation>;
  };

  template<class continuation>
  struct _when_continuation<when<always<true_>, continuation>>
  {
    using type = _when_impl<continuation>;
  };


  template<class x, class>
  struct _has_value
  {
    using type = false_;
  };

  template<class x>
  struct _has_value<x, std::void_t<decltype(x::value)>>
  {
    using type = true_;
  };

  template <class continuation, class... functions>
  struct _demux
  {
      template <class... xs>
      using f = typename continuation::template f<
        typename functions::template f<xs...>...>;
  };

  template <>
  struct _rotate<0>
  {
    template<unsigned size, class continuation, class... xs>
    using f = typename continuation::template f<xs...>;
  };

#define JLN_MP_ROTATE_IMPL(n, mp_xs)             \
  template<>                                     \
  struct _rotate<n>                              \
  {                                              \
    template<unsigned size, class continuation,  \
      mp_xs(class, JLN_MP_NIL), class... xs>     \
    using f = typename continuation::template f< \
      xs..., mp_xs(JLN_MP_NIL, JLN_MP_NIL)>;     \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_ROTATE_IMPL)

#undef JLN_MP_ROTATE_IMPL

#define JLN_MP_ROTATE_IMPL(n, mp_xs)                               \
  template<>                                                       \
  struct _rotate<n>                                                \
  {                                                                \
    template<unsigned size, class continuation,                    \
      mp_xs(class, JLN_MP_NIL), class... xs>                       \
    using f = typename _rotate<_rotate_step(size-n)>::template f<  \
      size-n, continuation, xs..., mp_xs(JLN_MP_NIL, JLN_MP_NIL)>; \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_ROTATE_IMPL)

#undef JLN_MP_ROTATE_IMPL

} // namespace jln::mp
