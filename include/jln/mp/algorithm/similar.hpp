// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/same.hpp>
#include <jln/mp/detail/compiler.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
#if (JLN_MP_GCC || JLN_MP_CUDA) && JLN_MP_FEATURE_CONCEPTS
#  define JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT(name, TplType, Tpl, ...) \
     requires requires{ static_cast<TplType<Tpl>*>(nullptr); }                \
     struct name<__VA_ARGS__>
#  define JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT_CUDA(name, TplType, Tpl, ...) \
     struct name<__VA_ARGS__>
    template<class>
#elif JLN_MP_CUDA
#  define JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT(name, TplType, Tpl, ...) \
     struct name<__VA_ARGS__, decltype(static_cast<void(*)(TplType<Tpl>*)>(nullptr)(nullptr))>
#  define JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT_CUDA JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT
    template<class, class = void>
#else
#  define JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT(name, TplType, Tpl, ...) \
     struct name<__VA_ARGS__, std::void_t<TplType<Tpl>>>
#  define JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT_CUDA(name, TplType, Tpl, ...) \
     struct name<__VA_ARGS__>
    template<class, class = void>
#endif
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
  template<template<class...> class Tpl>
  struct tpl_type1 {};

  template<template<class T, JLN_MP_TPL_AUTO_OR(T)...> class Tpl>
  struct tpl_type2 {};

#if JLN_MP_ENABLE_TPL_AUTO
  template<template<auto...> class Tpl>
#else
  template<template<class, std::size_t...> class Tpl>
#endif
  struct tpl_type3;

  template<template<JLN_MP_TPL_AUTO_OR(std::size_t), class...> class Tpl>
  struct tpl_type4;


#if (JLN_MP_GCC || JLN_MP_CUDA) && JLN_MP_FEATURE_CONCEPTS
#  define JLN_MP_NORMALIZE_SIMILAR2 normalize_similar
#  define JLN_MP_NORMALIZE_SIMILAR3 normalize_similar
#  define JLN_MP_NORMALIZE_SIMILAR4 normalize_similar
  template<class T>
  struct normalize_similar
#else
#  if JLN_MP_CUDA
#    define JLN_MP_NORMALIZE_SIMILAR2 normalize_similar2
#    define JLN_MP_NORMALIZE_SIMILAR3 normalize_similar3
#    define JLN_MP_NORMALIZE_SIMILAR4 normalize_similar4
#  else
#    define JLN_MP_NORMALIZE_SIMILAR2 normalize_similar2
#    define JLN_MP_NORMALIZE_SIMILAR3 normalize_similar2
#    define JLN_MP_NORMALIZE_SIMILAR4 normalize_similar2
#  endif
  template<class T, class = void>
  struct JLN_MP_NORMALIZE_SIMILAR4
#endif
  {
    using type = T;
  };

#if JLN_MP_CUDA && !JLN_MP_FEATURE_CONCEPTS
  template<class T, class = void>
  struct normalize_similar3 : normalize_similar4<T>
  {};

  template<class T, class = void>
  struct normalize_similar2 : normalize_similar3<T>
  {};
#else
  // fix ambiguous
# if JLN_MP_ENABLE_TPL_AUTO
  template<template<auto> class Tpl, auto x>
# else
  template<template<auto> class Tpl, std::size_t x>
# endif
  JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT(JLN_MP_NORMALIZE_SIMILAR2, tpl_type3, Tpl, Tpl<x>)
  {
    using type = tpl_type3<Tpl>;
  };
#endif

  template<class T, template<class, JLN_MP_TPL_AUTO_OR(T)...> class Tpl, JLN_MP_TPL_AUTO_OR(T)... xs>
  JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT_CUDA(JLN_MP_NORMALIZE_SIMILAR2, tpl_type2, Tpl, Tpl<T, xs...>)
  {
    using type = tpl_type2<Tpl>;
  };

#if JLN_MP_ENABLE_TPL_AUTO
  template<template<auto...> class Tpl, auto... xs>
  JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT_CUDA(
    JLN_MP_NORMALIZE_SIMILAR3, tpl_type3, Tpl, Tpl<xs...>)
#else
  template<template<class, std::size_t...> class Tpl, class T, std::size_t... N>
  JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT_CUDA(JLN_MP_NORMALIZE_SIMILAR3, tpl_type3, Tpl, Tpl<T, N...>)
#endif
  {
    using type = tpl_type3<Tpl>;
  };

  template<template<JLN_MP_TPL_AUTO_OR(std::size_t), class...> class Tpl,
    JLN_MP_TPL_AUTO_OR(std::size_t) N, class... T>
  JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT_CUDA(
    JLN_MP_NORMALIZE_SIMILAR4, tpl_type4, Tpl, Tpl<N, T...>)
  {
    using type = tpl_type4<Tpl>;
  };

#if !((JLN_MP_GCC || JLN_MP_CUDA) && JLN_MP_FEATURE_CONCEPTS)
  template<class T, class>
  struct normalize_similar : normalize_similar2<T>
  {};
#endif

  template<template<class...> class Tpl, class... xs>
  JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT(normalize_similar, tpl_type1, Tpl, Tpl<xs...>)
  {
    using type = tpl_type1<Tpl>;
  };

#undef JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT
}
/// \endcond
