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
    using f = call<typename mp::conditional_c<call<predicate, xs...>::value>
      ::template f<true_continuation, false_continuation>,
      xs...>;
  };

  template<class function, class continuation = identity>
  struct is_invocable
  {
    template<class... xs>
    using f = typename continuation::template f<decltype(detail::_is_invocable(static_cast<function*>(nullptr), static_cast<xs*>(nullptr)...))>;
  };

  namespace detail
  {
    template<bool>
    struct dcallf;

    template<>
    struct dcallf<true>
    {
        template<template<class...> class F, typename...xs>
        using f = F<xs...>;
    };
  }

  template<template<class...> class function, class continuation = identity>
  struct cfl
  {
    template<class... xs>
    using f = call<
      continuation,
      typename detail::dcallf<sizeof...(xs) < 1000000>
        ::template f<function, xs...>::type>;
  };

  template<template<class...> class function, class continuation = identity>
  struct cfe
  {
    template<class... xs>
    using f = call<
      continuation,
      typename detail::dcallf<sizeof...(xs) < 1000000>
        ::template f<function, xs...>>;
  };

  template<class... vals>
  class list {};

  using listify = cfe<list>;

  template<class continuation = identity>
  struct size
  {
    template<class... xs>
    using f = typename continuation::template f<number<sizeof...(xs)>>;
  };

  template<class continuation = identity>
  struct has_value
  {
    template<class x>
    using f = typename continuation
      ::template f<typename detail::_has_value<x>::type>;
  };

  namespace eager
  {
    template<class x>
    using identity = x;

    template<class predicate, class true_continuation, class false_continuation, class... xs>
    using if_ = typename mp::conditional_c<predicate::template f<xs...>::value>
      ::template f<true_continuation, false_continuation>
      ::template f<xs...>;

    template<class function, class... xs>
    using is_invocable = mp::call<mp::is_invocable<function>, xs...>;
  }

  template<class continuation>
  using when_continuation = typename detail::_when_continuation<continuation>::type;

  template<class predicate, class continuation>
  struct when;

  // TODO move to mp, eager, smp
  //@{
  template <class T, class C = identity>
  struct same_as
  {
    template <class x>
    using f = typename C::template f<number<std::is_same<T, x>::value>>;
  };

  template<class N, class C = identity>
  using size_of = size<same_as<N>>;

  template<class C = identity>
  using size_of_1 = size_of<number<1>, identity>;

  template<class C = identity>
  using size_of_2 = size_of<number<2>, identity>;
  //@}

  template<class Pred, class C = identity>
  using is_invocable_predicate = mp::if_<
      mp::is_invocable<Pred>,
      mp::detail::_demux<has_value<C>, Pred>,
      always<false_, C>>;

  namespace smp
  {
    using identity = when<mp::size_of_1<>, mp::identity>;
    using listify = when<mp::always<true_>, mp::listify>;

    // template<class Pred, class C = identity>
    // using is_invocable_predicate = sfinae<mp::is_invocable_predicate<Pred, C>>;

    template<class x, class C = identity>
    using always = typename detail::_demux<
      mp::cfe<mp::when>,
      mp::identity,
      if_<
        mp::identity,
        detail::_demux<C, mp::always<x>>,
        mp::always<void>
      >
    >::template f<
      typename mp::is_invocable<when_continuation<C>>::template f<x>
    >;

    template<class predicate, class true_continuation, class false_continuation>
    using if_ = when<
      mp::is_invocable_predicate<when_continuation<predicate>>,
      mp::if_<predicate,
        when_continuation<true_continuation>,
        when_continuation<false_continuation>>>;

    template<class function, class continuation = identity>
    using is_invocable = when<
      mp::is_invocable<function>,
      when_continuation<continuation>>;

    template<template<class...> class function, class continuation = identity>
    using cfl = when<
      mp::if_<mp::is_invocable<mp::cfe<function>>, mp::is_invocable<mp::cfl<function>>, mp::always<false_>>,
      mp::cfl<function, when_continuation<continuation>>>;

    template<template<class...> class function, class continuation = identity>
    using cfe = when<
      mp::is_invocable<mp::cfe<function>>,
      mp::cfe<function, when_continuation<continuation>>>;

    template<class continuation = identity>
    using size = when<
      mp::always<true_>,
      mp::size<when_continuation<continuation>>>;

    template<class continuation = identity>
    using same_as = when<
      mp::size_of_1<>,
      mp::same_as<when_continuation<continuation>>>;

    template<class C = identity>
    using has_value = when<
      mp::size_of_1<>,
      mp::has_value<when_continuation<C>>>;
  }

  struct unsatisfactory_concept_error;
  using unsatisfactory_concept = always<unsatisfactory_concept_error>;

  template<class predicate, class continuation>
  struct when
  {
    template<class... xs>
    using f = typename if_<
      same_as<unsatisfactory_concept_error>
    , cfl<unsatisfactory_concept::template f>
    , identity
    >::template f<
      typename conditional<call<predicate, xs...>>
      ::template f<continuation, unsatisfactory_concept>
      ::template f<xs...>
    >;
  };

  template<class WP, class WC, class C>
  struct is_invocable<when<WP, WC>, C>
  {
    template<class... xs>
    using f = typename C::template f<number<!std::is_same<
      typename mp::conditional<call<WP, xs...>>
      ::template f<WC, unsatisfactory_concept>
      ::template f<xs...>
    , unsatisfactory_concept_error
    >::value>>;
  };
}


#include "../config/enumerate.hpp"

namespace jln::mp::detail
{
  template<class predicate, class continuation>
  struct _when;

  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, when<xs...>>
  {
    using type = when<xs...>;
  };

  // template<template<class> class sfinae, class... xs>
  // struct _sfinae<sfinae, _when<xs...>>
  // {
  //   using type = _when<xs...>;
  // };

  template<template<class> class sfinae>
  struct _sfinae<sfinae, identity>
  {
    using type = smp::identity;
  };

  template<template<class> class sfinae>
  struct _sfinae<sfinae, listify>
  {
    using type = smp::listify;
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

  template<template<class> class sfinae, class continuation>
  struct _sfinae<sfinae, size<continuation>>
  {
    using type = smp::size<sfinae<continuation>>;
  };

  template<template<class> class sfinae, class continuation>
  struct _sfinae<sfinae, same_as<continuation>>
  {
    using type = smp::same_as<sfinae<continuation>>;
  };


  template<class predicate, class continuation>
  struct _when
  {
    template<class... xs>
    using f = mp::call<
      typename mp::conditional<mp::call<predicate, xs...>>
      ::template f<continuation, unsatisfactory_concept>
    , xs...>;
  };

  // for reduce recursivity
  // TODO when_continuation_for_unary
  // TODO when_continuation_for_binary
  // TODO when_continuation_for_list

  template<class function>
  struct _when_continuation
  {
    // TODO _when_continuation<sfinae<function>> or
    using type = _when<is_invocable<function>, function>;
  };

  template<class predicate, class continuation>
  struct _when_continuation<when<predicate, continuation>>
  {
    using type = _when<predicate, continuation>;
  };

  template<class continuation>
  struct _when_continuation<when<always<true_>, continuation>>
  {
    using type = continuation;
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
} // namespace jln::mp
