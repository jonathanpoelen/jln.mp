#pragma once

#include <jln/mp/functional/lift.hpp>
#include <jln/mp/utility/unpack.hpp>

#include <type_traits>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct _remove_unique;

    template<bool>
    struct _copy_unique;

    template<class Cmp, class C>
    struct mk_remove_unique;

    template<class Cmp, class C>
    struct mk_copy_unique;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Remove unique elements from a \sequence.
  /// \treturn \sequence
  /// \see remove_unique_if, copy_unique, copy_unique_if
  template<class C = listify>
  struct remove_unique
  {
    template<class... xs>
    using f = typename detail::_remove_unique<sizeof...(xs) < 2>::template f<C, xs...>;
  };

  /// Remove unique elements from a \sequence.
  /// \treturn \sequence
  /// \see remove_unique, copy_unique, copy_unique_if
  template<class Cmp = lift<std::is_same>, class C = listify>
  using remove_unique_if = typename detail::mk_remove_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using remove_unique = unpack<L, remove_unique<C>>;

    template<class L, class Cmp = lift<std::is_same>, class C = mp::listify>
    using remove_unique_if = unpack<L, remove_unique_if<Cmp, C>>;
  }

  /// Copy unique elements from a \sequence.
  /// \treturn \sequence
  /// \see copy_unique_if, remove_unique, remove_unique_if
  template<class C = listify>
  struct copy_unique
  {
    template<class... xs>
    using f = typename detail::_copy_unique<sizeof...(xs) < 2>::template f<C, xs...>;
  };

  /// Copy unique elements from a \sequence.
  /// \treturn \sequence
  /// \see copy_unique, remove_unique, remove_unique_if
  template<class Cmp = lift<std::is_same>, class C = listify>
  using copy_unique_if = typename detail::mk_copy_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using copy_unique = unpack<L, copy_unique<C>>;

    template<class L, class Cmp = lift<std::is_same>, class C = mp::listify>
    using copy_unique_if = unpack<L, copy_unique_if<Cmp, C>>;
  }
}


#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/algorithm/unique.hpp> // inherit / inherit_item
#include <jln/mp/list/join.hpp>
#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/list/wrap_in_list.hpp>

#include <jln/mp/utility/is_not.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class From, class To>
  constexpr auto is_convertible_to(From, To)
    -> decltype(To(From()), true)
  {
    return true;
  }

  constexpr bool is_convertible_to(...)
  {
    return false;
  }


  template<class C, class Inherit, class... xs>
  using remove_unique_impl = typename join<C>::template f<
    typename wrap_in_list_c<!is_convertible_to(
      static_cast<Inherit*>(nullptr),
      static_cast<detail::inherit_item<xs>*>(nullptr)
    )>
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
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };


  template<class C, class Inherit, class... xs>
  using copy_unique_impl = typename join<C>::template f<
    typename wrap_in_list_c<is_convertible_to(
      static_cast<Inherit*>(nullptr),
      static_cast<detail::inherit_item<xs>*>(nullptr)
    )>
    ::template f<xs>
  ...>;

  template<>
  struct _copy_unique<false>
  {
    template<class C, class... xs>
    using f = copy_unique_impl<
      C, detail::inherit<std::make_index_sequence<sizeof...(xs)>, xs...>, xs...
    >;
  };

  template<>
  struct _copy_unique<true>
  {
    template<class C, class... xs>
    using f = JLN_MP_CALL_TRACE(C, xs...);
  };


  template<class Indexes>
  struct remove_unique_if_impl;

  template<std::size_t... ints>
  struct remove_unique_if_impl<std::integer_sequence<std::size_t, ints...>>
  {
    template<class C, class Cmp, class... xs>
    using f = typename join<C>::template f<
      JLN_MP_MSVC_FIX_CALL((
        rotate_c<ints, pop_front<index_if<
          push_back<xs, Cmp>,
          always<wrap_in_list_c<true>>,
          always<wrap_in_list_c<false>>
        >>>
        ::template f<xs...>
      ), xs)...
    >;
  };

  template<>
  struct remove_unique_if_impl<std::integer_sequence<std::size_t>>
  {
    template<class C, class Cmp, class... xs>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  template<std::size_t i>
  struct remove_unique_if_impl<std::integer_sequence<std::size_t, i>>
  : remove_unique_if_impl<std::integer_sequence<std::size_t>>
  {};

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


  template<class Indexes>
  struct copy_unique_if_impl;

  template<std::size_t... ints>
  struct copy_unique_if_impl<std::integer_sequence<std::size_t, ints...>>
  {
    template<class C, class Cmp, class... xs>
    using f = typename join<C>::template f<
      JLN_MP_MSVC_FIX_CALL((
        rotate_c<ints, pop_front<index_if<
          push_back<xs, Cmp>,
          always<wrap_in_list_c<false>>,
          always<wrap_in_list_c<true>>
        >>>
        ::template f<xs...>
      ), xs)...
    >;
  };

  template<>
  struct copy_unique_if_impl<std::integer_sequence<std::size_t>>
  : remove_unique_if_impl<std::integer_sequence<std::size_t>>
  {};

  template<std::size_t i>
  struct copy_unique_if_impl<std::integer_sequence<std::size_t, i>>
  {
    template<class C, class Cmp, class... xs>
    using f = JLN_MP_CALL_TRACE(C, xs...);
  };

  template<class Cmp, class C>
  struct _copy_unique_if
  {
    template<class... xs>
    using f = typename detail::copy_unique_if_impl<std::make_index_sequence<sizeof...(xs)>>
      ::template f<C, Cmp, xs...>;
  };

  template<class Cmp, class C>
  struct mk_copy_unique
  {
    using type = _copy_unique_if<Cmp, C>;
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

  template<class C>
  struct mk_remove_unique<lift<std::is_same, not_<>>, C>
  {
    using type = mp::copy_unique<C>;
  };

  template<class C>
  struct mk_remove_unique<lift_t<std::is_same, not_<>>, C>
  {
    using type = mp::copy_unique<C>;
  };

  template<class C>
  struct mk_remove_unique<same<not_<>>, C>
  {
    using type = mp::copy_unique<C>;
  };

  template<class F, class C>
  struct mk_remove_unique<tee<F, not_<>>, C>
  : mk_copy_unique<F, C>
  {};

  template<class C>
  struct mk_copy_unique<lift<std::is_same>, C>
  {
    using type = mp::copy_unique<C>;
  };

  template<class C>
  struct mk_copy_unique<lift_t<std::is_same>, C>
  {
    using type = mp::copy_unique<C>;
  };

  template<class C>
  struct mk_copy_unique<same<>, C>
  {
    using type = mp::copy_unique<C>;
  };

  template<class C>
  struct mk_copy_unique<lift<std::is_same, not_<>>, C>
  {
    using type = mp::remove_unique<C>;
  };

  template<class C>
  struct mk_copy_unique<lift_t<std::is_same, not_<>>, C>
  {
    using type = mp::remove_unique<C>;
  };

  template<class C>
  struct mk_copy_unique<same<not_<>>, C>
  {
    using type = mp::remove_unique<C>;
  };

  template<class F, class C>
  struct mk_copy_unique<tee<F, not_<>>, C>
  : mk_remove_unique<F, C>
  {};
}
/// \endcond
