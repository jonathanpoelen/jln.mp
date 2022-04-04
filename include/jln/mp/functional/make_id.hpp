#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/detail/compiler.hpp>

#ifdef __cpp_generic_lambdas
#if __cpp_generic_lambdas >= 201707L

# ifdef __cpp_consteval
#   if __cpp_consteval >= 201811L
#     define JLN_MP_CONSTEVAL_OR_CONSTEXPR consteval
#   endif
# endif
# ifndef JLN_MP_CONSTEVAL_OR_CONSTEXPR
#   define JLN_MP_CONSTEVAL_OR_CONSTEXPR constexpr
# endif

namespace jln::mp
{
  /// \ingroup functional

  class default_make_id_tag {};

  /// \cond
  namespace detail::mkid
  {
    JLN_MP_DIAGNOSTIC_PUSH()
    JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wnon-template-friend")
    template <class T, int X>
    struct flag
    {
      friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto f(flag<T, X>);
    };
    JLN_MP_DIAGNOSTIC_POP()

    template <class T, int X>
    struct injecter
    {
      friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto f(flag<T, X>) { return X; }
    };

    template <class T = default_make_id_tag, int X = 0, auto v = []{}>
    JLN_MP_CONSTEVAL_OR_CONSTEXPR auto next_id()
    {
      if constexpr (requires { f(flag<T, X+10>{}); }) {
        if constexpr (requires { f(flag<T, X+100>{}); }) {
          if constexpr (requires { f(flag<T, X+1000>{}); }) {
            if constexpr (requires { f(flag<T, X+10000>{}); }) {
              return next_id<T, X+10001, v>();
            }
            else if constexpr (requires { f(flag<T, X+3000>{}); }) {
              return next_id<T, X+3001, v>();
            }
            else {
              return next_id<T, X+1001, v>();
            }
          }
          else if constexpr (requires { f(flag<T, X+300>{}); }) {
            return next_id<T, X+301, v>();
          }
          else {
            return next_id<T, X+101, v>();
          }
        }
        else if constexpr (requires { f(flag<T, X+30>{}); }) {
          return next_id<T, X+31, v>();
        }
        else {
          return next_id<T, X+11, v>();
        }
      }
      else if constexpr (requires { f(flag<T, X>{}); }) {
        if constexpr (requires { f(flag<T, X+2>{}); }) {
          if constexpr (requires { f(flag<T, X+4>{}); }) {
            return next_id<T, X+5, v>();
          }
          else if constexpr (requires { f(flag<T, X+3>{}); }) {
            return next_id<T, X+4, v>();
          }
          else {
            return next_id<T, X+3, v>();
          }
        }
        else if constexpr (requires { f(flag<T, X+1>{}); }) {
            return next_id<T, X+2, v>();
        }
        else {
            return next_id<T, X+1, v>();
        }
      }
      else {
        void(injecter<T, X>{});
        return f(flag<T, X>{});
      }
    }
  }
  /// \endcond

  using detail::mkid::next_id;

  /// Generates a unique id per type.
  template<class T>
  struct id_of
  {
    static constexpr int value = next_id<default_make_id_tag, 0, []{}>();
  };

  template<class T>
  static constexpr int id_of_v = id_of<T>::value;

  template<class T>
  using id_of_t = number<id_of<T>::value>;


  /// Generates a unique id per type for a specified tag.
  template<class Tag, class T>
  struct tagged_id_of
  {
    static constexpr int value = next_id<Tag, 0, []{}>();
  };

  template<class Tag, class T>
  static constexpr int tagged_id_of_v = tagged_id_of<Tag, T>::value;

  template<class Tag, class T>
  using tagged_id_of_t = number<tagged_id_of<Tag, T>::value>;


  /// Generates a unique id per type.
  /// \treturn \number
  template<class Tag, class C = identity>
  struct make_id_for
  {
    template<class T>
    using f = JLN_MP_CALL_TRACE(C, tagged_id_of_t<Tag, T>);
  };

  template<class C = identity>
  using make_id = make_id_for<default_make_id_tag, C>;

  /// \cond
  template<class T>
  struct tagged_id_of<default_make_id_tag, T>
  : id_of<T>
  {};

  template<>
  struct make_id_for<default_make_id_tag, identity>
  {
    template<class T>
    using f = id_of_t<T>;
  };

  template<class Tag>
  struct make_id_for<Tag, identity>
  {
    template<class T>
    using f = tagged_id_of_t<Tag, T>;
  };

  template<class C>
  struct make_id_for<default_make_id_tag, C>
  {
    template<class T>
    using f = JLN_MP_CALL_TRACE(C, id_of_t<T>);
  };
  /// \endcond
}

#endif
#endif
