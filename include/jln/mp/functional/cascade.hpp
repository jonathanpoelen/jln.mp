#pragma once

namespace jln::mp
{
  namespace detail
  {
    template<class, class...>
    struct _cascade;
  }

  template<class F, class... Fs>
  using cascade = typename detail::_cascade<F, Fs...>::type;
}


#include "../algorithm/transform.hpp"
#include "../utility/unpack.hpp"

namespace jln::mp::detail
{
  // TODO _cascade<i>::f<....>
  template<class F, class... Fs>
  struct _cascade
  {
    using type = transform<unpack<typename _cascade<Fs...>::type>, F>;
  };

  template<class F0, class F1>
  struct _cascade<F0, F1>
  {
    using type = transform<unpack<F1>, F0>;
  };

  template<class F>
  struct _cascade<F>
  {
    using type = transform<F>;
  };
}
