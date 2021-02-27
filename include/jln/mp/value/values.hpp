#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/value/val.hpp>

#if __cplusplus >= 201703L
namespace jln::mp
{
  /// \ingroup value

  template<class C = listify>
  struct values
  {
    template<class... xs>
    using f = call<C, val<xs::value>...>;
  };

  template<class C = listify>
  struct typed_values
  {
    template<class T, class... xs>
    using f = call<C, val<T(xs::value)>...>;
  };

  namespace emp
  {
    template<auto... xs>
    using values = list<val<xs>...>;

    template<class T, T... xs>
    using typed_values = list<val<T(xs)>...>;
  }
} // namespace jln::mp
#else
namespace jln::mp
{
  template<class C>
  struct values
  {
    template<class... xs>
    using f = call<C, typed_val<decltype(xs::value), xs::value>...>;
  };

  template<class C>
  struct typed_values
  {
    template<class T, class... xs>
    using f = call<C, typed_val<T, xs::value>...>;
  };

  namespace emp
  {
    template<class T, T... xs>
    using typed_values = list<typed_val<T, xs>...>;
  }
}
#endif
