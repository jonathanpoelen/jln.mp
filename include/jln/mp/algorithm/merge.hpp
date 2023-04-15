#pragma once

#include <jln/mp/number/operators.hpp>

#include <type_traits>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class L, class Seq1, class Seq2, class Cmp>
    struct merge_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Merges two \list into one sorted \sequence.
  /// \pre `emp::is_sorted<seq1, Cmp>`
  /// \pre `emp::is_sorted<seq2, Cmp>`
  /// \post \c emp::is_sorted<result...>
  /// \treturn \sequence
  template<class Cmp = less<>, class C = listify>
  struct merge
  {
    template<class seq1, class seq2>
    using f = typename detail::_unpack<
      C,
      typename detail::merge_impl<
        list<>, seq1, seq2, JLN_MP_TRACE_F(Cmp)
      >::type
    >::type;
  };

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = listify>
    using merge = unpack<L, mp::merge<Cmp, C>>;
  }
}


/// \cond
namespace jln::mp
{
  template<class Cmp>
  struct merge<Cmp, listify>
  {
    template<class seq1, class seq2>
    using f = typename detail::merge_impl<
      list<>, seq1, seq2, JLN_MP_TRACE_F(Cmp)
    >::type;
  };
}

namespace jln::mp::detail
{
  template <bool, class L, class Seq1, class Seq2, class Cmp>
  struct merge_insert;

  template <class... R, class T0, class T1, class... Ts, class U, class... Us, class Cmp>
  struct merge_insert<false, list<R...>, list<T0, T1, Ts...>, list<U, Us...>, Cmp>
  : merge_insert<Cmp::template f<U, T1>::value,
                 list<R..., T0>, list<T1, Ts...>, list<U, Us...>, Cmp>
  {};

  template <class... R, class T, class U, class... Us, class Cmp>
  struct merge_insert<false, list<R...>, list<T>, list<U, Us...>, Cmp>
  {
    template<class... xs> using out   = list<xs..., R..., T>;
    template<class... xs> using left  = list<xs...>;
    template<class... xs> using right = list<U, Us..., xs...>;
  };

  template <class... R, class T, class... Ts, class U0, class U1, class... Us, class Cmp>
  struct merge_insert<true, list<R...>, list<T, Ts...>, list<U0, U1, Us...>, Cmp>
  : merge_insert<Cmp::template f<U1, T>::value,
                 list<R..., U0>, list<T, Ts...>, list<U1, Us...>, Cmp>
  {};

  template <class... R, class T, class... Ts, class U, class Cmp>
  struct merge_insert<true, list<R...>, list<T, Ts...>, list<U>, Cmp>
  {
    template<class... xs> using out   = list<xs..., R..., U>;
    template<class... xs> using left  = list<T, Ts..., xs...>;
    template<class... xs> using right = list<xs...>;
  };

  template <class... R, class T0, class T1, class T2, class T3, class T4, class T5,
            class T6, class T7, class T8, class T9, class... Ts, class U0, class U1,
            class U2, class U3, class U4, class U5, class U6, class U7, class U8,
            class U9, class... Us, class Cmp>
  struct merge_impl<list<R...>, list<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, Ts...>,
                    list<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9, Us...>, Cmp>
  {
    using sub = merge_insert<Cmp::template f<U0, T0>::value, list<>,
                             list<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>,
                             list<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>, Cmp>;
    using type = typename merge_impl<typename sub::template out<R...>,
                                     typename sub::template left<Ts...>,
                                     typename sub::template right<Us...>,
                                     Cmp>::type;
  };

  template <class... R, class T, class... Ts, class U, class... Us, class Cmp>
  struct merge_impl<list<R...>, list<T, Ts...>, list<U, Us...>, Cmp>
  : conditional_c<Cmp::template f<U, T>::value>::template f<
      merge_impl<list<R..., U>, list<T, Ts...>, list<Us...>, Cmp>,
      merge_impl<list<R..., T>, list<Ts...>, list<U, Us...>, Cmp>
    >
  {};

  template <class... R, class... Ts, class Cmp>
  struct merge_impl<list<R...>, list<Ts...>, list<>, Cmp>
  {
    using type = list<R..., Ts...>;
  };

  template <class... R, class... Us, class Cmp>
  struct merge_impl<list<R...>, list<>, list<Us...>, Cmp>
  {
    using type = list<R..., Us...>;
  };

  template <class... R, class Cmp>
  struct merge_impl<list<R...>, list<>, list<>, Cmp>
  {
    using type = list<R...>;
  };
}
/// \endcond
