#pragma once

#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_ n>
    struct repat_impl;
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
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(
      N,
      detail::repat_impl<sizeof...(xs) < 2 ? sizeof...(xs) : 2>::template impl
    )::template f<C, xs...>;
  };

  template<class N, class C = listify>
  using repeat = repeat_c<N::value, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using repeat = unpack<L, mp::repeat<n, C>>;

    template<class L, int_ n, class C = mp::listify>
    using repeat_c = unpack<L, mp::repeat_c<n, C>>;
  }
}


#include <jln/mp/list/join.hpp>
#include <jln/mp/functional/memoize.hpp> // _first

/// \cond
namespace jln::mp::detail
{
  template<>
  struct repat_impl<0>
  {
    template<class, int_...>
    struct impl
    {
      template<class C>
      using f = JLN_MP_CALL_TRACE_0_ARG(C);
    };
  };

  template<>
  struct repat_impl<1>
  {
    template<class, int_... ns>
    struct impl
    {
      template<class C, class x>
      using f = JLN_MP_CALL_TRACE(C, _first<x, decltype(ns)>...);
    };
  };

  template<>
  struct repat_impl<2>
  {
    template<class, int_... ns>
    struct impl
    {
      template<class C, class... xs>
      using f = typename join<C>::template f<_first<list<xs...>, decltype(ns)>...>;
    };
  };
}

namespace jln::mp
{
  template<class C>
  struct repeat_c<0, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS_0(xs, C);
  };

  template<class C>
  struct repeat_c<1, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };
}
/// \endcond
