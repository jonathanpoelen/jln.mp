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
  template<int_ n, class C = listify>
  struct group_n_c
  {
    template<class... xs>
    using f = typename detail::_group_n<sizeof...(xs) != 0 && 0 < n>
      ::template f<C, n, xs...>;
  };

  template<class n, class C = listify>
  using group_n = group_n_c<n::value, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using group_n = unpack<L, mp::group_n<n, C>>;

    template<class L, int_ n, class C = mp::listify>
    using group_n_c = unpack<L, mp::group_n_c<n, C>>;
  }
}


#include <jln/mp/algorithm/split.hpp>
#include <jln/mp/list/pop_front.hpp>
#include <utility>

/// \cond
namespace jln::mp::detail
{
  template<class>
  struct _group_n_impl;

  template<std::size_t... i>
  struct _group_n_impl<std::integer_sequence<std::size_t, i...>>
  {
    template<class C, std::size_t n, class... xs>
    using f = typename fold_right<lift<split_state_t>, unpack<pop_front<C>>>
      ::template f<
        list<list<>>,
        list<number<(i % n ? split_keep : split_before)>, xs>...
      >;
  };

  template<>
  struct _group_n<true>
  {
    template<class C, int_ n, class... xs>
    using f = typename _group_n_impl<std::make_index_sequence<sizeof...(xs)>>
      ::template f<C, n, xs...>;
  };

  template<>
  struct _group_n<false>
  {
    template<class C, int_, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };
}
/// \endcond
