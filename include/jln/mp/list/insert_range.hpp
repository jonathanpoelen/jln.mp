#pragma once

#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/functional/bind_front.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct insert_range_index;

    template<int_ index, class C, class... xs>
    using insert_range_impl = rotate_c<index, bind_front<rotate_c<-index, C>, xs...>>;
  }
  /// \endcond

  /// \ingroup list

  /// Inserts all elements of \c seq at an arbitrary position.
  /// A negative value represents an index starting from the end.
  /// \pre seq must be a \list
  /// \treturn \sequence
  template<int_ index, class seq, class C = listify>
  struct insert_range_c
  {};

  template<int_ index, class... xs, class C>
  struct insert_range_c<index, list<xs...>, C>
  {
    template<class... ys>
    using f = typename detail::insert_range_impl<
      detail::insert_range_index<index < 0>::template index<index, sizeof...(ys)>, C, xs...
    >::template f<ys...>;
  };

  /// \cond
  template<class... xs, class C>
  struct insert_range_c<0, list<xs...>, C> : bind_front<C, xs...>
  {};
  /// \endcond

  template<class index, class seq, class C = listify>
  using insert_range = insert_range_c<index::value, seq, C>;

  namespace emp
  {
    template<class L, class index, class seq, class C = mp::listify>
    using insert_range = unpack<L, mp::insert_range<index, seq, C>>;

    template<class L, int_ index, class seq, class C = mp::listify>
    using insert_range_c = unpack<L, mp::insert_range_c<index, seq, C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<>
  struct insert_range_index<true>
  {
    template<int_ i, int_ n>
    static constexpr int_ index = -i < n ? n+i : 0;
  };

  template<>
  struct insert_range_index<false>
  {
    template<int_ i, int_ n>
    static constexpr int_ index = i < n ? i : n;
  };
}
/// \endcond
