#pragma once

#include <jln/mp/algorithm/same.hpp>
#include <jln/mp/detail/compiler.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
#if JLN_MP_CLANG
# define JLN_MP_NORMALIZE_SIMILAR_EXTRA_PARAM(...)
#else
# define JLN_MP_NORMALIZE_SIMILAR_EXTRA_PARAM(...) , __VA_ARGS__
#endif
    template<class JLN_MP_NORMALIZE_SIMILAR_EXTRA_PARAM(class = void)>
    struct normalize_similar;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether all types are the same or instantiations of the same class template.
  /// The list of supported class templates are:
  ///   - `template<class...>`
  ///   - `template<class T, T...>`
  ///   - `template<class, std::size_t>`
  ///   - `template<std::size_t, class...>`
  ///   - `template<class, auto...>` (when supported)
  ///   - `template<auto, class...>` (when supported)
  ///   - `template<auto...>` (when supported)
  /// \treturn \bool
  template<class C = identity>
  struct similar
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::same_impl<sizeof...(xs) < 3 ? sizeof...(xs) : 3>
        ::template f<typename detail::normalize_similar<xs>::type...>
    );
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using similar = unpack<L, mp::similar<C>>;

#ifdef JLN_MP_DOXYGENATING
    template<class x, class y>
    using is_similar = similar<>::f<x, y>;
#else
    template<class x, class y>
    using is_similar = detail::same_impl<2>::f<
      typename detail::normalize_similar<x>::type,
      typename detail::normalize_similar<y>::type
    >;
#endif
  }
}


/// \cond
namespace jln::mp
{
  template<>
  struct similar<identity>
  {
    template<class... xs>
    using f = typename detail::same_impl<sizeof...(xs) < 3 ? sizeof...(xs) : 3>
      ::template f<typename detail::normalize_similar<xs>::type...>;
  };
}

namespace jln::mp::detail
{
  template<class T JLN_MP_NORMALIZE_SIMILAR_EXTRA_PARAM(class)>
  struct normalize_similar
  {
    using type = T;
  };

  template<template<class...> class Tpl>
  struct tpl_type1 {};

  template<template<class...> class Tpl, class... xs>
  struct normalize_similar<Tpl<xs...>>
  {
    using type = tpl_type1<Tpl>;
  };

  // fix ambiguous
  template<template<class> class Tpl, class x>
  struct normalize_similar<Tpl<x> JLN_MP_NORMALIZE_SIMILAR_EXTRA_PARAM(std::void_t<tpl_type1<Tpl>>)>
  {
    using type = tpl_type1<Tpl>;
  };

  template<template<class T, JLN_MP_TPL_AUTO_OR(T)...> class Tpl>
  struct tpl_type2 {};

  template<class T, template<class, JLN_MP_TPL_AUTO_OR(T)...> class Tpl, JLN_MP_TPL_AUTO_OR(T)... xs>
  struct normalize_similar<Tpl<T, xs...>>
  {
    using type = tpl_type2<Tpl>;
  };

#if JLN_MP_ENABLE_TPL_AUTO
  template<template<auto...> class Tpl>
  struct tpl_type3 {};

  // fix ambiguous
  template<template<auto> class Tpl, auto x>
  struct normalize_similar<Tpl<x> JLN_MP_NORMALIZE_SIMILAR_EXTRA_PARAM(std::void_t<tpl_type3<Tpl>>)>
  {
    using type = tpl_type3<Tpl>;
  };

  template<template<auto...> class Tpl, auto... xs>
  struct normalize_similar<Tpl<xs...>>
#else
  template<template<class, std::size_t...> class Tpl>
  struct tpl_type3;

  // fix ambiguous
  template<template<auto> class Tpl, std::size_t x>
  struct normalize_similar<Tpl<x> JLN_MP_NORMALIZE_SIMILAR_EXTRA_PARAM(std::void_t<tpl_type3<Tpl>>)>
  {
    using type = tpl_type3<Tpl>;
  };

  template<template<class, std::size_t...> class Tpl, class T, std::size_t... N>
  struct normalize_similar<Tpl<T, N>>
#endif
  {
    using type = tpl_type3<Tpl>;
  };

  template<template<JLN_MP_TPL_AUTO_OR(std::size_t), class...> class Tpl>
  struct tpl_type4;

  template<template<JLN_MP_TPL_AUTO_OR(std::size_t), class...> class Tpl,
    JLN_MP_TPL_AUTO_OR(std::size_t) N, class... T>
  struct normalize_similar<Tpl<N, T...>>
  {
    using type = tpl_type4<Tpl>;
  };

}

#undef JLN_MP_NORMALIZE_SIMILAR_EXTRA_PARAM
/// \endcond
