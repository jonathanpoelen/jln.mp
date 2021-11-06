#pragma once

#include <jln/mp/functional/lift.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/list/wrap_in_list.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct _remove_unique;

    template<class Cmp, class C>
    struct mk_remove_unique;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Remove unique elements from a \sequence.
  /// \treturn \sequence
  /// \see remove_unique_if
  template<class C = listify>
  struct remove_unique
  {
    template<class... xs>
    using f = typename detail::_remove_unique<sizeof...(xs) < 2>::template f<C, xs...>;
  };

  /// Remove unique elements from a \sequence.
  /// \treturn \sequence
  /// \see remove_unique
  template<class Cmp = lift<std::is_same>, class C = listify>
  using remove_unique_if = typename detail::mk_remove_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using remove_unique = unpack<L, remove_unique<C>>;

    template<class L, class Cmp = lift<std::is_same>, class C = mp::listify>
    using remove_unique_if = unpack<L, remove_unique_if<Cmp, C>>;
  }
}


#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/algorithm/unique.hpp> // inherit / inherit_item
#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/list/join.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class From, class To>
  auto wrap_in_list_if_convertible(From, To)
    -> decltype(To(From()), wrap_in_list_c<false>());

  wrap_in_list_c<true> wrap_in_list_if_convertible(...);

  template<class C, class Inherit, class... xs>
  using remove_unique_impl = typename join<C>::template f<typename
    decltype(wrap_in_list_if_convertible(
      static_cast<Inherit*>(nullptr),
      static_cast<detail::inherit_item<xs>*>(nullptr)
    ))
    ::template f<xs>
  ...>;

  template<>
  struct _remove_unique<false>
  {
    template<class C, class... xs>
    using f = remove_unique_impl<
      C, detail::inherit<std::make_index_sequence<sizeof...(xs)>, xs...>, xs...
    >;
  };

  template<>
  struct _remove_unique<true>
  {
    template<class C, class... xs>
    using f = typename C::template f<>;
  };

  template<class Indexes>
  struct remove_unique_if_impl;

  template<std::size_t... ints>
  struct remove_unique_if_impl<std::integer_sequence<std::size_t, ints...>>
  {
    template<class C, class Cmp, class... xs>
    using f = typename join<C>::template f<
      typename rotate_c<ints, pop_front<index_if<
        push_back<xs, Cmp>,
        always<wrap_in_list_c<true>>,
        always<wrap_in_list_c<false>>
      >>>
      ::template f<xs...>
      ::template f<xs>...
    >;
  };

  template<>
  struct remove_unique_if_impl<std::integer_sequence<std::size_t>>
  {
    template<class C, class Cmp, class... xs>
    using f = typename C::template f<>;
  };

  template<std::size_t i>
  struct remove_unique_if_impl<std::integer_sequence<std::size_t, i>>
  {
    template<class C, class Cmp, class... xs>
    using f = typename C::template f<>;
  };

  template<class Cmp, class C>
  struct _remove_unique_if
  {
    template<class... xs>
    using f = typename detail::remove_unique_if_impl<std::make_index_sequence<sizeof...(xs)>>
      ::template f<C, Cmp, xs...>;
  };

  template<class Cmp, class C>
  struct mk_remove_unique
  {
    using type = _remove_unique_if<Cmp, C>;
  };

  template<class C>
  struct mk_remove_unique<lift<std::is_same>, C>
  {
    using type = mp::remove_unique<C>;
  };

  template<class C>
  struct mk_remove_unique<lift_t<std::is_same>, C>
  {
    using type = mp::remove_unique<C>;
  };

  template<class C>
  struct mk_remove_unique<same<>, C>
  {
    using type = mp::remove_unique<C>;
  };
}
/// \endcond
