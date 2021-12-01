#pragma once

#include <jln/mp/smp/list/at.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/algorithm/mismatch.hpp>
#include <jln/mp/smp/concepts.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Cmp, class C, class NC>
  struct _smp_mismatch;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Cmp = equal<>, class C = listify, class NC = C>
  using mismatch = try_contract<detail::_smp_mismatch<
    assume_binary<Cmp>, assume_numbers<C>, assume_numbers<NC>>>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C, class NC>
  struct _sfinae<sfinae, mismatch<Cmp, C, NC>>
  {
    using type = smp::mismatch<sfinae<Cmp>, sfinae<C>, sfinae<NC>>;
  };

  template<class C>
  struct _smp_mismatch_check
  {
    template<class i, class direction, class = void>
    struct f
    {
      template<class Cmp, class seq1, class seq2>
      using impl = typename C::template f<i, direction>;
    };

    template<class i>
    struct f<i, number<0>, std::enable_if_t<(i::value != -1)>>
    {
      template<class Cmp, class seq1, class seq2>
      using impl = typename conditional<
        typename smp::concepts::predicate<Cmp, mp::always<true_>>
        ::template f<emp::at<seq1, i>, emp::at<seq2, i>>
      >::template f<C, violation>
      ::template f<i, number<0>>;
    };
  };

  template<class Cmp, class C, class NC>
  struct _smp_mismatch
  {
    template<class seq1, class seq2>
    using f = typename mismatch<
      smp::concepts::predicate<Cmp>,
      _smp_mismatch_check<C>,
      _smp_mismatch_check<NC>
    >
    ::template f<seq1, seq2>
    ::template impl<Cmp, seq1, seq2>;
  };
}
/// \endcond
