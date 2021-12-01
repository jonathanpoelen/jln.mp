#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/number/number.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct _group_n;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a sequence by arbitrary size group.
  /// \post If `n <= 0`, then the result sequence is empty
  /// \semantics
  ///   \code
  ///   group_n<number<2>>::f<
  ///     void, void, int, void, void
  ///   > = list<
  ///     list<void, void>,
  ///     list<int, void>,
  ///     list<void>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class n, class C = listify>
  struct group_n
  {
    template<class... xs>
    using f = typename detail::_group_n<sizeof...(xs) != 0 && (n::value > 0)>
      ::template f<C, n::value, xs...>;
  };

  template<int_ n, class C = listify>
  using group_n_c = group_n<number<n>, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using group_n = unpack<L, mp::group_n<n, C>>;

    template<class L, int_ n, class C = mp::listify>
    using group_n_c = unpack<L, mp::group_n_c<n, C>>;
  }
}


#include <jln/mp/algorithm/split.hpp>
#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/list/pop_front.hpp>

/// \cond
namespace jln::mp::detail
{
  template<int_... i>
  struct _group_n_impl
  {
    template<class C, unsigned long long n, class... xs>
    using f = typename fold_right<lift_t<split_state>, unpack<pop_front<C>>>
      ::template f<
        list<list<>>,
        list<number<(i % n ? split_keep : split_before)>, xs>...
      >;
  };

  template<>
  struct _group_n<true>
  {
    template<class C, unsigned long long n, class... xs>
    using f = typename emp::make_int_sequence_v_c<
      sizeof...(xs), lift_c<_group_n_impl>
    >::template f<C, n, xs...>;
  };

  template<>
  struct _group_n<false>
  {
    template<class C, unsigned long long, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };
}
/// \endcond
