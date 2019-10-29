#pragma once

#include "sfinae.hpp"
#include "call.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class F>
    struct _invoke;
  }

  template<class F, class... xs>
  using invoke = typename detail::dcall<(sizeof...(xs) < 1000000)>
    ::template f<detail::_invoke<sfinae<F>>, xs...>
    ::type;
}

#include "fork.hpp"

namespace jln::mp::detail
{
  struct _type
  {
    template<class T>
    struct f
    {
      using type = T;
    };
  };

  template<>
  struct _type::f<unsatisfactory_concept_error>;

  template<class WP, class WC>
  struct _invoke<when<WP, WC>>
  {
    template<class... xs>
    using f = typename mp::conditional<call<WP, xs...>>
      ::template f<fork<WC, _type>, unsatisfactory_concept>
      ::template f<xs...>;
  };
} // namespace jln::mp
