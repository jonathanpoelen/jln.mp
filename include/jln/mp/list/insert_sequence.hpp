// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/functional/bind_front.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct insert_sequence_index;

    template<int_t index, class C, class... xs>
    using insert_sequence_impl = rotate_c<index, bind_front<rotate_c<-index, C>, xs...>>;
  }
  /// \endcond

  /// \ingroup list

  /// Inserts all elements of \c seq at an arbitrary position.
  /// A negative value represents an index starting from the end.
  /// \treturn \sequence
  template<int_t index, class seq, class C = listify>
  struct insert_sequence_c
  {};

  template<int_t index, template<class...> class List, class... xs, class C>
  struct insert_sequence_c<index, List<xs...>, C>
  {
    template<class... ys>
    using f = typename detail::insert_sequence_impl<
      detail::insert_sequence_index<index < 0>::template index<index, sizeof...(ys)>, C, xs...
    >::template f<ys...>;
  };

  /// \cond
  template<class... xs, template<class...> class List, class C>
  struct insert_sequence_c<0, List<xs...>, C> : bind_front<C, xs...>
  {};
  /// \endcond

  template<class index, class seq, class C = listify>
  using insert_sequence = insert_sequence_c<index::value, seq, C>;

  namespace emp
  {
    template<class L, class index, class seq, class C = mp::listify>
    using insert_sequence = typename detail::_unpack<mp::insert_sequence<index, seq, C>, L>::type;

    template<class L, int_t index, class seq, class C = mp::listify>
    using insert_sequence_c = typename detail::_unpack<mp::insert_sequence_c<index, seq, C>, L>::type;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<>
  struct insert_sequence_index<true>
  {
    template<int_t i, int_t n>
    static constexpr int_t index = -i < n ? n+i : 0;
  };

  template<>
  struct insert_sequence_index<false>
  {
    template<int_t i, int_t n>
    static constexpr int_t index = i < n ? i : n;
  };
}
/// \endcond
