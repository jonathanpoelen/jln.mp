#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/list/list.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct ends_with_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks if the \sequence ends with the given prefix.
  /// \treturn \bool
  /// \see ends_with
  template<class Seq, class C = identity>
  struct ends_with
  {};

  template<class... Ts, class C>
  struct ends_with<list<Ts...>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::ends_with_impl<sizeof...(Ts) <= sizeof...(xs)>
      ::template f<sizeof...(Ts), list<Ts...>, xs...>
    );
  };

  namespace emp
  {
    template<class L, class Seq, class C = mp::identity>
    using ends_with = unpack<ends_with<Seq, C>, L>;
  }
}

/// \cond
#include <jln/mp/list/take_back.hpp>
#include <jln/mp/utility/is.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/conditional.hpp>

namespace jln::mp::detail
{
  template<>
  struct ends_with_impl<true>
  {
    template<unsigned n, class L, class... xs>
    using f = number<std::is_same<typename take_back_c<n>::template f<xs...>, L>::value>;
  };

  template<>
  struct ends_with_impl<false>
  {
    template<unsigned n, class L, class... xs>
    using f = false_;
  };
}

namespace jln::mp
{
  template<class... Ts>
  struct ends_with<list<Ts...>, identity>
  {
    template<class... xs>
    using f = typename detail::ends_with_impl<sizeof...(Ts) <= sizeof...(xs)>
      ::template f<sizeof...(Ts), list<Ts...>, xs...>;
  };

  template<class T, class C>
  struct ends_with<list<T>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename conditional_c<1 <= sizeof...(xs)>
      ::template f<take_back_c<1, is<T>>, always<false_>>
      ::template f<xs...>
    );
  };

  template<class T>
  struct ends_with<list<T>, identity>
  {
    template<class... xs>
    using f = typename conditional_c<1 <= sizeof...(xs)>
      ::template f<take_back_c<1, is<T>>, always<false_>>
      ::template f<xs...>;
  };

  template<class C>
  struct ends_with<list<>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, true_);
  };

  template<>
  struct ends_with<list<>, identity>
  {
    template<class... xs>
    using f = true_;
  };
}
/// \endcond
