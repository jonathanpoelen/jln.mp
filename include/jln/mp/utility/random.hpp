// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/utility/make_id.hpp>
#include <jln/mp/list/clear.hpp>

#if defined(__cpp_generic_lambdas) && __cpp_generic_lambdas >= 201707L

# if JLN_MP_CLANG
#   include <cstddef>
# endif

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class T, class Tag = default_make_id_tag>
    JLN_MP_CONSTEVAL_OR_CONSTEXPR unsigned next_random_for();
  }
  /// \endcond

  /// \ingroup utility

#ifdef JLN_MP_DOXYGENATING
/// Z value for the seed of random.
# define JLN_MP_RANDOM_SEED_Z 0
/// W value for the seed of random.
# define JLN_MP_RANDOM_SEED_W 0
/// Less than 0 to not rely on the \c __TIME__ macro (default) ;
/// 0 for use \c __TIME__ macro as seed ;
/// greater than 0 for used this value as a replacement of \c __TIME__ macro.
# define JLN_MP_RANDOM_SEED_TIME -1
#endif

  namespace emp
  {
    /// Generates a random number per type for a specified tag.
    template<class T, class Tag = default_make_id_tag>
    inline constexpr unsigned random_of_v = detail::next_random_for<list<T>, Tag>();

    /// Generates a random number per type for a specified tag.
    template<class T, class Tag = default_make_id_tag, auto v = []{}>
    using random_of = number<detail::next_random_for<list<T>, Tag>()>;

    /// Generates a random number per call for a specified tag.
    template<class Tag = default_make_id_tag, auto v = []{}>
    inline constexpr unsigned random_v = detail::next_random_for<decltype(v), Tag>();

    /// Generates a random number per call for a specified tag.
    template<class Tag = default_make_id_tag, auto v = []{}>
    using random = number<detail::next_random_for<decltype(v), Tag>()>;
  }

  /// Generate a random number for a specified tag on each call with different \c xs.
  /// \treturn \number
  template<class Tag = default_make_id_tag, class C = identity, auto = []{}>
  struct random_for
  #ifdef JLN_MP_DOXYGENATING
  {
    template<class... xs>
    using f;
  }
  #endif
  ;

  template<class C = identity, auto v = []{}>
  using random = random_for<default_make_id_tag, C, v>;


/// \cond
#if JLN_MP_MEMOIZED_ALIAS
  namespace detail
  {
    template<class...>
    class rand_marker;
  }

  template<class Tag, class C, auto v>
  struct random_for
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      number<detail::next_random_for<detail::rand_marker<decltype(v), xs...>, Tag>()>
    );
  };

  template<class Tag, auto v>
  struct random_for<Tag, identity, v>
  {
    template<class... xs>
    using f
      = number<detail::next_random_for<detail::rand_marker<decltype(v), xs...>, Tag>()>;
  };
#else // if ! JLN_MP_MEMOIZED_ALIAS
  namespace detail
  {
    template<class Tag, class...>
    struct random_impl
    {
      using type = number<detail::next_random_for<random_impl, Tag>()>;
    };
  }

  template<class Tag, class C, auto v>
  struct random_for
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::random_impl<Tag, decltype(v), xs...>::type
    );
  };

  template<class Tag, auto v>
  struct random_for<Tag, identity, v>
  {
    template<class... xs>
    using f = typename detail::random_impl<Tag, decltype(v), xs...>::type;
  };
#endif
/// \endcond
}

namespace jln::mp::detail
{
  template<unsigned Z, unsigned W>
  struct random_data
  {
    // algorithm found on https://www.codeproject.com/Articles/25172/Simple-Random-Number-Generation
    using next = random_data<
      36969 * (Z & 65535) + (Z >> 16),
      18000 * (W & 65535) + (W >> 16)
    >;
    static constexpr unsigned value = (Z << 16) + W;
  };

  template<class Tag>
  class random_tag;

  #ifndef JLN_MP_RANDOM_SEED_Z
  #  define JLN_MP_RANDOM_SEED_Z 0
  #endif
  #ifndef JLN_MP_RANDOM_SEED_W
  #  define JLN_MP_RANDOM_SEED_W 0
  #endif
  #ifndef JLN_MP_RANDOM_SEED_TIME
  #  define JLN_MP_RANDOM_SEED_TIME -1
  #endif

  #if JLN_MP_RANDOM_SEED_TIME >= 0
  #  if JLN_MP_RANDOM_SEED_TIME == 0
  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Wdate-time")
  constexpr unsigned t = unsigned((__TIME__[0] * 10 + __TIME__[1]) * 3600
                                + (__TIME__[3] * 10 + __TIME__[4]) * 60
                                + (__TIME__[6] * 10 + __TIME__[7]));
  JLN_MP_DIAGNOSTIC_POP()
  #    undef JLN_MP_RANDOM_SEED_TIME
  #    define JLN_MP_RANDOM_SEED_TIME t
  #  endif
  #  if JLN_MP_RANDOM_SEED_Z == 0
  #    undef JLN_MP_RANDOM_SEED_Z
  #    define JLN_MP_RANDOM_SEED_Z \
          (JLN_MP_RANDOM_SEED_TIME >> 16) ? (JLN_MP_RANDOM_SEED_TIME >> 16) : 362436069
  #  endif
  #  if JLN_MP_RANDOM_SEED_W == 0
  #    undef JLN_MP_RANDOM_SEED_W
  #    define JLN_MP_RANDOM_SEED_W \
          (JLN_MP_RANDOM_SEED_TIME % 4294967296) ? (JLN_MP_RANDOM_SEED_TIME % 4294967296) : 521288629
  #  endif
  #else
  #  if JLN_MP_RANDOM_SEED_Z == 0
  #    undef JLN_MP_RANDOM_SEED_Z
  #    define JLN_MP_RANDOM_SEED_Z 362436069
  #  endif
  #  if JLN_MP_RANDOM_SEED_W == 0
  #    undef JLN_MP_RANDOM_SEED_W
  #    define JLN_MP_RANDOM_SEED_W 521288629
  #  endif
  #endif

  template<int id, class Tag>
  struct get_random_data
  {
    using type = emp::type_of<id-1, Tag>;
  };

  template<class Tag>
  struct get_random_data<0, Tag>
  {
    using type = random_data<JLN_MP_RANDOM_SEED_Z, JLN_MP_RANDOM_SEED_W>;
  };

  #undef JLN_MP_RANDOM_SEED_Z
  #undef JLN_MP_RANDOM_SEED_W
  #undef JLN_MP_RANDOM_SEED_TIME

  template<class T, class Tag>
  JLN_MP_CONSTEVAL_OR_CONSTEXPR unsigned next_random_for()
  {
    constexpr int id = mkid::get_next_id<T*, random_tag<Tag>>();
    using data = typename get_random_data<id, random_tag<Tag>>::type;
    void(mkid::injecter<id, typename data::next*, random_tag<Tag>>{});
    return data::value;
  }
}

#endif
