// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/make_id.hpp>
#include <jln/mp/list/clear.hpp>

#ifdef __cpp_generic_lambdas
#if __cpp_generic_lambdas >= 201707L

namespace jln::mp
{
  /// \ingroup functional

  /// \cond
  namespace detail::rand
  {
    JLN_MP_DIAGNOSTIC_PUSH()
    JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wnon-template-friend")
    template<int X>
    struct flag
    {
      friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto f(flag<X>);
    };
    JLN_MP_DIAGNOSTIC_POP()

    struct random_data
    {
      unsigned z;
      unsigned w;
    };

    template<int X, unsigned z, unsigned w>
    struct injecter
    {
      friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto f(flag<X>) { return random_data{z,w}; }
    };

    #ifndef JLN_MP_RANDOM_SEED_Z
    #   define JLN_MP_RANDOM_SEED_Z 0
    #endif
    #ifndef JLN_MP_RANDOM_SEED_W
    #   define JLN_MP_RANDOM_SEED_W 0
    #endif
    // -1 -> do not use __TIME__
    // 0 -> use __TIME__
    // >= 0 -> use value as __TIME__
    #ifndef JLN_MP_RANDOM_SEED_TIME
    #   define JLN_MP_RANDOM_SEED_TIME -1
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
    #    define JLN_MP_RANDOM_SEED_Z \
           (JLN_MP_RANDOM_SEED_TIME >> 16) ? (JLN_MP_RANDOM_SEED_TIME >> 16) : 362436069
    #  endif
    #  if JLN_MP_RANDOM_SEED_W == 0
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

    inline JLN_MP_CONSTEVAL_OR_CONSTEXPR auto f(flag<0>)
    {
      return random_data{JLN_MP_RANDOM_SEED_Z, JLN_MP_RANDOM_SEED_W};
    }

    #undef JLN_MP_RANDOM_SEED_Z
    #undef JLN_MP_RANDOM_SEED_W
    #undef JLN_MP_RANDOM_SEED_TIME

    /// \pre id >= 1
    /// \pre random_for_id<id-1>() must have been called
    template<int id>
    JLN_MP_CONSTEVAL_OR_CONSTEXPR unsigned random_for_id()
    {
      constexpr auto data = f(flag<id-1>{});
      // algorithm found on https://www.codeproject.com/Articles/25172/Simple-Random-Number-Generation
      constexpr unsigned z = 36969 * (data.z & 65535) + (data.z >> 16);
      constexpr unsigned w = 18000 * (data.w & 65535) + (data.w >> 16);
      void(injecter<id, z, w>{});
      return (z << 16) + w;
    }

    template<auto v = []{}>
    JLN_MP_CONSTEVAL_OR_CONSTEXPR unsigned next_random()
    {
      return random_for_id<next_id<random_data, 1, v>()>();
    }
  }
  /// \endcond

  /// Generates a unique id per call for a specified tag.
  /// Signature: `unsigned next_random<auto = []{}>()`
  using detail::rand::next_random;

  namespace emp
  {
    template<auto v = []{}>
    using random = number<next_random<v>()>;

    template<auto v = []{}>
    static constexpr unsigned random_v = next_random<v>();
  }

  /// Generate a random number.
  /// The seed can be configured with `JLN_MP_RANDOM_SEED_TIME`
  /// or `JLN_MP_RANDOM_SEED_W` and `JLN_MP_RANDOM_SEED_Z`
  /// \treturn \number
  template<class C = identity, auto = []{}>
  struct random
  #ifdef JLN_MP_DOXYGENATING
  {
    template<class... xs>
    using f;
  }
  #endif
  ;

/// \cond
#if JLN_MP_CLANG
  namespace detail
  {
    template<std::size_t, auto v = []{}>
    using random_impl = number<next_random<v>()>;
  }

  template<class C, auto>
  struct random
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, detail::random_impl<sizeof...(xs)>);
  };

  template<auto v>
  struct random<identity, v>
  {
    template<class... xs>
    using f = detail::random_impl<sizeof...(xs)>;
  };
#else
  template<class C, auto>
  struct random
  {
    template<class...>
    using f = JLN_MP_CALL_TRACE(C, number<next_random<[]{}>()>);
  };

  template<auto v>
  struct random<identity, v>
  {
    template<class...>
    using f = number<next_random<[]{}>()>;
  };
#endif
/// \endcond
}

#endif
#endif
