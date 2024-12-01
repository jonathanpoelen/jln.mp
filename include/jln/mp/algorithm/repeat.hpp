// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<std::size_t ns, unsigned N, class C>
    struct repeat_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Returns a \sequence that contains a \number of copies of the same \sequence.
  /// \pre `N >= 0`
  /// \treturn \sequence
  template<unsigned N, class C = listify>
  struct repeat_c
  {
    template<class... xs>
    using f = typename detail::repeat_impl<sizeof...(xs), N, C>
      ::template f<xs...>::type;
  };

  template<class N, class C = listify>
  using repeat = repeat_c<N::value, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using repeat = typename detail::_unpack<mp::repeat<n, C>, L>::type;

    template<class L, int_t n, class C = mp::listify>
    using repeat_c = typename detail::_unpack<mp::repeat_c<n, C>, L>::type;
  }
}


#include <jln/mp/list/lookup.hpp> // index0
#include <jln/mp/functional/capture_front.hpp>
#include <jln/mp/algorithm/make_int_sequence.hpp>

/// \cond
namespace jln::mp
{
  template<class C>
  struct repeat_c<0, C>
    : detail::call_trace_xs_0<C>
  {};

  template<class C>
  struct repeat_c<1, C>
    : detail::call_trace_xs<C>
  {};
}

namespace jln::mp::detail
{
  template<class T>
  struct repeat_impl_0
  {
    using type = T;
    template<class...> using f = repeat_impl_0;
  };

  template<unsigned N, class C>
  struct repeat_impl<0, N, C>
    : repeat_impl_0<typename C::template f<>>
  {};

  template<unsigned N>
  struct repeat_impl<0, N, listify>
    : repeat_impl_0<list<>>
  {};


#if JLN_MP_CUDA && JLN_MP_HOST_COMPILER_GCC
  template<class x, class> using emp_index0 = x;
#  define JLN_MP_INDEX0 emp_index0
#else
#  define JLN_MP_INDEX0 detail::index0::f
#endif

#if JLN_MP_MSVC || JLN_MP_GCC
# if JLN_MP_MSVC
  template<class C, class x, class... xs>
  using repeat_impl_1 = typename C::template f<JLN_MP_INDEX0<x, xs>...>;
# endif

  template<class C>
  struct repeat_impl_1_cont
  {
    template<class, int... ns>
    struct impl
    {
      template<class x>
      struct f
      {
# if JLN_MP_MSVC
        using type = repeat_impl_1<C, x, decltype(ns)...>;
# else
        using type = typename C::template f<JLN_MP_INDEX0<x, decltype(ns)>...>;
# endif
      };
    };
  };

  template<unsigned N>
  struct repeat_impl<1, N, listify>
    : JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, N, repeat_impl_1_cont<listify>::impl)
  {};

  template<unsigned N, class C>
  struct repeat_impl<1, N, C>
    : JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, N, repeat_impl_1_cont<C>::template impl)
  {};
#else // ^^^ JLN_MP_MSVC || JLN_MP_GCC
  template<class, int... ns>
  struct repeat_impl_1_list
  {
    template<class x>
    struct f
    {
      using type = list<JLN_MP_INDEX0<x, decltype(ns)>...>;
    };
  };

  template<unsigned N>
  struct repeat_impl<1, N, listify>
    : JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, N, repeat_impl_1_list)
  {};

  template<class, int... ns>
  struct repeat_impl_1_cont
  {
    template<class x>
    struct duplicate : capture_front<JLN_MP_INDEX0<x, decltype(ns)>...>
    {};
  };

  template<unsigned N, class C>
  struct repeat_impl<1, N, C>
  {
    using impl = JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, N, repeat_impl_1_cont);

    template<class x>
    struct f
    {
      using type = typename impl::template duplicate<x>::template f<C>;
    };
  };
#endif


  template<bool, class L, class L2>
  struct rep_seq;

  template<class... xs, class L2>
  struct rep_seq<false, list<xs...>, L2>
  {
    using type = list<xs..., xs...>;
  };

  template<class... xs, class... ys>
  struct rep_seq<true, list<xs...>, list<ys...>>
  {
    using type = list<ys..., xs..., xs...>;
  };

  template<unsigned n, class L>
  struct mk_seq
  : rep_seq<n & 1, typename mk_seq<n / 2, L>::type, L>
  {};

  template<class... xs>
  struct mk_seq<2, list<xs...>>
  {
    using type = list<xs..., xs...>;
  };

  template<class L> struct mk_seq<1, L> { using type = L; };
  // template<class L> struct mk_seq<0, L> { using type = list<>; };

  template<std::size_t ns, unsigned N>
  struct repeat_impl<ns, N, listify>
  {
    template<class... xs>
    using f = mk_seq<N, list<xs...>>;
  };


  template<class C, bool, class L, class L2>
  struct rep_seq2;

  template<class C, class... xs, class L2>
  struct rep_seq2<C, false, list<xs...>, L2>
  {
    using type = typename C::template f<xs..., xs...>;
  };

  template<class C, class... xs, class... ys>
  struct rep_seq2<C, true, list<xs...>, list<ys...>>
  {
    using type = typename C::template f<ys..., xs..., xs...>;
  };

  template<class C, unsigned n, class L>
  struct mk_seq2
  : rep_seq2<C, n & 1, typename mk_seq<n / 2, L>::type, L>
  {};

  template<class C, class... xs>
  struct mk_seq2<C, 2, list<xs...>>
  {
    using type = typename C::template f<xs..., xs...>;
  };

  template<class C, class... xs>
  struct mk_seq2<C, 1, list<xs...>>
  {
    using type = typename C::template f<xs...>;
  };

  // template<class C, class L>
  // struct mk_seq2<C, 0, L> : repeat_impl_0<typename C::template f<>>
  // {};

  template<std::size_t ns, unsigned N, class C>
  struct repeat_impl
  {
    template<class... xs>
    using f = mk_seq2<C, N, list<xs...>>;
  };

#undef JLN_MP_INDEX0
}
/// \endcond
