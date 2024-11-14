// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/list/list.hpp>

namespace jln::mp
{
  namespace detail
  {
    struct false_fn_impl
    {
      static false_ impl(...);
    };
  }
  /// \ingroup algorithm

  /// Checks if the \sequence begins with the given prefix.
  /// \treturn \bool
  /// \see ends_with, remove_suffix, remove_prefix
  template<class Seq, class C = identity>
  struct starts_with
  {};

#ifdef JLN_MP_DOXYGENATING
  template<class... Ts, class C>
  struct starts_with<list<Ts...>, C>
  {
    template<class... xs>
    using f;
  };
#elif !JLN_MP_GCC
  // doing a specialization with C=identity is 4% slower with clang,
  // but 4% faster with gcc thanks to memoization
  template<class... Ts, class C>
  struct starts_with<list<Ts...>, C> : detail::false_fn_impl
  {
    using false_fn_impl::impl;

    template<class... Us>
    static true_ impl(list<Ts..., Us...>*);

    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, decltype(impl(static_cast<list<xs...>*>(nullptr))));
  };
#else
# if JLN_MP_FEATURE_CONCEPTS
  template<class... Ts>
  struct starts_with<list<Ts...>, identity>
  {
    template<class... Us>
    static void impl(list<Ts..., Us...>*);

    template<class... xs>
    using f = number<requires { impl(static_cast<list<xs...>*>(nullptr)); }>;
  };
# else
  template<class... Ts>
  struct starts_with<list<Ts...>, identity> : detail::false_fn_impl
  {
    using false_fn_impl::impl;

    template<class... Us>
    static true_ impl(list<Ts..., Us...>*);

    template<class... xs>
    using f = decltype(impl(static_cast<list<xs...>*>(nullptr)));
  };
# endif

  template<class... Ts, class C>
  struct starts_with<list<Ts...>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      decltype(starts_with<list<Ts...>>::impl(static_cast<list<xs...>*>(nullptr)))
    );
  };
#endif

  namespace emp
  {
    template<class L, class Seq, class C = mp::identity>
    using starts_with = typename detail::_unpack<starts_with<Seq, C>, L>::type;

    template<class L, class Seq, class C = mp::identity>
    inline constexpr bool starts_with_v = detail::_unpack<starts_with<Seq, C>, L>::type::value;
  }
}


#include <jln/mp/algorithm/drop_while_xs.hpp>
#include <jln/mp/algorithm/take_while_xs.hpp>
#include <jln/mp/algorithm/index.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/is.hpp>

/// \cond
namespace jln::mp
{
  namespace detail
  {
    template<bool>
    struct starts_with1_impl : always<false_>
    {};

    template<>
    struct starts_with1_impl<true>
    {
      template<class T, class x, class... xs>
      using f = number<JLN_MP_IS_SAME(T, x)>;
    };
  }


  template<class T, class C>
  struct starts_with<list<T>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::starts_with1_impl<1 <= sizeof...(xs)>
      ::template f<T, xs...>
    );
  };

  template<class T>
  struct starts_with<list<T>, identity>
  {
    template<class... xs>
    using f = typename detail::starts_with1_impl<1 <= sizeof...(xs)>
      ::template f<T, xs...>;
  };


  template<class C>
  struct starts_with<list<>, C>
  {
    template<class... xs>
    using f = JLN_MP_FORCE_DCALL_TRACE_XS(xs, C, true_);
  };

  template<>
  struct starts_with<list<>, identity> : always<true_>
  {};
}

namespace jln::mp::detail
{
  template<class C>
  struct optimized_starts_with_empty
  {
    using type = if_<size<>, always<true_, C>>;
  };

  template<>
  struct optimized_starts_with_empty<identity>
  {
    using type = size<>;
  };


  template<int_>
  struct optimized_index_if_xs_starts_with;

  template<>
  struct optimized_index_if_xs_starts_with<0>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = if_<typename optimized_starts_with_empty<C>::type, always<number<0>, TC>, FC>;
  };

  template<>
  struct optimized_index_if_xs_starts_with<1>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = index_if<is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_index_if_xs_starts_with<2>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = partial_index_if_xs_c<-int_(sizeof...(Ts)),
      starts_with<list<Ts...>, C>, TC, FC>;
  };
}

namespace jln::mp
{
  // optimize index_if_xs with starts_with
  template<class... Ts, class C, class TC, class FC>
  struct index_if_xs<starts_with<list<Ts...>, C>, TC, FC>
  : detail::optimized_index_if_xs_starts_with<sizeof...(Ts) < 2 ? sizeof...(Ts) : 2>
    ::template f<C, TC, FC, Ts...>
  {};
}

namespace jln::mp::detail
{
  template<int_>
  struct optimized_drop_while_starts_with;

  template<>
  struct optimized_drop_while_starts_with<0>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = if_<typename optimized_starts_with_empty<C>::type, clear<TC>, FC>;
  };

  template<>
  struct optimized_drop_while_starts_with<1>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = drop_while<is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_drop_while_starts_with<2>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = partial_drop_while_xs_c<-int_(sizeof...(Ts)),
      starts_with<list<Ts...>, C>, TC, FC>;
  };
}

namespace jln::mp
{
  template<class... Ts, class C, class TC, class FC>
  struct drop_while_xs<starts_with<list<Ts...>, C>, TC, FC>
  : detail::optimized_drop_while_starts_with<sizeof...(Ts) < 2 ? sizeof...(Ts) : 2>
    ::template f<C, TC, FC, Ts...>
  {};
}

namespace jln::mp::detail
{
  template<int_>
  struct optimized_take_while_starts_with;

  template<>
  struct optimized_take_while_starts_with<0>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = if_<typename optimized_starts_with_empty<C>::type, TC, FC>;
  };

  template<>
  struct optimized_take_while_starts_with<1>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = take_while<is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_take_while_starts_with<2>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = partial_take_while_xs_c<-int_(sizeof...(Ts)),
      starts_with<list<Ts...>, C>, TC, FC>;
  };
}

namespace jln::mp
{
  template<class... Ts, class C, class TC, class FC>
  struct take_while_xs<starts_with<list<Ts...>, C>, TC, FC>
  : detail::optimized_take_while_starts_with<sizeof...(Ts) < 2 ? sizeof...(Ts) : 2>
    ::template f<C, TC, FC, Ts...>
  {};
}

namespace jln::mp::detail
{
  template<int_>
  struct optimized_take_while_extended_by_n_starts_with;

  template<>
  struct optimized_take_while_extended_by_n_starts_with<0>
  {
    template<std::size_t ExtendedByN, class C, class TC, class FC, class... Ts>
    using f = if_<typename optimized_starts_with_empty<C>::type, TC, FC>;
  };

  template<>
  struct optimized_take_while_extended_by_n_starts_with<1>
  {
    template<std::size_t ExtendedByN, class C, class TC, class FC, class... Ts>
    using f = take_while_extended_by_n_c<ExtendedByN, is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_take_while_extended_by_n_starts_with<2>
  {
    template<std::size_t ExtendedByN, class C, class TC, class FC, class... Ts>
    using f = partial_take_while_extended_by_n_xs_c<
      -int_(sizeof...(Ts)), ExtendedByN, starts_with<list<Ts...>, C>, TC, FC
    >;
  };
}

namespace jln::mp
{
  template<std::size_t ExtendedByN, class... Ts, class C, class TC, class FC>
  struct take_while_extended_by_n_xs_c<ExtendedByN, starts_with<list<Ts...>, C>, TC, FC>
  : detail::optimized_take_while_extended_by_n_starts_with<sizeof...(Ts) < 2 ? sizeof...(Ts) : 2>
    ::template f<C, TC, FC, Ts...>
  {};
}
/// \endcond
