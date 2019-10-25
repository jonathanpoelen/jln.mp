#pragma once

#include "../number/number.hpp"
#include "call.hpp"

#include <type_traits>

// mp::sfinae / mp::sfinae_once
// TODO mp::unsafe_sfinae / mp::unsafe_sfinae_once ? for sfinae<F> without specialization on F
namespace jln::mp
{
  namespace detail
  {
    template<template<class> class sfinae, class x>
    struct _sfinae;

    template<class x> struct _recursive_sfinae_impl;
    template<class x> struct _sfinae_once_impl;

    template<class x>
    using _recursive_sfinae = typename _recursive_sfinae_impl<x>::type;

    template<class x>
    using _sfinae_once = typename _sfinae_once_impl<x>::type;
  }

  template<class x>
  using sfinae = typename detail::_sfinae<detail::_recursive_sfinae, x>::type;

  template<class x>
  using sfinae_once = typename detail::_sfinae<detail::_sfinae_once, x>::type;
}


namespace jln::mp
{
  namespace detail
  {
    template<class C>
    struct _when_continuation;

    template<class function, class... xs, class = std::void_t<typename function::template f<xs...>>>
    true_ _is_invocable(function*, xs*...);
    false_ _is_invocable(...);

    template <class C, class... Fs>
    struct _demux;

    template<bool>
    struct dcallf;

    template<>
    struct dcallf<true>
    {
        template<template<class...> class F, typename...xs>
        using f = F<xs...>;
    };

    template<class x, class = void>
    struct _has_value;

    template <unsigned n>
    struct _rotate;

    // TODO n_8_or_less_16_64_256
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

    // TODO compatibility with negative n ?
    constexpr unsigned _rotate_size(unsigned n, unsigned size) {
      return n >= size ? (size == 0 ? 0 : n % size) : n;
    }

    template <typename C, typename L, typename... Ts>
    struct _unpack;
  }

  struct identity
  {
    template<class x>
    using f = x;
  };

  template<class x, class C = identity>
  struct always
  {
    template<class... xs>
    using f = typename C::template f<x>;
  };

  template<bool>
  struct conditional_c
  {
    template<class x, class y>
    using f = x;
  };

  template<>
  struct conditional_c<false>
  {
    template<class x, class y>
    using f = y;
  };

  template<class v>
  using conditional = conditional_c<bool(v::value)>;

  template<class Pred, class TC, class FC = always<false_>>
  struct if_
  {
    template<class... xs>
    using f = typename mp::conditional_c<bool(call<Pred, xs...>::value)>
      ::template f<TC, FC>
      ::template f<xs...>;
  };

  // TODO is_callable
  template<class F, class C = identity>
  struct is_invocable
  {
    template<class... xs>
    using f = typename C::template f<decltype(detail::_is_invocable(
      static_cast<F*>(nullptr),
      static_cast<xs*>(nullptr)...
    ))>;
  };

  template<template<class...> class F, class C = identity>
  struct cfl
  {
    template<class... xs>
    using f = call<
      C,
      typename detail::dcallf<sizeof...(xs) < 1000000>
        ::template f<F, xs...>::type>;
  };

  template<template<class...> class F>
  struct cfl<F, identity>
  {
    template<class... xs>
    using f = typename detail::dcallf<sizeof...(xs) < 1000000>
      ::template f<F, xs...>::type;
  };

  template<template<class...> class F, class C = identity>
  struct cfe
  {
    template<class... xs>
    using f = call<
      C,
      typename detail::dcallf<sizeof...(xs) < 1000000>
        ::template f<F, xs...>>;
  };

  template<template<class...> class F>
  struct cfe<F, identity>
  {
    template<class... xs>
    using f = typename detail::dcallf<sizeof...(xs) < 1000000>
      ::template f<F, xs...>;
  };

  template<class C>
  struct unpack
  {
    template<class... Ls>
    using f = typename detail::_unpack<C, Ls...>::type;
  };

  template<class L, class C>
  using eager = mp::call<mp::unpack<C>, L>;

  // TODO size<identity> = demux<size<>, C> ?
  template<class C = identity>
  struct size
  {
    template<class... xs>
    using f = typename C::template f<number<sizeof...(xs)>>;
  };

  template<class... xs>
  class list {};

  using listify = cfe<list>;

  template<class C = identity>
  struct has_value
  {
    // TODO xs...
    template<class x>
    using f = typename C::template f<
      typename detail::_has_value<x>::type>;
  };

  template <class n, class C = listify>
  struct rotate
  {
    template<class... xs>
    using f = typename detail::_rotate<
      detail::_rotate_step(
        detail::_rotate_size(n::value, sizeof...(xs)))
    >::template f<
      detail::_rotate_size(n::value, sizeof...(xs)),
      C, xs...>;
  };

  template <int_ n, class C = listify>
  using rotate_c = rotate<number<n>, C>;

  // TODO DOXY template<class... F, class C>
  template <class... Fs>
  struct demux
  : rotate<number<sizeof...(Fs)-1>, cfe<detail::_demux>>
  ::template f<Fs...>
  {};

  template <class F, class C>
  struct demux<F, C>
  {
    template<class... xs>
    using f = typename C::template f<mp::call<F, xs...>>;
  };

  template <class F0, class F1, class C>
  struct demux<F0, F1, C>
  {
    template<class... xs>
    using f = typename C::template f<
      mp::call<F0, xs...>,
      mp::call<F1, xs...>
    >;
  };

  template <class T, class C = identity>
  struct same_as
  {
    // TODO xs... ?
    template <class x>
    using f = typename C::template f<number<std::is_same<T, x>::value>>;
  };

  namespace emp
  {
    template<class x>
    using identity = x;

    template<class v, class x, class y>
    using conditional = typename mp::conditional_c<bool(v::value)>
      ::template f<x, y>;

    template<bool cond, class x, class y>
    using conditional_c = typename mp::conditional_c<cond>
      ::template f<x, y>;

    template<class Pred, class TC, class FC, class... xs>
    using if_ = typename conditional<call<Pred, xs...>, TC, FC>
      ::template f<xs...>;

    template<bool cond, class TC, class FC, class... xs>
    using if_c = typename conditional_c<cond, TC, FC>
      ::template f<xs...>;

    template<class F, class... xs>
    using is_invocable = mp::call<mp::is_invocable<F>, xs...>;

    template<class F, class... xs>
    inline constexpr bool is_invocable_v
      = mp::call<mp::is_invocable<F>, xs...>::value;

    template<template<class...> class F, class... xs>
    using cfl = mp::call<mp::cfl<F>, xs...>;

    template<template<class...> class F, class... xs>
    using cfe = mp::call<mp::cfe<F>, xs...>;

    template<class L>
    using size = typename mp::unpack<mp::size<>>::f<L>;

    template<class L>
    inline constexpr bool size_v
      = mp::unpack<mp::size<>>::f<L>::value;

    template<class x>
    using has_value = typename detail::_has_value<x>::type;

    template<class x>
    inline constexpr bool has_value_v
      = detail::_has_value<x>::type::value;

    template <class n, class... xs>
    using rotate = mp::call<mp::rotate<n>, xs...>;

    template <int_ n, class... xs>
    using rotate_c = mp::call<mp::rotate<number<n>>, xs...>;
  }

  template<class C>
  using when_continuation = typename detail::_when_continuation<C>::type;

  template<class Pred, class C>
  struct when;

  // TODO move to mp, emp, smp
  //@{

  // TODO is_size_of*
  template<class N, class C = identity>
  using size_of = size<same_as<N, C>>;

  template<class C = identity>
  using size_of_1 = size_of<number<1>, C>;

  template<class C = identity>
  using size_of_2 = size_of<number<2>, C>;
  //@}

  template<class Pred, class C = identity>
  using is_invocable_predicate = mp::if_<
    mp::is_invocable<when_continuation<Pred>>,
    mp::demux<Pred, has_value<C>>,
    always<false_, C>>;

  namespace detail
  {
    template<class C, class... Fs>
    using _smp_demux = mp::when<
      mp::demux<
        mp::is_invocable<Fs>...,
        if_<
          mp::identity,
          mp::demux<Fs..., mp::is_invocable<sfinae<C>>>,
          mp::always<false_>
        >
      >,
      mp::demux<Fs..., when_continuation<C>>
    >;
  }

  // TODO na
  struct unsatisfactory_concept_error;
  using unsatisfactory_concept = always<unsatisfactory_concept_error>;

  template<class F, class TC = identity, class FC = unsatisfactory_concept>
  struct try_invoke;

  template<class F, class TC, class FC = unsatisfactory_concept>
  using when_try_invoke = when<
    mp::always<mp::true_>,
    try_invoke<when_continuation<F>, TC, FC>
  >;

  namespace smp
  {
    using identity = when<mp::size_of_1<>, mp::identity>;
    using listify = when<mp::always<true_>, mp::listify>;

    template<class x, class C = identity>
    // using always = typename mp::demux<
    //   mp::cfe<mp::always>,
    //   if_<
    //     mp::identity,
    //     mp::demux<mp::always<x>, mp::demux<C, mp::cfe<mp::always>>>,
    //     mp::always<void>
    //   >,
    //   mp::cfe<mp::when>
    // >::template f<
    //   typename mp::is_invocable<when_continuation<C>>::template f<x>
    // >;
    using always = mp::when<
      mp::is_invocable<sfinae<C>>,
      mp::always<x, when_continuation<C>>>;

    template<class v>
    using conditional = when<mp::size_of_2<>, mp::conditional<v>>;

    template<class Pred, class TC, class FC>
    /*when<
      mp::is_invocable_predicate<Pred>,
      mp::if_<Pred,
        when_continuation<TC>,
        when_continuation<FC>>>*/
    using if_ = when_try_invoke<
      Pred,
      mp::if_<
        mp::has_value<>,
        mp::if_<
          mp::identity,
          when_continuation<TC>,
          when_continuation<FC>
        >,
        mp::unsatisfactory_concept
      >
    >;

    template<class F, class C = identity>
    using is_invocable = when<
      mp::always<true_>,
      when_continuation<C>>;

    template<template<class...> class F, class C = identity>
    using cfl = when<
      // TODO and_
      mp::if_<
        mp::is_invocable<mp::cfe<F>>,
        mp::is_invocable<mp::cfl<F>>,
        mp::always<false_>>,
      mp::cfl<F, when_continuation<C>>>;

    template<template<class...> class F, class C = identity>
    using cfe = when<
      mp::is_invocable<mp::cfe<F>>,
      mp::cfe<F, when_continuation<C>>>;

    template<class C = identity>
    using size = when<
      mp::always<true_>,
      mp::size<when_continuation<C>>>;

    template<class C>
    using unpack = mp::when<
      mp::size<>,
      mp::unpack<when_continuation<C>>>;

    template<class C = identity>
    using has_value = when<
      mp::size_of_1<>,
      mp::has_value<when_continuation<C>>>;

    template <class n, class C = listify>
    using rotate = mp::when<
      mp::always<true_>,
      mp::rotate<when_continuation<C>>>;

    template <int_ n, class C = listify>
    using rotate_c = mp::rotate<number<n>, C>;

    template <class... Fs>
    using demux = typename mp::rotate<
      mp::number<sizeof...(Fs)-1>,
      mp::cfe<detail::_smp_demux>
    >::template f<Fs...>;

    template<class C = identity>
    using same_as = when<
      mp::size_of_1<>,
      mp::same_as<when_continuation<C>>>;
  }

  template<class Pred, class C>
  struct when
  {
    template<class... xs>
    using f = typename if_<
      same_as<unsatisfactory_concept_error>
    , cfl<unsatisfactory_concept::template f>
    , identity
    >::template f<
      typename conditional<call<Pred, xs...>>
      ::template f<C, unsatisfactory_concept>
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

  template<class Pred, class C, class TC, class FC>
  struct try_invoke<when<Pred, C>, TC, FC>
  {
    template<class... xs>
    using f = typename conditional<call<Pred, xs...>>
      ::template f<demux<C, TC>, FC>
      ::template f<xs...>;
  };

  namespace detail
  {
    template<class F, class... xs>
    typename F::template f<xs...> _try_invoke(F*, xs*...);

    unsatisfactory_concept_error _try_invoke(...);
  }

  // TODO rename or rename ^^^
  template<class F, class TC, class FC>
  struct try_invoke
  {
    template<class... xs>
    using f = typename if_<
      same_as<unsatisfactory_concept_error>
    , FC
    , TC
    >::template f<decltype(detail::_try_invoke(
      static_cast<F*>(nullptr),
      static_cast<xs*>(nullptr)...
    ))>;
  };
}


#include "../config/enumerate.hpp"

namespace jln::mp::detail
{
  template<class x>
  struct _recursive_sfinae_impl
  {
    using type = typename _sfinae<_recursive_sfinae, x>::type;
  };

  template<class x>
  struct _sfinae_once_impl
  {
    using type = typename _sfinae<emp::identity, x>::type;
  };

  template<class Pred, class C>
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

  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, if_<Pred, TC, FC>>
  {
    using type = smp::if_<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, class T, class C>
  struct _sfinae<sfinae, always<T, C>>
  {
    using type = smp::always<T, sfinae<C>>;
  };

  template<template<class> class sfinae, template<class...> class F, class C>
  struct _sfinae<sfinae, cfl<F, C>>
  {
    using type = smp::cfl<F, sfinae<C>>;
  };

  template<template<class> class sfinae, template<class...> class F, class C>
  struct _sfinae<sfinae, cfe<F, C>>
  {
    using type = smp::cfe<F, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, size<C>>
  {
    using type = smp::size<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, same_as<C>>
  {
    using type = smp::same_as<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unpack<C>>
  {
    using type = smp::unpack<sfinae<C>>;
  };


  template<class Pred, class C>
  struct _when
  {
    template<class... xs>
    using f = mp::call<
      typename mp::conditional_c<mp::call<Pred, xs...>::value>
      ::template f<C, unsatisfactory_concept>
    , xs...>;
  };

  // for reduce recursivity
  // TODO when_continuation_for_unary
  // TODO when_continuation_for_binary
  // TODO when_continuation_for_list

  template<class F>
  struct _when_continuation
  {
    // TODO _when_continuation<sfinae<F>> or
    using type = _when<is_invocable<F>, F>;
  };

  template<class Pred, class C>
  struct _when_continuation<when<Pred, C>>
  {
    using type = _when<Pred, C>;
  };

  template<class C>
  struct _when_continuation<when<always<true_>, C>>
  {
    using type = C;
  };

  template<class C, template<class...> class Seq, class... Ts, class... xs>
  struct _unpack<C, Seq<Ts...>, xs...>
  {
      using type = typename C::template f<xs..., Ts...>;
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

  template <class C, class... Fs>
  struct _demux
  {
    template <class... xs>
    using f = typename C::template f<
      typename Fs::template f<xs...>...>;
  };
  template <>
  struct _rotate<0>
  {
    template<unsigned size, class continuation, class... xs>
    using f = typename continuation::template f<xs...>;
  };

#define JLN_MP_ROTATE_IMPL(n, mp_xs, _)          \
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

#define JLN_MP_ROTATE_IMPL(n, mp_xs, _)                            \
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
