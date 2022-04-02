#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/size.hpp>
#include <jln/mp/smp/list/clear.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/algorithm/search.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/functional/invoke_twice.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Pred, class TC>
  using _smp_search_tc =
    mp::if_<
      mp::if_<
        mp::size<>,
        smp::concepts::predicate<assume_unary_or_more<Pred>>,
        mp::always<mp::true_>
      >,
      mp::subcontract<TC>,
      mp::violation
    >;

  template<class Pred>
  using _smp_search_pred = smp::concepts::predicate<
    assume_unary_or_more<Pred>, mp::identity, mp::always<true_>>;

  template<class TC>
  struct _smp_search_before_take_front;

  template<class StopWhenAtLeast, class = void>
  struct _smp_partial_search;

  template<class StopWhenAtLeast, class = void>
  struct _smp_partial_search_before;

  template<class ExtendedByN, class = void>
  struct _smp_search_before_extended_by_n;

  template<class StopWhenAtLeast, class ExtendedByN, class = void>
  struct _smp_partial_search_extended_by_n;

  template<class TC>
  struct _smp_search_to_index;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using search = contract<mp::search<
    detail::_smp_search_pred<Pred>,
    detail::_smp_search_tc<Pred, TC>,
    subcontract<FC>
  >>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using search_before = contract<mp::invoke_twice<
    mp::search<
      detail::_smp_search_pred<Pred>,
      mp::if_<
        concepts::predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
        detail::_smp_search_before_take_front<subcontract<TC>>,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;

  template<class Pred, class ExtendedByN, class TC = listify, class FC = clear<TC>>
  using search_before_extended_by_n = typename detail::_smp_search_before_extended_by_n<ExtendedByN>
    ::template f<Pred, TC, FC>;

  template<class StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search = typename detail::_smp_partial_search<StopWhenAtLeast>
    ::template f<Pred, TC, FC>;

  template<class StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_before = typename detail::_smp_partial_search_before<StopWhenAtLeast>
    ::template f<Pred, TC, FC>;

  template<class StopWhenAtLeast, class Pred, class ExtendedByN,
           class TC = listify, class FC = clear<TC>>
  using partial_search_before_extended_by_n
    = typename detail::_smp_partial_search_extended_by_n<StopWhenAtLeast, ExtendedByN>
    ::template f<Pred, TC, FC>;

  template<int_ StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_c = contract<mp::partial_search_c<
    StopWhenAtLeast,
    detail::_smp_search_pred<Pred>,
    detail::_smp_search_tc<Pred, TC>,
    subcontract<FC>
  >>;

  template<int_ StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_before_c = contract<mp::invoke_twice<
    mp::partial_search_c<
      StopWhenAtLeast,
      detail::_smp_search_pred<Pred>,
      mp::if_<
        smp::concepts::predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
        detail::_smp_search_before_take_front<subcontract<TC>>,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;

  template<int_ StopWhenAtLeast, class Pred, class ExtendedByN,
           class TC = listify, class FC = clear<TC>>
  using partial_search_before_extended_by_n_c =
    typename detail::_smp_partial_search_extended_by_n<
      number<StopWhenAtLeast>, ExtendedByN>
    ::template f<Pred, TC, FC>;
}

/// \cond
namespace jln::mp::detail
{
  template<class TC>
  struct _smp_search_before_take_front
  {
    template<std::size_t n>
    struct take
    {
      template<class... xs>
      using f = typename mp::take_front_c<sizeof...(xs) - n, TC>
        ::template f<xs...>;
    };

    template<class... xs>
    using f = take<sizeof...(xs)>;
  };

  template<class TC, class ExtendedByN>
  struct _smp_search_before_extended_by_n_take_front
  {
    template<std::size_t n>
    struct take
    {
      template<class... xs>
      using f = typename mp::take_front_c<
        extended_by_n(sizeof...(xs), n, ExtendedByN::value), TC
      >::template f<xs...>;
    };

    template<class... xs>
    using f = take<sizeof...(xs)>;
  };

  template<class StopWhenAtLeast, class>
  struct _smp_partial_search
  {
    template<class Pred, class TC, class FC>
    using f = bad_contract;
  };

  template<class StopWhenAtLeast>
  struct _smp_partial_search<StopWhenAtLeast, std::void_t<number<int_{StopWhenAtLeast::value}>>>
  {
    template<class Pred, class TC, class FC>
    using f = contract<mp::partial_search_c<
      StopWhenAtLeast::value,
      _smp_search_pred<Pred>,
      _smp_search_tc<Pred, TC>,
      subcontract<FC>
    >>;
  };

  template<class StopWhenAtLeast, class>
  struct _smp_partial_search_before
  {
    template<class Pred, class TC, class FC>
    using f = bad_contract;
  };

  template<class StopWhenAtLeast>
  struct _smp_partial_search_before<
    StopWhenAtLeast,
    std::void_t<number<int_{StopWhenAtLeast::value}>>>
  {
    template<class Pred, class TC, class FC>
    using f = contract<mp::invoke_twice<
      mp::partial_search_c<
        StopWhenAtLeast::value,
        detail::_smp_search_pred<Pred>,
        mp::if_<
          smp::concepts::predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
          detail::_smp_search_before_take_front<subcontract<TC>>,
          mp::always<violation>
        >,
        mp::always<subcontract<FC>>
      >
    >>;
  };

  template<class ExtendedByN, class>
  struct _smp_search_before_extended_by_n
  {
    template<class Pred, class TC, class FC>
    using f = bad_contract;
  };

  template<class ExtendedByN>
  struct _smp_search_before_extended_by_n<
    ExtendedByN, std::void_t<number<int_{ExtendedByN::value}>>>
  {
    template<class Pred, class TC, class FC>
    using f = contract<mp::invoke_twice<
      mp::search<
        detail::_smp_search_pred<Pred>,
        mp::if_<
          smp::concepts::predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
          detail::_smp_search_before_extended_by_n_take_front<
            subcontract<TC>, number<ExtendedByN::value>
          >,
          mp::always<violation>
        >,
        mp::always<subcontract<FC>>
      >
    >>;
  };

  template<class StopWhenAtLeast, class ExtendedByN, class>
  struct _smp_partial_search_extended_by_n
  {
    template<class Pred, class TC, class FC>
    using f = bad_contract;
  };

  template<class StopWhenAtLeast, class ExtendedByN>
  struct _smp_partial_search_extended_by_n<
    StopWhenAtLeast, ExtendedByN,
    std::void_t<number<int_{StopWhenAtLeast::value} || int_{ExtendedByN::value}>>>
  {
    template<class Pred, class TC, class FC>
    using f = contract<mp::invoke_twice<
      mp::partial_search_c<
        StopWhenAtLeast::value,
        detail::_smp_search_pred<Pred>,
        mp::if_<
          smp::concepts::predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
          detail::_smp_search_before_extended_by_n_take_front<
            subcontract<TC>, number<ExtendedByN::value>
          >,
          mp::always<violation>
        >,
        mp::always<subcontract<FC>>
      >
    >>;
  };


  template<class TC>
  struct _smp_search_to_index
  {
    template<std::size_t n>
    struct to_index
    {
      template<class... xs>
      using f = JLN_MP_DCALL_TRACE_XS(xs, TC, number<sizeof...(xs) - n>);
    };

    template<class... xs>
    using f = to_index<sizeof...(xs)>;
  };


  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, search<Pred, TC, FC>>
  {
    using type = smp::search<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, search_before<Pred, TC, FC>>
  {
    using type = smp::search_before<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, class Pred,
    class ExtendedByN, class TC, class FC>
  struct _sfinae<sfinae, search_before_extended_by_n<Pred, ExtendedByN, TC, FC>>
  {
    using type = smp::search_before_extended_by_n<
      sfinae<Pred>, ExtendedByN, sfinae<TC>, sfinae<FC>>;
  };


  template<template<class> class sfinae, int_ StopWhenAtLeast,
    class Pred, class TC, class FC>
  struct _sfinae<sfinae, partial_search_c<StopWhenAtLeast, Pred, TC, FC>>
  {
    using type = smp::partial_search_c<
      StopWhenAtLeast, sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, int_ StopWhenAtLeast,
    class Pred, class TC, class FC>
  struct _sfinae<sfinae, partial_search_before_c<StopWhenAtLeast, Pred, TC, FC>>
  {
    using type = smp::partial_search_before_c<
      StopWhenAtLeast, sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, int_ StopWhenAtLeast,
    class Pred, class ExtendedByN, class TC, class FC>
  struct _sfinae<sfinae, partial_search_before_extended_by_n_c<
    StopWhenAtLeast, Pred, ExtendedByN, TC, FC>>
  {
    using type = smp::partial_search_before_extended_by_n_c<
      StopWhenAtLeast, sfinae<Pred>, ExtendedByN, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
