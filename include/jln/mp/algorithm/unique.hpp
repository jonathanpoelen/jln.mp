#pragma once

#include <jln/mp/functional/lift.hpp>
#include <jln/mp/utility/unpack.hpp>

#include <type_traits>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class Cmp, class C>
    struct mk_unique;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Returns a list of the same form as L with the duplicate elements removed.
  /// Only the first element found is kept.
  /// \treturn \sequence
  template<class C = listify>
  using unique = typename detail::mk_unique<lift<std::is_same>, C>::type;

  /// Returns a list of the same form as L with the duplicate elements removed.
  /// Only the first element found is kept.
  /// \treturn \sequence
  template<class Cmp = lift<std::is_same>, class C = listify>
  using unique_if = typename detail::mk_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using unique = unpack<L, unique<C>>;

    template<class L, class Cmp = lift<std::is_same>, class C = mp::listify>
    using unique_if = unpack<L, unique_if<Cmp, C>>;
  }
}


#include <jln/mp/algorithm/same.hpp>
#include <jln/mp/algorithm/fold_left.hpp>
#include <jln/mp/algorithm/index.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/list/size.hpp>

#include <utility> // std::integer_sequence

/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct inherit_item {};
  template<std::size_t i, class x>
  struct inherit_impl : inherit_item<x> {};

  template<class, class...>
  struct inherit;

  template<std::size_t... ints, class... xs>
  struct inherit<std::integer_sequence<std::size_t, ints...>, xs...>
    : inherit_impl<ints, xs>...
  {};

  template<class... xs>
  struct inherit2 : inherit_item<xs>...
  {};

#if JLN_MP_MSVC_LIKE
  template<class... xs>
  struct _is_set
  {
      template <class Pack>
      static auto is_set(Pack pack) -> decltype((
          static_cast<inherit_item<xs>*>(pack),...
      ), number<1>());

      static number<0> is_set(...);

      using type = decltype(is_set(static_cast<
        inherit<std::make_index_sequence<sizeof...(xs)>, xs...>*
      >(nullptr)));
  };
#endif

  template<class L, class x, bool = false>
  struct _set_push_back
  {
    using type = L;
  };

  template<class... xs, class x>
  struct _set_push_back<list<xs...>, x,
#if JLN_MP_CLANG_LIKE || JLN_MP_GCC || JLN_MP_MSVC_LIKE
      __is_base_of(inherit_item<x>, inherit2<xs...>)
#else
      std::is_base_of<inherit_item<x>, inherit2<xs...>>::value
#endif
  >
  {
    using type = list<xs..., x>;
  };

  template<class Cmp>
  struct _set_cmp_push_back
  {
    template<class x, class... xs>
    using f = typename conditional_c<
      index_if<push_back<x, Cmp>, identity, always<number<-1>>>::template f<xs...>::value == -1
    >::template f<list<xs..., x>, list<xs...>>;
  };

  template<class Cmp, class C>
  struct mk_unique
  {
    using type = push_front<list<>, fold_left<
      unpack<_set_cmp_push_back<JLN_MP_TRACE_F(Cmp)>>,
      optimize_useless_unpack_t<unpack<C>>
    >>;
  };

  template<class x, class y>
  using set_push_back_t = typename _set_push_back<x, y>::type;

  template<class C>
  struct mk_unique<lift<std::is_same>, C>
  {
    using type = push_front<list<>, fold_left<
      lift<set_push_back_t>,
      optimize_useless_unpack_t<unpack<C>>
    >>;
  };

  template<class C>
  struct mk_unique<lift_t<std::is_same>, C>
  : mk_unique<lift<std::is_same>, C>
  {};

  template<class C>
  struct mk_unique<same<>, C>
  : mk_unique<lift<std::is_same>, C>
  {};
}
/// \endcond
