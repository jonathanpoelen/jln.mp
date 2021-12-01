#pragma once

#include <jln/mp/algorithm/mismatch.hpp>
#include <jln/mp/functional/lift.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class, class>
    struct _lexicographical_compare;

    template<class Cmp>
    struct _lexicographical_compare_equal;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks if \c seq1  is lexicographically less than \c seq2.
  /// \treturn \bool
  template<class Cmp = less<>, class C = identity>
  struct lexicographical_compare
  {
    template<class seq1, class seq2>
    using f = JLN_MP_CALL_TRACE((C),
      typename mismatch<
        detail::_lexicographical_compare_equal<JLN_MP_TRACE_F(Cmp)>,
        lift<detail::_lexicographical_compare>
      >
      ::template f<seq1, seq2>
      ::template f<JLN_MP_TRACE_F(Cmp), seq1, seq2>
    );
  };

  template<class CmpLess = less<>, class CmpEq = equal<>, class C = identity>
  struct lexicographical_compare2
  {
    template<class seq1, class seq2>
    using f = JLN_MP_CALL_TRACE((C),
      typename mismatch<JLN_MP_TRACE_F(CmpEq), lift<detail::_lexicographical_compare>>
      ::template f<seq1, seq2>
      ::template f<JLN_MP_TRACE_F(CmpLess), seq1, seq2>
    );
  };

  namespace emp
  {
    template<class seq1, class seq2, class Cmp = mp::less<>, class C = mp::identity>
    using lexicographical_compare = typename lexicographical_compare<Cmp, C>
      ::template f<seq1, seq2>;

    template<
      class seq1, class seq2,
      class CmpLess = mp::less<>, class CmpEq = mp::equal<>, class C = mp::identity>
    using lexicographical_compare2 = typename lexicographical_compare2<CmpLess, CmpEq, C>
      ::template f<seq1, seq2>;
  }

  /// \cond
  template<class Cmp>
  struct lexicographical_compare<Cmp, identity>
  {
    template<class seq1, class seq2>
    using f = typename mismatch<
      detail::_lexicographical_compare_equal<Cmp>,
      lift<detail::_lexicographical_compare>
    >
    ::template f<seq1, seq2>
    ::template f<Cmp, seq1, seq2>;
  };

  template<class CmpLess, class CmpEq>
  struct lexicographical_compare2<CmpLess, CmpEq, identity>
  {
    template<class seq1, class seq2>
    using f = typename mismatch<CmpEq, lift<detail::_lexicographical_compare>>
      ::template f<seq1, seq2>
      ::template f<CmpLess, seq1, seq2>;
  };
  /// \endcond
}


#include <jln/mp/list/at.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct _lexicographical_compare_equal
  {
    template<class x, class y>
    using f = number<!Cmp::template f<x, y>::value && !Cmp::template f<y, x>::value>;
  };

  template<class i, class n>
  struct _lexicographical_compare
  {
    template<class Cmp, class seq1, class seq2>
    using f = false_;
  };

  template<>
  struct _lexicographical_compare<number<-1>, number<0>>
  {
    template<class Cmp, class seq1, class seq2>
    using f = false_;
  };

  template<class i>
  struct _lexicographical_compare<i, number<0>>
  {
    template<class Cmp, class seq1, class seq2>
    using f = typename Cmp::template f<emp::at<seq1, i>, emp::at<seq2, i>>;
  };

  template<class i>
  struct _lexicographical_compare<i, number<-1>>
  {
    template<class Cmp, class seq1, class seq2>
    using f = true_;
  };
}
/// \endcond
