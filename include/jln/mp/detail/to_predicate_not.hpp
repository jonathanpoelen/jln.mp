#pragma once

#include <jln/mp/list/push_back.hpp>
#include <jln/mp/list/push_front.hpp>
#include <jln/mp/algorithm/same.hpp>
#include <jln/mp/utility/is.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/number/operators.hpp>

#include <type_traits>

namespace jln::mp::detail
{
  template<class Pred>
  struct to_predicate_not;

  template<class Pred>
  using to_predicate_not_t = typename to_predicate_not<Pred>::type;

  template<class x>
  struct to_predicate_not<is<x>>
  {
    using type = is<x, not_<>>;
  };

  template<class x>
  struct to_predicate_not<is<x, not_<>>>
  {
    using type = is<x>;
  };

  template<>
  struct to_predicate_not<same<>>
  {
    using type = same<not_<>>;
  };

  template<>
  struct to_predicate_not<same<not_<>>>
  {
    using type = same<>;
  };

  template<>
  struct to_predicate_not<lift<std::is_same>>
  {
    using type = lift<std::is_same, not_<>>;
  };

  template<>
  struct to_predicate_not<lift<std::is_same, not_<>>>
  {
    using type = lift<std::is_same>;
  };

  template<template<class...> class F>
  struct to_predicate_not<lift<F>>
  {
    using type = lift<F, not_<>>;
  };

  template<template<class...> class F>
  struct to_predicate_not<lift<F, not_<>>>
  {
    using type = lift<F>;
  };

  template<template<class...> class F>
  struct to_predicate_not<tee<lift<F>, not_<>>>
  {
    using type = lift<F>;
  };

  template<>
  struct to_predicate_not<not_<>>
  {
    using type = identity;
  };

  template<>
  struct to_predicate_not<identity>
  {
    using type = not_<>;
  };

  template<>
  struct to_predicate_not<not_<not_<>>>
  {
    using type = not_<>;
  };

  template<class C>
  struct to_predicate_not<not_<not_<not_<C>>>>
  : to_predicate_not<not_<C>>
  {};

  template<class x, class C>
  struct to_predicate_not<push_front<x, C>>
  {
    using type = push_front<x, to_predicate_not_t<C>>;
  };

  template<class x, class C>
  struct to_predicate_not<push_back<x, C>>
  {
    using type = push_back<x, to_predicate_not_t<C>>;
  };

  template<class Pred>
  struct to_predicate_not_tee;

  template<class Pred>
  struct to_predicate_not_tee<tee<Pred, not_<>>>
  {
    using type = Pred;
  };

  template<class Pred>
  struct to_predicate_not_tee
  : to_predicate_not<Pred>
  {};

  template<class Pred>
  struct to_predicate_not<tee<Pred, not_<>>>
  : to_predicate_not_tee<to_predicate_not_t<Pred>>
  {};

  template<class Pred>
  struct to_predicate_not
  {
    using type = tee<Pred, not_<>>;
  };
}
