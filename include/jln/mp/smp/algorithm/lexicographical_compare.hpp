#pragma once

#include "mismatch.hpp"
#include "../../functional/monadic.hpp"
#include "../../algorithm/lexicographical_compare.hpp"

/// \cond
namespace jln::mp::detail
{
  template<class Cmp, class C>
  struct _smp_lexicographical_compare;

  template<class CmpLess, class CmpEq, class C>
  struct _smp_lexicographical_compare2;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = identity>
  using lexicographical_compare = try_contract<detail::_smp_lexicographical_compare<
    assume_binary<Cmp>, assume_positive_number<C>>>;

  template<class CmpLess = less<>, class CmpEq = equal<>, class C = identity>
  using lexicographical_compare2 = try_contract<detail::_smp_lexicographical_compare2<
    assume_binary<CmpLess>, assume_binary<CmpEq>, assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, lexicographical_compare<Cmp, C>>
  {
    using type = smp::lexicographical_compare<sfinae<Cmp>, sfinae<C>>;
  };

  template<template<class> class sfinae, class CmpLess, class CmpEq, class C>
  struct _sfinae<sfinae, lexicographical_compare2<CmpLess, CmpEq, C>>
  {
    using type = smp::lexicographical_compare2<sfinae<CmpLess>, sfinae<CmpEq>, sfinae<C>>;
  };

  template<class Cmp, class C>
  struct _smp_lexicographical_compare
  {
    template<class seq1, class seq2>
    using f = typename monadic<C>::template f<
      typename mismatch<
        _lexicographical_compare_equal<
          smp::concepts::predicate<Cmp, mp::identity, mp::always<true_>>
        >,
        lift<_lexicographical_compare>
      >
      ::template f<seq1, seq2>
      ::template f<smp::concepts::predicate<Cmp, mp::identity, violation>, seq1, seq2>
    >;
  };

  template<class Cmp>
  struct _smp_lexicographical_compare<Cmp, identity>
  {
    template<class seq1, class seq2>
    using f = typename mismatch<
      _lexicographical_compare_equal<
        smp::concepts::predicate<Cmp, mp::identity, mp::always<true_>>
      >,
      lift<_lexicographical_compare>
    >
    ::template f<seq1, seq2>
    ::template f<smp::concepts::predicate<Cmp, mp::identity, violation>, seq1, seq2>;
  };

  template<class CmpLess, class CmpEq, class C>
  struct _smp_lexicographical_compare2
  {
    template<class seq1, class seq2>
    using f = typename monadic<C>::template f<
      typename mismatch<
        smp::concepts::predicate<CmpEq, mp::identity, mp::always<false_>>,
        lift<_lexicographical_compare>
      >
      ::template f<seq1, seq2>
      ::template f<
        if_<
          smp::concepts::predicate<CmpEq, always<true_>, always<false_>>,
          CmpLess,
          violation
        >,
        seq1, seq2
      >
    >;
  };

  template<class CmpLess, class CmpEq>
  struct _smp_lexicographical_compare2<CmpLess, CmpEq, identity>
  {
    template<class seq1, class seq2>
    using f = typename mismatch<
      smp::concepts::predicate<CmpEq, mp::identity, mp::always<false_>>,
      lift<_lexicographical_compare>
    >
    ::template f<seq1, seq2>
    ::template f<
      if_<
        smp::concepts::predicate<CmpEq, always<true_>, always<false_>>,
        CmpLess,
        violation
      >,
      seq1, seq2
    >;
  };
}
/// \endcond
